#include "../headers/Shape.h"
#include "../headers/Array.h"
#include "../headers/SVG.h"

namespace Geom2D {
	namespace Curve {
		// stroke
		std::ostream& operator<<(std::ostream& s, const Stroke& p) {
			return s << "stroke=" << p.stroke_color << " width=" << p.stroke_width << " opacity=" << p.opacity;
		}

		SVG::stream& operator<<(SVG::stream& s, const Stroke& p) {
			const Color col_none = Color(Color::none);
			return s << " stroke=" << quoted(p.stroke_color)
				<< " stroke-width=" << quoted(p.stroke_width)
				<< " fill=" << quoted(col_none) << " opacity=" << quoted(p.opacity);
		}

		// Circle
		std::ostream& operator<<(std::ostream& s, const Circle& d) {
			return s << "Circle[center=" << d.center << " radius=" << d.radius
				<< " " << d.getStroke() << "]";
		}

		SVG::stream& operator<<(SVG::stream& s, const Circle& p) {
			return s << "<circle"
				<< " cx=" << quoted(p.center.getx()) << " cy=" << quoted(p.center.gety())
				<< " r=" << quoted(p.radius)
				<< p.getStroke()
				<< "/>\n";
		}

		// Polyline
		std::ostream& operator<<(std::ostream& s, const Polyline& p) {
			const Array::Fixed<Point> &pp = p;
			return s << "Polyline[nVertex=" << p.size() << " " << pp << " " << p.getStroke() << "]";
		}

		SVG::stream& operator<<(SVG::stream& s, const Polyline& p) {
			const Array::Fixed<Point> &pp = p;
			return s << "<polyline"
				<< " points=" << quoted(pp)
				<< p.getStroke()
				<< "/>\n";
		}

		// Segment
		std::ostream& operator<<(std::ostream& s, const Segment& p) {
			const Array::Static<Point,2>  &pp = p;
			return s << "Segment[" << pp << " " << p.getStroke() << "]";
		}

		SVG::stream& operator<<(SVG::stream& s, const Segment& p) {
			const Array::Static<Point,2>  &pp = p;
			return s << "<polyline"
				<< " points=" << quoted(pp)
				<< p.getStroke()
				<< "/>\n";
		}

	}
}

// mot-clé pour l'initialisation
Default	defaut;
None	none;
Empty	empty;

////////////////////////////////////////////////////////////////////////////////////////
// classe de base de Color
const char *Color::name[] = { "red", "white", "yellow", "orange", "turquoise",
	"violet", "pink", "green", "grey", "cyan", "blue", "brown", "none" };
const Color::colortype Color::defaut;

namespace Geom2D {
	////////////////////////////////////////////////////////////////////////////////////////
	// classe de base de Geom2D
	Base::~Base() = default;

			// Fill
		std::ostream& operator<<(std::ostream& s, const FillProperty& p) {
			return s << "fill=" << p.GetFillColor() << " stroke=" << p.GetStrokeColor() << " stroke-width=" << p.GetStrokeWidth() << " opacity=" << p.GetOpacity();
		}

		SVG::stream& operator<<(SVG::stream& s, const FillProperty& p) {
			return s << " fill=" << quoted(p.GetFillColor())
				<< " stroke=" << quoted(p.GetStrokeColor())
				<< " stroke-width=" << quoted(p.GetStrokeWidth())
				<< " opacity=" << quoted(p.GetOpacity());
		}

		// Disk
		std::ostream& Disk::info(std::ostream& stream) const { return stream << *this; }

		std::ostream& operator<<(std::ostream& s, const Disk& d) {
			return s << "Disk[center=" << d.center << ",radius=" << d.radius
			<< " fill=" << d.fill_color << " stroke="<< d.stroke_color << " stroke-width=" << d.stroke_width << "]";
		}

		SVG::stream& operator<<(SVG::stream& s, const Disk& p) {
			return s << "<circle"
				<< " cx=" << quoted(p.center.getx()) << " cy=" << quoted(p.center.gety())
				<< " r=" << quoted(p.radius)
				<< p.GetFillProperty()
				<< "/>\n";
		}

		// Ellipse
		std::ostream& Ellipse::info(std::ostream& stream) const { return stream << *this; }

		std::ostream& operator<<(std::ostream& s, const Ellipse& d) {
			return s << "Ellipse[center=" << d.center << ",radiusX=" << d.rx << ",radiusY=" << d.ry
				<< d.GetFillProperty() << "]";
		}

		SVG::stream& operator<<(SVG::stream& s, const Ellipse& d) {
			return s << "<ellipse"
				<< " cx=" << quoted(d.center.getx()) << " cy=" << quoted(d.center.gety())
				<< " rx=" << quoted(d.rx) << " ry=" << quoted(d.ry)
				<< d.GetFillProperty()
				<< "/>\n";
		}

		// Polygon
		std::ostream& Polygon::info(std::ostream& stream) const { return stream << *this; }

		std::ostream& operator<<(std::ostream& s, const Polygon& p) {
			const Array::Fixed<Point> &pp = p;
			return s << "Polygon[nVertex=" << p.size() << "," << pp
				<< p.GetFillProperty() << "]";
		}

		SVG::stream& operator<<(SVG::stream& s, const Polygon& p) {
			const Array::Fixed<Point> &pp = p;
			return s << "<polygon "
				<< " points=" << quoted(pp)
				<< p.GetFillProperty()
				<< "/>\n";
		}

		// Triangle
		std::ostream& Triangle::info(std::ostream& stream) const { return stream << *this; }

		std::ostream& operator<<(std::ostream& s, const Triangle& p) {
			const Array::Static<Point,3> &pp = p;
			return s << "Triangle["  << pp 	<< p.GetFillProperty() << "]";
		}

		SVG::stream& operator<<(SVG::stream& s, const Triangle& p) {
			const Array::Static<Point,3> &pp = p;
			return s << "<polygon "
				<< " points=" << quoted(pp)
				<< p.GetFillProperty()
				<< "/>\n";
		}

		// Rectangle
		std::ostream& Rectangle::info(std::ostream& stream) const { return stream << *this; }

		std::ostream& operator<<(std::ostream& s, const Rectangle& d) {
			return s << "Rectangle[corner=" << d.corner
				<< " width=" << d.width	 << " height=" << d.height
				<< " angle=" << d.rotate << d.GetFillProperty() << "]";
		}

		SVG::stream& operator<<(SVG::stream& s, const Rectangle& p) {
			s << "<rect"
				<< " x=" << quoted(p.corner.getx()) << " y=" << quoted(p.corner.gety())
				<< " width=" << quoted(p.width) << " height=" << quoted(p.height)
				<< p.GetFillProperty();
			if (p.rotate) {
				Point center(p.corner.getx() + p.width / 2.f, p.corner.gety() + p.height / 2.f);
				s << " transform=" << quoted("rotate(" << p.rotate << " " << center << ")");
			}
			return s << "/>\n";
		}

		// Square
		std::ostream& Square::info(std::ostream& stream) const { return stream << *this; }

		std::ostream& operator<<(std::ostream& s, const Square& d) {
			return s << "Square[corner=" << d.corner
				<< " sidelen=" << d.width
				<< d.GetFillProperty() << "]";
		}
		SVG::stream& operator<<(SVG::stream& s, const Square& p) {
			const Rectangle& pp = p;
			return s << pp;
		}


}

