#include <windows.h> 
#include <vector>
#include <string>

HWND Button[9];
int click = 1;
WCHAR boof[8];
std::vector <std::wstring> boofers(9);

void check_gorizontal(std::vector <std::wstring> boofers, HWND hwnd) {
    int count = 1;
    std::wstring pred = boofers[0];
    for (int i = 1; i < 9; i++) {
        if (count != 3) {
            if (i <= 2) {
                if ((pred == boofers[i]) && (pred != L"")) {
                    count++;
                    pred = boofers[i];
                }
                else {
                    count = 1;
                    i = 3;
                    pred = boofers[3];
                }
            }
            else if (i > 3 && i <= 5) {
                if ((pred == boofers[i]) && (pred != L"")) {
                    count++;
                    pred = boofers[i];
                }
                else {
                    count = 1;
                    i = 5;
                    pred = boofers[6];
                }
            }
            else {
                if ((pred == boofers[i]) && (pred != L"")) {
                    count++;
                    pred = boofers[i];
                }
                else {
                    count = 1;
                }
            }
        }
        else{
            MessageBox(hwnd, (L"Победили: " + pred).c_str(), L"Game over: ", MB_OK | MB_ICONINFORMATION);
            PostQuitMessage(0);
        }
    }
}


LRESULT CALLBACK ProcessMessage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT pn{};
        HDC hdc = BeginPaint(hwnd, &pn);

        FillRect(hdc, &pn.rcPaint, reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1));

        EndPaint(hwnd, &pn);
        break;
    }
    case WM_COMMAND:
    {
        WORD buttonId = LOWORD(wp) - 1;
        if (click % 2 != 0) {
            SetWindowTextW(Button[buttonId], L"Крестик");
        }
        else { 
            SetWindowTextW(Button[buttonId], L"Нолик");
        };
        click++;
        GetWindowTextW(Button[buttonId], boof, 8);
        boofers[buttonId] = boof;
        check_gorizontal(boofers, hwnd);
    }
    default:
        return DefWindowProcW(hwnd, msg, wp, lp);
    }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {


    WCHAR mainWindow[] = L"Main Window";

    WNDCLASS wnd{};

    wnd.hInstance = hInstance;
    wnd.lpszClassName = mainWindow;
    wnd.lpfnWndProc = ProcessMessage;
    RegisterClass(&wnd);

    HWND hwnd = CreateWindowExW(
        0,
        mainWindow,
        L"Крестики нолики",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );
    int counter = 0;
    for (int i = 0; i < 9; i++) {
        if (counter <= 2) {
            Button[i] = CreateWindowExW(
                0,
                L"BUTTON",
                L"Жми",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                100 + (i % 3) * 100, 100, 100, 100,
                hwnd,
                reinterpret_cast<HMENU>(i + 1),
                reinterpret_cast<HINSTANCE>(GetClassLongPtr(hwnd, GWLP_HINSTANCE)),
                nullptr
            );
            counter++;
        }
        else if (counter <= 5 && counter > 2) {
            Button[i] = CreateWindowExW(
                0,
                L"BUTTON",
                L"Жми",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                100 + (i % 3) * 100, 200, 100, 100,
                hwnd,
                reinterpret_cast<HMENU>(i + 1),
                reinterpret_cast<HINSTANCE>(GetClassLongPtr(hwnd, GWLP_HINSTANCE)),
                nullptr
            );
            counter++;
        }
        else {
            Button[i] = CreateWindowExW(
                0,
                L"BUTTON",
                L"Жми",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                100 + (i % 3) * 100, 300, 100, 100,
                hwnd,
                reinterpret_cast<HMENU>(i + 1),
                reinterpret_cast<HINSTANCE>(GetClassLongPtr(hwnd, GWLP_HINSTANCE)),
                nullptr
            );
            counter++;
        }
    }

    if (hwnd == nullptr)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg{};
    while (GetMessageW(&msg, hwnd, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return 0;
}
