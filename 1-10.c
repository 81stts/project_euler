#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

// Problem 1: 求小于n的3或5的倍数之和
int problem1(int n) {
    int sum = 0;
    for (int i = 3; i < n; i++) {
        if (i % 3 == 0 || i % 5 == 0) sum += i;
    }
    return sum;
}

// Problem 2: 斐波那契数列偶数项和（<=n）
int problem2(int n) {
    int sum = 0, a = 1, b = 2;
    while (b <= n) {
        if (b % 2 == 0) sum += b;
        int next = a + b;
        a = b;
        b = next;
    }
    return sum;
}

// Problem 3: 求n的最大质因数
long long problem3(long long n) {
    long long max_prime = -1;
    while (n % 2 == 0) { max_prime = 2; n /= 2; }
    for (long long i = 3; i*i <= n; i += 2) {
        while (n % i == 0) {
            max_prime = i;
            n /= i;
        }
    }
    return (n > 2) ? n : max_prime;
}

// Problem 4: 两个n位数乘积的最大回文数
int is_palindrome(int num) {
    int reversed = 0, original = num;
    while (num > 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    return original == reversed;
}

int problem4(int n) {
    int max = 0, lower = (int)pow(10, n-1), upper = (int)pow(10, n);
    for (int i = lower; i < upper; i++) {
        for (int j = i; j < upper; j++) {
            int product = i * j;
            if (product > max && is_palindrome(product)) max = product;
        }
    }
    return max;
}

// Problem 5: 求1~n的最小公倍数
int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }
int lcm(int a, int b) { return a / gcd(a, b) * b; }

int problem5(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) result = lcm(result, i);
    return result;
}

// Problem 6: 求前n自然数的平方和与和的平方之差
int problem6(int n) {
    int sum = n*(n+1)/2;
    int sum_sq = (n*(n+1)*(2*n+1))/6;
    return sum*sum - sum_sq;
}

int is_prime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i*i <= num; i++) 
        if (num%i == 0) return 0;
    return 1;
}

// Problem 7: 第n个质数
int problem7(int n) {
    int count = 0, num = 1;
    while (count < n) {
        num++;
        if (is_prime(num)) count++;
    }
    return num;
}

// Problem 8: 1000位数字中相邻n位的最大乘积
const char num_str[] = 
"73167176531330624919225119674426574742355349194934"
"96983520312774506326239578318016984801869478851843"
/* 完整1000位数字需填入 */;

int problem8(int n) {
    int max = 0, len = strlen(num_str);
    for (int i = 0; i <= len - n; i++) {
        int product = 1;
        for (int j = 0; j < n; j++) 
            product *= num_str[i+j] - '0';
        if (product > max) max = product;
    }
    return max;
}

// Problem 9: 找到a+b+c=n的毕达哥拉斯三元组，返回a*b*c
int problem9(int n) {
    for (int a = 1; a < n; a++) {
        for (int b = a+1; b < n; b++) {
            int c = n - a - b;
            if (a*a + b*b == c*c) return a*b*c;
        }
    }
    return -1;
}

// Problem 10: 求n以下所有质数的和
long long problem10(int n) {
    bool *sieve = (bool*)calloc(n+1, sizeof(bool));
    long long sum = 0;
    for (int p = 2; p <= n; p++) {
        if (!sieve[p]) {
            sum += p;
            for (int i = p; i <= n; i += p) sieve[i] = true;
        }
    }
    free(sieve);
    return sum;
}