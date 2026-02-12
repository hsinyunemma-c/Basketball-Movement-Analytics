// Reads and validates basketball movement data
// groups samples by player, computes per-player statistics,
// and outputs individual results and overall
// winners for distance, speed, and slowdown
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "Sample.h"
#include "PlayerStats.h"
using namespace std;

int main() {
    vector<Sample> samples;
    int validCount = 0;
    int invalidCount = 0;

    string line;
    while (getline(cin, line)) {
        if (line.empty()) {
            continue;
        }
        // Put whole line into strinstream
        // ss = stringstream object
        stringstream ss(line);
        int id, time;
        double x, y;

        // Try to read 4 values from ss
        // Check wheather line has 4 valid nums
        if (!(ss >> id >> time >> x >> y)) {
            invalidCount++;
            continue;
        }

        if (id == -1) {
            break;
        }

        Sample s(id, time, x, y);

        if (s.isValid()) {
            samples.push_back(s);
            validCount++;
        } else {
            invalidCount++;
        }
    }

    // Counts how many in the valid samples
    vector<int> uniqueIDs;
    for (size_t i = 0; i < samples.size(); i++) {
    int pid = samples[i].getPlayerID();
    bool found = false;

        for (size_t j = 0; j < uniqueIDs.size(); j++) {
        if (uniqueIDs[j] == pid) {
            found = true;
            break;
        }
    }

        if (!found) {
            uniqueIDs.push_back(pid);
        }

    }

    cout << "Valid records: " << validCount << endl;
    cout << "Invalid records: " << invalidCount << endl;
    cout << "Unique Players: " << uniqueIDs.size() << endl;

    vector<PlayerStats> players;
    for (size_t i = 0; i < uniqueIDs.size(); i++) {
        players.push_back(PlayerStats(uniqueIDs[i]));
    }

    // Allocate sample to right player
    for (size_t i = 0; i < samples.size(); i++) {
        //把這筆sample屬於哪個球員先記下來
        int pid = samples[i].getPlayerID();
        // playerID = sampleID
        for (size_t j = 0; j < players.size(); j++) {
            if (players[j].getPlayerID() == pid) {
                players[j].addSample(samples[i]);
                break;
            }
        }
    }
    

    for (size_t i = 0; i < players.size(); i++) {
        players[i].computeStats();
    }

    sort(players.begin(), players.end(),
         [](const PlayerStats& a, const PlayerStats& b) {
             return a.getPlayerID() < b.getPlayerID();
     });

     cout << fixed << setprecision(2);

    for (size_t i = 0; i < players.size(); i++) {
        cout << "Player " << players[i].getPlayerID() << ": "
             << "distance=" << players[i].getTotalDistance() << " "
             << "max_speed=" << players[i].getMaxSpeed() << " ";

        if (players[i].getSampleCount() < 3) {
           cout << "slowdown=N/A\n";
        } else {
            cout << "slowdown=" << players[i].getLargestSlowdown() << "\n";
        }
    }

    int distWinner = players[0].getPlayerID();
    double maxDist = players[0].getTotalDistance();

    int speedWinner = players[0].getPlayerID();
    double maxSpeed = players[0].getMaxSpeed();

    int slowWinner = players[0].getPlayerID();
    double maxSlow = players[0].getLargestSlowdown();

    for (size_t i = 0; i < players.size(); i++) {

    if (players[i].getTotalDistance() > maxDist) {
        maxDist = players[i].getTotalDistance();
        distWinner = players[i].getPlayerID();
    }

    if (players[i].getMaxSpeed() > maxSpeed) {
        maxSpeed = players[i].getMaxSpeed();
        speedWinner = players[i].getPlayerID();
    }

    if (players[i].getLargestSlowdown() > maxSlow) {
        maxSlow = players[i].getLargestSlowdown();
        slowWinner = players[i].getPlayerID();
    }
}


    cout << "MOST DISTANCE: Player " << distWinner << endl;
    cout << "FASTEST PLAYER: Player " << speedWinner << endl;
    cout << "BIGGEST SLOWDOWN: Player " << slowWinner << endl;

return 0;
}
