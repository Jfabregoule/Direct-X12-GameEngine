#include "BlankProject.h"
#include "Map.h"
#include <string>
#include <vector>
#include "Engine/Random.h"

using namespace std;

Map::Map() {

    srand(time(0));
    numberOfPlanets = Random::GenerateRandomInt(10, 15);

}
Map::~Map() {

}

void Map::CreateEntities(DirectX12Instance* Inst) {

    for (int i = 0; i < numberOfPlanets; i++) {

        Inst->m_ListEntities.push_back(new Entity(Inst->device));
        Inst->m_ListEntities.at(i)->InitObject("pyramid");
    }


}

void Map::PlaceEntities(DirectX12Instance* Inst) {


    for (int i = 0; i < numberOfPlanets; i++) {

        sizeOfPlanet = Random::GenerateRandomFloat(10, 15);

        Inst->m_ListEntities.at(i)->Scale(sizeOfPlanet, sizeOfPlanet, sizeOfPlanet);

        m_CaseX = Random::GenerateRandomInt(0, m_CaseLimit);
        m_CaseY = Random::GenerateRandomInt(0, m_CaseLimit);
        m_CaseZ = Random::GenerateRandomInt(0, m_CaseLimit);


        if (grid[m_CaseX][m_CaseY][m_CaseZ] != 1) {
            Inst->m_ListEntities.at(i)->Translate(Random::IntToFloat(m_CaseX * 100), Random::IntToFloat(m_CaseY * 100), Random::IntToFloat(m_CaseZ * 100));
            grid[m_CaseX][m_CaseY][m_CaseZ] = 1;
        }

        else {

            while (grid[m_CaseX][m_CaseY][m_CaseZ] == 1) {

                m_CaseX = Random::GenerateRandomInt(0, m_CaseLimit);
                m_CaseY = Random::GenerateRandomInt(0, m_CaseLimit);
                m_CaseZ = Random::GenerateRandomInt(0, m_CaseLimit);

                if (grid[m_CaseX][m_CaseY][m_CaseZ] != 1) {
                    Inst->m_ListEntities.at(i)->Translate(Random::IntToFloat(m_CaseX * 100), Random::IntToFloat(m_CaseY * 100), Random::IntToFloat(m_CaseZ * 100));
                    grid[m_CaseX][m_CaseY][m_CaseZ] = 1;
                    break;
                }
            }

        }
        
    }
    


}

void Map::GenerateEntities(DirectX12Instance* Inst) {

    CreateEntities(Inst);
    PlaceEntities(Inst);
}