#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define Max_player 30
#define Questions 5

void banner(){
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



int main(){
	char playerNames[Max_player][50];
    int playerScores[Max_player];
    int playerCount = 0;
    int i;
    int choice;
	
	do {
    banner();   
    printf("\n");
    menu();
    scanf("%d", &choice);

    switch (choice) {

        case 1: {
    		int level;
    		int totalPlayer;
    		int score;
    		int p;
    		char name[50];

    		printf("\nEnter number of players: ");
    		scanf("%d", &totalPlayer);

    		printf("\nChoose Difficulty:\n");
    		printf("1. Easy\n");
    		printf("2. Medium\n");
    		printf("3. Hard\n");
    		printf("Choose: ");
    		scanf("%d", &level);

    		srand(time(NULL));

    		for (p = 0; p < totalPlayer; p++) {

        	score = 0;

        	printf("\nEnter name for Player %d: ", p + 1);
        	scanf("%s", name);

        	for (i = 1; i <= Questions; i++) {

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
            }
            else if (level == 2) {
                a = rand() % 20 + 1;
                b = rand() % 20 + 1;
                op = rand() % 4;
                point = 20;

                if (op == 0) {
                    printf("\nQ%d: %d + %d = ", i, a, b);
                    correctAnswer = a + b;
                }
                else if (op == 1) {
                    printf("\nQ%d: %d - %d = ", i, a, b);
                    correctAnswer = a - b;
                }
                else if (op == 2) {
                    printf("\nQ%d: %d * %d = ", i, a, b);
                    correctAnswer = a * b;
                }
                else {
                    b = (b == 0) ? 1 : b;
                    a = a * b;
                    printf("\nQ%d: %d / %d = ", i, a, b);
                    correctAnswer = a / b;
                }
            }
            	else {   /* HARD ONLY */
    				a = rand() % 9 + 1;        /* 1 digit */
    				b = rand() % 90 + 10;      /* 2 digit */
    				c = rand() % 8 + 2;        /* 2–9 */
    				type = rand() % 4;
    				point = 30;

    			if (type == 0) {
        			printf("\nQ%d: (%d + %d) * %d = ", i, a, b, c);
        			correctAnswer = (a + b) * c;
    		}
    			else if (type == 1) {
        			printf("\nQ%d: %d * (%d - %d) = ", i, c, b, a);
        			correctAnswer = c * (b - a);
    		}
    			else if (type == 2) {
        			b = b - (b % c);   /* ensure divisible */
        			printf("\nQ%d: (%d + %d) / %d = ", i, a, b, c);
        			correctAnswer = (a + b) / c;
    		}
    			else {
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

        	strcpy(playerNames[playerCount], name);
        	playerScores[playerCount] = score;
        	playerCount++;

        	printf("\n===== QUIZ RESULT =====\n");
        	printf("Player Name : %s\n", name);
        	printf("Total Score : %d\n", score);
    	}

    	break;
}

        
        case 2:
            printf("\n===== HOW TO PLAY =====\n");
            printf("1. Choose 'Let's Play' from menu option\n");
            printf("2. Enter player name\n");
            printf("3. Select difficulty level: Easy, Medium or Hard\n");
            printf("4. Answer a total of 5 math questions\n");
            printf("5. Correct answer gives points based on their difficulty\n");
            printf("6. Total Points will be displayed at the end of the game\n");
            break;

        case 3:
            if (playerCount == 0) {
                printf("\nNo players have played yet.\n");
            } else {
                printf("\n===== LEADERBOARD =====\n");
                printf("No\tName\tScore\n");
                for (i = 0; i < playerCount; i++) {
                    printf("%d\t%s\t%d\n", i + 1, playerNames[i], playerScores[i]);
                }
            }
            break;

        case 4:
            printf("\nThank you for playing Math Quiz!\n");
            break;

        default:
            printf("\nInvalid choice! Try again.\n");
        }
        
	} while (choice != 4);

	return 0;
}
