#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <cstdint>

class Span
{
    public:
        Span(const uint32_t N);
        ~Span();
        Span(const Span& other);
        Span operator=(const Span& other);
        
        void addNumber(const uint32_t number);
        void addMultipleNumbers(const std::vector<uint32_t>& container);

        unsigned int shortestSpan();
        unsigned int longestSpan();
    private:
        Span();

        bool canStoreNumbers(const size_t numbers_size);

        unsigned int maximum_storage_;
        std::vector<uint32_t> span_;
};

#endif