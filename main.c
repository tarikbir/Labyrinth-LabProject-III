#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* GLOBAL DEFINES */
#define MAX 40
#define X 20

char moves = {0 , 1 , 2 , 3};
/*  0 = Up
    1 = Right
    2 = Down
    3 = Left */

struct move{
    char nextMove;
    struct move *prev;
    struct move *next;
};

struct stack{
    struct move val;
    struct stack *next;
};

void drawMap(char map[X][X])
{
    /**Draws the map onto the cmd screen*/
    for (int i=0;i<3*X;i++) {printf("-");}
    printf("---\n");
    for (int i=0;i<=X;i++) {printf("%2d ",i);}
    printf("\n");
    for (int i=0;i<X;i++)
    {
        printf("%2d ",i+1);
        for (int j=0;j<X;j++)
        {
            if (map[i][j] == 1) //Labirent yolu
                printf("[ ]");
            else if (map[i][j] == 0) //Labirent duvari
                printf("   ");
            else if (map[i][j] == 2) //Labirent baslangic noktasi
                printf("<o>");
            else if (map[i][j] == 3) //Labirent bitis noktasi
                printf("/!\\");
        }
        printf("\n");
    }
    for (int i=0;i<3*X;i++) {printf("-");}
    printf("---");
}

void generateRandomMap(char map[X][X])
{
    /**Generates a random map between 0 and 1*/
    for (int i=0;i<X;i++)
    {
        for (int j=0;j<X;j++)
        {
            map[i][j] = rand()%2;
        }
    }
}

int getNumber(int max)
{
    /**Gets an integer from stdin within 0 and max.*/
    char integerToReturn[MAX];
    char *p;
    do{
        fgets(integerToReturn,MAX,stdin);
        int toReturn = (int)strtol(integerToReturn,&p,10);
        if ( integerToReturn[0] == 0 )
            return 0;
        if ( toReturn >= 0 && toReturn <= max && toReturn != NULL )
            return toReturn;
        printf("ERROR: Wrong input.\nTry again: ");
    }while(1);
}

int writeMapBySide(int side, int count, char map[X][X], int max, char info, int doCheck, int check)
{
    /**Picks given side and converts it to coordinates and writes down the information*/
    char *p;
    if (side == 1)
        p = &map[0][count-1];
    else if (side == 2)
        p = &map[count-1][max-1];
    else if (side == 3)
        p = &map[max-1][count-1];
    else if (side == 4)
        p = &map[count-1][0];
    else
        printf("ERROR: Wrong side or info in writeMapBySide!");
    if (doCheck)
    {
        if (check == *p)
        {
            *p = info;
            return 1;
        }
        return 0;
    }
    *p = info;
    return 1;
}

int main()
{
    /* INITIALIZATION */
    srand(time(NULL));
    char map[X][X];
    int besyuzbin=500;
    /* TODO: SCANF X MALLOC DIZI */
    generateRandomMap(map);
    drawMap(map);
    /* GET ENTRANCE AND EXIT */
    //ENTRANCE
    do{
        printf("\nPick the entrance:\n1 = Up\t2 = Right\t3 = Down\t4 = Left\nSide: ");
        int side = getNumber(4);
        printf("Point on side?: ");
        int point = getNumber(X);
        int check = writeMapBySide(side, point, map, X, 2, 1, 1);
        if (check) break;
        printf("ERROR: Wrong input! That point is not a valid target for an entrance!");
    }while(1);
    system("cls");
    drawMap(map);
    //EXIT
    do{
        printf("\nPick the exit:\n1 = Up\t2 = Right\t3 = Down\t4 = Left\nSide: ");
        int side = getNumber(4);
        printf("Point on side?: ");
        int point = getNumber(X);
        int check = writeMapBySide(side, point, map, X, 3, 1, 1);
        if (check) break;
        printf("ERROR: Wrong input! That point is not a valid target for an exit!");
    }while(1);
    system("cls");
    drawMap(map);
    /* START ITERATING THROUGH THE MAP */
    struct move *start;

    return 0;
}
