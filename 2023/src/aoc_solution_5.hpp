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

struct Mapping
{
    std::string dest;
    std::vector<size_t> src_range_starts;
    std::vector<size_t> dest_range_starts;
    std::vector<size_t> range_lengths;
};

size_t lookup_mapping(
        const std::unordered_map<std::string, Mapping>& almanac,
        const std::string& src,
        const std::string& dest,
        size_t src_num)
{
    size_t num = src_num;
    std::string key = src;
    while ( key != dest )
    {
        const Mapping& m = almanac.at(key);
        key = m.dest;
        for ( size_t i = 0; i < m.src_range_starts.size(); i++ )
        {
            if ( num < m.src_range_starts[i] + m.range_lengths[i] )
            {
                const size_t diff = num - m.src_range_starts[i];
                num = m.dest_range_starts[i] + diff;
                break;
            }
        }
    }
    return num;
}

size_t lookup_mapping_range(
        const std::unordered_map<std::string, Mapping>& almanac,
        const std::string& src,
        const std::string& dest,
        size_t src_num,
        size_t src_end_num)
{
    // std::cout << "inside lookup_mapping_range" << std::endl;
    const Mapping& m = almanac.at(src);
    size_t min_num = std::numeric_limits<size_t>::max();
    for ( size_t i = 0; i < m.src_range_starts.size(); i++ )
    {
        if ( m.src_range_starts[i] + m.range_lengths[i] < src_num )
        {
            continue;
        }
        if ( m.src_range_starts[i] > src_end_num )
        {
            continue;
        }
        size_t start, end;
        if ( m.src_range_starts[i] <= src_num && src_end_num < m.src_range_starts[i] + m.range_lengths[i] )
        {
            start = src_num;
            end = src_end_num;
        }
        else
        {
            start = std::max(src_num, m.src_range_starts[i]);
            end = std::min(src_end_num, m.src_range_starts[i] + m.range_lengths[i] - 1);
        }
        // std::cout << src << " " << m.dest << " " << src_num << " " << src_end_num << std::endl;
        // std::cout << "range " << m.src_range_starts[i] << " " << m.src_range_starts[i] + m.range_lengths[i] << std::endl;
        // std::cout << "start: " << start << std::endl;
        // std::cout << "end: " << end << std::endl;
        const size_t dest_start = m.dest_range_starts[i] + start - m.src_range_starts[i];
        const size_t dest_end = m.dest_range_starts[i] + end - m.src_range_starts[i];
        // std::cout << "dest_start: " << dest_start << std::endl;
        // std::cout << "dest_end: " << dest_end << std::endl;
        size_t num;
        if ( dest == m.dest )
        {
            num = dest_start;
        }
        else
        {
            num = lookup_mapping_range(almanac, m.dest, dest, dest_start, dest_end);
        }
        // std::cout << "num: " << num << std::endl;
        if ( num < min_num )
        {
            min_num = num;
        }
        // const size_t num = m.dest_range_starts[i] + src_num - m.src_range_starts[i];
        // std::cout << "num: " << num << std::endl;
    }
    return min_num;
}

void parse_file(
        const std::vector<std::string>& input_lines,
        std::unordered_map<std::string, Mapping>& almanac)
{
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
}

void print_almanac(
    const std::unordered_map<std::string, Mapping>& almanac)
{
    /* print almanac */
    for ( auto itr = almanac.cbegin(); itr != almanac.cend(); itr ++ )
    {
        std::cout << itr->first << " -> " << itr->second.dest << std::endl;
        for ( size_t i = 0; i < itr->second.src_range_starts.size(); i++ )
        {
            std::cout << itr->second.src_range_starts[i] << " "
                      << itr->second.dest_range_starts[i] << " "
                      << itr->second.range_lengths[i] << std::endl;
        }
    }
}

void sort_src_range_almanac(
        std::unordered_map<std::string, Mapping>& almanac)
{
    const size_t big = static_cast<size_t>(std::numeric_limits<unsigned int>::max()) + 1;
    // const size_t big = 100;
    /* sort src range */
    for ( auto itr = almanac.begin(); itr != almanac.end(); itr ++ )
    {
        Mapping& m = itr->second;
        Mapping m2;
        m2.dest = m.dest;
        size_t n = 0;
        while ( n < big )
        {
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
}

size_t aoc_2023_5(const std::vector<std::string>& input_lines, bool is_part_1)
{
    std::cout << "inside aoc_2023_5" << std::endl;

    std::unordered_map<std::string, Mapping> almanac;

    parse_file(input_lines, almanac);

    print_almanac(almanac);

    sort_src_range_almanac(almanac);

    print_almanac(almanac);

    std::vector<std::string> seed_strs = split(split(input_lines[0], ": ").back(), " ");
    const std::string target_dest = "location";
    const std::string initial_src = "seed";
    size_t min_location_num = std::numeric_limits<size_t>::max();
    size_t increment = ( is_part_1 ) ? 1 : 2;
    for ( size_t seed_itr = 0; seed_itr < seed_strs.size(); seed_itr += increment )
    {
        std::string seed_str = seed_strs[seed_itr];
        size_t num = std::stoul(seed_str);
        if ( !is_part_1 )
        {
            const std::string seed_str_2 = seed_strs[seed_itr+1];
            const size_t diff = std::stoul(seed_str_2);
            const size_t end_num = num + diff - 1;
            num = lookup_mapping_range(almanac, initial_src, target_dest, num, end_num);
            // num = lookup_mapping_range(almanac, initial_src, "fertilizer", num, end_num);
        }
        else
        {
            num = lookup_mapping(almanac, initial_src, target_dest, num);
        }
        if ( num < min_location_num )
        {
            min_location_num = num;
        }
    }

    return min_location_num;
}

