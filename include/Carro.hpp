#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

 class Carro
 {
 private:
    double speed;
    int Lives;

    sf::Sprite carro;
    sf::Texture texture;

    sf::SoundBuffer buffer;
    sf::Sound movimiento;

    sf::SoundBuffer bufferColo;
    sf::Sound colisionO;

    sf::SoundBuffer bufferCol;
    sf::Sound colision;

 public:

    void innitTexture()
    {
        // Cargar la textura de la nave
        if (!this->texture.loadFromFile("assets/images/carGray.png"))
        {
            std::cout << "ERROR::Nave::innitTexture::No se pudo cargar la textura de la nave" << std::endl;
        }
    }

    void innitSprite()
    {
        // Asignar la textura a la nave
        this->carro.setTexture(this->texture);

        // Escalar la sprite de la nave al tamaño deseado
        this->carro.scale(0.1, 0.1);
    }

    void innitSound()
    {
        // Cargar el sonido para cada disparo de la nave
        if (!this->bufferColo.loadFromFile("./assets/images/music/ColisionOil.wav"))
        {
            std::cout << "ERROR::Carro::innitSound::No se pudo cargar el sonido de disparo" << std::endl;
        }
        colisionO.setBuffer(bufferColo);

        // Cargar el sonido para cada colisión de la nave
        if (!this->bufferCol.loadFromFile("./assets/images/music/Colision.wav"))
        {
            std::cout << "ERROR::Arro::innitSound::No se pudo cargar el sonido de colisión" << std::endl;
        }
        colision.setBuffer(bufferCol);

        // Cargar el sonido para cada respawn de la nave
        if (!this->buffer.loadFromFile("./assets/images/music/Avanzar.wav"))
        {
            std::cout << "ERROR::Carro::innitSound::No se pudo cargar el sonido de respawn" << std::endl;
        }
        movimiento.setBuffer(buffer);
    }

    void innitVariables()
    {
        this->Lives = 1;
        this->speed = 2.f;
    }

    void updateInput()
    {
        /*
        Función que se encarga de constantemente revisar la tecla que se presione
        con relación a la nave, según la telca presionada, esta puede:
        - Moverse a la izquierda (LEFT)
        - Moverse a la derecha (RIGHT)
        - Disparar (SPACE)

        No confundir con pollEvents, ya que la mencionada actúa en función de los eventos
        ocurridos en la ventana completa y no sobre la nave.
        */

        // Movimiento de la nave con telcado
        // Izquierda (LEFT)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            this->carro.move(-this->speed, 0.f);
        }
        // Derecha (RIGHT)
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            this->carro.move(this->speed, 0.f);
        }
    }
    
    Carro(/* args */);
    ~Carro();
 };
 
 Carro::Carro(/* args */)
 {
 }
 
 Carro::~Carro()
 {
 }
 