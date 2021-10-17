#include <bits/stdc++.h>
using namespace std;

#define FastIO cin.tie(0);cout.tie(0);ios::sync_with_stdio(0);
#define LSOne(a) ( (a) & -(a) )
#define SQ(a) (a)*(a)
#define INF  ll(4e18)
#define OO   int(1e9)
#define EPS      1e-9
#define PB  push_back
#define MP  make_pair
#define S      second
#define F       first

typedef long long       ll;
typedef long double     ld;
typedef pair<int , int> ii;
typedef pair<int , ii>  iii;
typedef pair<ll , ll>   pll;
typedef pair<ll , pll>  plll;
typedef vector< int >   vi;
typedef vector< ll >    vl;
typedef vector< ii >    vii;
typedef vector< pll >   vll;
typedef vector< iii >   viii;
typedef vector< plll >  vlll;

const ll MOD = 1e9 + 7;
const ll N = 2e5 + 5e1;

const double PI = acos(-1.0);

double DEG_to_RAD(double d)
{
	return d * PI / 180.0;
}

double RAD_to_DEG(double r)
{
	return r * 180.0 / PI;
}

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

	bool operator != (Point p) const
	{
		return (fabs(x - p.x) > EPS) || (fabs(y - p.y) > EPS);
	}
};

double dist(Point p1 ,Point p2)
{
	return hypot(p1.x - p2.x ,p1.y - p2.y);
}

// NOTE: Functions Uses Radian Not Degree
// rotate p by theta degrees around origin (0 ,0)
Point rotate(Point p ,double theta) // theta in degree
{
	double rad = DEG_to_RAD(theta);

	double x1 = p.x * cos(rad) - p.y * sin(rad);
	double y1 = p.x * sin(rad) + p.y * cos(rad);

	return Point(x1 ,y1);
}

struct Line
{
	// ax + by + c = 0
	double a;
	double b;
	double c;

	// constructor
	Line() : a(0.0) ,b(0.0) ,c(0.0) {}
	Line(double _a ,double _b ,double _c) : a(_a) ,b(_b) ,c(_c) {}
};

// Make line from 2 points
Line pointsToLine(Point p1 ,Point p2)
{
	if( fabs(p1.x - p2.x) < EPS ) return Line(1.0 ,0.0 ,-p1.x);

	double m = double(p1.y - p2.y) / double(p1.x - p2.x);
	double a = -m;
	double b = 1.0;
	double c = -(a * p1.x + b * p1.y);

	return Line(a ,b ,c);
}

// Make line from point and gradient
// NOT FOR VERTICAL LINE ,X1 != X2 ,m < OO 
// But try it with the first if and check the OO
Line pointsGradientToLine(Point p ,double m)
{
	if( fabs(double(INT_MAX) - m) < EPS ) return Line(1.0 ,0.0 ,-p.x);

	double a = -m;
	double b = 1.0;
	double c = -(a * p.x + b * p.y);

	return Line(a ,b ,c);
}

bool areParallel(Line l1 ,Line l2) // check a & b
{
	// ax + by + c1 = 0 | ax + by + c2 = 0
	return (fabs(l1.a - l2.a) < EPS) && (fabs(l1.b - l2.b) < EPS);
}

bool areSame(Line l1 ,Line l2) // also check c
{
	// ax + by + c = 0 | ax + by + c = 0
	return areParallel(l1 ,l2) && (fabs(l1.c - l2.c) < EPS);
}

pair<bool , Point> areIntersect(Line l1 ,Line l2)
{
	/********************************************
		return false if they are parallel
		return true if they're not parallel
		store the intersect point in p
		by solving a system of two equations:
		a1x + b1y + c1 = 0 & a2x + b2y + c2 = 0 
		balta3weed :)
	********************************************/

	Point p;
	if( areParallel(l1 ,l2) ) return make_pair(false ,p);

	p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
	p.y = (fabs(l1.b) > EPS) ? -(l1.a * p.x + l1.c) : -(l2.a * p.x + l2.c);

	return make_pair(true ,p);
}

struct Vec
{
	// vector: (0 ,0) => (x ,y)
	double x;
	double y;

	// constructor
	Vec() : x(0.0) ,y(0.0) {}
	Vec(double _x ,double _y) : x(_x) ,y(_y) {}

	double size()
	{
		return hypot(x ,y);
	}
};

// Make vector from two points (a => b)
Vec toVec(Point a ,Point b)
{
	return Vec(b.x - a.x ,b.y - a.y);
}

double norm_sq(Vec v)
{
	return v.x * v.x + v.y * v.y;
}

Vec scale(Vec v ,double s)
{
	return Vec(v.x * s ,v.y * s);
}

Point translate(Point p ,Vec v)
{
	return Point(p.x + v.x ,p.y + v.y);
}

// DOT PRODUCT: jeda2 sulame
double dot(Vec a ,Vec b)
{
	// a * b = |a| * |b| * cos(@)
	// a * b = a.x * b.x + a.y * b.y
	// dotP = | vec b1 (Projection of b on a) | * |a|
	// dotP = 0 when a perpendicular b => @ = 90
	return a.x * b.x + a.y * b.y;
}

// CROSS PRODUCT: jeda2 shu3a3e
double cross(Vec a ,Vec b)
{
	// crossP = 0 when a parallel b => @ = 0
	// crossP = area of mutauazy Aladla3 ab
	return a.x * b.y - a.y * b.x;
}

// calc angle aob; 0 <= aob <= 180
double angle(Point a ,Point o ,Point b)
{
	Vec oa = toVec(o ,a);
	Vec ob = toVec(o ,b);

	// oa * ob = |oa| * |ob| * cos(@)
	// oa * ob = oa.x * ob.x + oa.y * ob.y
	// @ = arcCos((oa * ob) / (|oa| * |ob|)) 

	double dotP = dot(oa ,ob);
	double lenP = oa.size() * ob.size();

	if( fabs(lenP) < EPS ) return 0.0;

	// angle aob in rad
	return acos(dotP / lenP);
}

// check if Vec pq and pr make a CounterClockWise turn
bool ccw(Point p ,Point q ,Point r)
{
	// when they make ccw the product pq.x * pr.y > pq.y * pr.x
	// because pq.x ,pr.y are larger than pq.y ,pr.x
	// here true mean that r located to the left of pq
	return cross(toVec(p ,q) ,toVec(p ,r)) > -EPS;
}

// check if Vec pq and pr are collinear
bool collinear(Point p ,Point q ,Point r)
{
	// when they are collinear the product pq.x * pr.y == pq.y * pr.x
	return fabs(cross(toVec(p ,q) ,toVec(p ,r))) < EPS;
}

// Given three points p, q, r, the function checks if
// point q lies on line segment 'pr'
// they must be collinear first
bool onSegment(Point p, Point q, Point r)
{
	return collinear(p ,q ,r) &&
		   min(p.x ,r.x) <= q.x && q.x <= max(p.x ,r.x) &&
		   min(p.y ,r.y) <= q.y && q.y <= max(p.y ,r.y);
}

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool LineSegmentsDoIntersect(Point p1, Point q1, Point p2, Point q2)
{
	// Find the four orientations needed for general and special cases
	bool o1 = ccw(p1, q1, p2);
	bool o2 = ccw(p1, q1, q2);
	bool o3 = ccw(p2, q2, p1);
	bool o4 = ccw(p2, q2, q1);

	// General case
	if( o1 != o2 && o3 != o4 ) return true;

	o1 = collinear(p1, q1, p2);
	o2 = collinear(p1, q1, q2);
	o3 = collinear(p2, q2, p1);
	o4 = collinear(p2, q2, q1);

	// Special Cases
	// p1, q1 and p2 are collinear and p2 lies on segment p1q1
	if( o1 && onSegment(p1, p2, q1) ) return true;

	// p1, q1 and q2 are collinear and q2 lies on segment p1q1
	if( o2 && onSegment(p1, q2, q1) ) return true;

	// p2, q2 and p1 are collinear and p1 lies on segment p2q2
	if( o3 && onSegment(p2, p1, q2) ) return true;

	// p2, q2 and q1 are collinear and q1 lies on segment p2q2
	if( o4 && onSegment(p2, q1, q2) ) return true;

	return false; // Doesn't fall in any of the above cases
}

// calc dist from point to line represented by two distnect points
// return pair<dist , point Projection>
pair<double , Point> distPointToLine(Point p ,Point a ,Point b)
{
	Vec ap = toVec(a ,p);
	Vec ab = toVec(a ,b);

	double u = dot(ap ,ab) / norm_sq(ab);
	Point c = translate(a ,scale(ab ,u));
	// formula: c = a + u * ab

	return make_pair(dist(p ,c) ,c);
}

// calc dist from point to line
// return pair<dist , point Projection>
pair<double , Point> distPointToLine(Point p ,Line l)
{
	if( fabs(l.a) < EPS ) // horizontal line
	{
		// l must be {0.0 ,1.0 ,c}
		
		Point c(p.x ,-l.c);
		return make_pair(dist(p ,c) ,c);
	}

	if( fabs(l.b) < EPS ) // vertical line
	{
		// l must be {1.0 ,0.0 ,c}

		Point c(-l.c ,p.y);
		return make_pair(dist(p ,c) ,c);
	}

	double m1 = -l.a;
	double m2 = -1 / m1;

	Line perpendicular = pointsGradientToLine(p ,m2);

	Point c = areIntersect(l ,perpendicular).S;

	return make_pair(dist(p ,c) ,c);
}

// calc dist from point to line segment represented by two distnect points
// return pair<dist , point Projection>
pair<double , Point> distPointToLineSegment(Point p ,Point a ,Point b)
{
	Vec ap = toVec(a ,p);
	Vec ab = toVec(a ,b);

	double u = dot(ap ,ab) / norm_sq(ab);

	if( u < 0.0 ) return make_pair(dist(p ,a) ,a);
	if( u > 1.0 ) return make_pair(dist(p ,b) ,b);
	
	return distPointToLine(p ,a ,b);
}

int main()
{

	return 0;
}
