#ifndef TRAGECTORY_H
#define TRAGECTORY_H

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <format>

// calculate the trajectory iteratively using physical formulas
std::vector<std::pair<int, int>> calculateTragectory(const double v0,
                                                     const double angle_deg,
                                                     int GOLF_FIELD_FLAG_X,
                                                     const double r = 0.7,
                                                     const double g = 9.8,
                                                     const double dt = 0.1,
                                                     const double threshold = 0.5,
                                                     const double friction = 0.98,
                                                     const int max_steps = 1500);

#endif // TRAGECTORY_H
