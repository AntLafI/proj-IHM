#ifndef SVGCIRCLE_H
#define SVGCIRCLE_H
#include "SvgBase.h"
#include "Point2D.h"

class SVGCircle : public SVGBase{
public:
	Point2D center;
	float rad;
	std::string get_xml_node() const override{
        std::stringstream ss;
		Point2D c = center + coordinates;
		ss << "<circle "
           << "cx=\"" << c.x << "\" "
           << "cy=\"" << c.y << "\" "
		   << "r=\"" << rad << "\""
		   << "/>" ;
		return ss.str();
	}
};
#endif
