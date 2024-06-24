/*
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <variant>
#include <thread>
#include <chrono>

#include "Game.hpp"

int main()
{
    Game game;

    while (game.running())
    {
        game.actualizar();
        game.renderizar();
    }

    return 0;
}
*/

#include "Juego.hpp"

int main()
{
    Juego juego;
    juego.run();
    return 0;
}


