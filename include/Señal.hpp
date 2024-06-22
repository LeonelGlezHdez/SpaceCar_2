#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>


class Señal
{
private:
    sf::Texture texture;

    int hitCount;



public:
    void innitTexture()
    {
        if (!this->texture.loadFromFile("./assets/images/Señal.png"))
        {
            std::cout << "ERROR::Señal::innitTexture::No se pudo cargar la textura" << std::endl;
        }
    }

    

    Señal(/* args */);
    ~Señal();
};

Señal::Señal(/* args */)
{
}

Señal::~Señal()
{
}

