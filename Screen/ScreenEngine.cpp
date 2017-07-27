#include <cassert>
#include "ScreenEngine.h"

using namespace pong;

ScreenEngineControl ScreenEngine::getController() {return control;}

ScreenConstructionParameters ScreenEngine::getConstructionParameters() 
{
    return updateParameters.constructionParameters;
}

void ScreenEngine::changeScreen(std::unique_ptr<Screen> && screen)
{
    if (transition.transitioningIn || transition.transitioningOut)
        return; //not sure what would happen if this occured

    clock.restart();

    if (currentScreen == nullptr)
    {
        currentScreen = std::move(screen);

        transition.transitioningIn = true;

        return;
    }
    else
    {
        nextScreen = std::move(screen);

        transition.transitioningOut = true;
    }
}

void ScreenEngine::update()
{
    assert(currentScreen != nullptr && "Must set a screen before using engine");

    if  (transition.transitioningIn)
    {
        transition.transitionPercent = clock.getElapsedTime().asSeconds()/currentScreen->getTransitionInTime();

        if (transition.transitionPercent >= 1)
        {
            transition.transitioningIn = false;

            transition.transitionPercent = 0;

            currentScreen->onChangeIn(updateParameters.constructionParameters);
        }
    }
    else if (transition.transitioningOut)
    {
        transition.transitionPercent = clock.getElapsedTime().asSeconds()/currentScreen->getTransitionOutTime();

        if (transition.transitionPercent >= 1)
        {
            currentScreen->onChangeOut(updateParameters.constructionParameters);

            currentScreen = std::move(nextScreen);

            nextScreen = nullptr;

            transition.transitioningOut = false;

            transition.transitioningIn = true;

            transition.transitionPercent = 0;

            clock.restart();
        }
    }

    currentScreen->update(updateParameters);
}

void ScreenEngine::draw()
{
    currentScreen->draw(updateParameters.window, transition);
}

ScreenEngineControl::ScreenEngineControl(ScreenEngine & engine) : engine(engine) {}

void ScreenEngineControl::hiddenSetScreen(std::unique_ptr<Screen> && screen)
{
    engine.changeScreen(std::move(screen));
}