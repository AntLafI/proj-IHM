#pragma once
#include "SvgBase.h"
#include "Point2D.h"
#include <stringstream>
class SVGCircle : public SVGBase{
public:
	Point2D center;
	float rad;
	std::string get_xml_node() const override{
		std:stringstream ss();
		Point2D c = center + coordinates;
		ss << "<circle "
		   << "cx=\"" << center.x << "\" "
		   << "cy=\"" << center.y << "\" "
		   << "r=\"" << rad << "\""
		   << "/>" ;
		return ss.str();
	}
};