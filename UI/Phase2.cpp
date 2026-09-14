#include "Phase2.hpp"

Phase2::Phase2(sf::RenderWindow& window, RobotController& robot)
    : window_(window), robot_(robot) {

    font_.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");

    title_.setFont(font_);
    title_.setCharacterSize(26);
    title_.setFillColor(sf::Color::White);
    title_.setPosition(180.f, 40.f);

    countText_.setFont(font_);
    countText_.setCharacterSize(22);
    countText_.setFillColor(sf::Color::Yellow);
    countText_.setPosition(320.f, 150.f);

    // Buttons
    auto makeBtn = [](sf::RectangleShape& btn, float x, float y, sf::Color c) {
        btn.setSize({80.f, 50.f});
        btn.setPosition(x, y);
        btn.setFillColor(c);
    };

    makeBtn(btnMinus_, 250.f, 200.f, sf::Color(180, 60, 60));
    makeBtn(btnPlus_,  450.f, 200.f, sf::Color(60, 140, 60));
    makeBtn(btnContinue_, 280.f, 300.f, sf::Color(70, 100, 180));
    btnContinue_.setSize({220.f, 55.f});

    txtMinus_.setFont(font_);
    txtMinus_.setString("-");
    txtMinus_.setCharacterSize(28);
    txtMinus_.setPosition(280.f, 208.f);

    txtPlus_.setFont(font_);
    txtPlus_.setString("+");
    txtPlus_.setCharacterSize(28);
    txtPlus_.setPosition(480.f, 208.f);

    txtContinue_.setFont(font_);
    txtContinue_.setString("Continue to Map");
    txtContinue_.setCharacterSize(20);
    txtContinue_.setPosition(305.f, 315.f);

    mapArea_.setSize({600.f, 400.f});
    mapArea_.setPosition(100.f, 100.f);
    mapArea_.setFillColor(sf::Color(25, 25, 35));
    mapArea_.setOutlineThickness(2.f);
    mapArea_.setOutlineColor(sf::Color(100, 100, 130));

    robotDot_.setRadius(12.f);
    robotDot_.setFillColor(sf::Color::Cyan);
    robotDot_.setOrigin(12.f, 12.f);
}

void Phase2::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        exitRequested_ = true;
        return;
    }

    if (event.type != sf::Event::MouseButtonPressed ||
        event.mouseButton.button != sf::Mouse::Left)
        return;

    sf::Vector2f mouse = window_.mapPixelToCoords(
        {event.mouseButton.x, event.mouseButton.y});

    if (stage_ == Stage::SelectCount) {
        if (btnMinus_.getGlobalBounds().contains(mouse) && obstacleCount_ > 2)
            obstacleCount_--;
        if (btnPlus_.getGlobalBounds().contains(mouse) && obstacleCount_ < 4)
            obstacleCount_++;
        if (btnContinue_.getGlobalBounds().contains(mouse))
            stage_ = Stage::ShowMap;   // skip confirmation for simplicity
    }
}

void Phase2::update() {
    auto pos = robot_.getPosition();
    robotDot_.setPosition(100.f + 300.f + pos.x, 100.f + 200.f + pos.y);
}

void Phase2::render() {
    if (stage_ == Stage::SelectCount) {
        title_.setString("Phase 2 - Select Number of Obstacles (2-4)");
        window_.draw(title_);

        countText_.setString("Obstacles: " + std::to_string(obstacleCount_));
        window_.draw(countText_);

        window_.draw(btnMinus_);
        window_.draw(txtMinus_);
        window_.draw(btnPlus_);
        window_.draw(txtPlus_);
        window_.draw(btnContinue_);
        window_.draw(txtContinue_);
    }
    else { // ShowMap
        title_.setString("Phase 2 - Map View (from Phase 1 data - placeholder)");
        window_.draw(title_);
        window_.draw(mapArea_);
        window_.draw(robotDot_);

        // Later: draw obstacles + real mapped environment from Phase 1
    }
}