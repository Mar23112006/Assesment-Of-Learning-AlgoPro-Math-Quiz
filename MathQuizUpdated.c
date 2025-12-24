#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PLAYER 30
#define Questions 5
#define FILE_NAME "leaderboard.txt"

//helper func
void clearScreen() {
    system("cls");
}

void flushExtra() {
	while (getchar() != '\n');
}
void pauseGame() {
    while (getchar() != '\n');
    printf("\nPress [ENTER] to continue . . .");
    getchar();
}

//struct
typedef struct {
    char name[50];  
    int score;
} Player;

void saveScore(char name[], int score) {
    FILE *fp = fopen(FILE_NAME, "a");
    
    if (fp == NULL) {
        printf("[ERROR] Failed to open the file database!\n");
        return;
    }
    
    fprintf(fp, "%s %d\n", name, score);
    
    fclose(fp);
    printf(">> Scores saved successfully!\n");
}

void readScores(Player players[], int *count) {
    FILE *fp = fopen(FILE_NAME, "r");
    *count = 0;
    if (fp == NULL) return; 
    while (fscanf(fp, "%49s %d", players[*count].name, &players[*count].score) != EOF) {
        (*count)++;
        if (*count >= MAX_PLAYER) break;
    }
    fclose(fp);
}

void swap(Player *a, Player *b) {
    Player temp = *a;
    *a = *b;
    *b = temp;
}

void sortScores(Player players[], int count) {
    int i, j;
    Player temp;
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (players[j].score < players[j+1].score) {
                swap(&players[j], &players[j+1]);
            }
        }
    }
}

void viewLeaderboard() {
    Player players[MAX_PLAYER];
    int count = 0;

    clearScreen(); 
    printf("==================================\n");
    printf("       LEADERBOARD (TOP RANK)     \n");
    printf("==================================\n");
    
    readScores(players, &count);
    if (count == 0) {
        printf("   No datas yet.\n");
        printf("   Be the first one!\n");
    } else {
        sortScores(players, count);
        printf("%-4s | %-20s | %-5s\n", "No", "Username", "Score");
        printf("----------------------------------\n");
        for (int i = 0; i < count; i++) {
            //  Top 10
            if (i >= 10) break; 
            printf("%-4d | %-20s | %-5d\n", i + 1, players[i].name, players[i].score);
        }
    }
    printf("==================================\n");
    pauseGame();
}

void banner() {
    printf("=================================\n");
    printf("      WELCOME TO MATH QUIZ !!!     \n");
    printf("=================================\n");
}

void menu() {
    printf("===== MATH QUIZ LOBBY =====\n");
    printf("1. Let's Play\n");
    printf("2. How To Play The Game ?\n");
    printf("3. Show Leaderboard\n");
    printf("4. Exit The Game\n");
    printf("Choose: ");
}

void mathGame() {
	int level;
	int totalPlayer;
	int score;
	char name[50];
	
	clearScreen();
	printf("\nEnter number of players: ");
	scanf("%d", &totalPlayer);
	flushExtra();
	
	if (totalPlayer > 30) totalPlayer = 30;
	
	printf("\nChoose Difficulty:\n");
	printf("1. Easy\n");
	printf("2. Medium\n");
	printf("3. Hard\n");
	printf("Choose: ");
	scanf("%d", &level);
	flushExtra();
	
	if (level < 1 || level > 3) printf("Invalid choice, defaulting to hard.\n");
	
	srand(time(NULL));
	
	for (int p = 0; p < totalPlayer; p++) {
	    score = 0;
	
	    printf("\nEnter name for Player %d: ", p + 1);
    	scanf("%49s", name);
    	flushExtra();
	
	    for (int i = 1; i <= Questions; i++) {
	        int a, b, c;
	        int op, type;
	        int playerAnswer, correctAnswer;
	        int point;
	
	        if (level == 1) {
	            a = rand() % 10 + 1;
	            b = rand() % 10 + 1;
	            op = rand() % 2;
	            point = 10;
	
	            if (op == 0) {
	                printf("\nQ%d: %d + %d = ", i, a, b);
	                correctAnswer = a + b;
	            } else {
	                printf("\nQ%d: %d - %d = ", i, a, b);
	                correctAnswer = a - b;
	            }
	        } else if (level == 2) {
	            a = rand() % 20 + 1;
	            b = rand() % 20 + 1;
	            op = rand() % 4;
	            point = 20;
	
	            if (op == 0) {
	                printf("\nQ%d: %d + %d = ", i, a, b);
	                correctAnswer = a + b;
	            } else if (op == 1) {
	                printf("\nQ%d: %d - %d = ", i, a, b);
	                correctAnswer = a - b;
	            } else if (op == 2) {
	                printf("\nQ%d: %d * %d = ", i, a, b);
	                correctAnswer = a * b;
	            } else {
	                b = (b == 0) ? 1 : b;
	                a = a * b;
	                printf("\nQ%d: %d / %d = ", i, a, b);
	                correctAnswer = a / b;
	            }
	        } else {   /* HARD ONLY */
	            a = rand() % 9 + 1;        /* 1 digit */
	            b = rand() % 90 + 10;      /* 2 digit */
	            c = rand() % 8 + 2;        /* 2–9 */
	            type = rand() % 4;
	            point = 30;
	
	            if (type == 0) {
	                printf("\nQ%d: (%d + %d) * %d = ", i, a, b, c);
	                correctAnswer = (a + b) * c;
	            } else if (type == 1) {
	                printf("\nQ%d: %d * (%d - %d) = ", i, c, b, a);
	                correctAnswer = c * (b - a);
	            } else if (type == 2) {
	                b = b - (b % c);   /* ensure divisible */
	                printf("\nQ%d: (%d + %d) / %d = ", i, a, b, c);
	                correctAnswer = (a + b) / c;
	            } else {
	                printf("\nQ%d: (%d * %d) %% %d = ", i, a, c, b);
	                correctAnswer = (a * c) % b;
	            }
	        }
	
	        scanf("%d", &playerAnswer);
	
	        if (playerAnswer == correctAnswer) {
	            printf("Correct! The correct answer is %d\n", correctAnswer);
	            score += point;
	        } else {
	            printf("Wrong! The correct answer is %d\n", correctAnswer);
	        }
	    }
		clearScreen();
	    printf("\n===== QUIZ RESULT =====\n");
	    printf("Player Name : %s\n", name);
	    printf("Total Score : %d\n", score);
	    saveScore(name, score);
	    pauseGame();
	}
}

void howTo(){
	clearScreen();
	printf("\n===== HOW TO PLAY =====\n");
    printf("1. Choose 'Let's Play' from menu option\n");
    printf("2. Enter player name\n");
    printf("3. Select difficulty level: Easy, Medium or Hard\n");
    printf("4. Answer a total of 5 math questions\n");
    printf("5. Correct answer gives points based on their difficulty\n");
    printf("6. Total Points will be displayed at the end of the game\n");
    pauseGame();
}

int main() {
	Player players[MAX_PLAYER];
    int count = 0;
    int i;
    int choice;
    
    readScores(players, &count);

    do {
    	clearScreen();
        banner();
        printf("\n");
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
				mathGame();
                break;
            }

            case 2:
				howTo();
                break;

            case 3:
                viewLeaderboard();
                break;

            case 4:
                printf("\nThank you for playing Math Quiz!\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
                pauseGame();
        }
    } while (choice != 4);

    return 0;
}

