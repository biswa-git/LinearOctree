#pragma once

#include<Face.hpp>

#include<string>
#include<set>
#include <algorithm>
#include <exception>
#include <fstream>
#include <sstream>
#include <vector>

#ifdef STL_READER_NO_EXCEPTIONS
#define STL_READER_THROW(msg) return false;
#define STL_READER_COND_THROW(cond, msg) if(cond) return false;
#else
/// Throws an std::runtime_error with the given message.
#define STL_READER_THROW(msg) {std::stringstream ss; ss << msg; throw(std::runtime_error(ss.str()));}

/// Throws an std::runtime_error with the given message, if the given condition evaluates to true.
#define STL_READER_COND_THROW(cond, msg)  if(cond){std::stringstream ss; ss << msg; throw(std::runtime_error(ss.str()));}
#endif


enum error
{
    GEOMETRY_NO_ERROR = 0,
    GEOMETRY_ALREADY_READ,
    GEOMETRY_BOUNDING_BOX_PRESENT
};

struct GeometryResult
{
	bool success = false;
    int error = GEOMETRY_NO_ERROR;
};

class Geometry
{
public:
	Geometry();
	~Geometry();
    GeometryResult Read(const std::string& file_name);
    GeometryResult Write(const std::string& file_location, const std::string& file_name);
    std::vector<Face*>& GetFaceList();
    AABB GetAABB();
private:
    bool m_is_read;
    bool m_is_bounding_box;
    AABB m_bounding_box;

    std::vector<Vertex*> m_vertex_list;
    std::vector<Face*> m_face_list;

private:
    GeometryResult CalculateBoundingBox();
};
