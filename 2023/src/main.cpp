#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

#include <utils.hpp>
#include <aoc_solution_1.hpp>
#include <aoc_solution_2.hpp>
#include <aoc_solution_3.hpp>
#include <aoc_solution_4.hpp>
#include <aoc_solution_5.hpp>
#include <aoc_solution_6.hpp>
#include <aoc_solution_7.hpp>
#include <aoc_solution_8.hpp>
#include <aoc_solution_9.hpp>
#include <aoc_solution_10.hpp>

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
    // size_t answer = aoc_2023_5(input_lines, true);
    // size_t answer = aoc_2023_6(input_lines, true);
    // size_t answer = aoc_2023_7(input_lines, false);
    // size_t answer = aoc_2023_8(input_lines, false);
    // size_t answer = aoc_2023_9(input_lines, false);
    size_t answer = aoc_2023_10(input_lines, true);
    std::cout << "answer: " << answer << std::endl;

    return 0;
}
