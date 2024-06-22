#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

 class Carro
 {
 private:
    double velocidad;
    int vidas;

    sf::Sprite carro;
    sf::Texture texture;

    sf::SoundBuffer Sonido;
    sf::Sound movimiento;

    sf::SoundBuffer SonidoColO;
    sf::Sound colisionO;

    sf::SoundBuffer SonidoCol;
    sf::Sound colision;

 public:

    void iniciarTextura()
    {
        if (!this->texture.loadFromFile("assets/images/carGray.png"))
        {
            std::cout << "ERROR::Nave::innitTexture::No se pudo cargar la textura de la nave" << std::endl;
        }
    }

    void innitSprite()
    {
        this->carro.setTexture(this->texture);

        this->carro.scale(0.1, 0.1);
    }

    void innitSound()
    {
        if (!this->SonidoColO.loadFromFile("./assets/music/ColisionOil.wav"))
        {
            std::cout << "ERROR::Carro::innitSound::No se pudo cargar el sonido de disparo" << std::endl;
        }
        colisionO.setBuffer(SonidoColO);

        if (!this->SonidoCol.loadFromFile("./assets/music/Colision.wav"))
        {
            std::cout << "ERROR::Arro::innitSound::No se pudo cargar el sonido de colisión" << std::endl;
        }
        colision.setBuffer(SonidoCol);

        if (!this->Sonido.loadFromFile("./assets/music/Avanzar.wav"))
        {
            std::cout << "ERROR::Carro::innitSound::No se pudo cargar el sonido de respawn" << std::endl;
        }
        movimiento.setBuffer(Sonido);
    }

    void innitVariables()
    {
        this->vidas = 1;
        this->velocidad = 2.f;
    }

    void updateInput()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            this->carro.move(-this->velocidad, 0.f);
        }
        // Derecha (RIGHT)
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            this->carro.move(this->velocidad, 0.f);
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
 