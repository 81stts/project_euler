#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAX_SIZE 20

int max(int a, int b) {
    return (a > b) ? a : b;
}

int calculateProduct(int arr[], int size) {
    int product = 1;
    for (int i = 0; i < size; i++) {
        product *= arr[i];
    }
    return product;
}

// Problem 11: 20×20网格中相邻k个数的最大乘积
int problem11(int grid[][MAX_SIZE], int gridSize, int n) {
    int maxProduct = 0;

    // 水平方向计算最大乘积
    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col <= gridSize - n; col++) {
            int product = calculateProduct(grid[row] + col, n);
            maxProduct = max(maxProduct, product);
        }
    }

    // 垂直方向计算最大乘积
    for (int col = 0; col < gridSize; col++) {
        for (int row = 0; row <= gridSize - n; row++) {
            int product = 1;
            for (int i = 0; i < n; i++) {
                product *= grid[row + i][col];
            }
            maxProduct = max(maxProduct, product);
        }
    }

    // 对角线方向（从左上到右下）计算最大乘积
    for (int row = 0; row <= gridSize - n; row++) {
        for (int col = 0; col <= gridSize - n; col++) {
            int product = 1;
            for (int i = 0; i < n; i++) {
                product *= grid[row + i][col + i];
            }
            maxProduct = max(maxProduct, product);
        }
    }

    // 对角线方向（从右上到左下）计算最大乘积
    for (int row = 0; row <= gridSize - n; row++) {
        for (int col = n - 1; col < gridSize; col++) {
            int product = 1;
            for (int i = 0; i < n; i++) {
                product *= grid[row + i][col - i];
            }
            maxProduct = max(maxProduct, product);
        }
    }

    return maxProduct;
}

int count_factors(int num) {
    int count = 0;
    for (int i = 1; i*i <= num; i++) {
        if (num % i == 0) {
            count += (i*i == num) ? 1 : 2;
        }
    }
    return count;
}

// Problem 12: 第一个有超过n个因子的三角数
int problem12(int n) {
    int tri = 0;
    for (int i = 1; ; i++) {
        tri += i;
        if (count_factors(tri) > n) return tri;
    }
}

// Problem 13: 求a个k位数的和的前n位
char* problem13(int a, int k, int n, const char** numbers) {
    // 初始化累加数组（从低位到高位存储）
    const int max_digits = k + 100; // 预留足够空间处理进位
    int* sum = (int*)calloc(max_digits, sizeof(int));
    
    // 累加所有数字的各位
    for (int i = 0; i < a; i++) {
        const char* num = numbers[i];
        for (int j = 0; j < k; j++) {
            int pos = k - 1 - j; // 从数字字符串的末位开始取（对应个位）
            sum[j] += num[pos] - '0';
        }
    }

    // 处理进位
    int carry = 0;
    for (int i = 0; i < max_digits; i++) {
        sum[i] += carry;
        carry = sum[i] / 10;
        sum[i] %= 10;
    }

    // 找到最高有效位
    int highest = max_digits - 1;
    while (highest > 0 && sum[highest] == 0) highest--;

    // 提取前n位
    char* result = (char*)malloc(n + 1);
    int result_idx = 0;
    for (int i = 0; i < n && highest - i >= 0; i++) {
        result[result_idx++] = sum[highest - i] + '0';
    }
    result[result_idx] = '\0';

    free(sum);
    return result;
}

int collatz_length(long long num) {
    int len = 1;
    while (num != 1) {
        num = (num % 2 == 0) ? num/2 : 3*num + 1;
        len++;
    }
    return len;
}

// Problem 14: 最长Collatz序列（起始数 < n）
int problem14(int n) {
    int max_len = 0, max_num = 0;
    for (int i = 1; i < n; i++) {
        int len = collatz_length(i);
        if (len > max_len) {
            max_len = len;
            max_num = i;
        }
    }
    return max_num;
}

// Problem 15: 网格路径数（n×n网格）
long long problem15(int n) {
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result = result * (n + i) / i;
    }
    return result;
}

// Problem 16: 2^1000的数字和
int problem16(int exponent) {
    int digits[400] = {1}; // 足够存储2^1000
    int length = 1;

    for (int i = 0; i < exponent; i++) {
        int carry = 0;
        for (int j = 0; j < length; j++) {
            int temp = digits[j] * 2 + carry;
            digits[j] = temp % 10;
            carry = temp / 10;
        }
        if (carry > 0) digits[length++] = carry;
    }

    int sum = 0;
    for (int i = 0; i < length; i++) sum += digits[i];
    return sum;
}

const char* ones[] = {"", "one", "two", "three", "four", "five", 
                     "six", "seven", "eight", "nine"};
const char* teens[] = {"ten", "eleven", "twelve", "thirteen", 
                      "fourteen", "fifteen", "sixteen", 
                      "seventeen", "eighteen", "nineteen"};
const char* tens[] = {"", "", "twenty", "thirty", "forty", 
                     "fifty", "sixty", "seventy", "eighty", "ninety"};

int count_letters(int num) {
    if (num == 0) return 0;
    if (num >= 1000) return strlen("onethousand") + count_letters(num % 1000);
    if (num >= 100) {
        int part = strlen(ones[num/100]) + strlen("hundred");
        if (num % 100 != 0) part += 3; // "and"
        return part + count_letters(num % 100);
    }
    if (num >= 20) return strlen(tens[num/10]) + count_letters(num % 10);
    if (num >= 10) return strlen(teens[num-10]);
    return strlen(ones[num]);
}

// Problem 17: 1到n的数字的英文字母总数
int problem17(int n) {
    int total = 0;
    for (int i = 1; i <= n; i++) total += count_letters(i);
    return total;
}

// Problem 18: 三角形数组最大路径和
int problem18(int triangle[15][15], int rows) {
    // 从倒数第二层开始向上计算
    for (int i = rows - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            // 当前节点的最大路径和为下一层左右节点的较大值加上当前值
            int left = triangle[i+1][j];
            int right = triangle[i+1][j+1];
            triangle[i][j] += (left > right) ? left : right;
        }
    }
    return triangle[0][0];
}

// Problem 19: 20世纪（1901-2000）每月1日是星期日的数量
int problem19() {
    int day = 1; // 1900-01-01是星期一（假设）
    int count = 0;
    for (int year = 1900; year <= 2000; year++) {
        for (int month = 1; month <= 12; month++) {
            if (year >= 1901 && day % 7 == 0) count++;
            // 计算下个月的天数
            int days;
            switch (month) {
                case 2: 
                    days = (year%4 == 0 && (year%100 != 0 || year%400 == 0)) ? 29 : 28;
                    break;
                case 4: case 6: case 9: case 11: days = 30; break;
                default: days = 31;
            }
            day += days;
        }
    }
    return count;
}

// Problem 20: n! 的数字和
int problem20(int n) {
    int digits[1000] = {1}; // 足够存储1000!
    int length = 1;

    for (int i = 2; i <= n; i++) {
        int carry = 0;
        for (int j = 0; j < length; j++) {
            int temp = digits[j] * i + carry;
            digits[j] = temp % 10;
            carry = temp / 10;
        }
        while (carry > 0) {
            digits[length++] = carry % 10;
            carry /= 10;
        }
    }

    int sum = 0;
    for (int i = 0; i < length; i++) sum += digits[i];
    return sum;
}