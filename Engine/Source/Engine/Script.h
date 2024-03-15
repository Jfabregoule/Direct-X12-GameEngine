#pragma once

#include "Component.h"

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									Script Class						                |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Script Class

class ENGINE_API Script : public Component {

public :

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |								Constructor/Destructor						            |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Constructor And Destructor

	Script();
	~Script();

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |										Methods											|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Methods

	void Update(float dt, float* gameSpeed) override;

#pragma endregion

};

#pragma endregion