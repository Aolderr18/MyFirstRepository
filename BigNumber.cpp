#include "BigNumber.h"
#include <sstream>
#include <cmath>

BigNumber::BigNumber()
{
    /*
     * A default constructor is essential for 
     * implementations of BigNumber.
     */
}

BigNumber::BigNumber(string integerDigits, string decimalDigits)
{
    setNonNegative(true); // By default, a number should be nonnegative.
    setIntegerDigits(integerDigits);
    setDecimalDigits(decimalDigits);
}

BigNumber::BigNumber(bool nonNegative, string integerDigits, string decimalDigits)
{
    setNonNegative(nonNegative);
    setIntegerDigits(integerDigits);
    setDecimalDigits(decimalDigits);
}

string BigNumber::userVisibleRepresentation()
{
    if (nonNegative)
    {
        if (decimalDigits.length() > 0)
            return integerDigits + "." + decimalDigits;
        return integerDigits;
    }
    if (decimalDigits.length() > 0)
        return "-" + integerDigits + "." + decimalDigits;
    return "-" + integerDigits;
}

BigNumber BigNumber::sum(BigNumber other)
{
    BigNumber duplicate(nonNegative, integerDigits, decimalDigits);
    if (not(nonNegative == other.isNonNegative()))
    {
        if (hasGreaterAbsoluteValueThan(other))
        {
            other.setNonNegative(nonNegative);
            return difference(other);
            /*
             * If a negative number is being added to a positive number with a 
             * greater absolute value, it is roughly equivalent to subtracting 
             * the additive inverse of that number.
             */
        }
        duplicate.setNonNegative(other.isNonNegative());
        return other.difference(duplicate);
    }
    stringstream operand1, operand2;
    unsigned differenceInLength = 0;
    /*
     * Both operand strings must have the same length for the algorithm to work.
     */
    if (integerDigits.length() > other.getIntegerDigits().length())
    {
        differenceInLength = integerDigits.length() - other.getIntegerDigits().length();
        while (differenceInLength)
        {
            operand2 << "0";
            differenceInLength--;
        }
    }
    else
    {
        differenceInLength = other.getIntegerDigits().length() - integerDigits.length();
        while (differenceInLength)
        {
            operand1 << "0";
            differenceInLength--;
        }
    }
    operand1 << integerDigits << decimalDigits;
    operand2 << other.getIntegerDigits() << other.getDecimalDigits();
    unsigned digitsAfterDecimal = 0;
    if (decimalDigits.length() > other.getDecimalDigits().length())
    {
        digitsAfterDecimal = decimalDigits.length();
        differenceInLength = decimalDigits.length() - other.getDecimalDigits().length();
        while (differenceInLength)
        {
            operand2 << "0";
            differenceInLength--;
        }
    }
    else
    {
        digitsAfterDecimal = other.getDecimalDigits().length();
        differenceInLength = other.getDecimalDigits().length() - decimalDigits.length();
        while (differenceInLength)
        {
            operand1 << "0";
            differenceInLength--;
        }
    }
    unsigned index, carry = 0;
    stringstream sumDigits;
    for (index = operand1.str().length() - 1; index + 1; index--)
    {
        unsigned placeSum = carry + operand1.str().at(index) + operand2.str().at(index) - 96;
        carry = (placeSum - placeSum % 10) / 10;
        placeSum %= 10;
        sumDigits << placeSum;
    }
    sumDigits << carry;
    stringstream sumIntegerDigits, sumDecimalDigits;
    for (index = sumDigits.str().length() - 1; index + 1; index--)
    {
        if (index < digitsAfterDecimal)
        {
            sumDecimalDigits << sumDigits.str().at(index);
            continue;
        }
        sumIntegerDigits << sumDigits.str().at(index);
    }
    duplicate.setIntegerDigits(sumIntegerDigits.str());
    duplicate.setDecimalDigits(sumDecimalDigits.str());
    duplicate.trimZeros();
    return duplicate;
}

BigNumber BigNumber::difference(BigNumber other)
{
    BigNumber duplicate(nonNegative, integerDigits, decimalDigits);
    if (not(nonNegative == other.isNonNegative()))
    {
        if (hasGreaterAbsoluteValueThan(other))
        {
            other.setNonNegative(nonNegative);
            return sum(other);
        }
        duplicate.setNonNegative(other.isNonNegative());
        return other.sum(duplicate);
    }
    stringstream operand1, operand2;
    unsigned differenceInLength = 0;
    unsigned totalLength = 0;
    if (integerDigits.length() > other.getIntegerDigits().length())
    {
        totalLength += integerDigits.length();
        differenceInLength = integerDigits.length() - other.getIntegerDigits().length();
        while (differenceInLength)
        {
            operand2 << "0";
            differenceInLength--;
        }
    }
    else
    {
        totalLength += other.getIntegerDigits().length();
        differenceInLength = other.getIntegerDigits().length() - integerDigits.length();
        while (differenceInLength)
        {
            operand1 << "0";
            differenceInLength--;
        }
    }
    operand1 << integerDigits << decimalDigits;
    operand2 << other.getIntegerDigits() << other.getDecimalDigits();
    unsigned digitsAfterDecimal = 0;
    if (decimalDigits.length() > other.getDecimalDigits().length())
    {
        totalLength += decimalDigits.length();
        digitsAfterDecimal = decimalDigits.length();
        differenceInLength = decimalDigits.length() - other.getDecimalDigits().length();
        while (differenceInLength)
        {
            operand2 << "0";
            differenceInLength--;
        }
    }
    else
    {
        totalLength += other.getDecimalDigits().length();
        digitsAfterDecimal = other.getDecimalDigits().length();
        differenceInLength = other.getDecimalDigits().length() - decimalDigits.length();
        while (differenceInLength)
        {
            operand1 << "0";
            differenceInLength--;
        }
    }
    unsigned operand1Digits[totalLength];
    unsigned operand2Digits[totalLength];
    int index;
    for (index = 0; totalLength - index; index++)
    {
        operand1Digits[index] = operand1.str().at(index) - 48;
        operand2Digits[index] = operand2.str().at(index) - 48;
    }
    stringstream differenceDigits;
    for (index = totalLength - 1; index + 1; index--)
    {
        int borrowIndex = index;
        unsigned placeDifference;
        if (operand1Digits[index] >= operand2Digits[index])
            placeDifference = operand1Digits[index] - operand2Digits[index];
        else
        {
            placeDifference = 10 + operand1Digits[index] - operand2Digits[index];
            try
            {
                do
                {
                    --borrowIndex;
                    operand1Digits[borrowIndex] += 10;
                    operand1Digits[borrowIndex] %= 11;
                }
                while (!(operand1Digits[borrowIndex]));
            }
            catch (std::exception outOfBounds)
            {
                
            }
        }
        differenceDigits << placeDifference;
    }
    stringstream differenceIntegerDigits, differenceDecimalDigits;
    for (index = differenceDigits.str().length() - 1; index + 1; index--)
    {
        if (index < digitsAfterDecimal)
        {
            differenceDecimalDigits << differenceDigits.str().at(index);
            continue;
        }
        differenceIntegerDigits << differenceDigits.str().at(index);
    }
    duplicate.setIntegerDigits(differenceIntegerDigits.str());
    duplicate.setDecimalDigits(differenceDecimalDigits.str());
    duplicate.trimZeros();
    return duplicate;
}

BigNumber BigNumber::product(BigNumber other)
{
    BigNumber product;
    BigNumber Zero(true, "0", "0");
    if (isEqualTo(Zero) or other.isEqualTo(Zero))
    {
        product.setIntegerDigits("0");
        product.setDecimalDigits("0");
        product.setNonNegative(true);
        return product;/*
                        * Zero multiplied by any number returns zero.
                        */
    }
    if (not(nonNegative == other.isNonNegative()))
        product.setNonNegative(false);/*
                                       * A negative multiplied by a positive
                                       * returns a negative.
                                       */
    else
        product.setNonNegative(true);/*
                                      * A negative multiplied by a negative or
                                      * a positive multiplied by a positive returns
                                      * a positive.
                                      */
    stringstream operand1, operand2;
    unsigned differenceInLength = 0;
    if (integerDigits.length() > other.getIntegerDigits().length())
    {
        differenceInLength = integerDigits.length() - other.getIntegerDigits().length();
        while (differenceInLength)
        {
            operand2 << "0";
            differenceInLength--;
        }
    }
    else
    {
        differenceInLength = other.getIntegerDigits().length() - integerDigits.length();
        while (differenceInLength)
        {
            operand1 << "0";
            differenceInLength--;
        }
    }
    operand1 << integerDigits << decimalDigits;
    operand2 << other.getIntegerDigits() << other.getDecimalDigits();
    unsigned digitsAfterDecimal = 0;
    if (decimalDigits.length() > other.getDecimalDigits().length())
    {
        digitsAfterDecimal = decimalDigits.length();
        differenceInLength = decimalDigits.length() - other.getDecimalDigits().length();
        while (differenceInLength)
        {
            operand2 << "0";
            differenceInLength--;
        }
    }
    else
    {
        digitsAfterDecimal = other.getDecimalDigits().length();
        differenceInLength = other.getDecimalDigits().length() - decimalDigits.length();
        while (differenceInLength)
        {
            operand1 << "0";
            differenceInLength--;
        }
    }
    string productRows[operand2.str().length()];
    int indexA = 0, indexB = 0;
    unsigned carry = 0;
    for (indexB = operand2.str().length() - 1; indexB + 1; indexB--)
    {
        stringstream productRow;
        unsigned rowShift = operand2.str().length() - 1 - indexB;
        while (rowShift)
        {
            productRow << "0";
            rowShift--;
        }
        for (indexA = operand1.str().length() - 1; indexA + 1; indexA--)
        {
            unsigned placeProduct = carry + operand1.str().at(indexA) * operand2.str().at(indexB) - 96;
            carry = (placeProduct - placeProduct % 10) / 10;
            placeProduct %= 10;
            productRow << placeProduct;
        }
        productRow << carry;
        carry = 0;
        productRows[operand2.str().length() - indexB] = productRow.str();
    }
    unsigned index;
    for (index = 0; operand2.str().length() - index; index++)
    {
        BigNumber rowSum(productRows[index], "");
        product = product.sum(rowSum);
    }
    stringstream productIntegerDigits, productDecimalDigits;
    string productDigits = product.getIntegerDigits();
    for (index = productDigits.length() - 1; index + 1; index--)
    {
        if (index < digitsAfterDecimal)
        {
            productDecimalDigits << productDigits.at(index);
            continue;
        }
        productIntegerDigits << productDigits.at(index);
    }
    BigNumber Product(product.isNonNegative(), productIntegerDigits.str(), productDecimalDigits.str());
    Product.trimZeros();
    return Product;
}

BigNumber BigNumber::quotient(BigNumber other)
{
    BigNumber Quotient;
    if (nonNegative xor other.isNonNegative())/*
                                               * A negative divided by a positive
                                               * or a positive divided by a negative
                                               * returns a negative.
                                               */
        Quotient.setNonNegative(false);
    else
        Quotient.setNonNegative(true);
    BigNumber increment("1", "");
    Quotient.setIntegerDigits("1");
    unsigned precisionDestination = 129, precisionFactor = 0;
    while (precisionDestination - precisionFactor)
    {
        bool decrementNecessary = true;
        BigNumber temp = Quotient.product(other);
        while (isGreaterThanOrEqualTo(temp))
        {
            if (Quotient.getDecimalDigits().length() > 1)
                if (Quotient.getDecimalDigits().substr(Quotient.getDecimalDigits().length() - 2, 2) == "99")
                {
                    decrementNecessary = false;
		    Quotient.setDecimalDigits(Quotient.getDecimalDigits() + "0");
		    break;
                }
            Quotient = Quotient.sum(increment);
        }
        if (decrementNecessary)
            Quotient = Quotient.difference(increment);
        decrementNecessary = true;
        if (precisionFactor == 0)
        {
            increment.setIntegerDigits("0");
            increment.setDecimalDigits("1");
        }
        else
            increment.setDecimalDigits("0" + increment.getDecimalDigits());
        precisionFactor++;
    }
    Quotient.trimZeros();
    return Quotient;
}

BigNumber BigNumber::power(int x)
{
    BigNumber one("1", ""), duplicate(nonNegative, integerDigits, decimalDigits);
    if (x < 0)
        return one.quotient(power(-x));
    if (x == 0)
        return one; // Any number raised to the zero power is 1.
    if (x == 1)
        return duplicate; // Any number raised to the first power is itself.
    BigNumber Power("1", "");
    unsigned times = 0;
    while (x - ++times)
        Power = Power.product(duplicate);
    return Power;
}

BigNumber BigNumber::root(int x)
{
    BigNumber one("1", ""), duplicate(nonNegative, integerDigits, decimalDigits);
    if (x < 0)
        return one.quotient(power(-x));
    if (x == 0)
        return one;
    if (x == 1)
        return duplicate;
    BigNumber Root("1", ""), increment("1", "");
    unsigned precisionDestination = 129, precisionFactor = 0;
    while (precisionDestination - precisionFactor)
    {
        bool decrementNecessary = true;
        BigNumber temp = Root.power(x);
        while (isGreaterThanOrEqualTo(temp))
        {
            if (Root.getDecimalDigits().length() > 1)
                if (Root.getDecimalDigits().substr(Root.getDecimalDigits().length() - 2, 2) == "99")
                {
                    decrementNecessary = false;
		    Root.setDecimalDigits(Root.getDecimalDigits() + "0");
		    break;
                }
            Root = Root.sum(increment);
        }
        if (decrementNecessary)
            Root = Root.difference(increment);
        decrementNecessary = true;
        if (precisionFactor == 0)
        {
            increment.setIntegerDigits("0");
            increment.setDecimalDigits("1");
        }
        else
            increment.setDecimalDigits("0" + increment.getDecimalDigits());
        precisionFactor++;
    }
    Root.trimZeros();
    return Root;
}

void BigNumber::trimZeros()
{
    if (integerDigits.length())
        try
        {
            while (integerDigits.at(0) == '0')
                setIntegerDigits(integerDigits.substr(1, integerDigits.length() - 1));
            /*
             * The integer digits should be repeatedly updated until they no longer
             * start with a "0". 
             */
        }
        catch (std::exception outOfBounds)
        {
            /*
             * Deleting all unnecessary zeros may make the string representing
             * the integer digits empty.
             */
        }
    if (decimalDigits.length())
        try
        {
            while (decimalDigits.at(0) == '0')
                setDecimalDigits(decimalDigits.substr(1, decimalDigits.length() - 1));
            /*
             * The decimal digits should be repeatedly updated until they no longer
             * end with a "0".
             */
        }
        catch (std::exception outOfBounds)
        {
            /*
             * Deleting all unnecessary zeros may make the string representing
             * the decimal digits empty.
             */
        }
}

void BigNumber::round(int place)
{
    if (place < 0)
        try
        {
            setDecimalDigits(decimalDigits.substr(0, -place));
        }
        catch (std::exception outOfBounds)
        {
            /*
             * The desired place to round to may round beyond the available
             * digits.
             */
        }
    else
        setIntegerDigits(integerDigits.substr(0, integerDigits.length() - place) + "0");
	setDecimalDigits("");
}

bool BigNumber::hasGreaterAbsoluteValueThan(BigNumber other)
{
    stringstream comparativeA, comparativeB;
    unsigned differenceInLength, totalLength;
    // Both comparatives must be of the same length.
    if (integerDigits.length() > other.getIntegerDigits().length())
    {
        totalLength = integerDigits.length();
        differenceInLength = integerDigits.length() - other.getIntegerDigits().length();
    }
    else
    {
        totalLength = other.getIntegerDigits().length();
        differenceInLength = other.getIntegerDigits().length() - integerDigits.length();
    }
    while (--differenceInLength)
    {
        if (integerDigits.length() > other.getIntegerDigits().length())
            comparativeB << "0";
        else
            comparativeA << "0";
    }
    comparativeA << integerDigits;
    comparativeB << other.getIntegerDigits();
    unsigned comparisonIndex = 0;
    while (totalLength - comparisonIndex)
    {
        if (comparativeA.str().at(comparisonIndex) < comparativeB.str().at(comparisonIndex))
            return false;
        /*
         * If any digit starting from the beginning indices of each number is less
         * than the one it is being compared to, the number will always be less than
         * the one it is being compared to.
         */
        else if (comparativeA.str().at(comparisonIndex) > comparativeB.str().at(comparisonIndex))
            return true;
        /*
         * If any digit starting from the beginning indices of each number is greater
         * than the one it is being compared to, the number will always be greater than
         * the one it is being compared to.
         */
        comparisonIndex++;
    }
    /*
     * If the integer digits of both numbers are equal, their decimal digits
     * must be compared.
     */
    if (other.getDecimalDigits().length() + decimalDigits.length())
    {
        comparativeA.str("");
        comparativeB.str("");
        differenceInLength = 1 + std::abs(integerDigits.length() - other.getIntegerDigits().length());
        comparativeA << decimalDigits;
        comparativeB << other.getDecimalDigits();
        while (--differenceInLength)
        {
            if (decimalDigits.length() > other.getDecimalDigits().length())
                comparativeB << "0";
            else if (decimalDigits.length() < other.getDecimalDigits().length())
                comparativeA << "0";
        }
        BigNumber newComparativeA(comparativeA.str(), ""), newComparativeB(comparativeB.str(), "");
        return newComparativeA.hasGreaterAbsoluteValueThan(newComparativeB);
    }
    return false;
}

bool BigNumber::hasLowerAbsoluteValueThan(BigNumber other)
{
    stringstream comparativeA, comparativeB;
    unsigned differenceInLength, totalLength;
    if (integerDigits.length() > other.getIntegerDigits().length())
    {
        totalLength = integerDigits.length();
        differenceInLength = integerDigits.length() - other.getIntegerDigits().length();
    }
    else
    {
        totalLength = other.getIntegerDigits().length();
        differenceInLength = other.getIntegerDigits().length() - integerDigits.length();
    }
    while (--differenceInLength)
    {
        if (integerDigits.length() > other.getIntegerDigits().length())
            comparativeB << "0";
        else
            comparativeA << "0";
    }
    comparativeA << integerDigits;
    comparativeB << other.getIntegerDigits();
    unsigned comparisonIndex = 0;
    while (totalLength - comparisonIndex)
    {
        if (comparativeA.str().at(comparisonIndex) > comparativeB.str().at(comparisonIndex))
            return false;
        else if (comparativeA.str().at(comparisonIndex) < comparativeB.str().at(comparisonIndex))
            return true;
        comparisonIndex++;
    }
    if (other.getDecimalDigits().length() + decimalDigits.length())
    {
        comparativeA.str("");
        comparativeB.str("");
        differenceInLength = 1 + std::abs(integerDigits.length() - other.getIntegerDigits().length());
        comparativeA << decimalDigits;
        comparativeB << other.getDecimalDigits();
        while (--differenceInLength)
        {
            if (decimalDigits.length() > other.getDecimalDigits().length())
                comparativeB << "0";
            else if (decimalDigits.length() < other.getDecimalDigits().length())
                comparativeA << "0";
        }
        BigNumber newComparativeA(comparativeA.str(), ""), newComparativeB(comparativeB.str(), "");
        return newComparativeA.hasLowerAbsoluteValueThan(newComparativeB);
    }
    return false;
}

bool BigNumber::hasEqualAbsoluteValueTo(BigNumber other)
{
    stringstream comparativeA, comparativeB;
    unsigned differenceInLength, totalLength;
    if (integerDigits.length() > other.getIntegerDigits().length())
    {
        totalLength = integerDigits.length();
        differenceInLength = integerDigits.length() - other.getIntegerDigits().length();
    }
    else
    {
        totalLength = other.getIntegerDigits().length();
        differenceInLength = other.getIntegerDigits().length() - integerDigits.length();
    }
    while (--differenceInLength)
    {
        if (integerDigits.length() > other.getIntegerDigits().length())
            comparativeB << "0";
        else
            comparativeA << "0";
    }
    comparativeA << integerDigits;
    comparativeB << other.getIntegerDigits();
    unsigned comparisonIndex = 0;
    while (totalLength - comparisonIndex)
    {
        if (not(comparativeA.str().at(comparisonIndex) == comparativeB.str().at(comparisonIndex)))
            return false;
        /*
         * If any digits of any two numbers at the same digits place are not equal,
         * the numbers must not have equal absolute value.
         */
        comparisonIndex++;
    }
    if (other.getDecimalDigits().length() + decimalDigits.length())
    {
        comparativeA.str("");
        comparativeB.str("");
        differenceInLength = 1 + std::abs(integerDigits.length() - other.getIntegerDigits().length());
        comparativeA << decimalDigits;
        comparativeB << other.getDecimalDigits();
        while (--differenceInLength)
        {
            if (decimalDigits.length() > other.getDecimalDigits().length())
                comparativeB << "0";
            else if (decimalDigits.length() < other.getDecimalDigits().length())
                comparativeA << "0";
        }
        BigNumber newComparativeA(comparativeA.str(), ""), newComparativeB(comparativeB.str(), "");
        return newComparativeA.hasEqualAbsoluteValueTo(newComparativeB);
    }
    return true;
}

bool BigNumber::isGreaterThan(BigNumber other)
{
    return (hasGreaterAbsoluteValueThan(other) xor (not nonNegative));
    /*
     * If a positive number has a greater absolute value than another number, it 
     * must be greater than it. On the other hand, if a negative number has a 
     * greater absolute value than another number, is must be less than it.
     */
}

bool BigNumber::isLessThan(BigNumber other)
{
    return (hasLowerAbsoluteValueThan(other) xor (not nonNegative));
    /*
     * If a positive number has a lower absolute value than another number, it 
     * must be less than it. On the other hand, if a negative number has a lower
     * absolute value than another number, is must be greater than it.
     */
}

bool BigNumber::isEqualTo(BigNumber other)
{
    return (nonNegative == other.isNonNegative()) and hasEqualAbsoluteValueTo(other);
    /*
     * If two numbers have the same absolute value, they must be either both 
     * negative or nonnegative to be equal.
     */
}

bool BigNumber::isGreaterThanOrEqualTo(BigNumber other)
{
    return isEqualTo(other) or isGreaterThan(other);
}

bool BigNumber::isLessThanOrEqualTo(BigNumber other)
{
    return isEqualTo(other) or isLessThan(other);
}

bool BigNumber::isNonNegative()
{
    return nonNegative;
}

string BigNumber::getIntegerDigits()
{
    return integerDigits;
}

string BigNumber::getDecimalDigits()
{
    return decimalDigits;
}

void BigNumber::setNonNegative(bool nonNegative)
{
    this->nonNegative = nonNegative;
}

void BigNumber::setIntegerDigits(string integerDigits)
{
    this->integerDigits = integerDigits;
}

void BigNumber::setDecimalDigits(string decimalDigits)
{
    this->decimalDigits = decimalDigits;
}
