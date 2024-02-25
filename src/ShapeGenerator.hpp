#pragma once
#include "header.hpp"

class ShapeGenerator
{
public:
    static ShapeData makeTriangle();
    static ShapeData makeCube();
    static ShapeData makeArrow();
    static ShapeData makeTexCube();
};