#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include  <time.h>

#define High 35	//游戏画面尺寸
#define Width 70

/*函数外全局变量*/
int canvas[High][Width]	={0};	//二维数组记录游戏画面中的对应元素 	，0输出空格 ，-1输出边框, 1输出蛇头 ，>1是蛇身
					
int moveDirecttion;		//小蛇移动方向，1,2,3,4，分别表示上，下，左，右 
int food_x,food_y;		//食物 
int i,j;
 
void gotoxy(int x ,int y)   //光标移动到（x，y）位置
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle,pos);
} 
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = {1,0};	//第二个值为零表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}
/*----------------------------------------------------------------------------------------------*/

void startup()											//数据初始化
{
	//四周的边框 
	for(i=0;i<High;i++) 	//左右边框 
	{	
		canvas[i][0] = -1;
		canvas[i][Width-1] = -1;
	}
	for(j=0;j<Width;j++) 	//上下边框 
	{	
		canvas[0][j] = -1;
		canvas[High-1][j] = -1;
	}
	
	//初始化蛇头，蛇身
	 canvas[High/2][Width/2] = 1;
	
	for(i=1;i<=15;i++) 
		 canvas[High/2][Width/2-i] = i+1;

	moveDirecttion=4; 	//初始化小蛇的移动方向向右 

	//初始化食物的位置 
	food_x = rand() % (High-5) + 2;
	food_y = rand() % (Width-5) + 2;
	canvas[food_x][food_y] =-2;
	
//	HideCursor(); 	//隐藏光标 
}

/*----------------------------------------------------------------------------------------------*/
void moveSnakeByDirection()										//移动蛇的位置 
{	int max =0 ; 
	int oldTail_i,oldTail_j;	//旧的蛇尾 
	int oldHead_i,oldHead_j;	//旧的蛇头 
	int newHead_i,newHead_j;	
	for(i=1;i<High-1;i++)
		for(j=1;j<Width-1;j++)
		{
			if(canvas[i][j]>0)
			{
				//对所有大大于0的元素加一 
				canvas[i][j]++;
				
				//求出最大值max 
				if(max < canvas[i][j])
				{
					max = canvas[i][j];
					oldTail_i = i; 
					oldTail_j = j;
				} 
				//记录旧的蛇头位置 
				if( canvas[i][j] == 2)
				{
					oldHead_i = i; 
					oldHead_j = j;
				} 				
			}		
		}	
											//	canvas[oldTail_i][oldTail_j]= 0	; //最大值所在元素变为 0

	if(moveDirecttion == 1) //向上
	 	{
			newHead_i = oldHead_i-1; //在旧蛇头的位置上变化 
			newHead_j = oldHead_j;
	    }
	if(moveDirecttion == 2) //向下 
	 	{
			newHead_i = oldHead_i+1;
			newHead_j = oldHead_j;
	    }
	if(moveDirecttion == 3) //向左 
	 	{
			newHead_i = oldHead_i;
			newHead_j = oldHead_j-1;
	    }
	if(moveDirecttion == 4) //向右 
	 	{
			newHead_i = oldHead_i;
			newHead_j = oldHead_j+1;
	    }			
		    
	 //判断小蛇蛇头是否碰到食物   
	if(canvas[newHead_i][newHead_j] == -2)
	{
		//食物原始位置归 0 
		canvas[food_x][food_y] =	0;
		
		//产生新的食物			
		food_x = rand() % (High-5) + 2;
		food_y = rand() % (Width-5) + 2;
		canvas[food_x][food_y] =	-2;
		//吃到食物，不用最大值所在元素变为 0，长度加一 
	} 
	else
		//没有吃到食物的时候，长度不变 
		canvas[oldTail_i][oldTail_j]= 0	; //最大值所在元素变为 0
	    
	//判断小蛇蛇头撞到边框自身，游戏失败
	if(canvas[newHead_i][newHead_j] > 0 || canvas[newHead_i][newHead_j] ==-1) 
	{
		printf("游戏失败！\n");
		exit(-1);
	}
	else
		canvas[newHead_i][newHead_j] = 1;  //新蛇头的产生 
	
}
/*----------------------------------------------------------------------------------------------*/

void show()		//显示画面
{
	//system("cls");		//清屏 
	gotoxy(0,0);				 //清屏 ,光标移动到（x，y）位置
	
	for (i=0;i<High;i++)
		{for (j=0;j<Width;j++)
			{
				if(canvas[i][j]==0) 
					printf(" ");			//输出空格 
				else if(canvas[i][j]==-1) 
					printf("#");			//输出边框 
				else if(canvas[i][j]==1) 
					printf("@");			//输出蛇头 
				else if(canvas[i][j]>1) 
					printf("*");			//输出蛇身 
				else if(canvas[i][j]==-2) 
					printf("$");			//输出食物 
			}
		printf("\n");
		}
	Sleep(100) ;
}
/*----------------------------------------------------------------------------------------------*/

void updateWithoutInput()	//与用户输入无关的更新 
{
	moveSnakeByDirection();
}
/*----------------------------------------------------------------------------------------------*/

void updateWithtInput()	//与用户输入有关的更新 
{
	char input;
	
	if (kbhit())		//当按键时进行  
	{
		input = getch() ;
		if(input=='w')	
			moveDirecttion= 1 ;			
		if(input=='s')	
			moveDirecttion= 2 ;		
		if(input=='a')	
			moveDirecttion= 3 ;
		if(input=='d')	
			moveDirecttion= 4 ;

    } 
}
/*-------------------------------------------------------------------------------------------

										/*主程序*/
int main(int argc, char *argv[]) {
	
	/*---------------------------------------游戏说明-----------------------------*/
	 	
	printf("空格键  为射击\n");
	printf("   W键  为上移\t S键  为下移 \n   A键  为左移\t D键  为右移\n") ; 
	printf("------------------------------------\n");
	printf("注意：请将键盘切换至英文状态！"); 
	sleep(3);
	/*----------------------------------------------------------------------*/		
	
	startup();	//数据初始化
	
		while(1) 		//游戏循环执行，(及其执行时间内 )
		{	
			show();		//显示画面
			updateWithoutInput();	//与用户输入无关的更新 
			updateWithtInput();	//与用户输入有关的更新 

		} 
		

return 0;
}



