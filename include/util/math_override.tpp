#ifndef MATH_OVERRIDE_HPP
#define MATH_OVERRIDE_HPP

#include "../assets/curses_lib_selector.hpp"

/**
 * @brief https://en.wikipedia.org/wiki/Pairing_function#Cantor_pairing_function
 * 
 * @note PR function to pair two numbers into one: N x N -> N
 * @note It's the same thing as the swallowtail visualization,
 * mapping each pair of numbers to a single number.
 * @note (Used in the demonstration of cardinality of the set of all pairs of natural numbers)
 * 
 * @example cantor(0x323232, 0x646464) = 0x323232646464 -> 55191175193700
*/
#define cantor(a, b) ((a + b) * (a + b + 1) / 2 + b) 

/**
 * @brief https://en.wikipedia.org/wiki/Pairing_function#Inverting_the_Cantor_pairing_function
 * 
 * @note Inverse of the cantor function
 * 
 * @example dcantor(0x323232646464) = 0x323232, 0x646464
 * @example dcantor(55191175193700) = 0x323232, 0x646464
*/
#define dcantor(val) (int)((sqrt(8 * val + 1) - 1) / 2), (int)(val - ((int)((sqrt(8 * val + 1) - 1) / 2) * ((int)((sqrt(8 * val + 1) - 1) / 2) + 1)) / 2)

namespace mathy {
	// Returns the number of digits in a number
	template <class T> int numDigits(T number);
}

#include "../../src/util/math_override.ipp"

#endif