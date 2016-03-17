#This program uses the Euclidean Algorithm to find the greatest common divisor of two natural numbers.
def computeGreastestCommonDivisor(numberA, numberB):
  if (numberB > numberA) then: #For this recursive algorithm to work, numberA must be greater than numberB.
    return computeGreatestCommonDivisor(numberB, numberA)
  end
  if (numberA % numberB == 0) then:
    return numberB
  return computeGreatestCommonDivisor(numberB, numberA % numberB)
  end
end

#Prompt the user to enter the first number.
puts("Please enter the first number.")
numberA = gets
#Prompt the user to enter the second number.
puts("Please enter the second number.")
numberB = gets
#Call the method to find the greatest common divisor of these two methods
gcd = computeGreatestCommonDivisor(numberA, numberB)
print("The greatest common divisor of ", numberA, " and ", numberB, " is ", gcd, ".")
