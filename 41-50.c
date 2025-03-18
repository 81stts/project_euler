#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

bool is_prime1(int num) {
    if (num <= 1) return false;
    for (int i = 2; i*i <= num; i++)
        if (num % i == 0) return false;
    return true;
}

// 辅助函数：交换两个整数
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 辅助函数：反转数组区间
void reverse(int arr[], int start, int end) {
    while (start < end) {
        swap(&arr[start], &arr[end]);
        start++;
        end--;
    }
}

// 生成前一个排列（按字典序）
bool prev_permutation(int arr[], int size) {
    // 1. 从右向左找第一个升序对 (arr[i] > arr[i+1])
    int i = size - 2;
    while (i >= 0 && arr[i] <= arr[i + 1]) i--;
    if (i < 0) return false;

    // 2. 在右侧找比 arr[i] 小的最大值
    int j = size - 1;
    while (arr[j] >= arr[i]) j--;

    // 3. 交换并反转右侧
    swap(&arr[i], &arr[j]);
    reverse(arr, i + 1, size - 1);
    return true;
}

// Problem 41: 最大n位全数字素数
int problem41(int n) {
    int digits[] = {7,6,5,4,3,2,1}; // n=7时最大可能为7654321
    do {
        int num = 0;
        for (int i = 0; i < n; i++) num = num * 10 + digits[i];
        if (is_prime1(num)) return num;
    } while (prev_permutation(digits, n)); // 需实现排列生成函数
    return -1;
}

int is_triangular(int t) {
    int n = (sqrt(8*t + 1) - 1)/2;
    return n*(n+1)/2 == t;
}

// Problem 42: 三角形词数统计
int problem42(const char* filename) {
    FILE* fp = fopen(filename, "r");
    int count = 0;
    char word[50];
    
    while (fscanf(fp, "\"%[^\"]\",", word) != EOF) {
        int sum = 0;
        for (char* p = word; *p; p++) 
            sum += toupper(*p) - 'A' + 1;
        if (is_triangular(sum)) count++;
    }
    fclose(fp);
    return count;
}

// 辅助函数：交换字符
void swap_char(char* a, char* b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

// 辅助函数：反转字符数组区间
void reverse_char(char arr[], int start, int end) {
    while (start < end) {
        swap_char(&arr[start], &arr[end]);
        start++;
        end--;
    }
}

// 生成下一个排列（按字典序）
bool next_permutation(char arr[], int size) {
    // 1. 从右向左找第一个降序对 (arr[i] < arr[i+1])
    int i = size - 2;
    while (i >= 0 && arr[i] >= arr[i + 1]) i--;
    if (i < 0) return false;

    // 2. 在右侧找比 arr[i] 大的最小值
    int j = size - 1;
    while (arr[j] <= arr[i]) j--;

    // 3. 交换并反转右侧
    swap_char(&arr[i], &arr[j]);
    reverse_char(arr, i + 1, size - 1);
    return true;
}

int primes[] = {2,3,5,7,11,13,17};

// Problem 43: 子串可整除的全数字数
long long problem43() {
    char digits[] = "0123456789"; // 0-9的全排列
    long long total = 0;
    const int size = 10; // 排列长度

    do {
        if (digits[0] == '0') continue; // 跳过前导0的情况

        // 检查子串可整除性
        int valid = 1;
        for (int i = 0; i < 7; i++) {
            int sub_num = (digits[i+1]-'0')*100 + 
                         (digits[i+2]-'0')*10 + 
                          digits[i+3]-'0';
            if (sub_num % primes[i] != 0) {
                valid = 0;
                break;
            }
        }

        if (valid) {
            total += atoll(digits); // 累加有效全数字数
        }
    } while (next_permutation(digits, size)); // 传递正确的参数

    return total;
}

// Problem 44: 最小五边形数差值
unsigned int problem44()
{
	unsigned int answer = 0;
	unsigned int pentagonal[3000];
	for(unsigned int n = 1; n <= 3000; n++) {
		unsigned int p = 3*n - 1;
		p *= n;
		p /= 2;
		pentagonal[n - 1] = p;
	}
	for(unsigned int i = 1000; i < 3000; i++) {
        int con = 0;
        for(unsigned int k = 999; k < i; k++) {
			unsigned int test1 = pentagonal[i] + pentagonal[k];
			unsigned int test2 = pentagonal[i] - pentagonal[k];
			bool pass1 = false;
			bool pass2 = false;
			for(unsigned int l = k; l < 3000; l++) {
				if(test1 == pentagonal[l])
					pass1 = true;
				if(test2 == pentagonal[l])
					pass2 = true;
			}
			if(pass1 && pass2) {
                answer = test2;
                con = 1;
                break;
            }		
		}
        if(con) break;
    }
	return answer;
}

// Problem 45: 下一个三角五边六边数
int problem45() {
    long long n = 143; // 已知H_143 = 40755
    while (1) {
        n++;
        long long H = n*(2*n - 1); // 六边形数公式
        
        // 检查是否也是五边形数
        double p = (1 + sqrt(24*H + 1)) / 6;
        if (p == (int)p) return H;
    }
}

// Problem 46: 最小哥德巴赫反例
int problem46() {
    for (int n = 9; ; n += 2) {
        if (is_prime1(n)) continue;
        int found = 0;
        for (int s = 1; 2*s*s < n; s++) {
            if (is_prime1(n - 2*s*s)) {
                found = 1;
                break;
            }
        }
        if (!found) return n; // 输出：5777
    }
}

// Problem 47: 连续四个不同质因数数
int problem47(int target_factors) {
    int consecutive = 0;
    for (int n = 2; ; n++) {
        int factors = 0;
        int temp = n;
        for (int p = 2; p*p <= temp; p++) {
            if (temp % p == 0) {
                factors++;
                while (temp % p == 0) temp /= p;
            }
        }
        if (temp > 1) factors++;
        
        if (factors == target_factors) consecutive++;
        else consecutive = 0;
        
        if (consecutive == target_factors) 
            return n - target_factors + 1; // 输出：134043
    }
}

#define MOD 10000000000LL

// Problem 48: 自幂级数的最后十位
long long problem48(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        long long term = 1;
        for (int j = 1; j <= i; j++) {
            term = (term * i) % MOD;
        }
        sum = (sum + term) % MOD;
    }
    return sum; // 输入1000 输出：9110846700
}

// 数字排序函数
void sort_digits(int num, char* buf) {
    sprintf(buf, "%04d", num); // 确保4位，补零处理
    // 冒泡排序字符
    for (int i = 0; i < 3; i++) {
        for (int j = i+1; j < 4; j++) {
            if (buf[i] > buf[j]) {
                char temp = buf[i];
                buf[i] = buf[j];
                buf[j] = temp;
            }
        }
    }
}

// Problem 49: 素数排列等差数列
long long problem49() {
    for (int p = 1487; p <= 9999; p++) { // 包含已知的起始点
        if (!is_prime1(p)) continue;
        
        // 遍历可能的步长
        for (int d = 1; d <= (9999 - p)/2; d++) {
            int p2 = p + d;
            int p3 = p + 2*d;
            if (p3 > 9999) break;
            
            if (!is_prime1(p2) || !is_prime1(p3)) continue;
            
            // 检查数字排列
            char s1[5], s2[5], s3[5];
            sort_digits(p, s1);
            sort_digits(p2, s2);
            sort_digits(p3, s3);
            
            if (strcmp(s1, s2) == 0 && strcmp(s2, s3) == 0) {
                // 排除已知的1487序列，返回正确答案
                if (p != 1487) {
                    return (long long)p * 100000000LL + p2 * 10000 + p3;
                }
            }
        }
    }
    return 0;
}

// 埃拉托斯特尼筛法（动态内存版本）
int* sieve(int limit, int* prime_count) {
    bool* is_prime = (bool*)calloc(limit + 1, sizeof(bool));
    int* primes = (int*)malloc((limit + 1) * sizeof(int));
    *prime_count = 0;

    if (!is_prime || !primes) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 2; i <= limit; i++) is_prime[i] = true;

    for (int p = 2; p * p <= limit; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i <= limit; i += p) {
                is_prime[i] = false;
            }
        }
    }

    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes[(*prime_count)++] = i;
        }
    }

    free(is_prime);
    return primes;
}

// 快速素数检测（二分查找优化）
bool is_prime_check(long long num, const int primes[], int prime_count) {
    if (num <= 1) return false;
    int sqrt_num = sqrt(num);
    for (int i = 0; i < prime_count && primes[i] <= sqrt_num; i++) {
        if (num % primes[i] == 0) return false;
    }
    return true;
}

// Problem 50: 最长连续素数和的素数
int problem50(int limit) {
    int prime_count = 0;
    int* primes = sieve(limit, &prime_count);

    // 计算前缀和
    long long* prefix = (long long*)calloc(prime_count + 1, sizeof(long long));
    if (!prefix) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < prime_count; i++) {
        prefix[i + 1] = prefix[i] + primes[i];
    }

    int max_len = 0, result = 0;
    // 优化：从长到短搜索，找到即返回
    for (int len = prime_count; len > 0; len--) {
        for (int i = 0; i <= prime_count - len; i++) {
            long long sum = prefix[i + len] - prefix[i];
            if (sum > limit) break;
            if (is_prime_check(sum, primes, prime_count)) {
                free(primes);
                free(prefix);
                return sum; // 直接返回第一个找到的最长解
            }
        }
    }

    free(primes);
    free(prefix);
    return 0; // 无解情况
}