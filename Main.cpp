#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include "Screen/ScreenEngine.h"
#include "Screen/Screens/MainMenu.h"
#include "QuitException.h"

namespace {

class MissingFileException : public std::runtime_error
{
public:
    MissingFileException(const std::string & fileName) : std::runtime_error("Missing file: res/" + fileName) {}
};

}

using namespace pong;



int main()
{
    try
    {
        sf::RenderWindow window(sf::VideoMode(640, 480), "Pong");

        sf::Font font;

        if (!font.loadFromFile("res/Munro.ttf"))
            throw MissingFileException("Munro.ttf");

        sf::SoundBuffer clickSoundBuffer;

        if (!clickSoundBuffer.loadFromFile("res/click.wav"))
            throw MissingFileException("click.wav");

        sf::SoundBuffer bounceSoundBuffer;

        if (!bounceSoundBuffer.loadFromFile("res/bounce.wav"))
            throw MissingFileException("bounce.wav");

        sf::SoundBuffer scoreSoundBuffer;

        if (!scoreSoundBuffer.loadFromFile("res/score.wav"))
            throw MissingFileException("score.wav");

        sf::Sound clickSound;

        clickSound.setBuffer(clickSoundBuffer);
        
        sf::Sound bounceSound;

        bounceSound.setBuffer(bounceSoundBuffer);

        sf::Sound scoreSound;

        scoreSound.setBuffer(scoreSoundBuffer);

        ScreenEngine engine(window, font, clickSound, bounceSound, scoreSound);

        engine.getController().setScreen<screen::MainMenu>(engine.getConstructionParameters());

        sf::Clock update, draw;

        while (true)
        {
            if (update.getElapsedTime().asSeconds() > 0.03)
            {
                update.restart();

                engine.update();
            }

            if (draw.getElapsedTime().asSeconds() > 0.015)
            {
                draw.restart();

                engine.draw();

                window.display();
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    catch (const QuitException & exception)
    {
        //this is thrown when we want to quit (exit button, etc)

        return 0;
    }

    catch (const std::exception & exception)
    {
        std::cout << "\n\nError: " << exception.what();

        std::cin.get();
    }

    catch (...)
    {
        std::cout << "\n\nUnknown error occured";

        std::cin.get();
    }
}