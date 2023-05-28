#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include <fstream>
#include <cmath>
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 150
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004

class ScreenManager
{
public:
    ScreenManager();
    // 屏幕初始化
    void Screeninit();
    // 屏幕显示
    void ScreenShow(const std::vector<char> &screenBuffer, int width, int height);
    // VT输出模式
    bool EnableVTMode();

private:
    // 缓存区清空
    void ScreenClear();
    // 缓存区绘制
    void ScreenDraw(int x, int y, const std::string &text);
    // 缓存区交换
    void SwapBuffer();
    // 屏幕渲染
    void ScreenRender();
    // 获取缓存区索引
    int GetBufferIndex(int x, int y);

    HANDLE m_ConsoleOutput;
    std::vector<char> m_ScreenBuffer;
    std::vector<char> m_BackBuffer;
};

#endif // SCREENMANAGER_H