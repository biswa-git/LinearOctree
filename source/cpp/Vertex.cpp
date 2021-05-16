#include<Vertex.hpp>

size_t Vertex::m_count = 0;

Vertex::Vertex(const double& x, const double& y, const double& z, const size_t& id) : m_coord(Vector(x,y,z)), m_id(id)
{
}

Vertex* Vertex::New(const double& x, const double& y, const double& z, const size_t& id)
{
    return new Vertex(x, y, z, id);
}

Vertex::~Vertex()
{
}

void Vertex::Reassign(const double& x, const double& y, const double& z)
{
    m_coord.Reassign(x, y, z);
}

size_t Vertex::GetId() const
{
	return m_id;
}

Vector Vertex::GetPositionVector() const
{
    return m_coord;
}

std::set<Edge*>& Vertex::GetAssociatedEdge()
{
	return m_associated_edge;
}

void Vertex::Print() const
{
	std::cout << "id:" << m_id << " [" << m_coord[0] << "," << m_coord[1] << "," << m_coord[2] << "]" << std::endl;
}
