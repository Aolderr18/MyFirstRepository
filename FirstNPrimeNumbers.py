def isPrime(naturalNumber, listOfPrimes):#Check to see if any natural number is prime.
  for prime in listOfPrimes:
    limit = naturalNumber / prime
    if naturalNumber % prime == 0:
      return False
    if prime > limit:
      return True#If the prime number list is iterated through past the limit, the natural number must be composite.

listOfPrimes = [2]#The first prime number is 2.
naturalNumber = int(input('Please enter any natural number.'))
int trial = 1
int test = 3
print(2)#Print the first prime number.
while trial <= naturalNumber:
  if isPrime(test, listOfPrimes):
    listOfPrimes.append(test)
    print(test)
    trial = trial + 1
  test = test + 1
