#include<Geometry.hpp>
#include<AABB.hpp>
#include<Stl.hpp>
#include<iostream>

Geometry::Geometry() :m_is_read(false), m_is_bounding_box(false)
{

}

Geometry::~Geometry()
{
    /*
    if (!m_face_list.empty())
    {
        for (auto it : m_face_list)
        {
            FREE_OBJ_MACRO(*it);
        }
    }
    if (!m_vertex_list.empty())
    {
        for (auto it : m_vertex_list)
        {
            FREE_OBJ_MACRO(it);
        }
    }
    */
}

GeometryResult Geometry::Read(const std::string& file_name)
{
    GeometryResult result;
    // reading the mesh
    if (!m_is_read)
    {
        try {
            stl_reader::StlMesh <float, unsigned int> mesh(file_name.c_str());

            size_t vertNum = 0;
            for (size_t i = 0; i < mesh.num_vrts(); i++)
            {
                auto c = mesh.vrt_coords(i);

                ++vertNum;
                m_vertex_list.emplace_back(Vertex::New(c[0], c[1], c[2], vertNum));
            }

            size_t faceNum = 0;
            for (size_t i = 0; i < mesh.num_tris(); i++)
            {
                auto t = mesh.tri_corner_inds(i);
                auto n = mesh.tri_normal(i);
                Vector normal(n[0], n[1], n[2]);
                ++faceNum;
                auto new_face = TriFace::New(m_vertex_list[t[0]], m_vertex_list[t[1]], m_vertex_list[t[2]], normal, faceNum);
                m_face_list.push_back(new_face);
            }

            //CALCULATING AABB
            CalculateBoundingBox();

            result.success = true;
        }
        catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        m_is_read = true;
    }
    else
    {
        result.error = GEOMETRY_ALREADY_READ;
    }
    return result;
}

AABB Geometry::GetAABB()
{
    return m_bounding_box;
}

GeometryResult Geometry::CalculateBoundingBox()
{
    GeometryResult result;
    
    if (!m_is_bounding_box)
    {
        m_bounding_box = AABB::GetAABB(m_face_list);

        m_is_bounding_box = true;
        result.success = true;
    }
    else
    {
        result.error = GEOMETRY_BOUNDING_BOX_PRESENT;
    }

    return result;
}

GeometryResult Geometry::Write(const std::string& file_location, const std::string& file_name)
{
    GeometryResult result;

    std::ofstream myfile;
    auto file = file_location + "/" + file_name + ".dat";
    myfile.open(file);
    myfile << "TITLE = \"title\"\n";
    myfile << "VARIABLES = \"X\", \"Y\", \"Z\"\n";
    myfile << "ZONE T = \"Rampant\", N = " << m_vertex_list.size() << ", E = " << m_face_list.size() << ", DATAPACKING=POINT, ZONETYPE=FETRIANGLE\n";

    for (auto it : m_vertex_list)
    {
        auto coord = it->GetPositionVector();
        myfile << coord[0] << " " << coord[1] << " " << coord[2] << "\n";
    }

    for (auto it : m_face_list)
    {
        myfile << it->GetHalfEdge()[0]->GetStart()->GetId() << " " << it->GetHalfEdge()[1]->GetStart()->GetId() << " " << it->GetHalfEdge()[2]->GetStart()->GetId() << "\n";
    }
    
    myfile.close();

    result.success = true;
    return result;
}

std::vector<Face*>& Geometry::GetFaceList()
{
    return m_face_list;
}