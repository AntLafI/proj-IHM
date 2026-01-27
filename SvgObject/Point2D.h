struct Point2D{
	float x,y;
	Point2D(float _x,_y) : x(_x),y(_y){}
	Point2D(float v) : x(v),y(v){}
	static Point2D ZERO() { return Point2D(0); }
};
