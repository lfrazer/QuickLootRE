#pragma once

#include "skse64/GameBSExtraData.h"  // BaseExtraList

#include "Offsets.h"

#include "RE/ExtraContainerChanges.h"  // ExtraContainerChanges::Data

class BSExtraData;
class TESForm;


namespace RE
{
	class BaseExtraList
	{
	public:
		BaseExtraList();
		~BaseExtraList();

		bool			HasType(UInt32 a_type);
		void			MarkType(UInt32 a_type, bool a_bCleared);
		bool			Remove(UInt8 a_type, BSExtraData* a_toRemove);
		bool			Add(UInt8 a_type, BSExtraData* a_toAdd);
		bool			CheckContainerExtraData(bool a_isEquipped);
		const char*		GetDisplayName(TESForm* a_type);
		BSExtraData*	GetByType(UInt32 a_type);

		void			SetInventoryChanges(ExtraContainerChanges::Data* a_changes);
		UInt32			GetAshPileRefHandle(UInt32& a_refHandle);


		BSExtraData*						m_data;		// 00
		::BaseExtraList::PresenceBitfield*	m_presence;	// 08
		BSReadWriteLock						m_lock;		// 10

	private:
		typedef void _SetInventoryChanges_Impl_t(BaseExtraList* a_this, ExtraContainerChanges::Data* a_changes);
		static RelocAddr<_SetInventoryChanges_Impl_t*> _SetInventoryChanges_Impl;

		typedef UInt32 _GetAshPileRefHandle_Impl_t(BaseExtraList* a_this, UInt32& refHandle);
		static RelocAddr<_GetAshPileRefHandle_Impl_t*> _GetAshPileRefHandle_Impl;
	};
	STATIC_ASSERT(sizeof(BaseExtraList) == 0x18);
}
