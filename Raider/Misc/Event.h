#pragma once

#ifndef RAIDER_MISC_EVENT
#define RAIDER_MISC_EVENT

#include <Raider/Prefix.h>

namespace Raider {
	enum class EventType { None,
		ButtonPress,
		ButtonRelease,
		CursorMotion,
		CursorEnter,
		CursorLeave,
		ScrollUp,
		ScrollDown,
		KeyPress,
		KeyRelease,
		Create,
		Destroy,
		Close,
		Quit,
		Resize,
		Reposition,
		Reparent,
		Refresh,
		Render, // for opengl / vulkan? //
	};

	enum class ButtonID { None,
		Left, Right, Middle,
		// for some of the others //
		Back, Forward
	};

	enum class KeyID { None,
		A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z, // no shift key //
		N1,N2,N3,N4,N5,N6,N7,N8,N9,N0, // numbers above the keyboard //
		LQuation, Quotation, Comma, Period, FSlash, BSslash,
		Enter, LShift, RShift, LCtrl, RCtrl, LAlt, RAlt, Fn,
		Up, Right, Left, Down, Plus, Minus1, Minus2, Equal, Div,
		P1, P2, P3, P4, P5, P6, P7, P8, P9, P0, // number pad //
		LBracket, RBracket, NumLock, CapsLock, Tab, Space, WinKey,
		Escape, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		Insert, PrintScreen, Delete, Home, End, PageUp, PageDown
	};

	class KeyInfo {
	public:
		KeyInfo(uint32_t =0);
		~KeyInfo();

		bool operator == (const KeyInfo &) const;
		bool operator != (const KeyInfo &) const;
		KeyInfo & operator = (const KeyInfo &);

		KeyInfo & Set(uint32_t);
		KeyID Id() const;
		uint16_t Repeat() const;
		bool Active() const; // true if down, false if up //
		bool PrevActive() const; // true if previous state was down, else false //
		bool AltDown() const; // if the ALT key has been pressed //
		bool Extended() const; // special keys, CTRL, ALT, FN, etc... //

	protected:
		uint16_t repeat;
		uint8_t scancode;
		uint8_t endcode;
	};

	class Mouse {
	public:
		Mouse();
		~Mouse();
	protected:
# if WINDOWS_OS
		HICON icon;
# endif
	};

	class EventID {
	public:
	protected:
		EventType eType;
		KeyID kID;
		ButtonID bID;
	};

	class Widget;
	class Event {
	public:
		Event();
		~Event();

		typedef int32_t (*Method)(Widget &, const EventID &);

		bool operator == (const Event &) const;
		bool operator != (const Event &) const;
		Event & operator = (const Event &);

		bool Next();
		void Dispatch();
	private:
# if WINDOWS_OS
		MSG msg; // needed for the event system //
# endif
		void Decode();
	};

}

#endif // ending RAIDER_MISC_EVENT //