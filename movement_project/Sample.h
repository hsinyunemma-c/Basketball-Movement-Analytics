// Data for player at specific time and position
// store playerID, time in seconds, x, y, validity

#ifndef SAMPLE_H
#define SAMPLE_H

class Sample {
private:
    int playerID;  // 1-99
    int timeSec;   // 0-3600s
    double x;      // 0.0-94.0 (court w)
    double y;      // 0.0-50.0 (court l)
    bool valid;    // validation result

public:
    Sample(int id, int time, double xPos, double yPos);

    // Class member function declarations
    int getPlayerID() const;
    int getTimeSec() const;
    double getX() const;
    double getY() const;
    bool isValid() const;  // Returns validation result
};

#endif

