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

    // Test the box normals (x-, y- and z-axes)
    std::vector<Vector> boxNormals
    {
        Vector(1, 0, 0),
        Vector(0, 1, 0), 
        Vector(0, 0, 1)
    };

    auto triangle_vector = triangle->GetVerticesVector();
    auto AABB_vector = box.GetVerticesVector();

    auto AABB_center = (box.GetMin() + box.GetMax()) / 2.0;

    for (auto& it : triangle_vector)
    {
        it = it - AABB_center;
    }

    for (auto& it : AABB_vector)
    {
        it = it - AABB_center;
    }

    for (int i = 0; i < 3; i++)
    {
        IntersectionTool::Project(triangle_vector, boxNormals[i], triangle_min, triangle_max);
        if (triangle_max < box.GetMin()[i] || triangle_min > box.GetMax()[i])
        {
            return false; // No intersection possible.
        }
    }

    // Test the triangle normal
    double triangleOffset = triangle->GetNormalVector().Unit() * triangle_vector[0];
    Project(AABB_vector, triangle->GetNormalVector().Unit(), box_min, box_max);
    if (box_max < triangleOffset || box_min > triangleOffset)
        return false; // No intersection possible.

    // Test the nine edge cross-products
    std::vector<Vector> triangleEdges
    {
        triangle->GetHalfEdge()[0]->GetEdgeVector(),
        triangle->GetHalfEdge()[1]->GetEdgeVector(),
        triangle->GetHalfEdge()[2]->GetEdgeVector()
    };

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            // The box normals are the same as it's edge tangents
            Vector axis = triangleEdges[i]^boxNormals[j];
            Project(AABB_vector, axis, box_min, box_max);
            Project(triangle_vector, axis, triangle_min, triangle_max);
            if (box_max <= triangle_min || box_min >= triangle_max)
                return false; // No intersection possible
        }

    // No separating axis found.
    return true;
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