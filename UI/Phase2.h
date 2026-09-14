#pragma once
#include <SFML/Graphics.hpp>
#include "RobotController.hpp"

class Phase2 {
public:
    Phase2(sf::RenderWindow& window, RobotController& robot);

    void handleEvent(const sf::Event& event);
    void update();
    void render();

    bool wantsToExit() const { return exitRequested_; }

private:
    enum class Stage { SelectCount, Confirmation, ShowMap };

    sf::RenderWindow& window_;
    RobotController& robot_;
    Stage stage_ = Stage::SelectCount;
    int obstacleCount_ = 2;
    bool exitRequested_ = false;

    sf::Font font_;
    sf::Text title_;
    sf::Text countText_;
    sf::RectangleShape btnMinus_, btnPlus_, btnContinue_;
    sf::Text txtMinus_, txtPlus_, txtContinue_;
    sf::RectangleShape mapArea_;
    sf::CircleShape robotDot_;
};