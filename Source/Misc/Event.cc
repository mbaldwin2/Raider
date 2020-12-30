#define API_EXPORT
#include <Raider/Misc/Event.h>

namespace Raider {

	/* class KeyInfo */
	KeyInfo::KeyInfo(uint32_t info){
		Set(info);
	}

	KeyInfo::~KeyInfo() {}

	KeyInfo & KeyInfo::Set(uint32_t info){
		struct {
			uint16_t repeat;
			uint8_t scancode;
			uint8_t endcode;
		} key;

		memset(&key, info, sizeof(key));
		repeat = key.repeat;
		scancode = key.scancode;
		endcode = key.endcode;
	}

	uint16_t KeyInfo::Repeat() const { return repeat; }

	bool KeyInfo::Extended() const {
		return false;
	}

	bool KeyInfo::AltDown() const {
		return false;
	}

	bool KeyInfo::Active() const {
		return false;
	}

	bool KeyInfo::PrevActive() const {
		return false;
	}




	/* class Event */
	Event::~Event() {}
	Event::Event() {
		msg = {};
	}

	bool Event::Next() {
# if WINDOWS_OS
		return GetMessage(&msg, nullptr, 0,0);
# elif LINUX_OS
# endif
	}

}