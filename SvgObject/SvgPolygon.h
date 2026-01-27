#include "SvgPolyline.h"
#include "Point2D.h"
class SVGPolygon : public SVGPoliline{
public:
	std::string get_xml_node() const override{
		std:stringstream ss();
		ss << "<polygon ";
		ss << "points=\""
		for(Point2D p : points){
		   ss << p.x << ',' << p.y << ' ';
		}
		ss << "\"/>" ;
		return ss.str();
	}
};