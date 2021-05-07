#pragma once
#include<Edge.hpp>
#include<AABB.hpp>
#include<vector>

class HalfEdge;
class AABB;
class Face
{
public:
    Face();
    virtual ~Face();
    Face(Face const&) = delete;
    Face& operator=(Face const&) = delete;
    virtual double GetArea() = 0;
    virtual Vector GetCentroid() = 0;
    virtual Vector GetNormalVector() = 0;
    virtual void SetOrphanedEdgeRemoveFlag(bool);
    virtual std::vector<HalfEdge*>& GetHalfEdge() = 0;
    virtual std::vector<Vector> GetVerticesVector() = 0;
    virtual AABB GetAABB() = 0;

protected:
    virtual void CalculateArea() = 0;
    static size_t m_count;
    double m_area;
    Vector m_centroid;
    bool m_is_orphaned_edge_remove_flag;
    std::vector<HalfEdge*> m_half_edge;
    size_t m_id;
};

class TriFace :public Face
{
public:
    static TriFace* New(Vertex*, Vertex*, Vertex*, const Vector& normal, const size_t&);
    ~TriFace();
    virtual double GetArea();
    virtual Vector GetCentroid();
    virtual Vector GetNormalVector();
    virtual std::vector<HalfEdge*>& GetHalfEdge();
    virtual std::vector<Vector> GetVerticesVector();
    virtual AABB GetAABB();

protected:
    virtual void CalculateArea();
    virtual void CalculateCentroid();

private:
    TriFace(Vertex*, Vertex*, Vertex*, const Vector& normal,const size_t&);
};
