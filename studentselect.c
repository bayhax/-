#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 2                   //课程门数
typedef struct hour
{
	int teachhour;
	int practicehour;
}HOUR;
typedef struct info
{
	int year;
	char level[10];
	char term[10];
}INFO;
typedef struct course
{
	int number;
	char name[20];
	char nature[10];
	HOUR classhour;
	int score;
	INFO information;
}CO;
int menu()
{
	int item;
	printf("\tCOURSE SELECT\n");
	printf("1.Input course information\n");
	printf("2.Read course information\n");
	printf("3.Select course\n");
	printf("4.Query information\n");
	printf("5.Select by score\n");
	printf("6.Selective course information\n");
	printf("7.End of the program\n");
	printf("Please enter your choice:");
	scanf("%d",&item);
	return item;
}
void inputcourseinformation(CO co[N]);
void readcourseinformation(CO co[N]);
void select(CO co[N],int number[]);
void query(CO co[N],int number[]);
void selectbyscore(CO co[N]);
void selectiveinformation(CO co[],int number[]);
int main()
{
	CO co[N];
	int number[N];
	int n;
	while(1)
	{
		n=menu();
		switch(n)
		{
			case 1:inputcourseinformation(co);
			        break;
			case 2:readcourseinformation(co);
			        break;
			case 3:select(co,number);
			        break;
			case 4:query(co,number);
			        break;
			case 5:selectbyscore(co);
			        break;
			case 6:selectiveinformation(co,number);
			        break;
			case 7:printf("end of the program\n");
			       exit(0);
			default:printf("input error\n");
		}
		return 0;
	}
	return 0;
}
//输入课程信息
void inputcourseinformation(CO co[N])
{
	//CO co[N];
	FILE *fp;
	int i;
	//printf("please enter the information of course:\n");
	for(i=0;i<N;i++)
	{
		printf("please input the %d course number name nature\n",i+1);
		scanf("%d%s%s",&co[i].number,&co[i].name,&co[i].nature);
		getchar();
		printf("please input the %d course classhour teachhour practicehour\n",i+1);
		scanf("%d%d%d",&co[i].classhour.teachhour,&co[i].classhour.practicehour,&co[i].score);
	    printf("please input the %d course start year level trem\n",i+1);
		scanf("%d%s%s",&co[i].information.year,&co[i].information.level,&co[i].information.term);
	    printf("please input the %d course score\n",i+1);
		scanf("%d",&co[i].score);
	}
	if((fp=fopen("course.dat","wb"))==NULL)
	{
		printf("cannot open file\n");
		return;
	}
	for(i=0;i<N;i++)
		if(fwrite(&co[i],sizeof(struct course),1,fp)!=1)
			printf("file write error\n");
	fclose(fp);
}
//读取课程信息
void readcourseinformation(CO co[N])
{
	//CO co[N];
	FILE *fp;
	int i;
	if((fp=fopen("course.dat","rb"))==NULL)
	{
		printf("cannot open file\n");
		exit(0);
	}
	for(i=0;i<N;i++)
	{
		fread(&co[i],sizeof(struct course),1,fp);
		printf("%d\t%s\t%s\n",co[i].number,co[i].name,co[i].nature);
		printf("%d  %d   %d",co[i].classhour.teachhour,co[i].classhour.practicehour,co[i].score);
	    printf("%d  %s  %s",co[i].information.year,co[i].information.level,co[i].information.term);
	    printf("%d",co[i].score);
	}
	fclose(fp);
}
//学生选课
void select(CO co[],int number[])
{
	int i;
	int sum=0;
	int ch;
	char n;
	//char *p=ac[0];
	//char *pi=co[0].number;
	printf("Elective total credit shall not be less than 15 points.\n");
    printf(" Please register carefully according to your interests\n");
	while(1)
	{
		printf(" Please select course according to the number\n");
		scanf("%s",&ch);
		for(i=0;i<N;i++)
		{
			if(ch==co[i].number)
			{
				sum=sum+co[i].score;
				printf("course number:%s   course score:%d\n",co[i].number,co[i].score);
                number[i]=co[i].number;
			}
			printf("total credit:%d\n",sum);
		}
		//printf("if you want to continue select,please input 'y'\n");
		printf("If you want to quit or complete the course please enter 'n'\n");
		getchar();
		scanf("%c",&n);
		if(n=='n')
			break;
	}
}
//学生选课查询
void query(CO co[],int number[])
{
	int i;
	printf("You take the following courses\n");
	for(i=0;i<N;i++)
	{
		if(number[i]==co[i].number)
		{
			printf("%d\t%s\t%s\n",co[i].number,co[i].name,co[i].nature);
		    printf("%d  %d   %d",co[i].classhour.teachhour,co[i].classhour.practicehour,co[i].score);
	        printf("%d  %s  %s",co[i].information.year,co[i].information.level,co[i].information.term);
	        printf("%d",co[i].score);
		}
	}
}
//根据学分查询课程
void selectbyscore(CO co[])
{
	int i;
	int score;
	printf("please input the score of you want to query\n");
	scanf("%d",&score);
	for(i=0;i<N;i++)
	{
	    if(score==co[i].score)
		{
			printf("%s\t%s\t%s\n",co[i].number,co[i].name,co[i].nature);
		    printf("%d  %d   %d",co[i].classhour.teachhour,co[i].classhour.practicehour,co[i].score);
	        printf("%d  %s  %s",co[i].information.year,co[i].information.level,co[i].information.term);
	        printf("%d",co[i].score);
		}
	}
}
//查询课程有多少人选修
void selectiveinformation(CO co[],int number[])
{
	int count=0;
	int i;
	printf("please input the number of you want to course\n");
	int num;
	scanf("%s",&number);
	for(i=0;i<N;i++)
		if(num==number[i])
			count++;
	printf("choose the course total have %d students\n",count);
}
