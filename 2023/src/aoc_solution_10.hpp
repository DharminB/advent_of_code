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

    if ( is_part_1 )
    {
        return loop_length / 2;
    }

    /* part 2 */

    /* mask closed with input lines */
    std::vector<std::string> clean_loop(input_lines);
    for ( size_t i = 0; i < input_lines.size(); i++ )
    {
        for ( size_t j = 0; j < input_lines[i].size(); j++ )
        {
            if ( !closed[i][j] )
            {
                clean_loop[i][j] = '.';
            }
        }
    }

    /* replace 'S' with pipe symbol */
    // bool found_valid_neighbour = false;
    std::vector<int> neighbour_rows, neighbour_cols;
    for ( size_t i = 0; i < neighbour_row_offset.size(); i++ )
    {
        const char curr = input_lines[start_row][start_col];
        int new_row = start_row + neighbour_row_offset[i];
        int new_col = start_col + neighbour_col_offset[i];
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

        /* found a valid neighbour */
        // std::cout << "neighbour: " << new_row << " " << new_col << " " << neighbour << std::endl;
        neighbour_rows.push_back(new_row);
        neighbour_cols.push_back(new_col);
    }

    std::cout << neighbour_rows.front() << " " << neighbour_cols.front() << std::endl;
    std::cout << neighbour_rows.back() << " " << neighbour_cols.back() << std::endl;

    if ( neighbour_rows.front() == start_row - 1 &&
         neighbour_rows.back() == start_row + 1 &&
         neighbour_cols.front() == start_col &&
         neighbour_cols.back() == start_col ) // |
    {
        clean_loop[start_row][start_col] = '|';
    }
    else if ( neighbour_rows.front() == start_row &&
              neighbour_rows.back() == start_row &&
              neighbour_cols.front() == start_col - 1 &&
              neighbour_cols.back() == start_col + 1 ) // -
    {
        clean_loop[start_row][start_col] = '-';
    }
    else if ( neighbour_rows.front() == start_row - 1 &&
              neighbour_rows.back() == start_row &&
              neighbour_cols.front() == start_col &&
              neighbour_cols.back() == start_col + 1 ) // L
    {
        clean_loop[start_row][start_col] = 'L';
    }
    else if ( neighbour_rows.front() == start_row &&
              neighbour_rows.back() == start_row + 1 &&
              neighbour_cols.front() == start_col - 1 &&
              neighbour_cols.back() == start_col ) // 7
    {
        clean_loop[start_row][start_col] = '7';
    }
    else if ( neighbour_rows.front() == start_row - 1 &&
              neighbour_rows.back() == start_row &&
              neighbour_cols.front() == start_col &&
              neighbour_cols.back() == start_col - 1 ) // J
    {
        clean_loop[start_row][start_col] = 'J';
    }
    else if ( neighbour_rows.front() == start_row &&
              neighbour_rows.back() == start_row + 1 &&
              neighbour_cols.front() == start_col + 1 &&
              neighbour_cols.back() == start_col ) // F
    {
        clean_loop[start_row][start_col] = 'F';
    }

    /* print clean loop */
    // for ( size_t i = 0; i < clean_loop.size(); i++ )
    // {
    //     std::cout << clean_loop[i] << std::endl;
    // }


    size_t loop_area = 0;
    for ( size_t i = 0; i < clean_loop.size(); i++ )
    {
        for ( size_t j = 0; j < clean_loop[i].size(); j++ )
        {
            if ( clean_loop[i][j] != '.' )
            {
                continue;
            }

            // std::cout << i << " " << j << " " << clean_loop[i][j] << " -> ";
            /* ray casting to the right/east */
            char prev_corner = '.';
            size_t counter = 0;
            for ( size_t k = j+1; k < clean_loop[i].size(); k++ )
            {
                // std::cout << clean_loop[i][k] << " ";
                if ( clean_loop[i][k] == '|' )
                {
                    counter ++;
                }
                else if ( clean_loop[i][k] == '-' ||
                          clean_loop[i][k] == '.' )
                {
                    // no increase in counter
                }
                else // corner char (L, F, 7, J)
                {
                    if ( prev_corner == '.' ) // no prev corner
                    {
                        prev_corner = clean_loop[i][k];
                    }
                    else
                    {
                        const char curr_corner = clean_loop[i][k];
                        if ( prev_corner == 'L' && curr_corner == '7' )
                        {
                            counter += 1;
                        }
                        else if ( prev_corner == 'L' && curr_corner == 'J' )
                        {
                            counter += 2;
                        }
                        else if ( prev_corner == 'F' && curr_corner == 'J' )
                        {
                            counter += 1;
                        }
                        else if ( prev_corner == 'F' && curr_corner == '7' )
                        {
                            counter += 2;
                        }
                        prev_corner = '.'; // reset prev_corner
                    }
                }
            }
            // std::cout << counter << std::endl;
            if ( counter % 2 == 0 )
            {
                clean_loop[i][j] = 'O';
            }
            else
            {
                clean_loop[i][j] = 'I';
                loop_area ++;
            }
        }
    }

    /* print clean loop */
    for ( size_t i = 0; i < clean_loop.size(); i++ )
    {
        std::cout << clean_loop[i] << std::endl;
    }

    return loop_area;
}

