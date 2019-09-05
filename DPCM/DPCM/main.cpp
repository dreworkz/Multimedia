//
//  main.cpp
//  assn3
//
//  Created by Andrew Lee on 20/8/19.
//  Copyright © 2019 Andrew Lee. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <stdio.h>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <cmath>
#include <list>

using namespace std;

vector<int> encoded;
vector<int>::iterator encodedIt;

vector<int> decoded;
vector<int>::iterator decodedIt;

vector<double> SNR;
vector<double>::iterator SNRIt;


void decode (){
    
    vector<string> numInput;
    vector<string>::iterator numIt;
    
    vector<int> numbers;
    vector<int>::iterator numbersPnt;
    
    vector<int> found;
    vector<int>::iterator foundPnt;
    
    
    string seq;
    string temp;
    
    cin.clear();
    cin.ignore();
    
    // uncomment later
    cout << "Enter Sequence: ";
    getline(cin, seq);
    
    //comment later
    //seq = "130 24 -8 56";
    
    stringstream check1(seq);
    
    while( getline( check1, temp, ' ' ) )
    {
        numInput.push_back(temp);
    }
    
    
    // Accessing the elements using iterators
    numIt = numInput.begin();
    
    
    while(numIt != numInput.end())
    {
        //convert string (numInput vector) to int (numbers vector)
        string t = *numIt;
        int n = atoi (t.c_str() );
        numbers.push_back(n);
        
        numIt++;
    }
    
    cout << endl;
    cout << "\nDecoded Sequence as follows: ";
    
    
    numbersPnt = numbers.begin();
    foundPnt = found.begin();
    
    int fPrimeOne, fPrimeTwo;
    int fPrime = 0;
    int i = 0;
    
    while(numbersPnt != numbers.end())
    {
        
        //if number is not first number
        if (numbersPnt == numbers.begin()){
            //first number below
            fPrimeOne = *(numbersPnt);
            fPrimeTwo = *(numbersPnt);
            
        }else{
            //if number is second number
            
            if((numbersPnt -1) == (numbers.begin())){
                //second number below
                fPrimeOne = *(numbersPnt-1);
                fPrimeTwo = *(numbersPnt-1);
                
                
            }else{
                //other number below
                fPrimeOne = found[i];
                fPrimeTwo = found[i+1];
                
                i++;
            }
            
        }
        
        
        double fHat = trunc(0.5 * (fPrimeOne + fPrimeTwo) );
        
        int f = *numbersPnt;
        
        if (numbersPnt == numbers.begin()){
            //e = f;
            fPrime = f;
            found.push_back(fPrime);
            
        }else{
            
            fPrime = fHat + f;
            found.push_back(fPrime);
        }
        
        
        decoded.push_back(fPrime);
        
        cout << fPrime <<" ";
        
        numbersPnt++;
    }
    
    cout << "\n";
    
    numbersPnt = numbers.begin();
    numbersPnt++;
    decodedIt = decoded.begin();
    decodedIt++;
    float SNRcal;
    double totalSNR = 0.0;
    int numberOfEntries = 0;
    
    while (decodedIt != decoded.end()){
        
        double first = (*numbersPnt * 1.0);
        
        first = pow(first, 2.0);
        
        double second = (*decodedIt * 1.0);
        
        second = pow(second, 2.0);
        
        double divide = (first/second) * 1.0;
        
        SNRcal = 10.0*(log10(divide));
        
        totalSNR += SNRcal;
        
        numberOfEntries++;
        numbersPnt++;
        decodedIt++;
    }
    
    double SSNR = ( totalSNR / (numberOfEntries * 1.0) );
    
    cout << "SNR: " << SSNR << " (dB)\n";
}


void encode (){
    
    vector<string> numInput;
    vector<string>::iterator numIt;
    
    vector<int> numbers;
    vector<int>::iterator numbersPnt;
    
    //vector<int> EnNum;
    //vector<int>::iterator EnNumPt;
    
    string seq;
    string temp;
    
    // uncomment later
    cin.clear();
    cin.ignore();
    
    cout << "Enter Sequence: ";
    getline(cin, seq);
    
    //comment later
    //seq = "130 150 140 200 230";
    
    stringstream check1(seq);
    
    while( getline( check1, temp, ' ' ) )
    {
        numInput.push_back(temp);
    }
    
    
    // Accessing the elements using iterators
    numIt = numInput.begin();
    
    while(numIt != numInput.end())
    {
        //convert string (numInput vector) to int (numbers vector)
        string t = *numIt;
        int n = atoi (t.c_str() );
        numbers.push_back(n);
        
        numIt++;
    }
    
    cout << endl;
    cout << "\nEncoded Sequence as follows: ";
    
    
    numbersPnt = numbers.begin();
    
    int fPrimeOne, fPrimeTwo;
    
    while(numbersPnt != numbers.end())
    {
        //cout << *numbersPnt << " ";
        
        //if number is not first number
        if (numbersPnt == numbers.begin()){
            //first number below
            fPrimeOne = *(numbersPnt);
            fPrimeTwo = *(numbersPnt);
            
        }else{
            //if number is second number
            ///*
            if((numbersPnt -1) == (numbers.begin())){
                //second number below
                fPrimeOne = *(numbersPnt-1);
                fPrimeTwo = *(numbersPnt-1);
            }else{
                //other number below
                fPrimeOne = *(numbersPnt -1);
                fPrimeTwo = *(numbersPnt -2);
            }
            //*/
            //fPrimeOne = *(numbersPnt -1);
            //fPrimeTwo = *(numbersPnt -2);
        }
        
        double fHat = trunc(0.5 * (fPrimeOne + fPrimeTwo) );
        
        int f = *numbersPnt;
        int e;
        double ePrime;
        
        
        if (numbersPnt == numbers.begin()){
            //e = f;
            ePrime = f;
            
        }else{
            e = f - fHat;
            ePrime = ( 16 * (trunc((255+e) / 16)) ) - 256 +8;
        }
        
        
        
        
        //int fPrime = fHat + ePrime;
        
        cout << ePrime <<" ";
        
        encoded.push_back(ePrime);
        
        numbersPnt++;
    }
    
    cout << "\n";
    
    numbersPnt = numbers.begin();
    numbersPnt++;
    encodedIt = encoded.begin();
    encodedIt++;
    float SNRcal;
    double totalSNR = 0.0;
    int numberOfEntries = 0;
    
    
    while (encodedIt != encoded.end()){
        
        double first = (*numbersPnt * 1.0);
        
        first = pow(first, 2.0);
        
        double second = (*encodedIt * 1.0);
        
        second = pow(second, 2.0);
        
        double divide = (first/second) * 1.0;
        
        SNRcal = 10.0*(log10(divide));
        
        totalSNR += SNRcal;
        
        numberOfEntries++;
        numbersPnt++;
        encodedIt++;
    }
    
    double SSNR = ( totalSNR / (numberOfEntries * 1.0) );
    
    cout << "SNR: " << SSNR << " (dB)\n";
}



int main() {
    // insert code here...
    
    char userChoice;
    
    cout << "\nWelcome to DPCM\n" << endl;
    
    cout << "1) Encode Sequence" << endl;
    cout << "2) Decode Sequence" << endl;
    cout << "3) Help" << endl;
    cout << "Q) Quit" << endl;
    
    cout << "\nUser Choice: ";
    cin >> userChoice;
    
    switch (userChoice) {
        case '1':
            encoded.clear();
            encode();
            main();
            break;
            
        case '2':
            decoded.clear();
            decode();
            main();
            break;
            
        case ('3'):
            cout << "\n--- Help Menu ---" << endl;
            cout << "Press (1) to Encode" << endl;
            cout << "Press (2) to Decode" << endl;
            cout << "Press (Q) to Quit Program" << endl;
            cout << "SNR displays accordingly\n" << endl;
            
            break;
            
        case ('q'):
            cout << "\nShutting down…" << endl;
            return 0;
            break;
            
        case ('Q'):
            cout << "\nShutting down…" << endl;
            return 0;
            break;
            
        default:
            cout << "Input not recognised, try again.";
            main();
    }
    
    
    
    
    
    
    return 0;
}
