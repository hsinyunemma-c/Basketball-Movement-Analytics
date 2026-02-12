#include "PlayerStats.h"
#include <cmath>
using namespace std;

PlayerStats::PlayerStats(int id)
    : playerID(id), totalDistance(0.0), maxSpeed(0.0), largestSlowdown(0.0) {}

void PlayerStats::addSample(const Sample& s) {
    samples.push_back(s);
}

int PlayerStats::getPlayerID() const {
    return playerID;
}

double PlayerStats::getTotalDistance() const {
    return totalDistance;
}

double PlayerStats::getMaxSpeed() const {
    return maxSpeed;
}

double PlayerStats::getLargestSlowdown() const {
    return largestSlowdown;
}

int PlayerStats::getSampleCount() const {
    return static_cast<int>(samples.size());
}

bool PlayerStats::hasSlowdown() const {
    return getSampleCount() >= 3 && largestSlowdown > 0.0;
}

double PlayerStats::getMaxSlowdown() const {
    return largestSlowdown;
}

// ComputeStats(): total_dis, maxspeed, largestSlowdown
void PlayerStats::computeStats() {
    if (samples.size() < 2) {
        totalDistance = 0.0;
        maxSpeed = 0.0;
        largestSlowdown = 0.0;
        return;
    }

    totalDistance = 0.0;
    maxSpeed = 0.0;
    largestSlowdown = 0.0;

    vector<double> speeds;

    // dis + speed + Maxspeed
    for (size_t i = 1; i < samples.size(); i++) {
        double x1 = samples[i-1].getX();
        double y1 = samples[i-1].getY();
        double x2 = samples[i].getX();
        double y2 = samples[i].getY();
        int t1 = samples[i-1].getTimeSec();
        int t2 = samples[i].getTimeSec();

        double dx = x2 - x1;
        double dy = y2 - y1;
        double segmentDist = sqrt(dx * dx + dy * dy);
        totalDistance += segmentDist;

        int dt = t2 - t1;
        if (dt > 0) {
            double speed = segmentDist / dt;
            speeds.push_back(speed);  //need for slowdown
            if (speed > maxSpeed) {
                maxSpeed = speed;
            }
        }
    }

    // slowdown
    if (speeds.size() < 2) {
        largestSlowdown = 0.0;
        return;
    }

    for (size_t i = 1; i < speeds.size(); i++) {
        double drop = speeds[i-1] - speeds[i];
        if (drop > largestSlowdown) {
            largestSlowdown = drop;
        }
    }
}

