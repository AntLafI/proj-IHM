#include "SvgBase.h"
#include "Point2D.h"

class SVGRect : public SVGBase{
	Point2D xy;
	Point2D size;
	float rx,ry;//corner radius
};