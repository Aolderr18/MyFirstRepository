/*
 * The BigNumber class was designed to create instances of numbers with large 
 * amounts of digits. Its functions include addition, subtraction, multiplication
 * division, powers, and roots. It also includes the ability to round to a desired
 * digit place and get rid of unnecessary zeros at the beginning and end of each
 * number. It primarily serves for solving for variables in equations with decimal
 * digit precision exceeding 100 places.
 */

#ifndef BIGNUMBER_H
#define BIGNUMBER_H
#include <iostream>

using namespace std;

class BigNumber {
    private:
        bool nonNegative; // Whether a BigNumber is nonnegative or negative
        string integerDigits, decimalDigits;
    public:
        BigNumber();
        BigNumber(string, string);
        BigNumber(bool, string, string);
        string userVisibleRepresentation();
        BigNumber sum(BigNumber); // Adding another BigNumber
        BigNumber difference(BigNumber); // Subtracting another BigNumber
        BigNumber product(BigNumber); // Multiplying by another BigNumber
        BigNumber quotient(BigNumber); // Dividing by another BigNumber
        BigNumber power(int); // Raising the BigNumber to an integer power
        BigNumber root(int); // Computing the integer square root of a BigNumber
        void trimZeros(); /*
                           * This function deletes all unnecessary zeros at the
                           * beginning and end of a number. For example, 7.1300 
                           * becomes 7.13, 05.19 becomes 5.19, 08.34000 becomes 
                           * 8.34.
                           */
        void round(int); // Rounds the BigNumber to a desired digit place
        bool hasGreaterAbsoluteValueThan(BigNumber);
        bool hasLowerAbsoluteValueThan(BigNumber);
        bool hasEqualAbsoluteValueTo(BigNumber);
        bool isGreaterThan(BigNumber);
        bool isLessThan(BigNumber);
        bool isEqualTo(BigNumber);
        bool isGreaterThanOrEqualTo(BigNumber);
        bool isLessThanOrEqualTo(BigNumber);
        
        // Accessors
        bool isNonNegative();
        string getIntegerDigits();
        string getDecimalDigits();
        
        // Mutators
        void setNonNegative(bool);
        void setIntegerDigits(string);
        void setDecimalDigits(string);
};

#endif
