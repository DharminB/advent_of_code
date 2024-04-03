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

bool is_spring_str_valid(
        const std::string& spring_str,
        const std::vector<int>& contiguous_spring)
{
    std::vector<std::string> hash_strs = split(spring_str, ".");
    size_t spring_index = 0;
    for ( size_t i = 0; i < hash_strs.size(); i++ )
    {
        if ( hash_strs[i].empty() )
        {
            continue;
        }

        if ( hash_strs[i].size() == static_cast<size_t>(contiguous_spring[spring_index]) )
        {
            spring_index ++;
        }
        else
        {
            return false;
        }
    }
    return true;
}

size_t aoc_2023_12(const std::vector<std::string>& input_lines, bool is_part_1)
{
    std::cout << "inside aoc_2023_12" << std::endl;

    std::vector<std::string> spring_strs;
    std::vector<std::vector<int>> contiguous_springs;

    for ( size_t i = 0; i < input_lines.size(); i++ )
    {
        std::cout << input_lines[i] << std::endl;
        std::vector<std::string> strs = split(input_lines[i], " ");
        if ( is_part_1 )
        {
            spring_strs.push_back(strs.front());
        }
        else
        {
            std::string spring_str = strs.front();
            for ( size_t j = 0; j < 4; j++ )
            {
                spring_str += "?" + strs.front();
            }
            spring_strs.push_back(spring_str);
        }
        std::string contiguous_spring_str;
        if ( is_part_1 )
        {
            contiguous_spring_str = strs.back();
        }
        else
        {
            contiguous_spring_str = strs.back();
            for ( size_t j = 0; j < 4; j++ )
            {
                contiguous_spring_str += "," + strs.back();
            }
        }
        std::vector<std::string> nums = split(contiguous_spring_str, ",");
        std::vector<int> contiguous_spring(nums.size());
        for ( size_t j = 0; j < nums.size(); j++ )
        {
            contiguous_spring[j] = std::stoi(nums[j]);
        }
        contiguous_springs.push_back(contiguous_spring);
    }

    size_t total = 0;
    for ( size_t k = 0; k < spring_strs.size(); k++ )
    {
        const std::string& spring_str = spring_strs[k];
        const std::vector<int>& contiguous_spring = contiguous_springs[k];
        // std::cout << "spring_str: " << spring_str << std::endl;
        // std::cout << "contiguous_spring: " << printVec<int>(contiguous_spring) << std::endl;
        /* count num of ? and # */
        size_t question_count = 0, hash_count = 0;
        std::vector<size_t> question_indexes;
        for ( size_t i = 0; i < spring_str.size(); i++ )
        {
            if ( spring_str[i] == '?' )
            {
                question_count ++;
                question_indexes.push_back(i);
            }
            else if ( spring_str[i] == '#' )
            {
                hash_count ++;
            }
        }
        // std::cout << "question_count: " << question_count << std::endl;
        // std::cout << "hash_count: " << hash_count << std::endl;

        size_t total_hash_count = 0;
        for ( size_t i = 0; i < contiguous_spring.size(); i++ )
        {
            total_hash_count += contiguous_spring[i];
        }
        // std::cout << "total_hash_count: " << total_hash_count << std::endl;

        const size_t required_hash_count = total_hash_count - hash_count;
        // std::cout << "required_hash_count: " << required_hash_count << std::endl;

        // std::cout << "combinations: " << combination(question_count, required_hash_count) << std::endl;

        /* generate combinations */
        std::vector<std::vector<bool>> combinations = generate_combinations(
                question_count, required_hash_count);
        // std::cout << "combinations:" << std::endl;
        // for ( size_t i = 0; i < combinations.size(); i++ )
        // {
        //     std::cout << printVec<bool>(combinations[i]) << std::endl;
        // }
        size_t counter = 0;
        for ( size_t i = 0; i < combinations.size(); i++ )
        {
            std::string spring_str_candidate = spring_str;
            for ( size_t j = 0; j < question_indexes.size(); j++ )
            {
                spring_str_candidate[question_indexes[j]] = ( combinations[i][j] ) ? '#' : '.';
            }
            // std::cout << spring_str_candidate << std::endl;
            const bool valid = is_spring_str_valid(spring_str_candidate, contiguous_spring);
            // std::cout << "valid: " << valid << std::endl;
            if ( valid )
            {
                counter ++;
            }
        }
        // std::cout << "counter: " << counter << std::endl;
        // std::cout << std::endl;
        total += counter;

    }

    return total;
}
