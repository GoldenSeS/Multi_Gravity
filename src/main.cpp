#include "MyPlane.h"
#include "ScreenManager.h"
#include "Bitmap.h"
#include "FixedObject.h"
#include <thread>
#include <chrono>
#include "Keyboard.h"
#include "OrbitPredictor.h"
#include "Bullet.h"
#include "GameManager.h"
#include "Enemy.h"
#include "ColorImage.h"

void clearScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = { 0, 0 };
    SetConsoleCursorPosition(hConsole, coordScreen);
}

void printTips() {
    std::cout << "\nΪ���䲻ͬ��Ļ��С�����ڰ���������󽫿���̨ȫ��\n����CG����ʱ�����ֻ���̫С������ ctrl + ������ ���ڻ����С\n��Esc������������CG\n�������������\n";
    system("pause");
    clearScreen();
}

void simpleShow(std::vector<char> buffer, int width, int height) {
    std::string tem;
    size_t cnt=0;
    for (auto c : buffer) {
        tem += c;
        ++cnt;
        if (cnt % width == 0)
            tem += '\n';
    }
    std::cout << tem;
    std::this_thread::sleep_for(std::chrono::milliseconds(8));
    //system("cls");
    clearScreen();
}

void showSettlementPicture(short game_situation)
{
    if (game_situation == 1)
    {
        ColorImage("colorfulmap/victory.txt").show();
    }
    else
    {
        ColorImage("colorfulmap/defeat.txt").show();
    }
    system("pause");
    exit(0);
}

void gameScene(ScreenManager sm)
{
    short game_situation = 0;
    const int kFrameTime = 16;                                  // ÿ֡ʱ��Ϊ16���룬֡��Ϊ60fps
    auto last_time = std::chrono::high_resolution_clock::now(); // ��¼��һ֡��ʱ��
    // ���س�����ͼ
    Bitmap levelmap("LevelMap/background.txt");
    // ���طɻ�
    MyPlane plane(Point(0, 0), Vector(60, 0), Vector(0, 0), 0, 0, 5, 0.6);
    // ������Ļ������
    sm.EnableVTMode();
    // ���ؼ���
    Keyboard kb;
    // ���ع��Ԥ����
    OrbitPredictor op;
    static short predict_mode = 1;
    // ������Ϸ������
    GameManager gm;
    // ���ع̶�����
    std::list<FixedObject> fixedObjects;
    FixedObject planet1(Point(30, 160), 100, 1000);
    FixedObject planet2(Point(538, 105), 40, 600);
    FixedObject planet3(Point(1110, 65), 60, 1000);
    FixedObject planet4(Point(1020, 240), 60, 1000);
    FixedObject planet5(Point(1730, 155), 105, 1400);

    fixedObjects.push_back(planet1);
    fixedObjects.push_back(planet2);
    fixedObjects.push_back(planet3);
    fixedObjects.push_back(planet4);
    fixedObjects.push_back(planet5);

    // ���صл��б�
    std::list<Enemy> enemies;
    Enemy enemy1(0.1, 0, planet1, 120, 10);
    Enemy enemy2(0.1, PI, planet1, 120, 10);
    Enemy enemy3(0.1, 0, planet2, 70, 10);
    Enemy enemy4(0.1, PI, planet2, 80, 10);
    Enemy enemy5(0.1, PI, planet3, 80, 10);
    Enemy enemy6(0.1, PI, planet4, 80, 10);
    Enemy enemy7(0.1, PI, planet5, 130, 10);
    enemies.push_back(enemy1);
    enemies.push_back(enemy2);
    enemies.push_back(enemy3);
    enemies.push_back(enemy4);
    enemies.push_back(enemy5);
    enemies.push_back(enemy6);
    enemies.push_back(enemy7);

    // �����ӵ��б�
    std::list<Bullet> bullets;

    const int predict_step = 1000;

    // ���ڴ洢��ͼ���ݵĻ�����
    std::vector<char> asciiArtBuffer;
    for (;;)
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time).count();
        last_time = now;
        // ������ʾ��ͼ���߳�
        std::thread screenshow(simpleShow,asciiArtBuffer, SCREEN_WIDTH, SCREEN_HEIGHT);
//        simpleShow(asciiArtBuffer, SCREEN_WIDTH, SCREEN_HEIGHT);

        Bitmap planemap = plane.draw();
        // �и��ͼ����ȡ�ɻ���Χ�ĵ�ͼ
        Bitmap sub_levelmap = levelmap.getSubBitmap(Point(int(plane.getPosition().getX() - planemap.getWidth() * 0.5), int(plane.getPosition().getY() - planemap.getHeight() * 0.5)), SCREEN_WIDTH, SCREEN_HEIGHT);

        // ���Ԥ��
        if (predict_mode == 1)
            op.orbit_predict(plane, predict_step, fixedObjects);
        else
            op.bullet_predict(plane, predict_step, fixedObjects);

        // ����ӵ����ʱ��
        gm.detactBulletLife(bullets);

        // ��ȡ���
        std::list<Point> orbit = op.getOrbitList();

        // ��������ǵ���ͼ��
        for (auto it = orbit.begin(); it != orbit.end(); it++)
        {
            sub_levelmap.setPixel(*it, '*');
        }

        // �ڵ�ͼ�ϻ����ӵ�
        for (auto it = bullets.begin(); it != bullets.end(); it++)
        {
            sub_levelmap.set_big_Pixel(it->getPosition() - plane.getPosition() + Point(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5), 'O');
        }

        // �ڵ�ͼ�ϻ��Ƶл�
        for (auto it = enemies.begin(); it != enemies.end(); it++)
        {
            // sub_levelmap.set_big_Pixel(it->getPosition() - plane.getPosition() + Point(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5), 'E');
            sub_levelmap = sub_levelmap.overlayMap(it->getBitmap(), it->getPosition() - plane.getPosition() + Point(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5) - Point(it->getBitmap().getWidth() * 0.5, it->getBitmap().getHeight() * 0.5));
        }

        // �л��ƶ�
        for (auto it = enemies.begin(); it != enemies.end(); it++)
        {
            it->updateAngle(0.16);
        }

        // // ���������Ļ��Ƶ�
        // for (auto it = fixedObjects.begin(); it != fixedObjects.end(); it++)
        // {
        //     sub_levelmap.set_big_Pixel(it->getCenterPoint() - plane.getPosition() + Point(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5), 'O');
        // }

        // ���ɻ�ͼƬ���ǵ���ͼ��
        Bitmap buffer = sub_levelmap.overlayMap(planemap, Point(SCREEN_WIDTH * 0.5 - planemap.getWidth() + 12, SCREEN_HEIGHT * 0.5 - planemap.getHeight() + 10));

        // �����ײ
        gm.detactCollision(plane, bullets, fixedObjects, enemies, game_situation);

        // ���л��б��Ƿ�Ϊ��
        if (enemies.empty())
        {
            game_situation = 1;
        }

        screenshow.join();
        // ��ȡ���Ǻ�ĵ�ͼ
        asciiArtBuffer = buffer.getData();

        // ���̿���
        kb.planeControl(plane, bullets, predict_mode);

        // ���·ɻ�״̬
        plane.updateSituations(0.016, fixedObjects);

        // �����ӵ�״̬
        for (auto it = bullets.begin(); it != bullets.end(); it++)
        {
            it->updateSituations(0.016, fixedObjects);
        }

        // �����Ϸ״̬
        if (game_situation != 0)
        {
            showSettlementPicture(game_situation);
        }

        // �ȴ���һ֡��ʼ
        if (elapsed_time < kFrameTime)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(kFrameTime - elapsed_time));
        }
    }
}

void openingCG(ScreenManager sm)
{
    Keyboard kb;
    bool should_exit = false;
    Sleep(1000);
    std::vector<char> buffer;
    for(int i = 0; i < 147; i++)
    {
        std::thread screenshow(simpleShow, buffer, SCREEN_WIDTH, SCREEN_HEIGHT);
        Bitmap bitmap("openingCG/frame" + std::to_string(i) + ".txt");
        buffer = bitmap.getData();
        screenshow.join();
        kb.exitOpeningCG(should_exit);
        if (should_exit)
        {
            return;
        }
    }
    system("pause");
    system("cls");
}

void introduction(ScreenManager sm)
{
    Keyboard kb;
    short intro_index = 1;
    std::vector<char> buffer;
    for (;;)
    {
        std::thread screenshowinto(simpleShow, buffer, SCREEN_WIDTH, SCREEN_HEIGHT);
        Bitmap bitmap("Introduction/" + std::to_string(intro_index) + ".txt");
        buffer= bitmap.getData();
        screenshowinto.join();
        kb.introductionControl(intro_index);
        if (intro_index == 0)
            break;
    }
    system("cls");
}

int main()
{   
    printTips();
    ScreenManager sm;
    std::ios::sync_with_stdio(false);
    Sleep(2000);
    openingCG(sm);
    introduction(sm);
    gameScene(sm);
    system("pause");
    return 0;
}