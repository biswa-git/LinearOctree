#pragma once
#include<AABB.hpp>
#include<Face.hpp>

struct ProjectResults
{
    double min =  std::numeric_limits<double>::infinity();
    double max = -std::numeric_limits<double>::infinity();
};

class IntersectionTool
{
public:
	IntersectionTool();
	~IntersectionTool();

	static bool IsIntersect(const AABB&, Face*);
	static bool IsIntersect(const AABB&, const std::vector<Face*>&);
private:
	static ProjectResults Project(const std::vector<Vector>&, const Vector&);
};