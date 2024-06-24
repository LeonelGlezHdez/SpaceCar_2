#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <string>

using namespace sf;

// Variables globales para dimensiones y configuraciones del juego
int width = 1024;   // Ancho de la ventana del juego
int height = 768;   // Alto de la ventana del juego
int roadW = 2000;   // Ancho de la carretera
int segL = 200;     // Longitud de cada segmento de la carretera
float camD = 0.84;  // Profundidad de la cámara
float autoScrollSpeed = 150;

// Función para dibujar un cuadrilátero
void drawQuad(RenderWindow &w, Color c, int x1, int y1, int w1, int x2, int y2, int w2)
{
    ConvexShape shape(4);
    shape.setFillColor(c);
    shape.setPoint(0, Vector2f(x1 - w1, y1));
    shape.setPoint(1, Vector2f(x2 - w2, y2));
    shape.setPoint(2, Vector2f(x2 + w2, y2));
    shape.setPoint(3, Vector2f(x1 + w1, y1));
    w.draw(shape);
}

// Estructura que representa un segmento de la carretera
struct Line
{
    float x, y, z; // Coordenadas 3D del centro del segmento
    float X, Y, W; // Coordenadas de la pantalla
    float curve, spriteX, clip, scale;
    Sprite sprite;

    Line()
    {
        spriteX = curve = x = y = z = 0;
    }

    // Proyectar el segmento en coordenadas de pantalla
    void project(int camX, int camY, int camZ)
    {
        scale = camD / (z - camZ);
        X = (1 + scale * (x - camX)) * width / 2;
        Y = (1 - scale * (y - camY)) * height / 2;
        W = scale * roadW * width / 2;
    }

    // Dibujar el sprite del segmento
    void drawSprite(RenderWindow &app)
    {
        Sprite s = sprite;
        int w = s.getTextureRect().width;
        int h = s.getTextureRect().height;

        float destX = X + scale * spriteX * width / 2;
        float destY = Y + 4;
        float destW = w * W / 266;
        float destH = h * W / 266;

        destX += destW * spriteX; // offsetX
        destY += destH * (-1);    // offsetY

        float clipH = destY + destH - clip;
        if (clipH < 0)
            clipH = 0;

        if (clipH >= destH)
            return;
        s.setTextureRect(IntRect(0, 0, w, h - h * clipH / destH));
        s.setScale(destW / w, destH / h);
        s.setPosition(destX, destY);
        app.draw(s);
    }
};

// Clase principal del juego
class Paisaje
{
public:
    Paisaje()
    {
        // Crear ventana del juego
        app.create(VideoMode(width, height), "CAR SPACE");
        app.setFramerateLimit(60);

        // Cargar texturas y objetos del juego
        for (int i = 1; i <= 7; i++)
        {
            t[i].loadFromFile("images/" + std::to_string(i) + ".png");
            t[i].setSmooth(true);
            object[i].setTexture(t[i]);
        }

        // Cargar y configurar el fondo del juego
        bg.loadFromFile("assets/images/bg.png");
        bg.setRepeated(true);
        sBackground.setTexture(bg);
        sBackground.setTextureRect(IntRect(0, 0, 5000, 411));
        sBackground.setPosition(-2000, 0);

        // Configurar segmentos de la carretera
        for (int i = 0; i < 1600; i++)
        {
            Line line;
            line.z = i * segL;

            if (i > 300 && i < 700)
                line.curve = 0.5;
            if (i > 1100)
                line.curve = -0.7;

            if (i < 300 && i % 20 == 0)
            {
                line.spriteX = -2.5;
                line.sprite = object[5];
            }
            if (i % 17 == 0)
            {
                line.spriteX = 2.0;
                line.sprite = object[6];
            }
            if (i > 300 && i % 20 == 0)
            {
                line.spriteX = -0.7;
                line.sprite = object[4];
            }
            if (i > 800 && i % 20 == 0)
            {
                line.spriteX = -1.2;
                line.sprite = object[1];
            }
            if (i == 400)
            {
                line.spriteX = -1.2;
                line.sprite = object[7];
            }

            if (i > 750)
                line.y = sin(i / 30.0) * 1500;

            lines.push_back(line);
        }

        N = lines.size();
        playerX = 0;
        pos = 0;
        H = 1500;
    }

    // Método principal para ejecutar el juego
    void run()
    {
        while (app.isOpen())
        {
            handleEvents();
            update();
            render();
        }
    }

private:
    RenderWindow app;        // Ventana del juego
    Texture t[50];           // Texturas para los objetos del juego
    Sprite object[50];       // Sprites de los objetos del juego
    Texture bg;              // Textura del fondo
    Sprite sBackground;      // Sprite del fondo
    std::vector<Line> lines; // Vector de segmentos de la carretera
    int N;                   // Número de segmentos
    float playerX;           // Posición del jugador en el eje X
    int pos;                 // Posición del jugador en la carretera
    int H;                   // Altura de la cámara

    // Manejar eventos de la ventana
    void handleEvents()
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }
    }

    // Actualizar la lógica del juego
    void update()
{
    // Actualizar la posición del jugador con las teclas de dirección
    if (Keyboard::isKeyPressed(Keyboard::Right))
        playerX += 0.1;
    if (Keyboard::isKeyPressed(Keyboard::Left))
        playerX -= 0.1;

    // Actualizar la posición de la carretera automáticamente
    pos += autoScrollSpeed;
    while (pos >= N * segL)
        pos -= N * segL;
    while (pos < 0)
        pos += N * segL;

    int startPos = pos / segL;
    int camH = lines[startPos].y + H;

    // Mover el fondo de acuerdo con la curva del segmento actual
    sBackground.move(-lines[startPos].curve * autoScrollSpeed, 0);

    // Calcular y proyectar los segmentos de la carretera visibles
    int maxy = height;
    float x = 0, dx = 0;
    for (int n = startPos; n < startPos + 300; n++)
    {
        Line &l = lines[n % N];
        l.project(playerX * roadW - x, camH, startPos * segL - (n >= N ? N * segL : 0));
        x += dx;
        dx += l.curve;

        l.clip = maxy;
        if (l.Y >= maxy)
            continue;
        maxy = l.Y;
    }
}

    // Renderizar la escena del juego
void render()
{
    app.clear(Color(105, 205, 4));
    app.draw(sBackground);

    int startPos = pos / segL;
    int maxy = height;
    float x = 0, dx = 0;

    for (int n = startPos; n < startPos + 300; n++)
    {
        Line &l = lines[n % N];
        l.project(playerX * roadW - x, lines[startPos].y + H, startPos * segL - (n >= N ? N * segL : 0));
        x += dx;
        dx += l.curve;

        l.clip = maxy;
        if (l.Y >= maxy)
            continue;
        maxy = l.Y;

        Color grass = (n / 3) % 2 ? Color(16, 200, 16) : Color(0, 154, 0);
        Color rumble = (n / 3) % 2 ? Color(255, 255, 255) : Color(0, 0, 0);
        Color road = (n / 3) % 2 ? Color(107, 107, 107) : Color(105, 105, 105);

        Line p = lines[(n - 1) % N]; // Segmento previo

        drawQuad(app, grass, 0, p.Y, width, 0, l.Y, width);
        drawQuad(app, rumble, p.X, p.Y, p.W * 1.2, l.X, l.Y, l.W * 1.2);
        drawQuad(app, road, p.X, p.Y, p.W, l.X, l.Y, l.W);
    }

    for (int n = startPos + 300; n > startPos; n--)
        lines[n % N].drawSprite(app);

    app.display();
  }
};
