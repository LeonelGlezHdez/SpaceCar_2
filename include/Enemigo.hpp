#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <Carro.hpp>
#include <vector>
#include "Juego.hpp"

class Enemigo
{
private:
    // Variables

protected:
  
    sf::Sprite enemigo;
    double speed;
    int tipo;
    int movDirection;

    std::vector<Carro *> Carros;

public:
    // Funciones
    void innitVariables()
    {
        this->speed = 4.5;
        this->tipo = rand() % 3 + 1; 
    }

    
    void setToXY(float posX, float posY)
    {
       
        this->enemigo.setPosition(posX, posY);
        this->movDirection = 0;
    }

    void moveUp()
    {
        this->enemigo.move(0.f, -this->speed);
        this->movDirection = 8;
    }

    void moveDown()
    {
        this->enemigo.move(0.f, this->speed);
        this->movDirection = 2;
    }

    void moveLeft()
    {
        this->enemigo.move(-this->speed, 0.f);
        this->movDirection = 4;
    }

    void moveRight()
    {
        this->enemigo.move(this->speed, 0.f);
        this->movDirection = 6;
    }


    void moveDiagDownRight(float factorX = 1.f, float factorY = 1.f)
    {
        this->enemigo.move(0.707 * this->speed * factorX, 0.707 * this->speed * factorY);
        this->movDirection = 3;
    }

    void moveDiagDownLeft(float factorX = 1.f, float factorY = 1.f)
    {
        this->enemigo.move(-0.707 * this->speed * factorX, 0.707 * this->speed * factorY);
        this->movDirection = 1;
    }

    void moveDiagUpRight(float factorX = 1.f, float factorY = 1.f)
    {
        this->enemigo.move(0.707 * this->speed * factorX, -0.707 * this->speed * factorY);
        this->movDirection = 9;
    }

    void moveDiagUpLeft(float factorX = 1.f, float factorY = 1.f)
    {
        this->enemigo.move(-0.707 * this->speed * factorX, -0.707 * this->speed * factorY);
        this->movDirection = 7;
    }

 

    

  

    //------------------------------------------------------------------------------------------------------------------------------------
    void update()


    {
      
    }

    void render(sf::RenderTarget *target)
    {
        for (auto *Carro : this->Carros)
        {
            
        }

        target->draw(this->enemigo);
    }

    // Getters
    float getSpeed()
    {
        
        
        return this->speed;
    }

    float getXPos()
    {
        
        return this->enemigo.getPosition().x;
    }

    float getYPos()
    {
        
        return this->enemigo.getPosition().y;
    }

    int getType()
    {
      
        return this->tipo;
    }

    void setProjectilesColor(sf::Color color)
    {
        for (auto *Carro : this->Carros)
        {
           
        }
    }

    const sf::FloatRect getBounds() const
    {
        
        return this->enemigo.getGlobalBounds();
    }

  
    Enemigo(float posX = 0.f, float posY = 0.f)
    {
        this->innitVariables();
        this->enemigo.setPosition(posX, posY);
    }
    ~Enemigo()
    {
     
        for (auto *i : this->Carros)
        {
            delete i;
        }
    }
};