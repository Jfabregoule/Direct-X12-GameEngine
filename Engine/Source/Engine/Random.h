#pragma once

#include "Random.h"
#include <stdlib.h>
#include <time.h>
#include "windows.h"

namespace Random {

	int GenerateRandomInt(int min, int max) {

		return ( min + (rand() % (max+1) ) );
	}

	float GenerateRandomFloat(int min, int max) {

		return ( static_cast <float> (min + (rand() % (max+1)) ) );
	}

	float IntToFloat(int integer) {

		return (static_cast <float> (integer) );
	}

}