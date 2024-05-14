// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// ---------------------------------------------------
// Name : Alfred Lee
// ID: 1617346
// CMPUT 275 , Winter 2021
//
// WE #1: Twin Primes
// ---------------------------------------------------

#include <iostream>
#include <math.h>
using namespace std;

/*
    Description : check if a number is prime
    Arguments :
        n (int): the number to check
    Returns :
        bool: True if prime, false otherwise
*/
bool isPrime(int n) {
    // Start from 2 and loop until we pass sqrt(n)
    for (int i = 2; i <= sqrt(n); i++) {
        // use float division to avoid rounding.
        int result = n % i;

        // if 
        if (result == 0) {
            return false;
        }
    }

    return true;
}

/*
    Description : print k lines of prime pairs
    Arguments :
        k (int): the number of lines to print
    Returns :
        N/A
*/
void twinPrimes(int k) {
    // We start at 3 since 1,2 don't need to be calculated
    int start = 3;

    // loop for k lines
    for (int i = 0; i < k; i++) {
        // loop until we find a pair of primes
        while (true) {
            // if we find a pair of primes output them and exit while loop
            if (isPrime(start) && isPrime(start + 2)) {
                cout << start << ' ' << start + 2 << endl;

                start += 1;
                break;
            }

            start += 1;
        }
    }
}

int main() {
    // Initialize Variables
    char letter;
    int number;
       
    while(true){
        // Get User inputs
        cin >> letter;
        cin >> number;

        // Dependant on the input either call isPrime or twinPrimes function
        if (letter == 'p') {
            // output prime or not prime depending on isPrime return
            isPrime(number) ? cout << "prime" << endl : cout << "not prime" << endl;
        }
        else if (letter == 't') {
            twinPrimes(number);
        }
    }
}