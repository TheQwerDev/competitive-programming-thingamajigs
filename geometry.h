#include <utility>
#include <vector>
#include <cmath>
#include <climits>

double distPoints(std::pair<int, int> p1, std::pair<int, int> p2)
{
	double x=p1.first-p2.first;
	double y=p1.second-p2.second;
	return sqrt(x*x+y*y);
}

struct line {
	std::pair<int, int> p1, p2;
	int a, b, c;
	line():a(0), b(0), c(0) {}
	line(std::pair<int, int> p1, std::pair<int, int> p2)
	{
		line::p1=p1;
		line::p2=p2;
		if(p1.first>p2.first)
			swap(line::p1, line::p2);
		a=p1.second-p2.second;
		b=p2.first-p1.first;
		c=p1.first*p2.second-p2.first*p1.second;
	}

	double det(pair<int, int> p1, pair<int, int> p2, pair<int, int> p)
	{ return (p2.first-p1.first)*(p.second-p1.second)-(p.first-p1.first)*(p2.second-p1.second); }

	double isPointOnLine(std::pair<int, int> p)
	{ return a*p.first+b*p.second+c; }
	bool isPointOnSegment(std::pair<int, int> p)
	{ return (isPointOnLine(p) == 0 && p.first >= p1.first && p.first <= p2.first); }

	double dist(std::pair<int, int> p)
	{ return abs(a*p.first+b*p.second+c)/(sqrt(a*a+b*b)); }

	double distSegment(std::pair<int, int> p)
	{
		double s, t, u;
		s=distPoints(p, p1);
		t=distPoints(p1, p2);
		u=distPoints(p, p2);

		double angleP1=s*s+t*t-u*u;
		double angleP2=t*t+u*u-s*s;

		if(angleP1<0)
			return s;
		else if(angleP2<0)
			return u;
		else
			return dist(p);
	}

	std::pair<int, int> intersect(line l)
	{
		double x, y=INT_MIN;
		if(a*l.b==l.a*b)
		{
			if(a*l.c!=l.a*c)
				return {INT_MIN, INT_MIN};
			else
				return p1;
		}

		x=(l.c*b-c*l.b)/(a*l.b-l.a*b);

		if(b!=0)
			y=(-c-a*x)/b;
		else if(l.b!=0)
			y=(-l.c-l.a*x)/l.b;

		return {x, y};

	}

	bool intersectSegment(line l)
	{
		//std::pair<int, int> p=intersect(l);
		//return (isPointOnSegment(p) && l.isPointOnSegment(p));
		if(isPointOnSegment(l.p1) || isPointOnSegment(l.p2) || l.isPointOnSegment(p1) || l.isPointOnSegment(p2))
			return true;
		return det(l.p1)*det(l.p2)<0 && l.det(p1)*l.det(p2)<0;
	}

	double slope()
	{ return -a/b; }
};

struct polygon {
	std::vector<std::pair<int, int>> points;

	polygon(std::vector<std::pair<int, int>>& p)
	{
		points=p;
		points.push_back(points[0]);
	}

	double a=0;
	double area()
	{
		if(a==0)
		{
			for(size_t i=0; i<points.size()-1; i++)
				a+=(points[i].first*points[i+1].second-points[i+1].first*points[i].second);
			a/=2;
			a=fabs(a);
		}

		return a;
	}

	int pointCount()
	{ return points.size()-1; }
};