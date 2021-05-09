#pragma once
#include<AABB.hpp>
#include<Face.hpp>

class IntersectionTool
{
public:
	IntersectionTool();
	~IntersectionTool();

	static bool IsIntersect(AABB&, Face*);
	static bool IsIntersect(AABB&, std::vector<Face*>);
private:
	static void Project(std::vector<Vector>, Vector, double&, double&);
};