#include "InventoryList.h"

#include "skse64/GameExtraData.h"  // InventoryEntryData
#include "skse64/GameFormComponents.h"  // TESFullName
#include "skse64/GameForms.h"  // TESForm
#include "skse64/GameRTTI.h"  // DYNAMIC_CAST

#include <algorithm>  // sort
#include <utility>  // pair
#include <exception>  // exception
#include <map>  // map
#include <vector>  // vector

#include "LootMenu.h"

#include "RE/BaseExtraList.h"  // BaseExtraList
#include "RE/InventoryEntryData.h"  // RE::InventoryEntryData
#include "RE/TESObjectREFR.h"  // TESObjectREFR
#include "RE/TESObjectLIGH.h"  // RE::TESObjectLIGH


namespace QuickLootRE
{
	InventoryList::InventoryList() :
		_toDelete(end()),
		_deleteCount(0)
	{}


	InventoryList::~InventoryList()
	{
		clear();
	}


	void InventoryList::parseInventory(RE::BaseExtraList* a_xList, RE::TESObjectREFR* a_refr)
	{
		clear();
		ItemData::setContainer(a_refr);

		// Default container
		TESContainerVisitor containerOp(_defaultMap);
		a_refr->GetContainer()->Visit(containerOp);

		// Extra container changes
		ExtraContainerChanges* xContainerChanges = static_cast<ExtraContainerChanges*>(a_xList->GetByType(kExtraData_ContainerChanges));
		EntryDataListVisitor entryDataListOp(_defaultMap);
		if (xContainerChanges && xContainerChanges->data && xContainerChanges->data->objList) {
			xContainerChanges->data->objList->Visit(entryDataListOp);
		}

		// Add remaining default items
		for (auto& it : _defaultMap) {
			add(it.second.first, it.second.second);
		}

		std::sort(_itemList.rbegin(), _itemList.rend());
	}


	ItemData& InventoryList::operator[](UInt32 a_pos)
	{
		return _itemList[a_pos];
	}


	std::vector<ItemData>::iterator InventoryList::begin() noexcept
	{
		return _itemList.begin();
	}


	std::vector<ItemData>::iterator InventoryList::end() noexcept
	{
		return _itemList.end();
	}


	bool InventoryList::empty()
	{
		return _itemList.empty();
	}


	UInt32 InventoryList::size()
	{
		return _itemList.size();
	}


	void InventoryList::clear()
	{
		ItemData::setContainer(0);
		_defaultMap.clear();
		_itemList.clear();
		for (auto& entryData : _heapList) {
			entryData->Delete();
		}
		_heapList.clear();
		_toDelete = end();
		_deleteCount = 0;
	}


	std::vector<ItemData>::iterator InventoryList::erase(std::vector<ItemData>::iterator a_pos)
	{
		return _itemList.erase(a_pos);
	}


	void InventoryList::add(RE::InventoryEntryData* a_entryData)
	{
		if (isValidItem(a_entryData->type)) {
			_itemList.emplace_back(a_entryData);
		}
	}


	void InventoryList::add(RE::InventoryEntryData* a_entryData, SInt32 a_count)
	{
		if (isValidItem(a_entryData->type)) {
			_itemList.emplace_back(a_entryData, a_count);
		}
	}


	void InventoryList::add(TESForm* a_form, SInt32 a_count)
	{
		RE::InventoryEntryData* entryData = RE::InventoryEntryData::Create(a_form, a_count);
		_heapList.push_back(entryData);
		add(entryData);
	}


	bool InventoryList::isValidItem(TESForm* a_item)
	{
		if (!a_item) {
			return false;
		}

		if (a_item->formType == kFormType_LeveledItem) {
			return false;
		}

		if (a_item->formType == kFormType_Light) {
			RE::TESObjectLIGH* light = static_cast<RE::TESObjectLIGH*>(a_item);
			if (!light->CanBeCarried()) {
				return false;
			}
		} else if (!a_item->IsPlayable()) {
			return false;
		}

		TESFullName* fullName = 0;
		try {
			static BSFixedString emptyStr = "";
			fullName = DYNAMIC_CAST(a_item, TESForm, TESFullName);
			if (!fullName || fullName->name == emptyStr) {
				return false;
			}
		} catch (std::exception& e) {
			_ERROR("[ERROR] Form (0x%X) does not have TESFullName (%i)\n", a_item->formID, a_item->formType);
			_ERROR(e.what());
			return false;
		}

		return true;
	}


	InventoryList::TESContainerVisitor::TESContainerVisitor(std::map<FormID, std::pair<TESForm*, Count>>& a_defaultMap) :
		_defaultMap(a_defaultMap)
	{}


	bool InventoryList::TESContainerVisitor::Accept(TESContainer::Entry* a_entry)
	{
		_defaultMap.emplace(a_entry->form->formID, std::pair<TESForm*, Count>(a_entry->form, a_entry->count));
		return true;
	}


	InventoryList::EntryDataListVisitor::EntryDataListVisitor(std::map<FormID, std::pair<TESForm*, Count>>& a_defaultMap) :
		_defaultMap(a_defaultMap)
	{}


	bool InventoryList::EntryDataListVisitor::Accept(InventoryEntryData* a_entryData)
	{
		RE::InventoryEntryData* entryData = reinterpret_cast<RE::InventoryEntryData*>(a_entryData);

		if (!entryData) {
			return true;
		}

		auto it = _defaultMap.find(entryData->type->formID);
		if (it != _defaultMap.end()) {
			SInt32 count = it->second.second + entryData->countDelta;
			if (count > 0) {
				g_invList.add(entryData, count);
			}
			_defaultMap.erase(entryData->type->formID);
		} else if (entryData->countDelta > 0) {
			g_invList.add(entryData);
		}

		return true;
	}


	InventoryList g_invList;
}
