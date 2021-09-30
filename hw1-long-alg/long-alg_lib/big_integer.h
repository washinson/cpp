//
// Created by sanya112001 on 9/23/21.
//

#ifndef HW1_LONG_ALG_BIG_INTEGER_H
#define HW1_LONG_ALG_BIG_INTEGER_H

#include <vector>

class big_integer {
public:
    explicit big_integer(std::string str);
    big_integer(int l);
    big_integer(int64_t l);
    big_integer(uint64_t l);

    explicit operator std::string() const;

    friend std::ostream& operator <<(std::ostream& os, const big_integer& num);
    friend bool operator==(const big_integer &left, const big_integer &right);
    friend bool operator <(const big_integer& left, const big_integer& right);
    friend bool operator !=(const big_integer& left, const big_integer& right);
    friend bool operator <=(const big_integer& left, const big_integer& right);
    friend bool operator >(const big_integer& left, const big_integer& right);
    friend bool operator >=(const big_integer& left, const big_integer& right);
    friend big_integer operator +(big_integer left, const big_integer& right);
    friend big_integer operator -(big_integer left, const big_integer& right);
    friend big_integer operator *(big_integer left, const big_integer& right);
    friend big_integer operator /(const big_integer& left, const big_integer& right);
    friend big_integer operator %(big_integer left, const big_integer& right);
    big_integer operator +() const;
    big_integer operator -() const;

private:
    static const int BASE = 1000000000;
    std::vector<int> _nums;
    bool _negative;
    void _clear_useless_zeros();
    void _move_right();
};


#endif //HW1_LONG_ALG_BIG_INTEGER_H
