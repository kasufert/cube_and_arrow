#pragma once
#include "ShapeGenerator.hpp"

ShapeData ShapeGenerator::makeTriangle()
{
    ShapeData tri;
    if (tri.numVerts == 0)
    {
        fmt::print("Hi!\n");
    }
    Vertex myTri[] =
    {
        glm::vec3(-1.0, 1.0,  0.0), red, noTex,
        glm::vec3(-0.8,  1.0,  0.0), green, noTex,
        glm::vec3(-1.0, 0.0, 0.0), blue, noTex
    };
    tri.numVerts = NUM_ELEMS(myTri);
    tri.verts = new Vertex[tri.numVerts];
    fmt::print("Heap allocated vertex array\n");
    memcpy_s(tri.verts, tri.vertsSize(), myTri, sizeof(myTri));

    GLushort indices[] = { 0, 1, 2 };
    tri.numIndices = NUM_ELEMS(indices);
    tri.indices = new GLushort[tri.numIndices];
    fmt::print("Heap allocated index array\n");

    memcpy_s(tri.indices, tri.indsSize(), indices, sizeof(indices));

    return tri;
}

ShapeData ShapeGenerator::makeCube()
{
    using glm::vec2, glm::vec3, glm::vec4;
    ShapeData cube;
    vec2 noTex(0.0, 0.0);
    Vertex myCube[] =
    {
        vec3(-1.0, -1.0, -1.0), red,    noTex,// CBL - 0
        vec3(+1.0, -1.0, -1.0), green,  noTex,// CBR - 1
        vec3(-1.0, +1.0, -1.0), blue,   noTex,// CTL
        vec3(+1.0, +1.0, -1.0), cyan,    noTex,// CTR
        vec3(-1.0, -1.0, +1.0), yellow,  noTex,// FBL
        vec3(+1.0, -1.0, +1.0), magenta,   noTex,// FBR
        vec3(-1.0, +1.0, +1.0), black,    noTex,// FTL
        vec3(+1.0, +1.0, +1.0), white,  noTex // FTR
    };
    cube.numVerts = NUM_ELEMS(myCube);
    cube.verts = new Vertex[cube.numVerts];
    memcpy_s(cube.verts, cube.vertsSize(), myCube, sizeof(myCube));

    GLushort indices[] =
    {
        0, 1, 2,
        1, 2, 3,
        1, 5, 3,
        3, 5, 7,
        2, 3, 6,
        3, 7, 6,
        0, 2, 4,
        2, 6, 4,
        0, 4, 1,
        1, 5, 4,
        4, 6, 5,
        5, 6, 7
    };
    cube.numIndices = NUM_ELEMS(indices);
    cube.indices = new GLushort[cube.numIndices];
    memcpy_s(cube.indices, cube.indsSize(), indices, sizeof(indices));

    return cube;
}

ShapeData ShapeGenerator::makeArrow()
{
    ShapeData arrow;
    using glm::vec2, glm::vec3, glm::vec4;
    Vertex verts[] =
    {
        vec3(+0.0, +1.0,  0.0) ,red, noTex,// NT  - 0
        vec3(+0.3, +0.5,  0.0) ,red, noTex,// NRH - 1
        vec3(+0.1, +0.5,  0.0) ,red, noTex,// NRA - 2
        vec3(+0.1, -1.0,  0.0) ,red, noTex,// NRF - 3
        vec3(-0.1, -1.0,  0.0) ,red, noTex,// NLF - 4
        vec3(-0.1, +0.5,  0.0) ,red, noTex,// NLA - 5
        vec3(-0.3, +0.5,  0.0) ,red, noTex,// NLH - 6
        vec3(+0.0, +1.0, -0.5) ,blue, noTex,// BT  - 7
        vec3(+0.3, +0.5, -0.5) ,blue, noTex,// BRH - 8
        vec3(+0.1, +0.5, -0.5) ,blue, noTex,// BRA - 9
        vec3(+0.1, -1.0, -0.5) ,blue, noTex,// BRF - 10
        vec3(-0.1, -1.0, -0.5) ,blue, noTex,// BLF - 11
        vec3(-0.1, +0.5, -0.5) ,blue, noTex,// BLA - 12
        vec3(-0.3, +0.5, -0.5) ,blue, noTex,// BLH - 13
    };

    arrow.setVerts(verts, sizeof(verts));

    GLushort indices[] =
    {
        0, 1, 6,    //
        2, 3, 5,    // Near face
        3, 4, 5,    //

        7, 8, 13,   //
        9, 10, 12,  // Far face
        10, 11, 12, //

        // Backshot
        1, 8, 2,
        2, 8, 9,
        3, 10, 4,
        4, 10, 11,
        5, 12, 6,
        6, 12, 13,

        // Left view
        0, 6, 13,
        0, 13, 7,
        4, 11, 5,
        5, 11, 12,

        // Right view
        0, 1, 8,
        0, 8, 7,
        2, 3, 10,
        2, 10, 9

    };
    arrow.setInds(indices, sizeof(indices));


    return arrow;

}
