#ifndef SCREENENGINE_H
#define SCREENENGINE_H

#include <memory>
#include <unordered_map>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Mouse.hpp>
#include "../QuitException.h"

namespace pong {

struct TransitionInfo
{
    bool transitioningIn = false;
    bool transitioningOut = false;

    //[0, 1]
    double transitionPercent = 0;
};

class ScreenEngineControl;

struct ScreenConstructionParameters
{
    sf::RenderWindow & window;

    ScreenEngineControl & control;

    const sf::Font & font;

    sf::Sound & clickSound;

    sf::Sound & bounceSound;

    sf::Sound & scoreSound;
};

struct ScreenUpdateParameters
{
    sf::RenderWindow & window;

    const TransitionInfo & transition;

    ScreenEngineControl & control;

    ScreenConstructionParameters constructionParameters; 
};

class Screen
{
public:
    virtual void update(ScreenUpdateParameters stuff) = 0;

    virtual void draw(sf::RenderTarget & target, const TransitionInfo & transition) = 0;

    virtual double getTransitionInTime() {return 0;}
    virtual double getTransitionOutTime() {return 0;}

    virtual void onChangeIn(ScreenConstructionParameters parameters) {}
    virtual void onChangeOut(ScreenConstructionParameters parameters) {}

    //slightly out of place, but every screen will need this
    //since fullscreen is supported, it... messes things up
    //does seem slightly out of place, but much better than repeating it everywhere
    sf::Vector2i getMousePosition(const sf::RenderWindow & window)
    {
        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        return {(int) mousePosition.x, (int) mousePosition.y};
    }
};

class ScreenEngine;

class ScreenEngineControl
{
    ScreenEngine & engine;

    //hidden as template methods are in headers, need implementation to avoid circular
    void hiddenSetScreen(std::unique_ptr<Screen> && screen);

public:
    ScreenEngineControl(ScreenEngine & engine);

    template <typename T, typename ... Args>
    void setScreen(Args && ... args)
    {
        hiddenSetScreen(std::make_unique<T>(args...));
    }
};

class ScreenEngine
{
    friend class ScreenEngineControl;

    std::unique_ptr<Screen> currentScreen;
    std::unique_ptr<Screen> nextScreen;

    TransitionInfo transition;

    ScreenUpdateParameters updateParameters; //contains construction parameters

    ScreenEngineControl control;

    sf::Clock clock;

    //to be called by the control
    void changeScreen(std::unique_ptr<Screen> && screen);

public:
    template <typename ... Args>
    ScreenEngine(sf::RenderWindow & window, Args && ... args) : updateParameters ({window, transition, control, {window, control, args...}}), control(*this)
    {
        
    }

    ScreenEngineControl getController();

    ScreenConstructionParameters getConstructionParameters();

    void update();

    void draw();
};

}

#endif