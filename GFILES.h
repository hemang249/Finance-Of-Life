#ifndef GFILES_H_INCLUDED
#define GFILES_H_INCLUDED

/* LIBRARIES UTILISED*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/* CONSTANTS */
#define MAXYEAR 5    /// Max number of years to be played
#define MAXTURN 3       /// Max number of turns in a year
#define MINGOLD 1000    /// Min investment in Gold
#define MINRE 10000     /// Min investment in Real Estate
#define MINSTOCK 3000   /// Min investment in Stock Market

/* GLOBAL VARS */
int nPlays=0;           /// Number of time the game has been played
char playerList[10][40];     /// Matrix of player names
int scores[10];              /// Scores of the list of players
int remCash;                /// Amount of remaining cash

/* UDFs */
int DiceRoll ();                               /// function to simulate a dice roll
int PlayGame(int hiScore);                     /// Function containing the Game code
int Careerchoice(int diceVal);                 /// function to determine career based on dice roll
int Salary(int career);                        /// function to determine salary
int Turn(int remCash);                         /// function to simulate each turn
int Invest( int remCash);                       /// function to handle investments
int Growth( int sal);                           /// function to decide Promotion , demotion or Stagnancy
int RandomExpense( int remCash);                /// function to decide Expense
float Taxes(int sal);                          /// function to calculate taxes
int Fortune(int remCash);                      /// function to calculate Fortune
int Invest_in( int remCash , int choice);       /// function to invest in a particular field
void HighScores();                             /// function to display Score list


void HighScores()
{
    int i = 0  ;

    for(i=0 ; i < nPlays ; i++)
    {
        printf("%s : %d",playerList[i],scores[i]);
    }
}


int DiceRoll()    /// Simulates Roll of a dice
{
   time_t t ;
   srand(time(&t));
   int l = ( (rand()%6) + 1 );
   srand(time(&t));
   int h = ( (rand()%6) + 1 );
   return ((l+h) / 2);         /// As dice value starts from 1 and not 0
}

int Careerchoice(int diceVal)   /// Allots Career based on Dice roll
{
    enum career {DOCTOR=1 , ENGINEER , TEACHER , ARTIST , SCIENTIST , MANAGER };
    switch(diceVal)
    {
        case 1: return 1;
        case 2: return 2;
        case 3: return 3;
        case 4: return 4;
        case 5: return 5;
        case 6: return 6;
    }

    return 0;
}
/// ******************************************************************************************************

int Salary(int career)    /// Allots salary based on Career
{
    switch(career)
    {
        case 1: return 50000; break;
        case 2: return 25000; break;
        case 3: return 20000; break;
        case 4: return 25000; break;
        case 5: return 40000; break;
        case 6: return 45000; break;
    }
    return 0;
}
/// *******************************************************************************************************

int Invest_in(int remCash , int choice)    /// Choice based Investment in either Gold or Real estate or Stocks
{
    time_t x;
    srand(time(&x));
    time_t t;
    srand(time(&t));
    int l = rand()%5 + 1;
    srand(time(&t));
    int h = rand()%5 + 1;

    float  chance = (int)((l+h)/2);           ///  1 in 3 chance of Incurring A loss
    float luck =  (int)(rand()%5 + 1) ;      /// Return of 0 to 5% profit or loss
    int investAmt , min;                     /// min is the minimum amt a user must invest in a particular field

     switch(choice)
     {
         case 1:  min = MINGOLD;
                  if(remCash < MINGOLD)
                  {
                      printf("\t\t--You have insufficient funds to invest in Gold \n");
                      return remCash;
                  } break;
        case 2: min = MINRE;
                if(remCash < MINRE)
                {
                    printf("\t\t--You have insufficient funds to invest in Real estate \n");
                    Invest(remCash);
                } break;

        case 3: min = MINSTOCK;
                if(remCash < MINSTOCK)
                {
                    printf("\t\t--You have insufficient funds to invest in Stock Market \n");
                    Invest(remCash);
                }

     }

     retry:
    printf("\t\tHow much to invest  ? You will get a return of 0 to 5 percentage based on your luck \n");
    scanf("%d",&investAmt );

    if(investAmt > remCash)    /// Makes sure User doesn't invest what he doesn't have
    {
        printf("\t\tYou cannot invest more than you have \n");
        goto retry;
    }
    else if(investAmt < min)   /// To make sure user invests atleast the minimum amount
    {
        printf("\t\tYou must invest a minimum of %d \n",min);
        goto retry;
    }


    remCash -= investAmt;    /// Subtracts investment Amount from Remaining cash

    printf("\t\tYou have %d remaining after investing \n",remCash);

    if(chance == 1)   /// Based on Luck decides whether to incurr a loss or a Profit
    {
        investAmt += (investAmt * luck )/ 10;
        printf("\n\t\t--You have incurred a loss of %d \n\n\n",investAmt);
        remCash -= investAmt;         /// Subtract the losses from the remaining cash
    }
    else
    {
        investAmt += (investAmt * luck) / 10;
        printf("\n\t\t--Your Investment profit = %d \n\n\n",investAmt);
        remCash += investAmt;         /// Add the profits to the remaining cash

    }
    return remCash;

}

int Invest(int remCash)    /// Simulates the Investment
{
    int choice ;

    printf("\t\tYou must invest a minimum of 1000 in Gold \n");
    printf("\t\tYou must invest a minimum of 10000 in Real Estate \n");
    printf("\t\tYou must invest a minimum of 3000 in Stock Market \n");

    choose:
    printf("\n\t\tPress 1 to invest in Gold\n\t\tPress 2 to Invest in Real estate\n\t\tPress 3 to invest in Stock Market \n");
    scanf("%d",&choice);

    if(choice == 1 || choice == 2 || choice == 3)
          remCash = Invest_in(remCash , choice);
    else
        goto choose;


    return remCash;

}

int Turn(int remCash)      /// Provides possible choices that can be made during a Turn
{
    int choice;

    makechoice:
    printf(" \n\tPress 1 To Save Money , 2 to Invest \n");
    scanf("%d",&choice);

    switch(choice)      /// Perform operation based on choice
    {
        case 1:  break;
        case 2:  remCash = Invest(remCash); break;      /// calls the function invest
        default : goto makechoice;
    }
    return remCash;
}

int Growth(int sal)     /// Decides Growth
{
    time_t t;
    srand(time(&t));

    switch(rand()%3 + 1)    /// Based on chance decide Promotion , demotion or Stagnancy
    {
        case 1: printf("\t You were promoted and your salary increases by 3000 \n");
                sal+=3000;
                break;
        case 2: printf("\t Unfortunately you were demoted and your salary is decreased by 3000 \n");
                sal -= 3000;
                break;
        case 3: printf("\t No Change , Salary remains same \n");
                break;
    }

    return sal;
}

int RandomExpense(int remCash)    /// Generates a random expense
{
    int choice , dice;

    roll:
    printf("This is a Expense Turn , Roll the dice by pressing 1 \n");
    scanf("%d",&choice);

    if(choice==1)    /// Makes sure user presses 1 and not any other key
    {
        dice = DiceRoll();
    }
    else
    {
        printf("Enter a valid Input \n");
        goto roll;
    }

    switch(dice)  /// Determines expenses based on Roll of a dice
    {
        case 1: printf("You have incurred No expense \n");
                break;
        case 2: printf("You have incurred a Medical expense worth %d \n",(40 * remCash) / 100);
                remCash -= (40 * remCash) / 100;
                break;
        case 3: printf("You have incurred a Fine for A Crime worth %d \n",(20 * remCash) / 100);
                remCash -= (20 * remCash) / 100;
                break;
        case 4: printf("You have incurred Housing Expense worth %d \n",(15 * remCash) / 100);
                remCash -= (15 * remCash) / 100;
                break;
        case 5: printf("You have incurred Banking Expense worth %d \n",(50 * remCash) / 100 );
                remCash -= (50 * remCash) / 100;
                break;
        case 6: printf("You have incurred Vehicular Expense worth %d \n",(30 * remCash) / 100);
                remCash -= (30 * remCash) / 100;
                break;

 }

  return remCash;
}

float Taxes(int sal)   /// Calculates Taxes as 15% of Salary
{
    float tax = 0.10 * sal;   /// taxes to be paid are 10% of the salary
    return tax;
}

int Fortune(int remCash)
{
    int chance , choice , fort;

    roll:
    printf("There is a 1 in 6 chance of Getting a Fortune \nRoll the dice by pressing 1 \n");
    scanf("%d",&choice);

    if(choice == 1)
        chance = DiceRoll();
    else
        goto roll;

    if(chance == 1)
    {
        fort = (int) (10.0 * remCash) / 100;                  /// 10% fortune to be received
        printf("You have received a fortune of %d \n",fort);
        remCash += fort;
        printf("You have %d remaining \n",remCash);
    }
    else
    {
        printf("Bad Luck ! You have received no fortune \n");
    }

    return remCash;
}

int PlayGame(int hiScore)                 /// hiScore is the highest score achieved in the entire history of playing
{
    int  i = 0 ,career , choice, choices ;
    register int year = 1 , nturn = 1 ;
    int sal;
    float expense;

    printf("Welcome To Finance of Life \n");
    printf("This Game is designed to give the user a taste of the Outside Financial World \n");
    printf("Test Your Financial Skills , And see How Good You Are ! \n");

    again:
    printf("Press 1 to play , 2 to View High Scores And 3 to Quit\n");
    scanf("%d",&choices);
    getchar();
    if(choices == 1)
        goto Play;
    else if(choices==2)
        HighScores(nPlays);
    else if(choices == 3)
        goto end;
    else
        goto again;

    Play:
    printf("Enter Your Name \n");

    while( (playerList[nPlays][i] = getchar() ) != '\n')
        i++;

    printf("You will be provided 10 years time to Achieve Victory \n");
    printf("Each year consist of 3 turns \n");
    printf("Roll the dice to choose a career \n");
    printf("Based on Your Die result There are 6 career choices : DOCTOR(1) , ENGINEER(2) , TEACHER(3) , POLICE(4) , SCIENTIST(5) , MANAGER(6) \n");

   /* CAREER AND SALARY COMPUTUATION*/
    roll :
    printf("Press 1 to roll the dice \n");
    scanf("%d",&choice);

    if(choice == 1)       /// Makes sure that user presses 1 and not any other key
    {
         career = DiceRoll();
         Careerchoice(career);
    }
    else
    {
        printf("Enter valid number \n");
        goto roll;
    }

    switch(career)                 /// Print career
    {
        case 1: printf("\nYou have become an Doctor \n"); break;
        case 2: printf("\nYou have become a Engineer \n"); break;
        case 3: printf("\nYou have become a Teacher \n"); break;
        case 4: printf("\nYou have become an Artist \n"); break;
        case 5: printf("\nYou have become a Scientist \n"); break;
        case 6: printf("\nYou have become a Manager \n"); break;
    }

        sal = Salary(career);      /// Decides salary based on career

    printf("\nYour Salary is %d \n",sal);
    printf("\nYour Base expense based on your salary is 70 percent of your salary \n");

    expense = 0.7 * sal;      /// Calculates expenses based on Expenses

    printf("--Your Expense = %.2f \n",expense);
    printf("--Each year there is a one in three chance of you getting a promotion , demotion or stagnancy\n");
    printf("--REMEMBER YOU WILL LOSE IF YOUR REMAINING CASH REACHES 0 \n");
    printf("--INVESTMENTS BEAR A 1 IN 3 CHANCE OF A LOSS \n");
    printf("--TURN 3 IS A RANDOM EXPENSE TURN BE PREPARED FOR IT ! GOOD LUCK !! \n");
    printf("--AT THE END OF TURN 3 YOU WILL BE PROVIDED WITH A CHANCE OF FORTUNE \n");


    for(year = 1 ; year <= MAXYEAR ; year++)      /// Outer Loop which controls the Year Going on
    {
        expense = 0.7 * sal;
        remCash += sal;                          /// Before expenses All the salary is a part of remaining cash

        printf("\n\n------YEAR %d------ \n \n \n",year);
        printf("\t--This year you have to pay %.2f in taxes \n",Taxes(sal));
        printf("\t--Your expenses are : %.2f \n",expense);
        printf("\t--Remaining cash before expenses : %d \n",remCash);

        remCash -=  expense;                     /// To subtract the expenses from Remaining cash

        printf("\t--Remaining Cash after expenses = %d \n",remCash);
        printf("\t--Salary at start of year %d = %d \n\n\n",year,sal);

            for(nturn = 1 ; nturn <= MAXTURN ; nturn++)     /// Inner loop to Control the ongoing turn
            {
                printf("\n\t---Turn %d--- \n",nturn);
                remCash = Turn(remCash);                     /// Modify remaining cash based on Operation performed in The turn

                if(nturn == 3)                               /// As 3rd turn is a expense turn
                {
                   remCash =  RandomExpense(remCash);                  /// Allots a random expense based on dice roll

                    if(remCash <= 0 )            /// Checks if Money = 0 , if so then player has lost
                     {
                          printf("---------------You Lose-------------\n");
                           goto end;
                     }
                }

                printf("\t--At the end of Turn %d You Have %d remaining \n \n",nturn,remCash);
            }

        remCash = Fortune(remCash);
        printf("\t--Time to Pay Taxes worth %.2f \n",Taxes(sal));
        remCash -= Taxes(sal);                                                 /// To subtract taxes from remaining salary
        printf("\t--At the end of Year %d You Have %d remaining \n",year,remCash);

         if(remCash <= 0 )            /// Checks if Money = 0 , if so then player has lost
        {
             printf("-----------------You Lose---------------\n");
             goto end;
        }

        sal = Growth(sal);                                                     /// Modify salary based on promotion , demotion or Stagnancy
        printf("\t--At the end of year %d , Your salary = %d \n ------------------------------------------------------\n\n\n",year,sal);


    }

    scores[nPlays] = remCash;
    nPlays++;

    end:
    if(remCash > hiScore)                     /// If high score of previous play is Lower then modify it
        hiScore = remCash;

    printf("------------Current Score : %d--------------\n",scores[nPlays-1]);
    printf("--------------High Score : %d--------------\n",hiScore);

    return hiScore;

}
#endif // GFILES_H_INCLUDED
