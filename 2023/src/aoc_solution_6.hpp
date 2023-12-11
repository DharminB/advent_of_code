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

size_t aoc_2023_6(const std::vector<std::string>& input_lines, bool is_part_1)
{
    // std::cout << "inside aoc_2023_6" << std::endl;

    std::vector<std::string> time_strs = split(split(input_lines.front(), ": ").back(), " ");
    std::vector<std::string> dist_strs = split(split(input_lines.back(), ": ").back(), " ");

    std::vector<size_t> times;
    std::string time_str;
    for ( size_t i = 0; i < time_strs.size(); i++ )
    {
        if ( !time_strs[i].empty() )
        {
            if ( is_part_1 )
            {
                times.push_back(std::stoul(time_strs[i]));
            }
            else
            {
                time_str += time_strs[i];
            }
        }
    }
    if ( !is_part_1 )
    {
        times.push_back(std::stoul(time_str));
    }

    std::vector<size_t> distances;
    std::string dist_str;
    for ( size_t i = 0; i < dist_strs.size(); i++ )
    {
        if ( !dist_strs[i].empty() )
        {
            if ( is_part_1 )
            {
                distances.push_back(std::stoul(dist_strs[i]));
            }
            else
            {
                dist_str += dist_strs[i];
            }
        }
    }
    if ( !is_part_1 )
    {
        distances.push_back(std::stoul(dist_str));
    }

    // for ( size_t i = 0; i < times.size(); i++ )
    // {
    //     std::cout << i << " " << times[i] << std::endl;
    // }

    // for ( size_t i = 0; i < distances.size(); i++ )
    // {
    //     std::cout << i << " " << distances[i] << std::endl;
    // }

    size_t mul = 1;
    for ( size_t i = 0; i < times.size(); i++ )
    {
        const double t = static_cast<double>(times[i]);
        const double d = static_cast<double>(distances[i]);
        const double lower_sol_f = (t - std::sqrt(t*t - 4*(d+1))) / 2;
        const double upper_sol_f = (t + std::sqrt(t*t - 4*(d+1))) / 2;
        // std::cout << "lower_sol_f: " << lower_sol_f << std::endl;
        // std::cout << "upper_sol_f: " << upper_sol_f << std::endl;
        const size_t lower_sol = static_cast<size_t>(std::ceil(lower_sol_f));
        const size_t upper_sol = static_cast<size_t>(std::floor(upper_sol_f));
        // std::cout << "lower_sol: " << lower_sol << std::endl;
        // std::cout << "upper_sol: " << upper_sol << std::endl;
        const size_t diff = upper_sol - lower_sol + 1;
        // std::cout << "diff: " << diff << std::endl;
        mul *= diff;
    }

    return mul;
}

