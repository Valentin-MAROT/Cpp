#pragma once // Permet d'assurer un inclusion unique (évite d'utiliser #ifndef et #define)

#include <algorithm>
#include <cstdlib>
#include "SVG.h"
#include <cmath>
#include "Array.h"
#include <cstdint>
#include <iostream>
#include <initializer_list>
#include <cassert>
#include "shapetype.h"

////////////////////////////////////////////////////////////////////////////////////////
struct Default {};
extern Default	defaut;

struct None {};
extern None		none;

struct Empty {};
extern Empty	empty;
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
class Color {
	public:
		enum colortype : uint8_t {
			red = 0, white, yellow, orange, turquoise, violet, pink, green,
			grey, cyan, blue, brown, none
		};
	private:
		static const std::size_t nColor = 13;
		static const char *name[];
		colortype  color;
	public:
		static const colortype defaut = red;
		Color(const colortype &c) : color(c) {}
		Color(Default) : color(red) {}
		// note: construction et assignation par copie déjà définies

		Color(const Color &c) : color(c.color) {}
		Color& operator=(const Color& v) {
			if (&v != this) color = v.color;
			return *this;
		}
		const char *getName() const { return name[color]; }
		void set(const colortype &c) { color = c; }
		friend std::ostream &operator<<(std::ostream &s, const Color &c) {
			return s << c.getName();
		}
		friend SVG::stream& operator<<(SVG::stream& s, const Color &c) {
			return s << c.getName();
		}
};

namespace Geom2D {

	constexpr float pi_f = 3.14159265358979323846f;

	////////////////////////////////////////////////////////////////////////////////////////
	///  Point
	class Point {
	protected: float x, y;
	public:
		inline Point(float u, float v) : x(u), y(v) {}
		inline Point() : Point(0.f,0.f) {}
		inline Point(None) {}
		inline float getx() const { return x; }
		inline float gety() const { return y; }
		inline void set(float u, float v) { x = u; y = v; }
		inline void operator+=(const Point &p) { x += p.getx(); y += p.gety(); }
		inline void operator/=(float v) { x /= v; y/= v; }
		inline void min(const Point &p) { x = std::min(x, p.x); y = std::min(y, p.y); }
		inline void max(const Point &p) { x = std::max(x, p.x); y = std::max(y, p.y); }
		friend std::ostream& operator<<(std::ostream& s, const Point& p) { return s << "(" << p.x << "," << p.y << ")"; }
		friend SVG::stream& operator<<(SVG::stream& s, const Point& p) { s << p.x << "," << p.y; return s; }
		inline void translate(const Point &v) { x += v.x; y += v.y; }
		inline void scale(const Point &c, float s) {
			x = c.x + s*(x - c.x);
			y = c.y + s*(y - c.y);
		}
		inline void rotate(const Point &c, float a) {
			Point  p(x - c.x, y - c.y);
			float  sina = sinf(a), cosa = cosf(a);
			x = c.x + sina*p.x - cosa*p.y;
			y = c.y + cosa*p.x + sina*p.y;
		}
		inline void polar(float radius, float angle, const Point &center) {
			x = center.x + radius*cosf(angle);
			y = center.y + radius*sinf(angle);
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////
	// interface transformation
	class Transform {
	public:
		virtual void Translate(const Point &p) = 0;
		virtual void Rotate(float a) = 0;
		virtual void Scale(float s) = 0;
	};

	////////////////////////////////////////////////////////////////////////////////////////
	// classe de base de Geom2D
	class Base : public Transform, public SVG::Write{
	public:
		Base() {}
		virtual std::ostream& info(std::ostream&) const = 0;
		virtual ~Base() = 0;
		virtual Point centre() = 0;
		virtual ShapeType getType() = 0;
		virtual void write(SVG::stream &stream) const = 0;
	};

		////////////////////////////////////////////////////////////////////////////////////////
		// interface FillProperty
		class FillProperty {
		protected:
			Color   fill_color;
			Color  stroke_color;
			size_t  stroke_width;
			float   opacity = 1.0;
		public:
			FillProperty() : fill_color(Color::defaut), stroke_color(Color::none) {}
			FillProperty(const Color &c) : fill_color(c), stroke_color(Color::none), stroke_width(1) {}
			FillProperty(const Color &fill, const Color &stroke) : fill_color(fill), stroke_color(stroke), stroke_width(1) {}
			FillProperty(const Color &fill, const Color &stroke, size_t width) : fill_color(fill), stroke_color(stroke), stroke_width(width) {}
			virtual ~FillProperty() {}
			void SetFillColor(const Color &c) { fill_color = c; }
			void SetStrokeColor(const Color &c) { stroke_color = c; }
			const Color &GetFillColor() const { return fill_color; }
			const Color &GetStrokeColor() const { return stroke_color; }
			size_t GetStrokeWidth() const { return stroke_width; }
			FillProperty GetFillProperty() const { return *this; }
			float GetOpacity() const { return opacity; }
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Disk
		class Disk :
			public Base, public FillProperty{
		protected:
			Point center;
			float radius;
		public:
			Disk():FillProperty(Color::defaut), center(0,0), radius(1){}
			Disk(const Point &c, float r, const Color &col = Color::defaut) :
				FillProperty(col), center(c), radius(r) {}
			Disk(const Point &c, float r, const Color &fill, const Color &stroke) :
				FillProperty(fill, stroke), center(c), radius(r) {}
			Disk(const Point &c, float r, const Color &fill, const Color &stroke, size_t width) :
				FillProperty(fill, stroke, width), center(c), radius(r) {}
			virtual ~Disk() {}
			virtual std::ostream &info(std::ostream &stream) const;
			virtual void write(SVG::stream &stream) const { stream << *this; }
			void Translate(const Point &v) override { center += v; }
			void Scale(float s) override { radius *= s; }
			void Rotate(float) override {}	// ne rien faire : omission du nom du paramètre (évite un warning "unused parameter")
			void setRadius(float r) { radius = r; }
			void setCenter(const Point &c) { center = c; }
			void setFillColor(const Color &c) { fill_color = c; }
			void setStrokeColor(const Color &c) { stroke_color = c; }
			void setStrokeWidth(size_t w) { stroke_width = w; }
			void setOpacity(float o) { opacity = o; }
			Point centre(){ return center; }
			ShapeType getType() override { return ShapeType::Cercle; }
			friend std::ostream& operator<<(std::ostream& s, const Disk& d);
			friend SVG::stream& operator<<(SVG::stream& s, const Disk& p);
		};
		////////////////////////////////////////////////////////////////////////////////////////
		//  Ellipse
		class Ellipse :
			public Base, public FillProperty{
		protected:
			Point center;
			float rx, ry;
		public:
			Ellipse():FillProperty(Color::defaut), center(0,0), rx(1), ry(2){}
			Ellipse(const Point &c, float rx, float ry, const Color &col = Color::defaut) :
				FillProperty(col), center(c), rx(rx), ry(ry) {}
			Ellipse(const Point &c, float rx, float ry, const Color &fill, const Color &stroke) :
				FillProperty(fill, stroke), center(c), rx(rx), ry(ry) {}
			Ellipse(const Point &c, float rx, float ry, const Color &fill, const Color &stroke, size_t width) :
				FillProperty(fill, stroke, width), center(c), rx(rx), ry(ry) {}
			virtual ~Ellipse() {}
			virtual std::ostream &info(std::ostream &stream) const;
			virtual void write(SVG::stream &stream) const { stream << *this; }
			void Translate(const Point &v) override { center += v; }
			void Scale(float s) override { rx *= s; ry *= s; }
			void Rotate(float) override {}	// ne rien faire : omission du nom du paramètre (évite un warning "unused parameter")
			void setRadius(float x, float y) { rx = x; ry = y; }
			void setCenter(const Point &c) { center = c; }
			void setFillColor(const Color &c) { fill_color = c; }
			void setStrokeColor(const Color &c) { stroke_color = c; }
			void setStrokeWidth(size_t w) { stroke_width = w; }
			void setOpacity(float o) { opacity = o; }
			Point centre(){ return center; }
			ShapeType getType() override { return ShapeType::Ellipse; }
			friend std::ostream& operator<<(std::ostream& s, const Ellipse& d);
			friend SVG::stream& operator<<(SVG::stream& s, const Ellipse& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Polygon
		class Polygon : public Base, public Array::Fixed<Point>, public FillProperty{
		public:
			Polygon():Array::Fixed<Point>(3),FillProperty(Color::defaut,Color::none,1){
				Array::Geometry::FillnGon(*this,Point(0,0),1);
			}
			Polygon(std::size_t npoints, const Point &centre, float size, const Color &c = Color::defaut);
			Polygon(const std::initializer_list<Point> &list, const Color &c = Color::defaut);
			Polygon(std::size_t npoints, const Point &centre, float size, const Color &fill, const Color &stroke, size_t width);
			virtual ~Polygon() {}
			std::ostream& info(std::ostream& stream) const;
			void write(SVG::stream &stream) const { stream << *this; }
			void Translate(const Point &v) { Array::Geometry::Translate(*this,v); }
			void Scale(float s)            { Array::Geometry::Scale(*this,s); }
			void Rotate(float a)           { Array::Geometry::Rotate(*this,a); }
			void setPoints(const std::initializer_list<Point> &list) { Array::Fixed<Point>::operator=(list); }
			void setFillColor(const Color &c) { fill_color = c; }
			void setStrokeColor(const Color &c) { stroke_color = c; }
			void setStrokeWidth(size_t w) { stroke_width = w; }
			void setOpacity(float o) { opacity = o; }
			Point centre() { return Array::Geometry::Centre(*this); }
			ShapeType getType() override { return ShapeType::Polygone; }
			friend std::ostream& operator<<(std::ostream& s, const Polygon& p);
			friend SVG::stream& operator<<(SVG::stream& s, const Polygon& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Triangle
		class Triangle : public Base, public Array::Static<Point,3>, public FillProperty{
		public:
			Triangle():Array::Static<Point,3>(),FillProperty(Color::defaut){
				Array::Geometry::FillnGon(*this,Point(0,0),1);
			}
			Triangle(const Point &cent, float size, const Color &col = Color::defaut) :
				Array::Static<Point,3>(),FillProperty(col) {
					Array::Geometry::FillnGon(*this,cent,size);
			}
			Triangle(const std::initializer_list<Point> &list, const Color &col = Color::defaut) :
			 Array::Static<Point,3>(list),FillProperty(col){}
			virtual ~Triangle() {}
			std::ostream& info(std::ostream& stream) const;
			void write(SVG::stream &stream) const { stream << *this; }
			void Translate(const Point &v) { Array::Geometry::Translate(*this,v); }
			void Scale(float s) { Array::Geometry::Scale(*this,s); }
			void Rotate(float a) { Array::Geometry::Rotate(*this,a); }
			void setPoints(const Point &p1, const Point &p2, const Point &p3) {
				(*this)[0] = p1; (*this)[1] = p2; (*this)[2] = p3;
			}
			void setFillColor(const Color &c) { fill_color = c; }
			void setStrokeColor(const Color &c) { stroke_color = c; }
			void setStrokeWidth(size_t w) { stroke_width = w; }
			void setOpacity(float o) { opacity = o; }
			Point centre() { return Array::Geometry::Centre(*this); }
			ShapeType getType() override { return ShapeType::Triangle; }
			friend std::ostream& operator<<(std::ostream& s, const Triangle& p);
			friend SVG::stream& operator<<(SVG::stream& s, const Triangle& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Rectangle
		class Rectangle : public Base , public FillProperty{
		protected:
			Point corner;
			float width, height;
			float rotate;
		public:
			Rectangle():FillProperty(Color::defaut), corner(0,0), width(1), height(1), rotate(0){}
			Rectangle(const Point &xy, float w, float h, const Color &c = Color::defaut)
				: FillProperty(c), corner(xy), width(w), height(h), rotate(0.f) {}
			virtual ~Rectangle() {};
			std::ostream& info(std::ostream& stream) const;
			void write(SVG::stream &stream) const { stream << *this; }
			void Translate(const Point &v) { corner += v; }
			void Scale(float s) { width *= s; height *= s; }
			void Rotate(float a) { rotate += a; }
			void setWidth(float w) { width = w; }
			void setHeight(float h) { height = h; }
			void setFillColor(const Color &c) { fill_color = c; }
			void setStrokeColor(const Color &c) { stroke_color = c; }
			void setStrokeWidth(size_t w) { stroke_width = w; }
			void setOpacity(float o) { opacity = o; }
			Point centre() { return Point(corner.getx() + width/2, corner.gety() + height/2); }
			Rectangle *real_type() { return this; }
			ShapeType getType() override { return ShapeType::Rectangle; }
			friend std::ostream& operator<<(std::ostream& s, const Rectangle& d);
			friend SVG::stream& operator<<(SVG::stream& s, const Rectangle& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		///  Square
		class Square : public Rectangle {
			public:
				Square():Rectangle() {}
				Square(const Point &xy, float s, const Color &c = Color::defaut)
					: Rectangle(xy, s, s, c) {}
				void setSide(float s) { width = height = s; }
				void setWidth(float w) = delete;
				void setHeight(float h) = delete;
				virtual ~Square() {};
				std::ostream& info(std::ostream& stream) const;
				void write(SVG::stream &stream) const { stream << *this; }
				ShapeType getType() override { return ShapeType::Carre; }
				friend std::ostream& operator<<(std::ostream& s, const Square& d);
				friend SVG::stream& operator<<(SVG::stream& s, const Square& p);
		};

    namespace Curve {
		////////////////////////////////////////////////////////////////////////////////////////
		// interface FillProperty
		class Stroke {
		protected:
			Color	stroke_color;
			size_t	stroke_width;
			float	opacity = 1.0;
		public:
			explicit Stroke(const Color &c = Color::defaut, size_t width=1) :
				stroke_color(c), stroke_width(width) {}
			void setStrokeColor(const Color &color) { stroke_color = color; }
			void setStrokeWidth(size_t width) { stroke_width = width; }
			const Stroke &getStroke() const { return *this; }
			Point centre(){ return Point(0,0); }
			ShapeType getType() { return ShapeType::Segment; }
			friend std::ostream& operator<<(std::ostream& s, const Stroke& d);
			friend SVG::stream& operator<<(SVG::stream& s, const Stroke& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Surface
		class Base :
			public Geom2D::Base,
			public Stroke {
		public:
			Base() : Geom2D::Base(), Stroke() {}
			Base(const Color &col, size_t width=1) : Stroke(col,width) {}
			virtual ~Base() {}
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Circle
		class Circle :
			public Curve::Base {
		protected:
			Point center;
			float radius;
		public:
			Circle() : Base(), center(0,0), radius(1) {}
			Circle(const Point &xy, float r, const Color &color = Color::defaut, size_t width = 1) :
				Base(color, width), center(xy), radius(r) {}
			virtual ~Circle() {}
			std::ostream& info(std::ostream& stream) const { return stream << *this; }
			void write(SVG::stream &stream) const { stream << *this; }
			void Translate(const Point &v) override { center += v; }
			void Scale(float s) override { radius *= s; }
			void Rotate(float) override {}	// ne rien faire : omission du nom du paramètre (évite un warning "unused parameter")
			void setRadius(float r) { radius = r; }
			void setCenter(const Point &c) { center = c; }
			void setStrokeColor(const Color &c) { stroke_color = c; }
			void setFillColor(const Color) { return; }
			void setStrokeWidth(size_t w) { stroke_width = w; }
			void setOpacity(float o) { opacity = o; }
			Point centre(){ return center; }
			ShapeType getType() override { return ShapeType::Cercle; }
			friend std::ostream& operator<<(std::ostream& s, const Circle& d);
			friend SVG::stream& operator<<(SVG::stream& s, const Circle& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Polyline
		class Polyline :
			public Curve::Base,
			public Array::Fixed<Point> {
		public:
			Polyline(std::size_t npoints=3, const Point &centre=Point(0,0), float size=1, const Color &c = Color::defaut, size_t width = 1);
			Polyline(const std::initializer_list<Point> &list, const Color &c = Color::defaut, size_t width = 1);
			virtual ~Polyline() {}
			std::ostream& info(std::ostream& stream) const { return stream << *this; }
			void write(SVG::stream &stream) const { stream << *this; }
			void Translate(const Point &v) { Array::Geometry::Translate(*this,v); }
			void Scale(float s) { Array::Geometry::Scale(*this,s); }
			void Rotate(float a) { Array::Geometry::Rotate(*this,a); }
			Point centre(){ return Array::Geometry::Centre(*this); }
			void setPoints(std::initializer_list<Point> list) { Array::Fixed<Point>::operator=(list); }
			void setFillColor(const Color) { return; }
			void setStrokeColor(const Color &c) { stroke_color = c; }
			void setStrokeWidth(size_t w) { stroke_width = w; }
			void setOpacity(float o) { opacity = o; }
			ShapeType getType() override { return ShapeType::Polyline; }
			friend std::ostream& operator<<(std::ostream& s, const Polyline& p);
			friend SVG::stream& operator<<(SVG::stream& s, const Polyline& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Segment
		class Segment :
			public Curve::Base,
			public Array::Static<Point,2> {
		public:
			Segment() : Base(), Array::Static<Point,2>() {}
			Segment(const Point &p1, const Point &p2, const Color &col = Color::defaut, size_t width = 1) :
				Base(col, width), Array::Static<Point,2>({p1,p2}) {}
			Segment(const std::initializer_list<Point> &list, const Color &col = Color::defaut, size_t width = 1) :
				Base(col, width), Array::Static<Point,2>(list) {
				assert(list.size() == 2);
			}
			virtual ~Segment() {}
			std::ostream& info(std::ostream& stream) const { return stream << *this; }
			void write(SVG::stream &stream) const { stream << *this; }
			void Translate(const Point &v) { Array::Geometry::Translate(*this,v); }
			void Scale(float s) { Array::Geometry::Scale(*this,s); }
			void Rotate(float a) { Array::Geometry::Rotate(*this,a); }
			void setPoints(const Point &p1, const Point &p2) { (*this)[0] = p1; (*this)[1] = p2; }
			void setStrokeColor(const Color &c) { stroke_color = c; }
			void setStrokeWidth(size_t w) { stroke_width = w; }
			void setFillColor(const Color) { return; }
			void setOpacity(float o) { opacity = o; }
			Point centre(){ return Array::Geometry::Centre(*this); }
			ShapeType getType() override { return ShapeType::Segment; }
			friend std::ostream& operator<<(std::ostream& s, const Segment& p);
			friend SVG::stream& operator<<(SVG::stream& s, const Segment& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  inline definitions

		// polyline
		inline Polyline::Polyline(std::size_t npts, const Point &cent, float size, const Color &color, size_t width) :
			Base(color,width), Array::Fixed<Point>(npts) {
				Array::Geometry::FillnGon(*this,cent,size);
			}
		inline Polyline::Polyline(const std::initializer_list<Point> &list, const Color &color, size_t width) :
			Base(color,width), Array::Fixed<Point>(list) {}

	}

		////////////////////////////////////////////////////////////////////////////////////////
		//  inline definitions
}
		// polygon
		inline Geom2D::Polygon::Polygon(std::size_t npts, const Point &cent, float size, const Color &color) :
		Array::Fixed<Point>(npts),FillProperty(color){
				Array::Geometry::FillnGon(*this,cent,size);
		}
		inline Geom2D::Polygon::Polygon(const std::initializer_list<Point> &list, const Color &color) : Array::Fixed<Point>(list),FillProperty(color){}
		inline Geom2D::Polygon::Polygon(std::size_t npts, const Point &cent, float size, const Color &fill, const Color &stroke, size_t width) : Array::Fixed<Point>(npts),FillProperty(fill,stroke,width){
				Array::Geometry::FillnGon(*this,cent,size);
		}


