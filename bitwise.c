#include <stdio.h>
#include <string.h>

/*
 * Based on the way printf manipulating format strings, we can specify
 * a single string for each kind of thing we want to print, in power of
 * two lengths.
 *
 * For a single integer, "%u" length == 2
 * For fizz or buzz, "fizz" or "buzz" length == 4
 * For fizzbuzz, length == 8
 *
 * Even better, we can set up a string so the starts of our format are at
 * powers of 2
 *
 * "fizzbuzz%u"
 *  0   4   8
 */

#define MSG_LEN 8

#define DIV5(x) ((x & 2) >> 1)
#define DIV3(x) (x & 1)

int main(int argc, char **argv)
{
    for (size_t i = 1; i <= 100; i++) {
        /* Define mask/flags for storing divisibility */
        unsigned int mask = 0;

        /* Create bitmask of the form 000000ab
           a - divisible by 5
           b - divisible by 3 */
        mask |= (!(i % 5) << 1) | !(i % 3);

        unsigned int start =
            // Shift down 1 if div5
            (MSG_LEN >> DIV5(mask))
            // Shift down another 4 if div3 */
            >> (DIV3(mask) << 2);

        // Default length is 2
        // Shift up by one for each bit set
        unsigned int length = (2 << (DIV3(mask))) << DIV5(mask);
        // Shift up by 1 for each bit set

        char fmt[MSG_LEN + 1];
        strncpy(fmt, &"FizzBuzz%u"[start], length);
        fmt[length] = '\0';

        printf(fmt, i);
        printf("\n");
    }
    return 0;
}
