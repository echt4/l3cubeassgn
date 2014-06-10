#include<conio.h>
#include<stdio.h>
#include<string.h>

struct file
{
	char data[20][10];
	int tot_lines;
}file[100];

void append(char newdata[10]);
void resume();
void commit();
int check_digit(char a[10]);
int check_string(char a1[10]);
//void display(int ver);
void open1(char a2[10]);
void delete_line();
int pos=0,lines=0,open_vers=0;
char newdata[20];
FILE *fp1;
void main()
{
	int i=0,ch;
	char x[200],a1[10],a2[10],a3[10];
	FILE *fp;
	clrscr();
	fp= fopen("test.txt","r");
	printf("\nSVC\t\tInput file: test.txt\n\n");
	while(1)              //reading file and storing in structure
	{
		   if(fgets(x,200,fp)==NULL)break;
		strcpy(file[pos].data[lines],x);
		strcat(file[pos].data[lines++],'\0');
	}
	file[pos].tot_lines=lines;
	for(i=0;i<lines;i++)
	{
		printf("%s",file[pos].data[i]);
	}
	do
	{
		fgets(newdata,100,stdin);        //scanning input
		sscanf(newdata,"%s %s",a1,a2);
		if((strcmp(a1,"svc")==0) && check_string(a2))    //checking svc command
		{                                               //for commit
			commit();
		}
		else if((strcmp(a1,"svc")==0) &&check_digit(a2))  //checking svc command
		{                                                 //to open version
			open1(a2);
		}
		else if(strcmp(a1,"exit")==0)
		{
			exit(0);
		}
		else if((strcmp(a1,"delete")==0))     //delete a line
		{
			 delete_line();
		}
		else                              //append a line
		{
			append(newdata);
		}
	}while(strcmp(newdata,"exit")!=0);
	if(strcmp(newdata,"exit")==0)
		exit(0);
	getch();
}

void append(char newdata[10])
{
	int i,past_pos;
	char temp[20];
	past_pos=pos;
	pos++;
	for(i=0;i<lines;i++)
	{
		//copied previous version text into next version
		strcpy(file[pos].data[i],file[past_pos].data[i]);
	}
	strcat(file[pos].data[lines],newdata);
	strcat(file[pos].data[lines++],'\0');
	file[pos].tot_lines=lines;//count of total lines for each version

}

/*void display(int ver)
{
	int i,j,line_count;
	line_count=file[ver].tot_lines;
	for(i=0;i<=pos;i++)
	{
		if(ver==i)
		{
			for(j=0;j<line_count;j++)
			{
				printf("%s", file[i].data[j]);

			}
		}
	}
} */

void open1(char a2[20])    //open required file version
{
	char y[200];
	FILE *fp2;
	strcat(a2,".txt");
	fp2=fopen(a2,"r");
	while(1)
	{
		   if(fgets(y,200,fp2)==NULL)break;
		printf("%s",y);
	}
	fclose(fp2);
}


void commit()         //creating new version
{
	int i;
	char curr[10],x[200];
	int temp;
	temp=pos;
	itoa(temp,curr,10);
	strcat(curr,".txt");
	fp1=fopen(curr,"w");
	for(i=0;i<file[pos].tot_lines;i++)
	{
		fprintf(fp1,"%s",file[pos].data[i]);
	}
	fclose(fp1);
}

int check_string(char a1[10])      //check if command is string
{
	int i=0,flag=0;
	while(a1[i]!='\0')
	{
		  if(isdigit(a1[i]))
		  {
			flag=1;
			break;
		  }
		  if(a1[i]=='.')
			flag=0;
		  i++;
	}
	if(flag==1)
	{
		return 0;
	}
	else{
		return 1;
	}
}


int check_digit(char a1[10])      //check if command is number
{
	int i=0,flag=0;
	while(a1[i]!='\0')
	{
		  if(isdigit(a1[i]))
		  {	flag=1;
		break; }
		i++;
	}
	if(flag==1)
	{
		return 1;
	}
	else{
		return 0;
	}
}
void delete_line()         //function to delete line
{
	int x,i;
	int prev_pos;
	prev_pos=pos;
	x=file[pos].tot_lines;
	x=x-1;
	pos++;
	open_vers=pos;
	file[open_vers].tot_lines=x;
	for(i=0;i<x;i++)
	{
		strcpy(file[open_vers].data[i],file[prev_pos].data[i]);
	}
}