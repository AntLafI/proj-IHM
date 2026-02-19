#ifndef POINT2D_H
#define POINT2D_H
struct Point2D{
	float x,y;
    Point2D(float _x,float _y) : x(_x),y(_y){}
	Point2D(float v) : x(v),y(v){}
	static Point2D ZERO() { return Point2D(0); }
    Point2D operator+ (const Point2D& b) const{
		return Point2D(x+b.x,y+b.y);
	}
    Point2D operator- (const Point2D& b) const{
		return Point2D(x-b.x,y-b.y);
	}
    void operator +=(const Point2D& b){
        x += b.x;
        y += b.y;
    }
    void operator -=(const Point2D& b){
        x -= b.x;
        y -= b.y;
    }
};
#endif
