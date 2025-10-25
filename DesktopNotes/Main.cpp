#include <windows.h>

using namespace std;

// functions
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Global variables
const wchar_t g_szClassName[] = L"WindowClass";
bool isDragging = false;
POINT clickPos;
HWND edit;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) 
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    // Step 1: Registering the Window Class
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) 
    {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_TOOLWINDOW,
        g_szClassName,
        L"",
        WS_POPUPWINDOW | WS_THICKFRAME | WS_CAPTION,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 600,
        NULL, NULL, hInstance, NULL);

    SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 300, 600, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);

    if (hwnd == NULL) 
    {
        MessageBox(NULL, L"Window Creation Failed!", L"Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while (GetMessage(&Msg, NULL, 0, 0) > 0) 
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        edit = CreateWindow(
            L"EDIT", L"test",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL | ES_WANTRETURN | WS_VSCROLL,
            20, 0, 260, 560,
            hwnd, NULL, NULL, NULL);

        SetTimer(hwnd, 1, 1000, NULL);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case 0:
            //DestroyWindow(hwnd);
            break;
        }
        break;

    case WM_MOUSEMOVE:
        if (isDragging) {
            POINT currentPos;
            GetCursorPos(&currentPos);

            int offsetX = currentPos.x - clickPos.x;
            int offsetY = currentPos.y - clickPos.y;

            // Get current window position
            RECT rect;
            GetWindowRect(hwnd, &rect);

            MoveWindow(hwnd, rect.left + offsetX, rect.top + offsetY, rect.right - rect.left, rect.bottom - rect.top, TRUE);

            clickPos = currentPos; // Update clickPos for smooth dragging
        }
        return 0;

    case WM_LBUTTONUP:
        isDragging = false;
        ReleaseCapture();
        return 0;

    case WM_LBUTTONDOWN:
    {
        POINT pt = { LOWORD(lParam), HIWORD(lParam) };
        ClientToScreen(hwnd, &pt);  // Convert to screen coordinates

        HWND child = WindowFromPoint(pt);  // Correct way to detect child under cursor

        if (child == hwnd) {
            isDragging = true;
            SetCapture(hwnd);
            clickPos = pt;  // Save screen coords for movement calculation
        }clickPos = pt;
        return 0;
    }

    case WM_SIZE:
    {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);

        MoveWindow(edit, 20, 0, width-40, height-40, TRUE);
        return 0;
    }

    case WM_TIMER:
    {
        BOOL isVisible = IsWindowVisible(hwnd);

        SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 300, 600, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);

        if (!isVisible) {
            ShowWindow(hwnd, SW_SHOW);
        }
        return 0;
    }

    case WM_MOUSEACTIVATE:
        return MA_NOACTIVATE;
    
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        KillTimer(hwnd, 1);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
