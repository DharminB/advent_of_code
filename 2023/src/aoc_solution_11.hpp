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

size_t aoc_2023_11(const std::vector<std::string>& input_lines, bool is_part_1)
{
    std::cout << "inside aoc_2023_11" << std::endl;

    const size_t num_rows = input_lines.size();
    const size_t num_cols = input_lines.front().size();

    std::vector<bool> is_empty_row(num_rows, true);
    std::vector<bool> is_empty_col(num_rows, true);
    std::vector<size_t> galaxy_rows, galaxy_cols;

    for ( size_t i = 0; i < num_rows; i++ )
    {
        std::cout << input_lines[i] << std::endl;
        for ( size_t j = 0; j < num_cols; j++ )
        {
            if ( input_lines[i][j] != '.' )
            {
                is_empty_row[i] = false;
                is_empty_col[j] = false;
                galaxy_rows.push_back(i);
                galaxy_cols.push_back(j);
            }
        }
    }

    std::cout << "is_empty_row: ";
    for ( size_t i = 0; i < is_empty_row.size(); i++ )
    {
        std::cout << is_empty_row[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "is_empty_col: ";
    for ( size_t i = 0; i < is_empty_col.size(); i++ )
    {
        std::cout << is_empty_col[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "galaxy pos: " << std::endl;
    for ( size_t i = 0; i < galaxy_rows.size(); i++ )
    {
        std::cout << galaxy_rows[i] << " " << galaxy_cols[i] << std::endl;
    }
    std::cout << std::endl;

    size_t expansion_offset = ( is_part_1 ) ? 1 : 999999;
    size_t total_dist = 0;
    for ( size_t i = 0; i+1 < galaxy_rows.size(); i++ )
    {
        for ( size_t j = i+1; j < galaxy_rows.size(); j++ )
        {
            // std::cout << i << " " << j << std::endl;
            const int start_row = static_cast<int>(galaxy_rows[i]);
            const int start_col = static_cast<int>(galaxy_cols[i]);
            const int end_row = static_cast<int>(galaxy_rows[j]);
            const int end_col = static_cast<int>(galaxy_cols[j]);
            // std::cout << start_row << " " << start_col << " " << end_row << " " << end_col << std::endl;
            total_dist += std::abs(start_row - end_row) + std::abs(start_col - end_col);
            for ( int k = std::min(start_row, end_row)+1; k < std::max(start_row, end_row); k++ )
            {
                if ( is_empty_row[k] )
                {
                    total_dist += expansion_offset;
                }
            }
            for ( int k = std::min(start_col, end_col)+1; k < std::max(start_col, end_col); k++ )
            {
                if ( is_empty_col[k] )
                {
                    total_dist += expansion_offset;
                }
            }
        }
    }

    return total_dist;
}

