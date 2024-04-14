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

void tilt(std::vector<std::string>& platform, size_t dir)
{
    const int num_rows = static_cast<int>(platform.size());
    const int num_cols = static_cast<int>(platform.front().size());

    if ( num_rows != num_cols )
    {
        std::cerr << "ERROR: cannot handle rectangular platform" << std::endl;
        return;
    }

    int nxt;
    int start;
    int end;
    bool row_major;

    switch ( dir )
    {
        case 0: // north
            nxt = 1;
            start = 0;
            end = num_rows;
            row_major = false;
            break;
        case 1: // west
            nxt = 1;
            start = 0;
            end = num_cols;
            row_major = true;
            break;
        case 2: // south
            nxt = -1;
            start = num_rows-1;
            end = -1;
            row_major = false;
            break;
        case 3: // east
            nxt = -1;
            start = num_cols-1;
            end = -1;
            row_major = true;
            break;
        default:
            return;
    }

    for ( int k = start; k != end; k += nxt )
    {
        int j = start;
        for ( int i = start; i != end; i += nxt )
        {
            // std::cout << i << " " << j << " " << k << std::endl;
            const char c = ( row_major ) ? platform[k][i] : platform[i][k];
            // std::cout << "c: " << c << std::endl;

            if ( c == 'O' )
            {
                j += nxt;
            }
            else if ( c == '#' )
            {
                j += nxt;
            }
            else // c == '.'
            {
                for ( ; j != end; j += nxt )
                {
                    const char cj = ( row_major ) ? platform[k][j] : platform[j][k];
                    // std::cout << j << " " << cj << std::endl;
                    if ( cj == 'O' )
                    {
                        if ( row_major )
                        {
                            platform[k][i] = 'O';
                            platform[k][j] = '.';
                        }
                        else
                        {
                            platform[i][k] = 'O';
                            platform[j][k] = '.';
                        }
                        j += nxt;
                        break;
                    }
                    else if ( cj == '#' )
                    {
                        i = j;
                        j += nxt;
                        break;
                    }
                }
                if ( j == end )
                {
                    break;
                }
            }
            // std::cout << platform[k] << std::endl;
        }
    }
}

size_t aoc_2023_14(const std::vector<std::string>& input_lines, bool is_part_1)
{
    std::cout << "inside aoc_2023_14" << std::endl;

    print_string_vec(input_lines);

    size_t total = 0;

    const size_t num_rows = input_lines.size();
    const size_t num_cols = input_lines.front().size();

    std::vector<std::string> platform = input_lines;

    size_t num_of_spin = 1e7;

    std::vector<std::string> prev_platform = platform;

    for ( size_t i = 0; i < num_of_spin; i++ )
    {
        tilt(platform, 0);
        tilt(platform, 1);
        tilt(platform, 2);
        tilt(platform, 3);

        bool match = true;
        for ( size_t j = 0; j < platform.size(); j++ )
        {
            if ( platform[j] != prev_platform[j] )
            {
                match = false;
                break;
            }
        }
        if ( match )
        {
            std::cout << "matched at " << i << std::endl;
            break;
        }
        else
        {
            prev_platform = platform;
        }
    }
    print_string_vec(platform);

    /* count weight on north support beams */
    for ( size_t i = 0; i < num_rows; i++ )
    {
        for ( size_t j = 0; j < num_cols; j++ )
        {
            if ( platform[i][j] == 'O' )
            {
                total += (num_rows - i);
            }
        }
    }

    return total;
}
