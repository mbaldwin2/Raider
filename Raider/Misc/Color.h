#pragma once

#ifndef RAIDER_MISC_COLOR
#define RAIDER_MISC_COLOR

#include <Raider/Prefix.h>
#include <Math/Algebra/Vector.h>

namespace Raider {

	template<typename T>
	class ColorTemplate {
	public:
		ColorTemplate(){
			for(int i=0;i<3;i++)
				color[i] = T(0);
		}

		ColorTemplate(T const & r =T(), T const & g =T(), T & const b =T()) {
			color[0] = r;
			color[1] = g;
			color[2] = b;

			Smooth();
		}

		~ColorTemplate(){}

		typename ColorTemplate<T> & operator += (const ColorTemplate<T> & other) {
			color += other.color;
			Smooth();
			return *this;
		}

		typename ColorTemplate<T> & operator -= (const ColorTemplate<T> & other) {
			color -= other.color;
			Smooth();
			return *this;
		}

		typename ColorTemplate<T> & operator *= (T const & r) {
			color *= r;
			Smooth();
			return *this;
		}

		typename ColorTemplate<T> operator + (const ColorTemplate<T> & other) const {
			ColorTemplate<T> u = *this;
			return u += other;
		}

		typename ColorTemplate<T> operator - (const ColorTemplate<T> & other) const {
			ColorTemplate<T> u = *this;
			return u -= other;
		}

		typename ColorTemplate<T> operator * (T const & r) const {
			ColorTemplate<T> u = *this;
			return u *= r;
		}

		typename ColorTemplate<T> & operator = (const ColorTemplate<T> & other) {
			for(int i=0;i<3;i++) color[i] = other.color[i];
			return *this;
		}

		bool operator == (const ColorTemplate<T> & other) const {
			return other.color == color;
		}

		bool operator != (const ColorTemplate<T> & other) const { return !operator==(other); }
	protected:
		Math::Vector::Template<T,3> color;
	private:
		void Smooth(){
			for( int i=0;i<3;i++ ) {
				auto & cell = color[i];
				if( std::is_same<T,float>::value or std::is_same<T,double>::value ){
					if( cell > T(1) ) cell = T(1);
					else if( cell < T(0) ) cell = T(0);
				} else {
					if( cell > T(256) ) cell = T(256);
					else if( cell < T(0) ) cell = T(0);
				}
			}
		}
	};

	template<typename T>
	class ColorTemplateWithAlpha : public ColorTemplate<T> {
	public:
		ColorTemplateWithAlpha()
		: ColorTemplate<T>(), alpha() {}

		ColorTemplateWithAlpha(T const & r =T(), T const & g =T(), T const & b =T(), T const & a =T())
		: ColorTemplate<T>(r,g,b){
			alpha = a;
			Smooth();
		}

		~ColorTemplateWithAlpha() {}

		typename ColorTemplateWithAlpha<T> & operator = (const ColorTemplateWithAlpha<T> & other) {
			ColorTemplate<T>::operator=(other);
			alpha = other.alpha;
			return *this;
		}

		typename ColorTemplateWithAlpha<T> & operator += (const ColorTemplateWithAlpha<T> & other) {
			ColorTemplate<T>::operator+=(other);
			alpha += other.alpha;
			Smooth();
			return *this;
		}

		typename ColorTemplateWithAlpha<T> & operator -= (const ColorTemplateWithAlpha<T> & other) {
			ColorTemplate<T>::operator-=(other);
			alpha -= other.alpha;
			Smooth();
			return *this;
		}

		typename ColorTemplateWithAlpha<T> & operator *= (T const & r) {
			ColorTemplate<T>::operator*=(r);
			alpha *= r;
			Smooth();
			return *this;
		}

		typename ColorTemplateWithAlpha<T> & operator + (const ColorTemplateWithAlpha<T> & other) const {
			ColorTemplateWithAlpha<T> u = *this;
			return u += other;
		}

		typename ColorTemplateWithAlpha<T> & operator - (const ColorTemplateWithAlpha<T> & other) const {
			ColorTemplateWithAlpha<T> u = *this;
			return u -= other;
		}

		typename ColorTemplateWithAlpha<T> & operator * (T const & r) const {
			ColorTemplateWithAlpha<T> u = *this;
			return u *= other;
		}

	protected:
		T alpha;
	private:
		void Smooth() {
			if( std::is_same<T,float>::value or std::is_same<T,double>::value or std::is_same<T,long double>::value ){
				if( alpha > T(1) ) alpha = T(1);
			}else{
				if( alpha > T(256) ) alpha = T(256);
			}
			if( alpha < T(0) ) alpha = T(0);
		}
	};


	typedef ColorTemplate<uint8_t> bColorRGB; 
	typedef ColorTemplate<uint32_t> iColorRGB;
	typedef ColorTemplate<float> ColorRGB;
	typedef ColorTemplate<double> dColorRGB;

	typedef ColorTemplateWithAlpha<uint8_t> bColorRGBA;
	typedef ColorTemplateWithAlpha<uint32_t> iColorRGBA;
	typedef ColorTemplateWithAlpha<float> ColorRGBA;
	typedef ColorTemplateWithAlpha<double> dColorRGBA;
}

#endif // ending RAIDER_MISC_COLOR //