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

    void innitFont()
    {
        if (!this->font.loadFromFile("./assets/fonts/speed.ttf"))
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

    void setText(std::string ss)
    {
        this->pointsText.setString(ss);
    }

    void render(sf::RenderTarget &target)
    {
        target.draw(this->pointsText);
    }

    void setPuntos(int p)
    {
        points = p;
    }

    Puntos()
    {
        this->points = 0;
        this->innitFont();
        this->innitText();
    }
    ~Puntos()
    {
    }
};
