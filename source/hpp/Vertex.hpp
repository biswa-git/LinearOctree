#pragma once
#include<Preprocessor.hpp>
#include<set>
#include<Vector.hpp>

class Edge;
class Vertex
{
public:
    static Vertex* New(const double& = 0.0, const double& = 0.0, const double& = 0.0, const size_t & = 0 );
    virtual ~Vertex();
    Vertex(Vertex const&) = delete;
    Vertex& operator=(Vertex const&) = delete;

    void Reassign(const double& = 0.0, const double& = 0.0, const double& = 0.0);
    size_t GetId() const;
    Vector GetPositionVector() const;
    std::set<Edge*>& GetAssociatedEdge();
    void Print() const;
private:
    Vertex(const double& = 0.0, const double& = 0.0, const double& = 0.0, const size_t & = 0);

    static size_t m_count;
    size_t m_id;
    Vector m_coord;
    std::set<Edge*> m_associated_edge;
};
