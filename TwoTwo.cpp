#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int strength(int, int);

bool isPowerOfTwo(int);

int *A;

int main(void) {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int t;
    do
        cin >> t;
    while (t < 1 || t > 100);
    while (t) {
        string numbers;
        cin >> numbers;
        A = new int[numbers.length()];
        for (int s = 0; s < numbers.length(); s++) 
            *(A + s) = numbers.at(s) - 48;
        int strengthsPowersOfTwo = 0;
        for (int i = 0; i < numbers.length(); i++)
            for (int j = i; j < numbers.length(); j++) 
                if (isPowerOfTwo(strength(i, j)))
                    strengthsPowersOfTwo++;
        cout << strengthsPowersOfTwo << endl;
        delete A;
        t--;
    }
    return 0;
}

int strength(int i, int j) {
    if (!*(A + i))
        return 0;
    int value = 0;
    for (int k = i; j - (k - 1); k++)
        value = value * 10 + *(A + k);
    return value;
}

bool isPowerOfTwo(int d) {
    int power = 0;
    while (pow(2, power) < d && power < 800)
        power++;
    return pow(2, power) == d;
}
