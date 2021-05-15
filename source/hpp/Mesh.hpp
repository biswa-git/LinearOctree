#pragma once
#include<DataType.hpp>
#include<Geometry.hpp>
#include<Constants.hpp>
#include<list>

class Octant
{
	//friend class Mesh;
public:
	Octant(const size_t&, const size_t&, const size_t&, const int&);
	bool operator < (const Octant&) const;

//private:
	hash_int hash_value;
	coord_int x[3];
	int level;
};
class Mesh
{
public:
	Mesh(Geometry*);
	~Mesh();
	void Initialize();
	std::list<Octant>& GetOctantList();
	AABB GetAABB(const Octant&);
	void Mesh::Refine(const int&);
private:
	Geometry* m_geometry;
	AABB m_bounding_box;
	std::list<Octant> m_octants;
	hash_int m_start_hash_value;
	hash_int m_end_hash_value;
	size_t m_cell_num[3];
	double m_cell_size;
};