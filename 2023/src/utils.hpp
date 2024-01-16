#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

const std::vector<std::string> digit_strings{
"one",
"two",
"three",
"four",
"five",
"six",
"seven",
"eight",
"nine"
};


bool read_file(const std::string& input_file_name, std::vector<std::string>& input_lines)
{
    std::ifstream input_file(input_file_name);
    if ( input_file.is_open() )
    {
        std::string line;
        while ( std::getline(input_file, line) )
        {
            input_lines.push_back(line);
        }
        input_file.close();
        return true;
    }
    else
    {
        std::cout << "ERROR: unable to open file " << input_file_name << std::endl;
        return false;
    }
}

int get_digit(char c)
{
    if ( !isdigit(c) )
    {
        return -1;
    }
    return c - '0';
}

int get_first_digit(const std::string& line)
{
    for ( size_t i = 0; i < line.size(); i++ )
    {
        int num = get_digit(line[i]);
        if ( num >= 0 )
        {
            return num;
        }
    }
    return 0;
}

int get_first_digit_spelled(const std::string& line)
{
    for ( size_t i = 0; i < line.size(); i++ )
    {
        int num = get_digit(line[i]);
        if ( num >= 0 )
        {
            return num;
        }
        for ( size_t j = 0; j < digit_strings.size(); j++ )
        {
            if ( digit_strings[j].size() <= (line.size()-i) &&
                 line.substr(i, digit_strings[j].size()) == digit_strings[j] )
            {
                return j+1;
            }
        }
    }
    return 0;
}

int get_last_digit(const std::string& line)
{
    for ( size_t i = line.size()-1; i >= 0; i-- )
    {
        int num = get_digit(line[i]);
        if ( num >= 0 )
        {
            return num;
        }
    }
    return 0;
}

int get_last_digit_spelled(const std::string& line)
{
    for ( size_t i = line.size()-1; i >= 0; i-- )
    {
        int num = get_digit(line[i]);
        if ( num >= 0 )
        {
            return num;
        }
        for ( size_t j = 0; j < digit_strings.size(); j++ )
        {
            if ( digit_strings[j].size() <= (i+1) &&
                 line.substr(i+1-digit_strings[j].size(), digit_strings[j].size()) == digit_strings[j] )
            {
                return j+1;
            }
        }
    }
    return 0;
}

std::vector<std::string> split(const std::string& s, const std::string& delimeter)
{
    std::vector<std::string> split_strings;
    size_t start = 0;
    while ( start < s.size() )
    {
        size_t found = s.find(delimeter, start);
        if ( found == std::string::npos )
        {
            split_strings.push_back(s.substr(start));
            break;
        }
        else
        {
            split_strings.push_back(s.substr(start, found-start));
            start = found + delimeter.size();
        }
    }
    return split_strings;
}

bool parse_red_green_blue(const std::string& line, int& red, int& green, int& blue)
{
    std::vector<std::string> split_strings = split(line, ", ");

    red = 0;
    green = 0;
    blue = 0;

    for ( const std::string& s : split_strings )
    {
        if ( s.find("red") != std::string::npos )
        {
            red = std::stoi(split(s, " ").front());
        }
        else if ( s.find("green") != std::string::npos )
        {
            green = std::stoi(split(s, " ").front());
        }
        else if ( s.find("blue") != std::string::npos )
        {
            blue = std::stoi(split(s, " ").front());
        }
    }
    return true;
}

template <typename T>
void printVec(const std::vector<T>& vec)
{
    std::cout << "[";
    for ( size_t i = 0; i < vec.size(); i++ )
    {
        if ( i > 0 )
        {
            std::cout << ", ";
        }
        std::cout << vec[i];
    }
    std::cout << "]";
}
