#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

#include <aoc_solutions.hpp>
#include <utils.hpp>

int main(int argc, char *argv[])
{
    if ( argc < 2 )
    {
        std::cout << "ERROR: no input file provided." << std::endl;
        return -1;
    }

    const std::string input_file_name(argv[1]);
    std::cout << "input_file_name: " << input_file_name << std::endl;

    std::vector<std::string> input_lines;
    if ( !read_file(input_file_name, input_lines) )
    {
        return -1;
    }

    // size_t answer = aoc_2023_1(input_lines, true);
    // size_t answer = aoc_2023_2(input_lines, true);
    // size_t answer = aoc_2023_3(input_lines, true);
    // size_t answer = aoc_2023_4(input_lines, true);
    size_t answer = aoc_2023_5(input_lines, true);
    std::cout << "answer: " << answer << std::endl;

    return 0;
}
