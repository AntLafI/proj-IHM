#pragma once
#include "SvgBase.h"
#include "Point2D.h"
#include <stringstream>

class SVGLine : public SVGBase{
public:
	Point2D p1 ,p2;
	std::string get_xml_node() const override{
		std:stringstream ss();
		ss << "<line "
		   << "x1=\"" << p1.x << "\" "
		   << "y1=\"" << p1.y << "\" "
		   << "x2=\"" << p2.x << "\" "
		   << "y2=\"" << p2.y << "\" "
		   << "/>" ;
		return ss.str();
};