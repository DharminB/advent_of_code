#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <chrono>

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
#include <aoc_solution_11.hpp>
#include <aoc_solution_12.hpp>
#include <aoc_solution_13.hpp>
#include <aoc_solution_14.hpp>

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

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    // size_t answer = aoc_2023_1(input_lines, true);
    // size_t answer = aoc_2023_2(input_lines, true);
    // size_t answer = aoc_2023_3(input_lines, true);
    // size_t answer = aoc_2023_4(input_lines, true);
    // size_t answer = aoc_2023_5(input_lines, true);
    // size_t answer = aoc_2023_6(input_lines, true);
    // size_t answer = aoc_2023_7(input_lines, false);
    // size_t answer = aoc_2023_8(input_lines, false);
    // size_t answer = aoc_2023_9(input_lines, false);
    // size_t answer = aoc_2023_10(input_lines, false);
    // size_t answer = aoc_2023_11(input_lines, false);
    // size_t answer = aoc_2023_12(input_lines, false);
    // size_t answer = aoc_2023_13(input_lines, false);
    size_t answer = aoc_2023_14(input_lines, true);
    std::cout << "answer: " << answer << std::endl;

    std::chrono::duration<float> time_taken = std::chrono::steady_clock::now() - start;
    std::cout << "time taken: " << time_taken.count()*1000.0f << " ms" << std::endl;

    return 0;
}
