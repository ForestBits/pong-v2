#include "Singleplayer.h"
#include "Win.h"
#include "Lose.h"
#include "../../Utility/Random.h"
#include "../../Utility/StringNumberConvert.h"

using namespace pong;
using namespace pong::screen;

Singleplayer::Singleplayer(ScreenConstructionParameters parameters)
{
    leftPaddle.setSize({10, 100});
    leftPaddle.setPosition(0, 190);
    leftPaddle.setFillColor(sf::Color::White);

    rightPaddle.setSize({10, 100});
    rightPaddle.setPosition(630, 190);
    rightPaddle.setFillColor(sf::Color::White);

    topRectangle.left = 0;
    topRectangle.top = -1;
    topRectangle.width = 639;
    topRectangle.height = 1;

    bottomRectangle.left = 0;
    bottomRectangle.top = 480;
    bottomRectangle.width = 639;
    bottomRectangle.height = 1;

    leftRectangle.left = 0;
    leftRectangle.top = 190;
    leftRectangle.width = 10;
    leftRectangle.height = 100;

    rightRectangle.left = 630;
    rightRectangle.top = 190;
    rightRectangle.width = 10;
    rightRectangle.height = 100;

    inboundsRectangle.left = 0;
    inboundsRectangle.top = 0;
    inboundsRectangle.width = 640;
    inboundsRectangle.height = 480;


    collidableRectangles.push_back(topRectangle);
    collidableRectangles.push_back(bottomRectangle);
    collidableRectangles.push_back(leftRectangle);
    collidableRectangles.push_back(rightRectangle);

    ball.setPointCount(30);
    ball.setRadius(6);
    ball.setOrigin(6, 6);
    ball.setPosition(320, 240);
    ball.setFillColor(sf::Color::White);

    ballTrail = ball;

    centerText.setFont(parameters.font);

    leftScoreText.setFont(parameters.font);
    leftScoreText.setString("0");

    rightScoreText.setFont(parameters.font);
    rightScoreText.setString("0");
    ballTransitionClock.restart();
    textTransitionClock.restart();
}

void Singleplayer::update(ScreenUpdateParameters parameters)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        throw QuitException();

    EventQueue events(parameters.window);

    for (sf::Event event : events)
    {
        if (event.type == sf::Event::Closed)
            throw QuitException();
    }
    
    if (gameActive)
    {
        //ball movement/collisions

        //we collect excess (as we can only move integers), so we can still use decimal speeds

        int hMove = hSpeed;
        int vMove = vSpeed;

        excesshSpeed += std::abs(hSpeed - hMove);
        excessvSpeed += std::abs(vSpeed - vMove);

        while (excesshSpeed > 1)
        {
            --excesshSpeed;

            if (hMove > 0)
                ++hMove;
            else
                --hMove;
        }

        while (excessvSpeed > 1)
        {
            --excessvSpeed;

            if (vMove > 0)
                ++vMove;
            else
                --vMove;
        }

        //we move a pixel at a time, on each axis. This ensures any speed works

        int hSign = 0;

        if (hMove > 0)
            hSign = 1;
    
        if (hMove < 0)
            hSign = -1;

        int vSign = 0;

        if (vMove > 0)
            vSign = 1;

        if (vMove < 0)
            vSign = -1;

        while (std::abs(hMove) > 0 || std::abs(vMove) > 0)
        {
            //horizontal
            if (std::abs(hMove) > 0)
            {
                sf::FloatRect movedRectangle;

                movedRectangle.left = ball.getGlobalBounds().left + hSign;
                movedRectangle.top = ball.getGlobalBounds().top;
                movedRectangle.width = ball.getGlobalBounds().width;
                movedRectangle.height = ball.getGlobalBounds().height;

                 bool intersects = false;

                 if (movedRectangle.intersects(leftRectangle) || movedRectangle.intersects(rightRectangle))
                     intersects = true;

                 if (intersects)
                 {
                     parameters.constructionParameters.bounceSound.play();

                    hSpeed = -hSpeed;

                    hMove = -hMove;

                    hSign = -hSign;

                    Random random;

                    for (int i = 0; i < 10; ++i)
                        particles.push_back({ball.getPosition(), random.getFloat()*359, 3, 0});
                 }
                 else
                 {
                    ball.setPosition(movedRectangle.left + ball.getRadius(), ball.getPosition().y);
                 }

                 if (hMove > 0)
                     --hMove;
                 else
                     ++hMove;
            }

            //vertical
            if (std::abs(vMove) > 0)
            {
                sf::FloatRect movedRectangle;

                movedRectangle.left = ball.getGlobalBounds().left;
                movedRectangle.top = ball.getGlobalBounds().top + vSign;
                movedRectangle.width = ball.getGlobalBounds().width;
                movedRectangle.height = ball.getGlobalBounds().height;

                bool intersects = false;

                ///
                if (movedRectangle.intersects(topRectangle) || movedRectangle.intersects(bottomRectangle) || movedRectangle.intersects(leftRectangle) || movedRectangle.intersects(rightRectangle))
                    intersects = true;

                if (intersects)
                {
                    parameters.constructionParameters.bounceSound.play();

                    vSpeed = -vSpeed;

                    vMove = -vMove;

                    vSign = -vSign;

                    Random random;

                    for (int i = 0; i < 10; ++i)
                        particles.push_back({ball.getPosition(), random.getFloat()*359, 3, 0});
                }
                else
                {
                    ball.setPosition(ball.getPosition().x, movedRectangle.top + ball.getRadius());
                }

                if (vMove > 0)
                    --vMove;
                else
                    ++vMove;
            }
        }

        //for ball particle visuals

        if (ballPositions.size() < 30)
            ballPositions.push_back(ball.getPosition());

        //paddle movement

        double moveAmount = 6;

        //after moving (both this and AI), we must check if it went into the ball
        //if it can move into the ball, they already lost
        //however, moving into it causes bugs, so we cannot let it happen

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            leftPaddle.move(0, -moveAmount);

            while (leftPaddle.getGlobalBounds().intersects(ball.getGlobalBounds()))
                leftPaddle.move(0, 1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            leftPaddle.move(0, moveAmount);


            while (leftPaddle.getGlobalBounds().intersects(ball.getGlobalBounds()))
                leftPaddle.move(0, -1);
        }

        //make paddle inbounds

        if (leftPaddle.getGlobalBounds().top < 0)
            leftPaddle.setPosition(leftPaddle.getPosition().x, 0);

        if (leftPaddle.getGlobalBounds().top + leftPaddle.getGlobalBounds().height >= 480)
            leftPaddle.setPosition(leftPaddle.getPosition().x, 480 - leftPaddle.getGlobalBounds().height);

        //other paddle AI

        double paddleCenter = rightPaddle.getGlobalBounds().top + rightPaddle.getGlobalBounds().height/2;

        if (paddleCenter < ball.getPosition().y)
        {
            double toMove = ball.getPosition().y - paddleCenter;

            if (toMove > moveAmount)
                toMove = moveAmount;

            rightPaddle.move(0, toMove);

            while (rightPaddle.getGlobalBounds().intersects(ball.getGlobalBounds()))
               rightPaddle.move(0, -1);
        }

        if (paddleCenter > ball.getPosition().y)
        {
            double toMove = ball.getPosition().y - paddleCenter;

            if (std::abs(toMove) > moveAmount)
                toMove = -moveAmount;

            rightPaddle.move(0, toMove);

            while (rightPaddle.getGlobalBounds().intersects(ball.getGlobalBounds()))
               rightPaddle.move(0, 1);
        }

        //make paddle inbounds

        if (rightPaddle.getGlobalBounds().top < 0)
            rightPaddle.setPosition(rightPaddle.getPosition().x, 0);

        if (rightPaddle.getGlobalBounds().top + rightPaddle.getGlobalBounds().height >= 480)
            rightPaddle.setPosition(rightPaddle.getPosition().x, 480 - rightPaddle.getGlobalBounds().height);

        //adjust bounding boxes for collisions

        leftRectangle.top = leftPaddle.getGlobalBounds().top;
        rightRectangle.top = rightPaddle.getGlobalBounds().top;


        //speed up ball slightly

        double angle = std::atan2(vSpeed, hSpeed);
        double speed = std::sqrt(std::pow(vSpeed, 2) + std::pow(hSpeed, 2));

        speed += 0.01;

        hSpeed = std::cos(angle)*speed;
        vSpeed = std::sin(angle)*speed;

        //did somebody score?

        if (!ball.getGlobalBounds().intersects(inboundsRectangle))
        {
            //ball is out of bounds

            parameters.constructionParameters.scoreSound.play();

            gameActive = false;

            //who scored?

            if (ball.getGlobalBounds().left > 0)
            {
                ++leftScore;

                leftScoreText.setString(toString(leftScore));
            }
            else
            {
                ++rightScore;

                rightScoreText.setString(toString(rightScore));
            }

            paddleTransition = true;

            paddleTransitionClock.restart();

            scoreTransition = true;

            scoreTransitionClock.restart();
        }

        //win/lose

        if (leftScore > 5)
        {
            //the player wins

            parameters.constructionParameters.control.setScreen<Win>(parameters.constructionParameters);

            return;
        }

        if (rightScore > 5)
        {
            //computer wins

            parameters.constructionParameters.control.setScreen<Lose>(parameters.constructionParameters);

            return;
        }
    }

    if (paddleTransition)
    {
        double time = paddleTransitionClock.getElapsedTime().asSeconds();

        double timeFraction = time - (int) time;

        double leftCenter = leftPaddle.getGlobalBounds().top + leftPaddle.getGlobalBounds().height/2;
        double rightCenter = rightPaddle.getGlobalBounds().top + rightPaddle.getGlobalBounds().height/2;

        double leftDifference = leftCenter - 240;
        double rightDifference = rightCenter - 240;

        leftPaddle.move(0, leftDifference/-10);
        rightPaddle.move(0, rightDifference/-10);

        if (time > 1)
        {
            paddleTransition = false;

            ballTransition = true;

            ballTransitionClock.restart();

            ball.setPosition(320, 240);
        }
    }

    if (scoreTransition)
    {
        double time = scoreTransitionClock.getElapsedTime().asSeconds();

        double timeFraction = time - (int) time;

        leftScoreText.setCharacterSize(100*timeFraction);
        leftScoreText.setOrigin(leftScoreText.getGlobalBounds().width/2, leftScoreText.getGlobalBounds().height/2);
        leftScoreText.setPosition(240, 250 - timeFraction*50);
        leftScoreText.setFillColor(sf::Color(255, 255, 255, (1 - timeFraction)*255));

        rightScoreText.setCharacterSize(100*timeFraction);
        rightScoreText.setOrigin(rightScoreText.getGlobalBounds().width/2, rightScoreText.getGlobalBounds().height/2);
        rightScoreText.setPosition(400, 250 - timeFraction*50);
        rightScoreText.setFillColor(sf::Color(255, 255, 255, (1 - timeFraction)*255));

        if (time > 1)
            scoreTransition = false;
    }

    if (ballTransition)
    {
        double time = ballTransitionClock.getElapsedTime().asSeconds();

        double timeFraction = time - (int) time;

        if (time > 1)
        {
            ballTransition = false;

            ball.setScale(1, 1);
            ball.setFillColor(sf::Color::White);

            textTransition = true;

            textTransitionClock.restart();
        }
        else
        {
            ball.setScale(1/timeFraction, 1/timeFraction);
            ball.setFillColor(sf::Color(255, 255, 255, timeFraction*255));
        }
    }

    if (textTransition)
    {
        double time = textTransitionClock.getElapsedTime().asSeconds();

        double timeFraction = time - (int) time;

        if (time > 5)
            textTransition = false;
        else if (time > 4)
        {
            centerText.setString("Go!");

            if (!gameActive)
            {
                gameActive = true;

                Random random;

                hSpeed = random.iRandomRange(1, 4) * (random.getBool() ? 1 : -1);
                vSpeed = random.iRandomRange(1, 4) * (random.getBool() ? 1 : -1);
            }
        }
        else if (time > 3)
            centerText.setString("1");
        else if (time > 2)
            centerText.setString("2");
        else if (time > 1)
            centerText.setString("3");
        else if (time > 0)
            centerText.setString("Ready?");

        centerText.setCharacterSize(100*timeFraction);
        centerText.setOrigin(centerText.getGlobalBounds().width/2, centerText.getGlobalBounds().height/2);
        centerText.setPosition(320, 200 - timeFraction*50);
        centerText.setFillColor(sf::Color(255, 255, 255, (1 - timeFraction)*255));
    }
}

void Singleplayer::draw(sf::RenderTarget & target, const TransitionInfo & transition)
{
    target.clear(sf::Color::Black);

    target.draw(leftPaddle);
    target.draw(rightPaddle);
    target.draw(ball);

    //ball trail

    if (!ballPositions.empty())
    {
        if (!ballTransition)
            ballPositions[0] = ball.getPosition();

        for (int i = ballPositions.size() - 1; i > 0; --i)
            ballPositions[i] = ballPositions[i - 1];

        for (int i = 0; i < ballPositions.size(); ++i)
        {
            ballTrail.setPosition(ballPositions[i]);

            if (i != 0)
            {
                ballTrail.setFillColor(sf::Color(255, 255, 255, (1 - ((float) i/ballPositions.size()))*255));

                target.draw(ballTrail);
            }
        }
    }

    //particles

    std::vector<CollisionParticle> toRemove;

    for (auto & particle : particles)
    {
        particle.life += 0.01;

        particle.position.x += std::cos(particle.angle)*particle.speed;
        particle.position.y += std::sin(particle.angle)*particle.speed;

        if (particle.life > 1)
            toRemove.push_back(particle);
    }

    for (CollisionParticle particle : toRemove)
        particles.erase(std::find(particles.begin(), particles.end(), particle));

    sf::VertexArray vertices;

    vertices.setPrimitiveType(sf::Points);

    for (CollisionParticle particle : particles)
        vertices.append(sf::Vertex(particle.position, sf::Color(255, 255, 255, (1 - particle.life)*255)));

    target.draw(vertices);

    if (textTransition)
        target.draw(centerText);

    if (scoreTransition)
    {
        target.draw(leftScoreText);
        target.draw(rightScoreText);
    }
}

void Singleplayer::onChangeIn(ScreenConstructionParameters parameters)
{
    ballTransitionClock.restart();
    textTransitionClock.restart();
}