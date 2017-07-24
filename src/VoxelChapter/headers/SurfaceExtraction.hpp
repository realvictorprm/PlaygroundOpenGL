#ifndef SURFACE_EXTRACTION_HPP
#define SURFACE_EXTRACTION_HPP
#include <vector>
#include <tuple>
#include <iostream>
#include <array>
#include <map>


namespace SurfaceExtraction {



    template<typename ScalarType = float, typename TransformType = float>
    struct VoxelData {
       /* static_assert(std::is_arithmetic<ScalarType>(), "A scalar can only be a number, so the first parameter must be an arithmetic type!");
        static_assert(std::is_floating_point<TransformType>(), "The transformation values can only be a floating number, so the second parameter must be a floating point type!");*/
        std::vector<ScalarType> data;
        size_t width, height, depth;
        TransformType dx, dy, dz, x0, y0, z0;
        
        static auto calcIndex(size_t x, size_t y, size_t z, size_t height, size_t depth) {
            /*auto t = std::make_tuple(1, 2, 3);
            auto&[a, b, c] = t;*/
            return x * height * depth + y * depth + z;
        }

    private:
        static std::tuple<std::vector<ScalarType>, size_t, size_t, size_t> makeVolume3D(const std::array<std::array<ScalarType, 3>, 3>& dims,
            std::function<ScalarType(ScalarType, ScalarType, ScalarType)> function) {

            const auto width = size_t(ScalarType(2) + std::ceil((dims[0][1] - dims[0][0]) / dims[0][2])),
                height = size_t(ScalarType(2) + std::ceil((dims[1][1] - dims[1][0]) / dims[1][2])),
                depth = size_t(ScalarType(2) + std::ceil((dims[2][1] - dims[2][0]) / dims[2][2]));
            std::vector<ScalarType> data;
            data.resize(width * height * depth);
            auto x = dims[0][0] - dims[0][2];
            auto y = dims[1][0] - dims[1][2];
            auto z = dims[2][0] - dims[2][2];
            for (size_t k = 0; k < (size_t)depth; k++) {
                y = dims[1][0] - dims[1][2];
                for (size_t j = 0; j < (size_t)height; j++) {
                    x = dims[0][0] - dims[0][2];
                    for (size_t i = 0; i < (size_t)width; i++) {
                        auto index = calcIndex(k, j, i, (size_t)height, (size_t)depth);
                        if (index > data.size())
                            std::printf("index out of range: %u", index);
                        data[index] = function(x, y, z);
                        x += dims[0][2];
                    }
                    y += dims[1][2];
                }
                z += dims[2][2];
            }
            return std::make_tuple(data, width, height, depth);
        }
    public:

        static auto createTorus(TransformType dx, TransformType dy, TransformType dz) {
            std::array<std::array<float, 3>, 3> data = { { { -2., 2., 0.2 },{ -2., 2., 0.2 },{ -1., 1., 0.1 } } };
            
            /*std::array<std::array<float, 3>, 3> data = { { { -1., 1., 0.25 },{ -1., 1., 0.25 },{ -1., 1., 0.25 } } };*/

            /*std::function<float(float, float, float)> function = [](float x, float y, float z) {
                return x * x + y * y + z * z - 1.0;
            };*/
            
            std::function<float(float, float, float)> function = [](float x, float y, float z) {
                return std::pow(1. - std::sqrt(x * x + y * y), 2.) + z * z - 0.25;
            };
            auto [res, width, height, depth] = makeVolume3D(
                data,
                function
            ); 
            VoxelData<float, TransformType> ret;
            ret.data = res;
            ret.width = width;
            ret.height = height;
            ret.depth = depth;
            ret.dx = dx;
            ret.dy = dy;
            ret.dz = dz;
            ret.x0 = (-(float)width / 2.) * dx;
            ret.y0 = (-(float)height / 2.) * dy;
            ret.z0 = (-(float)depth / 2.) * dz;
            return ret;
        }
    };

    template<typename T>
    struct Vertex {
        static_assert(std::is_floating_point<T>(), "Vertex inner type must be a floating point type!");
        T x;
        T y;
        T z;

        Vertex<T> operator - (Vertex<T>& v) {
            return Vertex<T>{ x - v.x, y - v.y, z - v.z};
        }
    };

    struct Interpolate {

        static auto createSurfaceNets(const VoxelData<float, float>& scalars, size_t gridResolution, float isovalue) {
            std::vector<float> vertices;
            std::vector<size_t> faces;
            std::map<std::tuple<size_t, size_t, size_t>, size_t> indicies;
            size_t xMax = scalars.width - 1, yMax = scalars.height - 1, zMax = scalars.depth - 1;
            auto cubeEdgesSurfacenets =
                []() {
                std::vector<std::tuple<int, int>> res;
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 3; j++) {
                        auto p = i ^ (1 << j);
                        if (i <= p) {
                            res.push_back({ i, p });
                        }
                    }
                }
                return res;
            }();

            auto edgeTable = [&cubeEdgesSurfacenets]() {
                std::array<int, 256> res;
                for (int i = 0; i < res.size(); i++) {
                    int mask = 0;
                    for (int j = 0; j < 12; j++) {
                        auto a = std::get<0>(cubeEdgesSurfacenets[j]);
                        auto b = std::get<1>(cubeEdgesSurfacenets[j]);
                        a = i & (1 << a);
                        b = i & (1 << b);
                        mask |= (bool)a != (bool)b ? (1 << j) : 0;
                    }
                    res[i] = mask;
                }
                return res;
            }();

            auto calcIndex = [&scalars](size_t x, size_t y, size_t z) {
                return VoxelData<float, float>::calcIndex(x, y, z, scalars.height, scalars.depth);
            };

            std::array<float, 3> offset = {
                scalars.x0,
                scalars.y0,
                scalars.z0
            };

            std::array<float, 3> gap = {
                scalars.dx,
                scalars.dy,
                scalars.dz
            };

            size_t bufferPos = 0;
            for (size_t x = 0; x < xMax; x++) {
                for (size_t y = 0; y < yMax; y++) {
                    for (size_t z = 0; z < zMax; z++) {
                        /*std::array<float, 8> block = {
                            scalars.data[calcIndex(x    , y    , z    )],
                            scalars.data[calcIndex(x    , y    , z + 1)],
                            scalars.data[calcIndex(x    , y + 1, z    )],
                            scalars.data[calcIndex(x    , y + 1, z + 1)],
                            scalars.data[calcIndex(x + 1, y    , z    )],
                            scalars.data[calcIndex(x + 1, y    , z + 1)],
                            scalars.data[calcIndex(x + 1, y + 1, z    )],
                            scalars.data[calcIndex(x + 1, y + 1, z + 1)]
                        };*/
                        std::array<float, 8> block = {
                            scalars.data[calcIndex(x    , y    , z)],
                            scalars.data[calcIndex(x + 1, y    , z)],
                            scalars.data[calcIndex(x    , y + 1, z)],
                            scalars.data[calcIndex(x + 1, y + 1, z)],
                            scalars.data[calcIndex(x    , y    , z + 1)],
                            scalars.data[calcIndex(x + 1, y    , z + 1)],
                            scalars.data[calcIndex(x    , y + 1, z + 1)],
                            scalars.data[calcIndex(x + 1, y + 1, z + 1)]
                        };
                        auto calcMask = [&block, &isovalue]() {
                            unsigned int mask = 0;
                            for (unsigned int i = 0; i < block.size(); i++)
                                if (block[i] < isovalue)
                                    mask |= (1 << i);
                            return mask;
                        };

                        auto mask = calcMask();
                        if (mask != 0x00 && mask != 0xff) {
                            auto edge_mask = edgeTable[mask];
                            unsigned int edgeCount = 0;
                            std::array<float, 3> vertex = { 0., 0., 0. };
                            // interpolate vertices
                            for (unsigned int i = 0; i < 12; i++) {
                                // Only interpolate vertices if there is an intersection (checked through the mask)
                                if (edge_mask & (1 << i)) {
                                    auto firstVertexIndex = std::get<0>(cubeEdgesSurfacenets[i]),
                                        secondVertexIndex = std::get<1>(cubeEdgesSurfacenets[i]);
                                    auto weightZero = block[firstVertexIndex], weightOne = block[secondVertexIndex];
                                    auto diff = weightZero - weightOne;
                                    // Skipt interpolation if difference is too small
                                    auto t = weightZero / diff;
                                    for (unsigned int j = 0; j < 3; j++) {
                                        auto k = (1 << j);
                                        auto a = k & firstVertexIndex, b = k & secondVertexIndex;
                                        auto res =
                                            a != b ? t :
                                            (a ? 1. : 0.);
                                        vertex[j] += res;
                                    }
                                    edgeCount++;
                                }
                            }
                            auto factor = 1.0 / (float)edgeCount;
                            size_t c[]{ x, y, z };
                            for (unsigned int j = 0; j < 3; j++) {
                                // Translate global, adjust gap between each vertex and normalize their interpolated value.
                                vertex[j] = (float)c[j] + vertex[j] * factor;
                                vertex[j] *= gap[j];
                                vertex[j] += offset[j];
                            }
                            indicies[{ x, y, z}] = vertices.size() / 3;
                            vertices.push_back(vertex[0]);
                            vertices.push_back(vertex[1]);
                            vertices.push_back(vertex[2]);

                            if ((bool)(edge_mask & 1) && (z != 0 && y != 0)) {
                                if (mask & 0x01) {
                                    auto v0 = indicies[{ x, y, z }],
                                        v1 = indicies[{ x, y, z - 1}],
                                        v2 = indicies[{ x, y - 1, z - 1}],
                                        v3 = indicies[{ x, y - 1, z}];
                                    faces.push_back(v0);
                                    faces.push_back(v1);
                                    faces.push_back(v2);
                                    faces.push_back(v3);
                                }
                                else {
                                    auto v0 = indicies[{ x, y, z }],
                                        v1 = indicies[{ x, y - 1, z}],
                                        v2 = indicies[{ x, y - 1, z - 1}],
                                        v3 = indicies[{ x, y, z - 1}];
                                    faces.push_back(v0);
                                    faces.push_back(v1);
                                    faces.push_back(v2);
                                    faces.push_back(v3);
                                }
                            }
                            if ((bool)(edge_mask & 2) && (x != 0 && z != 0)) {
                                if (mask & 0x01) {
                                    auto v0 = indicies[{ x, y, z }],
                                        v1 = indicies[{ x - 1, y, z }],
                                        v2 = indicies[{ x - 1, y, z - 1 }],
                                        v3 = indicies[{ x, y, z - 1}];
                                    faces.push_back(v0);
                                    faces.push_back(v1);
                                    faces.push_back(v2);
                                    faces.push_back(v3);
                                }
                                else {
                                    auto v0 = indicies[{ x, y, z }],
                                        v1 = indicies[{ x, y, z - 1 }],
                                        v2 = indicies[{ x - 1, y, z - 1 }],
                                        v3 = indicies[{ x - 1, y, z}];
                                    faces.push_back(v0);
                                    faces.push_back(v1);
                                    faces.push_back(v2);
                                    faces.push_back(v3);
                                }
                            }
                            if ((bool)(edge_mask & 4) && (y != 0 && x != 0)) {
                                if (mask & 0x01) {
                                    auto v0 = indicies[{ x, y, z }],
                                        v1 = indicies[{ x, y - 1, z }],
                                        v2 = indicies[{ x - 1, y - 1, z }],
                                        v3 = indicies[{ x - 1, y, z}];
                                    faces.push_back(v0);
                                    faces.push_back(v1);
                                    faces.push_back(v2);
                                    faces.push_back(v3);
                                }
                                else {
                                    auto v0 = indicies[{ x, y, z }],
                                        v1 = indicies[{ x - 1, y, z }],
                                        v2 = indicies[{ x - 1, y - 1, z }],
                                        v3 = indicies[{ x, y - 1, z}];
                                    faces.push_back(v0);
                                    faces.push_back(v1);
                                    faces.push_back(v2);
                                    faces.push_back(v3);
                                }
                            }
                        }
                    }
                }
            }
            return std::make_tuple(vertices, faces);
        };
    };
}

#endif