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

size_t aoc_2023_10(const std::vector<std::string>& input_lines, bool is_part_1)
{
    std::cout << "inside aoc_2023_10" << std::endl;

    const int num_rows = static_cast<int>(input_lines.size());
    const int num_cols = static_cast<int>(input_lines.front().size());

    /* find 'S' */
    int start_row, start_col;
    for ( int i = 0; i < num_rows; i++ )
    {
        const size_t j = input_lines[i].find('S');
        if ( j != std::string::npos )
        {
            start_row = i;
            start_col = static_cast<int>(j);
            break;
        }
    }
    std::cout << "start_row: " << start_row << std::endl;
    std::cout << "start_col: " << start_col << std::endl;


    /* depth first search */
    /* initialise closed */
    std::vector<std::vector<bool>> closed(num_rows, std::vector<bool>(num_cols, false));
    closed[start_row][start_col] = true;

    std::vector<int> neighbour_row_offset{-1,  0, 0, 1};
    std::vector<int> neighbour_col_offset{ 0, -1, 1, 0};
    std::vector<std::string> valid_neighbour_symbol{"|7F", "-LF", "-J7", "|LJ"};
    std::vector<std::string> valid_current_symbol{"S|LJ", "S-J7", "S-LF", "S|7F"};

    int row = start_row;
    int col = start_col;
    const size_t itr_limit = num_rows * num_cols;
    // const size_t itr_limit = 20;
    size_t loop_length = 0;
    for ( size_t itr = 0; itr < itr_limit; itr++ )
    {
        // std::cout << std::endl << row << " " << col << std::endl;
        const char curr = input_lines[row][col];
        closed[row][col] = true;

        /* check valid neighbours */
        bool found_valid_neighbour = false;
        for ( size_t i = 0; i < neighbour_row_offset.size(); i++ )
        {
            int new_row = row + neighbour_row_offset[i];
            int new_col = col + neighbour_col_offset[i];
            if ( new_row < 0 || new_row >= num_rows ||
                 new_col < 0 || new_col >= num_cols ) // boundaries
            {
                continue;
            }
            size_t current_itr = valid_current_symbol[i].find(curr);
            if ( current_itr == std::string::npos ) // cannot travel in that direction
            {
                continue;
            }

            const char neighbour = input_lines[new_row][new_col];
            size_t neighbour_itr = valid_neighbour_symbol[i].find(neighbour);
            if ( neighbour_itr == std::string::npos ) // cannot travel in that direction
            {
                continue;
            }

            if ( closed[new_row][new_col] )
            {
                continue;
            }

            /* found a valid neighbour */
            // std::cout << "neighbour: " << new_row << " " << new_col << " " << neighbour << std::endl;
            row = new_row;
            col = new_col;
            found_valid_neighbour = true;
            break;
        }

        if ( !found_valid_neighbour )
        {
            std::cout << "itr: " << itr << std::endl;
            loop_length = itr + 1;
            break;
        }

    }


    return loop_length / 2;
}

