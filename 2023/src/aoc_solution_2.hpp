#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <utility>
#include <unordered_map>
#include <cmath>

#include <utils.hpp>

size_t aoc_2023_2(const std::vector<std::string>& input_lines, bool is_part_1)
{
    // std::cout << "inside aoc_2023_2" << std::endl;
    size_t sum = 0;
    // std::cout << "problem " << input_lines[0] << std::endl;

    int max_red = 0;
    int max_green = 0;
    int max_blue = 0;
    if ( is_part_1 )
    {
        parse_red_green_blue(input_lines[0], max_red, max_green, max_blue);
    }
    // std::cout << "max_red: " << max_red << std::endl;
    // std::cout << "max_green: " << max_green << std::endl;
    // std::cout << "max_blue: " << max_blue << std::endl;

    int red, green, blue = 0;
    for ( size_t i = 1; i < input_lines.size(); i++ )
    {
        // std::cout << i << " " << input_lines[i] << std::endl;
        int min_red = 0, min_green = 0, min_blue = 0;
        std::vector<std::string> split_strings = split(input_lines[i], ": ");
        std::vector<std::string> split_games = split(split_strings.back(), "; ");
        bool is_possible = true;
        for ( const std::string& s : split_games )
        {
            parse_red_green_blue(s, red, green, blue);
            if ( is_part_1 )
            {
                if ( red > max_red || green > max_green || blue > max_blue )
                {
                    is_possible = false;
                    break;
                }
            }
            else
            {
                min_red = std::max(red, min_red);
                min_green = std::max(green, min_green);
                min_blue = std::max(blue, min_blue);
            }
        }
        if ( is_part_1 )
        {
            if ( is_possible )
            {
                int game_num = std::stoi(split(split_strings.front(), " ").back());
                sum += game_num;
            }
        }
        else
        {
            sum += (min_red * min_green * min_blue);
        }
    }
    return sum;
}
