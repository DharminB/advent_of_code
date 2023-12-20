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

void print_series(const std::vector<std::vector<int>>& nums)
{
    /* print series */
    for ( size_t i = 0; i < nums.size(); i++ )
    {
        for ( size_t k = 0; k < i; k++ )
        {
            std::cout << " ";
        }
        for ( size_t j = 0; j < nums[i].size(); j++ )
        {
            std::cout << nums[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

size_t aoc_2023_9(const std::vector<std::string>& input_lines, bool is_part_1)
{
    std::cout << "inside aoc_2023_9" << std::endl;

    long sum = 0;

    for ( const std::string& line : input_lines )
    {
        std::vector<std::string> num_strs = split(line, " ");
        std::vector<std::vector<int>> nums;
        nums.push_back(std::vector<int>(num_strs.size()));
        for ( size_t i = 0; i < nums.front().size(); i++ )
        {
            nums.front()[i] = std::stoi(num_strs[i]);
        }

        for ( size_t k = 0; k < nums.front().size(); k++ )
        {
            nums.push_back(std::vector<int>(nums[k].size()-1));
            for ( size_t i = 0; i+1 < nums[k].size(); i++ )
            {
                nums[k+1][i] = nums[k][i+1] - nums[k][i];
            }

            bool all_zeros = true;
            for ( size_t i = 0; i < nums[k+1].size(); i++ )
            {
                if ( nums[k+1][i] != 0 )
                {
                    all_zeros = false;
                    break;
                }
            }

            if ( all_zeros )
            {
                break;
            }
        }

        print_series(nums);

        if ( is_part_1 )
        {
            int num_size = static_cast<int>(nums.size());
            for ( int i = num_size-1; i >= 0; i-- )
            {
                int num = 0;
                if ( i+1 != num_size )
                {
                    num = nums[i+1].back() + nums[i].back();
                }
                nums[i].push_back(num);
            }
        }
        else
        {
            int num_size = static_cast<int>(nums.size());
            for ( int i = num_size-1; i >= 0; i-- )
            {
                int num = 0;
                if ( i+1 != num_size )
                {
                    num = nums[i].front() - nums[i+1].front();
                }
                nums[i].insert(nums[i].begin(), num);
            }
        }

        print_series(nums);

        if ( is_part_1 )
        {
            sum += nums.front().back();
        }
        else
        {
            sum += nums.front().front();
        }

    }

    return static_cast<size_t>(sum);
}

