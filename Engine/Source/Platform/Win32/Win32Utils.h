#pragma once

#define DEFAULTWIDTH 1280
#define DEFAULTHEIGHT 720

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									 Win32 Namespace 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Win32 Namespace

namespace Win32 {

    enum WindowType : DWORD {
        STATIC = WS_OVERLAPPED,
        RESIZABLE = WS_SIZEBOX,
        POPUP = WS_POPUP
    };

    /*
    *  -------------------------------------------------------------------------------------
    * |                                                                                     |
    * |									 Utils Namespace 									|
    * |                                                                                     |
    *  -------------------------------------------------------------------------------------
    */

#pragma region Utils Namespace

    namespace Utils {

        /*
        *  -------------------------------------------------------------------------------------
        * |                                                                                     |
        * |									 Functions 							        		|
        * |                                                                                     |
        *  -------------------------------------------------------------------------------------
        */

#pragma region Functions

        BOOL ENGINE_API AddBitmap(CONST WCHAR* szFileName, HDC hWinDC, INT x = 0, INT y = 0);

        /// Sets and clears style flags for a particular window.
        inline VOID ENGINE_API ModifyWindowStyle(HWND hWnd, DWORD flagsToDisable, DWORD flagsToEnable)
        {
            DWORD style = GetWindowLong(hWnd, GWL_STYLE);
            SetWindowLong(hWnd, GWL_STYLE, (style & ~flagsToDisable) | flagsToEnable);
        }

        /// Sets and clears extended style flags for a particular window.
        inline VOID ENGINE_API ModifyWindowExStyle(HWND hWnd, DWORD flagsToDisable, DWORD flagsToEnable)
        {
            DWORD exStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
            SetWindowLong(hWnd, GWL_EXSTYLE, (exStyle & ~flagsToDisable) | flagsToEnable);
        }


        inline BOOL ENGINE_API HasStyle(HWND hwnd, DWORD style) {
            DWORD dwStyle = (DWORD)GetWindowLong(hwnd, GWL_STYLE);
            if ((dwStyle & style) != 0) return TRUE;
            return FALSE;
        }


        /// Sets and clears style flags for a particular window.
        inline VOID ENGINE_API ModifyClassStyle(HWND hWnd, DWORD flagsToDisable, DWORD flagsToEnable)
        {
            DWORD style = GetWindowLong(hWnd, GCL_STYLE);
            SetClassLong(hWnd, GCL_STYLE, (style & ~flagsToDisable) | flagsToEnable);
        }

        inline BOOL ENGINE_API IsWindowFullscreen(HWND hWnd)
        {
            WINDOWPLACEMENT placement;
            GetWindowPlacement(hWnd, &placement);

            if (placement.showCmd == SW_MAXIMIZE)
                return TRUE;
            return FALSE;
        }

        inline VOID ENGINE_API MaximizeWindow(HWND hwnd) {
            WINDOWPLACEMENT wPos;
            GetWindowPlacement(hwnd, &wPos);
            if (wPos.showCmd == SW_MAXIMIZE) ShowWindow(hwnd, SW_NORMAL);
            else  ShowWindow(hwnd, SW_MAXIMIZE);
        }

#pragma endregion

    }

#pragma endregion

}

#pragma endregion