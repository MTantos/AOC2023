#include <stdio.h>

#define SIZE 60

int str_cmp(char* s1, char* s2) {
    int i=0;
    while (s2[i]) {
        if (s1[i] == '\0' || s1[i] != s2[i]) return 0;
        i++;
    }
    return 1;
}

int get_num(char* s, int i) {
    // Part 1
    if (isdigit(s[i])) return s[i] - '0';
    // Part2
    if (str_cmp(s+i, "one")) return 1;
    if (str_cmp(s+i, "two")) return 2;
    if (str_cmp(s+i, "three")) return 3;
    if (str_cmp(s+i, "four")) return 4;
    if (str_cmp(s+i, "five")) return 5;
    if (str_cmp(s+i, "six")) return 6;
    if (str_cmp(s+i, "seven")) return 7;
    if (str_cmp(s+i, "eight")) return 8;
    if (str_cmp(s+i, "nine")) return 9;
    return 0;
}

int main(int argc, char const *argv[])
{
    FILE *fp;
    char line[SIZE];
    int i, c, f, l, sum;
    sum = 0;

    fp = fopen("../input/day1.txt", "r");
    if (fp == NULL) {
        perror("Error in opening file");
        return(-1);
    }

    while (fgets(line, SIZE, fp)) {
        i = f = 0;
        while (line[i] != '\0') {
            c = get_num(line, i);
            if (c) {
                f = f ? f : c;
                l = c;
            }
            i++;
        }
        sum += f*10 + l;
    }
    printf("Sum of calibration values: %d\n", sum);

    fclose(fp);
    return 0;
}
