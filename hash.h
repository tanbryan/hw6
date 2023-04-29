#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0};
        size_t idx = 4;

    for(size_t i = 0; i < k.size(); i+=6){
        std::vector<HASH_INDEX_T> vec(6, 0); 
        for(size_t j = 0; j < vec.size(); j++){
            w[idx] += letterDigitToNumber(k[k.size() - 1 - i - j]) * pow(36, j);
        }
        idx--;
    }
    unsigned long long h = 0;
    for(int i = 0; i < 5; i++){
        h += rValues[i] * w[i];
    }
    return h;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        letter = char(tolower(letter));
        if(letter >= 'a' && letter <= 'z'){
            return letter - 'a';
        }
        else if(isdigit(letter)){
            return letter - '0' + 26;
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
