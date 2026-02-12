#include "Sample.h"

Sample::Sample(int id, int time, double xPos, double yPos)
    :playerID(id), timeSec(time), x(xPos), y(yPos) {     // Initialization

    // Validation logic, turn false if anything wrong
    valid = true;

    if (playerID < 1 || playerID > 99) {
     valid = false;
    }
    if (timeSec < 0 || timeSec > 3600) {
     valid = false;
    }
    if (x < 0.0 || x > 94.0) {
        valid = false;
    }
    if (y < 0.0 || y > 50.0) {
        valid = false;
    }
}

// Function definition
int Sample::getPlayerID() const { return playerID; }
int Sample::getTimeSec() const { return timeSec; }
double Sample::getX() const { return x; }
double Sample::getY() const { return y; }
bool Sample::isValid() const { return valid; }
