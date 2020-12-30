#pragma once

#ifndef RAIDER_UI_CONTAINER
#define RAIDER_UI_CONTAINER

#include <Raider/UI/Widget.h>

namespace Raider {
	namespace UI {

		class API Container : public Widget {
		public:
			enum class Orientation {
				Horizontal,
				Vertical
			};

			enum class PackDirection {
				UpFromTop,
				DownFromTop,
				UpFromCenter,
				DownFromCenter,
				UpFromBottom,
				DownFromBottom
			};

			Container(Widget *, Orientation);
			~Container();

			virtual bool AddChild(Widget *, PackDirection =PackDirection::DownFromTop);

			void AdjustChildren();
			size_t ChildCount() const;
		protected:
			Padding padding, margin;
			bool homogeneous, fill;
		};
		
	}
}

#endif // ending RAIDER_UI_CONTAINER //