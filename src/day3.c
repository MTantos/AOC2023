#include <stdio.h>

#define m 140
#define n 142

int issymbol(char c) {
    return !(isdigit(c) || c == '.');
}

// Part 1
int getparts(char schematic[][m], int i, int j) {
    int k, l, val, num;
    val = 0;
    for (k = i - 1; k < i + 2; k++) {
        for (l = j - 1; l < j + 2; l++) {
            num = 0;
            if (isdigit(schematic[k][l])) {
                while ((l > 0) && isdigit(schematic[k][l-1])) l--;
                while (isdigit(schematic[k][l]) && (l < m)) {
                    num *= 10;
                    num += schematic[k][l] - '0';
                    l++;
                }
                val += num;
            }
        }
    }
    return val;
}

// Part 2
int getratio(char schematic[][m], int i, int j) {
    int k, l, ratio, num;
    ratio = 0;
    for (k = i - 1; k < i + 2; k++) {
        for (l = j - 1; l < j + 2; l++) {
            num = 0;
            if (isdigit(schematic[k][l])) {
                while ((l > 0) && isdigit(schematic[k][l-1])) l--;
                while (isdigit(schematic[k][l]) && (l < m)) {
                    num *= 10;
                    num += schematic[k][l] - '0';
                    l++;
                }
                if (ratio == 0) ratio = num;
                else return ratio * num;
            }
        }
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    FILE *fp;
    char schematic[m][m];
    int i, j, sum, ratio;

    fp = fopen("../input/day3.txt", "r");
    if (fp == NULL) {
        perror("Error in opening file");
        return(-1);
    }
    for (i = 0; i < m; i++) fgets(schematic[i], n, fp);
    fclose(fp);

    // Part 1
    sum = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < m; j++) {
            if (issymbol(schematic[i][j])) {
                sum += getparts(schematic, i, j);
            }
        }
    }
    printf("Sum of parts: %d\n", sum);

    // Part 2
    ratio = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < m; j++) {
            if (schematic[i][j] == '*') {
                ratio += getratio(schematic, i, j);
            }
        }
    }
    printf("Sum of ratios: %d\n", ratio);

    return 0;
}
