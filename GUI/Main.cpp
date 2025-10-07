#include <windows.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

// functions
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
vector<double> parseNumbers(wstring s);
vector<wstring> parseOperations(wstring s);
wstring calculate(wstring s);


// Global variables
const wchar_t g_szClassName[] = L"CalculatorWindowClass";
HWND hOutput;
wchar_t buffer[256];
wstring temp;
double total = 0;

enum {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, MULTIPLY, DIVIDE, ADD, SUBTRACT, BACKSPACE, DOT, EQUALS};

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
            total *= 10;

            GetWindowText(hOutput, buffer, 256);
            SetWindowText(hOutput, ((wstring)buffer + L"0").c_str());
            break;

        case ONE:
            GetWindowText(hOutput, buffer, 256);
            SetWindowText(hOutput, ((wstring)buffer + L"1").c_str()); 
            break;

        case TWO:
            GetWindowText(hOutput, buffer, 256);
            SetWindowText(hOutput, ((wstring)buffer + L"2").c_str());
            break;

        case THREE:
            GetWindowText(hOutput, buffer, 256);
            SetWindowText(hOutput, ((wstring)buffer + L"3").c_str());
            break;

        case FOUR:
            GetWindowText(hOutput, buffer, 256);
            SetWindowText(hOutput, ((wstring)buffer + L"4").c_str());
            break;

        case FIVE:
            GetWindowText(hOutput, buffer, 256);
            SetWindowText(hOutput, ((wstring)buffer + L"5").c_str());
            break;

        case SIX:
            GetWindowText(hOutput, buffer, 256);
            SetWindowText(hOutput, ((wstring)buffer + L"6").c_str());
            break;

        case SEVEN:
            GetWindowText(hOutput, buffer, 256);
            SetWindowText(hOutput, ((wstring)buffer + L"7").c_str());
            break;

        case EIGHT:
            GetWindowText(hOutput, buffer, 256);
            SetWindowText(hOutput, ((wstring)buffer + L"8").c_str());
            break;

        case NINE:
            GetWindowText(hOutput, buffer, 256);
            SetWindowText(hOutput, ((wstring)buffer + L"9").c_str());
            break;

        case MULTIPLY:
            GetWindowText(hOutput, buffer, 256);

            total *= stod(buffer);

            temp = (wstring)buffer;
            temp = temp.substr(temp.length() - 1, temp.length());

            if (temp != L"x" && temp != L"/" && temp != L"+" && temp != L"-")
            {
                SetWindowText(hOutput, ((wstring)buffer + L"x").c_str());
            }

            break;

        case DIVIDE:
            GetWindowText(hOutput, buffer, 256);
            temp = (wstring)buffer;
            temp = temp.substr(temp.length() - 1, temp.length());

            if (temp != L"x" && temp != L"/" && temp != L"+" && temp != L"-")
            {
                SetWindowText(hOutput, ((wstring)buffer + L"/").c_str());
            }
            break;

        case ADD:
            GetWindowText(hOutput, buffer, 256);
            temp = (wstring)buffer;
            temp = temp.substr(temp.length() - 1, temp.length());

            if (temp != L"x" && temp != L"/" && temp != L"+" && temp != L"-")
            {
                SetWindowText(hOutput, ((wstring)buffer + L"+").c_str());
            }
            break;

        case SUBTRACT:
            GetWindowText(hOutput, buffer, 256);
            temp = (wstring)buffer;
            temp = temp.substr(temp.length() - 1, temp.length());

            if (temp != L"x" && temp != L"/" && temp != L"+" && temp != L"-")
            {
                SetWindowText(hOutput, ((wstring)buffer + L"-").c_str());
            }
            break;

        case DOT:
            GetWindowText(hOutput, buffer, 256);
            temp = (wstring)buffer;
            if (temp.find(L".") == -1)
            {
                SetWindowText(hOutput, ((wstring)buffer + L".").c_str());
            }
            break;

        case BACKSPACE:
            GetWindowText(hOutput, buffer, 256);
            temp = (wstring)buffer;
            SetWindowText(hOutput, (temp.substr(0, temp.length() - 1)).c_str());
            break;

        case EQUALS:
            GetWindowText(hOutput, buffer, 256);

            temp = calculate((wstring)buffer + L"=");

            int i;
            wstring totalStrTemp = temp;

            for (i = temp.length() - 1; i > -1; i--)
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

vector<double> parseNumbers(wstring s)
{
    int cutoff = 0;
    vector<double> numbers;
    int i;
    wstring temp;

    for (i = 0; i < s.length(); i++)
    {
        temp = s.substr(i, 1);

        if (temp == L"x" || temp == L"/" || temp == L"+" || temp == L"-" || temp == L"=")
        {
            numbers.push_back(stod(s.substr(cutoff, i - cutoff)));
            cutoff = i + 1;
        }
    }
    return numbers;
}

vector<wstring> parseOperations(wstring s)
{
    vector<wstring> operations;
    int i;
    wstring temp;

    for (i = 0; i < s.length(); i++)
    {
        temp = s.substr(i, 1);

        if (temp == L"x" || temp == L"/" || temp == L"+" || temp == L"-")
        {
            operations.push_back(temp);
        }
    }
    return operations;
}

wstring calculate(wstring s)
{
    vector<double> numbers = parseNumbers(s);
    vector<wstring> operations = parseOperations(s);
    vector<wstring> tempOperations = operations;
    vector<wstring> bidmas = { L"/", L"x", L"+", L"-" };

    double tempNum = 0;

    for (auto i = bidmas.begin(); i != bidmas.end(); i++)
    {
        for (int j = 0; j < operations.size(); j++)
        {
            if (*i == operations.at(j))
            {
                if (*i == L"/")
                {
                    tempNum = numbers.at(j) / numbers.at(j + 1);
                }
                else if (*i == L"x")
                {
                    tempNum = numbers.at(j) * numbers.at(j + 1);
                }
                else if (*i == L"+")
                {
                    tempNum = numbers.at(j) + numbers.at(j + 1);
                }
                else if (*i == L"-")
                {
                    tempNum = numbers.at(j) - numbers.at(j + 1);
                }

                if (operations.size() != 1)
                {
                    tempOperations = operations;
                    tempOperations.erase(tempOperations.begin() + j);
                }
                numbers.erase(numbers.begin() + j + 1);
                numbers.at(j) = tempNum;
            }
        }
        operations = tempOperations;
    }
    return to_wstring(numbers[0]);
}















































//#include <windows.h>

/*
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdParam, int iCmdShow)
{

    //MessageBox(NULL, L"Hello World!", L"Note", 1);


    return 0;
}
*/


//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*
LONG_PTR: This is a platform-independent data type defined in the Windows headers. It is designed to represent a signed long integer that can hold a pointer.
On a 32-bit system, it is equivalent to a long (32 bits), and on a 64-bit system, it is equivalent to a __int64 (64 bits).
LRESULT: This is a typedef for LONG_PTR and is commonly used as the return type for Windows message-handling functions (e.g., WindowProc). It is used to ensure
compatibility across different platforms (32-bit and 64-bit).*/


/*
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

#include <windows.h>*/
/*

// Global variables
HINSTANCE hInst;
LPCWSTR szWindowClass = L"SimpleWindow";
LPCWSTR szTitle = L"Simple Window with Text";

// Forward declarations of functions
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Entry point for the program
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    // Initialize global strings
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    // Register class
    if (!RegisterClassEx(&wcex)) {
        MessageBox(nullptr, L"Window Registration Failed!", L"Error", MB_ICONERROR);
        return 1;
    }

    // Create window
    hInst = hInstance;
    HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 300,
        nullptr, nullptr, hInstance, nullptr);
    if (!hWnd) {
        MessageBox(nullptr, L"Window Creation Failed!", L"Error", MB_ICONERROR);
        return 1;
    }

    // Show and update the window
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// Window procedure: process messages
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_PAINT: {
        // Draw text on the window
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // Set text color and font
        SetTextColor(hdc, RGB(0, 0, 0));
        HFONT hFont = CreateFont(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH, L"Arial");
        SelectObject(hdc, hFont);

        // Display text in the center of the window
        RECT rect;
        GetClientRect(hWnd, &rect);
        DrawText(hdc, L"Hello, World!", -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        // Clean up
        DeleteObject(hFont);
        EndPaint(hWnd, &ps);
    }
                 break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

#include <windows.h>

// Global variables
const char g_szClassName[] = "myWindowClass";

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        // Create a static text label
        CreateWindow(
            "STATIC", "Hello, World!",
            WS_VISIBLE | WS_CHILD,
            20, 20, 200, 25,
            hwnd, NULL, NULL, NULL);

        // Create a button
        CreateWindow(
            "BUTTON", "Click Me",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            20, 60, 100, 30,
            hwnd, (HMENU)1, NULL, NULL);
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            MessageBox(hwnd, "Button Clicked!", "Info", MB_OK | MB_ICONINFORMATION);
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
    wc.cbSize = siz

        */


