#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include<conio.h>
int		robot();
int 	winner();
int 	best_move(int player,int position);
void	draw();
int 	restart();

int		grid[9],player=2,show_numbers=1;
int		odds[8][3]={ 	
						{0,1,2},{3,4,5},{6,7,8},{0,3,6},
						{1,4,7},{2,5,8},{0,4,8},{2,4,6} 
					};
int	main(){
	draw();
	printf("press any key to start");
	getch();
	show_numbers=0;
	while(1){
		

		int	i,position=0;
		for	(i =0;i<9;i++)
		{
			if 	(player==1){
				tryAgain:;
				printf("Enter cell number : ");
				scanf("%d",&position);
				if(position<0||position>9||grid[position-1]>0){
					draw();
					printf("not allowed\n");
					goto tryAgain;
				}
			}else
				position = robot();

			grid[position-1]=player;
			
			if(winner())
				break;
			draw();
			player=player==1?2:1;
			
		}
		draw();
		if(winner())
			printf("%s Won !\n\n",player==1?"You":"Computer");
		else
		printf("No one won\n");

		if(!restart())
			break;
	}
}




int winner(){
	int i;
	for (i = 0; i < 8; ++i){
		int r0 = grid[odds[i][0]],
			r1 = grid[odds[i][1]],
			r2 = grid[odds[i][2]];
		if (r0==r1&&r0==r2&&r0==player)
			return 1;
	}
	return 0;
}

int best_move(int player,int position){
	int i;
	for (i = 0; i < 8; ++i){
		int r0 = grid[odds[i][0]],
			r1 = grid[odds[i][1]],
			r2 = grid[odds[i][2]];
		int win1 = r0==player;
		int win2 = r1==player;
		if (r0==r1&&r1&&!r2)
			if(player==1||win1)
				return odds[i][2];
		 if (r0==r2&&r0&&!r1)
		 	if(player==1||win1)
				return odds[i][1];
		 if (r1==r2&&r1&&!r0)
		 	if(player==1||win2)
				return odds[i][0];
	}
	return position;
}
int		robot(){

		int arr[10],i,ln=0;
		for(i=0;i<9;i++)
			if(!grid[i])
				arr[ln++]=i;
		time_t t;
		srand((unsigned) time(&t));
		int position = arr[rand() % ln];  // Get a Random empty cell number
		position = best_move(1,position); // checking for winning cell
		position = best_move(2,position); // if there is a chance to win just ignore all and win 
		return position+1;
}

int restart(){
	int i;
	for (i = 0; i < 9; ++i)
		grid[i]=0;
	printf("Would you like to play again? (Y/N)\n");
	char again[1];
	player=2;
	scanf("%s",again);
	return !strcmp(again,"y")||!strcmp(again,"Y");
}

void draw(){
	#ifdef _WIN32
		system("cls");
	#endif
	#ifdef linux
		system("clear");
	#endif

	printf("Computer : X \nYou      : O");
	int i;
	printf("\n_____________\n");
	for(i=0;i<9;){
		int o = i+3;
		printf("|");
		for(i=i;i<o;){
			if(show_numbers)
				printf(" %d |", i+1);
			else
				printf(" %s |", grid[i]>0?grid[i]==2?"X":"O":" ");
			i++;
		}
		printf("\n|___|___|___|\n");
	}
	printf("\n");
}
