#include <string>
#include <iostream>
#include <cstdint>
#include <utility>
#include <algorithm>
#include <cmath>


struct Number {
    int length;
    std::string digits;

    Number() = default;

    Number(const Number &other) = default;

    explicit Number(std::string&& digits) : length(digits.length()), digits(std::move(digits)) {}

    Number(const Number &other, int position, int length) : digits(std::move(other.digits.substr(position, length))),
                                                            length(length) {}

    Number operator+(const Number &other) const {
        if (other.length <= 19 && length <= 19) {
            return Number(std::to_string(std::stoull(other.digits) + std::stoull(digits)));
        }
        if (length < other.length) {
            return other + *this;
        }
        std::string result(length + 1, '0');
        int carry = 0;
        for (int i = 1; i <= length; ++i) {
            int a = digits[length - i] - '0';
            int b = i <= other.length ? other.digits[other.length - i] - '0' : 0;
            int sum = a + b + carry;
            result[result.length() - i] = sum % 10 + '0';
            carry = sum / 10;
        }
        if (carry) {
            result[0] = '1';
        } else {
            result.erase(0, 1);
        }
        return Number(std::move(result));
    }


    Number operator-(const Number &other) const {
        if (other.length <= 19 && length <= 19) {
            return Number(std::to_string(std::stoull(digits) - std::stoull(other.digits)));
        }
        std::string result(digits.length(), '0');
        int borrow = 0;
        for (int i = 0; i < digits.length(); ++i) {
            int a = digits[digits.length() - 1 - i] - '0';
            int b = i < other.digits.length() ? other.digits[other.digits.length() - 1 - i] - '0' : 0;
            int diff = a - b - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result[result.length() - 1 - i] = diff + '0';
        }
        size_t pos = result.find_first_not_of('0');
        if (pos != std::string::npos) {
            result = result.substr(pos);
        } else {
            result = "0";
        }
        return Number(std::move(result));
    }

    static Number multiply(const Number& num1, const Number& num2) {
        std::string result(num1.length + num2.length, '0');
        for (int i = num1.length - 1; i >= 0; i--) {
            int carry = 0;
            for (int j = num2.length - 1; j >= 0; j--) {
                int temp = (result[i + j + 1] - '0') + (num1.digits[i] - '0') * (num2.digits[j] - '0') + carry;
                result[i + j + 1] = temp % 10 + '0';
                carry = temp / 10;
            }
            result[i] += carry;
        }
        size_t pos = result.find_first_not_of('0');
        if (std::string::npos != pos) {
            return Number(std::move(result.substr(pos)));
        }
        return Number("0");
    }

    void MulByTenDegree(int degree) {
        length += degree;
        digits += std::string(degree, '0');
    }

    static void normalizeNumbers(Number &a, Number &b) {
        int max_length = std::max(a.length, b.length);
        while (a.length < max_length) {
            a.digits.insert(a.digits.begin(), '0');
            a.length++;
        }
        while (b.length < max_length) {
            b.digits.insert(b.digits.begin(), '0');
            b.length++;
        }
    }
};

Number mulByKarasuba(Number a, Number b) {
    if (a.length + b.length <= 18) {
        return Number(std::to_string(std::stoull(a.digits) * std::stoull(b.digits)));
    }
    if(a.length + b.length <= 200) {
        return Number::multiply(a, b);
    }
    Number::normalizeNumbers(a, b);
    int half_length = a.length / 2 + a.length % 2;
    Number a_high(a, 0, half_length);
    Number a_low(a, half_length, a.length - half_length);
    Number b_high(b, 0, half_length);
    Number b_low(b, half_length, b.length - half_length);
    Number z0 = mulByKarasuba(a_low, b_low);
    Number z2 = mulByKarasuba(a_high, b_high);
    Number z1 = mulByKarasuba(a_low + a_high, b_low + b_high) - z2 - z0;
    z2.MulByTenDegree(a.length - a.length % 2);
    z1.MulByTenDegree(a.length / 2);
    return z2 + z1 + z0;
}

int main() {
    std::string str_a, str_b;
    std::cin >> str_a >> str_b;
    Number a(std::move(str_a));
    Number b(std::move(str_b));
    b = mulByKarasuba(a, b);
    int pos = b.digits.find_first_not_of('0');
    if (pos != std::string::npos) {
        std::cout << b.digits.substr(pos);
    } else {
        std::cout << 0;
    }
    return 0;
}