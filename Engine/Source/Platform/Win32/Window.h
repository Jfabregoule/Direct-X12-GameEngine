#pragma once

#include "SubObject.h"
#include "w32Caption.h"

#include <Uxtheme.h>
#pragma comment(lib,"uxtheme.lib")

namespace Win32 {

	class ENGINE_API Window : public Win32::SubObject, public Win32::Caption {

	public:
		Window(std::wstring title, HICON icon, WindowType type = RESIZABLE);
		~Window();

		virtual VOID Initialize() override;

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


	protected:

		SIZE			m_Size;
		WindowType		m_Type;

		BOOL			m_Active;
		BOOL			m_IsRunning = TRUE;

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
	};

}