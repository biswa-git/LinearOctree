#include<iostream>
#include<Mortonhasher.hpp>
#include<Geometry.hpp>
#include<set>
#include<iostream>
#include<AABBTree.hpp>
#include<IntersectionTool.hpp>
#include<chrono>


void printbbox(std::ofstream& file, AABB& bbox)
{
    auto min = bbox.GetMin();
    auto max = bbox.GetMax();

    file << min[0] << " " << min[1] << " " << min[2] << "\n";
    file << max[0] << " " << min[1] << " " << min[2] << "\n";
    file << max[0] << " " << max[1] << " " << min[2] << "\n";
    file << min[0] << " " << max[1] << " " << min[2] << "\n";
    file << min[0] << " " << min[1] << " " << max[2] << "\n";
    file << max[0] << " " << min[1] << " " << max[2] << "\n";
    file << max[0] << " " << max[1] << " " << max[2] << "\n";
    file << min[0] << " " << max[1] << " " << max[2] << "\n";
}

int main()
{
    auto v = NULL_VECTOR;
    HasherParams params;
    Hasher hash(params);
    //hash_int in = 786;
    //auto bin = hash.DecimalToBinary(in);
    //auto dec = hash.BinaryToDecimal(bin);

    hash.SetLevel(0);
    /*
    hash.SetCoord(4,2,0);
    auto ans = hash.Get();
    std::cout << ans << "\n";
    */

    std::string file_location = "C:/Users/MegaMind/Downloads/model/";
    std::string file_name = "CERF_Free_Triangulate.stl";

    Geometry geometry;
    geometry.Read(file_location + file_name);
    geometry.Write("E:/LinearOctree/output", "CERF_Free_Triangulate");

    /*
    std::ofstream myfile;
    myfile.open("test.dat");
    myfile << "TITLE = \"Example: Simple 3D Line\"" << std::endl;
    myfile << "VARIABLES = \"X\", \"Y\", \"Z\", \"T\"" << std::endl;
    myfile << "ZONE I = " << clist.size() << ", J = 1, K = 1, DATAPACKING = POINT" << std::endl;

    int num = 0;
    for (auto it = clist.begin(); it != clist.end(); ++it)
    {
        myfile << (*it).c[0] << " " << (*it).c[1] << " " << (*it).c[2] << " " << ++num << "\n";
    }
    */
    std::chrono::high_resolution_clock clock;
    std::cout << "start\n";
    auto start = clock.now();
    AABBTree tree(geometry.GetFaceList());
    auto end = clock.now();
    std::cout << "time taken tree: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    std::cout << "end\n";


    AABB bbox = geometry.GetFaceList().at(5)->GetAABB();
    double e = 20, a=1.0;
    bbox.Assign(
        Vector(a + 15.103 - e, a + 57.819 - e, a + 75.024 - e),
        Vector(a + 15.103 + e, a + 57.819 + e, a + 75.024 + e)
    );

    start = clock.now();
    //for (int i = 0; i < 1000; ++i)
    //{
        auto result = tree.GetFaces(bbox);
        std::vector<bool> res;
        for (size_t i = 0; i < result.size(); i++)
        {
            res.emplace_back(IntersectionTool::IsIntersect(bbox, result[i]));
        }

        std::ofstream myfile;
        auto file = file_location + "/" + "temp_" + ".dat";
        myfile.open(file);
        myfile << "TITLE = \"title\"\n";
        myfile << "VARIABLES = \"X\", \"Y\", \"Z\"\n";
        myfile << "ZONE T = \"triangle\", N = " << result.size()*3 << ", E = " << result.size() << ", DATAPACKING=POINT, ZONETYPE=FETRIANGLE\n";

        for (auto it = result.begin(); it != result.end(); it++)
        {
            auto he = (*it)->GetHalfEdge();
            for (auto i = 0; i < 3; ++i)
            {
                auto coord = he[i]->GetStart()->GetPositionVector();
                myfile << coord.GetDx() << " " << coord.GetDy() << " " << coord.GetDz() << "\n";
            }
        }

        auto ids = 0;
        for (auto it = result.begin(); it != result.end(); it++)
        {
            myfile << ids+1 << " " << ids+2 << " " << ids+3 << "\n";
            ids += 3;
        }
        result.clear();
        myfile << "ZONE T = \"bbox\", N = " << (result.size() + 1) * 8 << ", E = " << 6*(result.size() + 1)<< ", DATAPACKING=POINT, ZONETYPE=FEQUADRILATERAL\n";
        for (auto it : result)
        {
            printbbox(myfile, it->GetAABB());
        }
        printbbox(myfile, bbox);
        ids = 0;
        for (auto it : result)
        {
            myfile << ids + 1 << " " << ids + 2 << " " << ids + 3 << " " << ids + 4 << "\n";
            myfile << ids + 5 << " " << ids + 6 << " " << ids + 7 << " " << ids + 8 << "\n";
            myfile << ids + 4 << " " << ids + 1 << " " << ids + 5 << " " << ids + 8 << "\n";
            myfile << ids + 1 << " " << ids + 2 << " " << ids + 6 << " " << ids + 5 << "\n";
            myfile << ids + 3 << " " << ids + 2 << " " << ids + 6 << " " << ids + 7 << "\n";
            myfile << ids + 4 << " " << ids + 3 << " " << ids + 7 << " " << ids + 8 << "\n";

            ids += 8;
        }

        myfile << ids + 1 << " " << ids + 2 << " " << ids + 3 << " " << ids + 4 << "\n";
        myfile << ids + 5 << " " << ids + 6 << " " << ids + 7 << " " << ids + 8 << "\n";
        myfile << ids + 4 << " " << ids + 1 << " " << ids + 5 << " " << ids + 8 << "\n";
        myfile << ids + 1 << " " << ids + 2 << " " << ids + 6 << " " << ids + 5 << "\n";
        myfile << ids + 3 << " " << ids + 2 << " " << ids + 6 << " " << ids + 7 << "\n";
        myfile << ids + 4 << " " << ids + 3 << " " << ids + 7 << " " << ids + 8 << "\n"; 
        
        
        myfile.close();











    //}
    end = clock.now();
    std::cout << "time taken tree: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    //auto res_bbox = AABB::GetAABB(result);

    auto& faces = geometry.GetFaceList();

    start = clock.now();
    //for (int i = 0; i < 1000; ++i) 
    //{
        std::vector<Face*> fl;
        for (size_t i = 0; i < faces.size(); i++)
        {
            auto& face = faces[i];
            if (AABB::IsIntersect(face->GetAABB(), bbox))
            {
                fl.emplace_back(face);
            }
        }
    //}

    end = clock.now();
    std::cout << "time taken loop: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    
    return 0;
}