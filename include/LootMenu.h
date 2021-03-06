#pragma once

#undef PlaySound

#include "skse64/GameTypes.h"  // BSFixedString

#include <string>  // string

#include "RE/BSIInputDevice.h"  // BSIInputDevice
#include "RE/IMenu.h"  // IMenu
#include "RE/MenuEventHandler.h"  // MenuEventHandler
#include "RE/TESObjectREFR.h"  // TESObjectREFR

class InputEvent;
class TESObjectREFR;
class UIMessage;

namespace RE
{
	class ButtonEvent;
}


namespace QuickLootRE
{
	class ItemData;


	class LootMenuCreator
	{
	public:
		static RE::IMenu* Create();

	private:
		LootMenuCreator();
	};


	class LootMenu :
		public RE::IMenu,
		public RE::MenuEventHandler
	{
	private:
		friend class LootMenuCreator;

	public:
		enum Platform : UInt32
		{
			kPlatform_PC	= 0,
			kPlatform_Other	= 2
		};


		enum Scaleform : UInt32
		{
			kScaleform_SetKeyMappings,
			kScaleform_SetPlatform,
			kScaleform_SetSelectedIndex,
			kScaleform_Setup,
			kScaleform_SetContainer,
			kScaleform_OpenContainer,
			kScaleform_CloseContainer,
			kScaleform_UpdateButtons,
			kScaleform_SwitchStyle
		};


		enum Style : UInt32
		{
			kStyle_Default	= 0,
			kStyle_Dialogue	= 1
		};

	protected:
		LootMenu(const char* a_swfPath);
		virtual ~LootMenu();

	public:
		static LootMenu*			GetSingleton();
		static SInt32				GetSelectedIndex();
		static void					ModSelectedIndex(SInt32 a_indexOffset);
		static void					SetDisplaySize(SInt32 a_size);
		static RE::TESObjectREFR*	GetContainerRef();
		static bool					IsOpen();
		static bool					IsVisible();
		static bool					InTakeAllMode();
		static Platform				GetPlatform();
		static BSFixedString		GetName();
		static const char*			GetActiText();
		static void					SetActiText(const char* a_actiText);
		static const char*			GetSingleLootMapping();
		static void					SetSingleLootMapping(const char* a_singLootMapping);
		static const char*			GetTakeMapping();
		static void					SetTakeMapping(const char* a_takeStr);
		static const char*			GetTakeAllMapping();
		static void					SetTakeAllMapping(const char* a_takeAllStr);
		static const char*			GetSearchMapping();
		static void					SetSearchMapping(const char* a_searchStr);

		static void					Open();
		static void					Close();
		static void					SetVisible(bool a_visible);
		static void					SetContainerRef(TESObjectREFR* a_ref);
		static void					SetContainerRef(RE::TESObjectREFR* a_ref);
		static void					ClearContainerRef(bool a_playAnimation = true);
		static bool					CanOpen(RE::TESObjectREFR* a_ref, bool a_isSneaking);
		static void					Register(Scaleform a_reg);
		static Style				GetStyle();

		// IMenu
		virtual UInt32				ProcessMessage(UIMessage* a_message) override;
		virtual void				Render() override;

		// MenuEventHandler
		virtual bool				CanProcess(InputEvent* a_event) override;
		virtual bool				ProcessButton(RE::ButtonEvent* a_event) override;

		void						OnMenuOpen();
		void						OnMenuClose();
		void						TakeItemStack();
		void						TakeAllItems();

	private:
		bool						SingleLootEnabled();
		void						PlayAnimation(const char* a_fromName, const char* a_toName);
		void						PlayAnimationOpen();
		void						PlayAnimationClose();
		void						TakeItem(ItemData& a_item, UInt32 a_numItems);
		bool						TryToPickPocket(ItemData& a_item, RE::TESObjectREFR::RemoveType& a_lootMode);
		void						DispellWornItemEnchantments();
		UInt32						GetSingleLootKey(RE::BSInputDevice::InputDevice a_inputDevice);


		static LootMenu*			_singleton;
		static SInt32				_selectedIndex;
		static SInt32				_displaySize;
		static RE::TESObjectREFR*	_containerRef;
		static bool					_isContainerOpen;
		static bool					_isMenuOpen;
		static bool					_inTakeAllMode;
		static bool					_isRegistered;
		static Platform				_platform;
		static std::string			_actiText;
		static std::string			_singleLootMapping;
		static std::string			_takeMapping;
		static std::string			_takeAllMapping;
		static std::string			_searchMapping;
	};


	template <typename T>
	void AllocateAndDispatch()
	{
		T* dlgt = (T*)Heap_Allocate(sizeof(T));
		new (dlgt)T;
		g_task->AddUITask(dlgt);
	}
}
