#include <windows.h>
#include <libpq-fe.h>

static LPSTR g_szClassName = "PQWindowClass";

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{

    WNDCLASSEX wc = {0};

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = g_szClassName;
    wc.lpszMenuName = NULL;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    HWND hwnd = CreateWindowEx( 
        WS_EX_OVERLAPPEDWINDOW,
        g_szClassName,
        "PQVIEW",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        NULL, NULL, hInst, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    ShowWindow(hwnd, cmdshow);
    UpdateWindow(hwnd);
    MSG msg;
    BOOL ret;
    while ((ret = GetMessage(&msg, hwnd, 0, 0)) != 0)
    {
        if (ret == -1)
        {
            MessageBox(NULL, "GetMessage Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
            return 0;
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int)msg.wParam;
}


void TestPostgreConnection(HWND hwnd) {
    PGconn *conn;
    PGresult *res;
    const char *version;
    char successMessage[1024] =  {0};
    char errorMessage[1024] = {0};

    static const char *conninfo = "host=localhost port=5432 dbname=postgres user=postgres password=postgres";
    conn = PQconnectdb(conninfo);
    if (PQstatus(conn) != CONNECTION_OK) {
        MessageBox(hwnd, PQerrorMessage(conn), "Connection to database failed", MB_OK | MB_ICONERROR);
        PQfinish(conn);
        return;
    }
    static const char *sql = "SELECT version();";
    res = PQexec(conn, sql);
    if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res) > 0 ) {
        version = PQgetvalue(res, 0, 0);
        snprintf(successMessage, sizeof(successMessage), "PostgreSQL version: %s", version);
        MessageBox(hwnd, successMessage, "Success", MB_OK | MB_ICONINFORMATION);
    } else {
        snprintf(errorMessage, sizeof(errorMessage), "SQL query failed: %s", PQerrorMessage(conn));
        MessageBox(hwnd, errorMessage, "Error", MB_OK | MB_ICONERROR);
    }
    PQclear(res);
    PQfinish(conn);
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        TestPostgreConnection(hwnd);
        break;
    case WM_CLOSE:
        if (IDYES == MessageBox(hwnd, "Are you sure you want to exit?", "Exit", MB_YESNO | MB_ICONQUESTION )) {
            DestroyWindow(hwnd);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        RECT rect;
        GetClientRect(hwnd, &rect);
        HDC hdc = BeginPaint(hwnd,&ps);

        DrawText(hdc, "HELLO WORLD",-1,&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        EndPaint(hwnd,&ps);
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
