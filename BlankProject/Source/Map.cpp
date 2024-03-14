#include "BlankProject.h"
#include "Map.h"
#include <string>
#include <vector>
#include "Common/Random.h"
#include "Engine/Tags.h"
#include "Enemy.h"


Map::Map() {

    srand(time(0));
    numberOfPlanets = GenerateRandomInt(15, 31);


    numberOfHordes = GenerateRandomInt(20, 41);
    std::string Horde = "Hordes : " + std::to_string(numberOfHordes);
    OutputDebugStringA(Horde.c_str()); OutputDebugStringA("\n");

}
Map::~Map() {

}

void Map::CreateEntities(DirectX12Instance* Inst) {

    //Create Planets
    for (int i = 0; i < numberOfPlanets; i++) {

        Entity* pEntity = new Entity(Inst);
        Inst->m_ListEntities.push_back(pEntity);
        pEntity->InitObject("cube");

        m_ListPlanets.push_back(pEntity);
    }

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
            Enemy* newEnemy = new Enemy;
            newEnemy->InitializeEnemy(Inst, tab);
            Inst->m_ListEntities.push_back(newEnemy->GetEntity());
            m_ListEnemies.push_back(newEnemy->GetEntity());
            //Entity* pEntity = new Entity(Inst);

            //Inst->m_ListEntities.push_back(pEntity);
            //pEntity->InitObject("pyramid");
            ////pEntity->SetCollider();
            //dynamic_cast<Tags*>(pEntity->AddComponentByName("tags"))->AddTags("Horde" + std::to_string(i));

            //m_ListEnemies.push_back(pEntity);
        }
    }
}

void Map::PlaceEntities(DirectX12Instance* Inst) {

    float offset = m_CaseLimit * sizeOfCases * 0.5f;
    //Place Planets
    for (int i = 0; i < m_ListPlanets.size(); i++) {

        sizeOfObjects = GenerateRandomAsFloat(30, 41) * 0.5f;

        m_ListPlanets.at(i)->Scale(sizeOfObjects, sizeOfObjects, sizeOfObjects);

        m_CaseX = GenerateRandomInt(0, m_CaseLimit);
        m_CaseY = GenerateRandomInt(0, m_CaseLimit);
        m_CaseZ = GenerateRandomInt(0, m_CaseLimit);

        if (grid[m_CaseX][m_CaseY][m_CaseZ] != 1) {
            m_ListPlanets.at(i)->Translate(IntToFloat(m_CaseX * sizeOfCases - offset), IntToFloat(m_CaseY * sizeOfCases - offset), IntToFloat(m_CaseZ * sizeOfCases - offset));
            grid[m_CaseX][m_CaseY][m_CaseZ] = 1;
        }
        else {
            while (grid[m_CaseX][m_CaseY][m_CaseZ] == 1) {
                m_CaseX = GenerateRandomInt(0, m_CaseLimit);
                m_CaseY = GenerateRandomInt(0, m_CaseLimit);
                m_CaseZ = GenerateRandomInt(0, m_CaseLimit);

                if (grid[m_CaseX][m_CaseY][m_CaseZ] != 1) {
                    m_ListPlanets.at(i)->Translate(IntToFloat(m_CaseX * sizeOfCases - offset), IntToFloat(m_CaseY * sizeOfCases - offset), IntToFloat(m_CaseZ * sizeOfCases - offset));
                    grid[m_CaseX][m_CaseY][m_CaseZ] = 1;
                    break;

                }
            }
        }
        //m_ListPlanets.at(i)->Translate(IntToFloat(-sizeOfCases * 2), IntToFloat(-sizeOfCases * 2), IntToFloat(-sizeOfCases * 2));
    }

    //Place Hordes of Enemies
    for (int i = 0; i < numberOfHordes; i++) {

        OutputDebugStringA("Horde "); OutputDebugStringA(std::to_string(i).c_str()); OutputDebugStringA("\n");

        m_CaseX = GenerateRandomInt(0, m_CaseLimit);
        m_CaseY = GenerateRandomInt(0, m_CaseLimit);
        m_CaseZ = GenerateRandomInt(0, m_CaseLimit);



        for (int p = 0; p < m_ListEnemies.size(); p++) {

            if (m_ListEnemies.at(p)->HasTag("Horde" + std::to_string(i))) {
                m_EnemyCaseX = GenerateRandomInt(0, m_EnemyCaseLimit);
                m_EnemyCaseY = GenerateRandomInt(0, m_EnemyCaseLimit);
                m_EnemyCaseZ = GenerateRandomInt(0, m_EnemyCaseLimit);

                OutputDebugStringA("Enemy Found : "); OutputDebugStringA(std::to_string(p).c_str()); OutputDebugStringA("\n");

                sizeOfObjects = GenerateRandomAsFloat(10, 21) * 0.5f;

                m_ListEnemies.at(p)->Scale(sizeOfObjects, sizeOfObjects, sizeOfObjects);

                if (grid[m_CaseX][m_CaseY][m_CaseZ] != 1) {
                    m_ListEnemies.at(p)->Translate(IntToFloat(m_CaseX * sizeOfCases + m_EnemyCaseX * m_distanceOfEnemies - offset), IntToFloat(m_CaseY * sizeOfCases + m_EnemyCaseY * m_distanceOfEnemies - offset), IntToFloat(m_CaseZ * sizeOfCases + m_EnemyCaseZ * m_distanceOfEnemies - offset));
                    OutputDebugStringA("Enemy Placed"); OutputDebugStringA("\n");
                }
                else {
                    while (grid[m_CaseX][m_CaseY][m_CaseZ] == 1) {
                        m_CaseX = GenerateRandomInt(0, m_CaseLimit);
                        m_CaseY = GenerateRandomInt(0, m_CaseLimit);
                        m_CaseZ = GenerateRandomInt(0, m_CaseLimit);

                        OutputDebugStringA("Case Full"); OutputDebugStringA("\n");

                        if (grid[m_CaseX][m_CaseY][m_CaseZ] != 1) {
                            m_EnemyCaseX = GenerateRandomInt(0, m_EnemyCaseLimit);
                            m_EnemyCaseY = GenerateRandomInt(0, m_EnemyCaseLimit);
                            m_EnemyCaseZ = GenerateRandomInt(0, m_EnemyCaseLimit);

                            m_ListEnemies.at(p)->Translate(IntToFloat(m_CaseX * sizeOfCases + m_EnemyCaseX * m_distanceOfEnemies - offset), IntToFloat(m_CaseY * sizeOfCases + m_EnemyCaseY * m_distanceOfEnemies - offset), IntToFloat(m_CaseZ * sizeOfCases + m_EnemyCaseZ * m_distanceOfEnemies - offset));
                            grid[m_CaseX][m_CaseY][m_CaseZ] = 2;
                            OutputDebugStringA("Case Found"); OutputDebugStringA("\n"); OutputDebugStringA("Enemy Placed"); OutputDebugStringA("\n");
                            break;

                        }
                    }
                }

                //m_ListEnemies.at(p)->Translate(IntToFloat(-sizeOfCases * 2), IntToFloat(-sizeOfCases * 2), IntToFloat(-sizeOfCases * 2));


            }


        }

    }
}

void Map::UpdateEntities() {

}


void Map::GenerateEntities(DirectX12Instance* Inst) {

    CreateEntities(Inst);
    PlaceEntities(Inst);
}