#include<Face.hpp>

size_t Face::m_count = 0;

Face::Face() :m_area(0.0), m_is_orphaned_edge_remove_flag{ true }, m_id(0) 
{
}

Face::~Face()
{
}

void Face::SetOrphanedEdgeRemoveFlag(bool status)
{
	m_is_orphaned_edge_remove_flag = status;
}

TriFace* TriFace::New(Vertex* a, Vertex* b, Vertex* c, const Vector& normal, const size_t& id)
{
	return new TriFace(a, b, c, normal, id);
}

TriFace::~TriFace()
{
	for (size_t i = 0; i < 3; i++)
	{	
		auto parentEdge = m_half_edge[i]->GetParentEdge();
		m_half_edge[i]->SetNext(nullptr);
		m_half_edge[i]->SetFace(nullptr);
		if (m_is_orphaned_edge_remove_flag && parentEdge->GetHalfEdge(0)->GetFace() == nullptr && parentEdge->GetHalfEdge(1)->GetFace() == nullptr)
		{	
			//DELETE THE EDGE IF IT IS ORPHANED. i.e. NO ASSOCIATED WITH ANY FACE/FACES.
			delete parentEdge;
		}
	}
}

double TriFace::GetArea()
{
	return m_area;
}

Vector TriFace::GetCentroid()
{
    return m_centroid;
}

Vector TriFace::GetNormalVector()
{
	auto& half_edge = this->GetHalfEdge();
	return (half_edge[0]->GetEdgeVector() ^ half_edge[1]->GetEdgeVector()).Unit();
}

TriFace::TriFace(Vertex* a, Vertex* b, Vertex* c, const Vector& normal, const size_t& id = 0)
{
	m_id = id;
	m_half_edge.resize(3, nullptr);

	//	FIRST WE CREATE THREE EDGE / CHECK EXISTANCE

	Vertex* tempVertexArray[3]{ a,b,c };
	Edge* triEdge[3]{ nullptr,nullptr,nullptr };

	//CHECKING WHETHER EDGE EXIST BETWEEN Vertex
	for (size_t i = 0; i < 3; i++)
	{
		auto edgeList = tempVertexArray[i]->GetAssociatedEdge();
		for (auto associatedEdge : edgeList)
		{
			if (associatedEdge->GetEnd() == tempVertexArray[(i + 1) % 3] || associatedEdge->GetStart() == tempVertexArray[(i + 1) % 3])
			{
				triEdge[i] = associatedEdge;
				break;
			}
		}
		if (triEdge[i] == nullptr) triEdge[i] = Edge::New(tempVertexArray[i], tempVertexArray[(i + 1) % 3]);
	}

	for (size_t i = 0; i < 3; i++)
	{
		Vector directionVec(Edge::DistanceVector(triEdge[i]->GetHalfEdge(0)->GetEnd(), tempVertexArray[(i+2)%3]));

		if ((triEdge[i]->GetHalfEdge(0)->GetEdgeVector() ^ directionVec)*normal > 0.0)
		{
			m_half_edge[i] = triEdge[i]->GetHalfEdge(0);
		}
		else
		{
			m_half_edge[i] = triEdge[i]->GetHalfEdge(1);
		}
		m_half_edge[i]->SetFace(this);
	}

	if (m_half_edge[0]->GetEnd() == m_half_edge[1]->GetStart())
	{
		m_half_edge[0]->SetNext(m_half_edge[1]);
		m_half_edge[1]->SetNext(m_half_edge[2]);
		m_half_edge[2]->SetNext(m_half_edge[0]);
	}
	else
	{
		m_half_edge[0]->SetNext(m_half_edge[2]);
		m_half_edge[2]->SetNext(m_half_edge[1]);
		m_half_edge[1]->SetNext(m_half_edge[0]);
	}
	//AREA, CENTROID BEING A BASIC PROPERTY OF FACE, BEING CALCULATED IMMIDIATELY
	CalculateArea();

    //IF IT IS COLINEAR THEN IT IS NOT A VALID SURFACE. WE NEED TO STOP THAT.

    if (m_area < std::numeric_limits<double>::epsilon())
    {
        std::cout << "Warning:The points of the triangle wiht id=" << m_id << "are colinear!" << std::endl;
    }

    CalculateCentroid();
}

void TriFace::CalculateArea()
{
	Vector firstEdgeVector(Edge::DistanceVector(m_half_edge[0]->GetStart(), m_half_edge[0]->GetEnd()));
	Vector secondEdgeVector(Edge::DistanceVector(m_half_edge[1]->GetStart(), m_half_edge[1]->GetEnd()));
	m_area = 0.5*(firstEdgeVector ^ secondEdgeVector).Abs();
}

void TriFace::CalculateCentroid()
{
    m_centroid = ( m_half_edge[0]->GetStart()->GetPositionVector() +
                   m_half_edge[0]->GetStart()->GetPositionVector() +
                   m_half_edge[0]->GetStart()->GetPositionVector() ) / 3.0;
}

std::vector<HalfEdge*>& TriFace::GetHalfEdge()
{
	return m_half_edge;
}

std::vector<Vector> TriFace::GetVerticesVector()
{
	std::vector<Vector> result;
	for (auto it : m_half_edge)
	{
		result.emplace_back(it->GetStart()->GetPositionVector());
	}
	return result;
}

AABB TriFace::GetAABB()
{
    auto it = m_half_edge.begin();
    auto vertex = (*it)->GetStart();
    auto coord = vertex->GetPositionVector();
    Vector max_vector(coord);
    Vector min_vector(coord);
    
    it++;
    for (; it!=m_half_edge.end();++it)
    {
        vertex = (*it)->GetStart();
        coord = vertex->GetPositionVector();
        if (coord[0] < min_vector[0])
        {
            min_vector.SetDx(coord[0]);
        }

        if (coord[1] < min_vector[1])
        {
            min_vector.SetDy(coord[1]);
        }

        if (coord[2] < min_vector[2])
        {
            min_vector.SetDz(coord[2]);
        }

        if (coord[0] > max_vector[0])
        {
            max_vector.SetDx(coord[0]);
        }

        if (coord[1] > max_vector[1])
        {
            max_vector.SetDy(coord[1]);
        }

        if (coord[2] > max_vector[2])
        {
            max_vector.SetDz(coord[2]);
        }
    }

    return AABB(min_vector, max_vector);
}