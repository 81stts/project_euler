#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

// Problem 31: 硬币求和
int problem31(int target) {
    int coins[] = {1, 2, 5, 10, 20, 50, 100, 200};
    int dp[201] = {0};
    dp[0] = 1;
    
    for (int i = 0; i < 8; i++) {
        for (int j = coins[i]; j <= target; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }
    return dp[target];
}

int is_pandigital(int a, int b, int c) {
    int digits[10] = {0};
    while (a > 0) { digits[a%10]++; a /= 10; }
    while (b > 0) { digits[b%10]++; b /= 10; }
    while (c > 0) { digits[c%10]++; c /= 10; }
    if (digits[0] != 0) return 0;
    for (int i = 1; i <= 9; i++) 
        if (digits[i] != 1) return 0;
    return 1;
}

// Problem 32: 全数字乘积
int problem32() {
    int products[100], count = 0;
    for (int a = 1; a < 10000; a++) {
        for (int b = a; b < 10000; b++) {
            int c = a * b;
            if (c > 99999) break;
            if (is_pandigital(a, b, c)) {
                int exists = 0;
                for (int i = 0; i < count; i++) 
                    if (products[i] == c) exists = 1;
                if (!exists) products[count++] = c;
            }
        }
    }
    int sum = 0;
    for (int i = 0; i < count; i++) sum += products[i];
    return sum;
}

int _gcd(int a, int b) { return b ? _gcd(b, a % b) : a; }

// Problem 33: 数字约分分数
int problem33() {
    int num_prod = 1, den_prod = 1;
    for (int num = 10; num < 100; num++) {
        for (int den = num + 1; den < 100; den++) {
            int a = num / 10, b = num % 10;
            int c = den / 10, d = den % 10;
            if (b == 0 || d == 0) continue;
            if ((a == d && den * b == num * c) || 
                (b == c && den * a == num * d)) {
                num_prod *= num;
                den_prod *= den;
            }
        }
    }
    return den_prod / _gcd(num_prod, den_prod);
}

// Problem 34: 数字阶乘和
int problem34() {
    int factorials[] = {1,1,2,6,24,120,720,5040,40320,362880};
    int total = 0;
    for (int i = 10; i < 100000; i++) {
        int sum = 0, n = i;
        while (n > 0) {
            sum += factorials[n % 10];
            n /= 10;
        }
        if (sum == i) total += i;
    }
    return total;
}

int is__prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i*i <= n; i++) 
        if (n % i == 0) return 0;
    return 1;
}

int rotate(int n) {
    int last = n % 10;
    int digits = (int)log10(n) + 1;
    return (n / 10) + last * pow(10, digits - 1);
}

// Problem 35: 循环素数
int problem35(int n) {
    int count = 0;
    for (int i = 2; i < n; i++) {
        if (!is__prime(i)) continue;
        int num = i, valid = 1;
        for (int j = 0; j < (int)log10(i); j++) {
            num = rotate(num);
            if (!is__prime(num)) { valid = 0; break; }
        }
        if (valid) count++;
    }
    return count;
}

int ispalindrome(int n, int base) {
    int reversed = 0, original = n;
    while (n > 0) {
        reversed = reversed * base + (n % base);
        n /= base;
    }
    return original == reversed;
}

// Problem 36: 双进制回文数
int problem36(int n) {
    int sum = 0;
    for (int i = 1; i < n; i++) {
        if (ispalindrome(i, 10) && ispalindrome(i, 2))
            sum += i;
    }
    return sum;
}

int is_truncatable(int n) {
    if (n < 10) return 0;
    // 从左截断
    int left = n;
    while (left > 0) {
        if (!is__prime(left)) return 0;
        left %= (int)pow(10, (int)log10(left));
    }
    // 从右截断
    int right = n;
    while (right > 0) {
        if (!is__prime(right)) return 0;
        right /= 10;
    }
    return 1;
}

// Problem 37: 可截素数
int problem37(int count_needed) {
    int sum = 0, count = 0, i = 11;
    while (count < count_needed) {
        if (is_truncatable(i)) {
            sum += i;
            count++;
        }
        i += 2;
    }
    return sum;
}

int is_pandigital_9(int n) {
    int digits[10] = {0};
    while (n > 0) {
        int d = n % 10;
        if (d == 0 || digits[d]) return 0;
        digits[d] = 1;
        n /= 10;
    }
    return 1;
}

// Problem 38: 全数字乘积
int problem38() {
    int max = 0;
    for (int i = 1; i < 10000; i++) {
        int concat = 0, n = 0;
        for (int k = 1; ; k++) {
            int product = i * k;
            int digits = (int)log10(product) + 1;
            concat = concat * pow(10, digits) + product;
            n += digits;
            if (n >= 9) break;
        }
        if (n == 9 && is_pandigital_9(concat) && concat > max)
            max = concat;
    }
    return max;
}

// Problem 39: 整数直角三角形周长
int problem39(int max_p) {
    int max_sol = 0, best_p = 0;
    for (int p = 12; p <= max_p; p++) {
        int solutions = 0;
        for (int a = 1; a < p/3; a++) {
            if ((p*(p - 2*a)) % (2*(p - a)) == 0)
                solutions++;
        }
        if (solutions > max_sol) {
            max_sol = solutions;
            best_p = p;
        }
    }
    return best_p;
}

// Problem 40: 钱珀瑙恩常数
int problem40() {
    char str[1000001] = {0};
    int pos = 0, num = 1;
    while (pos < 1000000) {
        char buf[20];
        sprintf(buf, "%d", num++);
        int len = strlen(buf);
        if (pos + len > 1000000) len = 1000000 - pos;
        strncat(str + pos, buf, len);
        pos += len;
    }
    return (str[0]-'0') * (str[9]-'0') * (str[99]-'0') * 
           (str[999]-'0') * (str[9999]-'0') * (str[99999]-'0') * 
           (str[999999]-'0');
}