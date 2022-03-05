/**
 * AUTHORS: <Ohad Maday>
 * 
 * Date: 2022-03
 */

#include "doctest.h"
#include "mat.hpp"
#include <string>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
using namespace ariel;

float floatGenerator(bool type);
char randomSymbol();
int oddIntegerGenerator(bool type);
int evenIntegerGenerator(bool type);

char symbA = randomSymbol(), symbB = randomSymbol();

//printf( "got here! 22");
/** 
 * Returns the input string without the whitespace characters: space, newline and tab.
 * Requires std=c++2a.
 */
string no_spaces(string input) {
    std::erase(input, ' ');
    std::erase(input, '\t');
    std::erase(input, '\n');
    std::erase(input, '\r');
    return input;
}


/**
 * @brief Check if Rows and Cols are even number (aka even * even, odd * even, even*odd)
 * 
 */
TEST_CASE("Even ROWS * COLS"){
    int a = evenIntegerGenerator(true), b = evenIntegerGenerator(true), c = evenIntegerGenerator(false), d = evenIntegerGenerator(false); 
    int e = oddIntegerGenerator(true), g = oddIntegerGenerator(false);
     CHECK_THROWS(mat(2,2,'$','!')); // even * even (positive)
     CHECK_THROWS(mat(b,a,symbA,symbB)); // even * even (positive)
     CHECK_THROWS(mat(a,a,symbA,symbB)); // even * even (same positive)
     CHECK_THROWS(mat(a,c,symbA,symbB)); // even * even (positive - negative)
     CHECK_THROWS(mat(c,a,symbA,symbB)); // even * even (negative - positive)
     CHECK_THROWS(mat(c,d,symbA,symbB)); // even * even (negative - negative)
     CHECK_THROWS(mat(c,c,symbA,symbB)); // even * even (same negative)
     CHECK_THROWS(mat(a,e,symbA,symbB)); // even * odd (positive - positive)
     CHECK_THROWS(mat(e,a,symbA,symbB)); // odd * even (positive - positive)
     CHECK_THROWS(mat(a,g,symbA,symbB)); // even * odd (positive - negative)
     CHECK_THROWS(mat(g,a,symbA,symbB)); // odd * even (negative - positive)
     CHECK_THROWS(mat(c,g,symbA,symbB)); // even * odd (negative - negative)
}


/**
 * @brief Check if arguments can be negative and special characters are good
 * 
 */
TEST_CASE("Negative ROWS & COLS") {
    int a = oddIntegerGenerator(false), b = oddIntegerGenerator(true), c = oddIntegerGenerator(false);
    CHECK_THROWS(mat(a,b,symbA,symbB));
    CHECK_THROWS(mat(b,c,symbA,symbB));
    CHECK_THROWS(mat(a,c,symbA,symbB));

}

/**
 * @brief Check if can a parameter be a char\integer which isn't special and special where not needed
 * 
 */
TEST_CASE("Special characters arguments"){
    int a = oddIntegerGenerator(false), b = oddIntegerGenerator(true), c = oddIntegerGenerator(false);
    float z = floatGenerator(true), x = floatGenerator(false);
    CHECK_THROWS(mat(b,b,a,b));
    CHECK_THROWS(mat(b,b,b,b));
    CHECK_THROWS(mat(symbA,symbB,symbA,symbB));
    CHECK_THROWS(mat(symbA,symbA,symbA,symbA));
    CHECK_THROWS(mat(symbA,b,b,symbB));
    CHECK_THROWS(mat(b,symbB,b,symbB));
    CHECK_NOTHROW(mat(b,b,symbA,b)); // should print symbA filled matrix size of b*b
    CHECK_THROWS(mat(z,x,symbA,symbB));
    CHECK_THROWS(mat(a,x,b,symbB));
    CHECK_THROWS(mat(z,x,symbA,z));
    CHECK_THROWS(mat(z,x,b,symbB));
    CHECK_THROWS(mat(z,symbA,symbA,symbB));
    CHECK_THROWS(mat(z,z,symbA,z)); 
    CHECK_NOTHROW(mat(b,b,symbA,symbA)); // should work? haven't received clear instruction about same symbol
}

/**
 * @brief Rows or Cols are zero
 * 
 */
TEST_CASE("Zero in ROWS & COLS") {
    int a = oddIntegerGenerator(false), b = oddIntegerGenerator(true);
    CHECK_THROWS(mat(0,b,symbA,symbB));
    CHECK_THROWS(mat(0,a,symbA,symbB));
    CHECK_THROWS(mat(b,0,symbA,symbB));
    CHECK_THROWS(mat(a,0,symbA,symbB));
    CHECK_THROWS(mat(0,0,symbA,symbB));

}

/**
 * @brief matrix size of even number or odd number multiply by 1
 * 
 */
TEST_CASE("Row or Cols are 1"){
    int a = evenIntegerGenerator(true);
    int b = oddIntegerGenerator(true);
    CHECK_THROWS(mat(1,a,symbA,symbB));  //size is EVEN, 1 * even number = even number
    CHECK_THROWS(mat(a,1,symbA,symbB));  //size is EVEN, 1 * even number = even number
    CHECK_THROWS(mat(-a,1,symbA,symbB));  // negative number & 1
    CHECK_THROWS(mat(1,-a,symbA,symbB));  // negative number & 1
    CHECK_NOTHROW(mat(1,b,symbA,symbB)); //size is ODD 1 * odd number = odd number
    CHECK_NOTHROW(mat(b,1,symbA,symbB)); //size is ODD 1 * odd number = odd number   
}

/**
 * @brief Check if the rows & cols can be fractions (obviously can't)
 * 
 */
TEST_CASE("Fractions ROWS & COLS"){
    float a = floatGenerator(true), b = floatGenerator(false), e = floatGenerator(true), f = floatGenerator(false);
    int c = oddIntegerGenerator(true), d = oddIntegerGenerator(false);
    CHECK_THROWS(mat(a,c,symbA,symbB)); // positive float * positive integer
    CHECK_THROWS(mat(c,a,symbA,symbB)); // positive integer * positive float 
    CHECK_THROWS(mat(a,d,symbA,symbB)); // positive float * negative integer 
    CHECK_THROWS(mat(d,a,symbA,symbB)); // negative integer * positive float 
    CHECK_THROWS(mat(b,d,symbA,symbB)); // negative float * negative integer
    CHECK_THROWS(mat(d,b,symbA,symbB)); // negative integer * negative float
    CHECK_THROWS(mat(a,a,symbA,symbB)); // positive float * positive float -- same numbers
    CHECK_THROWS(mat(b,b,symbA,symbB)); // negative float * negative float -- same numbers
    CHECK_THROWS(mat(a,e,symbA,symbB)); // positive float * positive float -- different numbers
    CHECK_THROWS(mat(b,f,symbA,symbB)); // negative float * negative float -- different numbers
    CHECK_THROWS(mat(a,b,symbA,symbB)); // positive float * negative float
    CHECK_THROWS(mat(b,a,symbA,symbB)); // negative float * positive float

}

TEST_CASE("Good input") {
    CHECK(no_spaces(mat(9, 7, '@', '-')) == no_spaces("@@@@@@@@@@@@@\n@-----------@\n@-@@@@@@@@@-@\n@-----------@\n@@@@@@@@@@@@@"));

    CHECK(no_spaces(mat(13, 5, '@', '-')) == no_spaces("@@@@@@@@@\n@-------@\n@-@@@@@-@\n@-@---@-@\n@-@@@@@-@\n@-------@\n@@@@@@@@@"));
    
    CHECK(no_spaces(mat(3, 5, '$', '+')) == no_spaces("$$$\n$+$\n$+$\n$+$\n$$$"));
    
    CHECK(no_spaces(mat(7,7, '!', '$')) == no_spaces("!!!!!!!\n!$$$$$!\n!$!!!$!\n!$!$!$!\n!$!!!$!\n!$$$$$!\n!!!!!!!"));

    CHECK(no_spaces(mat(3, 5, '$', '+')) == no_spaces("!!!\n!!!\n!!!\n!!!\n!!!"));

    CHECK(no_spaces(mat(1, 1, '#', ')')) == no_spaces("#"));

    }



/**
 * @brief generates random float between 0 and 100 (is there any need to check for an higher number?) 
 * @param type :
 *               true - positive float
 *              ,false - negative float
 * @return float 
 */
float floatGenerator(bool type){
    srand(time(0));
    float num = ((float)rand()/(float)(RAND_MAX)) * 100.0;
    return type == true ? num : -num;
    }

/**
 * @brief generates random even number between 0 and 100 (is there any need for an higher number?) 
 * @param type :
 *               true - positive integer
 *              ,false - negative integer
 * @return int 
 */
int evenIntegerGenerator(bool type){
    srand(time(0));
    int num = 0;
    while (true)
    {  
        num = (int) (rand()*100); 
        if (num % 2 == 0) {
            break;
        }
    }
    return type == true ? num : -num;
}

/**
 * @brief generates random odd number between 0 and 100 (is there any need for an higher number?) 
 * @param type :
 *               true - positive integer
 *              ,false - negative integer
 * @return int 
 */
int oddIntegerGenerator(bool type){
    srand(time(0));
    int num = 0;
    while (true)
    {  
        num = (int) (rand()*100) + 1; // have to be from the form of 2k+1
        if (num % 2 != 0) {
            break;
        }
    }
    return type == true ? num : -num;
}

/**
 * @brief generate random symbol
 * couldn't find any better way doing it, the rand() with the bounderies would unefficient because of too many bounderies so went old school
 * @return char 
 */
char randomSymbol(){
    const char symbols[] = {'!','@','#','$','%','^','&','*','-','_','=','+','`','~'};
    srand(time(0)); //initialize the random seed
    int idx = rand() % 14; //instead of using sizeof(symbols)/sizeof(symbols[0]) because it's a known size
    return symbols[idx];
}