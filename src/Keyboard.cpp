#include "Keyboard.h"

void Keyboard::planeControl(MyPlane &plane, std::list<Bullet> &bullets, short &predict_mode)
{
    // ����������
    while (_kbhit())
    {
        int key = _getch();
        if (key == 0xE0 || key == 0)
        {
            // �����ܼ������
            key = _getch();
            switch (key)
            {
            case 0x48:
                // ��
                plane.accelerate();
                break;
            case 0x50:
                // ��
                plane.decelerate();
                break;
            case 0x4B:
                // ��
                plane.turnLeft();
                break;
            case 0x4D:
                // ��
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
                // �û��涶��һ�£���΢�е����У����и��ƶ༸������������
                // std::cout << std::endl;
                break;
            }
            default:
                break;
            }
            // �ڴ˴�����������,���밴����Ϊ��Ӧ�ַ�
            // �ر��, Enter��keyΪ0x0D('\r'), Backspace��Ϊ0x08, Esc��Ϊ0x1B, Tab��Ϊ0x09
        }
    }
}

void Keyboard::exitOpeningCG(bool &should_exit)
{
    // ����������
    while (_kbhit())
    {
        int key = _getch();
        if (key == 0xE0 || key == 0)
        {
            // �����ܼ������
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
    // ����������
    while (_kbhit())
    {
        int key = _getch();
        if (key == 0xE0 || key == 0)
        {
            // �����ܼ������
            key = _getch();
            switch (key)
            {
            case 0x4B:
                // ��
                {
                    if (intro_index > 1)
                        intro_index--;
                    break;
                }
            case 0x4D:
                // ��
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
            // �ڴ˴�����������,���밴����Ϊ��Ӧ�ַ�
            // �ر��, Enter��keyΪ0x0D('\r'), Backspace��Ϊ0x08, Esc��Ϊ0x1B, Tab��Ϊ0x09
        }
    }
}
