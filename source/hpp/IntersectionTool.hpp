#pragma once
#include<AABB.hpp>
#include<Face.hpp>

class IntersectionTool
{
public:
	IntersectionTool();
	~IntersectionTool();

	static bool IsIntersect(AABB&, Face*);
private:
	static void Project(std::vector<Vector>, Vector, double&, double&);
};