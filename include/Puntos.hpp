#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <sstream>

class Puntos
{
private:
    sf::Font font;
    sf::Text pointsText;

    int points;

    void initVariables()
    {
        this->points = 0;
    }

    void innitFont()
    {
        if (!this->font.loadFromFile("./assets/images/bg.png"))
        {
            std::cout << "ERROR::Puntos::innitFont::No se pudo cargar la fuente" << std::endl;
        }
    }

    void innitText()
    {
        this->pointsText.setFont(this->font);
        this->pointsText.setFillColor(sf::Color::Black);
    }

public:
    // Setters
    void setPosition(float x, float y)
    {
        this->pointsText.setPosition(x, y);
    }

    void setTextColor(sf::Color color)
    {
        this->pointsText.setFillColor(color);
    }

    void setTextSize(int size)
    {
        this->pointsText.setCharacterSize(size);
    }

    void setText(std::stringstream ss)
    {
        this->pointsText.setString(ss.str());
    }

    void render(sf::RenderTarget *target)
    {
        target->draw(this->pointsText);
    }

    void setPuntos(int p)
    {
        points = p;
    }

    Puntos(/* args */)
    {
        this->initVariables();
        this->innitFont();
        this->innitText();
    }
    ~Puntos()
    {
    }
};



