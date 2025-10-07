#include <windows.h>
#include <string>

using namespace std;


// Global variables
const wchar_t g_szClassName[] = L"CalculatorWindowClass";
HWND hOutput;
wchar_t buffer[256];
wstring temp;
int currentOperation = -1;
double prevValue = 0;
bool clearNum = false;
double total = 0;

enum { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, MULTIPLY, DIVIDE, ADD, SUBTRACT, BACKSPACE, DOT, EQUALS };

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        // Calculator output
        hOutput = CreateWindow(
            L"STATIC", L"",
            WS_VISIBLE | WS_CHILD,
            20, 20, 200, 25,
            hwnd, NULL, NULL, NULL);

        // backspace button
        CreateWindow(
            L"BUTTON", L"Backspace",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            20, 60, 110, 30,
            hwnd, (HMENU)BACKSPACE, NULL, NULL);

        // divison button
        CreateWindow(
            L"BUTTON", L"/",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            140, 60, 30, 30,
            hwnd, (HMENU)DIVIDE, NULL, NULL);

        // buttons 7,8,9
        CreateWindow(
            L"BUTTON", L"7",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            20, 100, 30, 30,
            hwnd, (HMENU)SEVEN, NULL, NULL);

        CreateWindow(
            L"BUTTON", L"8",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            60, 100, 30, 30,
            hwnd, (HMENU)EIGHT, NULL, NULL);

        CreateWindow(
            L"BUTTON", L"9",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            100, 100, 30, 30,
            hwnd, (HMENU)NINE, NULL, NULL);

        // multiply
        CreateWindow(
            L"BUTTON", L"x",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            140, 100, 30, 30,
            hwnd, (HMENU)MULTIPLY, NULL, NULL);

        // buttons 4,5,6
        CreateWindow(
            L"BUTTON", L"4",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            20, 140, 30, 30,
            hwnd, (HMENU)FOUR, NULL, NULL);

        CreateWindow(
            L"BUTTON", L"5",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            60, 140, 30, 30,
            hwnd, (HMENU)FIVE, NULL, NULL);

        CreateWindow(
            L"BUTTON", L"6",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            100, 140, 30, 30,
            hwnd, (HMENU)SIX, NULL, NULL);

        // subtract
        CreateWindow(
            L"BUTTON", L"-",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            140, 140, 30, 30,
            hwnd, (HMENU)SUBTRACT, NULL, NULL);

        // buttons 1,2,3
        CreateWindow(
            L"BUTTON", L"1",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            20, 180, 30, 30,
            hwnd, (HMENU)ONE, NULL, NULL);

        CreateWindow(
            L"BUTTON", L"2",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            60, 180, 30, 30,
            hwnd, (HMENU)TWO, NULL, NULL);

        CreateWindow(
            L"BUTTON", L"3",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            100, 180, 30, 30,
            hwnd, (HMENU)THREE, NULL, NULL);

        // addition
        CreateWindow(
            L"BUTTON", L"+",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            140, 180, 30, 30,
            hwnd, (HMENU)ADD, NULL, NULL);

        // butons 0,dot, =
        CreateWindow(
            L"BUTTON", L"0",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            20, 220, 70, 30,
            hwnd, (HMENU)ZERO, NULL, NULL);

        CreateWindow(
            L"BUTTON", L".",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            100, 220, 30, 30,
            hwnd, (HMENU)DOT, NULL, NULL);

        CreateWindow(
            L"BUTTON", L"=",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            140, 220, 30, 30,
            hwnd, (HMENU)EQUALS, NULL, NULL);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {

        case ZERO:
            GetWindowText(hOutput, buffer, 256);
            temp = buffer;

            if (clearNum)
            {
                prevValue = stod(buffer);
                temp = L"";
                clearNum = false;
            }

            SetWindowText(hOutput, (temp + L"0").c_str());
            break;

        case ONE:
            GetWindowText(hOutput, buffer, 256);
            temp = buffer;

            if (clearNum)
            {
                prevValue = stod(buffer);
                temp = L"";
                clearNum = false;
            }

            SetWindowText(hOutput, (temp + L"1").c_str());
            break;

        case TWO:
            GetWindowText(hOutput, buffer, 256);
            temp = buffer;

            if (clearNum)
            {
                prevValue = stod(buffer);
                temp = L"";
                clearNum = false;
            }
            SetWindowText(hOutput, (temp + L"2").c_str());
            break;

        case THREE:
            GetWindowText(hOutput, buffer, 256);
            temp = buffer;

            if (clearNum)
            {
                prevValue = stod(buffer);
                temp = L"";
                clearNum = false;
            }
            SetWindowText(hOutput, (temp + L"3").c_str());
            break;

        case FOUR:
            GetWindowText(hOutput, buffer, 256);
            temp = buffer;

            if (clearNum)
            {
                prevValue = stod(buffer);
                temp = L"";
                clearNum = false;
            }
            SetWindowText(hOutput, (temp + L"4").c_str());
            break;

        case FIVE:
            GetWindowText(hOutput, buffer, 256);
            temp = buffer;

            if (clearNum)
            {
                prevValue = stod(buffer);
                temp = L"";
                clearNum = false;
            }
            SetWindowText(hOutput, (temp + L"5").c_str());
            break;

        case SIX:
            GetWindowText(hOutput, buffer, 256);
            temp = buffer;

            if (clearNum)
            {
                prevValue = stod(buffer);
                temp = L"";
                clearNum = false;
            }
            SetWindowText(hOutput, (temp + L"6").c_str());
            break;

        case SEVEN:
            GetWindowText(hOutput, buffer, 256);
            temp = buffer;

            if (clearNum)
            {
                prevValue = stod(buffer);
                temp = L"";
                clearNum = false;
            }
            SetWindowText(hOutput, (temp + L"7").c_str());
            break;

        case EIGHT:
            GetWindowText(hOutput, buffer, 256);
            temp = buffer;

            if (clearNum)
            {
                prevValue = stod(buffer);
                temp = L"";
                clearNum = false;
            }
            SetWindowText(hOutput, (temp + L"8").c_str());
            break;

        case NINE:
            GetWindowText(hOutput, buffer, 256);
            temp = buffer;

            if (clearNum)
            {
                prevValue = stod(buffer);
                temp = L"";
                clearNum = false;
            }
            SetWindowText(hOutput, (temp + L"9").c_str());
            break;

        case MULTIPLY:
            currentOperation = MULTIPLY;
            clearNum = true;
            break;

        case DIVIDE:
            currentOperation = DIVIDE;
            clearNum = true;
            break;

        case ADD:
            currentOperation = ADD;
            clearNum = true;
            break;

        case SUBTRACT:
            currentOperation = SUBTRACT;
            clearNum = true;
            break;

        case DOT:
            GetWindowText(hOutput, buffer, 256);
            temp = (wstring)buffer;
            if (temp.find(L".") == -1)
            {
                if (clearNum)
                {
                    prevValue = stod(buffer);
                    temp = L"";
                    clearNum = false;
                }
                SetWindowText(hOutput, (temp + L".").c_str());
            }
            break;

        case BACKSPACE:
            GetWindowText(hOutput, buffer, 256);
            temp = (wstring)buffer;
            SetWindowText(hOutput, (temp.substr(0, temp.length() - 1)).c_str());
            break;

        case EQUALS:
            GetWindowText(hOutput, buffer, 256);
            temp = (wstring)buffer;
            
            switch (currentOperation)
            {
            case MULTIPLY:
                total = prevValue * stod(temp);
                break;

            case DIVIDE:
                total = prevValue / stod(temp);
                break;

            case ADD:
                total = prevValue + stod(temp);
                break;

            case SUBTRACT:
                total = prevValue - stod(temp);
                break;
            }
            wstring totalStr = to_wstring(total);

            int i;
            wstring totalStrTemp = totalStr;

            for (i = totalStr.length() - 1; i > -1; i--)
            {
                if (totalStrTemp.substr(i, i + 1) == L"0")
                {
                    totalStrTemp = totalStrTemp.substr(0, i);
                }
                else
                {
                    if (totalStrTemp.substr(totalStrTemp.length() - 1, totalStrTemp.length()) == L".")
                    {
                        totalStrTemp = totalStrTemp.substr(0, totalStrTemp.length() - 1);
                    }
                    break;
                }
            }

            SetWindowText(hOutput, totalStrTemp.c_str());
            currentOperation = -1;
            clearNum = true;
            break;
        }
        break;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) {
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

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        L"Calculator",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 210, 400,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, L"Window Creation Failed!", L"Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}