#include<iostream>
#include<Mortonhasher.hpp>
#include<Geometry.hpp>
#include<set>
#include<iostream>
#include<AABBTree.hpp>
#include<chrono>
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


    Geometry geometry;
    geometry.Read("C:/Users/bghosh/Downloads/bugatti.stl");
    geometry.Write("C:/Users/bugatti/Downloads", "bugatti");

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


    AABB bbox = geometry.GetFaceList().at(86023)->GetAABB();
    double e = 0.03;
    bbox.Assign(
        Vector(1.2917913198471069 - e, 1.5888619422912598 - e, -0.34591406583786011 - e), 
        Vector(1.2962168455123901 + e, 1.5888659954071045 + e, -0.34394556283950806 + e)
    );


    start = clock.now();
    for (int i = 0; i < 1000; ++i)
    {
        auto result = tree.GetFaces(bbox);
    }
    end = clock.now();
    std::cout << "time taken tree: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    //auto res_bbox = AABB::GetAABB(result);

    auto& faces = geometry.GetFaceList();

    start = clock.now();
    for (int i = 0; i < 1000; ++i) 
    {
        std::vector<Face*> fl;
        for (size_t i = 0; i < faces.size(); i++)
        {
            auto& face = faces[i];
            if (AABB::IsIntersect(face->GetAABB(), bbox))
            {
                fl.emplace_back(face);
            }
        }
    }

    end = clock.now();
    std::cout << "time taken loop: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    
    return 0;
}