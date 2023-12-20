#pragma once
#include "pch.hpp"
#include <iostream>
namespace YRT
{

	class Fonts
	{
	public:
		void InitializeFonts();
		sf::Texture cueStick;
		sf::Texture background;
		sf::Font Arial;
	private:
	};
}