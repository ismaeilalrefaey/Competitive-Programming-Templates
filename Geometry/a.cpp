const double PI = acos(-1.0);

struct Point
{
	double x;
	double y;

	Point() : x(0.0) ,y(0.0) {}
	Point(double _x ,double _y) : x(_x) ,y(_y) {}

	bool operator < (Point p) const
	{
		return (fabs(x - p.x) > EPS) ? (x < p.x) : (y < p.y);
	}

	bool operator > (Point p) const
	{
		return (fabs(x - p.x) > EPS) ? (x > p.x) : (y > p.y);
	}

	bool operator == (Point p) const
	{
		return (fabs(x - p.x) < EPS) && (fabs(y - p.y) < EPS);
	}
};

double dist(const Point &p1 ,const Point &p2)
{
	return hypot(p1.x - p2.x ,p1.y - p2.y);
}

// NOTE: Functions Uses Radian Not Degree

double DEG_to_RAD(double d)
{
	return d * PI / 180.0;
}

double RAD_to_DEG(double r)
{
	return r * 180.0 / PI;
}

// rotate p by theta degrees around origin (0 ,0)
Point rotate(const Point &p ,double theta) // theta in degree
{
	double rad = DEG_to_RAD(theta);
	return Point(p.x * cos(rad) - p.y * sin(rad) ,p.x * sin(rad) + p.y * cos(rad));
}