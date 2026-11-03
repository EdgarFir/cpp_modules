#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <vector>

template <typename T>
typename T::const_iterator easyfind(const T& container, int target)
{
    return std::find(container.begin(), container.end(), target);
}

#endif