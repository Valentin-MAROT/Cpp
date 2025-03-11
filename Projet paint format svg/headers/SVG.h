#ifndef _SVG_H
#define _SVG_H
#include <fstream>

////////////////////////////////////////////////////////////////////////////////////////
namespace SVG {
	class stream : public std::ofstream {
	private:
		void write_header(size_t width, size_t height, bool PureSVG=false);
		void write_trailer();
	public:
		void close();
		bool open(const char *fname, size_t width, size_t height, bool PureSVG=false);
		stream(const char *fname,size_t width, size_t height,bool PureSVG = false);
		~stream();
		friend stream& operator<<(stream& s, const char *str);
		friend stream& operator<<(stream& s, const float val);
		friend stream& operator<<(stream& s, const size_t val);
	};

	class Write {
	protected:
		virtual void write(SVG::stream&) const = 0;
	};

	stream& operator<<(stream& s, const char *str);
	stream& operator<<(stream& s, const float val);
	stream& operator<<(stream& s, const std::size_t val);
}

#define quoted(x) "\"" << x << "\""

#endif
