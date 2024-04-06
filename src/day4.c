#include <stdio.h>
#include <stdint.h>

#define NUM_WINS 10
#define NUM_NUMS 25
#define NUM_CARDS 220
#define LINE_LENGTH 118

typedef struct Card {
    uint8_t wins[NUM_WINS];
    uint8_t nums[NUM_NUMS];
} Card;

void parse_input(Card* cards, FILE* input) {
    char line[LINE_LENGTH+1];
    int i, j, offset;
    i = 0;
    while (fgets(line, LINE_LENGTH, input)) {
        for (j = 0; j < NUM_WINS; j++) {
            cards[i].wins[j] = atoi(line+10 + j*3);
        }
        for (j = 0; j < NUM_NUMS; j++) {
            offset = 42 + j*3;
            cards[i].nums[j] = atoi(line+offset);
        }
        i++;
    }
}

// Part 1
uint16_t get_points(Card* cards, int n) {
    int i, j, k, card_score;
    uint16_t result = 0;
    for (i = 0; i < n; i++) {
        card_score = 0;
        for (j = 0; j < NUM_WINS; j++) {
            for (k = 0; k < NUM_NUMS; k++) {
                if (cards[i].wins[j] == cards[i].nums[k]) {
                    card_score = card_score == 0 ? 1 : card_score * 2;
                    break;
                }
            }
        }
        result += card_score;
    }
    return result;
}

// Part 2
uint32_t get_scratchcards(Card* cards, int n) {
    unsigned int copies[NUM_WINS], result, copy;
    uint8_t i, j, k, l, win_count;
    for (l = 0; l < NUM_WINS; l++) {
        copies[l] = 1;
    }
    result = l = 0;
    for (i = 0; i < n; i++) {
        win_count = 0;
        for (j = 0; j < NUM_WINS; j++) {
            for (k = 0; k < NUM_NUMS; k++) {
                if (cards[i].wins[j] == cards[i].nums[k]) {
                    win_count++;
                    break;
                }
            }
        }
        result += copy = copies[l];
        copies[l] = 1;
        l = l == (NUM_WINS - 1) ? 0 : l + 1;
        for (j = 0; j < win_count; j++) {
            copies[(l + j) % NUM_WINS]+= copy;
        }
    }
    return result;
}

int main(int argc, char const *argv[])
{
    FILE *fp;
    Card cards[NUM_CARDS];
    uint32_t points, card_count;

    fp = fopen("../input/day4.txt", "r");
    if (fp == NULL) {
        perror("Error in opening file");
        return(-1);
    }
    parse_input(cards, fp);
    fclose(fp);

    points = get_points(cards, NUM_CARDS);
    printf("Total Points: %d\n", points);

    card_count = get_scratchcards(cards, NUM_CARDS);
    printf("Total scratchcards: %d\n", card_count);

    return 0;
}
