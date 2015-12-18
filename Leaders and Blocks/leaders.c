#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int leaderPos[50],i=0;

void sort()
{
    int c,d,t;
    for (c=1;c<i;c++)
    {
        d=c;
        while(d>0 && leaderPos[d]<leaderPos[d-1])
        {
            t=leaderPos[d];
            leaderPos[d]   = leaderPos[d-1];
            leaderPos[d-1] = t;
            d--;
        }
    }
}

void split2(char* lineNo,char* line)
{
    char *res,*tokens;
    int n=0;
    res=strstr(line,"goto");
    if(res!=NULL)
    {
        leaderPos[i]=atoi(lineNo)+1;
        i++;
        tokens=strtok(res," ");
        while(tokens!=NULL)
        {
            if(n>0)
            {
                leaderPos[i]=atoi(tokens);
                i++;
            }
            n++;
            tokens=strtok(NULL," ");
        }
    }
}

void split1(char* line)
{
    char *tokens,*lineNo;
    int n=0;
    printf("%s",line);
    tokens=strtok(line,":");
    while(tokens!=NULL)
    {
        if(n==0)
            lineNo=tokens;
        else
            line=tokens;
        n++;
        tokens=strtok(NULL,":");
    }
    //printf("No: %s\t",lineNo);
    //printf("Line: %s",line);
    split2(lineNo,line);
}

void getLeader()
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    size_t read;
    int i, j, k, z, flag;

    fp = fopen("input.txt", "r");
    while (read=getline(&line,&len,fp)!=-1)
        split1(line);
    fclose(fp);
}

void printLeader()
{
    int j;
    sort();
    printf("\n\nThe leaders are:\n");
    for(j=0;j<i;j++)
        printf("%d\t",leaderPos[j]);
}

void printBlocks()
{
    int c,d;
    printf("\n");
    for(c=0;c<i-1;c++)
    {
        if(leaderPos[c]!=leaderPos[c+1])
        {
            printf("\nBlock %d:\t",c+1);
            for(d=leaderPos[c];d<leaderPos[c+1];d++)
                printf("%d\t ",d);
        }
    }
}

int main()
{
    getLeader();
    printLeader();
    printBlocks();
    return 0;
}
