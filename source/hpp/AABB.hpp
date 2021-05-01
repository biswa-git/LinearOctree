#pragma once
#include<Face.hpp>
#include<Vector.hpp>
#include<vector>

class Face;
class AABB
{
public:
    AABB();
    AABB(const Vector&, const Vector&);
    ~AABB();
    void Assign(const Vector&, const Vector&);
    
    Vector GetMin() const;
    Vector GetMax() const;

    static bool IsIntersect(const AABB&, const AABB&);
    static AABB GetAABB(const std::vector<Face*>&);
    static AABB Union(const AABB&, const AABB&);
private:
    Vector m_min;
    Vector m_max;
};
