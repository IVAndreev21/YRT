#include "Renderer.hpp"
#include <iostream>
namespace YRT
{
    Renderer::Renderer()
    {
        fonts = std::make_unique<Fonts>();
        accmanagement = std::make_unique<AccManagement>();
        fonts->InitializeFonts();
        accmanagement->ConnectToDatabaseServer();
    }

    Renderer::~Renderer()
    {

    }

    void Renderer::HandleEvents(sf::RenderWindow& window, bool& windowOpen) {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                windowOpen = false;

                break;
            default:
                break;
            }
        }
    }


    void Renderer::MainMenu(sf::RenderWindow& window, bool& isPlaying)
    {
        window.clear(sf::Color::White);
        HandleEvents(window, isPlaying);
        m_LogInButton.setSize(sf::Vector2f(200.0f, 50.0f));
        m_LogInButton.setFillColor(sf::Color::Black);
        m_LogInButton.setPosition(sf::Vector2f(100.0f, 200.0f));
        m_LogInButton.setOutlineThickness(5.0f);
        m_LogInButton.setOutlineColor(sf::Color::Blue);

        // Center the text within the rectangle
        m_LogInText.setString("Log In");
        m_LogInText.setFillColor(sf::Color::White);
        m_LogInText.setCharacterSize(20);
        m_LogInText.setFont(fonts->Arial);

        sf::FloatRect textBounds = m_LogInText.getLocalBounds();
        sf::Vector2f buttonPosition = m_LogInButton.getPosition();

        m_LogInText.setPosition(buttonPosition.x + (m_LogInButton.getSize().x - textBounds.width) / 2,
            buttonPosition.y + (m_LogInButton.getSize().y - textBounds.height) / 2);


        m_RegisterButton.setSize(sf::Vector2f(200.0f, 50.0f));
        m_RegisterButton.setFillColor(sf::Color::Black);
        m_RegisterButton.setPosition(sf::Vector2f(400.0f, 200.0f));
        m_RegisterButton.setOutlineThickness(5.0f);
        m_RegisterButton.setOutlineColor(sf::Color::Blue);

        m_RegisterText.setString("Register");
        textBounds = m_RegisterText.getLocalBounds();
        buttonPosition = m_RegisterButton.getPosition();

        // Center the text within the rectangle
        m_RegisterText.setPosition(buttonPosition.x + (m_RegisterButton.getSize().x - textBounds.width) / 2,
            buttonPosition.y + (m_RegisterButton.getSize().y - textBounds.height) / 2);
        m_RegisterText.setFillColor(sf::Color::White);
        m_RegisterText.setCharacterSize(20);
        m_RegisterText.setFont(fonts->Arial);

        m_MousePos = sf::Mouse::getPosition(window);

        if (m_LogInButton.getGlobalBounds().contains(sf::Vector2f(m_MousePos)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            m_LogInWindowOpen = true;
            LogInWindow(window);

        }
        else if (m_RegisterButton.getGlobalBounds().contains(sf::Vector2f(m_MousePos)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            m_RegisterWindowOpen = true;
            RegisterWindow(window);

        }
        window.draw(m_LogInButton);
        window.draw(m_RegisterButton);
        window.draw(m_LogInText);
        window.draw(m_RegisterText);
        window.display();
    }
    void Renderer::RegisterWindow(sf::RenderWindow& window)
    {
        sf::Text email; // Text for the first input field
        sf::Text emailD; // Text for the first input field
        email.setFont(fonts->Arial);
        email.setCharacterSize(24);
        email.setFillColor(sf::Color::Black);
        emailD.setFont(fonts->Arial);
        emailD.setCharacterSize(24);
        emailD.setFillColor(sf::Color::Black);
        emailD.setString("EMail");


        sf::Text username; // Text for the second input field
        sf::Text usernameD; //D for display
        username.setFont(fonts->Arial);
        username.setCharacterSize(24);
        username.setFillColor(sf::Color::Black);
        usernameD.setFont(fonts->Arial);
        usernameD.setCharacterSize(24);
        usernameD.setFillColor(sf::Color::Black);
        usernameD.setString("Username");

        sf::Text password; // Text for the third input field
        sf::Text passwordD; // Text for the third input field
        password.setFont(fonts->Arial);
        password.setCharacterSize(24);
        password.setFillColor(sf::Color::Black);
        passwordD.setFont(fonts->Arial);
        passwordD.setCharacterSize(24);
        passwordD.setFillColor(sf::Color::Black);
        passwordD.setString("Password");

        sf::RectangleShape inputFieldEmail(sf::Vector2f(350.f, 40.f));
        inputFieldEmail.setPosition(250.f, 250.f);
        inputFieldEmail.setFillColor(sf::Color::White);
        inputFieldEmail.setOutlineColor(sf::Color::Black);
        inputFieldEmail.setOutlineThickness(2.f);

        sf::RectangleShape inputFieldUsername(sf::Vector2f(300.f, 40.f));
        inputFieldUsername.setPosition(250.f, 320.f);
        inputFieldUsername.setFillColor(sf::Color::White);
        inputFieldUsername.setOutlineColor(sf::Color::Black);
        inputFieldUsername.setOutlineThickness(2.f);

        sf::RectangleShape inputFieldPassword(sf::Vector2f(300.f, 40.f));
        inputFieldPassword.setPosition(250.f, 390.f);
        inputFieldPassword.setFillColor(sf::Color::White);
        inputFieldPassword.setOutlineColor(sf::Color::Black);
        inputFieldPassword.setOutlineThickness(2.f);

        emailD.setPosition(inputFieldEmail.getPosition().x + 100, inputFieldEmail.getPosition().y - 35);
        usernameD.setPosition(inputFieldUsername.getPosition().x + 100, inputFieldUsername.getPosition().y - 35);
        passwordD.setPosition(inputFieldPassword.getPosition().x + 100, inputFieldPassword.getPosition().y - 35);

        sf::RectangleShape button(sf::Vector2f(100.f, 50.f));
        sf::Text buttonD;
        button.setPosition(400.f, 470.f);
        button.setFillColor(sf::Color::Green);

        buttonD.setFont(fonts->Arial);
        buttonD.setCharacterSize(24);
        buttonD.setFillColor(sf::Color::Black);
        buttonD.setPosition(button.getPosition().x, button.getPosition().y);
        buttonD.setString("Submit");


        std::string inputTextEmail;
        std::string inputTextUsername;
        std::string inputTextPassword;

        sf::Clock cursorClockEmail;
        sf::Clock cursorClockUsername;
        sf::Clock cursorClockPassword;

        bool isFieldEmailClicked = false;
        bool isFieldUsernameClicked = false;
        bool isFieldPasswordClicked = false;
        bool notEnoughSpaceUsername = false;
        bool notEnoughSpaceEmail = false;
        bool notEnoughSpacePassword = false;
        bool isButtonClicked = false;

        while (m_RegisterWindowOpen) {
            window.clear(sf::Color::White);
            m_MousePos = sf::Mouse::getPosition(window);
            sf::Event event;
            if (window.pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    m_RegisterWindowOpen = false;
                    break;
                case sf::Event::MouseButtonPressed:
                    // Check which input field is clicked
                    if (inputFieldEmail.getGlobalBounds().contains(sf::Vector2f(m_MousePos))) {
                        isFieldEmailClicked = true;
                        isFieldUsernameClicked = false;
                        isFieldPasswordClicked = false;
                    }
                    else if (inputFieldUsername.getGlobalBounds().contains(sf::Vector2f(m_MousePos))) {
                        isFieldEmailClicked = false;
                        isFieldUsernameClicked = true;
                        isFieldPasswordClicked = false;
                    }
                    else if (inputFieldPassword.getGlobalBounds().contains(sf::Vector2f(m_MousePos))) {
                        isFieldEmailClicked = false;
                        isFieldUsernameClicked = false;
                        isFieldPasswordClicked = true;
                    }
                    else {
                        isFieldEmailClicked = false;
                        isFieldUsernameClicked = false;
                        isFieldPasswordClicked = false;
                    }

                    if (button.getGlobalBounds().contains(sf::Vector2f(m_MousePos))) {
                        isButtonClicked = true;
                    }
                    break;
                case sf::Event::TextEntered:
                    // Handle text input for the appropriate field
                    if (isFieldEmailClicked && !notEnoughSpaceUsername && event.text.unicode < 128) {
                        handleTextInput(event, inputTextEmail, email, inputFieldEmail, notEnoughSpaceUsername, cursorClockEmail);
                    }
                    else if (isFieldUsernameClicked && !notEnoughSpaceEmail && event.text.unicode < 128) {
                        handleTextInput(event, inputTextUsername, username, inputFieldUsername, notEnoughSpaceEmail, cursorClockUsername);
                    }
                    else if (isFieldPasswordClicked && !notEnoughSpacePassword && event.text.unicode < 128) {
                        handleTextInput(event, inputTextPassword, password, inputFieldPassword, notEnoughSpacePassword, cursorClockPassword);
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    if (isButtonClicked) {
                        std::cout << "Final Message 1 (Email): " << inputTextEmail << std::endl;
                        std::cout << "Final Message 2 (Username): " << inputTextUsername << std::endl;
                        std::cout << "Final Message 3 (Password): " << inputTextPassword << std::endl;
                        accmanagement->RegisterAccount(inputTextEmail, inputTextUsername, inputTextPassword);
                        // Insert your data handling logic here
                        isButtonClicked = false;
                    }
                    break;
                }
            }

            handleCursorBlinking(email, inputTextEmail, inputFieldEmail, isFieldEmailClicked, cursorClockEmail, window);
            handleCursorBlinking(username, inputTextUsername, inputFieldUsername, isFieldUsernameClicked, cursorClockUsername, window);
            handleCursorBlinking(password, inputTextPassword, inputFieldPassword, isFieldPasswordClicked, cursorClockPassword, window);

            window.draw(inputFieldEmail);
            window.draw(email);

            window.draw(inputFieldUsername);
            window.draw(username);

            window.draw(inputFieldPassword);
            window.draw(password);

            window.draw(button);

            window.draw(emailD);
            window.draw(usernameD);
            window.draw(passwordD);
            window.draw(buttonD);

            if (notEnoughSpaceUsername) {
                displayErrorMessage(window, inputFieldEmail, "Not enough space!");
            }

            if (notEnoughSpaceEmail) {
                displayErrorMessage(window, inputFieldUsername, "Not enough space!");
            }

            if (notEnoughSpacePassword) {
                displayErrorMessage(window, inputFieldPassword, "Not enough space!");
            }

            window.display();
        }
    }


    void Renderer::LogInWindow(sf::RenderWindow& window)
    {
        sf::Text username; // Text for the first input field
        sf::Text usernameD; // Text for the first input field
        username.setFont(fonts->Arial);
        username.setCharacterSize(24);
        username.setFillColor(sf::Color::Black);
        usernameD.setFont(fonts->Arial);
        usernameD.setCharacterSize(24);
        usernameD.setFillColor(sf::Color::Black);
        usernameD.setString("Username");

        sf::Text password; // Text for the second input field
        sf::Text passwordD;
        password.setFont(fonts->Arial);
        password.setCharacterSize(24);
        password.setFillColor(sf::Color::Black);
        passwordD.setFont(fonts->Arial);
        passwordD.setCharacterSize(24);
        passwordD.setFillColor(sf::Color::Black);
        passwordD.setString("Password");

        sf::RectangleShape inputFieldUsername(sf::Vector2f(300.f, 40.f));
        inputFieldUsername.setPosition(250.f, 250.f);
        inputFieldUsername.setFillColor(sf::Color::White);
        inputFieldUsername.setOutlineColor(sf::Color::Black);
        inputFieldUsername.setOutlineThickness(2.f);

        sf::RectangleShape inputFieldPassword(sf::Vector2f(300.f, 40.f));
        inputFieldPassword.setPosition(250.f, 320.f);
        inputFieldPassword.setFillColor(sf::Color::White);
        inputFieldPassword.setOutlineColor(sf::Color::Black);
        inputFieldPassword.setOutlineThickness(2.f);

        sf::RectangleShape button(sf::Vector2f(100.f, 50.f));
        button.setPosition(400.f, 400.f);
        button.setFillColor(sf::Color::Green);

        sf::Text buttonD;
        buttonD.setFont(fonts->Arial);
        buttonD.setCharacterSize(24);
        buttonD.setFillColor(sf::Color::Black);
        buttonD.setPosition(button.getPosition().x, button.getPosition().y);
        buttonD.setString("Submit");

        std::string inputTextUsername;
        std::string inputTextPassword;

        sf::Clock cursorClockUsername;
        sf::Clock cursorClockPassword;

        bool isField1Clicked = false;
        bool isField2Clicked = false;
        bool notEnoughSpaceUsername = false;
        bool notEnoughSpacePassword = false;
        bool isButtonClicked = false;

        while (m_LogInWindowOpen) {
            window.clear(sf::Color::White);
            m_MousePos = sf::Mouse::getPosition(window);
            sf::Event event;
            if (window.pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    m_LogInWindowOpen = false;
                    break;
                case sf::Event::MouseButtonPressed:
                    // Check which input field is clicked
                    if (inputFieldUsername.getGlobalBounds().contains(sf::Vector2f(m_MousePos))) {
                        isField1Clicked = true;
                        isField2Clicked = false;
                    }
                    else if (inputFieldPassword.getGlobalBounds().contains(sf::Vector2f(m_MousePos))) {
                        isField1Clicked = false;
                        isField2Clicked = true;
                    }
                    else {
                        isField1Clicked = false;
                        isField2Clicked = false;
                    }

                    if (button.getGlobalBounds().contains(sf::Vector2f(m_MousePos))) {
                        isButtonClicked = true;

                    }
                    break;
                case sf::Event::TextEntered:
                    // Handle text input for the appropriate field
                    if (isField1Clicked && !notEnoughSpaceUsername && event.text.unicode < 128) {
                        handleTextInput(event, inputTextUsername, username, inputFieldUsername, notEnoughSpaceUsername, cursorClockUsername);
                    }
                    else if (isField2Clicked && !notEnoughSpacePassword && event.text.unicode < 128) {
                        handleTextInput(event, inputTextPassword, password, inputFieldPassword, notEnoughSpacePassword, cursorClockPassword);
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    if (isButtonClicked) {
                        if (accmanagement->VerifyAccount(inputTextUsername, inputTextPassword))
                        {
                            std::cout << "Log in successful\n";
                            m_GameWindowOpen = true;
                            GameWindow(window);

                            std::cout << inputTextUsername;
                        }
                        else
                        {
                            std::cout << "Username or password is incorrect\n";
                        }
                        isButtonClicked = false;
                    }
                    break;
                }
            }
            usernameD.setPosition(inputFieldUsername.getPosition().x + 100, inputFieldUsername.getPosition().y - 35);
            passwordD.setPosition(inputFieldPassword.getPosition().x + 100, inputFieldPassword.getPosition().y - 35);

            handleCursorBlinking(username, inputTextUsername, inputFieldUsername, isField1Clicked, cursorClockUsername, window);
            handleCursorBlinking(password, inputTextPassword, inputFieldPassword, isField2Clicked, cursorClockPassword, window);

            window.draw(inputFieldUsername);
            window.draw(username);

            window.draw(inputFieldPassword);
            window.draw(password);

            window.draw(button);
            window.draw(usernameD);
            window.draw(passwordD);
            window.draw(buttonD);

            if (notEnoughSpaceUsername) {
                displayErrorMessage(window, inputFieldUsername, "Not enough space!");
            }

            if (notEnoughSpacePassword) {
                displayErrorMessage(window, inputFieldPassword, "Not enough space!");
            }

            window.display();
        }
    }

    void Renderer::displayErrorMessage(sf::RenderWindow& window, const sf::RectangleShape& inputField, const std::string& message)
    {
        sf::Text errorMessage(message, fonts->Arial, 24);
        errorMessage.setFillColor(sf::Color::Red);
        errorMessage.setPosition(inputField.getPosition().x, inputField.getPosition().y + inputField.getSize().y + 5);
        window.draw(errorMessage);
    }
    void Renderer::handleTextInput(const sf::Event& event, std::string& inputText, sf::Text& displayText, sf::RectangleShape& inputField, bool& notEnoughSpace, sf::Clock& cursorClock)
    {
        if (event.text.unicode == 8) {
            if (!inputText.empty()) {
                inputText.pop_back();
            }
        }
        else {
            inputText += static_cast<char>(event.text.unicode);
        }

        displayText.setString(inputText);

        if (displayText.getLocalBounds().width > inputField.getSize().x - 10) {
            notEnoughSpace = true;
        }

        cursorClock.restart();
    }

    void Renderer::handleCursorBlinking(sf::Text& displayText, const std::string& inputText, const sf::RectangleShape& inputField, bool isFieldClicked, sf::Clock& cursorClock, sf::RenderWindow& window)
    {
        if (isFieldClicked && cursorClock.getElapsedTime().asSeconds() > 0.5) {
            displayText.setString(inputText + (displayText.getString()[inputText.length()] == '|' ? "" : "|"));
            cursorClock.restart();
        }

        displayText.setPosition(inputField.getPosition().x + 5, inputField.getPosition().y + 5);
        window.draw(inputField);
        window.draw(displayText);
    }


    void Renderer::GameWindow(sf::RenderWindow& window)
    {
        m_background.setTexture(fonts->background);
        sf::RectangleShape navbar;
        navbar.setFillColor(sf::Color(182, 187, 196, 150));
        navbar.setPosition(0, 0);
        navbar.setSize(sf::Vector2f(1280, 100));

        sf::Text username;
        username.setString(m_logusername);
        username.setPosition(100, 100);
        username.setFillColor(sf::Color::Red);
        username.setCharacterSize(20);
        username.setFont(fonts->Arial);
        std::cout << m_logusername;
        ;        while (m_GameWindowOpen)
        {
            window.clear(sf::Color::White);
            HandleEvents(window, m_GameWindowOpen);
            window.draw(m_background);
            window.draw(navbar);
            window.display();
        }
    }
}