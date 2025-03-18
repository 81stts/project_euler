#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define MAXN 1000001

int num[MAXN];      // 标记是否为素数（0表示素数，1表示合数）
int prime[MAXN];    // 存储素数
int cnt = 0;        // 素数数量

// 欧拉筛法生成素数表
void _sieve() {
    for (int i = 2; i < MAXN; i++) {
        if (!num[i]) prime[cnt++] = i;
        for (int j = 0; j < cnt && prime[j] * i < MAXN; j++) {
            num[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

// 计算数字 x 中各个数字出现的次数
void calNum(int x, int* cal) {
    while (x) {
        cal[x % 10]++;
        x /= 10;
    }
}

// 判断数字 x 是否满足替换条件
bool isRight(int x, int digit, int cal) {
    int num1[10], len = 0;
    while (x) {
        num1[len++] = x % 10; // 将数字 x 的每一位存储到 num1 中
        x /= 10;
    }

    // 遍历所有可能的替换位置组合
    for (int a = 0; a < cal; a++) {
        for (int b = a + 1; b < cal; b++) {
            for (int c = b + 1; c < cal; c++) {
                int tot = 1; // 记录满足条件的数字数量
                for (int i = digit + 1; i <= 9; i++) {
                    int num2 = 0;
                    for (int j = len - 1, th = 0; j >= 0; j--) {
                        num2 *= 10;
                        if (num1[j] != digit) {
                            num2 += num1[j];
                        } else {
                            if (th == a || th == b || th == c) {
                                num2 += i; // 替换为新的数字
                            } else {
                                num2 += num1[j]; // 保留原数字
                            }
                            th++;
                        }
                    }
                    if (num[num2] == 0) tot++; // 如果替换后的数字是素数，计数器加1
                }
                if (tot >= 8) return true; // 如果满足条件的数字数量 >= 8，返回 true
            }
        }
    }
    return false;
}

// Problem 51: 最小质数替换模式
int problem51() {
    _sieve(); // 生成素数表

    int cal[10]; // 记录数字中各个数字出现的次数
    int out = 0;
    for (int i = 0; i < cnt; i++) {
        int t = 0;
        memset(cal, 0, sizeof(cal)); // 初始化 cal 数组
        calNum(prime[i], cal);       // 计算当前素数的数字分布

        // 检查是否有数字出现次数 >= 3，并尝试替换
        for (int j = 0; j < 3; j++) {
            if (cal[j] >= 3 && isRight(prime[i], j, cal[j])) {
                out = prime[i]; // 输出符合条件的素数
                t = 1;
                break;
            }
        }
        if (t) break; // 如果找到符合条件的素数，退出循环
    }

    return out;
}

// 将数字转换为字符串并排序
void sort_digits_1(int num, char* buffer) {
    sprintf(buffer, "%d", num);
    int len = strlen(buffer);
    // 冒泡排序字符
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (buffer[i] > buffer[j]) {
                char temp = buffer[i];
                buffer[i] = buffer[j];
                buffer[j] = temp;
            }
        }
    }
}

// 检查x是否满足条件
int check(int x) {
    char s_x[20];
    sort_digits_1(x, s_x);
    for (int i = 2; i <= 6; i++) {
        int multiple = x * i;
        char s_multi[20];
        sort_digits_1(multiple, s_multi);
        if (strcmp(s_x, s_multi) != 0) {
            return 0;
        }
    }
    return 1;
}

// Problem 52: 最小排列倍数
int problem52() {
    // 遍历六位数范围（满足6x的位数与x相同）
    int result = 0;
    for (int x = 100000; x <= 166666; x++) {
        if (check(x)) {
            result = x;
            break;
        }
    }
    return result;
}

// Problem 53: 组合数超过百万
int problem53(int limit) {
    int count = 0;
    for (int n = 1; n <= 100; n++) {
        int C = 1;
        for (int r = 1; r <= n/2; r++) {
            C = C * (n - r + 1) / r;
            if (C > limit) {
                count += (n - 2*r + 1); // 对称性优化
                break;
            }
        }
    }
    return count;
}

#define HAND_SIZE 5

// 牌面值映射
int cardValue(char card) {
    switch (card) {
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'T': return 10;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
        case 'A': return 14;
        default: return 0;
    }
}

// 比较函数，用于排序
int compare_1(const void *a, const void *b) {
    return cardValue(*(char*)a) - cardValue(*(char*)b);
}

// 判断是否为同花
int isFlush(char *hand) {
    char suit = hand[1];
    for (int i = 3; i < HAND_SIZE * 3; i += 3) {
        if (hand[i] != suit) return 0;
    }
    return 1;
}

// 判断是否为顺子
int isStraight(char *hand) {
    int values[HAND_SIZE];
    for (int i = 0; i < HAND_SIZE; i++) {
        values[i] = cardValue(hand[i * 3]);
    }
    qsort(values, HAND_SIZE, sizeof(int), compare_1);
    for (int i = 0; i < HAND_SIZE - 1; i++) {
        if (values[i] + 1 != values[i + 1]) return 0;
    }
    return 1;
}

// 获取牌型
int getHandType(char *hand) {
    int valueCount[15] = {0};
    for (int i = 0; i < HAND_SIZE; i++) {
        valueCount[cardValue(hand[i * 3])]++;
    }
    
    int pairs = 0, threeOfAKind = 0, fourOfAKind = 0;
    for (int i = 2; i <= 14; i++) {
        if (valueCount[i] == 2) pairs++;
        if (valueCount[i] == 3) threeOfAKind = 1;
        if (valueCount[i] == 4) fourOfAKind = 1;
    }
    
    if (isStraight(hand) && isFlush(hand)) {
        if (cardValue(hand[0]) == 10) return 9; // Royal Flush
        return 8; // Straight Flush
    }
    if (fourOfAKind) return 7; // Four of a Kind
    if (threeOfAKind && pairs == 1) return 6; // Full House
    if (isFlush(hand)) return 5; // Flush
    if (isStraight(hand)) return 4; // Straight
    if (threeOfAKind) return 3; // Three of a Kind
    if (pairs == 2) return 2; // Two Pairs
    if (pairs == 1) return 1; // One Pair
    return 0; // High Card
}

// 比较两手牌
int compareHands(char *hand1, char *hand2) {
    int type1 = getHandType(hand1);
    int type2 = getHandType(hand2);
    if (type1 != type2) return type1 > type2;
    
    // 如果牌型相同，比较牌面大小
    int values1[HAND_SIZE], values2[HAND_SIZE];
    for (int i = 0; i < HAND_SIZE; i++) {
        values1[i] = cardValue(hand1[i * 3]);
        values2[i] = cardValue(hand2[i * 3]);
    }
    qsort(values1, HAND_SIZE, sizeof(int), compare_1);
    qsort(values2, HAND_SIZE, sizeof(int), compare_1);
    
    for (int i = HAND_SIZE - 1; i >= 0; i--) {
        if (values1[i] != values2[i]) return values1[i] > values2[i];
    }
    return 0; // 两手牌完全相同
}

// Problem 54: 扑克胜负统计
int problem54(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return 1;
    }
    
    char line[50];
    int player1Wins = 0;
    while (fgets(line, sizeof(line), file)) {
        char hand1[16], hand2[16];
        strncpy(hand1, line, 15);
        hand1[15] = '\0';
        strncpy(hand2, line + 15, 15);
        hand2[15] = '\0';
        
        if (compareHands(hand1, hand2)) {
            player1Wins++;
        }
    }
    
    fclose(file);
    return player1Wins;
}

// 反转数字
long long reverseNumber(long long n) {
    long long reversed = 0;
    while (n > 0) {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }
    return reversed;
}

// 判断是否为回文数
bool isPalindrome(long long n) {
    return n == reverseNumber(n);
}

// 反转并相加
long long reverseAndAdd(long long n) {
    return n + reverseNumber(n);
}

// 判断是否为Lychrel数
bool isLychrelNumber(int n) {
    long long current = n;
    for (int i = 0; i < 50; i++) { // 进行50次迭代
        current = reverseAndAdd(current);
        if (isPalindrome(current)) {
            return false; // 形成回文数，不是Lychrel数
        }
    }
    return true; // 50次迭代后仍未形成回文数，是Lychrel数
}

// Problem 55: Lychrel数数量
int problem55(int limit) {
    int count = 0;
    for (int i = 1; i < limit; i++) {
        if (isLychrelNumber(i)) {
            count++;
        }
    }
    return count;
}

#define MAX_DIGITS 1000 // 定义最大位数

// 计算base的exp次幂，结果存储在result数组中
void bigPower(int base, int exp, int result[]) {
    while (exp > 0) {
        // 乘以base
        for (int i = 0; i < MAX_DIGITS; i++) {
            result[i] *= base;
        }
        // 处理进位
        for (int i = 0; i < MAX_DIGITS - 1; i++) {
            result[i + 1] += result[i] / 10;
            result[i] %= 10;
        }
        exp--;
    }
}
// 计算存储在数组中的大数的各位数字和
int digitSum(int num[]) {
    int sum = 0;
    for (int i = 0; i < MAX_DIGITS; i++) {
        sum += num[i];
    }
    return sum;
}

// Problem 56: 最大数字和
int problem56(int limit) {
    int maxSum = 0;
    int result[MAX_DIGITS] = {0}; // 用于存储大数结果的数组

    for (int a = 1; a < limit; a++) {
        for (int b = 1; b < limit; b++) {
            // 初始化结果为1
            memset(result, 0, sizeof(result));
            result[0] = 1;

            // 计算a的b次幂
            bigPower(a, b, result);

            // 计算数字和
            int sum = digitSum(result);
            if (sum > maxSum) {
                maxSum = sum;
            }
        }
    }

    return maxSum;
}

#define MAX_DIGITS_2 3000

typedef struct {
    char digits[MAX_DIGITS_2]; // 存储各位数字，低位在前
    int length;              // 数字的位数
} BigNum;

// 初始化BigNum为整数
void initBigNum(int num, BigNum *b) {
    memset(b->digits, 0, sizeof(b->digits));
    b->length = 0;
    if (num == 0) {
        b->digits[0] = 0;
        b->length = 1;
        return;
    }
    int i = 0;
    while (num > 0) {
        b->digits[i] = num % 10;
        num /= 10;
        i++;
    }
    b->length = i;
}

// 大数加法
BigNum addBigNums(BigNum a, BigNum b) {
    BigNum result;
    memset(result.digits, 0, sizeof(result.digits));
    int carry = 0;
    int max_len = (a.length > b.length) ? a.length : b.length;
    result.length = 0;

    for (int i = 0; i < max_len; i++) {
        int sum = a.digits[i] + b.digits[i] + carry;
        result.digits[i] = sum % 10;
        carry = sum / 10;
        result.length++;
    }

    if (carry > 0) {
        result.digits[result.length] = carry;
        result.length++;
    }
    return result;
}

// 大数乘以2
BigNum multiplyByTwo(BigNum a) {
    BigNum result;
    memset(result.digits, 0, sizeof(result.digits));
    int carry = 0;
    result.length = 0;

    for (int i = 0; i < a.length; i++) {
        int product = a.digits[i] * 2 + carry;
        result.digits[i] = product % 10;
        carry = product / 10;
        result.length++;
    }

    if (carry > 0) {
        result.digits[result.length] = carry;
        result.length++;
    }
    return result;
}

// Problem 57: 平方根近似展开
int problem57(int limit) {
    BigNum prev_prev_n, prev_n, prev_prev_d, prev_d;
    initBigNum(3, &prev_prev_n); // 初始分子：n=1时3/2
    initBigNum(7, &prev_n);      // 初始分子：n=2时7/5
    initBigNum(2, &prev_prev_d); // 初始分母：n=1时3/2
    initBigNum(5, &prev_d);      // 初始分母：n=2时7/5

    int count = 0;
    for (int i = 3; i <= limit; i++) {
        // 计算当前分子：current_n = 2*prev_n + prev_prev_n
        BigNum temp_n = multiplyByTwo(prev_n);
        BigNum current_n = addBigNums(temp_n, prev_prev_n);

        // 计算当前分母：current_d = 2*prev_d + prev_prev_d
        BigNum temp_d = multiplyByTwo(prev_d);
        BigNum current_d = addBigNums(temp_d, prev_prev_d);

        // 比较位数
        if (current_n.length > current_d.length) {
            count++;
        }

        // 更新前两次的值
        memcpy(&prev_prev_n, &prev_n, sizeof(BigNum));
        memcpy(&prev_n, &current_n, sizeof(BigNum));
        memcpy(&prev_prev_d, &prev_d, sizeof(BigNum));
        memcpy(&prev_d, &current_d, sizeof(BigNum));
    }
    return count;
}

bool is_prime2(int num) {
    if (num <= 1) return false;
    for (int i = 2; i*i <= num; i++)
        if (num % i == 0) return false;
    return true;
}

// Problem 58: 素数螺旋层
int problem58(double ratio) {
    int primes = 0, total = 1;
    for (int layer = 3; ; layer += 2) {
        // 计算四个角数
        for (int i = 0; i < 4; i++) {
            int corner = layer*layer - i*(layer-1);
            if (is_prime2(corner)) primes++;
        }
        total += 4;
        if ((double)primes / total < ratio) 
            return layer;
    }
}

// Problem 59: XOR解密
int problem59(const char *cipher) {
    FILE *file = fopen(cipher, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int code[1000];
    int index = 0;
    while (fscanf(file, "%d,", &code[index]) != EOF) {
        index++;
    }
    fclose(file);

    int key[3];
    int maxSum = 0;
    char *bestKey = malloc(4);
    bestKey[3] = '\0';

    for (key[0] = 'a'; key[0] <= 'z'; key[0]++) {
        for (key[1] = 'a'; key[1] <= 'z'; key[1]++) {
            for (key[2] = 'a'; key[2] <= 'z'; key[2]++) {
                int sum = 0;
                for (int i = 0; i < index; i++) {
                    int decrypted = code[i] ^ key[i % 3];
                    sum += decrypted;
                }
                if (sum > maxSum) {
                    maxSum = sum;
                    bestKey[0] = key[0];
                    bestKey[1] = key[1];
                    bestKey[2] = key[2];
                }
            }
        }
    }
    free(bestKey);

    return maxSum;
}

#define MAX_PRIME 10000  // 生成素数的上限
#define TARGET_SIZE 5    // 需要找到的素数个数

int primes_1[MAX_PRIME];   // 存储生成的素数
int primes_count = 0;    // 实际生成的素数数量
int min_sum = INT_MAX;   // 最小和

// 生成素数列表（埃拉托斯特尼筛法）
void sieve1() {
    bool is_prime[MAX_PRIME + 1];
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= MAX_PRIME; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAX_PRIME; j += i) {
                is_prime[j] = false;
            }
        }
    }
    primes_count = 0;
    for (int i = 2; i <= MAX_PRIME; i++) {
        if (is_prime[i]) {
            primes_1[primes_count++] = i;
        }
    }
}

// Miller-Rabin素数测试
bool is_prime_miller(unsigned long long n, int iterations) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;

    unsigned long long d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    for (int i = 0; i < iterations; i++) {
        unsigned long long a = 2 + rand() % (n - 3);
        unsigned long long x = 1;
        unsigned long long current = a;
        unsigned long long pow = d;
        // 快速幂计算 a^d mod n
        while (pow > 0) {
            if (pow % 2 == 1) {
                x = (x * current) % n;
            }
            current = (current * current) % n;
            pow /= 2;
        }
        if (x == 1 || x == n - 1) continue;

        for (int j = 0; j < s - 1; j++) {
            x = (x * x) % n;
            if (x == n - 1) break;
        }
        if (x != n - 1) return false;
    }
    return true;
}

// 拼接两个数并检查是否为素数
bool are_concatenatable(int a, int b) {
    char str_a[10], str_b[10];
    sprintf(str_a, "%d", a);
    sprintf(str_b, "%d", b);
    char str_ab[20], str_ba[20];
    strcpy(str_ab, str_a);
    strcat(str_ab, str_b);
    strcpy(str_ba, str_b);
    strcat(str_ba, str_a);

    unsigned long long ab = strtoull(str_ab, NULL, 10);
    unsigned long long ba = strtoull(str_ba, NULL, 10);

    return is_prime_miller(ab, 5) && is_prime_miller(ba, 5);
}

// 回溯搜索符合条件的素数集合
void backtrack(int* current_set, int size, int start, int current_sum) {
    if (size == TARGET_SIZE) {
        if (current_sum < min_sum) {
            min_sum = current_sum;
        }
        return;
    }

    for (int i = start; i < primes_count; i++) {
        int prime = primes_1[i];
        // 剪枝：如果当前和加上剩余可能的最小和已经超过已知最小值，停止
        if (current_sum + prime * (TARGET_SIZE - size) >= min_sum) {
            break;
        }
        bool valid = true;
        for (int j = 0; j < size; j++) {
            if (!are_concatenatable(current_set[j], prime)) {
                valid = false;
                break;
            }
        }
        if (valid) {
            current_set[size] = prime;
            backtrack(current_set, size + 1, i + 1, current_sum + prime);
        }
    }
}

// Problem 60: 素数对拼接
int problem60() {
    srand(time(NULL));
    sieve1();

    int current_set[TARGET_SIZE];
    backtrack(current_set, 0, 0, 0);

    return min_sum;
}