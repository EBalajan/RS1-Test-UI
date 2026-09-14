#pragma once
#include <SFML/Graphics.hpp>
#include "RobotController.hpp"

class Phase1 {
public:
    Phase1(sf::RenderWindow& window, RobotController& robot);

    void handleEvent(const sf::Event& event);
    void update();
    void render();

    bool wantsToExit() const { return exitRequested_; }

private:
    sf::RenderWindow& window_;
    RobotController& robot_;
    bool exitRequested_ = false;

    sf::Font font_;
    sf::Text infoText_;
    sf::RectangleShape mapArea_;
    sf::CircleShape robotDot_;
};