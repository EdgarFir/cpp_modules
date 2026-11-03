#include "Span.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

void fill_container_with_random_numbers(std::vector<uint32_t>& container, const unsigned int numbers_size)
{
    // Poppulate container with random numbers
    for (int i = 0; i < numbers_size; i++)
    {
        container.push_back(rand());
    }
}

void try_to_add_multiple_numbers(Span& span, const unsigned int numbers_size)
{
    // Poppulate container with random numbers
    std::vector<uint32_t> container;
    fill_container_with_random_numbers(container, numbers_size);
    
    // try to add
    try
    {
        span.addMultipleNumbers(container);
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void try_to_add_single_number(Span& span, const uint32_t val)
{
    // try to add
    try
    {
        span.addNumber(val);
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void try_to_get_longest_span(Span& span)
{
    try
    {
        uint32_t longest_span = span.longestSpan();
        std::cout << "Longest span: '" << longest_span << "'\n";
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void try_to_get_shortest_span(Span& span)
{
    try
    {
        uint32_t shortest_span = span.shortestSpan();
        std::cout << "Shortest span: '" << shortest_span << "'\n";
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

int main()
{
    // See random numbers
    srand(time(NULL));

    // 42 test
    {
        Span sp = Span(5);

        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        std::cout << sp.shortestSpan() << std::endl;
        std::cout << sp.longestSpan() << std::endl;
    }
    std::cout << "==================================================\n";
    // Test Empty Span    
    {
        Span span(0);

        try_to_add_multiple_numbers(span, 100);
        try_to_add_single_number(span, 3);
        try_to_get_longest_span(span);
        try_to_get_shortest_span(span);
    }
    std::cout << "==================================================\n";
    // Test Single number Span    
    {
        Span span(1);

        try_to_add_multiple_numbers(span, 100);
        try_to_add_single_number(span, 3);
        try_to_add_single_number(span, 10);
        try_to_get_longest_span(span);
        try_to_get_shortest_span(span);
    }
    std::cout << "==================================================\n";
    // Test minimum size allowed longest/shortest operations Span    
    {
        Span span(2);

        try_to_add_single_number(span, 0);
        try_to_add_single_number(span, std::numeric_limits<uint32_t>::max());
        try_to_get_longest_span(span);
        try_to_get_shortest_span(span);
    }
    std::cout << "==================================================\n";
    {

        Span span(100);
        
        // Not enough space
        {
            std::vector<uint32_t> container;
            try_to_add_multiple_numbers(span, 101);
        }
        {
            // Enough space, but full
            try_to_add_multiple_numbers(span, 100);
            // Trying to add +1
            try_to_add_single_number(span, 44);

            try_to_get_longest_span(span);
            try_to_get_shortest_span(span);
        }
    }
    std::cout << "==================================================\n";
    {
        // Testing limits
        const uint32_t big_size = 10000; 
        Span span(big_size);
        
        std::vector<uint32_t> container;
        try_to_add_multiple_numbers(span, big_size);
    
        // Trying to add +1
        try_to_add_single_number(span, 44);

        try_to_get_longest_span(span);
        try_to_get_shortest_span(span);
    }
}