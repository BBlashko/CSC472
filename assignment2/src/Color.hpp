#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>
#include <vector>

namespace assignment2
{
    class Color
    {
    public:
        Color() : _red(0.5), _green(0.5), _blue(0.5) {};
        Color(double red, double green, double blue) : _red(red), _green(green), _blue(blue) {};
        Color(double red, double green, double blue, double specular) : _red(red), _green(green), _blue(blue), _specular(specular) {};

        //deconstructor? needed?
        ~Color() {};

        double red() const { return _red; };
        double green() const { return _green; };
        double blue() const { return _blue; };
        double specular() const { return _specular; };

        void setRed(double red) { _red = red; };
        void setGreen(double green) { _green = green; };
        void setBlue(double blue) { _blue = blue; };
        void setSpecular(double specular) { _specular = specular; };

        double brightness() { return (_red + _green + _blue) / 3; };

        Color operator+() { return *this; };
        Color operator-() { return Color(-_red, -_green, -_blue); };

        void clamp()
        {
            if (_red > 1) { _red = 1; };
            if (_green > 1) { _green = 1; };
            if (_blue > 1) { _blue = 1; };
            if (_red < 0) { _red = 0; };
            if (_green < 0) { _green = 0; };
            if (_blue < 0) { _blue = 0; };
        }

        void remove_excess_light()
        {
            double all_light = _red + _green + _blue;
            double excess_light = all_light - 3;
            if (excess_light > 0)
            {
                _red = _red + excess_light * (_red / all_light);
                _green = _green + excess_light * (_green / all_light);
                _blue = _blue + excess_light * (_blue / all_light);
            }

            clamp();
        }
    private:
        double _red, _green, _blue, _specular;
    };

    Color operator*(const float k, const Color& a);
    Color operator*(const Color& a, const float k);
    Color operator/(const Color& a, const float k);

    Color operator+(const Color& a, const Color& b);
    Color operator-(const Color& a, const Color& b);
    Color operator*(const Color& a, const Color& b);
    Color operator/(const Color& a, const Color& b);

    void operator+=(Color& a, const Color& b);
    void operator-=(Color& a, const Color& b);
    void operator*=(Color& a, const Color& b);
    void operator/=(Color& a, const Color& b);

    Color average_colors(const std::vector<Color> colors);
    std::ostream& operator<<(std::ostream& outStream, const Color& v);

#endif#pragma once

}
