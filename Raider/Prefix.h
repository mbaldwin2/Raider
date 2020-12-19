#pragma once

#ifndef RAIDER_GRAPHICS_PREFIX
#define RAIDER_GRAPHICS_PREFIX

#include <OS/Prefix.h>
#include <Stringz/Utility.h>

# ifndef __cplusplus
#  error A C++ compiler must be used while compiling the Raider Engine...
# endif

#ifndef USING_VULKAN_GRAPHICS
# define USING_OPENGL_GRAPHICS
# define USING_VULKAN 0
# define USING_OPENGL 1
#else
# define USING_VULKAN 1
# define USING_OPENGL 0
#endif

# if USING_OPENGL
#  include <GL/glew.h>
#  include <GL/gl.h>
#  include <GL/glu.h>
#  if WINDOWS_OS
#  include <GL/wglew.h>
#  endif
# elif USING_VULKAN
#  include <vulkan/vulkan.hpp>
# endif

#endif // ending RAIDER_GRAPHICS_PREFIX //