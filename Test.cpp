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


char randomSymbol(); // generates random special character
int oddIntegerGenerator(bool type); // generates random odd number (negative/positive)
int evenIntegerGenerator(bool type); // generates random even number (negative/positive)

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
    srand(time(NULL));
    char symbA = randomSymbol(), symbB = randomSymbol(); // generates random special character
    int even_number1 = evenIntegerGenerator(true), even_number2 = evenIntegerGenerator(true), nega_even_number1 = evenIntegerGenerator(false), nega_even_number2 = evenIntegerGenerator(false);
    int odd_number1 = oddIntegerGenerator(true), odd_number2 = oddIntegerGenerator(true), nega_odd_number1 = oddIntegerGenerator(false), nega_odd_number2 = oddIntegerGenerator(false);
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
    srand(time(NULL));
    int odd_number1 = oddIntegerGenerator(true), odd_number2 = oddIntegerGenerator(true), nega_odd_number1 = oddIntegerGenerator(false), nega_odd_number2 = oddIntegerGenerator(false);
    char symbA = randomSymbol(), symbB = randomSymbol(); // generates random special character
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
    srand(time(NULL));
    int odd_number1 = oddIntegerGenerator(true), odd_number2 = oddIntegerGenerator(true), nega_odd_number1 = oddIntegerGenerator(false), nega_odd_number2 = oddIntegerGenerator(false);
     int even_number1 = evenIntegerGenerator(true), even_number2 = evenIntegerGenerator(true), nega_even_number1 = evenIntegerGenerator(false), nega_even_number2 = evenIntegerGenerator(false);
    char symbA = randomSymbol(), symbB = randomSymbol(); // generates random special character
    CHECK_NOTHROW(mat(odd_number1,odd_number1,odd_number1,odd_number1));
    CHECK_THROWS(mat(even_number1,odd_number1,odd_number1,symbB));
    CHECK_THROWS(mat(odd_number1,nega_odd_number1,odd_number1,symbB));
    CHECK_NOTHROW(mat(odd_number1,odd_number1,symbA,odd_number1)); // should print symbA filled matrix size of b*b
    CHECK_THROWS(mat(nega_odd_number1,nega_odd_number1,odd_number1,symbB));
    CHECK_THROWS(mat(odd_number1,nega_odd_number2,symbA,symbB));
    CHECK_NOTHROW(mat(odd_number1,odd_number1,symbA,symbA)); // should work? haven't received clear instruction about same symbol
}

/**
 * @brief Rows or Cols are zero
 *
 */
TEST_CASE("Zero in ROWS & COLS") {
    srand(time(NULL));
    int odd_number1 = oddIntegerGenerator(true), nega_odd_number1 = oddIntegerGenerator(false);
    char symbA = randomSymbol(), symbB = randomSymbol(); // generates random special character
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
    srand(time(NULL));
    char symbA = randomSymbol(), symbB = randomSymbol(); // generates random special character
    int even_number1 = evenIntegerGenerator(true), even_number2 = evenIntegerGenerator(true), nega_even_number1 = evenIntegerGenerator(false), nega_even_number2 = evenIntegerGenerator(false);
    int odd_number1 = oddIntegerGenerator(true), odd_number2 = oddIntegerGenerator(true), nega_odd_number1 = oddIntegerGenerator(false), nega_odd_number2 = oddIntegerGenerator(false);
    CHECK_THROWS(mat(1,even_number1,symbA,symbB));  //size is EVEN, 1 * even number = even number
    CHECK_THROWS(mat(even_number1,1,symbA,symbB));  //size is EVEN, 1 * even number = even number
    CHECK_THROWS(mat(nega_even_number1,1,symbA,symbB));  // negative even number & 1
    CHECK_THROWS(mat(1,nega_even_number1,symbA,symbB));  // negative even number & 1
    CHECK_NOTHROW(mat(1,odd_number1,symbA,symbB)); //size is ODD 1 * odd number = odd number
    CHECK_NOTHROW(mat(odd_number2,1,symbA,symbB)); //size is ODD 1 * odd number = odd number
    CHECK_THROWS(mat(nega_odd_number1,1,symbA,symbB));  // negative odd number & 1
    CHECK_THROWS(mat(1,nega_odd_number1,symbA,symbB));  // negative odd number & 1

}


TEST_CASE("Good input") {
    CHECK(no_spaces(mat(7,7, '!', '$')) == no_spaces("!!!!!!!\n!$$$$$!\n!$!!!$!\n!$!$!$!\n!$!!!$!\n!$$$$$!\n!!!!!!!"));
    CHECK(no_spaces(mat(3, 5, '!', '!')) == no_spaces("!!!\n!!!\n!!!\n!!!\n!!!"));
    CHECK(no_spaces(mat(1, 1, '#', ')')) == no_spaces("#"));
    CHECK(no_spaces(mat(1, 1, '!', ')')) == no_spaces("!"));
    CHECK(no_spaces(mat(5,3, '!', '$')) != no_spaces("!!!!\n!$$$$!\n!$!!!$!\n!$!$!$!\n!$!!!$!\n!$$$$$!\n!!!!!"));
    CHECK(no_spaces(mat(51,3, '_', '!')) != no_spaces("___________________________________________________\n_!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_\n___________________________________________________"));

}



/**
 * @brief generates random even number between 0 and 100 (is there any need for an higher number?)
 * @param type :
 *               true - positive integer
 *              ,false - negative integer
 * @return int
 */
int evenIntegerGenerator(bool type){
    int num = 0;
    while (true)
    {
        num = rand()%(100+1-0)+0;
        if (num % 2 == 0) {
            break;
        }
    }
    return type ? num : -num;
}

/**
 * @brief generates random odd number between 0 and 100 (is there any need for an higher number?)
 * @param type :
 *               true - positive integer
 *              ,false - negative integer
 * @return int
 */
int oddIntegerGenerator(bool type){
    int num = 0;
    while (true)
    {
        num = (int) rand()%(100+1-0)+0;
        if (num % 2 != 0) {
            break;
        }
    }
    return type ? num : -num;
}

/**
 * @brief generate random symbol
 * couldn't find any better way doing it, the rand() with the bounderies would unefficient because of too many bounderies so went old school
 * @return char
 */
char randomSymbol(){
    const char symbols[] = {'!','@','#','$','%','^','&','*','-','_','=','+','`','~'};
    int idx = rand() % 14; //instead of using sizeof(symbols)/sizeof(symbols[0]) because it's a known size
    return symbols[idx];
}
