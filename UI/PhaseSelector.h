#pragma once
#include <SFML/Graphics.hpp>

enum class AppPhase {
    Selector,
    Phase1_Movement,
    Phase2_Obstacles,
    Phase2_Map
};

class PhaseSelector {
public:
    PhaseSelector(sf::RenderWindow& window);

    void handleEvent(const sf::Event& event);
    void update();
    void render();

    AppPhase getSelectedPhase() const { return selected_; }
    bool isConfirmed() const { return confirmed_; }
    void reset();

private:
    sf::RenderWindow& window_;
    AppPhase selected_ = AppPhase::Selector;
    bool confirmed_ = false;

    sf::Font font_;
    sf::Text title_;
    sf::RectangleShape btnPhase1_;
    sf::RectangleShape btnPhase2_;
    sf::Text txtPhase1_;
    sf::Text txtPhase2_;
};