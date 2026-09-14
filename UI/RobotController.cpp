#include "RobotController.hpp"
#include <iostream>

void RobotController::move(Direction dir) {
    const float step = 10.0f;
    switch (dir) {
        case Direction::Up:    pos_.y -= step; break;
        case Direction::Down:  pos_.y += step; break;
        case Direction::Left:  pos_.x -= step; break;
        case Direction::Right: pos_.x += step; break;
        default: break;
    }
    // Later: send real command to robot hardware / other modules
}

void RobotController::stop() {
    // Later: send stop command
}

Position RobotController::getPosition() const {
    return pos_;
}

void RobotController::setPosition(float x, float y) {
    pos_.x = x;
    pos_.y = y;
}

bool RobotController::connectToRobot(const std::string& /*port_or_ip*/) {
    // Placeholder – later open serial / TCP / shared memory etc.
    connected_ = true;
    std::cout << "[RobotController] Connected (placeholder)\n";
    return true;
}

void RobotController::sendCommand(const std::string& command) {
    if (!connected_) return;
    std::cout << "[RobotController] Sending: " << command << "\n";
    // Later: forward to other .cpp modules
}