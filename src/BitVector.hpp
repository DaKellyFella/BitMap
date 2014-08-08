/*
 * BitVector.hpp
 *
 *  Created on: Feb 21, 2014
 *      Author: rob
 * A BitVector class useful for saving space for boolean arrays.
 * Accesses are constant time and very efficient with a lot
 * being optimised away at compile time, eg. all sizeof calls
 * can be destroyed and leaving only raw numbers.
 */

#ifndef BITVECTOR_HPP_
#define BITVECTOR_HPP_

#include <cmath>
#include <iostream>
#include <cstdint>
#include <cstring>

class BitVector
{
	uint64_t size;
	uint8_t * array;
public:
	enum Value{
		OFF,
		ON
	};
	BitVector(uint64_t inSize)
	{
		size = inSize / (sizeof(uint8_t) * 8); // Considering using a shift by 3 here.
		if((inSize & ((sizeof(uint8_t) * 8) - 1)) != 0) ++size; // Not a multiple of 8
		array = new uint8_t[size];
		for(uint64_t i = 0; i < size; ++i) array[i] = OFF;
	}

	BitVector(const BitVector & inVector):
		size(inVector.size), array(new u_int8_t[size])
	{
		std::memcpy(array, inVector.array, size);
	}

	const BitVector& operator=(const BitVector & inVector)
	{
		if(this == &inVector) return *this;
		delete[] array;
		size = inVector.size;
		array = new u_int8_t[inVector.size];
		std::memcpy(array, inVector.array, size);
		return *this;
	}

	inline bool getValue(int64_t inIndex) const
	{
		uint64_t realIndex = inIndex / (sizeof(uint8_t) * 8); // Potentially a left shift by 3
		uint8_t shiftOffset = inIndex & ((sizeof(uint8_t) * 8) - 1);
		uint8_t mask = 1 << shiftOffset;
		return (array[realIndex] & mask) != OFF; // A non-zero result means its set
	}
	inline void setValue(uint64_t inIndex, Value val)
	{
		uint64_t realIndex = inIndex / (sizeof(uint8_t) * 8);
		uint8_t shiftOffset = inIndex & ((sizeof(uint8_t) * 8) - 1);
		if(val == ON)
		{
			uint8_t mask = val << shiftOffset;
			array[realIndex] |= mask;
		}else
		{
			uint8_t mask = ~(ON << shiftOffset);
			array[realIndex] &= mask;
		}
	}
	inline void flipBit(int64_t inIndex)
	{
		getValue(inIndex) == ON ? setValue(inIndex, OFF) :
				setValue(inIndex, ON);
	}
	inline void reset()
	{
		for(uint64_t i = 0; i < size; ++i) array[i] = OFF;
	}
	inline uint64_t getSize()
	{
		return size * (sizeof(uint8_t) * 8); // A shift here could be useful too.
	}
	void printBits() const
	{
		std::cout << "[ ";
		for(uint64_t i = 0; i < size; ++i)
		{
			for(uint64_t j = 0; j < (sizeof(uint8_t) * 8); ++j)
			{
				uint8_t mask = 1 << j;
				u_int8_t val = (array[i] & mask);
				if(val != 0)
				{
					std::cout << 1 << " ";
				}else
				{
					std::cout << 0 << " ";
				}
			}
		}
		std::cout << "] ";
	}
};

#endif /* BITVECTOR_HPP_ */
