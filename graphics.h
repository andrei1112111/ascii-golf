#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "IO.h"

#include <iostream>
#include <string>
#include <vector>

//------------[SETTINGS]-------------
#define SCREEN_WIDTH 116
#define SCREEN_HEIGHT 7
#define GOLF_FIELD_FLAG_OFFSET_H 24
#define GOLF_FLAG_HEIGHT 6

#define BAR_SIZE 20
// -----------------------------------------

// draw border around on frame
std::string putBorder(std::string frame);

// draw flag on frame
std::string putFlag(std::string frame, int GOLF_FIELD_FLAG_X);

// screen[y][x] -> screen[cord)
int getFrameCords(const int x, const int y);

std::string replaceFirst(const std::string &str, const std::string &from, const std::string &to);

// power and angle bar
// displays power and angle selected by the player
class PowAngBar
{
private:
    float power;
    float angle;

    int pb = 0;
    int ab = 0;

    float maxAngle = 80.0;
    float minAngle = 15.0;

    float maxPower = 25.0;
    float minPower = 10.0;

public:
    PowAngBar()
    {
        power = minPower;
        angle = minAngle;
    }

    void increase_power()
    {
        if (pb + 1 > BAR_SIZE)
        {
            pb = BAR_SIZE;
            power = maxPower;
        }
        else
        {
            pb += 1;
            power += (maxPower - minPower) / BAR_SIZE;
        }
    }
    void increase_angle()
    {
        if (ab + 1 > BAR_SIZE)
        {
            ab = BAR_SIZE;
            angle = maxAngle;
        }
        else
        {
            ab += 1;
            angle += (maxAngle - minAngle) / BAR_SIZE;
        }
    }

    void decrease_power()
    {
        if (pb - 1 < 0)
        {
            pb = 0;
            power = minPower;
        }
        else
        {
            pb -= 1;
            power -= (maxPower - minPower) / BAR_SIZE;
        }
    }
    void decrease_angle()
    {
        if (ab - 1 < 0)
        {
            ab = 0;
            angle = minAngle;
        }
        else
        {
            ab -= 1;
            angle -= (maxAngle - minAngle) / BAR_SIZE;
        }
    }

    // render bar
    std::string frame()
    {
        std::string frame;

        // frame += "+" + std::string(BAR_SIZE + 1 + BAR_SIZE, '-') + "+\n";
        frame += "| power: [" + std::string(pb, '#') + std::string(BAR_SIZE - pb, '~') + "] |" + " angle: [" + std::string(ab, '#') + std::string(BAR_SIZE - ab, '~') + "] a/d to change power w/s to change angle  n to start |\n";

        frame += "+" + std::string(BAR_SIZE + 75 + BAR_SIZE, '-') + "+\n";

        return frame;
    }

    float getfV() { return static_cast<double>(power); }
    float getfA() { return static_cast<double>(angle); }
};

void quitScreen();
void startScreen();

// golf animation frames
extern std::vector<std::string> frames;

#endif // GRAPHICS_H
