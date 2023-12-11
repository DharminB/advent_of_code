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

size_t aoc_2023_1(const std::vector<std::string>& input_lines, bool is_part_1)
{
    // std::cout << "inside aoc_2023_1" << std::endl;
    size_t sum = 0;
    for ( size_t i = 0; i < input_lines.size(); i++ )
    {
        // std::cout << i << " " << input_lines[i] << std::endl;

        int first_digit = 0;
        int last_digit = 0;

        if ( is_part_1 )
        {
            first_digit = get_first_digit(input_lines[i]);
            last_digit = get_last_digit(input_lines[i]);
        }
        else
        {
            first_digit = get_first_digit_spelled(input_lines[i]);
            last_digit = get_last_digit_spelled(input_lines[i]);
        }

        // std::cout << "first_digit: " << first_digit << std::endl;
        // std::cout << "last_digit: " << last_digit << std::endl;
        sum += (first_digit * 10) + last_digit;
    }
    return sum;
}
