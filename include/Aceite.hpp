#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include <Enemigo.hpp>

class Aceite : public Enemigo
{
private:
    sf::Texture texture;

    float scaleX;
    float scaleY;

    sf::SoundBuffer buffer;
    sf::Sound death;

    int hitCount;

    void innitVariables()
    {
        this->tipo = 2;
        this->scaleX = 0.05;
        this->scaleY = 0.05;
    }

public:
    void innitTexture()
    {
        if (!this->texture.loadFromFile("./assets/images/Aceite.png"))
        {
            std::cout << "ERROR::Mariposa::innitTexture::No se pudo cargar la textura de la mariposa" << std::endl;
        }
    }

    void innitSprite()
    {
        this->enemigo.setTexture(this->texture);
        this->enemigo.scale(scaleX, scaleY);
    }

    void innitSound()
    {
        if (!this->buffer.loadFromFile("./assets/music/colision.wav"))
        {
            std::cout << "ERROR::Mariposa::innitSound::No se pudo cargar el sonido de disparo" << std::endl;
        }
        death.setBuffer(buffer);
    }

    void playDeathSound()
    {
        death.play();
    }

    void playDamageSound()
    {
    }

    void takeHit()
    {
    }

    int getHitCount()
    {
        return 0;
    }

    Aceite(float posX = 0.f, float posY = 0.f)
    {
        this->innitVariables();
        this->innitTexture();
        this->innitSprite();
        this->innitSound();
        this->setProjectilesColor(sf::Color::Red);

        this->enemigo.setPosition(posX, posY);
    }
    ~Aceite() {}
};
