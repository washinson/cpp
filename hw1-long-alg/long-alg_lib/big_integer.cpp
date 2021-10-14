//
// Created by sanya112001 on 9/23/21.
//

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "big_integer.h"

big_integer::big_integer(std::string str) {
    if (str.length() == 0) {
        _negative = false;
    } else {
        if (str[0] == '-') {
            str = str.substr(1);
            _negative = true;
        } else {
            _negative = false;
        }
        for (auto i = (int64_t) str.length(); i > 0; i -= 9) {
            if (i < 9) {
                _nums.push_back(std::stoi(str.substr(0, i)));
            } else {
                _nums.push_back(std::stoi(str.substr(i - 9, 9)));
            }
        }
        _clear_useless_zeros();
    }
}

void big_integer::_clear_useless_zeros() {
    while (_nums.size() > 1 && _nums.back() == 0) {
        _nums.pop_back();
    }
    if (_nums.size() == 1 && _nums[0] == 0) {
        _negative = false;
    }
}

std::ostream &operator<<(std::ostream &os, const big_integer &num) {
    if (num._nums.empty()) {
        os << 0;
    } else {
        if (num._negative) {
            os << '-';
        }
        os << num._nums.back();
        // следующие числа нам нужно печатать группами по 9 цифр
        // поэтому сохраним текущий символ-заполнитель, а потом восстановим его
        char old_fill = os.fill('0');
        for (int64_t i = (int64_t) (num._nums.size()) - 2; i >= 0; --i) {
            os << std::setw(9) << num._nums[i];
        }

        os.fill(old_fill);
    }

    return os;
}

big_integer::operator std::string() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

bool operator==(const big_integer &left, const big_integer &right) {
    if (left._negative != right._negative) {
        return false;
    }
    if (left._nums.empty()) {
        return right._nums.empty() || (right._nums.size() == 1 && right._nums[0] == 0);
    }
    if (right._nums.empty()) {
        return left._nums.size() == 1 && left._nums[0] == 0;
    }
    if (left._nums.size() != right._nums.size()) {
        return false;
    }
    for (size_t i = 0; i < left._nums.size(); ++i) {
        if (left._nums[i] != right._nums[i]) {
            return false;
        }
    }
    return true;
}

bool operator<(const big_integer &left, const big_integer &right) {
    if (left == right) {
        return false;
    }
    if (left._negative) {
        if (right._negative) {
            return ((-right) < (-left));
        } else {
            return true;
        }
    } else if (right._negative) {
        return false;
    } else {
        if (left._nums.size() != right._nums.size()) {
            return left._nums.size() < right._nums.size();
        } else {
            for (auto i = (int64_t) left._nums.size() - 1; i >= 0; --i) {
                if (left._nums[i] != right._nums[i]) {
                    return left._nums[i] < right._nums[i];
                }
            }
            return false;
        }
    }
}

big_integer big_integer::operator+() const {
    return big_integer{*this};
}

big_integer big_integer::operator-() const {
    big_integer copy(*this);
    copy._negative = !copy._negative;
    return copy;
}

bool operator!=(const big_integer &left, const big_integer &right) {
    return !(left == right);
}

bool operator<=(const big_integer &left, const big_integer &right) {
    return (left < right || left == right);
}

bool operator>(const big_integer &left, const big_integer &right) {
    return !(left <= right);
}

bool operator>=(const big_integer &left, const big_integer &right) {
    return !(left < right);
}

big_integer operator+(big_integer left, const big_integer &right) {
    if (left._negative) {
        if (right._negative) {
            return -(-left + (-right));
        } else {
            return right - (-left);
        }
    } else if (right._negative) {
        return left - (-right);
    }
    int carry = 0;
    for (size_t i = 0; i < std::max(left._nums.size(), right._nums.size()) || carry != 0; ++i) {
        if (i == left._nums.size()) {
            left._nums.push_back(0);
        }
        left._nums[i] += carry + (i < right._nums.size() ? right._nums[i] : 0);
        carry = left._nums[i] >= big_integer::BASE;
        if (carry != 0) {
            left._nums[i] -= big_integer::BASE;
        }
    }
    return left;
}

big_integer operator-(big_integer left, const big_integer &right) {
    if (right._negative) {
        return left + (-right);
    } else if (left._negative) {
        return -(-left + right);
    } else if (left < right) {
        return -(right - left);
    }
    int carry = 0;
    for (size_t i = 0; i < right._nums.size() || carry != 0; ++i) {
        left._nums[i] -= carry + (i < right._nums.size() ? right._nums[i] : 0);
        carry = left._nums[i] < 0;
        if (carry != 0) {
            left._nums[i] += big_integer::BASE;
        }
    }
    left._clear_useless_zeros();
    return left;
}

big_integer operator*(big_integer left, const big_integer &right) {
    big_integer result(0L);
    result._nums.resize(left._nums.size() + right._nums.size());
    for (size_t i = 0; i < left._nums.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < right._nums.size() || carry != 0; ++j) {
            int64_t cur =
                    result._nums[i + j] + left._nums[i] * 1LL * (j < right._nums.size() ? right._nums[j] : 0) + carry;
            result._nums[i + j] = (int) (cur % big_integer::BASE);
            carry = (int) (cur / big_integer::BASE);
        }
    }
    result._negative = left._negative != right._negative;
    result._clear_useless_zeros();
    return result;
}

void big_integer::_move_right() {
    if (_nums.empty()) {
        _nums.push_back(0);
        return;
    }
    _nums.push_back(_nums[_nums.size() - 1]);
    for (size_t i = _nums.size() - 2; i > 0; --i) {
        _nums[i] = _nums[i - 1];
    }
    _nums[0] = 0;
}

big_integer operator/(const big_integer &left, const big_integer &right) {
    if (right == big_integer(0)) {
        throw std::exception();
    }
    big_integer b = right;
    b._negative = false;
    big_integer result(0), current(0);
    result._nums.resize(left._nums.size());
    for (int64_t i = (int64_t) (left._nums.size()) - 1; i >= 0; --i) {
        current._move_right();
        current._nums[0] = left._nums[i];
        current._clear_useless_zeros();
        int x = 0, l = 0, r = big_integer::BASE;
        while (l <= r) {
            int m = (l + r) / 2;
            big_integer t = b * m;
            if (t <= current) {
                x = m;
                l = m + 1;
            } else r = m - 1;
        }

        result._nums[i] = x;
        current = current - b * x;
    }

    result._negative = left._negative != right._negative;
    result._clear_useless_zeros();
    return result;
}

big_integer operator%(big_integer left, const big_integer &right) {
    big_integer result = left - (left / right) * right;
    if (result._negative) {
        result = result + right;
    }
    return result;
}

big_integer::big_integer(int l) {
    if (l < 0) {
        _negative = true;
        l = -l;
    } else {
        _negative = false;
    }
    do {
        _nums.push_back(l % big_integer::BASE);
        l /= big_integer::BASE;
    } while (l != 0);
}

big_integer::big_integer(int64_t l) {
    if (l < 0) {
        _negative = true;
        l = -l;
    } else _negative = false;
    do {
        _nums.push_back(l % big_integer::BASE);
        l /= big_integer::BASE;
    } while (l != 0);
}

big_integer::big_integer(uint64_t l) {
    _negative = false;
    do {
        _nums.push_back(l % big_integer::BASE);
        l /= big_integer::BASE;
    } while (l != 0);
}