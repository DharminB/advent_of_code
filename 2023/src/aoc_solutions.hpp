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

size_t aoc_2023_1(const std::vector<std::string>& input_lines, bool is_part_1)
{
    // std::cout << "inside aoc_2023_1" << std::endl;
    size_t sum = 0;
    for ( size_t i = 0; i < input_lines.size(); i++ )
    {
        // std::cout << i << " " << input_lines[i] << std::endl;

        int first_digit = 0;
        int last_digit = 0;

        if ( is_part_1 )
        {
            first_digit = get_first_digit(input_lines[i]);
            last_digit = get_last_digit(input_lines[i]);
        }
        else
        {
            first_digit = get_first_digit_spelled(input_lines[i]);
            last_digit = get_last_digit_spelled(input_lines[i]);
        }

        // std::cout << "first_digit: " << first_digit << std::endl;
        // std::cout << "last_digit: " << last_digit << std::endl;
        sum += (first_digit * 10) + last_digit;
    }
    return sum;
}

size_t aoc_2023_2(const std::vector<std::string>& input_lines, bool is_part_1)
{
    // std::cout << "inside aoc_2023_2" << std::endl;
    size_t sum = 0;
    // std::cout << "problem " << input_lines[0] << std::endl;

    int max_red = 0;
    int max_green = 0;
    int max_blue = 0;
    if ( is_part_1 )
    {
        parse_red_green_blue(input_lines[0], max_red, max_green, max_blue);
    }
    // std::cout << "max_red: " << max_red << std::endl;
    // std::cout << "max_green: " << max_green << std::endl;
    // std::cout << "max_blue: " << max_blue << std::endl;

    int red, green, blue = 0;
    for ( size_t i = 1; i < input_lines.size(); i++ )
    {
        // std::cout << i << " " << input_lines[i] << std::endl;
        int min_red = 0, min_green = 0, min_blue = 0;
        std::vector<std::string> split_strings = split(input_lines[i], ": ");
        std::vector<std::string> split_games = split(split_strings.back(), "; ");
        bool is_possible = true;
        for ( const std::string& s : split_games )
        {
            parse_red_green_blue(s, red, green, blue);
            if ( is_part_1 )
            {
                if ( red > max_red || green > max_green || blue > max_blue )
                {
                    is_possible = false;
                    break;
                }
            }
            else
            {
                min_red = std::max(red, min_red);
                min_green = std::max(green, min_green);
                min_blue = std::max(blue, min_blue);
            }
        }
        if ( is_part_1 )
        {
            if ( is_possible )
            {
                int game_num = std::stoi(split(split_strings.front(), " ").back());
                sum += game_num;
            }
        }
        else
        {
            sum += (min_red * min_green * min_blue);
        }
    }
    return sum;
}

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

size_t aoc_2023_5(const std::vector<std::string>& input_lines, bool is_part_1)
{
    std::cout << "inside aoc_2023_5" << std::endl;
    size_t big = 100;

    struct Mapping
    {
        std::string dest;
        std::vector<size_t> src_range_starts;
        std::vector<size_t> dest_range_starts;
        std::vector<size_t> range_lengths;
    };
    std::unordered_map<std::string, Mapping> almanac;

    /* parse file */
    std::string curr_src;
    for ( size_t i = 1; i < input_lines.size(); i++ )
    {
        std::cout << input_lines[i] << std::endl;
        if ( input_lines[i].empty() )
        {
            continue;
        }
        else if ( input_lines[i].find("map:") != std::string::npos )
        {
            std::string src_dest_str = split(input_lines[i], " ").front();
            std::vector<std::string> src_dest_vec = split(src_dest_str, "-");
            std::string src = src_dest_vec.front();
            std::string dest = src_dest_vec.back();
            curr_src = src;
            almanac[curr_src] = Mapping();
            almanac[curr_src].dest = dest;
        }
        else
        {
            std::vector<std::string> num_strs = split(input_lines[i], " ");
            almanac[curr_src].dest_range_starts.push_back(std::stoul(num_strs[0]));
            almanac[curr_src].src_range_starts.push_back(std::stoul(num_strs[1]));
            almanac[curr_src].range_lengths.push_back(std::stoul(num_strs[2]));
        }
    }

    /* print almanac */
    for ( auto itr = almanac.begin(); itr != almanac.end(); itr ++ )
    {
        std::cout << itr->first << " -> " << itr->second.dest << std::endl;
        for ( size_t i = 0; i < itr->second.src_range_starts.size(); i++ )
        {
            std::cout << itr->second.src_range_starts[i] << " "
                      << itr->second.dest_range_starts[i] << " "
                      << itr->second.range_lengths[i] << std::endl;
        }
    }

    /* sort src range */
    for ( auto itr = almanac.begin(); itr != almanac.end(); itr ++ )
    {
        Mapping& m = itr->second;
        Mapping m2;
        m2.dest = m.dest;
        size_t n = 0;
        size_t itr_num = 0, itr_limit = 10;
        while ( n < big )
        {
            itr_num ++;
            if ( itr_num > itr_limit )
            {
                break;
            }
            size_t min_src_start = big;
            size_t min_index = 0;
            bool found = false;
            for ( size_t i = 0; i < m.src_range_starts.size(); i++ )
            {
                if ( m.src_range_starts[i] >= n && m.src_range_starts[i] < min_src_start )
                {
                    min_src_start = m.src_range_starts[i];
                    min_index = i;
                    found = true;
                }
            }
            if ( found && min_src_start == n )
            {
                m2.src_range_starts.push_back(m.src_range_starts[min_index]);
                m2.dest_range_starts.push_back(m.dest_range_starts[min_index]);
                m2.range_lengths.push_back(m.range_lengths[min_index]);
                n += m.range_lengths[min_index];
            }
            else
            {
                m2.src_range_starts.push_back(n);
                m2.dest_range_starts.push_back(n);
                m2.range_lengths.push_back(min_src_start - n);
                n = min_src_start;
            }
        }
        m.src_range_starts = m2.src_range_starts;
        m.dest_range_starts = m2.dest_range_starts;
        m.range_lengths = m2.range_lengths;
    }

    /* print almanac */
    for ( auto itr = almanac.begin(); itr != almanac.end(); itr ++ )
    {
        std::cout << itr->first << " -> " << itr->second.dest << std::endl;
        for ( size_t i = 0; i < itr->second.src_range_starts.size(); i++ )
        {
            std::cout << itr->second.src_range_starts[i] << " "
                      << itr->second.dest_range_starts[i] << " "
                      << itr->second.range_lengths[i] << std::endl;
        }
    }

    std::vector<std::string> seed_strs = split(split(input_lines[0], ": ").back(), " ");
    const std::string target_dest = "location";
    const std::string initial_src = "seed";
    size_t min_location_num = std::numeric_limits<size_t>::max();
    for ( const std::string& seed_str : seed_strs )
    {
        size_t num = std::stoul(seed_str);
        // std::cout << "num: " << num << std::endl;
        std::string key = initial_src;
        while ( key != target_dest )
        {
            const Mapping& m = almanac[key];
            key = m.dest;
            // std::cout << "key: " << key << std::endl;
            for ( size_t i = 0; i < m.src_range_starts.size(); i++ )
            {
                if ( num < m.src_range_starts[i] + m.range_lengths[i] )
                {
                    const size_t diff = num - m.src_range_starts[i];
                    num = m.dest_range_starts[i] + diff;
                    break;
                }
            }
            // std::cout << "num: " << num << std::endl;
        }
        if ( num < min_location_num )
        {
            min_location_num = num;
        }
    }

    return min_location_num;
}
