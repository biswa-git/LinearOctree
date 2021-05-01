#include<Mortonhasher.hpp>

Hasher::Hasher(const HasherParams& params) :m_params(params), m_level(0), m_octree_coord{ 0,0,0 }
{
}

Hasher::~Hasher()
{
}

void Hasher::SetLevel(const int& level)
{
    m_level = level;
}

void Hasher::SetCoord(const coord_int& x_coord, const coord_int& y_coord, const coord_int& z_coord)
{
    m_octree_coord[0] = x_coord;
    m_octree_coord[1] = y_coord;
    m_octree_coord[2] = z_coord;
}

hash_int Hasher::Get()
{
    auto x_b = DecimalToBinary<g_MaxLevel>(m_octree_coord[0]);
    auto y_b = DecimalToBinary<g_MaxLevel>(m_octree_coord[1]);
    auto z_b = DecimalToBinary<g_MaxLevel>(m_octree_coord[2]);

    std::bitset<g_BitsetHashSize> result_bitset(m_level);
    //INTERLACING
    for (size_t i = 0; i < g_BitsetCoordDataSize; i++)
    {
        result_bitset[g_BitsetLevelDataSize + 3*i + 0] = x_b[i];
        result_bitset[g_BitsetLevelDataSize + 3*i + 1] = y_b[i];
        result_bitset[g_BitsetLevelDataSize + 3*i + 2] = z_b[i];
    }
        return BinaryToDecimal<g_BitsetHashSize>(result_bitset);
}

template<hash_int T>
std::bitset<T> DecimalToBinary(const uint64_t& decimal)
{
    return std::bitset<T>(decimal);
}

template<hash_int T>
hash_int BinaryToDecimal(const std::bitset<T>& binary)
{
    return binary.to_ullong();
}
