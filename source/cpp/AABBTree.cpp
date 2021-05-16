#pragma once
#include<AABBTree.hpp>

AABBTree::AABBTree(const std::vector<Face*>& faces)
{
    Construct(faces);
}

AABBTree::~AABBTree()
{

}

std::vector<Face*> AABBTree::GetFaces(const AABB& query_box)
{
    std::vector<Face*> result;
    std::queue<AABBNode> nodes;
    
    nodes.emplace(m_node_data[0]);

    while (!nodes.empty())
    {
        if (AABB::IsIntersect(query_box, nodes.front().bounding_box))
        {
            if (nodes.front().face != nullptr)
            {
                result.emplace_back(nodes.front().face);
            }
            else
            {
                if (nodes.front().id * 2 + 1 < m_node_data.size())
                {
                    nodes.emplace(m_node_data[nodes.front().id * 2 + 1]);
                }

                if (nodes.front().id * 2 + 2 < m_node_data.size())
                {
                    nodes.emplace(m_node_data[nodes.front().id * 2 + 2]);
                }
            }
        }

        nodes.pop();
    }

    return result;
}

ConstructAABBTreeResult AABBTree::Construct(const std::vector<Face*>& face_vec)
{
    ConstructAABBTreeResult result;

    auto m_max_level = static_cast<size_t>(std::floor(std::log2(face_vec.size())) + 1);
    m_node_data.reserve(static_cast<size_t>(std::pow(2, m_max_level) - 1));
    
    size_t id = 0;
    size_t level = 0;
    size_t node_count_p_level = 0;
    size_t max_node_count_at_p_level = 1;

    std::queue<std::vector<Face*>> face_queue;
    face_queue.emplace(face_vec);
    AABBNode node;

    bool continue_flag = true;
    if (!face_queue.empty())
    {
        while (continue_flag)
        {
            AABBNode node;
            auto& faces = face_queue.front();
            node.bounding_box = AABB::GetAABB(faces);
            node.id = id++;

            //bug: add in last level only
            if (faces.size() == 1 && level == m_max_level)
            {
                node.face = faces[0];
            }
            else
            {
                node.face = nullptr;
            }
            m_node_data.emplace_back(node);
            if (faces.size() > 1)
            {
                // BRANCHING AABB TREE
                auto dir = level % 3;
                if (dir == 0) std::sort(faces.begin(), faces.end(), [](Face* a, Face* b) { return a->GetCentroid()[0] > b->GetCentroid()[0]; });
                if (dir == 1) std::sort(faces.begin(), faces.end(), [](Face* a, Face* b) { return a->GetCentroid()[1] > b->GetCentroid()[1]; });
                if (dir == 2) std::sort(faces.begin(), faces.end(), [](Face* a, Face* b) { return a->GetCentroid()[2] > b->GetCentroid()[2]; });

                std::vector<Face*> left;
                std::vector<Face*> right;

                auto half_size = faces.size() / 2;
                if (faces.size() % 2 == 1) ++half_size;
                std::vector<Face*>::iterator middleItr(faces.begin() + half_size);

                for (auto it = faces.begin(); it != middleItr; ++it)
                {
                    left.push_back(*it);
                }
                for (auto it = middleItr; it != faces.end(); ++it)
                {
                    right.push_back(*it);
                }

                face_queue.emplace(left);
                face_queue.emplace(right);
                face_queue.pop();
            }
            else
            {
                if (level != m_max_level)
                {
                    std::vector<Face*> dummy_face;
                    face_queue.emplace(faces);
                    face_queue.emplace(dummy_face);
                }
                face_queue.pop();
            }

            //LEVEL TRACK
            if (++node_count_p_level == max_node_count_at_p_level)
            {
                node_count_p_level = 0;
                max_node_count_at_p_level *= 2;

                if (++level > m_max_level)
                {
                    continue_flag = false;
                }
            }
        }
    }
    
    result.success = true;
    return result;
}