#define API_EXPORT
#include <Raider/Misc/Registry.h>

namespace Raider {
# if WINDOWS_OS

	namespace GlobalRegistry {

		static HINSTANCE hInstance;

		API HINSTANCE GetInstance() { return hInstance; }
		API void SetInstance(HINSTANCE Instance) { hInstance = Instance; }

		class Registry {
		public:
			Registry();
			~Registry();

			bool IsRegistered(const std::string &) const;
			int Store(WNDCLASSEX);
			int Store(const std::vector<WNDCLASSEX> &);
			int IsStored(const std::string &) const;
			float Register();
			size_t RegisteredClasses() const;
		private:
			std::vector< std::pair<WNDCLASSEX, bool> > set;
		};

		Registry::Registry() {
			set = {};
		}

		Registry::~Registry(){}

		bool Registry::IsRegistered(const std::string & classname) const {
			auto cls = Stringz::WString(classname);
			for(const auto & pair : set){
				if( cls == pair.first.lpszClassName )
					return pair.second;
			}
			return false;
		}

		int Registry::Store(WNDCLASSEX wc) {
			if( IsStored( Stringz::ToString( Stringz::WString(wc.lpszClassName) ) ) ) return -1;

			if( (wc.hInstance == nullptr) and (hInstance != nullptr) )
				wc.hInstance = hInstance;

			set.push_back( std::make_pair(wc,false) );
			return set.size()-1; // index of the class just inserted //
		}

		int Registry::Store( const std::vector<WNDCLASSEX> & cls ) {
			int x = 0;
			for(const auto & c : cls) if( Store(c) > -1 ) x++;
			return x;
		}

		int Registry::IsStored(const std::string & classname) const {
			auto cls = Stringz::WString(classname);
			int i=0;
			for(const auto & pair : set){
				if( cls == pair.first.lpszClassName ) return i;
				else i++;
			}
			return -1;
		}

		float Registry::Register() {
			float score = 0.f;
			for(auto & pair : set){
				if( RegisterClassEx(&pair.first) != 0 ){
					pair.second = true;
					score += 1.f;
				}
			}
			return score/float(set.size());
		}

		size_t Registry::RegisteredClasses() const { return set.size(); }

		static Registry registry;

		API float RegisterAll() { return registry.Register(); }
		API size_t RegisteredClasses() { return registry.RegisteredClasses(); }

		API int Store(WNDCLASSEX wc) { return registry.Store(wc); }
		API int Store(const std::vector<WNDCLASSEX> & list) { return registry.Store(list); }

	} // ending GlobalRegistry //
# endif // ending WINDOWS_OS defs //
} // ending Raider //