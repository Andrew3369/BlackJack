#pragma once
#include<iostream>
#include<string>
#include<sstream>

namespace color
{
    enum ansi_color_codes
    {
        black = 30,
        red = 31,
        green = 32,
        yellow = 33,
        blue = 34,
        magenta = 35,
        cyan = 36,
        white = 37,
        bright_black = 90,
        bright_red = 91,
        bright_green = 92,
        bright_yellow = 93,
        bright_blue = 94,
        bright_magenta = 95,
        bright_cyan = 96,
        bright_white = 97,
    };

    template<ansi_color_codes color, typename printable>
    std::string printwithcolor(printable const& value)
    {
        std::stringstream sstr;
        sstr << "\033[1;" << static_cast<int>(color) << "m" << value << "\033[0m";
        return sstr.str();
    }
}