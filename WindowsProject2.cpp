// WindowsProject2.cpp : Definiuje punkt wejścia dla aplikacji.
//

#include "framework.h"
#include "WindowsProject2.h"

#define MAX_LOADSTRING 100
#define ID_PRZYCISK1 501
#define ID_PRZYCISK2 502


// Zmienne globalne:
HINSTANCE hInst;                                // Bieżąca instancja aplikacji
WCHAR szTitle[100];                  // Tekst paska tytułu okna
WCHAR szWindowClass[MAX_LOADSTRING];            // Nazwa klasy głównego okna

// Deklaracje funkcji używanych w tym module kodu:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HWND g_hPrzycisk1; // Globalny uchwyt do przycisku
HWND g_hPrzycisk2; // Globalny uchwyt do przycisku

// Główna funkcja aplikacji WinMain (punkt wejścia)
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance); // Nie używana zmienna
    UNREFERENCED_PARAMETER(lpCmdLine);     // Nie używana zmienna

    // TODO: Umieść tutaj kod aplikacji.

    // Inicjalizacja globalnych łańcuchów znaków
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); // Załaduj tytuł aplikacji
    LoadStringW(hInstance, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING); // Załaduj nazwę klasy okna
    MyRegisterClass(hInstance); // Zarejestruj klasę okna

    // Inicjalizacja aplikacji:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE; // Zakończ, jeśli nie udało się zainicjować instancji
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2)); // Załaduj akceleratory (skróty klawiszowe)

    MSG msg; // Struktura wiadomości

    // Główna pętla komunikatów:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        // Jeśli komunikat nie został obsłużony przez akceleratory, przekaż go dalej
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg); // Przetłumacz komunikat
            DispatchMessage(&msg);  // Wyślij komunikat do odpowiedniej procedury okna
        }
    }

    return (int) msg.wParam; // Zwróć kod zakończenia aplikacji
}

//
//  FUNKCJA: MyRegisterClass()
//
//  CEL: Rejestruje klasę okna.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX); // Rozmiar struktury

    wcex.style          = CS_HREDRAW | CS_VREDRAW; // Styl klasy okna (przerysowanie przy zmianie rozmiaru)
    wcex.lpfnWndProc    = WndProc;                 // Wskaźnik do procedury obsługi okna
    wcex.cbClsExtra     = 0;                       // Dodatkowa ilość bajtów dla klasy
    wcex.cbWndExtra     = 0;                       // Dodatkowa ilość bajtów dla okna
    wcex.hInstance      = hInstance;               // Uchwyt instancji aplikacji
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2)); // Ikona aplikacji
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW); // Kursor myszy
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);       // Kolor tła okna
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2); // Nazwa menu
    wcex.lpszClassName  = szWindowClass;                   // Nazwa klasy okna
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); // Mała ikona

    return RegisterClassExW(&wcex); // Zarejestruj klasę okna
}

//
//   FUNKCJA: InitInstance(HINSTANCE, int)
//
//   CEL: Zapisuje uchwyt instancji i tworzy główne okno
//
//   UWAGI:
//        W tej funkcji zapisujemy uchwyt instancji w zmiennej globalnej i
//        tworzymy oraz wyświetlamy główne okno programu.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Zapisz uchwyt instancji w zmiennej globalnej

    // Ustal wymiary okna
    int szerokosc = 1080;
    int wysokosc = 720;

    // Utwórz główne okno aplikacji
    HWND hWnd = CreateWindowW(
        szWindowClass,
        szTitle,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, // stały rozmiar, brak możliwości zmiany
        CW_USEDEFAULT, CW_USEDEFAULT,
        szerokosc, wysokosc,
        nullptr, nullptr,
        hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE; // Zwróć FALSE, jeśli nie udało się utworzyć okna
    }

    ShowWindow(hWnd, nCmdShow); // Pokaż okno
    UpdateWindow(hWnd);         // Odśwież okno

    g_hPrzycisk1 = CreateWindowEx(
        0,
        L"BUTTON",
        L"Guzik Nr 1",
        WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
        50, 50,
        150, 30,
        hWnd,
        (HMENU)ID_PRZYCISK1,
        hInstance,
        NULL
    );

    g_hPrzycisk2 = CreateWindowEx(
        0,
        L"BUTTON",
        L"Guzik Nr 2",
        WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
        50, 110,
        150, 30,
        hWnd,
        (HMENU)ID_PRZYCISK2,
        hInstance,
        NULL
    );

    return TRUE; // Zwróć TRUE, jeśli wszystko się powiodło
}

//
//  FUNKCJA: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  CEL: Przetwarza komunikaty dla głównego okna.
//
//  WM_COMMAND  - obsługa menu aplikacji
//  WM_PAINT    - rysowanie głównego okna
//  WM_DESTROY  - wysłanie komunikatu o zakończeniu aplikacji
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam); // Pobierz identyfikator polecenia z menu
            // Obsługa wyborów menu:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About); // Wyświetl okno "O programie"
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd); // Zamknij główne okno
                break;
            case ID_PRZYCISK1:
                MessageBox(hWnd, L"Nacisnąłeś przycisk!", L"Informacja", MB_OK | MB_ICONINFORMATION);
                break;
            case ID_PRZYCISK2:
                MessageBox(hWnd, L"Nacisnąłeś przycisk numer 2!", L"Informacja", MB_OK | MB_ICONINFORMATION);
                break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam); // Domyślna obsługa
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps); // Rozpocznij rysowanie
            // TODO: Dodaj tutaj kod rysujący wykorzystujący hdc...
            EndPaint(hWnd, &ps); // Zakończ rysowanie
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0); // Wyślij komunikat o zakończeniu aplikacji
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam); // Domyślna obsługa pozostałych komunikatów
    }

    return 0;
}

// Procedura obsługi okna dialogowego "O programie"
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam); // Nie używana zmienna
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE; // Inicjalizacja okna dialogowego

    case WM_COMMAND:
        // Zamknij okno dialogowe po kliknięciu OK lub Anuluj
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE; // Domyślna obsługa
}
