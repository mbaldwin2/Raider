#pragma once

#ifndef RAIDER_GRAPHICS_RENDERER
#define RAIDER_GRAPHICS_RENDERER

#include <OS/Prefix.h>
#include <Raider/Prefix.h>

namespace Raider {

	namespace Graphics {

		class API Renderer {
		public:
			Renderer();
			~Renderer();

			bool Initialize();
			void Finalize();
			bool Update();

			Renderer & operator = (const Renderer &);
		protected:
			struct {
				uint32_t width, height;
				int32_t x, y;

				float aspect() const;
			} frame;

			struct {
				float red, green, blue, alpha;
			} bg;
# if WINDOWS_OS
			HINSTANCE instance;
			HWND handle;
			HWND parent;
			HDC dc;
#  if USING_OPENGL
			HGLRC context;
#  elif USING_VULKAN
#  endif
# elif LINUX_OS
			xcb_connection_t * instance;
			xcb_window_t handle;
			xcb_window_t parent;
# endif

# if WINDOWS_OS
		private:
			bool IsRegistered() const;
			bool Register();
# endif
		};

	}

}

#endif // ending RAIDER_GRAPHICS_RENDERER //