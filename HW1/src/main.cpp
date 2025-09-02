#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML window");
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("boid-sm.png"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Hello SFML", font, 50);
    // Load a music to play
    // sf::Music music;
    // if (!music.openFromFile("file_example_OOG_1MG.ogg"))
    //     return EXIT_FAILURE;
    // // Play the music
    // music.play();
    // Start the game loop

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear(sf::Color::White);
        // Draw the sprite
        window.draw(sprite);
        // Draw the string
        window.draw(text);
        // Draw the shape
        window.draw(shape);
        // Update the window

        sprite.move(sf::Vector2f(0.1f, 0.f));
        window.display();
    }
    return EXIT_SUCCESS;
}