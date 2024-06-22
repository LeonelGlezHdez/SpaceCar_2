#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <time.h>

#include <Game.hpp>
#include <iostream>

int main(int argc, char const *argv[])
{
    srand(time(static_cast<unsigned>(0)));

    Game game;

    while (game.running() && !(game.getEndGame()))
    {
        game.actualizar();
        game.renderizar();
    }

    return 0;
}
