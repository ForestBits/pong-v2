//singleplayer game vs computer

#ifndef SINGLEPLAYER_H
#define SINGLEPLAYER_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>
#include "../ScreenEngine.h"

namespace pong { namespace screen {

class Singleplayer : public Screen
{
    //particles when ball bounces
    //life is incremented until 1, then it is killed
    //doesn't use accurate time, but easy to change value (that is 1)
    struct CollisionParticle
    {
        sf::Vector2f position;

        double angle;
        double speed;
        double life;

        bool operator==(const CollisionParticle & other) {return this->position == other.position && this->angle == other.angle && this->speed == other.speed && this->life == other.life;}
    };

    std::vector<CollisionParticle> particles;

    sf::Text centerText;
    sf::Text leftScoreText;
    sf::Text rightScoreText;

    //paddles and ball moving
    bool gameActive = false;

    //3, 2, 1, go
    bool textTransition = false;

    //placing ball after it goes out of bounds
    bool ballTransition = true;

    //scores being displayed
    bool scoreTransition = false;

    //paddles being moved back
    bool paddleTransition = false;

    int leftScore = 0;
    int rightScore = 0;

    sf::Clock ballTransitionClock;
    sf::Clock textTransitionClock;
    sf::Clock scoreTransitionClock;
    sf::Clock paddleTransitionClock;

    sf::RectangleShape leftPaddle;
    sf::RectangleShape rightPaddle;

    sf::CircleShape ball;
    sf::CircleShape ballTrail;

    //for ball
    double hSpeed;
    double vSpeed;
    double excesshSpeed = 0;
    double excessvSpeed = 0;

    sf::FloatRect topRectangle;
    sf::FloatRect bottomRectangle;
    sf::FloatRect leftRectangle;
    sf::FloatRect rightRectangle;
    sf::FloatRect inboundsRectangle;

    std::vector<sf::FloatRect> collidableRectangles;

    std::vector<sf::Vector2f> ballPositions;

public:
    Singleplayer(ScreenConstructionParameters parameters);

    void update(ScreenUpdateParameters parameters) override;

    void draw(sf::RenderTarget & target, const TransitionInfo & transition) override;

    void onChangeIn(ScreenConstructionParameters parameters);
};

}}


#endif