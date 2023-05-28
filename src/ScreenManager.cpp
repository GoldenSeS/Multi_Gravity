#include "ScreenManager.h"

ScreenManager::ScreenManager() : m_ScreenBuffer(SCREEN_WIDTH * SCREEN_HEIGHT),
                                 m_BackBuffer(SCREEN_WIDTH * SCREEN_HEIGHT)
{
    // ��ȡ����̨������
    m_ConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    // ���ÿ���̨���ڴ�С
    SMALL_RECT windowSize = {0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1};
    SetConsoleWindowInfo(m_ConsoleOutput, true, &windowSize);

    // ���ÿ���̨��������С
    COORD bufferSize = {SCREEN_WIDTH, SCREEN_HEIGHT};
    SetConsoleScreenBufferSize(m_ConsoleOutput, bufferSize);

    Screeninit();
}

void ScreenManager::Screeninit()
{
    // ��ȡ��׼������
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    // ��ȡ����̨���ڴ�С
    HWND consoleWindow = GetConsoleWindow();
    RECT windowRect;
    GetWindowRect(consoleWindow, &windowRect);
    int windowWidth = windowRect.right - windowRect.left;
    int windowHeight = windowRect.bottom - windowRect.top;

    // ���ÿ���̨��Ļ��������С
    COORD bufferSize = {SCREEN_WIDTH, SCREEN_HEIGHT};
    SetConsoleScreenBufferSize(hConsoleOutput, bufferSize);

    // ���ÿ���̨���ڴ�С��λ��
    SMALL_RECT windowSize = {0, 0, 99, 39};
    SetConsoleWindowInfo(hConsoleOutput, TRUE, &windowSize);
    SetConsoleOutputCP(CP_UTF8);
    // ���ñ༭����
    DWORD consoleMode;
    GetConsoleMode(hConsoleOutput, &consoleMode);
    consoleMode &= ~ENABLE_QUICK_EDIT_MODE; // �Ƴ����ٱ༭ģʽ
    SetConsoleMode(hConsoleOutput, consoleMode);
    consoleMode &= ~ENABLE_INSERT_MODE;     // �Ƴ�����ģʽ
    SetConsoleMode(hConsoleOutput, consoleMode);
    consoleMode &= ~ENABLE_MOUSE_INPUT;     // �Ƴ��������
    SetConsoleMode(hConsoleOutput, consoleMode);

    // ���ع�����
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsoleOutput, &csbi);
    csbi.dwSize.Y = 40;
    csbi.dwSize.X = 100;
    SetConsoleScreenBufferSize(hConsoleOutput, csbi.dwSize);
    SetConsoleMode(hConsoleOutput, consoleMode | CONSOLE_FULLSCREEN_MODE);

    // // ���ô�����ʽ
    // LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    // style &= ~(WS_SIZEBOX | WS_MAXIMIZEBOX);
    // SetWindowLong(consoleWindow, GWL_STYLE, style);

    // ���ô��ڴ�С��λ��
    SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);

    // ��ȡ��׼������
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    // ��ȡ��ǰ������Ϣ
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hConsoleOutput, FALSE, &fontInfo);

    // �����������ƺʹ�С
    wcscpy_s(fontInfo.FaceName, L"Consolas");
    fontInfo.dwFontSize.X = 3;
    fontInfo.dwFontSize.Y = 6;

    // fontInfo.dwFontSize.X = GetSystemMetrics(SM_CXSCREEN) / 8000;
    // fontInfo.dwFontSize.Y = GetSystemMetrics(SM_CYSCREEN) / 2500;

    // ��������
    SetCurrentConsoleFontEx(hConsoleOutput, FALSE, &fontInfo);
}

void ScreenManager::ScreenShow(const std::vector<char> &screenBuffer, int width, int height)
{
    ScreenClear();
    // ����Ļ��������ַ���
    // int x = (SCREEN_WIDTH - width) / 2;
    // int y = (SCREEN_HEIGHT - height) / 2;
    int x = 0;
    int y = 0;

    for (int i = 0; i < screenBuffer.size(); i++)
    {
        int dx = i % width;
        int dy = i / width;
        ScreenDraw(x + dx, y + dy, std::string(1, screenBuffer[i]));
    }
    SwapBuffer();
    ScreenRender();
}

void ScreenManager::ScreenClear()
{
    for (int i = 0; i < m_BackBuffer.size(); i++)
    {
        m_BackBuffer[i] = ' ';
    }
}

void ScreenManager::ScreenDraw(int x, int y, const std::string &text)
{
    for (int i = 0; i < text.length(); i++)
    {
        int bufferIndex = GetBufferIndex(x + i, y);
        if (bufferIndex >= 0 && bufferIndex < m_BackBuffer.size())
        {
            m_BackBuffer[bufferIndex] = text[i];
        }
    }
}

void ScreenManager::SwapBuffer()
{
    m_ScreenBuffer = m_BackBuffer;
}

int ScreenManager::GetBufferIndex(int x, int y)
{
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
    {
        return -1;
    }

    return y * SCREEN_WIDTH + x;
}

bool ScreenManager::EnableVTMode()
{
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return false;
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return false;
    }
    return true;
}

void ScreenManager::ScreenRender()
{
    std::string outputString;
    for (int i = 0; i < m_ScreenBuffer.size(); i++)
    {
        outputString += m_ScreenBuffer[i];
        if ((i + 1) % SCREEN_WIDTH == 0)
        {
            outputString += '\n';
        }
    }

    // ���ַ������������̨
    DWORD bytesWritten;
    WriteConsole(m_ConsoleOutput, outputString.c_str(), outputString.length(), &bytesWritten, NULL);
}