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

size_t aoc_2023_12(const std::vector<std::string>& input_lines, bool is_part_1)
{
    std::cout << "inside aoc_2023_12" << std::endl;

    std::vector<std::string> spring_strs;
    std::vector<std::vector<int>> contiguous_springs;

    for ( size_t i = 0; i < input_lines.size(); i++ )
    {
        std::cout << input_lines[i] << std::endl;
        std::vector<std::string> strs = split(input_lines[i], " ");
        spring_strs.push_back(strs.front());
        std::vector<std::string> nums = split(strs.back(), ",");
        std::vector<int> contiguous_spring(nums.size());
        for ( size_t j = 0; j < nums.size(); j++ )
        {
            contiguous_spring[j] = std::stoi(nums[j]);
        }
        contiguous_springs.push_back(contiguous_spring);
    }

    for ( size_t k = 0; k < spring_strs.size(); k++ )
    {
        const std::string& spring_str = spring_strs[k];
        const std::vector<int>& contiguous_spring = contiguous_springs[k];
        /* count num of ? and # */
        size_t question_count = 0, hash_count = 0;
        for ( size_t i = 0; i < spring_str.size(); i++ )
        {
            if ( spring_str[i] == '?' )
            {
                question_count ++;
            }
            else if ( spring_str[i] == '#' )
            {
                hash_count ++;
            }
        }
        std::cout << "question_count: " << question_count << std::endl;
        std::cout << "hash_count: " << hash_count << std::endl;

        size_t required_hash_count = 0;
        for ( size_t i = 0; i < contiguous_spring.size(); i++ )
        {
            required_hash_count += contiguous_spring[i];
        }
        std::cout << "required_hash_count: " << required_hash_count << std::endl;

        const size_t needed_hash = required_hash_count - hash_count;

        std::vector<size_t> hash_index(needed_hash, 0);
        for ( size_t i = 1; i < needed_hash; i++ )
        {
            hash_index[i] = hash_index[i-1] + 1;
        }
        while ( hash_index.front() <= question_count - needed_hash )
        {

        }

        std::cout << "hash_index: ";
        printVec<size_t>(hash_index);
        std::cout << std::endl;

        break;
    }

    return 0;
}

