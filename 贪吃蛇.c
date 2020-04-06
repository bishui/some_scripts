#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include  <time.h>

#define High 35	//��Ϸ����ߴ�
#define Width 70

/*������ȫ�ֱ���*/
int canvas[High][Width]	={0};	//��ά�����¼��Ϸ�����еĶ�ӦԪ�� 	��0����ո� ��-1����߿�, 1�����ͷ ��>1������
					
int moveDirecttion;		//С���ƶ�����1,2,3,4���ֱ��ʾ�ϣ��£����� 
int food_x,food_y;		//ʳ�� 
int i,j;
 
void gotoxy(int x ,int y)   //����ƶ�����x��y��λ��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle,pos);
} 
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = {1,0};	//�ڶ���ֵΪ���ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}
/*----------------------------------------------------------------------------------------------*/

void startup()											//���ݳ�ʼ��
{
	//���ܵı߿� 
	for(i=0;i<High;i++) 	//���ұ߿� 
	{	
		canvas[i][0] = -1;
		canvas[i][Width-1] = -1;
	}
	for(j=0;j<Width;j++) 	//���±߿� 
	{	
		canvas[0][j] = -1;
		canvas[High-1][j] = -1;
	}
	
	//��ʼ����ͷ������
	 canvas[High/2][Width/2] = 1;
	
	for(i=1;i<=15;i++) 
		 canvas[High/2][Width/2-i] = i+1;

	moveDirecttion=4; 	//��ʼ��С�ߵ��ƶ��������� 

	//��ʼ��ʳ���λ�� 
	food_x = rand() % (High-5) + 2;
	food_y = rand() % (Width-5) + 2;
	canvas[food_x][food_y] =-2;
	
//	HideCursor(); 	//���ع�� 
}

/*----------------------------------------------------------------------------------------------*/
void moveSnakeByDirection()										//�ƶ��ߵ�λ�� 
{	int max =0 ; 
	int oldTail_i,oldTail_j;	//�ɵ���β 
	int oldHead_i,oldHead_j;	//�ɵ���ͷ 
	int newHead_i,newHead_j;	
	for(i=1;i<High-1;i++)
		for(j=1;j<Width-1;j++)
		{
			if(canvas[i][j]>0)
			{
				//�����д����0��Ԫ�ؼ�һ 
				canvas[i][j]++;
				
				//������ֵmax 
				if(max < canvas[i][j])
				{
					max = canvas[i][j];
					oldTail_i = i; 
					oldTail_j = j;
				} 
				//��¼�ɵ���ͷλ�� 
				if( canvas[i][j] == 2)
				{
					oldHead_i = i; 
					oldHead_j = j;
				} 				
			}		
		}	
											//	canvas[oldTail_i][oldTail_j]= 0	; //���ֵ����Ԫ�ر�Ϊ 0

	if(moveDirecttion == 1) //����
	 	{
			newHead_i = oldHead_i-1; //�ھ���ͷ��λ���ϱ仯 
			newHead_j = oldHead_j;
	    }
	if(moveDirecttion == 2) //���� 
	 	{
			newHead_i = oldHead_i+1;
			newHead_j = oldHead_j;
	    }
	if(moveDirecttion == 3) //���� 
	 	{
			newHead_i = oldHead_i;
			newHead_j = oldHead_j-1;
	    }
	if(moveDirecttion == 4) //���� 
	 	{
			newHead_i = oldHead_i;
			newHead_j = oldHead_j+1;
	    }			
		    
	 //�ж�С����ͷ�Ƿ�����ʳ��   
	if(canvas[newHead_i][newHead_j] == -2)
	{
		//ʳ��ԭʼλ�ù� 0 
		canvas[food_x][food_y] =	0;
		
		//�����µ�ʳ��			
		food_x = rand() % (High-5) + 2;
		food_y = rand() % (Width-5) + 2;
		canvas[food_x][food_y] =	-2;
		//�Ե�ʳ��������ֵ����Ԫ�ر�Ϊ 0�����ȼ�һ 
	} 
	else
		//û�гԵ�ʳ���ʱ�򣬳��Ȳ��� 
		canvas[oldTail_i][oldTail_j]= 0	; //���ֵ����Ԫ�ر�Ϊ 0
	    
	//�ж�С����ͷײ���߿�������Ϸʧ��
	if(canvas[newHead_i][newHead_j] > 0 || canvas[newHead_i][newHead_j] ==-1) 
	{
		printf("��Ϸʧ�ܣ�\n");
		exit(-1);
	}
	else
		canvas[newHead_i][newHead_j] = 1;  //����ͷ�Ĳ��� 
	
}
/*----------------------------------------------------------------------------------------------*/

void show()		//��ʾ����
{
	//system("cls");		//���� 
	gotoxy(0,0);				 //���� ,����ƶ�����x��y��λ��
	
	for (i=0;i<High;i++)
		{for (j=0;j<Width;j++)
			{
				if(canvas[i][j]==0) 
					printf(" ");			//����ո� 
				else if(canvas[i][j]==-1) 
					printf("#");			//����߿� 
				else if(canvas[i][j]==1) 
					printf("@");			//�����ͷ 
				else if(canvas[i][j]>1) 
					printf("*");			//������� 
				else if(canvas[i][j]==-2) 
					printf("$");			//���ʳ�� 
			}
		printf("\n");
		}
	Sleep(100) ;
}
/*----------------------------------------------------------------------------------------------*/

void updateWithoutInput()	//���û������޹صĸ��� 
{
	moveSnakeByDirection();
}
/*----------------------------------------------------------------------------------------------*/

void updateWithtInput()	//���û������йصĸ��� 
{
	char input;
	
	if (kbhit())		//������ʱ����  
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

										/*������*/
int main(int argc, char *argv[]) {
	
	/*---------------------------------------��Ϸ˵��-----------------------------*/
	 	
	printf("�ո��  Ϊ���\n");
	printf("   W��  Ϊ����\t S��  Ϊ���� \n   A��  Ϊ����\t D��  Ϊ����\n") ; 
	printf("------------------------------------\n");
	printf("ע�⣺�뽫�����л���Ӣ��״̬��"); 
	sleep(3);
	/*----------------------------------------------------------------------*/		
	
	startup();	//���ݳ�ʼ��
	
		while(1) 		//��Ϸѭ��ִ�У�(����ִ��ʱ���� )
		{	
			show();		//��ʾ����
			updateWithoutInput();	//���û������޹صĸ��� 
			updateWithtInput();	//���û������йصĸ��� 

		} 
		

return 0;
}



