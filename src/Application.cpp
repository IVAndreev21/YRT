#include "pch.hpp"
#include "Application.hpp"
namespace YRT
{
    Application::Application(int width, int height, const char* title)
        : window(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close),
        m_isPlaying(false) {

        VariableInitialization();
        window.setFramerateLimit(60);
    }

    Application::~Application() {}

    void Application::VariableInitialization() {
        m_Renderer = std::make_unique<Renderer>();
    }

    void Application::Update() {

        if (!m_isPlaying) {
            // Render to the main window
            m_Renderer->MainMenu(window, m_isPlaying);

            // Render to the game window only when the condition is met
            if (m_isPlaying) {
                m_Renderer->GameWindow(window);
            }
        }
    }

    void Application::Run() {
        while (window.isOpen()) {
            Update();
        }
    }
}