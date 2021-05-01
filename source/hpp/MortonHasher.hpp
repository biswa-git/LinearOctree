#include<bitset>
#include "DataType.hpp"
#include "Constants.hpp"

struct HasherParams
{
};

class Hasher
{
public:
    Hasher(const HasherParams& params);
    ~Hasher();
    void SetLevel(const int& level);
    void SetCoord(const coord_int& x_coord, const coord_int& y_coord, const coord_int& z_coord);
    hash_int Get();
private:
    HasherParams m_params;
    int m_level;
    coord_int m_octree_coord[3];
};

template<hash_int T>
std::bitset <T> DecimalToBinary(const uint64_t& binary);

template<hash_int T>
hash_int BinaryToDecimal(const std::bitset <T>& binary);
