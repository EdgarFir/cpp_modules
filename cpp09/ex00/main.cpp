#include "BitcoinExchange.hpp"

int main()
{
    BitcoinExchange btc;

    if (!btc.LoadCsvDatabase("data.csv"))
    {
        return 1;
    }
    
    return 0;
}