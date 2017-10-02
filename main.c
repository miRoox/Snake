#include <stdio.h>
#include "utils.h"
#include "conmanip.h"

// prepare
void startup(void);
void aboutToQuit(void);
// interactive ui
void mainMenu(void);
void newGame(void);
void loadGame(void);
void maybeQuit(void);
unsigned int getSpeed(void);

void playing();

int main(int argc, char *argv[])
{
    startup();
    mainMenu();
    return EXIT_SUCCESS;
}

void mainMenu(void)
{
    bool reselect = true;
    while(reselect) 
    {
        int choice = 0;
        reselect = true;
        setBackground(Blue);
        clearScreen();
        printf("Menu:\n"
               "1=New Game.\n"
               "2=Load Game.\n"
               "0=Quit Game\n"
               "Please input(1, 2 or 0):");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            newGame();
        break;
        case 2:
            loadGame();
        break;
        case 0:
            reselect = false;
            maybeQuit();
            reselect = true;
        break;
        default:
            reselect = true;
            warning("Wrong Input!");
            system("pause");
        break;
        }
    }
}

void newGame(void)
{
    bool reselect = true;
    while(reselect) 
    {
        int choice = 0;
        unsigned int speed = 0;
        reselect = false;
        clearScreen();
        printf("Choose model:\n"
               "1=Boundless model\n"
               "2=Limitary model\n"
               "0=Back to previous\n"
               "Please input(1, 2 or 0):");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            speed = getSpeed();
            playing();//TODO
        break;
        case 2:
            speed = getSpeed();
            playing();//TODO
        break;
        case 0:
            reselect = false;
        break;
        default:
            reselect = true;
            warning("Wrong Input!");
            system("pause");
        break;
        }
    }
}

void loadGame(void)//TODO
{
    return;
}

void maybeQuit(void)
{
    int ch = 'Y';
    puts("Press Y or y to quit the game.");
    ch = getch();
    ch = toupper(ch);
    if(ch == 'Y') 
        exit(EXIT_SUCCESS);
}

unsigned int getSpeed(void)
{
    unsigned int maxSpeed = 5;//TODO
    unsigned int speed = maxSpeed;
    bool re = false;
    do {
        clearScreen();
        printf("Input Speed(1~%d):",maxSpeed);
        scanf("%u",&speed);
        if(speed<1 || speed>maxSpeed)
        {
			re = true;
            warning("Wrong Input!");
            system("pause");
        }
        else 
        {
            re = false;
        }
    }
    while(re);
    return speed;
}

void playing()//TODO
{
    debug("playing...");
    maybeQuit();
}

void startup(void)
{
    atexit(aboutToQuit);
    //TODO
}

void aboutToQuit(void)//TODO
{
    return;
}
