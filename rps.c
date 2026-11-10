#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROCK 1
#define PAPER 2
#define SCISSOR 3

void main(){
    srand(time(NULL));
    //seeding random number with current time
    int player_throw ,ai_throw;
    int draw = 0;

    do{
        printf("Select your throw.\n");
        printf("1) ROCK\n");
        printf("2) PAPER\n");
        printf("3) SCISSOR\n");
        printf("Select:");
        scanf("%d", &player_throw);

        ai_throw = (rand() % 3) + 1;

        if(ai_throw == ROCK) printf("\nAI throws ROCK.\n");
        else if(ai_throw == PAPER) printf("\nAI throws PAPER.\n");
        else if(ai_throw == SCISSOR) printf("\nAI throws SCISSOR.\n");

        draw = 0;

        if(ai_throw == ROCK && player_throw == PAPER)
            printf("\nPAPER beats ROCK. YOU WIN.\n\n");
        else if(ai_throw == PAPER && player_throw == SCISSOR)
            printf("\nSCISSOR beats PAPER. YOU WIN.\n\n");
        else if(ai_throw == SCISSOR && player_throw == ROCK)
            printf("\nROCK beats SCISSOR. YOU WIN.\n\n");
        else if(ai_throw == PAPER && player_throw == ROCK)
            printf("\nPAPER beats ROCK. YOU LOSE.\n\n");
        else if(ai_throw == SCISSOR && player_throw == PAPER)
            printf("\nSCISSOR beats PAPER. YOU LOSE.\n\n");
        else if(ai_throw == ROCK && player_throw == SCISSOR)
            printf("\nROCK beats SCISSOR. YOU LOSE.\n\n");
        else{
            printf("\nDRAW! Play Again.\n\n");
            draw = 1;
        }
        
    }while(draw == 1);
    
}