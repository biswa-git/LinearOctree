#include<AABB.hpp>
#include<algorithm>

AABB::AABB() : m_min(NULL_VECTOR), m_max(NULL_VECTOR)
{

}

AABB::AABB(const Vector& min, const Vector& max) : m_min(min), m_max(max)
{

}

AABB::~AABB()
{
}

void AABB::Assign(const Vector& min, const Vector& max)
{
    m_min = min;
    m_max = max;
}

Vector AABB::GetMin() const
{
    return m_min;
}

Vector AABB::GetMax() const
{
    return m_max;
}

std::vector<Vector> AABB::GetVerticesVector()
{
    std::vector<Vector> result;

    auto& min = this->GetMin();
    auto& max = this->GetMax();

    result.emplace_back(Vector(min[0], min[1], min[2]));
    result.emplace_back(Vector(min[0], min[1], max[2]));
    result.emplace_back(Vector(min[0], max[1], min[2]));
    result.emplace_back(Vector(min[0], max[1], max[2]));
    result.emplace_back(Vector(max[0], min[1], min[2]));
    result.emplace_back(Vector(max[0], min[1], max[2]));
    result.emplace_back(Vector(max[0], max[1], min[2]));
    result.emplace_back(Vector(max[0], max[1], max[2]));

    return result;
}

bool AABB::IsIntersect(const AABB& bb_first, const AABB& bb_second)
{
    return (bb_first.m_min.GetDx() <= bb_second.m_max.GetDx() && bb_first.m_max.GetDx() >= bb_second.m_min.GetDx()) &&
           (bb_first.m_min.GetDy() <= bb_second.m_max.GetDy() && bb_first.m_max.GetDy() >= bb_second.m_min.GetDy()) &&
           (bb_first.m_min.GetDz() <= bb_second.m_max.GetDz() && bb_first.m_max.GetDz() >= bb_second.m_min.GetDz());
}

AABB AABB::Union(const AABB& box_first, const AABB& box_second)
{
    auto box_first_min = box_first.GetMin();
    auto box_first_max = box_first.GetMax();
    auto box_second_min = box_second.GetMin();
    auto box_second_max = box_second.GetMax();
    
    Vector min(
        std::min(box_first_min.GetDx(), box_second_min.GetDx()),
        std::min(box_first_min.GetDy(), box_second_min.GetDy()),
        std::min(box_first_min.GetDz(), box_second_min.GetDz())
    );
    Vector max(
        std::max(box_first_max.GetDx(), box_second_max.GetDx()),
        std::max(box_first_max.GetDy(), box_second_max.GetDy()),
        std::max(box_first_max.GetDz(), box_second_max.GetDz())
    );

    return AABB(min, max);
}

AABB AABB::GetAABB(const std::vector<Face*>& faces)
{
    AABB result;
    AABB temp;
    if (!faces.empty())
    {
        auto it = faces.begin();
        result.Assign((*it)->GetAABB().GetMin(), (*it)->GetAABB().GetMax());
        ++it;

        for (; it != faces.end(); ++it)
        {
            temp = result;
            auto face_AABB = (*it)->GetAABB();
            result = AABB::Union(face_AABB, temp);
        }
    }

    return result;
}
