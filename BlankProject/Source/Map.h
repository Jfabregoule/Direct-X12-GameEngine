#pragma once
#include "Engine/Entity.h"
#include <string>
#include "DirectX12/dx12Inst.h"

class Map {

private:

    int m_CaseX;
    int m_CaseY;
    int m_CaseZ;

    // 333 = 27 cases

    int m_CaseLimit = 4;
    int grid[4][4][4];


    int numberOfPlanets;
    float sizeOfPlanet;
    int m_Distance;


public:



    Map();
    ~Map();

    void CreateEntities(DirectX12Instance* Inst);
    void PlaceEntities(DirectX12Instance* Inst);

    void GenerateEntities(DirectX12Instance* Inst);
};