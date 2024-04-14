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

void print_pattern(const std::vector<std::string>& pattern)
{
    for ( size_t i = 0; i < pattern.size(); i++ )
    {
        std::cout << pattern[i] << std::endl;
    }
    std::cout << std::endl;
}

std::vector<std::string> transpose(const std::vector<std::string>& pattern)
{
    /* transpose pattern */
    std::vector<std::string> pattern_T(pattern.front().size());
    for ( size_t i = 0; i < pattern.size(); i++ )
    {
        for ( size_t j = 0; j < pattern[i].size(); j++ )
        {
            pattern_T[j] += pattern[i][j];
        }
    }
    return pattern_T;
}

bool is_matching(
        const std::string& s1,
        const std::string& s2,
        const size_t allowed_num_of_mismatch,
        size_t& num_of_mismatch)
{
    if ( s1.size() != s2.size() )
    {
        return false;
    }

    num_of_mismatch = 0;
    for ( size_t i = 0; i < s1.size(); i++ )
    {
        if ( s1[i] != s2[i] )
        {
            num_of_mismatch ++;
            if ( num_of_mismatch > allowed_num_of_mismatch )
            {
                return false;
            }
        }
    }
    return true;
}

/* find horizontal pattern (if it exists) */
int find_horizontal_mirror(
        const std::vector<std::string>& pattern,
        const size_t allowed_num_of_mismatch = 0)
{
    for ( size_t i = 0; i+1 < pattern.size(); i++ )
    {
        size_t num_of_mismatch = 0;
        if ( is_matching(pattern[i], pattern[i+1], allowed_num_of_mismatch, num_of_mismatch) )
        {
            std::cout << "found repeated line at " << i << std::endl;

            const size_t before = i + 1;
            const size_t after = pattern.size() - i - 1;
            const size_t check_limit = std::min(before, after);

            bool all_match = true;
            for ( size_t j = 1; j < check_limit; j++ )
            {
                const size_t up = i - j;
                const size_t down = i + j + 1;
                size_t n_mismatch = 0;
                if ( !is_matching(pattern[up], pattern[down], allowed_num_of_mismatch - num_of_mismatch, n_mismatch) )
                {
                    std::cout << "pattern " << up << " and " << down << " do not match" << std::endl;
                    all_match = false;
                    break;
                }
                num_of_mismatch += n_mismatch;
            }
            if ( all_match && num_of_mismatch == allowed_num_of_mismatch )
            {
                return static_cast<int>(i);
            }
        }
    }
    return -1;

}

size_t aoc_2023_13(const std::vector<std::string>& input_lines, bool is_part_1)
{
    std::cout << "inside aoc_2023_13" << std::endl;

    for ( size_t i = 0; i < input_lines.size(); i++ )
    {
        std::cout << input_lines[i] << std::endl;
    }

    size_t total = 0;

    /* separate patters from each other */
    std::vector<std::vector<std::string>> patterns;
    size_t pattern_start_index = 0;
    for ( size_t i = 0; i < input_lines.size(); i++ )
    {
        if ( input_lines[i].empty() || i+1 == input_lines.size() )
        {
            std::vector<std::string> pattern;
            const size_t end_index = ( i+1 == input_lines.size() ) ? i+1 : i;
            pattern.reserve(end_index-pattern_start_index);
            pattern.insert(
                    pattern.end(),
                    input_lines.begin()+pattern_start_index,
                    input_lines.begin()+end_index);
            patterns.push_back(pattern);
            pattern_start_index = i+1;
        }
    }

    const size_t allowed_num_of_mismatch = ( is_part_1 ) ? 0 : 1;

    for ( size_t p = 0; p < patterns.size(); p++ )
    {
        const std::vector<std::string>& pattern = patterns[p];
        std::cout << "pattern " << p << std::endl;
        // print_pattern(pattern);

        int horizontal_mirror_pos = find_horizontal_mirror(pattern, allowed_num_of_mismatch);
        std::cout << "horizontal_mirror_pos: " << horizontal_mirror_pos << std::endl;

        if ( horizontal_mirror_pos < 0 )
        {
            std::vector<std::string> pattern_T = transpose(pattern);
            // print_pattern(pattern_T);

            int vertical_mirror_pos = find_horizontal_mirror(pattern_T, allowed_num_of_mismatch);
            std::cout << "vertical_mirror_pos: " << vertical_mirror_pos << std::endl;

            if ( vertical_mirror_pos < 0 )
            {
                std::cout << "ERROR: neither horizontal nor vertical mirror found in pattern " << p << std::endl;
                print_pattern(pattern);
                return 0;
                // continue;
            }

            total += vertical_mirror_pos + 1;
        }
        else
        {
            total += (100 * (horizontal_mirror_pos+1));
        }

    }

    return total;
}
