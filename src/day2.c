#include <stdio.h>

#define SIZE 160

// Part 1
int check_game(char* s) {
    const int r_max = 12, g_max = 13, b_max = 14;
    int game_num, i, val;
    i = 5;
    val = 0;
    game_num = s[i++] - '0';
    while (s[i]!=':') game_num = game_num * 10 + s[i++] - '0';
    i++; // Space after :
    while (s[i]) {
        if (isdigit(s[i])) {
            val = val * 10 + s[i] - '0';
        } else if (s[i] == 'b') {
            if (val > b_max) return 0;
            i += 4;
            val = 0;
        } else if (s[i] == 'r') {
            if (val > r_max) return 0;
            i += 3;
            val = 0;
        } else if (s[i] == 'g') {
            if (val > g_max) return 0;
            i += 5;
            val = 0;
        }
        i++;
    }
    return game_num;
}

// Part 2
int get_power(char* s) {
    int i, val, b_max, r_max, g_max;
    i = 6;
    val = 0;
    while (s[i]!=':') i++;
    i++; // Space after :
    b_max = r_max = g_max = 1;
    while (s[i]) {
        if (isdigit(s[i])) {
            val = val * 10 + s[i] - '0';
        } else if (s[i] == 'b') {
            if (val > b_max) b_max = val;
            i += 4;
            val = 0;
        } else if (s[i] == 'r') {
            if (val > r_max) r_max = val;
            i += 3;
            val = 0;
        } else if (s[i] == 'g') {
            if (val > g_max) g_max = val;
            i += 5;
            val = 0;
        }
        i++;
    }
    return b_max * r_max * g_max;
}

int main(int argc, char const *argv[])
{
    FILE *fp;
    char line[SIZE];
    int r, g, b, sum, power_sum;
    
    sum = power_sum = 0;

    fp = fopen("../input/day2.txt", "r");
    if (fp == NULL) {
        perror("Error in opening file");
        return(-1);
    }

    while (fgets(line, SIZE, fp)) {
        sum += check_game(line);
        power_sum += get_power(line);
    }
    printf("Sum of possible game IDs: %d\n", sum);
    printf("Sum of powers: %d\n", power_sum);

    fclose(fp);
    return 0;
}
