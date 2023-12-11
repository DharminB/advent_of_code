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

size_t aoc_2023_4(const std::vector<std::string>& input_lines, bool is_part_1)
{
    // std::cout << "inside aoc_2023_4" << std::endl;
    size_t sum = 0;

    std::vector<size_t> num_of_cards(input_lines.size(), 1);

    int max_num = 100; // only 2 digit nums are allowed
    for ( size_t i = 0; i < input_lines.size(); i++ )
    {
        std::cout << input_lines[i] << std::endl;
        std::vector<std::string> split_strings = split(split(input_lines[i], ": ").back(), " | ");
        std::vector<std::string> winning_num_strs = split(split_strings.front(), " ");
        std::vector<std::string> my_num_strs = split(split_strings.back(), " ");
        std::vector<bool> is_winning_num(max_num, false);
        for ( size_t j = 0; j < winning_num_strs.size(); j++ )
        {
            if ( !winning_num_strs[j].empty() )
            {
                int num = std::stoi(winning_num_strs[j]);
                if ( num < max_num )
                {
                    is_winning_num[num] = true;
                }
            }
        }
        size_t num_of_matches = 0;
        for ( size_t j = 0; j < my_num_strs.size(); j++ )
        {
            if ( !my_num_strs[j].empty() )
            {
                int num = std::stoi(my_num_strs[j]);
                if ( num < max_num && is_winning_num[num] )
                {
                    num_of_matches ++;
                }
            }
        }
        // std::cout << "num_of_matches: " << num_of_matches << std::endl;
        const size_t points = ( num_of_matches > 0 ) ? std::pow(2, num_of_matches-1) : 0;
        sum += points;

        if ( !is_part_1 )
        {
            for ( size_t j = 0; j < num_of_matches; j++ )
            {
                num_of_cards[i+j+1] += num_of_cards[i];
            }
        }
    }

    if ( !is_part_1 )
    {
        sum = 0;
        for ( size_t i = 0; i < num_of_cards.size(); i++ )
        {
            sum += num_of_cards[i];
        }
    }

    return sum;
}
