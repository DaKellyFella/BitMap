#include <iostream>
#include "Sieve.hpp"


int main(int argc, char * argv[])
{
	std::cout << returnNthPrime(1000) << std::endl;
	std::cout << returnNthPrime(1000000) << std::endl;
	std::cout << returnNthPrime(1000000000) << std::endl;
    return 0;
}
