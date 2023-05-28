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
    std::cout << "\n为适配不同屏幕大小，请在按下任意键后将控制台全屏\n播放CG动画时若发现画面太小，请用 ctrl + 鼠标滚轮 调节画面大小\n按Esc可以跳过开场CG\n按下任意键继续\n";
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
    const int kFrameTime = 16;                                  // 每帧时长为16毫秒，帧率为60fps
    auto last_time = std::chrono::high_resolution_clock::now(); // 记录上一帧的时间
    // 加载场景地图
    Bitmap levelmap("LevelMap/background.txt");
    // 加载飞机
    MyPlane plane(Point(0, 0), Vector(60, 0), Vector(0, 0), 0, 0, 5, 0.6);
    // 加载屏幕管理器
    sm.EnableVTMode();
    // 加载键盘
    Keyboard kb;
    // 加载轨道预测器
    OrbitPredictor op;
    static short predict_mode = 1;
    // 加载游戏管理器
    GameManager gm;
    // 加载固定物体
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

    // 加载敌机列表
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

    // 加载子弹列表
    std::list<Bullet> bullets;

    const int predict_step = 1000;

    // 用于存储地图数据的缓冲区
    std::vector<char> asciiArtBuffer;
    for (;;)
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time).count();
        last_time = now;
        // 用于显示地图的线程
        std::thread screenshow(simpleShow,asciiArtBuffer, SCREEN_WIDTH, SCREEN_HEIGHT);
//        simpleShow(asciiArtBuffer, SCREEN_WIDTH, SCREEN_HEIGHT);

        Bitmap planemap = plane.draw();
        // 切割地图，获取飞机周围的地图
        Bitmap sub_levelmap = levelmap.getSubBitmap(Point(int(plane.getPosition().getX() - planemap.getWidth() * 0.5), int(plane.getPosition().getY() - planemap.getHeight() * 0.5)), SCREEN_WIDTH, SCREEN_HEIGHT);

        // 轨道预测
        if (predict_mode == 1)
            op.orbit_predict(plane, predict_step, fixedObjects);
        else
            op.bullet_predict(plane, predict_step, fixedObjects);

        // 检测子弹存活时间
        gm.detactBulletLife(bullets);

        // 获取轨道
        std::list<Point> orbit = op.getOrbitList();

        // 将轨道覆盖到地图上
        for (auto it = orbit.begin(); it != orbit.end(); it++)
        {
            sub_levelmap.setPixel(*it, '*');
        }

        // 在地图上绘制子弹
        for (auto it = bullets.begin(); it != bullets.end(); it++)
        {
            sub_levelmap.set_big_Pixel(it->getPosition() - plane.getPosition() + Point(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5), 'O');
        }

        // 在地图上绘制敌机
        for (auto it = enemies.begin(); it != enemies.end(); it++)
        {
            // sub_levelmap.set_big_Pixel(it->getPosition() - plane.getPosition() + Point(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5), 'E');
            sub_levelmap = sub_levelmap.overlayMap(it->getBitmap(), it->getPosition() - plane.getPosition() + Point(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5) - Point(it->getBitmap().getWidth() * 0.5, it->getBitmap().getHeight() * 0.5));
        }

        // 敌机移动
        for (auto it = enemies.begin(); it != enemies.end(); it++)
        {
            it->updateAngle(0.16);
        }

        // // 在星球中心绘制点
        // for (auto it = fixedObjects.begin(); it != fixedObjects.end(); it++)
        // {
        //     sub_levelmap.set_big_Pixel(it->getCenterPoint() - plane.getPosition() + Point(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5), 'O');
        // }

        // 将飞机图片覆盖到地图上
        Bitmap buffer = sub_levelmap.overlayMap(planemap, Point(SCREEN_WIDTH * 0.5 - planemap.getWidth() + 12, SCREEN_HEIGHT * 0.5 - planemap.getHeight() + 10));

        // 检测碰撞
        gm.detactCollision(plane, bullets, fixedObjects, enemies, game_situation);

        // 检测敌机列表是否为空
        if (enemies.empty())
        {
            game_situation = 1;
        }

        screenshow.join();
        // 获取覆盖后的地图
        asciiArtBuffer = buffer.getData();

        // 键盘控制
        kb.planeControl(plane, bullets, predict_mode);

        // 更新飞机状态
        plane.updateSituations(0.016, fixedObjects);

        // 更新子弹状态
        for (auto it = bullets.begin(); it != bullets.end(); it++)
        {
            it->updateSituations(0.016, fixedObjects);
        }

        // 检测游戏状态
        if (game_situation != 0)
        {
            showSettlementPicture(game_situation);
        }

        // 等待下一帧开始
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