#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>

template <typename T>
class Array
{
    public:
        Array() : size_(0), array_(NULL)
        {
            std::cout << "Calling default Array constructor\n";
        }
        Array(const size_t n) : size_(n), array_(NULL)
        {
            std::cout << "Calling parameterized Array constructor\n";

            if (size_)
            {
                array_ = new T[size_];  
            }
        }

        Array(const Array<T>& other) : size_(other.size_), array_(NULL)
        {
            // Deep copy array from other
            DeepCopyArray(other.array_, other.size_);
        }

        Array& operator=(const Array<T>& other)
        {
            if (this != other)
            {
                // Reset to default Array parameters(array_ to NULL, size_ to 0)
                ResetToDefault();

                // Deep copy array from other
                size_ = other.size_;
                DeepCopyArray(other.array_, other.size_);
            }
            return *this;
        }

        T& operator[](const size_t index)
        {
            if (index < size_)
            {
                return array_[index];
            }
            throw std::out_of_range("Index out of bounds");
        }

        const T& operator[](const size_t index) const 
        {
            if (index < size_)
            {
                return array_[index];
            }
            throw std::out_of_range("Index out of bounds");
        }

        ~Array()
        {
            DeleteArray();
        }
    private:
        size_t size_;
        T* array_;

        void DeepCopyArray(const T* source, const size_t source_size)
        {
            if (source && source_size && source_size == size_)
            {
                array_ = new T[source_size];
                for (size_t i = 0; i < source_size; ++i)
                {
                    array_[i] = source[i];
                }
            } 
        }

        void ResetToDefault()
        {
            DeleteArray();
            size_ = 0;
        }

        void DeleteArray()
        {
            if (array_)
            {
                delete[] array_;
                array_ = NULL;
            }
        }
};

#endif