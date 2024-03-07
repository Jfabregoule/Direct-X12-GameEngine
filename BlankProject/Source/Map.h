#pragma once
#include "Engine/Entity.h"
#include <string>
#include "DirectX12/dx12Inst.h"

class Map {

private:

    int numberOfPlanets;
    float sizeOfPlanet;

public:



    Map();
    ~Map();

    void CreateEntities(DirectX12Instance* Inst);
    void PlaceEntities(DirectX12Instance* Inst);

    void GenerateEntities(DirectX12Instance* Inst);
};