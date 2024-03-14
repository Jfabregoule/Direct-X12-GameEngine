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

    int m_CaseLimit = 5;
    int grid[5][5][5];

    int m_EnemyCaseLimit = 3;
    int enemyGrid[3][3][3];

    float sizeOfCases = 500;
    float sizeOfObjects;

    //Planets
    int numberOfPlanets;
    std::vector <Entity*> m_ListPlanets;

    //Enemies
    int numberOfEnemiesPerHorde;
    int numberOfHordes;
    int m_distanceOfEnemies = 1;
    std::vector <Entity*> m_ListEnemies;

    Entity*                m_pMainPlayer;
    DirectX12Instance*     m_pInst;


public:



    Map(Entity* player, DirectX12Instance* inst);
    ~Map();

    void CreateEntities();
    void PlaceEntities();
    void UpdateEntities();

    void GenerateEntities();
};