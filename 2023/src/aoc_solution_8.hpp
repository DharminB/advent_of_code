#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <utility>
#include <map>
#include <unordered_map>
#include <cmath>

#include <utils.hpp>

size_t aoc_2023_8(const std::vector<std::string>& input_lines, bool is_part_1)
{
    std::cout << "inside aoc_2023_8" << std::endl;

    std::string directions = input_lines.front();
    std::cout << "directions: " << directions << std::endl;

    std::unordered_map<std::string, std::string> left, right;
    left.reserve(input_lines.size());
    right.reserve(input_lines.size());

    std::vector<std::string> starting_locations, ending_locations;

    for ( size_t i = 2; i < input_lines.size(); i++ )
    {
        std::vector<std::string> strs = split(input_lines[i], " = ");
        const std::string current_location = strs.front();
        if ( current_location.back() == 'A' )
        {
            starting_locations.push_back(current_location);
        }
        else if ( current_location.back() == 'Z' )
        {
            ending_locations.push_back(current_location);
        }
        std::vector<std::string> target_locations = split(strs.back(), ", ");
        left[current_location] = target_locations.front().substr(1);
        right[current_location] = target_locations.back().substr(0, target_locations.back().size()-1);
    }

    size_t num_of_steps = 0;

    if ( is_part_1 )
    {
        std::string loc = "AAA";
        const std::string target_loc = "ZZZ";
        while ( loc != target_loc )
        {
            for ( size_t i = 0; i < directions.size(); i++ )
            {
                if ( directions[i] == 'L' )
                {
                    loc = left.at(loc);
                }
                else
                {
                    loc = right.at(loc);
                }
                std::cout << "loc: " << loc << std::endl;
            }
            num_of_steps += directions.size();
        }
    }
    else
    {
        std::unordered_map<std::string, std::string> apply_directions;
        apply_directions.reserve(left.size());
        for ( auto itr = left.begin(); itr != left.end(); itr ++ )
        {
            std::string loc = itr->first;
            for ( size_t i = 0; i < directions.size(); i++ )
            {
                if ( directions[i] == 'L' )
                {
                    loc = left.at(loc);
                }
                else
                {
                    loc = right.at(loc);
                }
                // std::cout << "loc: " << loc << std::endl;
            }
            apply_directions[itr->first] = loc;
        }

        for ( auto itr = apply_directions.begin(); itr != apply_directions.end(); itr ++ )
        {
            std::cout << itr->first << " " << itr->second << std::endl;
        }

        std::vector<std::string> locs(starting_locations);
        // std::vector<std::string> locs(1, starting_locations.front());
        size_t prod = 1;
        for ( size_t i = 0; i < locs.size(); i++ )
        {
            num_of_steps = 0;
            std::cout << locs[i] << " " << num_of_steps << std::endl;
            while ( true )
            {
                // std::cout << locs[i] << " " << num_of_steps << std::endl;
                locs[i] = apply_directions.at(locs[i]);
                // num_of_steps += directions.size();
                num_of_steps ++;
                // std::cout << "num_of_steps: " << num_of_steps << std::endl;

                /* check if locs are ending locations */

                if ( locs[i].back() == 'Z' )
                {
                    break;
                }
            }
            std::cout << locs[i] << " " << num_of_steps << std::endl;
            std::cout << std::endl;
            prod *= num_of_steps;
        }
        num_of_steps = prod * directions.size();
    }

    return num_of_steps;
}

