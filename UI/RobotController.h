#pragma once
#include <string>
#include <vector>

struct Position {
    float x = 0.0f;
    float y = 0.0f;
};

class RobotController {
public:
    enum class Direction { Up, Down, Left, Right, None };

    RobotController() = default;

    // These will later talk to your real C++ robot modules
    void move(Direction dir);
    void stop();
    Position getPosition() const;
    void setPosition(float x, float y);

    // Placeholder for future communication with other .cpp modules
    bool connectToRobot(const std::string& port_or_ip);
    void sendCommand(const std::string& command);

private:
    Position pos_;
    bool connected_ = false;
};