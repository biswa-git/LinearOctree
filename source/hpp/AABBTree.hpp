#pragma once
#include<AABB.hpp>
#include<Face.hpp>
#include<queue>

struct AABBNode
{
    size_t id = -1;
    Face* face = nullptr;
    AABB bounding_box;
};

struct ConstructAABBTreeResult
{
    bool success = false;
};

class Face;
class AABBTree
{
public:
    AABBTree(const std::vector<Face*>&);
    ~AABBTree();
    std::vector<Face*> GetFaces(const AABB&);

private:
    std::vector<AABBNode> m_node_data;
    std::vector<Face*> m_leaf_face;

private://FUNCTION
    ConstructAABBTreeResult Construct(const std::vector<Face*>&);
};
