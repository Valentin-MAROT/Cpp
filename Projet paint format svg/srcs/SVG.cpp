#include "../headers/SVG.h"

void SVG::stream::write_header(size_t width,size_t height,bool PureSVG) {
	if (!PureSVG) *this << "<!DOCTYPE html>" << std::endl;
	*this << "<svg width=\""<< width << "\" height=\""<< height << "\" xmlns=\"http://www.w3.org/2000/svg\" >" << std::endl;
}

void SVG::stream::write_trailer() {
	*this << "</svg>" << std::endl;
}

void SVG::stream::close() {
	if (is_open()) {
		write_trailer();
		std::ofstream::close();   // close hérité
	}
}

bool SVG::stream::open(const char *fname, size_t width, size_t height, bool PureSVG) {
	close(); // c'est toujours la surcharge
	std::ofstream::open(fname, std::ios::out | std::ios::trunc); // open hérité
	bool status = is_open();
	if (status) write_header(width,height,PureSVG);
	return status;
}

SVG::stream::stream(const char *fname,size_t width, size_t height, bool PureSVG):
	std::ofstream(fname, std::ios::out | std::ios::trunc) {
	if (is_open()) write_header(width,height,PureSVG);
}

SVG::stream::~stream() {
	close();
}

template <typename T> static inline SVG::stream& write_into_stream(SVG::stream& s, T val) {
	std::ofstream &f = s;
	f << val;
	return s;
}

SVG::stream& SVG::operator<<(SVG::stream& s, const char *str) { return write_into_stream(s, str); }
SVG::stream& SVG::operator<<(SVG::stream& s, const float val) { return write_into_stream(s, val); }
SVG::stream& SVG::operator<<(SVG::stream& s, const std::size_t val) { return write_into_stream(s, val); }
