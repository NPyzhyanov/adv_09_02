#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

class big_integer
{
public:
    big_integer();
    big_integer(std::string string_notation);
    big_integer(const big_integer &object_to_copy);
    big_integer(big_integer &&object_to_move) noexcept;
    
    ~big_integer();
    
    big_integer& operator=(const big_integer &value_to_assign);
    big_integer& operator=(big_integer &&value_to_assign) noexcept;
    
    big_integer& operator+(const big_integer &right);
    big_integer& operator+=(const big_integer &additive);
    big_integer& operator*(const int &right);
    
    void print();
    
private:
    std::string notation;
    
    void swap(big_integer &source);
    
};

#endif // BIG_INTEGER_H
