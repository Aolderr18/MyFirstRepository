'''
The purpose of this program is to read from a text file containing an essay. The program
counts how many times each word is used and finds the most frequently used word. It also
tells the user if a word was used twice or more in a row.
'''

validCharacters = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '.', ',', '?', '!', '"', '\'', '\\', '/', '_', '-', '+', '=', '@', '#', '$', '%', '^', '&', '&', '*', '(', ')']

def similarCharacters(characterA, characterB):
    comparativeA = validCharacters.index(characterA)
    comparativeB = validCharacters.index(characterB)
    #For this algorithm to work, the index of characterA should be greater than or equal to the index of characterB
    if comparativeB > comparativeA:
        return similarCharacters(characterB, characterA)
    return comparativeA is comparativeB or comparativeA % 26 is comparativeB and comparativeA < 52 and comparativeB < 52

def similarWords(wordA, wordB):
    #Punctuation must be excluded before comparing two words.
    wordA = lettersOnly(wordA)
    wordB = lettersOnly(wordB)
    if not len(wordA) == len(wordB):
        return False
    #Similar words must contain all of the same characters.
    for character in wordA:
        if not similarCharacters(character, wordB[wordA.index(character)]):
            return False
    return True

#The following function excludes any punctuation found in a word.
def lettersOnly(word):
    lettersOnly = ''
    for character in word:
        if validCharacters.index(character) < 52:
            lettersOnly = lettersOnly + character
    return lettersOnly

def readNextCharacter(readOnlyFile):
    nextCharacter = readOnlyFile.read(1)
    assert nextCharacter in validCharacters
    return nextCharacter

def readNextWord(readOnlyFile):
    nextWord = ''
    while True:
        try:
            nextWord = nextWord + readNextCharacter(readOnlyFile)
        except:
            assert len(nextWord) > 0
            return nextWord

def putInAllLowerCase(words):
    wordsInLowerCaseForm = []
    for word in words:
        word = lettersOnly(word)
        wordInLowerCaseForm = ''
        for character in word:
            wordInLowerCaseForm = wordInLowerCaseForm + validCharacters[validCharacters.index(character) % 26 + 26]
        wordsInLowerCaseForm.append(wordInLowerCaseForm)
    return wordsInLowerCaseForm

def findFavoriteWord(wordFrequency):
    favoriteWord = ''
    highestRank = 1
    for key in wordFrequency:
        if wordFrequency[key] > highestRank:
            favoriteWord = key
            highestRank = wordFrequency[key]
    if favoriteWord is 'i':
        favoriteWord = 'I'
    return favoriteWord
    
def wordFrequency(words):
    words = putInAllLowerCase(words)
    wordFrequency = {}
    examinedWords = []
    i = len(words) - 1
    while i >= 0:
        if not words[i] in examinedWords:
            examinedWords.append(words[i])
            wordFrequency.update({words[i]: 1})
            n = 0
            while n < i:
                if similarWords(words[n], words[i]):
                    wordFrequency[words[i]] = wordFrequency[words[i]] + 1
                n = n + 1
        i = i - 1
    return wordFrequency
#The following function determines if any word is used twice or more in a row.
def findRepetitions(wordFrequency, words):
    words = putInAllLowerCase(words)
    repeatedWords = []
    i = len(words) - 1
    while i >= 0:
        if not words[i] in repeatedWords:
            occurences = 1
            n = i - 1
            while n > i - wordFrequency[words[i]] and n >= 0:
                if similarWords(words[i], words[n]):
                    occurences = occurences + 1
                    repeatedWords.append(words[i])
                else:
                    break
                n = n - 1
            if occurences > 1:
                print(words[i], 'was used ', occurences, ' times in a row!')
        i = i - 1
        
def readFile(readOnlyFile):
    words = []
    spaceCount = 0
    while spaceCount < 30:
        try:
            words.append(readNextWord(readOnlyFile))
            spaceCount = 0
        except:
            spaceCount = spaceCount + 1
    return words

#Open the file.
readOnlyFile = open('userFile.txt', 'r')
words = readFile(readOnlyFile)
wordFrequency = wordFrequency(words)
for key in wordFrequency:
    if wordFrequency[key] == 1:
        word = key
        if key is 'i':
            word = 'I'
        print('\'', word, '\'', ' was used ', wordFrequency[key], ' time.')
    else:
        word = key
        if key is 'i':
            word = 'I'
        print('\'', word, '\'', ' was used ', wordFrequency[key], ' times.')
print('\nThere are ', len(words), ' words in the document.')
favoriteWord = findFavoriteWord(wordFrequency)
print('\nThe favorite word is', favoriteWord, '.\n')
findRepetitions(wordFrequency, words)
