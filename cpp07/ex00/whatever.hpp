#ifndef WHATEVER_HPP
#define WHATEVER_HPP

template<typename Value>
void swap(Value& a, Value& b)
{
    Value tmp = a;
    a = b;
    b = tmp;
}

template<typename Value>
Value min(const Value& a, const Value& b)
{
    return (a < b) ? a : b;
}

template <typename Value>
Value max(const Value& a, const Value& b)
{
    return (a > b) ? a : b;
}

#endif // WHATEVER_HPP
