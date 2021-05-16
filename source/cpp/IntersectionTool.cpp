#pragma once
#include<IntersectionTool.hpp>

IntersectionTool::IntersectionTool()
{
}

IntersectionTool::~IntersectionTool()
{
}

bool IntersectionTool::IsIntersect(const AABB& box, Face* triangle)
{
    std::vector<Vector> box_normals
    {
        Vector(1, 0, 0),
        Vector(0, 1, 0), 
        Vector(0, 0, 1)
    };

    auto triangle_vertex_vector = triangle->GetVerticesVector();
    auto AABB_vertex_vector = box.GetVerticesVector();

    /*
    for (int i = 0; i < 3; i++)
    {
        IntersectionTool::Project(triangle_vertex_vector, box_normals[i], triangle_min, triangle_max);
        if (triangle_max < box.GetMin()[i] || triangle_min > box.GetMax()[i])
        {
            return false; // No intersection possible.
        }
    }
    */

    // Test the triangle normal
    ProjectResults box_bound;
    ProjectResults triangle_bound;
    double triangle_offset = triangle->GetNormalVector().Unit() * triangle_vertex_vector[0];
    box_bound = Project(AABB_vertex_vector, triangle->GetNormalVector().Unit());
    if (box_bound.max < triangle_offset || box_bound.min > triangle_offset)
    {
        return false; // No intersection possible.
    }

    std::vector<Vector> triangle_edges
    {
        triangle->GetHalfEdge()[0]->GetEdgeVector(),
        triangle->GetHalfEdge()[1]->GetEdgeVector(),
        triangle->GetHalfEdge()[2]->GetEdgeVector()
    };

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            Vector axis = triangle_edges[i]^box_normals[j];
            box_bound = Project(AABB_vertex_vector, axis);
            triangle_bound = Project(triangle_vertex_vector, axis);
            if (box_bound.max < triangle_bound.min || box_bound.min > triangle_bound.max)
            {
                return false; // No intersection possible
            }
        }

    // No separating axis found.
    return true;
}

bool IntersectionTool::IsIntersect(const AABB& box, const std::vector<Face*>& faces)
{
    for (auto face : faces)
    {
        if(IsIntersect(box, face)) return true;
    }
    return false;
}

ProjectResults IntersectionTool::Project(const std::vector<Vector>& points, const Vector& axis)
{
    ProjectResults result;

    for (auto p : points)
    {
        auto value = axis * p;
        if (value < result.min)
        {
            result.min = value;
        }
        if (value > result.max)
        {
            result.max = value;
        }
    }

    return result;
}