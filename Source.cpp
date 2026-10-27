#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

class big_integer {
private:
    std::string digits;

public:
    big_integer() = default;

    big_integer(const std::string& str) : digits(str) {
        if (digits.empty()) {
            digits = "0";
        }
    }

    big_integer(const big_integer& other) = default;

    big_integer(big_integer&& other) noexcept : digits(std::move(other.digits)) {
        other.digits = "0";
    }

    big_integer& operator=(const big_integer& other) = default;

    big_integer& operator=(big_integer&& other) noexcept {
        if (this != &other) {
            digits = std::move(other.digits);
            other.digits = "0";
        }
        return *this;
    }

    ~big_integer() = default;

    big_integer operator+(const big_integer& other) const {
        std::string result = "";
        int i = digits.length() - 1;
        int j = other.digits.length() - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) {
                sum += digits[i] - '0';
                i--;
            }
            if (j >= 0) {
                sum += other.digits[j] - '0';
                j--;
            }
            carry = sum / 10;
            result += std::to_string(sum % 10);
        }

        std::reverse(result.begin(), result.end());
        return big_integer(result);
    }

    big_integer operator*(int num) const {
        if (num == 0 || digits == "0") {
            return big_integer("0");
        }

        std::string result = "";
        int carry = 0;

        for (int i = digits.length() - 1; i >= 0; --i) {
            long long current = static_cast<long long>(digits[i] - '0') * num + carry;
            carry = current / 10;
            result += std::to_string(current % 10);
        }

        while (carry) {
            result += std::to_string(carry % 10);
            carry /= 10;
        }

        std::reverse(result.begin(), result.end());
        return big_integer(result);
    }

    friend std::ostream& operator<<(std::ostream& os, const big_integer& num) {
        os << num.digits;
        return os;
    }
};

int main() {
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result << std::endl;

    auto number3 = big_integer("1234");
    auto result2 = number3 * 25;
    std::cout << result2 << std::endl;

    return 0;
}