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
    float sizeOfCases = 300;

    int m_EnemyCaseLimit = 9;
    int enemyGrid[9][9][9];
    int m_distanceOfEnemies = 4;

    float sizeOfObjects;

    //Planets
    int numberOfPlanets;
    std::vector <Entity*> m_ListPlanets;

    //Enemies
    int numberOfEnemiesPerHorde;
    int numberOfHordes;
    std::vector <Entity*> m_ListEnemies;



    Entity* m_pMainPlayer;
    DirectX12Instance* m_pInst;


public:



    Map(Entity* player, DirectX12Instance* inst);
    ~Map();

    void CreateEntities(bool m_planet, bool m_enemies);
    void PlaceEntities(bool m_planet, bool m_enemies);
    void UpdateEntities();

    void GenerateEntities();
};