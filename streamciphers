//
//  main.cpp
//  project2
//
//  Created by Michelle Wong on 2019-11-06.
//  Copyright © 2019 Michelle Wong. All rights reserved.
//

#include <iostream>
#include<cmath>

char *encode(char *plaintext, unsigned long key);
char *decode (char *ciphertext, unsigned long key);


int main();


int main() {
    
}

//find length of text
std::size_t string_length(char *s_str )
{
    
    for (std::size_t k{0}; true; ++k)
    {
        if (s_str[k] == '\0' )
        {
            return k;
        }
    }
}


char *encode(char *plaintext, unsigned long key)
{
    
    std::size_t stringLength {string_length(plaintext)};
    
    int nullbytes = stringLength%4;
    std::size_t oldLength = stringLength;
    
    if (stringLength%4 !=0)
    {
        stringLength = stringLength + (4-nullbytes);
    }
    
    char *a_plaintext = new char[stringLength];
    
    for (int i = 0 ; i < stringLength; i++)
    {
        a_plaintext[i] = plaintext[i];
    }
    
    for (std::size_t i = oldLength; i < stringLength+(4-nullbytes); i++)
    {
        a_plaintext[i] = '\0';
    }
    
    unsigned long dividend = key;
    int key_arr[64]{};
    unsigned char S[256]{};
    
    for (std::size_t i{0}; i<64; i++)
    {
        key_arr[i]= (dividend%2);
        dividend = (dividend/2);
        
    }
    
    for (int i = 0; i < 256 ; ++i)
    {
        S[i] = i;
        
    }
    
    unsigned int j{0};
    unsigned int i{0};
    int temp{0};
    int k{0};
    
    for (int a = 0; a < 256; ++a)
    {
        k = i%64;
        j = (j+ S[i] + key_arr[k])%256;
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
        
        i = (i+1) % 256;
        
    }
    
    //find r value
    
    int r{0};
    int r_value{0};
    
    
    for (int a = 0 ; a < stringLength; ++a)
    {
        i = (i+1)%256;
        j = (j + S[i])%256;
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
        r = (S[i] + S[j])%256;
        r_value = S[r];
        a_plaintext[a] = a_plaintext[a]^r_value;
    }
    
    std::size_t numberOfBinary = stringLength/4 ;
    char *printencode = new char[numberOfBinary*5+1];
    
    int count{0};
    
    /////// ascii armour ///////////
    
    for (int a = 0 ; a < numberOfBinary; a++)
    {
        //bit shift to add bytes together
        unsigned int result{0};
        unsigned int num_1 = static_cast<unsigned char>(a_plaintext[4*a]) << 24;
        unsigned int num_2 = static_cast<unsigned char>(a_plaintext[4*a+1]) << 16;
        unsigned int num_3 = static_cast<unsigned char>(a_plaintext[4*a+2]) << 8;
        unsigned int num_4 = static_cast<unsigned char>(a_plaintext[4*a+3]);
        
        result = num_1+num_2+num_3+num_4;
        
        int get_numbers[numberOfBinary];
        
        //get the five numbers from result
        for(int i = 0; i < 5; i++)
        {
            get_numbers[i] = (result%85);
            result = result/85;
            
        }
        
        //reverse order
        for (int i = 4; i >=0; i--)
        {
            printencode[count] =  char(get_numbers[i] +33);
            count = count+1;
        }
        
    }
    
    printencode[numberOfBinary*5+1] = '\0';
    
    return printencode;
    
}

char *decode (char *ciphertext, unsigned long key)
{
    //undo ascii armour
    std::size_t stringLength = string_length(ciphertext);
    std::size_t numberOfGroups = stringLength/5;
    char *printdecode = new char[(numberOfGroups*4)+1];
    unsigned int *bytes = new unsigned int[numberOfGroups];

    for (int i = 0 ; i < numberOfGroups; i ++)
    {
        unsigned int num1 = ciphertext[5*i+4] - 33;
        unsigned int num2 = ciphertext[5*i+3] - 33;
        unsigned int num3 = ciphertext[5*i+2] - 33;
        unsigned int num4 = ciphertext[5*i+1] - 33;
        unsigned int num5 = ciphertext[5*i] - 33;
        
        unsigned int result{0};
        result = num1*pow(85, 0) + num2*pow(85, 1) + num3*pow(85, 2) + num4*pow(85, 3) + num5*pow(85, 4);
        bytes[i] = result;
        
    }

    
    for(int i = 0 ; i < numberOfGroups; i++)
    {
        unsigned int getNumbers = bytes[i];
        printdecode[0 + 4*i] = static_cast<unsigned char> (getNumbers >> 24);
        printdecode[1 + 4*i] = static_cast<unsigned char> ((getNumbers << 8) >>24);
        printdecode[2 + 4*i] =static_cast<unsigned char> ((getNumbers <<16)>>24);
        printdecode[3 + 4*i] = static_cast<unsigned char> ((getNumbers << 24)>>24);
        
    }
    unsigned long dividend = key;
    int key_arr[64]{};
    unsigned char S[256]{};
    
    for (std::size_t i{0}; i<64; i++)
    {
        key_arr[i]= (dividend%2);
        dividend = (dividend/2);
        
    }
    
    for (int i = 0; i < 256 ; ++i)
    {
        S[i] = i;
        
    }
    
    unsigned int j{0};
    unsigned int i{0};
    int temp{0};
    int k{0};
    
    for (int a = 0; a < 256; ++a)
    {
        k = i%64;
        j = (j+ S[i] + key_arr[k])%256;
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
        i = (i+1) % 256;
    }
    
    //find r value
    int r{0};
    int r_value{0};
    
    
    for (int a = 0 ; a < stringLength; ++a)
    {
        i = (i+1)%256;
        j = (j + S[i])%256;
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
        r = (S[i] + S[j])%256;
        r_value = S[r];
        printdecode[a] = printdecode[a]^r_value;
    }
    
    printdecode[numberOfGroups*4] = '\0';
    
    return printdecode;
}
