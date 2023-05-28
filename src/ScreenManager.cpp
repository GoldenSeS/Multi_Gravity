#include "ScreenManager.h"

ScreenManager::ScreenManager() : m_ScreenBuffer(SCREEN_WIDTH * SCREEN_HEIGHT),
                                 m_BackBuffer(SCREEN_WIDTH * SCREEN_HEIGHT)
{
    // 获取控制台输出句柄
    m_ConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    // 设置控制台窗口大小
    SMALL_RECT windowSize = {0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1};
    SetConsoleWindowInfo(m_ConsoleOutput, true, &windowSize);

    // 设置控制台缓冲区大小
    COORD bufferSize = {SCREEN_WIDTH, SCREEN_HEIGHT};
    SetConsoleScreenBufferSize(m_ConsoleOutput, bufferSize);

    Screeninit();
}

void ScreenManager::Screeninit()
{
    // 获取标准输出句柄
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    // 获取控制台窗口大小
    HWND consoleWindow = GetConsoleWindow();
    RECT windowRect;
    GetWindowRect(consoleWindow, &windowRect);
    int windowWidth = windowRect.right - windowRect.left;
    int windowHeight = windowRect.bottom - windowRect.top;

    // 设置控制台屏幕缓冲区大小
    COORD bufferSize = {SCREEN_WIDTH, SCREEN_HEIGHT};
    SetConsoleScreenBufferSize(hConsoleOutput, bufferSize);

    // 设置控制台窗口大小和位置
    SMALL_RECT windowSize = {0, 0, 99, 39};
    SetConsoleWindowInfo(hConsoleOutput, TRUE, &windowSize);
    SetConsoleOutputCP(CP_UTF8);
    // 禁用编辑功能
    DWORD consoleMode;
    GetConsoleMode(hConsoleOutput, &consoleMode);
    consoleMode &= ~ENABLE_QUICK_EDIT_MODE; // 移除快速编辑模式
    SetConsoleMode(hConsoleOutput, consoleMode);
    consoleMode &= ~ENABLE_INSERT_MODE;     // 移除插入模式
    SetConsoleMode(hConsoleOutput, consoleMode);
    consoleMode &= ~ENABLE_MOUSE_INPUT;     // 移除鼠标输入
    SetConsoleMode(hConsoleOutput, consoleMode);

    // 隐藏滚动条
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsoleOutput, &csbi);
    csbi.dwSize.Y = 40;
    csbi.dwSize.X = 100;
    SetConsoleScreenBufferSize(hConsoleOutput, csbi.dwSize);
    SetConsoleMode(hConsoleOutput, consoleMode | CONSOLE_FULLSCREEN_MODE);

    // // 设置窗口样式
    // LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    // style &= ~(WS_SIZEBOX | WS_MAXIMIZEBOX);
    // SetWindowLong(consoleWindow, GWL_STYLE, style);

    // 重置窗口大小和位置
    SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);

    // 获取标准输出句柄
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    // 获取当前字体信息
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hConsoleOutput, FALSE, &fontInfo);

    // 设置字体名称和大小
    wcscpy_s(fontInfo.FaceName, L"Consolas");
    fontInfo.dwFontSize.X = 3;
    fontInfo.dwFontSize.Y = 6;

    // fontInfo.dwFontSize.X = GetSystemMetrics(SM_CXSCREEN) / 8000;
    // fontInfo.dwFontSize.Y = GetSystemMetrics(SM_CYSCREEN) / 2500;

    // 设置字体
    SetCurrentConsoleFontEx(hConsoleOutput, FALSE, &fontInfo);
}

void ScreenManager::ScreenShow(const std::vector<char> &screenBuffer, int width, int height)
{
    ScreenClear();
    // 在屏幕中心输出字符画
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

    // 将字符串输出到控制台
    DWORD bytesWritten;
    WriteConsole(m_ConsoleOutput, outputString.c_str(), outputString.length(), &bytesWritten, NULL);
}