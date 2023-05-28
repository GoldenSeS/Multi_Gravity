#include "Keyboard.h"

void Keyboard::planeControl(MyPlane &plane, std::list<Bullet> &bullets, short &predict_mode)
{
    // 处理按键输入
    while (_kbhit())
    {
        int key = _getch();
        if (key == 0xE0 || key == 0)
        {
            // 处理功能键或方向键
            key = _getch();
            switch (key)
            {
            case 0x48:
                // 上
                plane.accelerate();
                break;
            case 0x50:
                // 下
                plane.decelerate();
                break;
            case 0x4B:
                // 左
                plane.turnLeft();
                break;
            case 0x4D:
                // 右
                plane.turnRight();
                break;
            default:
                break;
            }
        }
        else
        {
            switch (key)
            {
            case 0x1B:
                // Esc
                system("pause");
                break;
            case 0x09:
                // Tab
                predict_mode *= (-1);
                // std::cout << std::endl;
                break;
            case 0x20:
            {
                // space
                bullets.push_back(Bullet(Point(plane.getPosition()), plane.getVelocity() + plane.getAngularVector().getUnitVector() * BULLET_SPEED, plane.getAcceleration(), 5, std::chrono::high_resolution_clock::now()));
                Vector addVelocity = plane.getAngularVector() * -5;
                plane.setPosition(Point(plane.getPosition() + addVelocity.toPoint() * 0.5));
                plane.setVelocity(Vector(plane.getVelocity() + Vector(addVelocity.getXComponent(), addVelocity.getYComponent() * 0.5)));
                // 让画面抖动一下，稍微有点打击感，此行复制多几遍以增大打击感
                // std::cout << std::endl;
                break;
            }
            default:
                break;
            }
            // 在此处处理按键输入,输入按键即为对应字符
            // 特别的, Enter键key为0x0D('\r'), Backspace键为0x08, Esc键为0x1B, Tab键为0x09
        }
    }
}

void Keyboard::exitOpeningCG(bool &should_exit)
{
    // 处理按键输入
    while (_kbhit())
    {
        int key = _getch();
        if (key == 0xE0 || key == 0)
        {
            // 处理功能键或方向键
            key = _getch();
            switch (key)
            {
            default:
                break;
            }
        }
        else
        {
            switch (key)
            {
            case 0x1B:
                // Esc
                should_exit = true;
                break;
            default:
                break;
            }
        }
    }
}

void Keyboard::introductionControl(short &intro_index)
{
    // 处理按键输入
    while (_kbhit())
    {
        int key = _getch();
        if (key == 0xE0 || key == 0)
        {
            // 处理功能键或方向键
            key = _getch();
            switch (key)
            {
            case 0x4B:
                // 左
                {
                    if (intro_index > 1)
                        intro_index--;
                    break;
                }
            case 0x4D:
                // 右
                {
                    if (intro_index < 8)
                        intro_index++;
                    break;
                }
            default:
                break;
            }
        }
        else
        {
            switch (key)
            {
            case 0x1B:
                // Esc
                intro_index = 0;
            default:
                break;
            }
            // 在此处处理按键输入,输入按键即为对应字符
            // 特别的, Enter键key为0x0D('\r'), Backspace键为0x08, Esc键为0x1B, Tab键为0x09
        }
    }
}
