#include "PhaseSelector.hpp"
#include <iostream>

PhaseSelector::PhaseSelector(sf::RenderWindow& window) : window_(window) {
    if (!font_.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        // Fallback – try another common path or leave empty
        std::cerr << "Warning: Could not load font\n";
    }

    title_.setFont(font_);
    title_.setString("RS1 Robot Control - Select Phase");
    title_.setCharacterSize(28);
    title_.setFillColor(sf::Color::White);
    title_.setPosition(180.f, 80.f);

    // Phase 1 Button
    btnPhase1_.setSize({400.f, 70.f});
    btnPhase1_.setPosition(200.f, 200.f);
    btnPhase1_.setFillColor(sf::Color(70, 130, 180));

    txtPhase1_.setFont(font_);
    txtPhase1_.setString("Phase 1: Manual Movement + Mapping");
    txtPhase1_.setCharacterSize(20);
    txtPhase1_.setFillColor(sf::Color::White);
    txtPhase1_.setPosition(230.f, 220.f);

    // Phase 2 Button
    btnPhase2_.setSize({400.f, 70.f});
    btnPhase2_.setPosition(200.f, 300.f);
    btnPhase2_.setFillColor(sf::Color(60, 140, 90));

    txtPhase2_.setFont(font_);
    txtPhase2_.setString("Phase 2: Obstacle Placement");
    txtPhase2_.setCharacterSize(20);
    txtPhase2_.setFillColor(sf::Color::White);
    txtPhase2_.setPosition(250.f, 320.f);
}

void PhaseSelector::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {

        sf::Vector2f mousePos = window_.mapPixelToCoords(
            {event.mouseButton.x, event.mouseButton.y});

        if (btnPhase1_.getGlobalBounds().contains(mousePos)) {
            selected_ = AppPhase::Phase1_Movement;
            confirmed_ = true;
        }
        else if (btnPhase2_.getGlobalBounds().contains(mousePos)) {
            selected_ = AppPhase::Phase2_Obstacles;
            confirmed_ = true;
        }
    }
}

void PhaseSelector::update() {}

void PhaseSelector::render() {
    window_.draw(title_);
    window_.draw(btnPhase1_);
    window_.draw(txtPhase1_);
    window_.draw(btnPhase2_);
    window_.draw(txtPhase2_);
}

void PhaseSelector::reset() {
    confirmed_ = false;
    selected_ = AppPhase::Selector;
}