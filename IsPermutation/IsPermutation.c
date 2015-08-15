#define DEBUG 0
#include <stdio.h>

// Runtime: O(c^2)
	// O(c) 	  for size comparison
	// O(c^2 - c) for shifting
// this code should realistically never be used,
// it's a brainteaser example of how to check if
// string A is a permutation of string B with the
// following rules:
// 1. No variable creation
// 2. No function/macro calls (except printf for debugging)
// 2. No memory (stack, heap) usage/manipulation outside of the char*
// 3. Either (not both) of the strings may be modified, but its padding/null
//    terminator may not be modified
// 4. A[-1] = 0 (see assumptions)

// return 1 if true, 0 if false, 2 if rule three and/or assumptions violated

// Assumption 1: the caller's stack is laid out such that
// A exists on the stack adjacent to B,
// at a higher address than B,
// both padded to `wordsize` bytes
//
// Concrete example: A = "a" (0x61), B = "b" (0x62)
// B[16] = A = 'a'
// A[-16] = B = 'b'
// addr0:	62 00 ?? ?? ?? ?? ?? ?? ??
// addr8:	61 00 ?? ?? ?? ?? ?? ?? ??
//
// Generic example:
// addr0:	B0 B1 B2 B3 B4 B5 B6 B7 B8
//			...
// addrN:	BN 00 ?? ?? ?? ?? ?? ?? ??
// addrN+8:	A0 A1 ...   AN 00 ?? ?? ??

// Assumption 2: the uninitialized bytes ("??"s) are set to 00 so
// A[-1] = 0
int isPermutation(char * stA, char * stB)
{
	if (DEBUG)
	{
		printf("1: ptrA: %p, ptrB: %p\n", stA, stB);
		
		if (*(stA - 1) != 0)
		{
			printf("rule 3 and/or assumptions violated");
			return 2;
		}
	}

	// if we're given 2 empty strings, they are permutations
	if (!*stA && !*stB)
	{
		return 1;
	}

	// if we're given 1 empty string, no permutation
	if (!*stA || !*stB)
	{
		return 0;
	}

// REGION: compare length
// O(c)
	// travel to the end of one/both of the arrays
	while (*stA && *stB)
	{
		stA++;
		stB++;
	}

	// if we're at the end of only 1 array, the
	// strings are different lengths
	if (*stA != *stB)
	{
		return 0;
	}

	// go back one byte to make the following loop easier
	stA--;
	stB--;

	if (DEBUG)
	{
		printf("2: ptrA: %p, ptrB: %p\n", stA, stB);
	}
// ENDREGION

// REGION: loop backwards through A, removing equal chars from B until either a
// char is not found, or B is entirely 00 and stA points one right of the terminator
// Worst case is a reversed and no duplicates string, every character will shift
// the string by the number of characters remaining
// O(c^2 - c)
	// for all the characters in string A
	while (*stA)
	{
		// for all characters in string B
		while (*stB)
		{
			// if we match
			if (*stB == *stA)
			{
				// remove this char from the string and shift
				// the remaining characters to the left
				while (*stB)
				{
					*stB = *(stB + 1);
					stB++;
				}

				// we're pointing to 0x00 and we just
				// moved 0x00 to our left, move
				// left two chars to get to the new
				// end of B
				stB--;
				stB--;

				// if the end of B is now 0x00, and the
				// byte to the left of stA is A's null terminator, then
				// the strings are a permutations
				if (!*stB && !*(stA - 1))
				{
					return 1;
				}

				// we break here where `!*stB` is guaranteed to be 
				// false so that we can use that `!*stB` to see if
				// we've searched through all chars and are
				// now at the beginning of the string without a match
				break;
			}
			stB--;
		}

		// if we finished the inner loop and are now back
		// at the beginning of the string, we didn't find
		// the char from A in B, so it is not a permutation
		if (!*stB)
		{
			return 0;
		}

		// increment the outer loop
		stA--;
	}
// ENDREGION

	printf("Some assumption/rule was violated, or a bug exists \n");
	return 2;
}
