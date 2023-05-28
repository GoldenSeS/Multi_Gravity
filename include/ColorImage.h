#ifndef COLORIMAGE_H
#define COLORIMAGE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

struct Pixel
{
    char ch;
    int red, green, blue;
    Pixel(char c = ' ', int r = 0, int g = 0, int b = 0) : ch(c), red(r), green(g), blue(b) {}
};

class ColorImage
{
public:
    ColorImage(const std::string &filename);
    void setPixel(int x, int y, Pixel p);
    Pixel getPixel(int x, int y) const;
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    void show();

private:
    int width, height;
    std::vector<Pixel> data;
};

#endif // COLORIMAGE_H