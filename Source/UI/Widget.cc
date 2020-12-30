#define API_EXPORT
#include <Raider/UI/Widget.h>
#include <Raider/Misc/Registry.h>

#define NOT_VISIBLE -2
#define HIDDEN -1
#define MINIMIZED 0
#define SHOWING 1
#define MAXIMIZED 2

#define PARENTABLE 0x0100
#define MAXIMIZABLE 0x0200
#define MINIMIZABLE 0x0400

# if WINDOWS_OS
#  define InvalidWindow nullptr
# elif LINUX_OS
#  define InvalidWindow -1
# endif

namespace Raider {
	namespace UI {

		Widget::Widget(Widget * Parent) {
			parent = Parent;

			visibility = NOT_VISIBLE;
			winstate = 0;
			createFlags = 0;
			x = y = 0;
			width = height = 0;
			radius = 0;
			padding = margin = Padding();
			window = InvalidWindow;
			id = 0;
			SetName("");
# if WINDOWS_OS
#  if UNICODE_DEFINED
			classname = Stringz::WString("");
#  else
			classname = "";
#  endif
# endif
		}

		Widget::Widget(Widget * Parent, uint32_t ID, const std::string & Alias)
		: Widget(Parent) {
			id = ID;
			SetName(Alias);
		}

		Widget::~Widget() {}

		void Widget::OnCreate() {}
		void Widget::OnDestroy() {}
		void Widget::OnKeyPress() {}
		void Widget::OnKeyRelease() {}
		void Widget::OnLeftMouseClick() {}
		void Widget::OnLeftMouseRelease() {}
		void Widget::OnLeftMouseDoubleClick() {}
		void Widget::OnRightMouseClick() {}
		void Widget::OnRightMouseRelease() {}
		void Widget::OnRightMouseDoubleClick() {}
		void Widget::OnMiddleMouseClick() {}
		void Widget::OnMiddleMouseRelease() {}
		void Widget::OnMouseEnter() {}
		void Widget::OnMouseLeave() {}
		void Widget::OnPaint(PAINTSTRUCT * ps) {}
		void Widget::OnDraw() {}
		void Widget::OnResize() {}
		void Widget::OnReposition() {}
		void Widget::OnActivate() {}
		void Widget::OnDeactivate() {}
		void Widget::OnScrollUp() {}
		void Widget::OnScrollDown() {}
		void Widget::OnShow() {}
		void Widget::OnHide() {}
		void Widget::OnMaximize() {}
		void Widget::OnMinimize() {}
		void Widget::OnRestore() {}

		bool Widget::Showing() const { return visibility == 1; }
		uint32_t Widget::GetID() const { return id; } 
		void Widget::SetID(uint32_t nid) { id = nid; }

		void Widget::SetName(const std::string & name) {
			if( name.length() < 1 ) return;
# if UNICODE_DEFINED
			alias = Stringz::WString(name);
# else
			alias = name;
# endif

			if( !IsValid() ) return;
# if WINDOWS_OS
			SetWindowText(window, alias.c_str());
# elif LINUX_OS
# endif
		}

# if WINDOWS_OS
		HWND Widget::GetWindow() { return window; }
# elif LINUX_OS
		xcb_window_t Widget::GetWindow() { return window; }
# endif

		bool Widget::IsValid() const {
# if WINDOWS_OS
			return window != nullptr;
# elif LINUX_OS
			return window > -1;
# endif
		}

		bool Widget::Create() {
			auto created = [](const Widget * self) {return self->IsValid();};
			if( created(this) ) return false;
# if WINDOWS_OS
			window = CreateWindow(
				classname.c_str(), alias.c_str(),
				createFlags, x,y,
				width, height,
				parent != nullptr ? parent->GetWindow() : nullptr,
				nullptr, GlobalRegistry::GetInstance(), this
			);
# endif
			return created(this);
		}

		bool Widget::Destroy() {
			auto destroyed = [](const Widget * self) {return !self->IsValid();};
			if( destroyed(this) ) return false;
# if WINDOWS_OS
			DestroyWindow(window);
			window = nullptr;
# elif LINUX_OS
			xcb_destroy_window(Server::GetConnection(), window);
			window = -1;
# endif
			return destroyed(this);
		}
# if WINDOWS_OS
		LRESULT CALLBACK Widget::Callback(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
			Widget * self = Self<Widget>(hWnd);
			switch(msg) {
			case WM_NCCREATE: {
				StoreSelf<Widget>(hWnd,lParam,self);
				self->OnCreate();
				} break;
			}

			// pointer safety //
			if( self ) {
				switch(msg) {
				case WM_LBUTTONDOWN: {
						self->OnLeftMouseClick();
					} break;
				case WM_LBUTTONUP: {
						self->OnLeftMouseRelease();
					} break;
				case WM_LBUTTONDBLCLK: {
						self->OnLeftMouseDoubleClick();
					} break;
				case WM_RBUTTONDOWN: {
						self->OnRightMouseClick();
					} break;
				case WM_RBUTTONUP: {
						self->OnRightMouseRelease();
					} break;
				case WM_RBUTTONDBLCLK: {
						self->OnRightMouseDoubleClick();
					} break;
				case WM_MOUSELEAVE: {
						self->OnCursorLeave();
					} break;
				case WM_MOUSEHOVER: {
					} break;
				
				/*
				* This is covered in the WM_ACTIVATE case.
				case WM_MOUSEACTIVATE: {
					} break;
				*/
				
				case WM_SIZE: {
						self->width = LOWORD(lParam);
						self->height = HIWORD(lParam);

						switch(wParam){
						case SIZE_MAXIMIZED: self->OnMaximize();
							break;
						case SIZE_MINIMIZED: self->OnMinimize();
							break;
						case SIZE_RESTORED: self->OnRestore();
							break;
						}
					} break;
				case WM_MOVE: {
						self->x = LOWORD(lParam);
						self->y = HIWORD(lParam);
						self->OnReposition();
					} break;
				case WM_SHOWWINDOW: {
						if( wParam ) self->OnShow();
						else if( !wParam ) self->OnHide();
					} break;
				case WM_DESTROY: {
						self->OnDestroy();
					} break;
				case WM_CLOSE: {
					} break;
				case WM_PAINT: {
					PAINTSTRUCT ps = {};
					BeginPaint(self->window, &ps);
					self->OnPaint(&ps);
					EndPaint(self->window, &ps);
					} break;
				case WM_DRAWITEM: {
					} break;
				case WM_KEYDOWN: {
						self->OnKeyPress();
					} break;
				case WM_KEYUP: {
						self->OnKeyRelease();
					} break;
				case WM_ENABLE: {
						if( wParam ) self->OnEnable();
						else self->OnDisable();
					} break;
				case WM_ACTIVATE: {
						HWND window = (HWND)lParam;
						if( window == self->window ){
							switch(LOWORD(wParam)){
							case WA_ACTIVE:
									self->OnActivate();
								break;
							case WA_INACTIVE:
									self->OnDeactivate();
								break;
							case WA_CLICKACTIVE:
									self->OnActivate();
								break;
							}
						}
					} break;
				/*
				case : {
					} break;
				*/
				default: break;
				}
			}
			return DefWindowProc(hWnd,msg,wParam,lParam);
		}
# endif

		bool Widget::Show() {
			if( Showing() ) return false;
# if WINDOWS_OS
# elif LINUX_OS
# endif
			return true;
		}

		bool Widget::Maximized() const {
		
		}

		bool Widget::Minimized() const {}

		bool Widget::Maximize() {
			if( Maximized() ) return false;
# if WIDNOWS_OS
# elif LINUX_OS
# endif
			return Maximized();
		}

		bool Widget::Minimize() {
			if( Minimized() ) return false;
			
			return Minimized();
		}

		bool Widget::Hide() {
			auto hidden = [](const Widget * w){return false;};
# if WINDOWS_OS
# elif LINUX_OS
# endif
			return hidden(this);
		}


		bool Widget::AttemptResize(uint32_t w, uint32_t h) {
			if( (w > maxWidth) or (w < minWidth) ) return false;
			else if( (h > maxHeight) or (h < minHeight) ) return false;

			width = w;
			height = h;
# if WINDOWS_OS
			
# elif LINUX_OS
# endif
			return true;
		}

		bool Widget::AttemptReposition(int32_t x, int32_t y) {
			this->x = x;
			this->y = y;
# if WINDOWS_OS
# elif LINUX_OS
# endif
			return false;
		}
	}
}