#ifndef TRINITY_H
#define TRINITY_H

#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <algorithm>    // std::reverse
/*
 * Imitating Neomm pack and unpack of navantia
 *
 *
 */

class Trinity
{
public:
    Trinity();

    static void pack(const int variable,
                     std::vector<unsigned char> &buffer,
                     const uint8_t numberBits);

    static void pack(const long variable,
                     std::vector<unsigned char> &buffer,
                     const uint8_t numberBits);

    static void pack(const float variable,
                     std::vector<unsigned char> &buffer,
                     const uint8_t numberBits,
                     const uint8_t num_bit_integer,
                     const uint8_t num_bit_decimal);
                
    static void pack(const double variable, 
                     std::vector<unsigned char> &buffer, 
                     const uint8_t numberBits, 
                     const uint8_t num_bit_integer, 
                     const uint8_t num_bit_decimal);

    
    static void unpack(int &variable, //unpack int
                       const std::vector<unsigned char> buffer,
                       const uint word,
                       const int num_bit_word,
                       const int ini_bit,
                       const int  final_bit,
                       const bool withsign);

    static void unpack(long &variable, //unpack long
                       const std::vector<unsigned char> buffer,
                       const uint word,
                       const int num_bit_word,
                       const int ini_bit,
                       const int  final_bit,
                       const bool withsign);

    static void unpack(float &variable, //unpack float
                       std::vector<unsigned char> buffer,
                       const uint word,
                       const uint8_t num_bit_word,
                       const uint8_t ini_bit,
                       const uint8_t  final_bit,
                       const bool withsign,
                       const uint8_t num_bit_integer,
                       const uint8_t num_bit_decimal);

    static void unpack(double &variable, //unpack float
                       std::vector<unsigned char> buffer,
                       const uint word,
                       const uint8_t num_bit_word,
                       const uint8_t ini_bit,
                       const uint8_t  final_bit,
                       const bool withsign,
                       const uint8_t num_bit_integer,
                       const uint8_t num_bit_decimal);

private:
    template <class T>
    static std::string transformIntTobinary( const T dec )
    {
         //std::cout << "dec " <<dec << std::endl;
        std::string binary_number = "";
        T decimal = dec;

        T division_result, resto;

        while (decimal >=2)
        {   
            resto = decimal % 2;
            //std::cout << resto << std::endl;
            binary_number.append(std::to_string(resto));
            decimal = decimal / 2;
        }
        binary_number.append(std::to_string(1));

        std::reverse(binary_number.begin(), binary_number.end());
        //std::cout << binary_number << std::endl;
        return binary_number;
    }
    template <class T>
    static T transformBinaryToInt( const std::string binary )
    {
        T decimalNumber = 0;
        int i_pow = 0;
        for (int i=binary.size()-1; i>=0; i--)
        {
            int number_binary = binary[i]-48;
            decimalNumber = decimalNumber + number_binary*std::pow(2,i_pow);
            i_pow++;
        }
        return decimalNumber;
    }

    static std::string byteToBinary(unsigned char byte);

    template <class T>
    static void convertIntToBuffer(const T variable, std::vector<unsigned char> &buffer, const uint8_t numberBits, const bool withsign)
    {
        std::string variable_base2_subset = "";
        std::string variableBase2 = transformIntTobinary((T)std::abs(variable));

        while (variableBase2.size() != numberBits)
        {
            variableBase2 = variableBase2.insert(0,"0");
        }
        if(withsign)
        {
            variableBase2[0] = '1' ;
        }
        //std::cout << "variableBase2 " << variableBase2 << std::endl;
        for (int i=0; i<variableBase2.size();i=i+8)
        {
            variable_base2_subset.clear();
            variable_base2_subset = variableBase2.substr(i,8);
            int value = transformBinaryToInt<int>(variable_base2_subset);
            unsigned char value_char = value;

            buffer.push_back(value_char);
        }
    }
    static void convertDecimalToBuffer(const float variableDecimal, std::vector<unsigned char> &buffer, const uint8_t num_bit_decimal);

    template <class T>
    static std::string transformDecimalTobinary(const T variableDecimal, int num_bits)
    {
        std::string binary_number = "";
        int negative_pow = -1;
        double two_double = 2.0;
        T result = variableDecimal;
        while(binary_number.size()<num_bits)
        {
            T power = pow(two_double, negative_pow);
            if(power >= result)
            {
                negative_pow--;
                binary_number.append("0");
            }
            else
            {
                negative_pow--;
                result = result - power;
                binary_number.append("1");
            }
        }
        return binary_number;
    }
    
    template <class T>
    static T transformBinaryToDecimal( const std::string binary )
    {
    T decimalNumber = 0;
    T two = 2.0;
    int i_pow = -1;
    for (int i=0; i<binary.size(); i++)
    {
        int number_binary = binary[i]-48;
        decimalNumber = decimalNumber + number_binary*std::pow(two,i_pow);
        i_pow--;
    }
    return decimalNumber;
}
    static void bufferToInteger(const std::vector<unsigned char> &buffer, int &variable, const bool withsign);
    
};
#endif // TRINITY_H
