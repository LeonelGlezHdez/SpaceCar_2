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

    sf::Sprite nave;
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
        if (!this->texture.loadFromFile("assets/images/Ambulance.png"))
        {
            std::cout << "ERROR::Nave::innitTexture::No se pudo cargar la textura de la nave" << std::endl;
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
 