#pragma once


namespace Win32 {

	class ENGINE_API SubObject {

	public:
		SubObject(std::wstring className, std::wstring classTitle, HICON icon);
		~SubObject();

		virtual VOID RegisterNewClass();
		virtual VOID Initialize() = 0;

	protected:
		static			LRESULT CALLBACK	SetupMessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static			LRESULT				AssignMessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		virtual			LRESULT				MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	protected:
		std::wstring			m_Class;
		std::wstring			m_Title;

		HICON					m_hIcon;

		HWND					m_Handle;
	public:
		HWND					Handle() { return m_Handle; }

	public:
		VOID					Handle(HWND hwnd) { m_Handle = hwnd; }

	};

}