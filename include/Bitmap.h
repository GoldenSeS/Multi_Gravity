#ifndef BITMAP_H
#define BITMAP_H
#include <vector>
#include <string>
#include "Point.h"
#include <fstream>
#include <iostream>
#include <windows.h>
class Bitmap
{
public:
    Bitmap();
    Bitmap(int width, int height, Point position = Point(0, 0));
    // 复制构造函数
    Bitmap(const Bitmap &bitmap);
    Bitmap(const std::string &file_path, Point position = Point(0, 0));
    Bitmap(const std::vector<char> &data, int width, int height, Point position = Point(0, 0));

    // 从指定点，切割指定大小的地图
    Bitmap getSubBitmap(Point position, int width, int height);
    // 从指定点，将指定地图覆盖到当前地图上
    Bitmap overlayMap(const Bitmap &sub_map, Point position);
    // 从文件中加载地图
    void loadAsciiArt(const std::string &file_path);

    void setPixel(Point position, char pixel);
    void set_big_Pixel(Point position, char pixel);
    int getWidth() const;
    int getHeight() const;
    std::vector<char> getData() const;

private:
    Point position;
    int bitmap_width;
    int bitmap_height;
    std::vector<char> bitmap_data;
};

#endif