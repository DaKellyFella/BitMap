/*
 * Sieve.hpp
 *
 *  Created on: Feb 21, 2014
 *      Author: rob
 */

#ifndef SIEVE_HPP_
#define SIEVE_HPP_

#include <cmath>
#include "BitMap.hpp"

// A prime finding technique for finding primes.
int64_t returnNthPrime(int64_t nTh)
{
	int64_t arraySize = 1.3f * nTh * std::log(nTh);
	if(nTh < 10) arraySize = 100; // For the safe side
	BitMap array(arraySize); // The boss
	for(int64_t i = 2; i < arraySize; ++i) array.setValue(i, BitMap::ON);
	int64_t limit = std::sqrt(arraySize) + 1;
	array.setValue(0, BitMap::OFF);
	array.setValue(1, BitMap::OFF);
	for(int64_t i = 2; i < limit; ++i)
	{
		if(array.getValue(i))
		{
			for(int64_t j = i + i; j < arraySize; j += i)
			{
				array.setValue(j, BitMap::OFF);
			}
		}
	}
	int64_t primes = 0;
	int64_t nthPrime = 0;
	for(int64_t i = 2; i < arraySize; ++i)
	{
		if(array.getValue(i))
		{
			++primes;
			if(primes == nTh)
			{
				nthPrime = i;
				break;
			}
		}
	}
	return nthPrime;
}

#endif /* SIEVE_HPP_ */
