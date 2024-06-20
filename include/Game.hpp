#pragma once
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
    bool endGame;
    bool gameStarted;

    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event event;

    sf::SoundBuffer introBuffer;
    sf::Sound introTone;

    sf::SoundBuffer stageStartBuffer;
    sf::Sound stageStartTone;

    sf::SoundBuffer gameOverBuffer;
    sf::Sound gameOverTone;

    sf::Texture backgroundTexture;
    sf::Sprite background;

    Puntos *puntos;

    int toneTimer;
    int toneTimerLimit;

    void initVariables()
    {
        this->endGame = false;

        this->window = nullptr;

        this->toneTimer = 0;
        this->toneTimerLimit = 4000;
    }

    void initWindow()
    {
        this->videoMode.height = 768;
        this->videoMode.width = 1024;

        this->window = new sf::RenderWindow(this->videoMode, "¡¡Space Car!!", sf::Style::Titlebar | sf::Style::Close);

        this->window->setFramerateLimit(165);
    }

    void initEntities()
    {

        this->puntos = new Puntos();
    }

    void initGameSound()
    {
        if (!this->introBuffer.loadFromFile("assets/images/music/intro.wav"))
        {
            std::cout << "ERROR::Game::innitGameSound::No se pudo cargar el sonido de inicio" << std::endl;
        }
        introTone.setBuffer(introBuffer);

        /*if (!this->stageStartBuffer.loadFromFile("./assets/music/inicioetapaD.wav"))
        {
            std::cout << "ERROR::Game::innitGameSound::No se pudo cargar el sonido de inicio de nivel" << std::endl;
        }
        stageStartTone.setBuffer(stageStartBuffer);
        */
        if (!this->gameOverBuffer.loadFromFile("./assets/images/music/EndGame.wav"))
        {
            std::cout << "ERROR::Game::innitGameSound::No se pudo cargar el sonido de fin de juego" << std::endl;
        }
        gameOverTone.setBuffer(gameOverBuffer);
    }


public:
    Game(/* args */)
    {
        this->initVariables();
        this->initWindow();
        this->initGameSound();
        this->initEntities();
    }

    ~Game()
    {
        delete this->window;
    }

    const bool running() const
    {
        return this->window->isOpen();
    }

    const bool getEndGame() const
    {
        return this->endGame;
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
        this->window->draw(this->background);
    }

        void printPoints()
    {
        this->puntos->setTextSize(20);
        this->puntos->setTextColor(sf::Color::White);
        this->puntos->setPosition(10.f, 10.f);
        //this->puntos->setText(std::stringstream() << this->puntos->getPuntos());
    }

    void loadStartScreen()
    {

        this->window->clear();

        this->renderGameBackground();

        this->puntos->setTextSize(34);
        this->puntos->setTextColor(sf::Color::Black);
        this->puntos->setPosition(210.f, 100.f);
        this->puntos->setText(std::stringstream() << "SPACE CAR");
        this->puntos->render(this->window);

        this->puntos->setTextSize(12);
        this->puntos->setTextColor(sf::Color::Black);
        this->puntos->setPosition(160.f, 380.f);
        this->puntos->setText(std::stringstream() << "Presiona Enter para continuar");
        this->puntos->render(this->window);

        this->puntos->setTextSize(10);
        this->puntos->setTextColor(sf::Color::Black);
        this->puntos->setPosition(220.f, 780.f);
        this->puntos->setText(std::stringstream() << "23110177  -  23110186");
        this->puntos->render(this->window);

        this->pollEvents();

        if (this->toneTimer == 0)
        {
            this->introTone.play();
            this->toneTimer = this->toneTimerLimit;
        }
        else
        {
            this->toneTimer--;
        }

        this->window->display();
    }

    void loadstageStartScreen()
    {
        this->stageStartTone.play();

        this->window->clear();
        this->renderGameBackground();
        this->puntos->setTextSize(16);
        this->puntos->setTextColor(sf::Color::Cyan);
        this->puntos->setPosition(225.f, 250.f);
        this->puntos->setText(std::stringstream() << "Preparate Madafaker");
        this->puntos->render(this->window);

        this->printPoints();
        this->window->display();

        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    void pollEvents()
    {
        /*
            Esta función se encarga de revisar si ocurre algún evento relacionado a la ventana, por ejemplo,
            si el usuario presiona el botón de cerrar la ventana, la ventana se cerrará lo que terminará el
            juego, lo mismo sucede con la tecla ESC en el teclado. Sin embargo, la función pollEvents también
            se encarga de revisar si el usuario presiona la tecla ENTER, lo que en la pantalla de inicio, dará
            inicio al juego.
        */

        while (this->window->pollEvent(this->event)) // Revisa si en la ventana ocurre un evento
        {
            switch (this->event.type) // Determina la acción segun que evento suceda
            {
            case sf::Event::Closed: // Cerrar ventana si se presiona la "X" de la ventana
                this->window->close();
                break;

            case sf::Event::KeyPressed:
                if (this->event.key.code == sf::Keyboard::Escape) // Cerrar ventana si se presiona ESC en el teclado
                {
                    this->window->close();
                }
                else if (this->event.key.code == sf::Keyboard::Enter && !this->gameStarted)
                {
                    this->gameStarted = true;
                    this->introTone.stop();
                    this->loadstageStartScreen();
                    this->introTone.stop();
                }
                break;
            }
        }
    }

    void update()
    {
        /*
            Esta función se encarga de actualizar todos los eventos que ocurran en el juego previo a ser renderizados.
            Se ejecuta solo si el juego ha sido iniciado (el usuario ha presionado la tecla ENTER en la pantalla de
            inicio).
        */

        if (gameStarted == true)
        {
            /*     // Actualiza los eventos de la ventana
            this->pollEvents();

            // Actualiza todo lo relacionado con la nave, como su posición, proyectiles, etc.
            this->updateNave();

            // Actualiza todo lo relacionado con los enemigos, como su posición, movimiento, estado, etc.
            this->updateEnemigos();

            // Actualiza los disparos realizados por los enemigos
            for (int i = 0; i < this->enemigosActivos.size(); i++)
            {
                std::visit([this](const auto &arg)
                           { arg->update(); }, enemigosActivos[i]);
            }
            */
            // Actualiza el puntaje
            this->printPoints();
        }
        else if (this->gameStarted == false)
        {
            this->loadStartScreen();
        }
    }

    void render()
    {
        if (gameStarted == true) // Solo comienza a renderizar si el juego ha comenzado (Se presionó la tecla ENTER)
        {
            /*
                Muestra en la ventana del juego todos los elementos
                que sean dibujados previamente según el siguiente orden:

                - Borra el frame anterior
                - Dibuja todos los elementos especificados
                - Muestra el frame
            */

            this->window->clear();

            // Dibujar elementos en ventana

            this->renderGameBackground();

            this->puntos->render(this->window);

            //this->nave->render(this->window);

            /*for (int i = 0; i < this->enemigosActivos.size(); i++)
            {
                std::visit([this](const auto &arg)
                           { arg->render(this->window); }, enemigosActivos[i]);
            }
            */
            // Una vez dibujados los elementos, se muestra la ventana (Equivale a 1 frame)

            this->window->display();
        }
    }







};

