#pragma once
#include<IntersectionTool.hpp>

IntersectionTool::IntersectionTool()
{
}

IntersectionTool::~IntersectionTool()
{
}

bool IntersectionTool::IsIntersect(AABB& box, Face* triangle)
{
    double triangle_min, triangle_max;
    double box_min, box_max;

    std::vector<Vector> box_normals
    {
        Vector(1, 0, 0),
        Vector(0, 1, 0), 
        Vector(0, 0, 1)
    };

    auto triangle_vertex_vector = triangle->GetVerticesVector();
    auto AABB_vertex_vector = box.GetVerticesVector();
    for (int i = 0; i < 3; i++)
    {
        IntersectionTool::Project(triangle_vertex_vector, box_normals[i], triangle_min, triangle_max);
        if (triangle_max < box.GetMin()[i] || triangle_min > box.GetMax()[i])
        {
            return false; // No intersection possible.
        }
    }

    // Test the triangle normal
    double triangle_offset = triangle->GetNormalVector().Unit() * triangle_vertex_vector[0];
    Project(AABB_vertex_vector, triangle->GetNormalVector().Unit(), box_min, box_max);
    if (box_max < triangle_offset || box_min > triangle_offset)
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
            Project(AABB_vertex_vector, axis, box_min, box_max);
            Project(triangle_vertex_vector, axis, triangle_min, triangle_max);
            if (box_max < triangle_min || box_min > triangle_max)
            {
                return false; // No intersection possible
            }
        }

    // No separating axis found.
    return true;
}
bool IntersectionTool::IsIntersect(AABB& box, std::vector<Face*> faces)
{
    for (auto face : faces)
    {
        if(IsIntersect(box, face)) return true;
    }
}

void IntersectionTool::Project(std::vector<Vector> points, Vector axis, double& min, double& max)
{
    min = std::numeric_limits<double>::infinity();
    max = -std::numeric_limits<double>::infinity();

    for (auto p : points)
    {
        auto val = axis * p;
        if (val < min) min = val;
        if (val > max) max = val;
    }
}