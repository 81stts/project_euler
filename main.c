#include "1-10.c"
#include "11-20.c"
#include "21-30.c"
#include "31-40.c"

int main() {
    printf("Problem 1: %d\n", problem1(1000));       // 233168
    printf("Problem 2: %d\n", problem2(4000000));    // 4613732
    printf("Problem 3: %lld\n", problem3(13195));    // 29
    printf("Problem 4: %d\n", problem4(2));          // 9009
    printf("Problem 5: %d\n", problem5(20));         // 232792560
    printf("Problem 6: %d\n", problem6(100));        // 25164150
    printf("Problem 7: %d\n", problem7(10001));      // 104743
    printf("Problem 8: %d\n", problem8(13));         // 2040733440
    printf("Problem 9: %d\n", problem9(1000));       // 31875000
    printf("Problem 10: %lld\n", problem10(2000000)); // 142913828922
    int grid[4][4] = {
        {8, 2, 22, 97},
        {49, 49, 99, 40},
        {81, 4, 32, 17},
        {32, 33, 32, 9}
    };
    printf("Problem 11: %d\n", problem11(grid, 4, 1));
    printf("Problem 12: %d\n", problem12(500));              // 76576500
    const char* numbers[] = {
        "3719",
        "2156",
        "9843"
    };
    printf("Problem 13: %s\n", problem13(3, 4, 3, numbers)); // 157
    printf("Problem 14: %d\n", problem14(15));               // 9
    printf("Problem 15: %lld\n", problem15(20));             // 137846528820
    printf("Problem 16: %d\n", problem16(1000));             // 1366
    printf("Problem 17: %d\n", problem17(1000));             // 21124
    int triangle[15][15] = {
        {75},
        {95, 64},
        {17, 47, 82},
        {18, 35, 87, 10},
        {20,  4, 82, 47, 65},
        {19,  1, 23, 75,  3, 34},
        {88,  2, 77, 73,  7, 63, 67},
        {99, 65,  4, 28,  6, 16, 70, 92},
        {41, 41, 26, 56, 83, 40, 80, 70, 33},
        {41, 48, 72, 33, 47, 32, 37, 16, 94, 29},
        {53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14},
        {70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57},
        {91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48},
        {63, 66,  4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31},
        { 4, 62, 98, 27, 23,  9, 70, 98, 73, 93, 38, 53, 60,  4, 23}
    };
    printf("Problem 18: %d\n", problem18(triangle, 15));     // 输出1074
    printf("Problem 19: %d\n", problem19());                 // 输出171
    printf("Problem 20: %d\n", problem20(10));               // 输出27
    printf("Problem 21: %d\n", problem21(10000));      // 31626
    char* names[] = {
        "COLIN",
        "JOHN",
        "MARY",
        "SARAH"
    };
    printf("Problem 22: %d\n", problem22(names, 4));   // 506
    printf("Problem 23: %d\n", problem23(28123));      // 4179871
    char digits[] = "0123456789\0";
    problem24(1000000, digits, 10);
    printf("Problem 24: %s\n", digits);                // 0645193872
    printf("Problem 25: %d\n", problem25(1000));       // 4782
    printf("Problem 26: %d\n", problem26(1000));       // 983
    printf("Problem 27: %d\n", problem27(1000));       // -59231
    printf("Problem 28: %d\n", problem28(1001));       // 669171001
    printf("Problem 29: %d\n", problem29(100));        // 9183
    printf("Problem 30: %d\n", problem30(5));          // 443839
    return 0;
}