#ifndef THEME_HPP
#define THEME_HPP

#include <raylib.h>
#include <string>

namespace Theme {
    struct Colors {
        Color background;
        Color defaultBar;
        Color comparing;
        Color swapping;
        Color sorted;
        Color pivot;
        Color comparingAlt;
        Color done;
    };

    std::string getCurrentThemeName();
    Colors getThemeColors(const std::string& themeName);
    Colors getDefaultColors();
}

#endif