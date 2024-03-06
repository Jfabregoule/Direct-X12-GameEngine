#pragma once

#include "SubObject.h"
#include "w32Caption.h"

#include <Uxtheme.h>
#pragma comment(lib,"uxtheme.lib")

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
	* |									  Window Class 									    |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Window Class

	class ENGINE_API Window : public Win32::SubObject, public Win32::Caption {

	public:

		/*
		*  -------------------------------------------------------------------------------------
		* |                                                                                     |
		* |								 Constructor/Destructor 								|
		* |                                                                                     |
		*  -------------------------------------------------------------------------------------
		*/

#pragma region Constructor And Destructor

		Window(std::wstring title, HICON icon, WindowType type = RESIZABLE);
		~Window();

#pragma endregion

		/*
		*  -------------------------------------------------------------------------------------
		* |                                                                                     |
		* |									    Initialize 									    |
		* |                                                                                     |
		*  -------------------------------------------------------------------------------------
		*/

#pragma region Initialize

		virtual VOID Initialize() override;

#pragma endregion

		/*
		*  -------------------------------------------------------------------------------------
		* |                                                                                     |
		* |									    Methods 									    |
		* |                                                                                     |
		*  -------------------------------------------------------------------------------------
		*/

#pragma region Methods

		virtual			LRESULT				MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

		VOID RedrawWindow();

		VOID OnNonClientCreate();

		VOID OnNonClientActivate(BOOL active);

		VOID OnNonClientPaint(HRGN region);

		VOID PaintCaption(HDC hdc);

		VOID OnNonClientLeftMouseButtonDown();

		VOID OnGetMinMaxInfo(MINMAXINFO* minmax);

		VOID OnExitSizeMove();

		VOID OnPaint();

#pragma endregion

		/*
		*  -------------------------------------------------------------------------------------
		* |                                                                                     |
		* |									    Attributs 									    |
		* |                                                                                     |
		*  -------------------------------------------------------------------------------------
		*/

#pragma region Attributs

	protected:

		SIZE			m_Size;
		WindowType		m_Type;

		BOOL			m_Active;
		BOOL			m_IsRunning = TRUE;

#pragma endregion

		/*
		*  -------------------------------------------------------------------------------------
		* |                                                                                     |
		* |									  Getters/Setters 									|
		* |                                                                                     |
		*  -------------------------------------------------------------------------------------
		*/

#pragma region Getters And Setters

	public:
		SIZE			Size() { return m_Size; }
		BOOL			Active() { return m_Active; }
		BOOL			IsRunning() { return m_IsRunning; }
		Window*			GetWindow() { return this; }

	public:
		VOID			Size(SIZE size) { m_Size = size; }
		VOID			Size(INT cx, INT cy) { m_Size.cx = cx; m_Size.cy = cy; }
		VOID			Active(BOOL active) { m_Active = active; }
		VOID			IsRunning(BOOL IsRunning) { m_IsRunning = IsRunning; }

#pragma endregion

	};

#pragma endregion

}

#pragma endregion