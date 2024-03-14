#pragma once
#include "Engine/Entity.h"
#include <string>
#include "DirectX12/dx12Inst.h"

class Map {

private:

    int m_CaseX;
    int m_CaseY;
    int m_CaseZ;

    int m_EnemyCaseX;
    int m_EnemyCaseY;
    int m_EnemyCaseZ;

    // GRID ( [3][3][3] -> 3*3*3 = 27 cases )

    int m_CaseLimit = 6;
    int grid[6][6][6];

    int m_EnemyCaseLimit = 3;
    int enemyGrid[3][3][3];

    float sizeOfCases = 1200;
    float sizeOfObjects;

    //Planets
    int numberOfPlanets;
    std::vector <Entity*> m_ListPlanets;

    //Enemies
    int numberOfEnemiesPerHorde;
    int numberOfHordes;
    int m_distanceOfEnemies = 150 ;
    std::vector <Entity*> m_ListEnemies;


public:



    Map();
    ~Map();

    void CreateEntities(DirectX12Instance* Inst);
    void PlaceEntities(DirectX12Instance* Inst);
    void UpdateEntities();

    void GenerateEntities(DirectX12Instance* Inst);
};