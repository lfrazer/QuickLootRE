#pragma once

#include "common/ITypes.h"  // UInt32
#include "skse64/GameEvents.h"  // EventResult, EventDispatcher, MenuOpenCloseEvent
#include "skse64/GameExtraData.h"  // InventoryEntryData
#include "skse64/GameFormComponents.h"  // TESContainer
#include "skse64/GameInput.h"  // InputEvent
#include "skse64/PapyrusEvents.h"  // SKSECrosshairRefEvent

#include <map>
#include <vector>  // vector


namespace QuickLootRE
{
	enum Keyboard : UInt32
	{
		kKeyboard_Escape		= 0x01,
		kKeyboard_Num1			= 0x02,
		kKeyboard_Num2			= 0x03,
		kKeyboard_Num3			= 0x04,
		kKeyboard_Num4			= 0x05,
		kKeyboard_Num5			= 0x06,
		kKeyboard_Num6			= 0x07,
		kKeyboard_Num7			= 0x08,
		kKeyboard_Num8			= 0x09,
		kKeyboard_Num9			= 0x0A,
		kKeyboard_Num0			= 0x0B,
		kKeyboard_Minus			= 0x0C,
		kKeyboard_Equals		= 0x0D,
		kKeyboard_Backspace		= 0x0E,
		kKeyboard_Tab			= 0x0F,
		kKeyboard_Q				= 0x10,
		kKeyboard_W				= 0x11,
		kKeyboard_E				= 0x12,
		kKeyboard_R				= 0x13,
		kKeyboard_T				= 0x14,
		kKeyboard_Y				= 0x15,
		kKeyboard_U				= 0x16,
		kKeyboard_I				= 0x17,
		kKeyboard_O				= 0x18,
		kKeyboard_P				= 0x19,
		kKeyboard_BracketLeft	= 0x1A,
		kKeyboard_BracketRight	= 0x1B,
		kKeyboard_Enter			= 0x1C,
		kKeyboard_LeftControl	= 0x1D,
		kKeyboard_A				= 0x1E,
		kKeyboard_S				= 0x1F,
		kKeyboard_D				= 0x20,
		kKeyboard_F				= 0x21,
		kKeyboard_G				= 0x22,
		kKeyboard_H				= 0x23,
		kKeyboard_J				= 0x24,
		kKeyboard_K				= 0x25,
		kKeyboard_L				= 0x26,
		kKeyboard_Semicolon		= 0x27,
		kKeyboard_Apostrophe	= 0x28,
		kKeyboard_Tilda			= 0x29,
		kKeyboard_LeftShift		= 0x2A,
		kKeyboard_Backslash		= 0x2B,
		kKeyboard_Z				= 0x2C,
		kKeyboard_X				= 0x2D,
		kKeyboard_C				= 0x2E,
		kKeyboard_V				= 0x2F,
		kKeyboard_B				= 0x30,
		kKeyboard_N				= 0x31,
		kKeyboard_M				= 0x32,
		kKeyboard_Comma			= 0x33,
		kKeyboard_Period		= 0x34,
		kKeyboard_Slash			= 0x35,
		kKeyboard_RightShift	= 0x36,
		kKeyboard_KP_Multiply	= 0x37,
		kKeyboard_LeftAlt		= 0x38,
		kKeyboard_Spacebar		= 0x39,
		kKeyboard_CapsLock		= 0x3A,
		kKeyboard_F1			= 0x3B,
		kKeyboard_F2			= 0x3C,
		kKeyboard_F3			= 0x3D,
		kKeyboard_F4			= 0x3E,
		kKeyboard_F5			= 0x3F,
		kKeyboard_F6			= 0x40,
		kKeyboard_F7			= 0x41,
		kKeyboard_F8			= 0x42,
		kKeyboard_F9			= 0x43,
		kKeyboard_F10			= 0x44,
		kKeyboard_NumLock		= 0x45,
		kKeyboard_ScrollLock	= 0x46,
		kKeyboard_KP_7			= 0x47,
		kKeyboard_KP_8			= 0x48,
		kKeyboard_KP_9			= 0x49,
		kKeyboard_KP_Subtract	= 0x4A,
		kKeyboard_KP_4			= 0x4B,
		kKeyboard_KP_5			= 0x4C,
		kKeyboard_KP_6			= 0x4D,
		kKeyboard_KP_Plus		= 0x4E,
		kKeyboard_KP_1			= 0x4F,
		kKeyboard_KP_2			= 0x50,
		kKeyboard_KP_3			= 0x51,
		kKeyboard_KP_0			= 0x52,
		kKeyboard_KP_Decimal	= 0x53,
		kKeyboard_F11			= 0x57,
		kKeyboard_F12			= 0x58,
		kKeyboard_KP_Enter		= 0x9C,
		kKeyboard_RightControl	= 0x9D,
		kKeyboard_KP_Divide		= 0xB5,
		kKeyboard_PrintScreen	= 0xB7,
		kKeyboard_RightAlt		= 0xB8,
		kKeyboard_Pause			= 0xC5,
		kKeyboard_Home			= 0xC7,
		kKeyboard_Up			= 0xC8,
		kKeyboard_PageUp		= 0xC9,
		kKeyboard_Left			= 0xCB,
		kKeyboard_Right			= 0xCD,
		kKeyboard_End			= 0xCF,
		kKeyboard_Down			= 0xD0,
		kKeyboard_PageDown		= 0xD1,
		kKeyboard_Insert		= 0xD2,
		kKeyboard_Delete		= 0xD3
	};


	enum Mouse : UInt32
	{
		kMouse_LeftButton = 0,
		kMouse_RightButton,
		kMouse_MiddleButton,
		kMouse_Button3,
		kMouse_Button4,
		kMouse_Button5,
		kMouse_Button6,
		kMouse_Button7,
		kMouse_WheelUp,
		kMouse_WheelDown,
	};


	enum Gamepad : UInt32
	{
		kGamepad_Up				= 0x0001,
		kGamepad_Down			= 0x0002,
		kGamepad_Left			= 0x0004,
		kGamepad_Right			= 0x0008,
		kGamepad_Start			= 0x0010,
		kGamepad_Back			= 0x0020,
		kGamepad_LeftThumb		= 0x0040,
		kGamepad_RightThumb		= 0x0080,
		kGamepad_LeftShoulder	= 0x0100,
		kGamepad_RightShoulder	= 0x0200,
		kGamepad_A				= 0x1000,
		kGamepad_B				= 0x2000,
		kGamepad_X				= 0x4000,
		kGamepad_Y				= 0x8000,
		kGamepad_LT				= 0x0009,
		kGamepad_RT				= 0x000A
	};


	class TESContainerVisitor
	{
	public:
		virtual bool Accept(TESContainer::Entry* a_entry);
	};


	class EntryDataListVisitor
	{
	public:
		virtual bool Accept(InventoryEntryData* a_entryData);
	};


	class CrosshairRefEventHandler : public BSTEventSink<SKSECrosshairRefEvent>
	{
	public:
		virtual	EventResult ReceiveEvent(SKSECrosshairRefEvent* a_event, EventDispatcher<SKSECrosshairRefEvent>* a_dispatcher) override;
	};


	class MenuOpenCloseEventHandler : public BSTEventSink<MenuOpenCloseEvent>
	{
	public:
		virtual EventResult ReceiveEvent(MenuOpenCloseEvent* a_event, EventDispatcher<MenuOpenCloseEvent>* a_dispatcher) override;
	};


	class InputEventHandler : public BSTEventSink<InputEvent>
	{
	public:
		virtual EventResult ReceiveEvent(InputEvent** a_event, InputEventDispatcher* a_dispatcher) override;
	};


	class TESContainerChangedEventHandler : public BSTEventSink<TESContainerChangedEvent>
	{
	public:
		virtual EventResult ReceiveEvent(TESContainerChangedEvent* a_event, EventDispatcher<TESContainerChangedEvent>* a_dispatcher) override;
	};


	void getInventoryList(BaseExtraList* a_xList, TESContainer* a_container);


	typedef SInt32 Count;
	static std::map<TESForm*, Count> defaultMap;

	extern CrosshairRefEventHandler g_crosshairRefEventHandler;
	extern MenuOpenCloseEventHandler g_menuOpenCloseEventHandler;
	extern InputEventHandler g_inputEventHandler;
	extern TESContainerChangedEventHandler g_containerChangedEventHandler;
}
