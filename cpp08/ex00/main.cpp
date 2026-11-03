#include "easyfind.hpp"

#include <vector>
#include <map>
#include <list>
#include <iostream>

template <typename Container>
void test_container(const Container& container, const int target)
{
    std::cout << "Testing target '" << target << "'\n";
    
    if (::easyfind(container, target) == container.end())
    {
        std::cout << "Target not found\n";
    }
    else
    {
        std::cout << "Target found\n";
    }
}

template <typename Container>
void poppulate_container(const int* arr, const size_t arr_size, Container& container)
{
    for (size_t i = 0; i < arr_size; ++i)
    {
        container.push_back(arr[i]);
    }
}

template <typename Container>
void print_container(const Container& container)
{
    typename Container::const_iterator list_beg_it = container.begin();
    while (list_beg_it != container.end())
    {
        std::cout << *list_beg_it;
        if (list_beg_it != container.end()) std::cout << ", ";

        list_beg_it++;
    }
    std::cout << "\n";
}


int main()
{
    const int arr[] = {1, 2, 3, 4, 5};
    const size_t arr_size = 5;
    {
        std::vector<int> container;

        poppulate_container(arr, arr_size, container);
        print_container(container);
        test_container(container, 4);
        test_container(container, -1);
    }
    
    {
        std::list<int> container;
        poppulate_container(arr, arr_size, container);
        print_container(container);
        test_container(container, 4);
        test_container(container, -1);
    }
}
