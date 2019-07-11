#include<stdio.h>
#include<GFILES.h>
#include<windows.h>

int main()
{
    int hiScore = 0;
    int choice;

    game:
    Beep(400,500);
    Beep(700,500);
    Beep(600,500);
    Beep(200,500);
    Beep(200,500);
    Beep(600,500);
    Beep(700,500);
    Beep(400,500);

    hiScore = PlayGame(hiScore);
    printf("\n\t\tPress 1 to play again and 0 to quit \n");
    scanf("%d",&choice);

    if(choice == 1)    /// Whether user wishes to play again or not
        goto game;
    else
        printf("-----------------------------------Thank You For Playing !!----------------------------------------------- \n");

    return 0;
}
