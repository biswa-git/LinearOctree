#pragma once
#include <Vector.hpp>
#include <Vertex.hpp>
#include <Face.hpp>

class HalfEdge;
class Face;
class Edge
{
public:
    static Edge* New(Vertex*, Vertex*);
    ~Edge();
    Edge(Edge const&) = delete;
    Edge& operator=(Edge const&) = delete;
    void Flip();
    size_t GetId();
    Vertex* GetStart();
    Vertex* GetEnd();
    HalfEdge* GetHalfEdge(const size_t&);
    static void Legalize(Edge*);
    static Vector DistanceVector(Vertex*, Vertex*);
private:
    Edge(Vertex*, Vertex*);

    static size_t m_count;
    size_t m_id;

    Vertex* m_start;
    Vertex* m_end;

    HalfEdge* m_half_edge[2];
};

class HalfEdge
{
public:
    static HalfEdge* New(Edge*, Vertex*);
    ~HalfEdge() = default;
    HalfEdge(HalfEdge const&) = delete;
    HalfEdge& operator=(HalfEdge const&) = delete;
    Edge* GetParentEdge();
    Vertex* GetStart();
    Vertex* GetEnd();
    void SetNext(HalfEdge*);
    HalfEdge* GetNext();
    void SetFace(Face*);
    Face* GetFace();
    Vector GetEdgeVector();

private:
    HalfEdge(Edge*, Vertex*);
    Edge* m_parent;
    Vertex* m_start;
    Face* m_associated_Face;
    HalfEdge* m_next;
};
