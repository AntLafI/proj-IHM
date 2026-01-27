#pragma once
#include "SvgBase.h"
#include "Point2D.h"
#include <stringstream>
class SVGEllipse : public SVGBase{
	Point2D c;
	float rx,ry;
	std::string get_xml_node() const override{
		std:stringstream ss();
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