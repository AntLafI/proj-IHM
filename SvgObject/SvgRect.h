#ifndef SVGRECT_H
#define SVGRECT_H
#include "SvgBase.h"
#include "Point2D.h"

class SVGRect : public SVGBase{
public:
	Point2D xy,size,cornerRad;

	std::string get_xml_node() const override{
        std::stringstream ss;
		ss << "<rect "
		   << "\"x=\"" << xy.x << "\" "
		   << "\"width=\"" << size.x << "\" "
		   << "\"y=\"" << xy.y << "\" "
		   << "\"height=\"" << size.y << "\" "
		   << "\"rx=\"" << cornerRad.x << "\" "
		   << "\"ry=\"" << cornerRad.y << "\""
		   << "/>" ;
		return ss.str();
	}

};
#endif
