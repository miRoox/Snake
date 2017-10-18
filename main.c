#include "utils.h"
#include "conmanip.h"
#include "easytimer.h"
#include "maps.h"
#include "snake.h"
#include "food.h"

typedef unsigned int Speed;
typedef enum
{
    BackToGame = 0,
    LeaveGame,
    ReplayGame
} GameOption;

// prepare
void startup(void);
void aboutToQuit(void);
// interactive ui
void mainMenu(void);
void newGame(void);
void loadGame(void);
void maybeQuit(void);
bool leaveGame(void);
bool replayGame(void);
GameOption showOptions(void);
Speed getSpeed(void);

bool playing(MapModel mapModel,
             Speed speed,
             const void* snakeData,
             const Pos* food);
void repaint(void);

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
            pause("Press any key to continue.");
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
        reselect = false;
        MapModel mapModel;
        clearScreen();
        printf("Choose model:\n"
               "1=Boundless model\n"
               "2=Limitary model\n"
               "0=Back to previous\n"
               "Please input(1, 2 or 0):");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1: case 2:
            if(choice==1)
            {
                mapModel = Boundless;
            }
            else
            {
                mapModel = Limitary;
            }
            Speed speed = getSpeed();
            while(playing(mapModel,speed,NULL,NULL));
            reselect = false;
        break;
        case 0:
            reselect = false;
        break;
        default:
            reselect = true;
            warning("Wrong Input!");
            pause("Press any key to continue.");
        break;
        }
    }
}

void loadGame(void)//TODO
{
    pause("TODO...");
}

void maybeQuit(void)
{
    puts("Press Y to quit the game.");
    int ch = getch();
    ch = toupper(ch);
    if(ch == 'Y')
        exit(EXIT_SUCCESS);
}

bool leaveGame(void)
{
    bool leave = false;
    puts("Do you want to leave the game?[Y/N]");
    int ch = getch();
    ch = toupper(ch);
    if(ch == 'Y')
    {
        leave = true;
    }
    return leave;
}

bool replayGame(void)
{
    bool replay = false;
    puts("Do you want to replay the game?[Y/N]");
    int ch = getch();
    ch = toupper(ch);
    if(ch == 'Y')
    {
        replay = true;
    }
    return replay;
}

GameOption showOptions(void)
{
    GameOption option = BackToGame;
    bool reselect = true;
    while(reselect)
    {
        int choice = 0;
        reselect = false;
        repaint();
        printf("Options:\n"
               "1=Save game\n"
               "2=Leave game\n"
               "3=Replay game\n"
               "4=Quit\n"
               "0=Back to the game\n"
               "Please input(1, 2, 3, 4 or 0):");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1://TODO: save game
            pause("TODO...");
            reselect = true;
        break;
        case 2:
            if(leaveGame())
            {
                option = LeaveGame;
                reselect = false;
            }
            else
            {
                reselect = true;
            }
        break;
        case 3:
            if(replayGame())
            {
                option = ReplayGame;
                reselect = false;
            }
            else
            {
                reselect = true;
            }
        break;
        case 4:
            maybeQuit();
            reselect = true;
        break;
        case 0:
            reselect = false;
        break;
        default:
            reselect = true;
            warning("Wrong Input!");
            pause("Press any key to continue.");
        break;
        }
    }
    return option;
}

unsigned int getSpeed(void)
{
    Speed maxSpeed = 5;//TODO: load from config
    Speed speed = maxSpeed;
    bool re = false;
    do {
        clearScreen();
        printf("Enter speed level(1~%u):",maxSpeed);
        scanf("%u",&speed);
        if(speed<1 || speed>maxSpeed)
        {
			re = true;
            warning("Wrong Input!");
            pause("Press any key to continue.");
        }
        else
        {
            re = false;
        }
    }
    while(re);
    return speed;
}

//return replay
bool playing(MapModel mapModel,
             Speed speed,
             const void* snakeData,
             const Pos* food)
{
    bool replay = false;
    ConColor oldForegrd = foreground();
    ConColor oldBackgrd = background();
    Timer* timer = NULL;
    //map model
    setMapModel(mapModel);
    //speed
    clock_t rate = CLOCKS_PER_SEC*1/5;
    Speed maxSpeed = 5;
    clock_t timerInterval = rate*(maxSpeed + 1 - speed);
    timer = installTimer(timerInterval);
    //snake
    if(!initSnake(snakeData))
    {
        warning("Snake data is corrupted!");
        delay(2*CLOCKS_PER_SEC);
        goto ret;
    }
    //food
    if(!initFood(food))
    {
        warning("Food data is corrupted!");
        delay(2*CLOCKS_PER_SEC);
        goto ret;
    }
    //running
    setColor(LightGreen,Yellow);
    repaint();
    startTimer(timer);
    forever
    {
        if(kbhit())
        {
            int ch = getch();
            switch(ch)
            {
            case 'w': case 'W':
                turnTo(Up);
            break;
            case 's': case 'S':
                turnTo(Down);
            break;
            case 'a': case 'A':
                turnTo(Left);
            break;
            case 'd': case 'D':
                turnTo(Right);
            break;
            case 'q': case 'Q': //quick quit
                stopTimer(timer);
                maybeQuit();
                repaint();
                startTimer(timer);
            break;
            case ' ': case ASCII_ESC: //options
                stopTimer(timer);
                switch(showOptions())
                {
                    case LeaveGame:
                        replay = false;
                        goto ret;
                    break;
                    case ReplayGame:
                        replay = true;
                        goto ret;
                    break;
                    case BackToGame:
                    break;
                }
                repaint();
                startTimer(timer);
            break;
            default:
            break;
            }
        }
        if(timeout(timer))
        {
            //update
            updateSnake();
            updateFood();
            if(isVictorious())
            {
                setColor(LightYellow,Gray);
                puts("You are victorious!");
                if(replayGame())
                {
                    replay = true;
                }
                else
                {
                    replay = false;
                }
                goto ret;
            }
            else if(isFailed())
            {
                setColor(LightRed,Red);
                printf("Your final score is %u.\n", currentLength());
                if(replayGame())
                {
                    replay = true;
                }
                else
                {
                    replay = false;
                }
                goto ret;
            }
            //repaint
            repaint();
        }
    }
ret:
    setColor(oldForegrd,oldBackgrd);
    removeTimer(timer);
    return replay;
}

void repaint(void)
{
    static char buffer[BufferSize];
    clearScreen();
    printf("Use \'W\',\'S\',\'A\',\'D\' Key to Change the Direction.\n"
           "Press ESC or space key to show the options.\n"
           "Score:%u\n\n", currentLength());
    drawMap(buffer);
    drawSnake(buffer);
    drawFood(buffer);
    puts(buffer);
}

void startup(void)
{
    atexit(aboutToQuit);
    srand(time(0));
    char buffer[BufferSize];
    drawMap(buffer);//init map buffer
    //TODO: config
}

void aboutToQuit(void)//TODO: config
{
    debug("quit...");
}
