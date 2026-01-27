#pragma once
#include <string>
#include "Point2D.h"
class SVGBase{
public:
	Point2D coordinates,anchor,scale;
	[[nodiscard]]
	virtual std::string get_xml_node() const = 0;
};