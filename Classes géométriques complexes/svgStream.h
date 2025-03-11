#ifndef _SVGSTREAM_H
#define _SVGSTREAM_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

class SVGstream {
private:
        std::ofstream    svgstream;
        inline void write_header(bool PureSVG = false) {
                if (!PureSVG) svgstream << "<!DOCTYPE html>" << std::endl;
                svgstream << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1000\" height=\"1000\" >" << std::endl;
        }
        inline void write_trailer() { *this << "</svg>\n"; }
        template <class T> inline SVGstream &write_to_file(const T &val) {
            svgstream << val;
            return *this;
        }
public:
        void close() {
                if (svgstream.is_open()) {
                        write_trailer();
                        svgstream.close();
                }
        }
        bool open(const char *fname, bool PureSVG = false) {
            close();
            svgstream.open(fname, std::ios::out | std::ios::trunc);
            bool status = svgstream.is_open();
            if (status) write_header(PureSVG);
            return status;
        }
        SVGstream(const char *fname, bool PureSVG = false) :
                svgstream(fname, std::ios::out | std::ios::trunc)
        {
            if (svgstream.is_open()) write_header(PureSVG);
        }
        ~SVGstream() { svgstream.close(); }
        friend SVGstream& operator<<(SVGstream& s, float val) {
            return s.write_to_file(val);
        }
        friend SVGstream& operator<<(SVGstream& s, const char *str) {
            return s.write_to_file(str);
        }
};
#endif