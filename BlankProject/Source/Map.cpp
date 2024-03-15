#include "BlankProject.h"
#include "Map.h"
#include <string>
#include <vector>
#include "Common/Random.h"
#include "Engine/Tags.h"
#include "EnemyScript.h"
#include "ShipScript.h"
#include "Engine/Collider.h"
#include "HandleCollisions.h"


Map::Map(Entity* player, DirectX12Instance* inst) {

    m_pMainPlayer = player;
    m_pInst = inst;

    srand(time(0));
    numberOfPlanets = GenerateRandomInt(15, 31);


    numberOfHordes = GenerateRandomInt(10, 15);
    std::string Horde = "Hordes : " + std::to_string(numberOfHordes);
    OutputDebugStringA(Horde.c_str()); OutputDebugStringA("\n");

}
Map::~Map() {

}

void Map::CreateEntities(bool m_planet, bool m_enemies) {

    if (m_planet == true) {
        //Create Planets
        for (int i = 0; i < numberOfPlanets; i++) {

            Entity* pEntity = new Entity(m_pInst);
            m_pInst->m_ListEntities.push_back(pEntity);
            pEntity->InitObject("sphere");

            m_ListPlanets.push_back(pEntity);
        }
    }

    if (m_enemies == true) {
        //Create Hordes of Enemies
        DirectX::XMFLOAT3 tab[4] = {
            XMFLOAT3(20.0f,0.0f,0.0f),
            XMFLOAT3(10.0f,0.0f,5.0f),
            XMFLOAT3(5.0f,0.0f,0.0f),
            XMFLOAT3(5.0f,0.0f,10.0f)
        };
        for (int i = 0; i < numberOfHordes; i++) {

            numberOfEnemiesPerHorde = GenerateRandomInt(3, 6);
            OutputDebugStringA(std::to_string(numberOfEnemiesPerHorde).c_str());
            OutputDebugStringA("\n");
            for (int j = 0; j < numberOfEnemiesPerHorde; j++) {

                Entity* enemy = new Entity(m_pInst);

                m_pInst->m_ListEntities.push_back(enemy);
                dynamic_cast<Tags*>(enemy->AddComponentByName("tags"))->AddTags("enemy", "Horde" + std::to_string(i));
                m_ListEnemies.push_back(enemy);



                EnemyScript* enemyScript = new EnemyScript();
                ShipScript* shipScript = new ShipScript();

                shipScript->Initialize(m_pInst, enemy);
                enemy->AttachComponent(enemyScript);
                enemy->AttachComponent(shipScript);
                enemyScript->InitEnemyScript(4.0f, enemy, m_pMainPlayer);
                enemyScript->InitializeEnemy(m_pInst, tab);


            }
        }
    }
}

void Map::PlaceEntities(bool m_planet, bool m_enemies) {

    if (m_planet == true) {
        //Select Every Planet One By One
        for (int i = 0; i < m_ListPlanets.size(); i++) {

            //Set Size
            sizeOfObjects = GenerateRandomAsFloat(50, 70) * 0.5f;
            m_ListPlanets.at(i)->Scale(sizeOfObjects, sizeOfObjects, sizeOfObjects);

            //Find A Case In Grid
            m_CaseX = GenerateRandomInt(0, m_CaseLimit);
            m_CaseY = GenerateRandomInt(0, m_CaseLimit);
            m_CaseZ = GenerateRandomInt(0, m_CaseLimit);

            //Check A Slot For The Planet == Free
            if (grid[m_CaseX][m_CaseY][m_CaseZ] != 1) {
                //Place Planet
                m_ListPlanets.at(i)->Translate(IntToFloat(m_CaseX * sizeOfCases), IntToFloat(m_CaseY * sizeOfCases), IntToFloat(m_CaseZ * sizeOfCases));
                //Case Is Full
                grid[m_CaseX][m_CaseY][m_CaseZ] = 1;
            }
            //Check A Slot For The Planet == Full
            else {
                while (grid[m_CaseX][m_CaseY][m_CaseZ] == 1) {
                    //Find A New Case
                    m_CaseX = GenerateRandomInt(0, m_CaseLimit);
                    m_CaseY = GenerateRandomInt(0, m_CaseLimit);
                    m_CaseZ = GenerateRandomInt(0, m_CaseLimit);

                    //Check A Slot For The Planet == Free
                    if (grid[m_CaseX][m_CaseY][m_CaseZ] != 1) {
                        //Place Planet
                        m_ListPlanets.at(i)->Translate(IntToFloat(m_CaseX * sizeOfCases), IntToFloat(m_CaseY * sizeOfCases), IntToFloat(m_CaseZ * sizeOfCases));
                        //Case Is Full
                        grid[m_CaseX][m_CaseY][m_CaseZ] = 1;
                        break;

                    }
                }
            }
            //Offset

            m_ListPlanets.at(i)->Translate(IntToFloat(-sizeOfCases * 2), IntToFloat(-sizeOfCases * 2), IntToFloat(-sizeOfCases * 2));
        }
    }

    if (m_enemies == true) {
        //Set Tinier Grid For Enemies To Spawn
        m_CaseLimit -= 3;
        sizeOfCases /= 4;

        //Select Every Horde Of Enemies One By One
        for (int i = 0; i < numberOfHordes; i++) {


            //Find A Case In Grid
            m_CaseY = GenerateRandomInt(0, m_CaseLimit);
            m_CaseZ = GenerateRandomInt(0, m_CaseLimit);

            //Reset Enemy Mini Grid
            for (int k = 0; k < m_EnemyCaseLimit; k++) {
                for (int l = 0; l < m_EnemyCaseLimit; l++) {
                    for (int m = 0; m < m_EnemyCaseLimit; m++) {
                        enemyGrid[k][l][m] = 0;
                    }
                }
            }

            //Select The Enemies Of The Selected Horde
            for (int p = 0; p < m_ListEnemies.size(); p++) {
                if (m_ListEnemies.at(p)->HasTag("Horde" + std::to_string(i))) {


                    //Find A Case In Enemy Mini Grid / Enemy Cloud
                    m_EnemyCaseX = GenerateRandomInt(0, m_EnemyCaseLimit);
                    m_EnemyCaseY = GenerateRandomInt(0, m_EnemyCaseLimit);
                    m_EnemyCaseZ = GenerateRandomInt(0, m_EnemyCaseLimit);

                    //Define The Size Of The Enemy
                    sizeOfObjects = GenerateRandomAsFloat(2, 3) * 0.5f;
                    m_ListEnemies.at(p)->Scale(sizeOfObjects, sizeOfObjects, sizeOfObjects);

                    //Check A Slot For The Cloud == Free
                    if (grid[m_CaseX][m_CaseY][m_CaseZ] != 1 && grid[m_CaseX][m_CaseY][m_CaseZ] != 2) {

                        //Check A Slot In The Cloud For The Enemy == Free
                        if (enemyGrid[m_EnemyCaseX][m_EnemyCaseY][m_EnemyCaseZ] != 1) {

                            m_ListEnemies.at(p)->Translate(IntToFloat(m_CaseX * sizeOfCases + m_EnemyCaseX * m_distanceOfEnemies), IntToFloat(m_CaseY * sizeOfCases + m_EnemyCaseY * m_distanceOfEnemies), IntToFloat(m_CaseZ * sizeOfCases + m_EnemyCaseZ * m_distanceOfEnemies));
                            OutputDebugStringA("Enemy Placed"); OutputDebugStringA("\n");
                            enemyGrid[m_EnemyCaseX][m_EnemyCaseY][m_EnemyCaseZ] = 1;

                        }

                        //Check A Slot In The Cloud For The Enemy == Full
                        else {
                            while (enemyGrid[m_EnemyCaseX][m_EnemyCaseY][m_EnemyCaseZ] == 1) {
                                m_EnemyCaseX = GenerateRandomInt(0, m_EnemyCaseLimit);
                                m_EnemyCaseY = GenerateRandomInt(0, m_EnemyCaseLimit);
                                m_EnemyCaseZ = GenerateRandomInt(0, m_EnemyCaseLimit);

                                OutputDebugStringA("Mini Case Full");

                                if (enemyGrid[m_EnemyCaseX][m_EnemyCaseY][m_EnemyCaseZ] != 1) {
                                    m_ListEnemies.at(p)->Translate(IntToFloat(m_CaseX * sizeOfCases + m_EnemyCaseX * m_distanceOfEnemies), IntToFloat(m_CaseY * sizeOfCases + m_EnemyCaseY * m_distanceOfEnemies), IntToFloat(m_CaseZ * sizeOfCases + m_EnemyCaseZ * m_distanceOfEnemies));

                                    OutputDebugStringA("Mini Case Found"); OutputDebugStringA("Enemy Placed"); OutputDebugStringA("\n");
                                    enemyGrid[m_EnemyCaseX][m_EnemyCaseY][m_EnemyCaseZ] = 1;
                                    break;
                                }
                            }
                        }

                    }

                    //Check A Slot For The Cloud == Full
                    else {
                        while (grid[m_CaseX][m_CaseY][m_CaseZ] == 1 || grid[m_CaseX][m_CaseY][m_CaseZ] == 2) {
                            m_CaseX = GenerateRandomInt(0, m_CaseLimit);
                            m_CaseY = GenerateRandomInt(0, m_CaseLimit);
                            m_CaseZ = GenerateRandomInt(0, m_CaseLimit);

                            OutputDebugStringA("Case Full"); OutputDebugStringA("\n");

                            if (grid[m_CaseX][m_CaseY][m_CaseZ] != 1 && grid[m_CaseX][m_CaseY][m_CaseZ] != 2) {

                                OutputDebugStringA("Case Found"); OutputDebugStringA("\n");


                                //Check A Slot In The Cloud For The Enemy == Free
                                if (enemyGrid[m_EnemyCaseX][m_EnemyCaseY][m_EnemyCaseZ] != 1) {

                                    m_ListEnemies.at(p)->Translate(IntToFloat(m_CaseX * sizeOfCases + m_EnemyCaseX * m_distanceOfEnemies), IntToFloat(m_CaseY * sizeOfCases + m_EnemyCaseY * m_distanceOfEnemies), IntToFloat(m_CaseZ * sizeOfCases + m_EnemyCaseZ * m_distanceOfEnemies));
                                    OutputDebugStringA("Enemy Placed"); OutputDebugStringA("\n");
                                    enemyGrid[m_EnemyCaseX][m_EnemyCaseY][m_EnemyCaseZ] = 1;

                                }

                                //Check A Slot In The Cloud For The Enemy == Full
                                else {
                                    while (enemyGrid[m_EnemyCaseX][m_EnemyCaseY][m_EnemyCaseZ] == 1) {
                                        m_EnemyCaseX = GenerateRandomInt(0, m_EnemyCaseLimit);
                                        m_EnemyCaseY = GenerateRandomInt(0, m_EnemyCaseLimit);
                                        m_EnemyCaseZ = GenerateRandomInt(0, m_EnemyCaseLimit);

                                        OutputDebugStringA("Mini Case Full");

                                        if (enemyGrid[m_EnemyCaseX][m_EnemyCaseY][m_EnemyCaseZ] != 1) {
                                            m_ListEnemies.at(p)->Translate(IntToFloat(m_CaseX * sizeOfCases + m_EnemyCaseX * m_distanceOfEnemies), IntToFloat(m_CaseY * sizeOfCases + m_EnemyCaseY * m_distanceOfEnemies), IntToFloat(m_CaseZ * sizeOfCases + m_EnemyCaseZ * m_distanceOfEnemies));

                                            OutputDebugStringA("Mini Case Found"); OutputDebugStringA("Enemy Placed"); OutputDebugStringA("\n");
                                            enemyGrid[m_EnemyCaseX][m_EnemyCaseY][m_EnemyCaseZ] = 1;
                                            break;
                                        }
                                    }
                                }

                                break;

                            }
                        }
                    }

                    //Offset
                    m_ListEnemies.at(p)->Translate(IntToFloat(-sizeOfCases * 1.5), IntToFloat(-sizeOfCases * 1.5), IntToFloat(-sizeOfCases * 1.5));


                }


            }
            //When All Enemies Frome The Horde Are Placed, Set The Case As Full In The Grid
            grid[m_CaseX][m_CaseY][m_CaseZ] = 2;

        }
    }
}



void Map::UpdateEntities() {

}


void Map::GenerateEntities() {

    CreateEntities(true, true);
    PlaceEntities(true, true);
}