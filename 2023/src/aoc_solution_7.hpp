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

const std::unordered_map<char, size_t> card_value{
{'A', 12},
{'K', 11},
{'Q', 10},
{'T', 9},
{'9', 8},
{'8', 7},
{'7', 6},
{'6', 5},
{'5', 4},
{'4', 3},
{'3', 2},
{'2', 1},
{'J', 0}
};

size_t calc_hand_value(const std::string& hand)
{
    size_t sum = 0;
    std::vector<size_t> counter(card_value.size(), 0);
    for ( size_t i = 0; i < hand.size(); i++ )
    {
        sum += card_value.at(hand[i]) * std::pow(13, hand.size()-i-1);
        counter[card_value.at(hand[i])] ++;
    }

    /* assign value to type */
    sum += 0;
    std::vector<size_t> meta_counter(5, 0);
    for ( size_t i = 0; i < counter.size(); i++ )
    {
        if ( counter[i] > 0 )
        {
            meta_counter[counter[i]-1] ++;
        }
    }
    for ( size_t i = 0; i < meta_counter.size(); i++ )
    {
        std::cout << meta_counter[i] << " ";
    }
    std::cout << std::endl;
    const size_t num_of_jokers = counter.front();
    size_t type_value = 0;
    if ( meta_counter[4] > 0 ) // five of a kind
    {
        type_value = 6;
    }
    else if ( meta_counter[3] > 0 ) // four of a kind
    {
        type_value = ( num_of_jokers == 1 || num_of_jokers == 4 ) ? 6 : 5;
    }
    else if ( meta_counter[2] > 0 && meta_counter[1] > 0 ) // full house
    {
        type_value = ( num_of_jokers == 2 || num_of_jokers == 3 ) ? 6 : 4;
    }
    else if ( meta_counter[2] > 0 && meta_counter[1] == 0 ) // three of a kind
    {
        type_value = ( num_of_jokers == 1 || num_of_jokers == 3 ) ? 5 : 3;
    }
    else if ( meta_counter[1] == 2 ) // two pairs
    {
        if ( num_of_jokers == 1 )
        {
            type_value = 4;
        }
        else if ( num_of_jokers == 2 )
        {
            type_value = 5;
        }
        else
        {
            type_value = 2;
        }
    }
    else if ( meta_counter[1] == 1 ) // one pair
    {
        type_value = ( num_of_jokers == 1 || num_of_jokers == 2 ) ? 3 : 1;
    }
    else // high card
    {
        type_value = ( num_of_jokers == 1 ) ? 1 : 0;
    }
    sum += type_value * std::pow(13, hand.size());

    return sum;
}

struct Comp
{
    bool operator() (const std::string& lhs, const std::string& rhs) const
    {
        return calc_hand_value(lhs) < calc_hand_value(rhs);
    }
};

size_t aoc_2023_7(const std::vector<std::string>& input_lines, bool is_part_1)
{
    std::cout << "inside aoc_2023_7" << std::endl;

    std::map<std::string, size_t, Comp> hand_map;

    for ( size_t i = 0; i < input_lines.size(); i++ )
    {
        std::vector<std::string> strs = split(input_lines[i], " ");
        const std::string hand = strs.front();
        const size_t bid = std::stoul(strs.back());
        // std::cout << "hand: " << hand << std::endl;
        // std::cout << "bid: " << bid << std::endl;
        hand_map[hand] = bid;
        // const size_t value = calc_hand_value(hand);
        // std::cout << "value: " << value << std::endl;
    }

    size_t sum = 0;
    size_t hand_rank = 1;
    for ( auto itr = hand_map.cbegin(); itr != hand_map.cend(); itr ++ )
    {
        std::cout << itr->first << " " << itr->second << std::endl;
        sum += hand_rank * itr->second;
        hand_rank ++;
    }
    std::cout << "sum: " << sum << std::endl;

    return sum;
}

