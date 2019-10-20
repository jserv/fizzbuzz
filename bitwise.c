#include <stdbool.h>
#include <stdint.h>
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

static inline bool is_divisible(uint32_t n, uint64_t M)
{
    return n * M <= M - 1;
}

static uint64_t M3 = UINT64_C(0xFFFFFFFFFFFFFFFF) / 3 + 1;
static uint64_t M5 = UINT64_C(0xFFFFFFFFFFFFFFFF) / 5 + 1;

int main(int argc, char **argv)
{
    for (size_t i = 1; i <= 100; i++) {
        uint8_t div3 = is_divisible(i, M3);
        uint8_t div5 = is_divisible(i, M5);
        unsigned int length = (2 << div3) << div5;
        /* default length is 2 and shift up by one for each bit set */

        char fmt[MSG_LEN + 1];
        strncpy(fmt, &"FizzBuzz%u"[(MSG_LEN >> div5) >> (div3 << 2)], length);
        /*                           [--------]             [----]
         *                 Shift down 1 if div5   Shift down another 4 if div3
         */
        fmt[length] = '\0';

        printf(fmt, i);
        printf("\n");
    }
    return 0;
}
