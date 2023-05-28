#include "Bitmap.h"

Bitmap::Bitmap():position(Point(0, 0))
{
    bitmap_width = 0;
    bitmap_height = 0;
}

Bitmap::Bitmap(int width, int height, Point position):position(position)
{
    bitmap_width = width;
    bitmap_height = height;
    for (int i = 0; i < width * height; i++)
    {
        bitmap_data.push_back(' ');
    }
}

Bitmap::Bitmap(const Bitmap &bitmap):position(bitmap.position)
{
    bitmap_width = bitmap.bitmap_width;
    bitmap_height = bitmap.bitmap_height;
    bitmap_data = bitmap.bitmap_data;
}

Bitmap::Bitmap(const std::string &file_path, Point position) : position(position)
{
    loadAsciiArt(file_path);
}

Bitmap::Bitmap(const std::vector<char> &data, int width, int height, Point position):position(position)
{
    bitmap_data = data;
    bitmap_width = width;
    bitmap_height = height;
}

Bitmap Bitmap::getSubBitmap(Point position, int width, int height) 
{
    Bitmap sub_map;
    sub_map.bitmap_width = width;
    sub_map.bitmap_height = height;
    for (int i = position.getY(); i < position.getY() + height; i++)
    {
        for (int j = position.getX(); j < position.getX() + width; j++)
        {
            if (i < 0 || i >= bitmap_height || j < 0 || j >= bitmap_width)
            {
                sub_map.bitmap_data.push_back(' ');
            }
            else
            {
                sub_map.bitmap_data.push_back(bitmap_data[i * bitmap_width + j]);
            }
        }
        // sub_map_data.push_back('\n');
    }
    return Bitmap(sub_map.bitmap_data, sub_map.bitmap_width, sub_map.bitmap_height, position);
}

Bitmap Bitmap::overlayMap(const Bitmap &sub_map, Point position)
{
    Bitmap temp = *this;
    if (position.getX() < 0 || position.getY() < 0 || position.getX() + sub_map.getWidth() > this->getWidth() || position.getY() + sub_map.getHeight() > this->getData().size() / this->getWidth())
    {
        return temp;
    }
    int y = position.getY();
    int x = position.getX();
    int sub_map_width = sub_map.getWidth();
    int sub_map_height = sub_map.getHeight();
    int temp_width = temp.getWidth();
    for (int i = y; i < y + sub_map_height; i++)
    {
        for (int j = x; j < x + sub_map_width; j++)
        {
            char c = sub_map.getData()[(i - y) * sub_map_width + (j - x)];
            if (c != ' ')
            {
                temp.setPixel(Point(j, i), c);
            }
        }
    }
    return temp;
}

void Bitmap::loadAsciiArt(const std::string &file_path)
{
    std::ifstream file(file_path);

    if (!file)
    {
        std::cout << "Error: Cannot open file \"" << file_path << "\".\n";
        system("pause");
        HANDLE hself = GetCurrentProcess();
        TerminateProcess(hself, 0);
    }

    std::string line;
    while (getline(file, line))
    {
        this->bitmap_width = (int)line.length();
        for (int i = 0; i < line.length(); i++)
        {
            this->bitmap_data.push_back(line[i]);
        }
    }

    this->bitmap_height = this->bitmap_data.size() / this->bitmap_width;
}

void Bitmap::setPixel(Point position, char pixel)
{
    if (position.getX() < 1 || position.getY() < 1 || position.getX() >= bitmap_width-1 || position.getY() >= bitmap_height-1)
    {
        return;
    }
    bitmap_data[int(position.getY()) * bitmap_width + int(position.getX())] = pixel;
}

void Bitmap::set_big_Pixel(Point position, char pixel)
{
    this->setPixel(Point(position.getX(),position.getY()), pixel);
    this->setPixel(Point(position.getX()+1,position.getY()), pixel);
    this->setPixel(Point(position.getX()-1,position.getY()), pixel);
    this->setPixel(Point(position.getX(),position.getY()+1), pixel);
    this->setPixel(Point(position.getX()+1,position.getY()+1), pixel);
    this->setPixel(Point(position.getX()-1,position.getY()+1), pixel);
}

int Bitmap::getWidth() const
{
    return bitmap_width;
}

int Bitmap::getHeight() const
{
    return bitmap_height;
}

std::vector<char> Bitmap::getData() const
{
    return bitmap_data;
}
