#include<Edge.hpp>
#include<vector>

size_t Edge::m_count = 0;

Edge* Edge::New(Vertex* start, Vertex* end)
{
	Edge* newEdge = new Edge(start, end);
	start->GetAssociatedEdge().insert(newEdge);
	end->GetAssociatedEdge().insert(newEdge);
	return newEdge;
}

Edge::~Edge()
{
	m_start->GetAssociatedEdge().erase(this);
	m_end->GetAssociatedEdge().erase(this);
	delete m_half_edge[0];
	delete m_half_edge[1];
}

Edge::Edge(Vertex* start, Vertex* end) :m_id(m_count++), m_start(start), m_end(end)
{
	m_half_edge[0] = HalfEdge::New(this, start);
	m_half_edge[1] = HalfEdge::New(this, end);
}

void Edge::Flip()
{
	Vertex* temp = m_start;
	m_start = m_end;
	m_end = temp;
}

size_t Edge::GetId()
{
	return m_id;
}

Vertex* Edge::GetStart()
{
	return m_start;
}

Vertex* Edge::GetEnd()
{
	return m_end;
}

HalfEdge* Edge::GetHalfEdge(const size_t& index)
{
	return m_half_edge[index];
}

void Edge::Legalize(Edge* E)
{
}

Vector Edge::DistanceVector(Vertex* start, Vertex* end)
{
    auto start_vector = start->GetPositionVector();
    auto end_vector = end->GetPositionVector();
    
    auto dx = end_vector.GetDx() - start_vector.GetDx();
	auto dy = end_vector.GetDy() - start_vector.GetDy();
	auto dz = end_vector.GetDz() - start_vector.GetDz();

	return Vector(dx, dy, dz);
}

HalfEdge* HalfEdge::New(Edge* e, Vertex* v)
{
	return new HalfEdge(e, v);
}

Edge* HalfEdge::GetParentEdge()
{
	return m_parent;
}

Vertex* HalfEdge::GetStart()
{
	return m_start;
}

Vertex* HalfEdge::GetEnd()
{
	if (m_start == m_parent->GetStart()) return m_parent->GetEnd();
	else return m_parent->GetStart();
}

void HalfEdge::SetNext(HalfEdge* half_edge)
{
	m_next = half_edge;
}

HalfEdge* HalfEdge::GetNext()
{
	return m_next;
}

void HalfEdge::SetFace(Face* f)
{
	m_associated_Face = f;
}

Face* HalfEdge::GetFace()
{
	return m_associated_Face;
}

Vector HalfEdge::GetEdgeVector()
{
	auto end = GetEnd();
	return Edge::DistanceVector(m_start, end);
}

HalfEdge::HalfEdge(Edge* e, Vertex* v) :m_parent(e), m_start(v), m_next(nullptr), m_associated_Face(nullptr)
{
}
