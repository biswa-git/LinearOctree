#pragma once
#include<Mesh.hpp>
#include<MortonHasher.hpp>
#include<IntersectionTool.hpp>
#include<AABBTree.hpp>

Octant::Octant(const coord_int& x, const coord_int& y, const coord_int& z, const int& level)
{
    this->x[0] = x;
    this->x[1] = y;
    this->x[2] = z;
    this->level = level;

    HasherParams params;
    Hasher hash(params);
    hash.SetLevel(level);
    hash.SetCoord(this->x[0], this->x[1], this->x[2]);

    this->hash_value = hash.Get();
}

bool Octant::operator < (const Octant& c) const
{
    return this->hash_value < c.hash_value;
}

Mesh::Mesh(Geometry* geometry) :m_geometry(geometry)
{
}

Mesh::~Mesh()
{
}

void Mesh::Initialize()
{
    int max_dir = 0;

    auto geometry_AABB = m_geometry->GetAABB();
    auto size = geometry_AABB.GetMax() - geometry_AABB.GetMin();

    if (size[0] < size[1])
    {
        if (size[1] < size[2])
        {
            max_dir = 2;
        }
        else
        {
            max_dir = 1;
        }
    }
    else
    {
        if (size[0] < size[2])
        {
            max_dir = 2;
        }
        else
        {
            max_dir = 0;
        }
    }

    m_cell_size = size[max_dir] / 8.0;

    for (int i = 0; i < 3; ++i)
    {
        m_cell_num[i] = static_cast<size_t>(size[i] / m_cell_size);
        if (i != max_dir)
        {
            ++m_cell_num[i];
        }
    }

    Vector cell_diagon(m_cell_size * m_cell_num[0], m_cell_size * m_cell_num[1], m_cell_size * m_cell_num[2]);

    auto geometry_center = (geometry_AABB.GetMax() + geometry_AABB.GetMin()) * 0.5;
    auto cell_bounding_box_min = geometry_center - (cell_diagon * 0.5);
    auto cell_bounding_box_max = geometry_center + (cell_diagon * 0.5);

    m_bounding_box.Assign(cell_bounding_box_min, cell_bounding_box_max);

    HasherParams params;
    Hasher hash(params);

    std::set<Octant> octants_set;
    auto octant_coord_size = static_cast<coord_int>(pow(2, g_MaxLevel));
    for (coord_int i = 0; i < m_cell_num[0]; i++)
    {
        for (coord_int j = 0; j < m_cell_num[1]; j++)
        {
            for (coord_int k = 0; k < m_cell_num[2]; k++)
            {
                Octant octant(i * octant_coord_size, j * octant_coord_size, k * octant_coord_size, 0);
                octants_set.emplace(octant);
            }
        }
    }

    for (auto octant : octants_set)
    {
        m_octants.emplace_back(octant);
    }
}

std::list<Octant>& Mesh::GetOctantList()
{
    return m_octants;
}

AABB Mesh::GetAABB(const Octant& octant)
{
    auto min_cell_size = m_cell_size / pow(2, g_MaxLevel);
    Vector min(
        this->m_bounding_box.GetMin()[0] + octant.x[0] * min_cell_size,
        this->m_bounding_box.GetMin()[1] + octant.x[1] * min_cell_size,
        this->m_bounding_box.GetMin()[2] + octant.x[2] * min_cell_size);
    Vector max(
        this->m_bounding_box.GetMin()[0] + (octant.x[0] + pow(2, g_MaxLevel - octant.level)) * min_cell_size,
        this->m_bounding_box.GetMin()[1] + (octant.x[1] + pow(2, g_MaxLevel - octant.level)) * min_cell_size,
        this->m_bounding_box.GetMin()[2] + (octant.x[2] + pow(2, g_MaxLevel - octant.level)) * min_cell_size
    );

    return AABB(min, max);
}

void Mesh::Refine(const int& level)
{

    auto faces = m_geometry->GetFaceList();
    AABBTree aabb_tree(faces);

    int current_level = 0;
    while (current_level < level)
    {
        std::cout << "in level:" << current_level << " cell count: " << m_octants.size()<<std::endl;
        for (auto& octant : m_octants)
        {
            if (octant.level == current_level)
            {
                auto& octant_aabb = GetAABB(octant);
                auto intsct = IntersectionTool::IsIntersect(octant_aabb, aabb_tree.GetFaces(octant_aabb));
                if (intsct)
                {
                    coord_int length = static_cast<coord_int>(pow(2, g_MaxLevel - current_level - 1));
                    Octant oc1(octant.x[0], octant.x[1], octant.x[2], current_level + 1);
                    Octant oc2(octant.x[0], octant.x[1], octant.x[2] + length, current_level + 1);
                    Octant oc3(octant.x[0], octant.x[1] + length, octant.x[2], current_level + 1);
                    Octant oc4(octant.x[0], octant.x[1] + length, octant.x[2] + length, current_level + 1);
                    Octant oc5(octant.x[0] + length, octant.x[1], octant.x[2], current_level + 1);
                    Octant oc6(octant.x[0] + length, octant.x[1], octant.x[2] + length, current_level + 1);
                    Octant oc7(octant.x[0] + length, octant.x[1] + length, octant.x[2], current_level + 1);
                    Octant oc8(octant.x[0] + length, octant.x[1] + length, octant.x[2] + length, current_level + 1);
                    m_octants.push_back(oc1);
                    m_octants.push_back(oc2);
                    m_octants.push_back(oc3);
                    m_octants.push_back(oc4);
                    m_octants.push_back(oc5);
                    m_octants.push_back(oc6);
                    m_octants.push_back(oc7);
                    m_octants.push_back(oc8);
                }
            }
        }
        ++current_level;
    }
}