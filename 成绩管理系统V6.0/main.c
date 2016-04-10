//
//  main.c
//  成绩管理系统V6.0
//
//  Created by 李展 on 15/11/17.
//  Copyright © 2015年 李展. All rights reserved.
//

#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#define N 30
#define MAX_LEN 15
#define COURSE 6
struct student
{
    char name[MAX_LEN];
    long studentID;
    int score[COURSE];
    int sum;
    float aver;
};
typedef struct student STU;
int ReadScore(STU stu[]);
void AverforCourse(STU stu[],int n,int sumc[],float averc[N]);
void AverforStudent(STU stu[],int n);
int Ascending(int a,int b);
int Descending(int a,int b);
void SelectionSort(STU stu[],int n,int (*compare)(int a,int b));
void ScoreSwap(int *x,int *y);
void NumSwap(long *x,long *y);
void NameSwap(char str1[],char str2[]);
void NumSort(STU stu[],int n);
void NameSort(STU stu[],int n);
int NumSearch(STU stu[],long searchNum,int n);
int NameSearch(STU stu[],char searchName[],int n);
void Statistics(STU stu[],int n);
void PrintScore(STU stu[],int n,int sumc[],float averc[]);
void WritetoFile(STU stu[],int n);
int ReadfromFile(STU stu[]);


int main(int argc, char* argv[])
{
    STU stu[N];
    int n = 0,choice,pos1,pos2,sumc[COURSE];
    long searchNum;
    float averc[N];
    char searchName[MAX_LEN];
    do{
        printf("1.Input record\n");
        printf("2.Caculate total and average score of ever course\n");
        printf("3.Caculate total and average score of ever student\n");
        printf("4.Sort in descending order by score\n");
        printf("5.Sort in ascending order by score\n");
        printf("6.Sort in ascending order by number\n");
        printf("7.Sort in dictionary order by name\n");
        printf("8.Search by number\n");
        printf("9.Search by name\n");
        printf("10.Statistic analysis for every course\n");
        printf("11.List record\n");
        printf("12.Write to a file\n");
        printf("13.Read from a file\n");
        printf("0.Exit\n");
        printf("Please enter your choice:");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1:
                n=ReadScore(stu);
                break;
            case 2:
                AverforCourse(stu, n, sumc,averc);
                break;
            case 3:
                AverforStudent(stu, n);
                break;
            case 4:
                SelectionSort(stu, n, Ascending);
                break;
            case 5:
                SelectionSort(stu, n, Descending);
                break;
            case 6:
                NumSort(stu, n);
                break;
            case 7:
                NameSort(stu, n);
                break;
            case 8:
                printf("Input the searching ID:");
                scanf("%ld",&searchNum);
                pos1=NumSearch(stu,searchNum,n);
                if (pos1 != -1) {
                    printf("The name is %s\n",stu[pos1].name);
                    printf("The score is:\n");
                    for (int i=0; i<COURSE; i++) {
                        printf("%d\n",stu[pos1].score[i]);
                    }
                }
                else
                    printf("Not found\n");
                break;
            case 9:
                printf("Input the searching Name:");
                scanf("%s",searchName);
                pos2=NameSearch(stu, searchName, n);
                if (pos2 != -1) {
                    printf("The IDnumber is %ld\n",stu[pos2].studentID);
                    printf("The score is:\n");
                    for (int i=0; i<COURSE; i++) {
                        printf("%d\n",stu[pos2].score[i]);
                    }
                }
                else
                    printf("Not found\n");
                break;
            case 10:
                Statistics(stu,n);
                break;
            case 11:
                PrintScore(stu, n, sumc, averc);
                break;
            case 0:
                exit(0);
            default:
                printf("Input wrong\n");
        }
    }while (choice);
    
    return 0;
}


int ReadScore(STU stu[])
{
    int i=-1,j=0;
    printf("Input student's name ,ID and six course score:\n");
    do {
        i++;
        scanf("%s",stu[i].name);
        if (strcmp(stu[i].name, "stop")==0) {
            return i;
        }
        scanf("%ld",&stu[i].studentID);
        for ( j=0; j<COURSE; j++) {
            scanf("%d",&stu[i].score[j]);
            if (stu[i].score[j]<0 || stu[i].studentID<=0) {
                return i;
            }
        }
    } while (stu[i].studentID>0);
    return i;
}


void AverforCourse(STU stu[],int n,int sumc[],float averc[N])
{
    for(int i=0;i<COURSE;i++)
    {
        sumc[i]=0;
        for (int j=0; j<n; j++) {
            sumc[i]+=stu[j].score[i];
        }
        averc[i]=(float)sumc[i]/n;
    }
}

void AverforStudent(STU stu[],int n)
{
    for (int i=0; i<n; i++) {
        stu[i].sum=0;
        for (int j=0; j<COURSE; j++) {
            stu[i].sum+=stu[i].score[j];
        }
        stu[i].aver=(float)stu[i].sum/COURSE;
    }
}

int Ascending(int a,int b)
{
    return a<b;
}


int Descending(int a,int b)
{
    return a>b;
}


void SelectionSort(STU stu[],int n,int (*compare)(int a,int b))
{
    for (int i=0; i<n-1; i++)
    {
        int k=i;
        for (int j=i+1; j<n; j++)
        {
            if ((*compare)(stu[j].sum,stu[k].sum)) {
                k=j;
            }
        }
        if (k!=i) {
            ScoreSwap(&stu[i].sum, &stu[k].sum);
            NumSwap(&stu[i].studentID,&stu[k].studentID);
            NameSwap(stu[i].name, stu[k].name);
        }
    }
}

void ScoreSwap(int *x,int *y)
{
    int temp;
    temp=*x;
    *x=*y;
    *y=temp;
}


void NumSwap(long *x,long *y)
{
    long temp;
    temp=*x;
    *x=*y;
    *y=temp;
    
}
void NameSwap(char str1[],char str2[])
{
    char temp[MAX_LEN];
    strcpy(temp,str1);
    strcpy(str1,str2);
    strcpy(str2, temp);
}


void NumSort(STU stu[],int n)
{
    for (int i=0;i<n-1;i++) {
        int k=i;
        for (int j=i+1; j<n; j++) {
            if (stu[j].studentID<stu[k].studentID) {
                k=j;
            }
        }
        if (k!=i) {
            for (int c=0; c<COURSE; c++) {
                ScoreSwap(&stu[k].score[c], &stu[i].score[c]);
            }
            NumSwap(&stu[i].studentID,&stu[k].studentID);
            NameSwap(stu[i].name, stu[k].name);
        }
    }
}



void NameSort(STU stu[],int n)
{
    for (int i=0; i<n-1; i++) {
        int k=i;
        for (int j=i+1; j<n; j++) {
            if (strcmp(stu[j].name, stu[k].name)<0) {
                k=j;
            }
        }
        if (k!=i) {
            for (int c=0; c<COURSE; c++) {
                ScoreSwap(&stu[k].score[c], &stu[i].score[c]);
            }
            NumSwap(&stu[i].studentID,&stu[k].studentID);
            NameSwap(stu[i].name, stu[k].name);
        }
    }
}

int NumSearch(STU stu[],long searchNum,int n)
{
    for (int i=0; i<n; i++)
    {
        if (stu[i].studentID==searchNum) {
            return i;
        }
    }
    return -1;
}


int NameSearch(STU stu[],char searchName[],int n)
{
    for (int i=0; i<n; i++) {
        if(!strcmp(stu[i].name, searchName)) return i;
    }
    return -1;
}


void Statistics(STU stu[],int n)
{
    int excellent[COURSE],good[COURSE],medium[COURSE],pass[COURSE],fail[COURSE];
    for (int i=0; i<COURSE; i++)
    {
        excellent[i]=good[i]=medium[i]=pass[i]=fail[i]=0;
        for (int j=0; j<n; j++) {
            if (stu[j].score[j]<=100 && stu[j].score[j]>=90) excellent[i]++;
            else if (stu[j].score[j]<=89 && stu[j].score[j]>=80) good[i]++;
            else if (stu[j].score[j]<=79 && stu[j].score[j]>=70) medium[i]++;
            else if (stu[j].score[j]<=69 && stu[j].score[j]>=60) pass[i]++;
            else fail[i]++;
        }
    }
    for (int i=0; i<COURSE; i++) {
        printf("%d:\n",i+1);
        printf("The excellent(90-100) rate is %f\n",(float)excellent[i]/n);
        printf("The good(80-89) rate is %f\n",(float)good[i]/n);
        printf("The medium(70-79) rate is %f\n",(float)medium[i]/n);
        printf("The pass(60-69) rate is %f\n",(float)pass[i]/n);
        printf("The fail(<60) rate is %f\n",(float)fail[i]/n);
        printf("\n");
    }
}




void PrintScore(STU stu[],int n,int sumc[],float averc[])
{
    printf("NAME\t STUDENT'S ID\t 1\t 2\t 3\t 4\t 5\t 6\t SUM\t AVER\n");
    for(int i=0;i<n;i++)
    {
        printf("%s\t",stu[i].name);
        printf("%11ld\t",stu[i].studentID);
        for (int j=0; j<COURSE; j++) {
            printf("%4d",stu[i].score[j]);
        }
        printf("%4d\t%5.1f\n",stu[i].sum,stu[i].aver);
    }
    printf("SumofCourse\t");
    for (int i=0; i<COURSE; i++) {
        printf("%4d\t",sumc[i]);
    }
    printf("\nAverofCourse\t");
    for (int i=0; i<COURSE; i++) {
        printf("%4.1f\t",averc[i]);
    }
    printf("\n");
}

void WritetoFile(STU stu[],int n)
{
    FILE *fp;
    if ((fp=fopen("/Users/lizhan666/text", "w"))==NULL) {
        printf("Failure to open text!\n");
        exit(0);
    }
    fwrite(stu, sizeof(STU), n, fp);
    fclose(fp);
}

int ReadfromFile(STU stu[])
{
    int i;
    FILE *fp;
    if ((fp=fopen("/Users/lizhan666/desktop/txt.txt", "r"))==NULL) {
        printf("Failure to open text!\n");
        exit(0);
    }
    for (i=0 ; !feof(fp); i++) {
        fread(&stu[i], sizeof(STU), 1, fp);
    }
    fclose(fp);
    printf("Total students is %d.\n",i-1);
    return i-1;
}
