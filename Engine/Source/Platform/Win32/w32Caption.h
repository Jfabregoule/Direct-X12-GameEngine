#pragma once

#define			CB_CLOSE		0
#define			CB_MINIMIZE		1
#define			CB_MAXIMIZE		2

#include <list>

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
	* |									 Caption Class	 									|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Caption Class

	class Caption
	{

	public:

		/*
		*  -------------------------------------------------------------------------------------
		* |                                                                                     |
		* |										Attributs 										|
		* |                                                                                     |
		*  -------------------------------------------------------------------------------------
		*/

#pragma region Attributs

		struct CaptionButton {
			std::wstring Text = L"";

			INT Command = -1;
			INT Width = 50;
			RECT Rect;

			CaptionButton(std::wstring text, INT command, INT width = 50) {
				Text = text;
				Command = command;
				Width = width;
			}
		};



	private:
		BOOL m_ShowTitle = TRUE;

		std::list<CaptionButton*> m_CaptionButtons;

#pragma endregion

		/*
		*  -------------------------------------------------------------------------------------
		* |                                                                                     |
		* |									Getters/Setters										|
		* |                                                                                     |
		*  -------------------------------------------------------------------------------------
		*/

#pragma region Getters And Setters

	public:
		BOOL ShowTitle() { return m_ShowTitle; }
		std::list<CaptionButton*> CaptionButtons() { return m_CaptionButtons; };

#pragma endregion

		/*
		*  -------------------------------------------------------------------------------------
		* |                                                                                     |
		* |										Methods 										|
		* |                                                                                     |
		*  -------------------------------------------------------------------------------------
		*/

#pragma region Methods

	public:
		VOID ShowTitle(BOOL show) { m_ShowTitle = show; }

	public:
		VOID AddCaptionButton(CaptionButton* button);

	};

#pragma endregion


#pragma endregion

}

#pragma endregion