'''
    This program prompts the user to enter a natural number and then, using
    the fundamental theorem of arithmetic, it computes the prime factors of
    that natural number and displays them.
    
    The fundamental theorem of arithmetic states that any integer greater than 
    1 is either a prime number itself or the product of prime numbers.
'''
#Check to see if a number is prime.
def isPrime(divisor, possiblePrimes):
    for number in possiblePrimes:
        if divisor % number is 0:
            return False
    return divisor is not 1

#The possible prime factors of a natural number must be less than or equal to that natural number.
def generatePossiblePrimes(naturalNumber):
    possiblePrimes = [2]
    i = 3
    while i <= naturalNumber:
        if isPrime(i, possiblePrimes):
            possiblePrimes.append(i)
        i += 1
    return possiblePrimes

def generateListOfPrimeFactors(naturalNumber):
    possiblePrimes = generatePossiblePrimes(naturalNumber)
    listOfPrimeFactors = []
    remainder = naturalNumber
    for element in possiblePrimes:
        power = 0
        while remainder % element**(power + 1) is 0:
            power += 1
        if power > 0:
            primeFactor = str(element) + '^' + str(power)
            listOfPrimeFactors.append(primeFactor)
    return listOfPrimeFactors

#Display the list
def displayList(userList):
    for element in userList:
        print(element)
        
naturalNumber = int(input('Enter a natural number: '))
listOfPrimeFactors = generateListOfPrimeFactors(naturalNumber)
print(naturalNumber, ' written as the product of primes is: ')
displayList(listOfPrimeFactors)
