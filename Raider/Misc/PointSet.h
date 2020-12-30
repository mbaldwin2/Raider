#pragma once

#ifndef RAIDER_MISC_POINTSET
#define RAIDER_MISC_POINTSET

#include <Raider/Prefix.h>
#include <Math/Algebra/Vector.h>

#include <utility>

namespace Raider {

	template<typename T, size_t points, size_t space=2>
	class PointSet {
	public:
		PointSet(){
			if( points < 2 ) throw std::exception("A point-set must have more than one point");
			else if( space < 2 ) throw std::exception("A point-set's spacial cardinality must be greater than one");
			for(int i=0;i<points;i++) e[i] = Math::Vector::Template<T,space>();
		}
		PointSet(const std::initializer_list< Math::Vector::Template<T,space> > & list){
			if( points < 2 ) throw std::exception("A shape must have more than one point");
			else if( space < 2 ) throw std::exception("A shape's spacial cardinality must be greater than one");
			else if( list.size() != points ) throw std::exception("initializer list must be the same length as suggested");
			int i=0;
			for(const auto & _ : list) e[i++] = _;
		}

		~PointSet(){}

		// how the shape will be drawn //
		virtual void Draw() =0;

		bool operator == (const PointSet<T,points,space> & shape) const {
			for(int i=0;i<points;i++)
				if( e[i] != shape.e[i] ) return false;
			return true;
		}

		bool operator != (const PointSet<T,points,space> & shape) const { return !operator==(shape); }

		typename PointSet<T,points,space> & operator = (const PointSet<T,points,space> & shape) {
			for(int i=0;i<points;i++)
				e[i] = shape.e[i];
			return *this;
		}

		typename PointSet<T,points,space> & operator += (const PointSet<T,points,space> & shape) {
			for(int i=0;i<points;i++)
				e[i] += shape.e[i];
			return *this;
		}

		typename PointSet<T,points,space> & operator -= (const PointSet<T,points,space> & shape) {
			for(int i=0;i<points;i++)
				e[i] -= shape.e[i];
			return *this;
		}

		typename Math::Vector::Template<T,space> CenterPoint() const {
			Math::Vector::Template<T,space> center;
			for(int i=0;i<space;i++){
				for(int c=0;c<points;c++){
					center[i] += e[c];
				}

				center[i] /= points;
			}
			return center;
		}
	protected:
		Math::Vector::Template<T,space> e[points];
	};


	template<typename T, size_t points, size_t space=2>
	class Polygon : public PointSet<T,points,space> {
	public:
		Polygon();
		~Polygon();
	protected:
	};
}

#endif // ending RAIDER_MISC_POINTSET //