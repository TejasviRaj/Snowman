	// Header file declaration.

#include "stdio.h"
#include "conio.h"
#include "dos.h"
#include "graphics.h"
#include "string.h"
#include<ctype.h>
#include<stdlib.h>

// Global variable declaration.

int lives = 4,len, firstrun=0, clen=0,wrongcount=0,oldkey[20],keycount=0,newkey,score=0;
char data[20], hint[200], uname[20], message[50]="Its our only chance to save the World,", datakey[50],last,wrong[50];
FILE *datafile,*hintfile;
struct info {
char database[20];
char hintbase[100];
} element[20];
//Function declaration.
void load();
void getName();
void intro();
void game();
void drawman();
void endgame();
void playagain();
void keygenerator();
//Main Function, Loads the load() function that opens files...
int main(){
	int gdriver=DETECT, gmode;
	int result,i;
	  initgraph(&gdriver, &gmode, "C:\\TC\\bgi");
	clrscr();
	result = graphresult();

	 if(result!=0){
		printf("Graphics could not be initialized Error Code : %d", result);
		}
		else{
		datafile=fopen("data.txt","r");
		for (i=0;i<=19;i++)
	      fscanf (datafile,"%s",element[i].database);
		fclose(datafile);
		hintfile=fopen("hint.txt","r");
		for (i=0;i<=19;i++)
		fgets(element[i].hintbase,100,hintfile);
		fclose(hintfile);
		for (i=0;i<=19;i++)
		oldkey[i]=100;

		 load();
		 }
	getch();
	return 0;
}

//Welcomes user with nice UI and loads data files...
void load(){
	int i;
	cleardevice();
	setbkcolor(0);
	setcolor(WHITE);
	settextstyle(TRIPLEX_SCR_FONT, HORIZ_DIR, 9);
	outtextxy(90, 80, "SNOWMAN");
	gotoxy(38,18);
		printf ("Loading...");
	   for(i=0;i<100; i++){
		delay(20);
		rectangle(280, 260, 280+i, 265);
		}
	gotoxy(34,18);
	   printf("\t\t\t\t\t\t\t\t\t\t\t\t\t");
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
	outtextxy(180,350,"Press any key to Continue...");
	getch();
       getName();

}

//Gets Name of user ;)
void getName(){
	int i,j;
	char c, localfuname[100];

	localfuname[0]=32;
	localfuname[1]='\0';

	cleardevice();
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
	setbkcolor(1);
	setcolor(WHITE);
	rectangle(220, 100, 420, 300);
	gotoxy(34, 12);
	printf ("May i know you??");

	 for (i=1;localfuname[i-1]!=13;i++)
	  {
	 localfuname[i]=254;
	  localfuname[i+1]='\0';
	  if (i%2==0)
	  {
	  gotoxy(39-((i-2)/2),13);
	  printf ("%s",localfuname);
	  gotoxy(40+i/2,13);
	  localfuname[i]=getche();
	   localfuname[i+1]='\0';
	  }
	  else
	  {
	   gotoxy(39-((i-1)/2) ,13);
	  printf ("%s",localfuname);
	  gotoxy(40+(i-1)/2,13);
	   localfuname[i]=getche();
	   localfuname[i+1]='\0';
	  }
	  }
	strcpy(uname, localfuname);
      intro();
}

//Story of snowman
void intro(){
	cleardevice();
	setcolor(WHITE);
	setbkcolor(8);
	rectangle(100, 100, 540, 380);
	rectangle(102, 102, 538, 378);
	gotoxy(32, 10);
	printf("STORY OF THE SNOWMAN");

	gotoxy(17, 13);
	printf("Long time ago, the world used to be full of snow.");
	delay(100);
	gotoxy(17,14);
	printf("A monster, the snowman reigned the Earth and all.");
	delay(100);
	gotoxy(17, 15);
	printf("After the God Zeus put him under a spell, the wo");
	gotoxy(17,16);
	delay(100);
	printf("rld was freed. Now the snowman has come back. Spell");
	gotoxy(17, 17);
	delay(100);
	printf("to banish him to whence he sprung forth from !");
	gotoxy(33, 18);
	delay(100);
	printf("Can you do it?");
	gotoxy(23, 21);
	delay(250);
	printf("Press any key to accept the challange");
	getch();
	keygenerator();

}
void keygenerator()
{
int r,flag,i;
float f;
gotoxy(26,20);
printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
gotoxy(36,20);
printf("Loading...");
if (keycount>19)
{
for (i=0;i<=19;i++)
oldkey[i]=100;
keycount=0 ;
}
do
	 {
	 flag=0;
	 srand (time(NULL));
	 r=rand();
	 f=r/32768.0;
	 newkey=(int)(f*20);
	 for (i=0;i<=19;i++)
	 {
	 if (newkey==oldkey[i])
	 flag=1;
	 }
	 }
	 while (flag==1);
	 oldkey [keycount] =newkey;
	 keycount=keycount+1;
	 game();
}
// OK, Main game screen
void game(){
	int len, i, cx, flag=0, location,hintlen;
	char c;
	strcpy(data, element[newkey].database);
	strcpy(hint, element[newkey].hintbase);
	if(lives == 0){
		cleardevice();
		setbkcolor(LIGHTGREEN);
		rectangle(220, 200, 440, 300);
		gotoxy(40-(strlen(uname)/2)+1,14);
		printf ("%s",uname);
		gotoxy(37, 15);
		printf ("You lose");
gotoxy (35,16);
printf("Correct Answer:");
gotoxy(42-(strlen(data)/2),17);
printf ("%s",data);
gotoxy(36,18) ;
			printf("Total Score:%d",score);
		playagain();
		getch();
		exit(0);

	}

	if(clen == strlen(data)){
		cleardevice();
		setbkcolor(LIGHTGREEN);
		rectangle(220, 200, 420, 280);
		score=score+1;
		gotoxy(40-(strlen(uname)/2)+1,14);
		printf ("%s",uname);
		gotoxy(37, 15);
		printf("YOU WON!");
	   gotoxy(34,16);
		printf("Total Score:%d",score);
		playagain();
		exit(0);
	}
	len = strlen(data);
	hintlen=strlen(hint);
	cleardevice();
	drawman();
	setbkcolor(CYAN);
	setcolor(WHITE);
	settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
	outtextxy(240, 40, "Snowman");

	rectangle (20, 300, 620, 460);
gotoxy(2,2);
	printf("Score:%d",score);
	gotoxy(65, 23);
	printf("Lives: %d", lives);
	gotoxy(35, 22);
	printf("You Pressed:");
	gotoxy(40, 23);
	printf("%c", last);
	gotoxy(12, 24);
	printf("God Zeus: %s%s",message,uname );
	gotoxy(12,23);
	printf ("Wrong:%s",wrong);
	gotoxy(30,25);
	printf ("Note-Press ESC to exit");
       gotoxy(12, 7);
	printf("Spell the word or you are dead, of %d letters it is made", len);
	gotoxy(35, 11);
	printf("Start typing\n\n");
	gotoxy(38-(hintlen/2), 14);
	printf("Hint: %s", hint);
	// Draw the boxes now to fill the slot.
	cx = (80 - len)/2 + 1;

		if(firstrun == 0){
		for(i=0;i<len;i++){
			datakey[i] = 254;
		   }
		firstrun=1;
		}
	gotoxy(cx, 13);
	printf("%s",datakey);
	c= getch();
	if (c==27) endgame();
      if(c<65 || c>122)
	game();
	last=c;

	for(i=0; i<len; i++){
		if(toupper(c) ==toupper(data[i]) && toupper(c) != toupper(datakey[i]))
		{
			strcpy(message, "Very good,");
			flag = 1;
			location = i;
			clen++;
			break;
		}
		}
		if (flag==1)
		datakey[location]=c;
	else{
		strcpy(message, "Try harder, snowman is coming,");
		lives = lives - 1;
		wrong[wrongcount]=c;
		wrong[wrongcount+1]=' ';
		wrongcount=wrongcount+2;
	}
	game();
	}
void drawman(){
	int life = lives;
	if(life <=3){
	//Eyes:
	circle(560, 150, 5);
	circle(600, 150, 5);

	}
	if(life<=2){
	//Head
	circle(580, 150, 30);
	floodfill(580, 150, WHITE);
	}
	if(life<=1){
	//Body
	circle(580, 230, 50);
	floodfill(580, 230, WHITE);
	}
}

void endgame()
{
char c,d;
cleardevice();
gotoxy (20,15);
printf ("Are you sure you want to end the game (Y/N)");
c=getch();
d=toupper(c);
if (d=='Y') exit(0);
else if (d=='N') game();
else endgame();
}


void playagain()
{
char tempuname[50];
char c,d;
int i;
strcpy(tempuname,uname);
lives= 4, firstrun=0, clen=0,wrongcount=0;
for (i=0;i<=50;i++)
{
datakey[i]='\0';
wrong[i]='\0';
}
last='\0' ;
strcpy(uname,tempuname);
strcpy(message,"Its our only chance to save the World,") ;
gotoxy (26,20);
printf ("Do you want to play again??(Y/N)");
c=getch();
d=toupper(c);
if (d=='Y') keygenerator();
else if (d=='N') exit(0);
else playagain();

}

