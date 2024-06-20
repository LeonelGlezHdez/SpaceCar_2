#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <time.h>

#include <Game.hpp>

int main()
{
    srand(time(static_cast<unsigned>(0)));

    Game game;

    while (game.running() && !(game.getEndGame())) // Revisa constantemente si la ventana sigue abierta
    {

        // Update
        game.update();

        // Render
        game.render();
    }

    return 0;
}