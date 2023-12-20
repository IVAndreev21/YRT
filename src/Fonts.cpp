#include "Fonts.hpp"
namespace YRT
{
    void Fonts::InitializeFonts() {
        if (Arial.loadFromFile("../res/fonts/Arial/arial.ttf"))
            return;
        std::cout << "font not loaded";
    }
}