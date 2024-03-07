#include "BlankProject.h"
#include "Map.h"
#include <string>
#include <vector>
#include "Engine/Random.h"



Map::Map() {

    srand(time(0));
    numberOfPlanets = Random::GenerateRandomInt(1, 5);

}

Map::~Map() {

}

void Map::CreateEntities(DirectX12Instance* Inst) {
    if (Inst->m_ListEntities.size() < numberOfPlanets) {
        for (int i = Inst->m_ListEntities.size(); i < numberOfPlanets; i++) {
            Inst->m_ListEntities.push_back(new Entity(Inst->device));
            if (!Inst->m_ListEntities.back()) {
                // Erreur : Impossible de créer une nouvelle entité
                return;
            }
        }
    }
}

void Map::PlaceEntities(DirectX12Instance* Inst) {
    if (Inst->m_ListEntities.size() < numberOfPlanets) {
        // Erreur : Pas assez d'entités pour placer
        return;
    }

    float x = 0.0f;

    for (int i = 0; i < numberOfPlanets; i++) {
        sizeOfPlanet = Random::GenerateRandomFloat(5, 10);
        if (Inst->m_ListEntities.at(i)) {
            Inst->m_ListEntities.at(i)->Scale(sizeOfPlanet, sizeOfPlanet, sizeOfPlanet);
            Inst->m_ListEntities.at(i)->Translate(0.0f + x, 0.0f, 0.0f);
        }
        else {
            // Erreur : Entité invalide
            return;
        }
        x += sizeOfPlanet + 10.0f;
    }
}

void Map::GenerateEntities(DirectX12Instance* Inst) {
    CreateEntities(Inst);
    PlaceEntities(Inst);
}