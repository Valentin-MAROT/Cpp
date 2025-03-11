#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <utility>
#include <iostream>
#include <limits>

int main(){
    printf("size of (bit):\n");
    printf("\t char: %lu\n", sizeof(char)*8);
    printf("\t unsigned char: %lu\n", sizeof(unsigned char)*8);
    printf("\t short: %lu\n", sizeof(short)*8);
    printf("\t unsigned short: %lu\n", sizeof(unsigned short)*8);
    printf("\t int: %lu\n", sizeof(int)*8);
    printf("\t unsigned int: %lu\n", sizeof(unsigned int)*8);
    printf("\t long: %lu\n", sizeof(long)*8);
    printf("\t unsigned long: %lu\n", sizeof(unsigned long)*8);
    printf("\t long long: %lu\n", sizeof(long long)*8);
    printf("\t unsigned long long: %lu\n", sizeof(unsigned long long)*8);

    printf("max values:\n");
    printf("\t char: %d\n", (std::numeric_limits<char>::max()));
    printf("\t unsigned char: %u\n", (std::numeric_limits<unsigned char>::max()));
    printf("\t short: %d\n", (std::numeric_limits<short>::max()));
    printf("\t int: %d\n", (std::numeric_limits<int>::max()));
    printf("\t unsigned int: %u\n", (std::numeric_limits<unsigned int>::max()));
    printf("\t long: %ld\n", (std::numeric_limits<long>::max()));
    printf("\t unsigned long: %lu\n", (std::numeric_limits<unsigned long>::max()));
    printf("\t long long: %lld\n", (std::numeric_limits<long long>::max()));
    printf("\t unsigned long long: %llu\n", (std::numeric_limits<unsigned long long>::max()));

    printf("min values:\n");
    printf("\t char: %d\n", (std::numeric_limits<char>::min()));
    printf("\t unsigned char: %u\n", (std::numeric_limits<unsigned char>::min()));
    printf("\t short: %d\n", (std::numeric_limits<short>::min()));
    printf("\t int: %d\n", std::numeric_limits<int>::min());
    printf("\t unsigned int: %u\n", std::numeric_limits<unsigned int>::min());
    printf("\t long: %ld\n", std::numeric_limits<long>::min());
    printf("\t unsigned long: %lu\n", std::numeric_limits<unsigned long>::min());
    printf("\t long long: %lld\n", std::numeric_limits<long long>::min());
    printf("\t unsigned long long: %llu\n", std::numeric_limits<unsigned long long>::min());

    int8_t a = 127;
    uint8_t b = 255;
    int16_t c = 32767;
    uint16_t d = 65535;
    int32_t e = 2147483647;
    uint32_t f = 4294967295;
    int32_t g = 2147483647l;
    uint32_t h = 4294967295l;
    int64_t i = 9223372036854775807ll;
    uint64_t j = 18446744073709551615ull;
    
    printf("variables:\n");
    printf("\t char, int8_t a: %d\n", a);
    printf("\t unsigned char, uint8_t b: %u\n", b);
    printf("\t short, int16_t c: %d\n", c);
    printf("\t unsigned short, uint16_t d: %u\n", d);
    printf("\t int, int32_t e: %ld\n", e);
    printf("\t unsigned int, uint32_t f: %lu\n", f);
    printf("\t long, int64_t g: %ld\n", g);
    printf("\t unsigned long, uint64_t h: %lu\n", h);
    printf("\t long long, int64_t i: %lld\n", i);
    printf("\t unsigned long long, uint64_t j: %llu\n", j);
    



    return EXIT_SUCCESS;
}