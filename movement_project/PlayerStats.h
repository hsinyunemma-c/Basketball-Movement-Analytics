// Computes and stores analytics for one player
// calculates distance, speed, and slowdown for a player

#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H

#include <vector>
#include "Sample.h"
using namespace std;

class PlayerStats {
private:
    int playerID;              // Player identifier
    double totalDistance;      // Total distance traveled
    double maxSpeed;           // Highest speed achieved
    double largestSlowdown;    // Biggest speed drop (fatigue)
    vector<Sample> samples;    // All valid samples for this player

public:
    PlayerStats(int id);

    void addSample(const Sample &s);
    void computeStats();

    int getPlayerID() const;
    double getTotalDistance() const;
    double getMaxSpeed() const;
    double getLargestSlowdown() const;
    int getSampleCount() const;  // Returns samples.size()

    bool hasSlowdown() const;       // It happened?
    double getMaxSlowdown() const;  // How big?
};
#endif
