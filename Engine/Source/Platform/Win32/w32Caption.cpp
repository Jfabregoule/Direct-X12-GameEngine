#include "Engine.h"

#include "w32Caption.h"

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									 Win32 Namespace 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Win32 Namespace

namespace Win32 {

    /*
    *  -------------------------------------------------------------------------------------
    * |                                                                                     |
    * |									    Methods 									    |
    * |                                                                                     |
    *  -------------------------------------------------------------------------------------
    */

#pragma region Methods

    VOID Caption::AddCaptionButton(CaptionButton* button)
    {
        m_CaptionButtons.push_back(button);
    }

#pragma endregion

}

#pragma endregion