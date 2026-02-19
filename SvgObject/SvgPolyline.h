#ifndef SVGPOLYLINE_H
#define SVGPOLYLINE_H
#include "SVGBase.h"
#include "Point2D.h"
#include <vector>

class SVGPolyline : public SVGBase{
public:
	std::vector<Point2D> points;
	std::string get_xml_node() const override{
        std::stringstream ss;
		ss << "<polyline ";
        ss << "points=\"";
		for(Point2D p : points){
		   ss << p.x << ',' << p.y << ' ';
		}
        ss << "\"";
        ss << "fill=\"none\"";
        ss << "/>" ;
		return ss.str();
	}
};
#endif
