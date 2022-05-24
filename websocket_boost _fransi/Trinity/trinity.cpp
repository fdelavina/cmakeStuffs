#include "trinity.h"
#include <string>
#include <sstream>
#include <stdio.h>
#include <iostream>

#include <bitset>
Trinity::Trinity()
{

}

void Trinity::pack(const int variable,
                     std::vector<unsigned char> &buffer,
                     const uint8_t numberBits)
{
    bool withsign = false;
    if (variable < 0) withsign = true;
    convertIntToBuffer<int>(variable, buffer, numberBits, withsign);
}

void Trinity::pack(const long variable,
                     std::vector<unsigned char> &buffer,
                     const uint8_t numberBits)
{
    bool withsign = false;
    if (variable < 0) withsign = true;
    convertIntToBuffer<long>(variable, buffer, numberBits, withsign);
}

void Trinity::pack(const float variable, std::vector<unsigned char> &buffer, const uint8_t numberBits, const uint8_t num_bit_integer, const uint8_t num_bit_decimal)
{   
    bool withsign = false;
    if (variable < 0.0) withsign=true;

    int variableInteger = int(variable);
    float variableDecimal = variable - float(variableInteger);
    if(withsign && variableInteger<0)
    {
         variableInteger = -variableInteger ;
         variableDecimal = -float(variableInteger) - variable;
    }

    //std::cout << "variableInteger: " << variableInteger << std::endl;
    //std::cout << "variableDecimal: " << variableDecimal << std::endl;

    //integer part
    std::string binary_integer = transformIntTobinary<int>(variableInteger);
    while (binary_integer.size() != num_bit_integer)
    {
        binary_integer = binary_integer.insert(0,"0");
    }
    if(withsign)
    {
        binary_integer[0] = '1' ;
    }
    // decimal part
    std::string binary_decimal = transformDecimalTobinary<float>(variableDecimal, num_bit_decimal);
    //total
    std::string binary = binary_integer + binary_decimal;
    std::string binary_subset = "";
    for (int i=0; i<binary.size();i=i+8)
    {
        binary_subset.clear();
        binary_subset = binary.substr(i,8);
        int value = transformBinaryToInt<int>(binary_subset);
        unsigned char value_char = value;

        buffer.push_back(value_char);
    }
}

void Trinity::pack(const double variable, std::vector<unsigned char> &buffer, const uint8_t numberBits, const uint8_t num_bit_integer, const uint8_t num_bit_decimal)
{   
    bool withsign = false;
    if (variable < 0.0) withsign=true;

    int variableInteger = int(variable);
    double variableDecimal = variable - double(variableInteger);
    if(withsign && variableInteger<0)
    {
         variableInteger = -variableInteger ;
         variableDecimal = -double(variableInteger) - variable;
    }

    //std::cout << "variableInteger: " << variableInteger << std::endl;
    //std::cout << "variableDecimal: " << variableDecimal << std::endl;

    //integer part
    std::string binary_integer = transformIntTobinary<int>(variableInteger);
    while (binary_integer.size() != num_bit_integer)
    {
        binary_integer = binary_integer.insert(0,"0");
    }
    if(withsign)
    {
        binary_integer[0] = '1' ;
    }
    // decimal part
    std::string binary_decimal = transformDecimalTobinary<double>(variableDecimal, num_bit_decimal);
    //total
    std::string binary = binary_integer + binary_decimal;
    std::string binary_subset = "";
    for (int i=0; i<binary.size();i=i+8)
    {
        binary_subset.clear();
        binary_subset = binary.substr(i,8);
        int value = transformBinaryToInt<int>(binary_subset);
        unsigned char value_char = value;

        buffer.push_back(value_char);
    }
}

void Trinity::unpack(int &variable,
                       const std::vector<unsigned char> buffer,
                       const uint word,
                       const int num_bit_word,
                       const int ini_bit,
                       const int final_bit,
                       const bool withsign)
{
    std::string bin = "";
    for (auto byte : buffer)
    {
        bin = bin + byteToBinary(byte);
    }
    
    std::string::const_iterator first = bin.begin() + word*num_bit_word + ini_bit;
    std::string::const_iterator last  = bin.begin() + word*num_bit_word + final_bit;
    std::string sub_buffer(first, last);
    if(withsign && sub_buffer[0] == '1')
    {
        sub_buffer[0] = '0';
        variable = -transformBinaryToInt<int>(sub_buffer);
    }
    else
    {
        variable = transformBinaryToInt<int>(sub_buffer);
    }
}

void Trinity::unpack(long &variable,
                       const std::vector<unsigned char> buffer,
                       const uint word,
                       const int num_bit_word,
                       const int ini_bit,
                       const int final_bit,
                       const bool withsign)
{
    std::string bin = "";
    for (auto byte : buffer)
    {
        bin = bin + byteToBinary(byte);
    }
    
    std::string::const_iterator first = bin.begin() + word*num_bit_word + ini_bit;
    std::string::const_iterator last  = bin.begin() + word*num_bit_word + final_bit;
    std::string sub_buffer(first, last);
    if(withsign && sub_buffer[0] == '1')
    {
        sub_buffer[0] = '0';
        variable = -transformBinaryToInt<long>(sub_buffer);
    }
    else
    {
        variable = transformBinaryToInt<long>(sub_buffer);
    }
}

void Trinity::unpack(float &variable,
                       std::vector<unsigned char> buffer,
                       const uint word,
                       const uint8_t num_bit_word,
                       const uint8_t ini_bit,
                       const uint8_t  final_bit,
                       const bool withsign,
                       const uint8_t num_bit_integer,
                       const uint8_t num_bit_decimal)
{
    variable = 0.0; //clean just in case
    std::string bin = "";
    for (auto byte : buffer)
    {
        bin = bin + byteToBinary(byte);
    }
    std::string::const_iterator first_number = bin.begin() + word*num_bit_word + ini_bit;
    std::string::const_iterator last_number  = bin.begin() + word*num_bit_word + final_bit;
    std::string sub_buffer(first_number, last_number);
    //decimal part
    std::string::const_iterator first_decimal = sub_buffer.begin() + num_bit_integer ;
    std::string::const_iterator last_decimal  = sub_buffer.begin() + num_bit_integer + num_bit_decimal;
    std::string sub_buffer_decimal(first_decimal, last_decimal);
    variable = transformBinaryToDecimal<float>(sub_buffer_decimal);

    //integer part
    std::string::const_iterator first_integer = sub_buffer.begin() + 0;
    std::string::const_iterator last_integer  = sub_buffer.begin() + num_bit_integer;
    std::string sub_buffer_integer(first_integer, last_integer);   

    if(withsign && sub_buffer_integer[0] == '1')
    {
        sub_buffer_integer[0] = '0';
        variable = - (variable + transformBinaryToInt<int>(sub_buffer_integer));
    }
    else
    {
        variable = variable + transformBinaryToInt<int>(sub_buffer_integer);
    }
    
}

void Trinity::unpack(double &variable,
                       std::vector<unsigned char> buffer,
                       const uint word,
                       const uint8_t num_bit_word,
                       const uint8_t ini_bit,
                       const uint8_t  final_bit,
                       const bool withsign,
                       const uint8_t num_bit_integer,
                       const uint8_t num_bit_decimal)
{
    variable = 0.0; //clean just in case
    std::string bin = "";
    for (auto byte : buffer)
    {
        bin = bin + byteToBinary(byte);
    }
    std::string::const_iterator first_number = bin.begin() + word*num_bit_word + ini_bit;
    std::string::const_iterator last_number  = bin.begin() + word*num_bit_word + final_bit;
    std::string sub_buffer(first_number, last_number);
    //decimal part
    std::string::const_iterator first_decimal = sub_buffer.begin() + num_bit_integer ;
    std::string::const_iterator last_decimal  = sub_buffer.begin() + num_bit_integer + num_bit_decimal;
    std::string sub_buffer_decimal(first_decimal, last_decimal);
    variable = transformBinaryToDecimal<double>(sub_buffer_decimal);

    //integer part
    std::string::const_iterator first_integer = sub_buffer.begin() + 0;
    std::string::const_iterator last_integer  = sub_buffer.begin() + num_bit_integer;
    std::string sub_buffer_integer(first_integer, last_integer);   

    if(withsign && sub_buffer_integer[0] == '1')
    {
        sub_buffer_integer[0] = '0';
        variable = - (variable + transformBinaryToInt<int>(sub_buffer_integer));
    }
    else
    {
        variable = variable + transformBinaryToInt<int>(sub_buffer_integer);
    }
    
}

std::string Trinity::byteToBinary(unsigned char byte)
{
    std::string binary = "";
    unsigned char mask = 1; 
    for (int i = 0; i < 8; i++) 
    {
        // Mask each bit in the byte and store it
        bool yes =  (byte & (mask << i)) != 0;
        if(yes == true)
        {
            binary.append("1");
        }
        else
        {
            binary.append("0");
        }        
    }
    std::reverse(binary.begin(), binary.end());
    return binary;
}


void Trinity::convertDecimalToBuffer(const float variableDecimal, 
                                            std::vector<unsigned char> &buffer, 
                                            const uint8_t num_bit_decimal)
{
    std::string variable_base2_subset = "";
    std::string variableBase2 = transformDecimalTobinary(variableDecimal, num_bit_decimal);
    while (variableBase2.size() != num_bit_decimal)
    {
        //variableBase2 = variableBase2.insert(0,"0");
        variableBase2.append("0");
    }
    //std::cout<< "variableBase2 Decimal" << variableBase2 << std::endl;
    for (int i=0; i<variableBase2.size();i=i+8)
    {
        variable_base2_subset.clear();
        variable_base2_subset = variableBase2.substr(i,8);
        int value = transformBinaryToInt<int>(variable_base2_subset);
        unsigned char value_char = value;

        buffer.push_back(value_char);
    }
}

void Trinity::bufferToInteger(const std::vector<unsigned char> &buffer, int &variable, const bool withsign)
{
    std::string bin = "";
    for (auto byte : buffer)
    {
        bin = bin + byteToBinary(byte);
    }
    std::cout << "bin " <<bin <<std::endl;
    if(withsign)
    {
        bin[0] = '0';
        variable = -transformBinaryToInt<int>(bin);
    }
    else
    {
        variable = transformBinaryToInt<int>(bin);
    }
}

