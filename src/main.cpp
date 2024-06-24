#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <time.h>
#include <Puntos.hpp>
//#include <Game.hpp>
#include <iostream>
#include<Paisaje.hpp>

/*
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
*/

/*
    int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Juego de Carreras Retro");

    // Cargar la fuente
    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/Minecraft.ttf")) {
        // Manejar el error de carga
        return -1;
    }

    // Crear una instancia de Cronometro
    Puntos Puntos(font);

    // Bucle principal del juego
    while (window.isOpen()) {
        // Manejar eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Actualizar el cronometro
        Puntos.update();

        // Limpiar la ventana
        window.clear();

        // Dibujar el cronometro
        Puntos.draw(window);

        // Mostrar lo que se ha dibujado en la ventana
        window.display();
    }

    return 0;
}

*/
int main()
{
    JuegoCarrerasRetro juego;
    juego.run();
    

    return 0;
}