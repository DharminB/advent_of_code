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

size_t aoc_2023_3(const std::vector<std::string>& input_lines, bool is_part_1)
{
    // std::cout << "inside aoc_2023_3" << std::endl;
    size_t sum = 0;

    int rows = input_lines.size();
    int cols = input_lines.front().size();
    for ( int i = 0; i < rows; i++ )
    {
        std::cout << input_lines[i] << std::endl;
    }

    // map(star index: pair<num of parts around it, product of part numbers>)
    std::unordered_map<size_t, std::pair<int, long>> stars;
    for ( int i = 0; i < rows; i++ )
    {
        std::string num_str;
        int start = 0, end = 0;
        for ( int j = 0; j < cols; j++ )
        {
            bool is_digit = ( get_digit(input_lines[i][j]) >= 0 );
            if ( is_digit ) // accumulate
            {
                if ( num_str.empty() )
                {
                    start = j;
                }
                end = j;
                num_str += input_lines[i][j];
            }

            if ( !is_digit || j+1 == cols )
            {
                // TODO: when num is at the end
                if ( !num_str.empty() )
                {
                    int num = std::stoi(num_str);
                    // std::cout << num << " " << start << " " << end << std::endl;
                    num_str = "";
                    // check surrounding characters
                    bool is_part_number = false;
                    for ( int m = std::max(0, i-1); m < std::min(rows, i+2); m++ )
                    {
                        for ( int n = std::max(0, start-1);
                              n < std::min(cols, end+2);
                              n++ )
                        {
                            if ( m != i || n < start || n > end )
                            {
                                if ( input_lines[m][n] != '.' && !isdigit(input_lines[m][n]) ) // not . and not a digit
                                {
                                    is_part_number = true;
                                    if ( input_lines[m][n] == '*' )
                                    {
                                        const size_t star_index = (m*cols) + n;
                                        if ( stars.find(star_index) == stars.end() )
                                        {
                                            stars[star_index] = std::make_pair<int, long>(0, 1);
                                        }
                                        stars[star_index].first += 1;
                                        stars[star_index].second *= num;
                                    }
                                }
                                // std::cout << input_lines[m][n] << " ";
                            }
                        }
                    }
                    if ( is_part_number )
                    {
                        sum += num;
                    }
                    // std::cout << std::endl;
                }
            }
        }
    }

    if ( !is_part_1 )
    {
        sum = 0;
        for ( auto itr = stars.begin(); itr != stars.end(); itr ++ )
        {
            // std::cout << itr->first << " " << itr->second.first << " " << itr->second.second << std::endl;
            if ( itr->second.first == 2 )
            {
                sum += itr->second.second;
            }
        }
    }

    return sum;
}
