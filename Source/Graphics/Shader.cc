#define API_EXPORT
#include <Raider/Graphics/Shader.h>

#include <iostream>
#include <fstream>

namespace Raider {
	namespace Graphics {

		Shader::Shader() : type(InvalidShader), filename(), buffer() {
# if USING_OPENGL
			id = 0;
# elif USING_VULKAN
			self = vk::Shader();
# endif
		}

		Shader::Shader(const std::string & name)
		: filename(name), buffer(), type(InvalidShader),
# if USING_OPENGL
			id()
# elif USING_VULKAN
			self()
# endif
		{}

		Shader::~Shader() {
		}

		bool Shader::ValidShaderName(const std::string & name) const {
			bool valid = name.length() > 0;
			valid |= ObtainType(name) != InvalidShader;
			return valid;
		}

		bool Shader::Loaded() const { return buffer.length() > 0; }
		bool Shader::Load() {
			std::ifstream file;
			file.open(filename);

			if( file.is_open() ) {
				buffer.clear();
				while( file.good() ){
					char c = file.get();
					if( c == EOF ) break;
					else buffer += c;
				}
				return true;
			}else	return false;
		}

		bool Shader::Load(const std::string & newFilename) {
			if( !ValidShaderName(newFilename) ) return false;
			else filename = newFilename;
			return Load();
		}

		ShaderType Shader::ObtainType(const std::string & name) const {
			if( name.length() < 1 ) return InvalidShader;

			std::vector<std::string> group = Stringz::Split(name,".");

			if( group.size() == 1 ) return InvalidShader;
			
			std::string lower = Stringz::ToLower(group[1]);
			if( lower == "vert" or lower == "v" ) return VertexShader;
			else if( lower == "frag" or lower == "f" ) return FragmentShader;
			else if( lower == "geom" or lower == "g" ) return GeometryShader;
			else if( lower == "teval" or lower == "tv" ) return TessEvalShader;
			else if( lower == "tctrl" or lower == "tc" ) return TessCtrlShader;
			else if( lower == "comp" or lower == "c" ) return ComputeShader;
			else return InvalidShader;
		}

		bool Shader::Compile() {
# if USING_OPENGL
			if( !glIsShader(id) ) return false;
			else glCompileShader(id);

			int status = false;
			glGetShaderiv(id, GL_COMPILE_STATUS, &status);
			return (status == true);
# elif USING_VULKAN
# endif
		}

# if USING_OPENGL
		std::string Shader::GetIV() const {
			if( !glIsShader(id) ) return "Invalid Shader";
			
			std::vector<char> log;
			int len;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
			if( len < 1 ) return "Success";

			glGetShaderInfoLog(id, len, nullptr, log.data());
			return static_cast<std::string>(log.data());
		}
# endif

		bool Shader::SaveAs(const std::string & newFilename) {
			if( !ValidShaderName(newFilename) ) return false;
			else filename = newFilename;
			return Save();
		}

		bool Shader::Save() {
			std::ofstream file;
			file.open(filename, std::ios::out);
			file << buffer;
			file.close();
			return true;
		}

		bool Shader::IsInvalid() const { return type == InvalidShader; }

		uint8_t Shader::VersionMajor() const {
			if( !Loaded() ) return 0;

			int hash = buffer.find("#");
			int nl = buffer.find("\n",hash);
			auto group = Stringz::Split( buffer.substr(hash,nl), "version" );
			std::cout << group[0] << " " << group[1] << std::endl;
		}

		uint8_t Shader::VersionMinor() const {
			if( !Loaded() ) return 0;
		}

		bool Shader::operator == (const Shader & shader) const {
			bool is = type == shader.type;
			is &= filename == shader.filename;
			is &= buffer == shader.buffer;
# if USING_OPENGL
			is &= id == shader.id;
# elif USING_VULKAN
			is &= shader.self == self;
# endif
			return is;
		}

		bool Shader::operator != (const Shader & shader) const { return !operator==(shader); }
		Shader & Shader::operator = (const Shader & shader) {
			type = shader.type;
			filename = shader.filename;
			buffer = shader.buffer;
# if USING_OPENGL
			id = shader.id;
# elif USING_VULKAN
			self = shader.self;
# endif
			return *this;
		}
	}
}