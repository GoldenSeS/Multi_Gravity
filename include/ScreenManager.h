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
    // ��Ļ��ʼ��
    void Screeninit();
    // ��Ļ��ʾ
    void ScreenShow(const std::vector<char> &screenBuffer, int width, int height);
    // VT���ģʽ
    bool EnableVTMode();

private:
    // ���������
    void ScreenClear();
    // ����������
    void ScreenDraw(int x, int y, const std::string &text);
    // ����������
    void SwapBuffer();
    // ��Ļ��Ⱦ
    void ScreenRender();
    // ��ȡ����������
    int GetBufferIndex(int x, int y);

    HANDLE m_ConsoleOutput;
    std::vector<char> m_ScreenBuffer;
    std::vector<char> m_BackBuffer;
};

#endif // SCREENMANAGER_H