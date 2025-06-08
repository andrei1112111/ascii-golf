#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <random>

#include "graphics.h"
#include "IO.h"
#include "tragectory.h"

int main()
{
    bool game = true;

    // initialize power/angle bar
    PowAngBar bar;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 80); // uniform [0, 80]

    int GOLF_FIELD_FLAG_X = dist(gen);

    // start screen
    startScreen();
    while (true)
    {
        const char ch = getCharNonBlocking();
        if (ch == 's' || ch == 'S') // just waiting for start button s
        {
            break;
        }
        if (ch == 'q' || ch == 'Q')
        {
            game = false;
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    //
    // game loop
    while (game)
    {
        //
        bool repr = true; // update screen
        bool won = false;
        std::vector<std::pair<int, int>> tragectory; // ball tragectory

        // player chooses the power and angle of impact
        while (true)
        {
            if (repr == true)
            {
                clearConsole();
                std::cout << putBorder(putFlag(frames[0], GOLF_FIELD_FLAG_X));
                std::cout << bar.frame();
                repr = false;
            }
            //
            const char ch = getCharNonBlocking();
            if (ch == 'n' || ch == 'N') // start simulation
            {
                break;
            }
            if (ch == 'q' || ch == 'Q')
            {
                game = false;
                break;
            }
            if (ch == 'd')
            {
                bar.increase_power();
                repr = true;
            }
            if (ch == 'a')
            {
                bar.decrease_power();
                repr = true;
            }
            if (ch == 'w')
            {
                bar.increase_angle();
                repr = true;
            }
            if (ch == 's')
            {
                bar.decrease_angle();
                repr = true;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        //
        // simulation with animation
        while (game)
        {
            for (int fc = 0; fc < frames.size(); ++fc)
            {
                //
                const char ch = getCharNonBlocking();
                if (ch == 'n' || ch == 'N')
                {
                    break;
                }
                if (ch == 'q' || ch == 'Q')
                {
                    game = false;
                    break;
                }

                if (fc == 10) // the frame when the character swings and aims
                {             // run calculating tragectory
                    tragectory = calculateTragectory(
                        bar.getfV(), bar.getfA(), GOLF_FIELD_FLAG_X);
                }

                if (fc == 13) // the frame when the character hit the ball
                {             // run ball flying animation
                    std::string chframe = putFlag(frames[fc], GOLF_FIELD_FLAG_X);

                    for (auto p : tragectory)
                    {
                        clearConsole();

                        if (p.first == INT16_MIN && p.second == INT16_MIN) // tragectory contains this values if the ball hit the hole
                        {
                            won = true;
                            GOLF_FIELD_FLAG_X = dist(gen);

                            break;
                        }

                        p.first += 11; // offset x
                        p.second += 2; // offset y

                        // draw ball only if its on screen
                        if (getFrameCords(p.first, p.second) > 0 and getFrameCords(p.first, p.second) < frames[fc].size())
                        {
                            chframe[getFrameCords(p.first, p.second)] = 'o';

                            std::cout << putBorder(chframe);
                            std::cout << bar.frame();

                            chframe[getFrameCords(p.first, p.second)] = '.'; // ball shadow tragectory

                            std::this_thread::sleep_for(std::chrono::milliseconds(50));
                        }
                        else
                        {
                            std::cout << putBorder(chframe);
                            std::cout << bar.frame();
                            std::this_thread::sleep_for(std::chrono::milliseconds(30));
                        }

                        const char ch = getCharNonBlocking();
                        if (ch == 'n' || ch == 'N')
                        {
                            break;
                        }
                        if (ch == 'q' || ch == 'Q')
                        {
                            game = false;
                            break;
                        }
                    }
                }

                clearConsole();
                if (won == true)
                {
                    // changing miss to won in the animation
                    std::cout << putBorder(putFlag(replaceFirst(frames[fc], "miss :(", "WON !!!"), GOLF_FIELD_FLAG_X));
                }
                else
                {
                    std::cout << putBorder(putFlag(frames[fc], GOLF_FIELD_FLAG_X));
                }

                std::cout << bar.frame();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }

            break;
        }
    }

    quitScreen();
    return 0;
}
