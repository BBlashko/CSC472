#include "Color.hpp"

namespace assignment2
{

    Color operator*(const float k, const Color& a)
    {
        return Color(k * a.red(), k * a.green(), k * a.blue(), a.specular());
    }

    Color operator*(const Color& a, const float k)
    {
        return Color(k * a.red(), k * a.green(), k * a.blue(), a.specular());
    }

    Color operator/(const Color& a, const float k)
    {
        return Color(a.red() / k, a.green() / k, a.blue() / k, a.specular());
    }

    Color operator+(const Color& a, const Color& b)
    {
        return Color(a.red() + b.red(), a.green() + b.green(), a.blue() + b.blue(), a.specular());
    }

    Color operator-(const Color& a, const Color& b)
    {
        return Color(a.red() - b.red(), a.green() - b.green(), a.blue() - b.blue(), a.specular());
    }

    Color operator*(const Color& a, const Color& b)
    {
        return Color(a.red() * b.red(), a.green() * b.green(), a.blue() * b.blue(), a.specular());
    }

    Color operator/(const Color& a, const Color& b)
    {
        return Color(a.red() / b.red(), a.green() / b.green(), a.blue() / b.blue(), a.specular());
    }

    void operator+=(Color& a, const Color& b)
    {
        a = Color(a.red() + b.red(), a.green() + b.green(), a.blue() + b.blue(), a.specular());
    }

    void operator-=(Color& a, const Color& b)
    {
        a = Color(a.red() - b.red(), a.green() - b.green(), a.blue() - b.blue(), a.specular());
    }

    void operator*=(Color& a, const Color& b)
    {
        a = Color(a.red() * b.red(), a.green() * b.green(), a.blue() * b.blue(), a.specular());
    }

    void operator/=(Color& a, const Color& b)
    {
        a = Color(a.red() / b.red(), a.green() / b.green(), a.blue() / b.blue(), a.specular());
    }

    Color average_colors(const std::vector<Color> colors)
    {
        Color average_color = Color(0, 0, 0, 0);
        for (unsigned a = 0; a < colors.size(); a++)
        {
            average_color += colors[a];
        }
        average_color = average_color / colors.size();
        return average_color;
    }

    std::ostream& operator<<(std::ostream& outStream, const Color& a)
    {
        outStream << a.red() << " " << a.green() << " " << a.blue() << " " << a.specular();
        return outStream;
    }
}
