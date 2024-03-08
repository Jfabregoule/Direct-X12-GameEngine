#pragma once
#include "Engine/Entity.h"
#include <string>
#include "DirectX12/dx12Inst.h"

class Map {

private:

    int m_CaseX;
    int m_CaseY;
    int m_CaseZ;

    // 3*3*3 = 27 cases

    int m_CaseLimit = 3;
    int grid[3][3][3];

    int numberOfPlanets;
    float sizeOfPlanet;


public:



    Map();
    ~Map();

    void CreateEntities(DirectX12Instance* Inst);
    void PlaceEntities(DirectX12Instance* Inst);

    void GenerateEntities(DirectX12Instance* Inst);
};