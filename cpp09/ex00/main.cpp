#include "include/BitcoinExchange.hpp"

int main()
{
    BitcoinExchange btc;

    if (!btc.LoadCsvDatabase("data.csv"))
    {
        return 1;
    }

    if (!btc.LoadInputAndDisplayResults("input.txt"))
    {
        return 1;
    }
    
    return 0;
}