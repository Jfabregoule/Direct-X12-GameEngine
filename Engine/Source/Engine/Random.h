#pragma once

#include "Random.h"
#include <stdlib.h>
#include <time.h>
#include "windows.h"

namespace Random {

    int GenerateRandomInt(int min, int max) {

        return (min + (rand() % max));
    }

    float GenerateRandomFloat(int min, int max) {

        return (static_cast <float> (min + (rand() % max)));
    }

    float IntToFloat(int integer) {

        return (static_cast <float> (integer));
    }

    int FloatToInt(float floating) {

        return (static_cast <int> (floating));
    }

}