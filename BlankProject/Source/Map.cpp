#include "BlankProject.h"
#include "Map.h"
#include <string>
#include <vector>
#include "Engine/Random.h"

using namespace std;

Map::Map() {

    srand(time(0));
    numberOfPlanets = 1;
        //Random::GenerateRandomInt(10, 15);

}
Map::~Map() {

}

void Map::CreateEntities(DirectX12Instance* Inst) {

    for (int i = 0; i < numberOfPlanets; i++) {

        Inst->m_ListEntities.push_back(new Entity(Inst));
        Inst->m_ListEntities.at(i)->InitObject("sphere");
        Inst->m_ListEntities.at(i)->SetCollider();
    }


}

void Map::PlaceEntities(DirectX12Instance* Inst) {

    m_Distance = 100;


    for (int i = 0; i < numberOfPlanets; i++) {

        sizeOfPlanet = Random::GenerateRandomFloat(10, 15);

        Inst->m_ListEntities.at(i)->Scale(sizeOfPlanet, sizeOfPlanet, sizeOfPlanet);

        m_CaseX = Random::GenerateRandomInt(0, m_CaseLimit);
        m_CaseY = Random::GenerateRandomInt(0, m_CaseLimit);
        m_CaseZ = Random::GenerateRandomInt(0, m_CaseLimit);


        if (grid[m_CaseX][m_CaseY][m_CaseZ] != 1) {
            Inst->m_ListEntities.at(i)->Translate(Random::IntToFloat(m_CaseX * m_Distance), Random::IntToFloat(m_CaseY * m_Distance), Random::IntToFloat(m_CaseZ * m_Distance));
            grid[m_CaseX][m_CaseY][m_CaseZ] = 1;
        }

        else {

            while (grid[m_CaseX][m_CaseY][m_CaseZ] == 1) {

                m_CaseX = Random::GenerateRandomInt(0, m_CaseLimit);
                m_CaseY = Random::GenerateRandomInt(0, m_CaseLimit);
                m_CaseZ = Random::GenerateRandomInt(0, m_CaseLimit);

                if (grid[m_CaseX][m_CaseY][m_CaseZ] != 1) {
                    Inst->m_ListEntities.at(i)->Translate(Random::IntToFloat(m_CaseX * m_Distance), Random::IntToFloat(m_CaseY * m_Distance), Random::IntToFloat(m_CaseZ * m_Distance));
                    grid[m_CaseX][m_CaseY][m_CaseZ] = 1;
                    break;
                }
            }

        }

        Inst->m_ListEntities.at(i)->Translate(Random::IntToFloat(-m_Distance * 1.5), Random::IntToFloat(-m_Distance * 1.5), Random::IntToFloat(-m_Distance * 1.5));


    }



}

void Map::GenerateEntities(DirectX12Instance* Inst) {

    CreateEntities(Inst);
    PlaceEntities(Inst);
}