#pragma once

#include "skse64/NiObjects.h"  // NiObject
#include "skse64/GameTypes.h"  // BSFixedString

class NiExtraData;
class NiTimeController;


namespace RE
{
	class NiObjectNET : public NiObject
	{
	public:
		void				AddExtraData(NiExtraData* extraData);
		bool				RemoveExtraData(NiExtraData* extraData);
		SInt32				GetIndexOf(NiExtraData* extraData);
		NiExtraData*		GetExtraData(BSFixedString name);

		NiTimeController*	GetController() const;


		// members
		const char*			m_name;					// 10
		NiTimeController*	m_controller;			// 18 next pointer at +0x30
		NiExtraData**		m_extraData;			// 20 extra data
		UInt16				m_extraDataLen;			// 28 max valid entry
		UInt16				m_extraDataCapacity;	// 2A array len
		UInt32				pad2C;					// 2C
	};
}
