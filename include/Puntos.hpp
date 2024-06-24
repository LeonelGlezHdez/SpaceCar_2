#include <SFML/Graphics.hpp>
#include <sstream>

class Puntos {
public:
    Puntos(const sf::Font& font) {
        // Inicializar el reloj
        clock.restart();

        // Configurar el texto de los puntos
        pointsText.setFont(font);
        pointsText.setCharacterSize(24);
        pointsText.setFillColor(sf::Color::White);
        pointsText.setPosition(10, 40);
    }

    void update() {
        // Actualizar el tiempo transcurrido
        timeElapsed = clock.getElapsedTime();
        float seconds = timeElapsed.asSeconds();

        // Actualizar los puntos basados en el tiempo transcurrido
        points = static_cast<int>(seconds);

        // Actualizar el texto del tiempo y los puntos
        std::stringstream ss;

        ss.str("");  // Limpiar el stringstream
        ss << "Puntos: " << points;
        pointsText.setString(ss.str());
    }

    void draw(sf::RenderWindow& window) {
        window.draw(pointsText);
    }

private:
    sf::Clock clock;
    sf::Time timeElapsed;
    int points = 0;

    sf::Text timeText;
    sf::Text pointsText;
};
