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

float floatGenerator(bool type); // generates float number (negative/positive)
char randomSymbol(); // generates random special character
int oddIntegerGenerator(bool type); // generates random odd number (negative/positive)
int evenIntegerGenerator(bool type); // generates random even number (negative/positive)

char symbA = randomSymbol(), symbB = randomSymbol();

int even_number1 = evenIntegerGenerator(true), even_number2 = evenIntegerGenerator(true), nega_even_number1 = evenIntegerGenerator(false), nega_even_number2 = evenIntegerGenerator(false); 
int odd_number1 = oddIntegerGenerator(true), odd_number2 = oddIntegerGenerator(true), nega_odd_number1 = oddIntegerGenerator(false), nega_odd_number2 = oddIntegerGenerator(false);
float fraction = floatGenerator(true), nega_fraction = floatGenerator(false), fraction2 = floatGenerator(true), nega_fraction2 = floatGenerator(false) ;
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
     CHECK_THROWS(mat(even_number1,even_number2,symbA,symbB)); // even * even (positive)
     CHECK_THROWS(mat(even_number2,even_number1,symbA,symbB)); // even * even (positive)
     CHECK_THROWS(mat(even_number1,even_number1,symbA,symbB)); // even * even (same positive)
     CHECK_THROWS(mat(even_number1,nega_even_number1,symbA,symbB)); // even * even (positive - negative)
     CHECK_THROWS(mat(nega_even_number1,even_number1,symbA,symbB)); // even * even (negative - positive)
     CHECK_THROWS(mat(nega_even_number1,nega_even_number2,symbA,symbB)); // even * even (negative - negative)
     CHECK_THROWS(mat(nega_even_number1,nega_even_number1,symbA,symbB)); // even * even (same negative)
     CHECK_THROWS(mat(even_number1,odd_number1,symbA,symbB)); // even * odd (positive - positive)
     CHECK_THROWS(mat(odd_number1,even_number1,symbA,symbB)); // odd * even (positive - positive)
     CHECK_THROWS(mat(even_number1,nega_odd_number1,symbA,symbB)); // even * odd (positive - negative)
     CHECK_THROWS(mat(nega_odd_number1,even_number1,symbA,symbB)); // odd * even (negative - positive)
     CHECK_THROWS(mat(nega_even_number1,nega_odd_number1,symbA,symbB)); // even * odd (negative - negative)
}


/**
 * @brief Check if arguments can be negative and special characters are good
 * 
 */
TEST_CASE("Negative ROWS & COLS") {
    CHECK_THROWS(mat(nega_odd_number1,odd_number1,symbA,symbB)); // odd * odd (negative - positive)
    CHECK_THROWS(mat(odd_number1,nega_odd_number2,symbA,symbB)); // odd * odd (positive - negative)
    CHECK_THROWS(mat(nega_odd_number1,nega_odd_number2,symbA,symbB)); // odd * odd (negative - negative)
    CHECK_THROWS(mat(nega_odd_number1,nega_odd_number1,symbA,symbB)); // odd * odd (negative - negative)

}

/**
 * @brief Check if can a parameter be a char\integer which isn't special and special where not needed
 * 
 */
TEST_CASE("Special characters arguments"){
    CHECK_THROWS(mat(odd_number1,odd_number1,nega_odd_number1,odd_number1));
    CHECK_THROWS(mat(odd_number1,odd_number1,odd_number1,odd_number1));
    CHECK_THROWS(mat(symbA,symbB,symbA,symbB));
    CHECK_THROWS(mat(symbA,symbA,symbA,symbA));
    CHECK_THROWS(mat(symbA,odd_number1,odd_number1,symbB));
    CHECK_THROWS(mat(odd_number1,symbB,odd_number1,symbB));
    CHECK_NOTHROW(mat(odd_number1,odd_number1,symbA,odd_number1)); // should print symbA filled matrix size of b*b
    CHECK_THROWS(mat(fraction,nega_fraction,symbA,symbB));
    CHECK_THROWS(mat(nega_odd_number1,nega_fraction,odd_number1,symbB));
    CHECK_THROWS(mat(fraction,nega_fraction,symbA,fraction));
    CHECK_THROWS(mat(fraction,nega_fraction,odd_number1,symbB));
    CHECK_THROWS(mat(fraction,symbA,symbA,symbB));
    CHECK_THROWS(mat(fraction,fraction,symbA,fraction)); 
    CHECK_NOTHROW(mat(odd_number1,odd_number1,symbA,symbA)); // should work? haven't received clear instruction about same symbol
}

/**
 * @brief Rows or Cols are zero
 * 
 */
TEST_CASE("Zero in ROWS & COLS") {
    CHECK_THROWS(mat(0,odd_number1,symbA,symbB));
    CHECK_THROWS(mat(0,nega_odd_number1,symbA,symbB));
    CHECK_THROWS(mat(odd_number1,0,symbA,symbB));
    CHECK_THROWS(mat(nega_odd_number1,0,symbA,symbB));
    CHECK_THROWS(mat(0,0,symbA,symbB));

}

/**
 * @brief matrix size of even number or odd number multiply by 1
 * 
 */
TEST_CASE("Row or Cols are 1"){
    CHECK_THROWS(mat(1,even_number1,symbA,symbB));  //size is EVEN, 1 * even number = even number 
    CHECK_THROWS(mat(even_number1,1,symbA,symbB));  //size is EVEN, 1 * even number = even number
    CHECK_THROWS(mat(nega_even_number1,1,symbA,symbB));  // negative even number & 1
    CHECK_THROWS(mat(1,nega_even_number1,symbA,symbB));  // negative even number & 1
    CHECK_NOTHROW(mat(1,odd_number1,symbA,symbB)); //size is ODD 1 * odd number = odd number
    CHECK_NOTHROW(mat(odd_number2,1,symbA,symbB)); //size is ODD 1 * odd number = odd number   
    CHECK_THROWS(mat(nega_odd_number1,1,symbA,symbB));  // negative odd number & 1
    CHECK_THROWS(mat(1,nega_odd_number1,symbA,symbB));  // negative odd number & 1
    
}

/**
 * @brief Check if the rows & cols can be fractions (obviously can't)
 * 
 */
TEST_CASE("Fractions ROWS & COLS"){
    CHECK_THROWS(mat(fraction,odd_number1,symbA,symbB)); // positive float * positive integer
    CHECK_THROWS(mat(odd_number1,fraction2,symbA,symbB)); // positive integer * positive float 
    CHECK_THROWS(mat(fraction,nega_odd_number1,symbA,symbB)); // positive float * negative integer 
    CHECK_THROWS(mat(nega_odd_number1,fraction,symbA,symbB)); // negative integer * positive float 
    CHECK_THROWS(mat(nega_fraction,nega_odd_number2,symbA,symbB)); // negative float * negative integer
    CHECK_THROWS(mat(nega_odd_number1,nega_fraction,symbA,symbB)); // negative integer * negative float
    CHECK_THROWS(mat(fraction,fraction,symbA,symbB)); // positive float * positive float -- same numbers
    CHECK_THROWS(mat(nega_fraction,nega_fraction,symbA,symbB)); // negative float * negative float -- same numbers
    CHECK_THROWS(mat(fraction,odd_number1,symbA,symbB)); // positive float * positive float -- different numbers
    CHECK_THROWS(mat(nega_fraction,nega_fraction2,symbA,symbB)); // negative float * negative float -- different numbers
    CHECK_THROWS(mat(fraction,nega_fraction,symbA,symbB)); // positive float * negative float
    CHECK_THROWS(mat(nega_fraction,fraction2,symbA,symbB)); // negative float * positive float

}

TEST_CASE("Good input") {
    CHECK(no_spaces(mat(9, 7, '@', '-')) == no_spaces("@@@@@@@@@@@@@\n@-----------@\n@-@@@@@@@@@-@\n@-----------@\n@@@@@@@@@@@@@"));
    CHECK(no_spaces(mat(13, 5, '@', '-')) == no_spaces("@@@@@@@@@\n@-------@\n@-@@@@@-@\n@-@---@-@\n@-@@@@@-@\n@-------@\n@@@@@@@@@"));
    CHECK(no_spaces(mat(3, 5, '$', '+')) == no_spaces("$$$\n$+$\n$+$\n$+$\n$$$"));
    CHECK(no_spaces(mat(7,7, '!', '$')) == no_spaces("!!!!!!!\n!$$$$$!\n!$!!!$!\n!$!$!$!\n!$!!!$!\n!$$$$$!\n!!!!!!!"));
    CHECK(no_spaces(mat(3, 5, '!', '!')) == no_spaces("!!!\n!!!\n!!!\n!!!\n!!!"));
    CHECK(no_spaces(mat(1, 1, '#', ')')) == no_spaces("#"));
    CHECK(no_spaces(mat(5,3, '!', '$')) != no_spaces("!!!!\n!$$$$!\n!$!!!$!\n!$!$!$!\n!$!!!$!\n!$$$$$!\n!!!!!"));
    CHECK(no_spaces(mat(51,3, '_', '!')) != no_spaces("___________________________________________________\n_!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_\n___________________________________________________"));


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
    return type == false ? -num : -num;
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
    return type == false ? -num : num;
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
    return type == false ? -num : num;
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
