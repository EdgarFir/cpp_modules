#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

template <typename Array, typename Function>
void iter(Array* arr, const size_t arr_size, Function func)
{
    for (size_t i = 0; i < arr_size; ++i)
    {
        func(arr[i]);
    }
}

#endif