//CHECK THIS OUT!!!!!!!
//AWESOME WORK GUYS!!-  @VB
/*

    1st Executable CUI Run : June 3
    1st Executable GUI Run : June 12
    Added color scheme & Fixed some bugs : June 21
    Increased size of grid : June 23
    Made more user intractive(can change window size): June 25
    Made much much more user intractive(addition of credits,loading and startmenu): June 26
    Added pause, exit, menu buttons: June 28
    Increased Size of the grid ... A Lot :P : June 30
    Integrated previous two improvements
    window size adjustability removed
    Made changes to Credits and start menu and experimented with fonts : July 7
*/

#include <iostream>
#include <graphics.h>
#include <fstream>

using namespace std;


class cell{
public:

    int cs, ns, fs; //Current State, Neighbour Sum, Future State
    cell(){
        cs=0;       //Constructor to initialise the cs to 0
    }
    void CalcNS();  //This function calculates a value for each
                    //cell which is equal to number of neighbouring live cells
    void CalcFS();  //This function calculates the future state of each cell based on rules given in algorithm above
    void SwitchtoFS();  //This function 'changes generations' i.e it assigns the future state value to current state

};

int i, j;
cell o[27][47];

void drawStart();
void drawCell();
void startGame();
void startmenu();
void getXY();
void options();
void createintructions();
void loading();
void setState();
void convert();
void startScreen();
void startLife();
void credits();
void startmenu();
void statements();
void choose(int l);

int main(){

    int gd=DETECT,gm;

    initgraph(&gd,&gm,"C:\\TC\\BGI");       //show credits window
    credits();
    closegraph();

    initwindow(990,700,"THE GAME OF LIFE",30,30);      //Initialises the window
    drawStart();
    closegraph();

    getch();
    return(0);

}

void startScreen(){
    int gd=DETECT,gm;

    initgraph(&gd,&gm,"C:\\TC\\BGI");       //show credits window
    credits();
    closegraph();
}

void startLife(){                           //Main Game play


    while(1){                  //Main loop: this iterates every generation
    delay(1000);


            for (i=0;i<27;i++){          //calculates Neighbour Sum and Future State
                    for(j=0;j<47;j++){
                       o[i][j].CalcNS();
                       o[i][j].CalcFS();
                    }
                }

            drawCell();                 //Draws the cells
            setfillstyle(SOLID_FILL, YELLOW);
            setcolor(YELLOW);
            bar(50,600,125,650);                  //Draws Pause button
            outtextxy(55,670,"PAUSE");

            getmouseclick(WM_LBUTTONDOWN, j, i);        //Gets position of mouse click into j and i
            if(getpixel(j,i)== YELLOW){
                cleardevice();
                setcolor(WHITE);
                setfillstyle(SOLID_FILL, WHITE);
                for (int a=20 ; a < 960 ; a+=20){
                    for (int b=20 ; b < 560 ; b+=20){
                        setcolor(WHITE);
                        setfillstyle(SOLID_FILL, WHITE);
                        rectangle(a,b,a+19,b+19);         //Draws Empty Boxes
                    }
                }
                while (1){                          //Loop for Accepting values
                    drawStart();
                    startLife();
                }
            }

            for (i=0;i<27;i++){  //Assigns FS to CS. This must be done in a separate loop
                                //from the above two functions because the
                                // new current state depends only on old current states
                for(j=0;j<47;j++){
                   o[i][j].SwitchtoFS();
                }
            }
    }

}

void credits(){                 //the credits (for an awesome game)
    createintructions();
    int i;
    for(i=500;i>=100;i-=10){
        delay(10);
        cleardevice();
        settextstyle(5,0,1);
        outtextxy(100,i-20,"J. H. Conway's");
        settextstyle(3,0,6);
        outtextxy(100,i,"THE GAME OF LIFE");
        settextstyle(8,0,2);
        outtextxy(180,i+50,"©Varun Bhargava & Julian D'Costa & ");
        outtextxy(430,i+70,"Shreyas Singh");
    }
    loading();
    startmenu();
    cleardevice();
}

void loading(){                     //just a liitle loading to admire the big three ;)
    int i;
    rectangle(200,300,440,350);
    for(i=200;i<=420;i+=20){
        bar(i+3,303,i+18,348);
        Sleep(200);
    }
    Sleep(200);
}

void createintructions(){
    ofstream fout;                      //create the instructions file
    fout.open("Instructions.txt");
    fout<<"The Game of Life was invented by John Horton Conway. It is a classic example of two-dimensional cellular automata."
        <<"\nIt takes place on a plane grid of cells (theoretically infinite- in our version torus-connected)"
        <<"\nCells are either dead or alive. "
        <<"\nYou start by choosing some cells to be alive. Then sit back and watch life unfold."
        <<"\nEvery generation cells are born and die according to the following two rules : "
        <<"\nNote-Neighbours means the eight cells adjacent to any cell."
        <<"\n\n1.A live cell with two or three live neighbours survives into the next generation (Green cells)."
        <<"\nOtherwise it dies of starvation (Yellow cells) or overcrowding (Blue cells)"
        <<"\n2.A dead cell with exactly three live neighbours is born in the next generation (White rectangle). ";
    fout.close();
}

void startmenu(){

        while(1){
            statements();
            i=mousex();
            j=mousey();
            setfillstyle(SOLID_FILL, BLUE);
            setcolor(BLUE);
            if (j>330&&j<390){
            if(i>=70&&i<=200){
                bar(60,340,195,380);
                statements();
            }else if(i>=300&&i<=355){
                bar(290,340,360,380);
                statements();
            }else if(i>=470&&i<=525){
                bar(460,340,530,380);
                statements();
            }
            }

            if(ismouseclick(WM_LBUTTONDOWN))
                break;
            delay(100);
            cleardevice();

        }
        getmouseclick(WM_LBUTTONDOWN,j,i);
        if (i>330&&i<390)
            choose(j);
        else
            startmenu();
}

void choose(int l){

        if(l>=70&&l<=200){
            cleardevice();
            closegraph();
            startGame();
        }else if(l>=300&&l<=355){
            cleardevice();
            ShellExecute(NULL,"open","instructions.txt",NULL, NULL, SW_SHOWNORMAL );
            startmenu();
        }else if(l>=470&&l<=525){
            exit(0);
        }else{
            startmenu();
        }

}

void startGame(){
    initwindow(990,700,"THE GAME OF LIFE",30,30);      //Initialises the window
    drawStart();
    startLife();
    closegraph();
}

void statements(){
    setcolor(WHITE);
    settextstyle(5,0,1);
    outtextxy(100,100-20,"J. H. Conway's");
    settextstyle(3,0,6);
    outtextxy(100,100,"THE GAME OF LIFE");
    settextstyle(8,0,2);
    outtextxy(180,100+50,"©Varun Bhargava & Julian D'Costa & ");
    outtextxy(430,100+70,"Shreyas Singh");


    setcolor(WHITE);
    settextstyle(3,0,1);
    outtextxy(70,350," START GAME ");
    outtextxy(300,350," HELP ");
    outtextxy(470,350," QUIT ");

}

void drawStart(){                                   //Initialises the Graphic window

    setfillstyle(SOLID_FILL, RED);
    setcolor(RED);
    bar(50,600,125,650);                  //Draws Start Button
    outtextxy(55,670,"START");
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    bar(150,600,225,650);                 //Draws Menu Button
    outtextxy(155,670,"MENU");

    setfillstyle(SOLID_FILL, WHITE);
    for (int a=20 ; a < 960 ; a+=20){
        for (int b=20 ; b < 560 ; b+=20){
            setcolor(WHITE);
            setfillstyle(SOLID_FILL, WHITE);
            rectangle(a,b,a+19,b+19);         //Draws Empty Boxes
            j=(a-20)/20;   i=(b-20)/20;       //For checking the values at specific cells
            if (o[i][j].cs==1){
                bar (a,b,a+19,b+19);
            }
        }
    }                                           //Draws the matrix

    while (1){                                  //Loop for Accepting values
        getXY();
        if (getpixel(j,i) == RED)               //Starts Life if Start is clicked
            break;
        else if (getpixel(j,i) == BLUE){
            closegraph();
            startScreen();
        }
        else
            setState();                         //Assigns State
    }
    i=0;j=0;
    cleardevice();
}

void drawCell(){                                    //Draws Cells

    system("cls");                              //Clears console screen
    cleardevice();                              //Clears graphics screen
    for (int a=20 ; a < 960 ; a+=20){
        for (int b=20 ; b < 560 ; b+=20){
            setcolor(WHITE);

            j=(a-20)/20;   i=(b-20)/20;       //For checking the values at specific cells

            if (o[i][j].cs==1){                 //Draws filled boxes
                if (o[i][j].ns==0 || o[i][j].ns==1){
                    setfillstyle(SOLID_FILL,YELLOW);
                    bar(a,b,a+19,b+19);
                }
                else if (o[i][j].ns==2 || o[i][j].ns==3){
                    setfillstyle(SOLID_FILL,GREEN);
                    bar(a,b,a+19,b+19);
                }
                else if (o[i][j].ns==4 || o[i][j].ns==5 || o[i][j].ns==6){
                    setfillstyle(SOLID_FILL,BLUE);
                    bar(a,b,a+19,b+19);
                }
            }
            /*else if (o[i][j].fs==1){
                setcolor(WHITE);
                rectangle(a,b,a+19,b+19);       //Draws empty boxes- commented out
                                                // because it was visually distracting
            }*/
        }
    }

}

void getXY(){                                       //Getting position of Mouse click

    while (!ismouseclick(WM_LBUTTONDOWN)){      //Waits for mouse to clicked or else
        delay(100);                             //the program would run forward
    }

    getmouseclick(WM_LBUTTONDOWN, j, i);        //Gets position of mouse click into j and i

}

void setState (){                                   //To set the state of the cells

    j = (j -((j-20)%20));                       //To get cell position
    i = (i -((i-20)%20));                       //j-j%100 gives us the poition in 100's
    i = i/20-1; j = j/20-1;                 //Then divide it by 100 to get row/column no.

    if  (i<27 && j<47){
    if (o[i][j].cs == 1){                       //If cell already exists make it black
        o[i][j].cs = 0;
        i = (i+1)*20;j = (j+1)*20;
        setfillstyle(SOLID_FILL, BLACK);
        bar(j,i,j+19,i+19);
        rectangle(j,i,j+19,i+19);
    }
    else{
        o[i][j].cs = 1;                       //Sets cs to 1
        i = (i+1)*20;j = (j+1)*20;
        setfillstyle(SOLID_FILL, WHITE);
        bar(j,i,j+19,i+19);                   //Fills Box
    }
    }
}

void cell::CalcNS(){    //This function calculates a value for each
                        //cell which is equal to number of neighbouring live cells
    ns = o[(i+26)%27][j].cs + \
         o[(i+1)%27][j].cs + \
         o[(i+26)%27][(j+1)%47].cs + \
         o[(i+26)%27][(j+46)%47].cs + \
         o[(i+1)%27][(j+1)%47].cs + \
         o[(i+1)%27][(j+46)%47].cs + \
         o[i][(j+1)%47].cs +  \
         o[i][(j+46)%47].cs ;

}

void cell::CalcFS(){    //This function calculates the future state of each cell based on rules given in algorithm above

    if(o[i][j].cs==0){
        if(o[i][j].ns==3){
            o[i][j].fs=1;
        }
        else{
            o[i][j].fs=0;
        }
    }
    else if(o[i][j].cs==1){
        if((o[i][j].ns==2)||(o[i][j].ns==3)){
                o[i][j].fs=1;
        }
        else{
            o[i][j].fs=0;
        }
    }

}

void cell::SwitchtoFS(){    //Assigns the future state value to current state

cs=fs;

}


