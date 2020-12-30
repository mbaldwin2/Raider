#pragma once

#ifndef RAIDER_UI_WIDGET
#define RAIDER_UI_WIDGET

#include <Raider/Prefix.h>
#include <Raider/Misc/Event.h>

namespace Raider {
	namespace UI {

		enum class State {
			Showing = 0x0001,
			Maximized = 0x0002,
			Minimized = 0x0003,
			Inactive = 0x1000, // if not present, then assumed active //
			Resizable = 0x0100,
		};

		// this should be put into a seperate file //
		class API Padding {
		public:
			Padding() : top(), left(), bottom(), right() {}
			Padding(uint32_t Top, uint32_t Left, uint32_t Bottom, uint32_t Right)
			: top(Top), left(Left), bottom(Bottom), right(Right) {}

			~Padding() {}

			uint32_t GetTop() const { return top; }
			void SetTop(uint32_t t) { top = t; }

			uint32_t GetRight() const { return right; }
			void SetRight(uint32_t r) { right = r; }

			uint32_t GetLeft() const { return left; }
			void SetLeft(uint32_t l) { left = l; }

			uint32_t GetBottom() const { return bottom; }
			void SetBottom(uint32_t b) { bottom = b; }

			uint32_t GetTall() const { return top + bottom; }
			uint32_t GetWide() const { return right + left; }

			bool operator == (const Padding & p) const {
				return	top == p.top
				and	left == p.left
				and	right == p.right
				and	bottom == p.bottom;
			}

			bool operator != (const Padding & p) const {return !operator==(p);}
			Padding & operator = (const Padding & p) {
				top = p.top;
				left = p.left;
				bottom = p.bottom;
				right = p.right;
				return *this;
			}

			Padding & operator += (const Padding & p) {
				top += p.top;
				left += p.left;
				bottom += p.bottom;
				right += p.right;
				return *this;
			}
			
			Padding & operator -= (const Padding & p) {
				top -= p.top;
				left -= p.left;
				bottom -= p.bottom;
				right -= p.right;
				return *this;
			}

			Padding operator + (const Padding & p) {
				Padding u = *this;
				return u += p;
			}

			Padding operator - (const Padding & p) {
				Padding u = *this;
				return u -= p;
			}
		protected:
			uint32_t top, bottom, left, right;
		};

		class API Widget {
		public:
			Widget(Widget * Parent);
			Widget(Widget * Parent, uint32_t ID, const std::string & Name="");
			~Widget();

			virtual void OnCreate();
			virtual void OnDestroy();
			virtual void OnLeftMouseClick();
			virtual void OnLeftMouseRelease();
			virtual void OnLeftMouseDoubleClick();
			virtual void OnRightMouseClick();
			virtual void OnRightMouseRelease();
			virtual void OnRightMouseDoubleClick();
			virtual void OnMiddleMouseClick();
			virtual void OnMiddleMouseRelease();
			virtual void OnCursorLeave();
			virtual void OnCursorEnter();
			virtual void OnKeyPress();
			virtual void OnKeyRelease();
			virtual void OnMouseEnter();
			virtual void OnMouseLeave();
			virtual void OnPaint(PAINTSTRUCT *);
			virtual void OnDraw();
			virtual void OnResize();
			virtual void OnReposition();
			virtual void OnActivate();
			virtual void OnDeactivate();
			virtual void OnEnable();
			virtual void OnDisable();
			virtual void OnScrollUp();
			virtual void OnScrollDown();
			virtual void OnShow();
			virtual void OnHide();
			virtual void OnMaximize();
			virtual void OnMinimize();
			virtual void OnRestore();

			virtual bool Create();
			virtual bool Destroy();
			virtual bool AttemptResize(uint32_t, uint32_t);
			virtual bool AttemptReposition(int32_t, int32_t);

			virtual bool Showing() const final;
			virtual uint32_t GetID() const final;
			virtual void SetID(uint32_t) final;
			virtual bool Show() final;
			virtual bool Hide() final;
			virtual bool Maximize() final;
			virtual bool Minimize() final;
			virtual bool Maximized() const final;
			virtual bool Minimized() const final;
# if WINDOWS_OS
			virtual HWND GetWindow() final;
# elif LINUX_OS
			virtual xcb_window_t GetWindow() final;
# endif
			virtual void SetName(const std::string &) final;

			// used for both win32 and xcb //
			friend int32_t DefaultMethod(Widget &, const EventID &);
		protected:
			Widget * parent;
# if WINDOWS_OS
		static	LRESULT CALLBACK Callback(HWND,UINT,WPARAM,LPARAM);
			HWND window;
#  if UNICODE_DEFINED
			std::wstring classname;
			std::wstring alias;
#  elif
			std::string classname;
			std::string alias;
#  endif // ending UNICODE_DEFINED //
# elif LINUX_OS
			xcb_window_t window;
		static	void * Callback(xcb_window_t, xcb_generic_event_t, void *);
# endif
			int32_t createFlags;
			int32_t x,y;
			uint32_t width,height;
			uint32_t minWidth, maxWidth;
			uint32_t minHeight, maxHeight;
			uint32_t id;
			uint32_t radius;
			uint32_t winstate;
			int8_t visibility; // -2 -> not created, -1 -> hiding, 0 -> minimized, 1 -> showing, 2 -> maximized //
			Padding padding, margin;
			int16_t z;
			uint32_t cx, cy; // cursor x and y. used for mouse events //

			bool IsValid() const;
		};

# if WINDOWS_OS
		template<typename T>
		T * Self(HWND hWnd) { return reinterpret_cast<T *>( GetWindowLongPtr(hWnd, GWLP_USERDATA) ); }

		template<typename T>
		void StoreSelf(HWND hWnd, LPARAM lParam, T *& self) {
			LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
			self = reinterpret_cast<T *>(lpcs->lpCreateParams);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self) );
		}
# endif
	}
}

#endif // ending RAIDER_UI_WIDGET //