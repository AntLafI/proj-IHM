#ifndef SVGBASE_H
#define SVGBASE_H
#include <string>
#include <sstream>
#include "Point2D.h"
class SVGBase{
public:
	Point2D coordinates,anchor,scale;
	[[nodiscard]]
	virtual std::string get_xml_node() const = 0;
};
#endif
