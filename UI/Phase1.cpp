#include "Phase1.hpp"

Phase1::Phase1(sf::RenderWindow& window, RobotController& robot)
    : window_(window), robot_(robot) {

    font_.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");

    infoText_.setFont(font_);
    infoText_.setCharacterSize(18);
    infoText_.setFillColor(sf::Color::White);
    infoText_.setPosition(20.f, 20.f);
    infoText_.setString(
        "PHASE 1 - Manual Control\n"
        "Arrow Keys or WASD : Move robot\n"
        "Mouse click on map : Move toward point (placeholder)\n"
        "ESC : Back to menu"
    );

    // Simple map area (placeholder for real mapping)
    mapArea_.setSize({600.f, 450.f});
    mapArea_.setPosition(100.f, 120.f);
    mapArea_.setFillColor(sf::Color(30, 30, 40));
    mapArea_.setOutlineColor(sf::Color(100, 100, 120));
    mapArea_.setOutlineThickness(2.f);

    robotDot_.setRadius(12.f);
    robotDot_.setFillColor(sf::Color::Cyan);
    robotDot_.setOrigin(12.f, 12.f);
}

void Phase1::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        using Dir = RobotController::Direction;
        switch (event.key.code) {
            case sf::Keyboard::Up:
            case sf::Keyboard::W:    robot_.move(Dir::Up);    break;
            case sf::Keyboard::Down:
            case sf::Keyboard::S:    robot_.move(Dir::Down);  break;
            case sf::Keyboard::Left:
            case sf::Keyboard::A:    robot_.move(Dir::Left);  break;
            case sf::Keyboard::Right:
            case sf::Keyboard::D:    robot_.move(Dir::Right); break;
            case sf::Keyboard::Escape: exitRequested_ = true; break;
            default: break;
        }
    }

    // Mouse click on map (placeholder – just moves robot toward click)
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {

        sf::Vector2f mouse = window_.mapPixelToCoords(
            {event.mouseButton.x, event.mouseButton.y});

        if (mapArea_.getGlobalBounds().contains(mouse)) {
            // Simple move toward click (placeholder)
            auto pos = robot_.getPosition();
            float dx = mouse.x - (100.f + 300.f + pos.x); // rough centre offset
            float dy = mouse.y - (120.f + 225.f + pos.y);

            if (std::abs(dx) > std::abs(dy)) {
                robot_.move(dx > 0 ? RobotController::Direction::Right
                                   : RobotController::Direction::Left);
            } else {
                robot_.move(dy > 0 ? RobotController::Direction::Down
                                   : RobotController::Direction::Up);
            }
        }
    }
}

void Phase1::update() {
    auto pos = robot_.getPosition();
    // Keep robot inside the map area visually
    robotDot_.setPosition(100.f + 300.f + pos.x, 120.f + 225.f + pos.y);
}

void Phase1::render() {
    window_.draw(infoText_);
    window_.draw(mapArea_);
    window_.draw(robotDot_);

    // Later: draw real mapped environment here
}