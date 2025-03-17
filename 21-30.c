#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

int sum_proper_divisors(int num) {
    int sum = 1;
    for (int i = 2; i*i <= num; i++) {
        if (num % i == 0) {
            sum += i;
            if (i != num/i) sum += num/i;
        }
    }
    return sum;
}

// Problem 21: 亲和数之和（小于n的所有亲和数对之和）
int problem21(int n) {
    int total = 0;
    for (int a = 2; a < n; a++) {
        int b = sum_proper_divisors(a);
        if (b > a && sum_proper_divisors(b) == a) {
            total += a + b;
        }
    }
    return total;
}

int compare(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

// Problem 22: 姓名得分总和
int problem22(char* names[], int count) {
    qsort(names, count, sizeof(char*), compare);
    int total = 0;
    for (int i = 0; i < count; i++) {
        int sum = 0;
        for (int j = 0; names[i][j]; j++) {
            sum += names[i][j] - 'A' + 1;
        }
        total += sum * (i+1);
    }
    return total;
}

int is_abundant(int num) {
    int sum = sum_proper_divisors(num);
    return sum > num;
}

// Problem 23: 不能表示为两个过剩数之和的正整数之和
int problem23(int limit) {
    int* abundant = (int*)calloc(limit+1, sizeof(int));
    int count = 0;
    for (int i = 12; i <= limit; i++) {
        if (is_abundant(i)) abundant[count++] = i;
    }

    char* expressible = (char*)calloc(limit+1, 1);
    for (int i = 0; i < count; i++) {
        for (int j = i; j < count; j++) {
            int sum = abundant[i] + abundant[j];
            if (sum > limit) break;
            expressible[sum] = 1;
        }
    }

    int total = 0;
    for (int i = 1; i <= limit; i++) {
        if (!expressible[i]) total += i;
    }

    free(abundant);
    free(expressible);
    return total;
}

// Problem 24: 第n个字典序排列
void problem24(int n, char* digits, int len) {
    int factorials[] = {1,1,2,6,24,120,720,5040,40320,362880};
    n--; // 转换为0-based索引

    for (int i = 0; i < len; i++) {
        int fact = factorials[len-1-i];
        int index = n / fact;
        char selected = digits[index];
        
        // 移除已选字符
        memmove(digits+index, digits+index+1, len-i-index);
        digits[len-1-i] = selected;
        
        n %= fact;
    }
}

// Problem 25: 第一个包含n位数字的斐波那契数索引
int problem25(int target_digits) {
    double phi = (1 + sqrt(5)) / 2;
    return (int)ceil((target_digits-1 + log10(5)/2) / log10(phi));
}

int cycle_length(int d) {
    int seen[1000] = {0};
    int remainder = 1, position = 1;
    while (remainder != 0 && !seen[remainder]) {
        seen[remainder] = position++;
        remainder = (remainder * 10) % d;
    }
    return (remainder == 0) ? 0 : position - seen[remainder];
}

// Problem 26: 最长循环节（分母 < n）
int problem26(int limit) {
    int max_len = 0, best_d = 0;
    for (int d = 2; d < limit; d++) {
        int len = cycle_length(d);
        if (len > max_len) {
            max_len = len;
            best_d = d;
        }
    }
    return best_d;
}

int isprime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i*i <= n; i++) 
        if (n%i == 0) return 0;
    return 1;
}

int count_primes(int a, int b) {
    for (int n = 0; ; n++) {
        int val = n*n + a*n + b;
        if (!isprime(val)) return n;
    }
}

// Problem 27: 二次方程素数链
int problem27(int limit) {
    int max_primes = 0, product = 0;
    for (int a = -limit+1; a < limit; a++) {
        for (int b = -limit; b <= limit; b++) {
            int primes = count_primes(a, b);
            if (primes > max_primes) {
                max_primes = primes;
                product = a * b;
            }
        }
    }
    return product;
}

// Problem 28: 螺旋对角线之和
int problem28(int size) { // size为螺旋的边长（奇数）
    int total = 1; // 中心点1
    for (int layer = 3; layer <= size; layer += 2) {
        int corner = layer*layer;
        total += 4*corner - 6*(layer-1);
    }
    return total;
}

typedef struct {
    int base;
    int exponent;
} Factor;

typedef struct {
    Factor factors[20]; // 假设最多20个质因数
    int count;
} PrimeFactors;

// 质因数分解并排序基
PrimeFactors factorize(int n) {
    PrimeFactors result = { .count = 0 };
    if (n <= 1) return result;

    // 分解质因数
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int exp = 0;
            while (n % i == 0) {
                exp++;
                n /= i;
            }
            result.factors[result.count].base = i;
            result.factors[result.count].exponent = exp;
            result.count++;
        }
    }
    if (n > 1) { // 处理剩余的质数
        result.factors[result.count].base = n;
        result.factors[result.count].exponent = 1;
        result.count++;
    }

    // 按基从小到大排序
    for (int i = 0; i < result.count; i++) {
        for (int j = i+1; j < result.count; j++) {
            if (result.factors[i].base > result.factors[j].base) {
                Factor temp = result.factors[i];
                result.factors[i] = result.factors[j];
                result.factors[j] = temp;
            }
        }
    }
    return result;
}

// 生成唯一键字符串，格式如 "2:4;3:2;"
char* generate_key(PrimeFactors pf, int b) {
    char buffer[1024] = {0};
    for (int i = 0; i < pf.count; i++) {
        char part[50];
        sprintf(part, "%d:%d;", pf.factors[i].base, pf.factors[i].exponent * b);
        strcat(buffer, part);
    }
    return strdup(buffer); // 复制字符串以避免覆盖
}

// Problem 29: 不同幂的数量
int problem29(int limit) {
    char** keys = NULL; // 存储唯一键
    int key_count = 0;

    for (int a = 2; a <= limit; a++) {
        PrimeFactors pf = factorize(a);
        for (int b = 2; b <= limit; b++) {
            char* key = generate_key(pf, b);
            // 检查键是否已存在
            int found = 0;
            for (int i = 0; i < key_count; i++) {
                if (strcmp(keys[i], key) == 0) {
                    found = 1;
                    break;
                }
            }
            if (!found) { // 新键则添加
                keys = realloc(keys, (key_count + 1) * sizeof(char*));
                keys[key_count++] = key;
            } else {
                free(key); // 释放重复键的内存
            }
        }
    }

    int result = key_count;
    // 清理内存
    for (int i = 0; i < key_count; i++) free(keys[i]);
    free(keys);
    return result;
}

// Problem 30: 各位数字的五次幂之和
int problem30(int power) {
    int total = 0;
    int upper = pow(9, power) * (power+1); // 计算上限
    for (int num = 2; num <= upper; num++) {
        int sum = 0, temp = num;
        while (temp) {
            int d = temp % 10;
            sum += pow(d, power);
            temp /= 10;
        }
        if (sum == num) total += sum;
    }
    return total;
}