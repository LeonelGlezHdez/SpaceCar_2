#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
#include <variant>
#include <thread>
#include <chrono>

#include <Puntos.hpp>



class Game
{
private:
    bool EndGame;
    bool GameStarted;

    sf::RenderWindow Pantalla;
    sf::Event event;

    sf::SoundBuffer IntroBuffer;
    sf::Sound IntroTone;

    sf::SoundBuffer stageStartBuffer;
    sf::Sound stageStartTone;

    sf::SoundBuffer gameOverBuffer;
    sf::Sound gameOverTone;

    sf::Texture backgroundTexture;
    sf::Sprite background;

    Puntos puntos;

    int ToneTimer;
    int toneTimerLimit;

    sf::Font font;
    sf::Text pointsText;

    void iniciarVariables()
    {
        this->EndGame = false;

        this->ToneTimer = 0;
        this->toneTimerLimit = 4000;

        if (!this->font.loadFromFile("./assets/fonts/Minecraft.ttf"))
        {
            std::cout << "ERROR::Puntos::innitFont::No se pudo cargar la fuente" << std::endl;
        }

        this->pointsText.setFont(this->font);
        this->pointsText.setCharacterSize(30);
        this->pointsText.setFillColor(sf::Color::White);
        this->pointsText.setPosition(10.f, 10.f);
        this->pointsText.setString("");
    }

    void sonidoJuego()
    {
        if (!this->IntroBuffer.loadFromFile("./assets/music/intro.wav"))
        {
            std::cout << "ERROR::Game::innitGameSound::No se pudo cargar el sonido de inicio" << std::endl;
        }
        IntroTone.setBuffer(IntroBuffer);

        if (!this->gameOverBuffer.loadFromFile("./assets/music/EndGame.wav"))
        {
            std::cout << "ERROR::Game::innitGameSound::No se pudo cargar el sonido de fin de juego" << std::endl;
        }
        gameOverTone.setBuffer(gameOverBuffer);
    }


public:
    Game() : Pantalla(sf::RenderWindow(sf::VideoMode(768, 411), "SPACE CAR", sf::Style::Titlebar))
    {
        this->iniciarVariables();
        this->sonidoJuego();
        this->innitGameBackground();
    }

    ~Game()
    {
    }

    const bool running() const
    {
        return this->Pantalla.isOpen();
    }

    const bool getEndGame() const
    {
        return this->EndGame;
    }

    void innitGameBackground()
    {
        if (!this->backgroundTexture.loadFromFile("./assets/images/bg.png"))
        {
            std::cout << "ERROR::Game::innitGameBackground::No se pudo cargar la textura del fondo" << std::endl;
        }
        this->background.setTexture(this->backgroundTexture);
    }

    void renderGameBackground()
    {
        this->Pantalla.draw(this->background);
    }

    void printPoints()
    {
        this->puntos.setTextSize(20);
        this->puntos.setTextColor(sf::Color::White);
        this->puntos.setPosition(10.f, 10.f);
        this->puntos.render(this->Pantalla);
        this->Pantalla.draw(this->pointsText);

    }

    void loadStartScreen()
    {
        this->renderGameBackground();

        this->puntos.setTextSize(65);
        this->puntos.setTextColor(sf::Color::Black);
        this->puntos.setPosition(210.f, 100.f);
        this->puntos.setText("SPACE CAR");
        this->puntos.render(this->Pantalla);

        this->puntos.setTextSize(18);
        this->puntos.setTextColor(sf::Color::Black);
        this->puntos.setPosition(310.f, 200.f);
        this->puntos.setText("Presiona Enter para continuar");
        this->puntos.render(this->Pantalla);

    }

    void pantallaCarga()
    {
        this->renderGameBackground();
        
        this->puntos.setTextSize(16);
        this->puntos.setTextColor(sf::Color::Cyan);
        this->puntos.setPosition(400.f, 300.f);
        this->puntos.setText("Preparate Madafaker");
        this->puntos.render(this->Pantalla);

        this->printPoints();
    }

    void pollEvents()
    {
        while (this->Pantalla.pollEvent(this->event))
        {
            switch (this->event.type)
            {
            case sf::Event::Closed:
                this->Pantalla.close();
                break;

            case sf::Event::KeyPressed:
                if (this->event.key.code == sf::Keyboard::Escape) // Cerrar ventana si se presiona ESC en el teclado
                {
                    this->Pantalla.close();
                }
                else if (this->event.key.code == sf::Keyboard::Enter && !this->GameStarted)
                {
                    this->GameStarted = true;
                    this->IntroTone.stop();
                }
                break;
            }
        }
    }

    void actualizar()
    {
        this->pollEvents();

        if (this->ToneTimer == 0)
        {
            this->IntroTone.play();
            this->ToneTimer = this->toneTimerLimit;
        }
        else
        {
            this->ToneTimer--;
        }

    }

    void renderizar()
    {
        // Limpiar
        this->Pantalla.clear();
        
        
        // Dibujar
        if (GameStarted){
            this->printPoints();
        } else {
            this->loadStartScreen();
        }

        // Mostrar
        this->Pantalla.display();
    }

};

