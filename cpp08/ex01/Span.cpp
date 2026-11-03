#include <algorithm>
#include <iostream>
#include <sstream>
#include <limits>
#include "Span.hpp"

Span::Span(const uint32_t N) : maximum_storage_(N), span_()
{
    std::cout << "Instantiating parameterized Span with capacity for '" 
              << N << "' members.\n";
}

Span::~Span()
{
    std::cout << "Destroying Span.\n";
}

Span::Span(const Span& other) : maximum_storage_(other.maximum_storage_), span_(other.span_)
{
    std::cout << "Span copy constructor called.\n";
}

Span Span::operator=(const Span& other)
{
    std::cout << "Span assignment constructor called.\n";

    if (this != &other)
    {
        this->maximum_storage_ = other.maximum_storage_;
        this->span_ = other.span_;
    }
    return *this;
}

void Span::addNumber(const uint32_t number)
{
    const uint32_t numbers_to_add_size = 1;
    if (!canStoreNumbers(numbers_to_add_size))
    {
        throw std::runtime_error("Error: Span is full.");
    }
    span_.push_back(number);
}

void Span::addMultipleNumbers(const std::vector<uint32_t>& container)
{
    if (!canStoreNumbers(container.size()))
    {
        std::stringstream stream;
        stream << "Error: Span has not enough capacity for saving '";
        stream << container.size();
        stream << "' numbers.";
    
        throw std::runtime_error(stream.str());
    }
    span_.insert(span_.end(), container.begin(), container.end());
}

unsigned int Span::shortestSpan()
{
    if (span_.size() < 2)
    {
        throw std::runtime_error(
            "Error: Not enough numbers to find the shortest span.");
    }

    std::sort(span_.begin(), span_.end());
    uint32_t result = std::numeric_limits<unsigned int>::max();
    for (size_t i = 0; i < span_.size() - 1; ++i)
    {
        const uint32_t curr_span_val = span_[i];
        const uint32_t next_span_val = span_[i + 1];
        const uint32_t span_diff = next_span_val - curr_span_val;
        if (span_diff < result)
        {
            result = span_diff;
        }
    }

    return result;
}

unsigned int Span::longestSpan()
{
    if (span_.size() < 2)
    {
        throw std::runtime_error(
            "Error: Not enough numbers to find longest span.");
    }

    std::sort(span_.begin(), span_.end());
    const uint32_t min_val = *span_.begin();
    const uint32_t max_val = *(span_.end() - 1);
    const uint32_t result = max_val - min_val;

    return result;
}

Span::Span() : maximum_storage_(0), span_()
{
    std::cout << "Default Span constructor called.\n";
}

bool Span::canStoreNumbers(const size_t numbers_size)
{
    const uint32_t free_space = maximum_storage_ - span_.size();
    if (numbers_size > free_space)
    {
        return false;
    }

    return true;
}
