'''
This program prompts the user to enter a decimal(base 10) number
and then converts them to base 2, base 3, base 4, base 5, base 6, 
base 7, base 8, base 9, and base 16.

Most of these methods user a recursive algorithm.
'''
def decimalToBinary(decimal):
    if decimal > 0:
        power = 0
        while 2**power <= (decimal / 2):
            power += 1
        return 10**power + decimalToBinary(decimal - 2**power)
    return 0

def decimalToTernary(decimal):
    if decimal > 0:
        power = 0
        while 3**power <= (decimal / 3):
            power += 1
        return 10**power + decimalToTernary(decimal - 3**power)
    return 0

def decimaltoQuaternary(decimal):
    if decimal > 0:
        power = 0
        while 4**power <= (decimal / 4):
            power += 1
        return 10**power + decimalToQuaternary(decimal - 4**power)
def decimalToPental(decimal): 
    if decimal > 0:
        power = 0
        while 5**power <= (decimal / 5):
            power += 1
        return 10**power + decimalToPental(decimal - 5**power)
    return 0

def decimalToHexal(decimal):
    if decimal > 0:
        power = 0
        while 6**power <= (decimal / 6):
            power += 1
        return 10**power + decimalToHexal(decimal - 6**power)
    return 0

def decimalToSeptal(decimal):
    if decimal > 0:
        power = 0
        while 7**power <= (decimal / 7):
            power += 1
        return 10**power + decimalToSeptal(decimal - 7**power)
    return 0
        
def decimalToOctal(decimal):
    if decimal > 0:
        power = 0
        while 8**power <= (decimal / 8):
            power += 1
        return 10**power + decimalToOctal(decimal - 8**power)
    return 0

def decimalToNonal(decimal):
    if decimal > 0:
        power = 0
        while 9**power <= (decimal / 9):
            power += 1
        return 10**power + decimalToNonal(decimal - 9**power)
    return 0

def nonDecimalToDecimal(nonDecimal, base):
    if nonDecimal > 0:
        power = 0
        while 10**power <= (nonDecimal / 10):
            power += 1
        return base**power + nonDecimalToDecimal((nonDecimal - 10**power), 2)
    return 0

def decimalToHexadecimal(decimal, decimalIsNegative):
    hexDigitGuide = {10: 'A', 11: 'B', 12: 'C', 13: 'D', 14: 'E', 15: 'F'}
    hexResult = ''
    if decimalIsNegative:
        hexResult += '-'
    binaryForm = decimalToBinary(decimal)
    digits = 0
    while 10**digits <= binaryForm:
        digits += 1
    if digits % 4 == 0:
        section = digits / 4
        while section > 0:
            sectionBit = int((binaryForm / 10**((section - 1) * 4)))
            sectionDigit = nonDecimalToDecimal(sectionBit, 2)
            if decimalIsNegative:
                sectionDigit *= -1
            binaryForm = int(binaryForm % 10**((section - 1) * 4))
            section -= 1
            if sectionDigit < 10:
                hexResult += str(sectionDigit)
            else:
                hexResult += str(hexDigitGuide[sectionDigit])
    else:
        section = 1 + int(digits / 4)
        initialSection = section
        while section > 0:
            sectionBit = int((binaryForm / 10**((section - 1) * 4)))
            sectionDigit = nonDecimalToDecimal(sectionBit, 2)
            binaryForm = int(binaryForm % 10**((section - 1) * 4))
            section -= 1
            if sectionDigit < 10:
                hexResult += str(sectionDigit)
            else:
                hexResult += str(hexDigitGuide[sectionDigit])
    return hexResult

decimalIsNegative = False
decimal = int(input('Please enter a positive integer in base 10: '))
if decimal < 0:
    decimalIsNegative = True
    decimal *= -1
#For the following functions to work, all of their parameters must be positive values.
binaryForm = decimalToBinary(decimal)
ternaryForm = decimalToTernary(decimal)
quaternaryForm = decimalToQuaternary(decimal)
pentalForm = decimalToPental(decimal)
hexalForm = decimalToHexal(decimal)
septalForm = decimalToSeptal(decimal)
octalForm = decimalToOctal(decimal)
hexadecimalForm = decimalToHexadecimal(decimal, decimalIsNegative)
if decimalIsNegative:
    decimal *= -1
    binaryForm *= -1
    ternaryForm *= -1
    quaternaryForm *= -1
    pentalForm *= -1
    hexalForm *= -1
    septalForm *= -1
    octalForm *= -1
print()
print(decimal, ' in binary form is : ', binaryForm, '.')
print(decimal, ' in ternary form is : ', ternaryForm, '.')
print(decimal, ' in quaternary form is : ', quaternaryForm, '.')
print(decimal, ' in pental form is : ', pentalForm, '.')
print(decimal, ' in hexal form is : ', hexalForm, '.')
print(decimal, ' in septal form is : ', septalForm, '.')
print(decimal, ' in octal form is : 0o', octalForm, '.')
print(decimal, ' in hexadecimal form is : 0x', hexadecimalForm, '.')
