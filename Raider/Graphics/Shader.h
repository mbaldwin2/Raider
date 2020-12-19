#pragma once

#ifndef RAIDER_GRAPHICS_SHADER
#define RAIDER_GRAPHICS_SHADER

#include <Raider/Prefix.h>

namespace Raider {
	namespace Graphics {

		enum ShaderType {
			InvalidShader,
			VertexShader,
			FragmentShader,
			GeometryShader,
			TessEvalShader,
			TessCtrlShader,
			ComputeShader
		};

		class API Shader {
		public:
			Shader();
			Shader(const std::string &);
			~Shader();

			uint8_t VersionMajor() const;
			uint8_t VersionMinor() const;

			bool Load();
			bool Loaded() const;
			bool Load(const std::string &);
			bool Save();
			bool SaveAs(const std::string &); // throws exception when ShaderTypes don't match //
			bool Compile();
# if USING_OPENGL
			std::string GetIV() const;
# endif

			bool operator == (const Shader &) const;
			bool operator != (const Shader &) const;
			Shader & operator = (const Shader &);
		
		private:
			ShaderType ObtainType(const std::string &) const;

			ShaderType type;
		protected:
			bool IsInvalid() const;
			bool ValidShaderName(const std::string &) const;

# if USING_OPENGL
			GLuint id;
# elif USING_VULKAN
			vk::Shader self;
# endif
			std::string filename, buffer;
		};

	}
}

#endif // ending RAIDER_GRAPHICS_SHADER //