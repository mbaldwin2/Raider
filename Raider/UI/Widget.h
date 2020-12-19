#pragma once

#ifndef RAIDER_UI_WIDGET
#define RAIDER_UI_WIDGET

#include <Raider/Prefix.h>
#include <Raider/Misc/Color.h>

namespace Raider {

	namespace UI {

		class API Widget {
		public:
			Widget(Widget *);
			~Widget();

			virtual void OnResize() =0;
			virtual void OnCreate() =0;
			virtual void OnDestroy() =0;
			virtual void OnActivate() =0;
			virtual void OnDeactivate() =0;
			virtual void OnShow() =0;
			virtual void OnHide() =0;
			virtual void OnEnter() =0;
			virtual void OnLeave() =0;

			virtual bool HasChildren() const final;

			bool operator == (const Widget &) const;
			bool operator != (const Widget &) const;
			Widget & operator = (const Widget &);
		protected:
			Widget * parent;
			std::vector<Widget *> children;

			iColorRGB color;
# if WINDOWS_OS
			HANDLE handle;
# elif LINUX_OS
			xcb_window_t handle;
# endif
		};

	}

}

#endif // ending RAIDER_UI_WIDGET //