#include "ColorImage.h"

ColorImage::ColorImage(const std::string &filename)
{
    std::ifstream fin(filename);
    if (!fin)
    {
        std::cerr << "Error: failed to open file " << filename << std::endl;
        return;
    }

    fin >> width >> height;

    data.resize(width * height);

    for (int i = 0; i < width * height; i++)
    {
        char c;
        int r, g, b;
        fin >> c >> r >> g >> b;
        data[i] = Pixel(c, r, g, b);
    }

    fin.close();
}

void ColorImage::setPixel(int x, int y, Pixel p)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        data[y * width + x] = p;
    }
}

Pixel ColorImage::getPixel(int x, int y) const
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        return data[y * width + x];
    }
    else
    {
        return Pixel();
    }
}

void ColorImage::show()
{
    std::string buffer = "";
    for (int y = 0; y < getHeight(); ++y)
    {
        for (int x = 0; x < getWidth()-10; ++x)
        {
            Pixel p = getPixel(x, y);
            std::string tem = "\033[38;2;" + std::to_string(p.red) + ";" + std::to_string(p.green) + ";" + std::to_string(p.blue) + "m" + "#";
            buffer += tem;
        }
        buffer += '\n';
    }
    std::cout << buffer;
}
