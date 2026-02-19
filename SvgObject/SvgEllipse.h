#ifndef SVGELLIPSE_H
#define SVGELLIPSE_H
#include "SvgBase.h"
#include "Point2D.h"

class SVGEllipse : public SVGBase{
    Point2D center;
	float rx,ry;
	std::string get_xml_node() const override{
        std::stringstream ss;
        Point2D c = center + coordinates;
		ss << "<ellipse "
		   << "cx=\"" << center.x << "\" "
		   << "cy=\"" << center.y << "\" "
		   << "rx=\"" << rx << "\""
		   << "ry=\"" << ry << "\""
		   << "/>" ;
		return ss.str();
	}
};
#endif
