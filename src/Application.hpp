#pragma once
#include "pch.hpp"
#include "Renderer.hpp"
#include <memory>
namespace YRT
{
	class Application
	{
	public:

		Application(int width, int height, const char* title);
		~Application();
		void Run();

		bool m_isPlaying;
		bool m_gameWindowOpen;
	private:
		std::unique_ptr<Renderer> m_Renderer;

		sf::RenderWindow window;
		void Update();
		void VariableInitialization();
	};
}
