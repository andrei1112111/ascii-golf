#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <thread>
#include <chrono>

// field size
const int WIDTH = 102;
const int HEIGHT = 6;

std::vector<std::pair<int, int>> calculateTragectory(const double v0,
                                                     const double angle_deg,
                                                     int GOLF_FIELD_FLAG_X,
                                                     const double r = 0.7,
                                                     const double g = 9.8,
                                                     const double dt = 0.1,
                                                     const double threshold = 0.5,
                                                     const double friction = 0.98,
                                                     const int max_steps = 1500)
{
    std::vector<std::pair<int, int>> result;

    double theta = angle_deg * M_PI / 180.0;
    double vx = v0 * std::cos(theta);
    double vy = v0 * std::sin(theta);
    double x = 0.0, y = 0.0;

    bool rolling = false; // ball rolls without changing y

    for (int step = 0; step < max_steps; ++step)
    {
        result.emplace_back(static_cast<int>(std::round(x)), static_cast<int>(std::round(y)));

        if (rolling)
        {
            x += vx * dt;
            y = 0.0;
            vx *= friction * 0.8; // slowing down harder
            if (std::abs(vx) < 0.1)
            {
                break;
            }
            if (x >= WIDTH) // bounce off the wall
            {
                x = WIDTH - 1e-6;
                vx = -vx * r;
            }
        }
        else
        {
            x += vx * dt;
            y += vy * dt;
            vy -= g * dt;

            if (y < 0.0)
            {
                y = 0.0;
                vy = -vy * r;
                vx *= r;
            }

            if (x < 0.0)
            {
                x = 0.0;
                vx = -vx * r;
            }
            else if (x >= WIDTH) // bounce off the wall
            {
                x = WIDTH - 1e-6;
                vx = -vx * r;
            }
            if (std::abs(vy) < 0.5)             //            \ suppress small jumps
                vy = 0.0;                       //                      |
            if (std::abs(vy) < 3.8 && y <= 0.5) // /
            {
                vy = 0.0;
                rolling = true;
            }
        }
        if (static_cast<int>(std::round(x)) == (GOLF_FIELD_FLAG_X + 13) and y <= 0.0) // hitting the hole
        {
            result.emplace_back(static_cast<int>(std::round(x)), static_cast<int>(std::round(y)));

            result.emplace_back(static_cast<int>(std::round(INT16_MIN)), static_cast<int>(std::round(INT16_MIN)));

            break;
        }

        if (y <= 0.0 && std::abs(vx) <= 1 && std::abs(vy) <= 1) // ball stoped
        {
            break;
        }
    }

    return result;
}
