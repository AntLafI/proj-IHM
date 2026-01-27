#include "SVGBase.h"
#include "Point2D.h"
#include <vector>
class SVGPolyline : public SVGBase{
	std::vector<Point2D> points;
};