#pragma once

#ifndef RAIDER_CLASS_REGISTRY
#define RAIDER_CLASS_REGISTRY

#include <Raider/Prefix.h>

namespace Raider {
# if WINDOWS_OS
	namespace GlobalRegistry {
		API HINSTANCE GetInstance();
		API int Store(WNDCLASSEX);
		API int Store(const std::vector<WNDCLASSEX> &);
		API float RegisterAll();
		API size_t RegisteredClasses();
	}
# endif
}

#endif // ending RAIDER_CLASS_REGISTRY //