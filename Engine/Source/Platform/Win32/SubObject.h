#pragma once

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									  Win32 Namespace 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Win32 Namespace

namespace Win32 {

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |									SubObject Class 									|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region SubObject Class

	class ENGINE_API SubObject {

	public:

		/*
		*  -------------------------------------------------------------------------------------
		* |                                                                                     |
		* |								Constructor/Destructor 									|
		* |                                                                                     |
		*  -------------------------------------------------------------------------------------
		*/

#pragma region Constructor And Destructor

		SubObject(std::wstring className, std::wstring classTitle, HICON icon);
		~SubObject();

#pragma endregion

		/*
		*  -------------------------------------------------------------------------------------
		* |                                                                                     |
		* |									    Methods 									    |
		* |                                                                                     |
		*  -------------------------------------------------------------------------------------
		*/

#pragma region Methods

		virtual VOID RegisterNewClass();
		virtual VOID Initialize() = 0;

	protected:
		static			LRESULT CALLBACK	SetupMessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static			LRESULT				AssignMessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		virtual			LRESULT				MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

#pragma endregion

		/*
		*  -------------------------------------------------------------------------------------
		* |                                                                                     |
		* |										Attributes 									    |
		* |                                                                                     |
		*  -------------------------------------------------------------------------------------
		*/

#pragma region Attributes

	protected:
		std::wstring			m_Class;
		std::wstring			m_Title;

		HICON					m_hIcon;

		HWND					m_Handle;

#pragma endregion

		/*
		*  -------------------------------------------------------------------------------------
		* |                                                                                     |
		* |									Getters/Setters 									|
		* |                                                                                     |
		*  -------------------------------------------------------------------------------------
		*/

#pragma region Getters And Setters

	public:
		HWND					Handle() { return m_Handle; }

	public:
		VOID					Handle(HWND hwnd) { m_Handle = hwnd; }

#pragma endregion

	};

#pragma endregion

}

#pragma endregion