#include <string>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <iostream>

#include "big_integer.h"

big_integer::big_integer()
{
    notation = "0";
}

big_integer::big_integer(std::string string_notation)
{
    for (auto it = string_notation.cbegin(); it != string_notation.cend(); it++)
    {
        if (*it < '0' || *it > '9')
        {
            throw std::invalid_argument("incorrect number");
        }
    }
    notation = string_notation;
}

big_integer::big_integer(const big_integer &object_to_copy)
{
    notation = object_to_copy.notation;
}

big_integer::big_integer(big_integer &&object_to_move)
{
    notation = std::move(object_to_move.notation);
}

big_integer::~big_integer()
{
}

big_integer& big_integer::operator=(const big_integer &value_to_assign)
{
    if (this == &value_to_assign)
    {
        return *this;
    }
    big_integer tmp = value_to_assign;
    swap(tmp);
    return *this;
}

big_integer& big_integer::operator=(big_integer &&value_to_assign)
{
    if (this == &value_to_assign)
    {
        return *this;
    }
    big_integer tmp = big_integer(value_to_assign);
    swap(tmp);
    return *this;
}

void big_integer::swap(big_integer &source)
{
    big_integer tmp;
    tmp.notation = std::move(notation);
    notation = std::move(source.notation);
    source.notation = std::move(tmp.notation);
}

big_integer& big_integer::operator+(const big_integer &right)
{
    if (right.notation == "0")
    {
        return *this;
    }
    
    auto it_left = notation.rbegin();
    auto it_right = right.notation.rbegin();
    int next_place_additive = 0;
    int position = 0;
    
    while (it_left != notation.rend() && it_right != right.notation.rend())
    {
        int sum = static_cast<int>(*it_left - '0') + static_cast<int>(*it_right - '0') + next_place_additive;
        next_place_additive = sum / 10;
        *it_left = static_cast<char>(sum % 10) + '0';
        
        it_left++;
        it_right++;
        position++;
    }
    
    if (it_right == right.notation.rend() && it_left != notation.rend()) // правое число короче левого
    {
        std::string zeros_to_add = "";
        for (int i = 0; i < position; i++)
        {
            zeros_to_add += "0";
        }
        big_integer additive(big_integer (std::to_string(next_place_additive) + zeros_to_add));
        *this = *this + additive;
    }
    else if (it_right != right.notation.rend() && it_left == notation.rend()) // правое число длиннее левого
    {
        big_integer right_copy(right);
        right_copy.notation.replace(right_copy.notation.length() - position, position, notation);
        
        std::string zeros_to_add = "";
        for (int i = 0; i < position; i++)
        {
            zeros_to_add += "0";
        }
        big_integer additive(big_integer (std::to_string(next_place_additive) + zeros_to_add));
        
        notation = (right_copy + additive).notation;
    }
    else // у чисел одинаковое количество знаков
    {
        if(next_place_additive != 0)
        {
            notation = std::to_string(next_place_additive) + notation;
        }
    }
    
    return *this;
}

big_integer& big_integer::operator+=(const big_integer &additive)
{
    return (*this + additive);
}

big_integer& big_integer::operator*(const int &right)
{
    if (right == 1)
    {
        return *this;
    }
    if (notation == "0")
    {
        return *this;
    }
    if (right == 0)
    {
        notation = "0";
        return *this;
    }
    if (right < 0)
    {
        throw std::invalid_argument("Operator * is not defined for negative arguments");
    }
    
    big_integer result = big_integer();
    
    int divisor = 1;
    int residue = 0;
    int multiplier = 0;
    
    do
    {
        divisor *= 10;
        multiplier = (right % divisor) / (divisor / 10);
        residue = right / divisor;
        int next_place_additive = 0;
        std::string digitwise_multiplucation_result = notation + (std::to_string(divisor / 10)).erase(0, 1);
        
        for (auto it = digitwise_multiplucation_result.rbegin(); it != digitwise_multiplucation_result.rend(); it++)
        {
            int product = static_cast<int>(*it - '0') * multiplier + next_place_additive;
            *it = static_cast<char>(product % 10) + '0';
            next_place_additive = product / 10;
        }
        if (next_place_additive != 0)
        {
            result += big_integer(std::to_string(next_place_additive) + digitwise_multiplucation_result);
        }
        else
        {
            result += big_integer(digitwise_multiplucation_result);
        }
        digitwise_multiplucation_result += "0";
    }
    while (residue != 0);
    
    notation = std::move(result.notation);
    
    return *this;
}

void big_integer::print()
{
    std::cout << notation;
}
