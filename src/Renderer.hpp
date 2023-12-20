#pragma once
#include "pch.hpp"
#include "AccManagement.hpp"
#include "Fonts.hpp"
namespace YRT
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void MainMenu(sf::RenderWindow& window, bool& isPlaying);
		void LogInWindow(sf::RenderWindow& window);
		void RegisterWindow(sf::RenderWindow& window);
		void HandleEvents(sf::RenderWindow& window, bool& windowOpen);
		void GameWindow(sf::RenderWindow& window);

	private:
		std::unique_ptr<AccManagement> accmanagement;
		std::unique_ptr<Fonts> fonts;

		sf::RectangleShape m_LogInButton;
		sf::RectangleShape m_RegisterButton;

		sf::RectangleShape m_LogInUsernameField;
		sf::RectangleShape m_LogInPasswordField;

		sf::RectangleShape m_RegisterField;

		sf::RectangleShape m_LogInConfirmButton;
		sf::RectangleShape m_RegisterConfirmButton;

		sf::Text m_LogInUsernameText;
		sf::Text m_LogInPasswordText;

		sf::Vector2i m_MousePos;

		sf::Text m_LogInText;
		sf::Text m_RegisterText;
		sf::Text m_EnteringUsernameText;

		bool m_MainMenuWindowOpen;
		bool m_GameWindowOpen;
		bool m_LogInWindowOpen;
		bool m_RegisterWindowOpen;
		bool m_EnteringUsername;

		std::string m_UsernameInput;
		std::string m_PasswordInput;

		char m_typedChar;

		sf::Sprite m_background;

		std::string m_logusername;
		void handleTextInput(const sf::Event& event, std::string& inputText, sf::Text& displayText, sf::RectangleShape& inputField, bool& notEnoughSpace, sf::Clock& cursorClock);
		void handleCursorBlinking(sf::Text& displayText, const std::string& inputText, const sf::RectangleShape& inputField, bool isFieldClicked, sf::Clock& cursorClock, sf::RenderWindow& window);
		void displayErrorMessage(sf::RenderWindow& window, const sf::RectangleShape& inputField, const std::string& message);
	};
}