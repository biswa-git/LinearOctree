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

std::vector<Vector> AABB::GetVerticesVector() const
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
    return (bb_first.m_min[0] <= bb_second.m_max[0] && bb_first.m_max[0] >= bb_second.m_min[0]) &&
           (bb_first.m_min[1] <= bb_second.m_max[1] && bb_first.m_max[1] >= bb_second.m_min[1]) &&
           (bb_first.m_min[2] <= bb_second.m_max[2] && bb_first.m_max[2] >= bb_second.m_min[2]);
}

AABB AABB::Union(const AABB& box_first, const AABB& box_second)
{
    auto box_first_min = box_first.GetMin();
    auto box_first_max = box_first.GetMax();
    auto box_second_min = box_second.GetMin();
    auto box_second_max = box_second.GetMax();
    
    Vector min(
        std::min(box_first_min[0], box_second_min[0]),
        std::min(box_first_min[1], box_second_min[1]),
        std::min(box_first_min[2], box_second_min[2])
    );
    Vector max(
        std::max(box_first_max[0], box_second_max[0]),
        std::max(box_first_max[1], box_second_max[1]),
        std::max(box_first_max[2], box_second_max[2])
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
