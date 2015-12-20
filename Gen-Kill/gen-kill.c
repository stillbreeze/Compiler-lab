#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int leaderPos[50],i=0,blocks[20][20],j=0,lNo[50],k=0,graph[10][10]={0},gen[10][20],kill[10][20],m=0;
char l[50][50];


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
//Checks if a line contains a goto and then splits the goto keyword and the target address
//Stores the goto target address and the next address to an array of leaders
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
//Splits the address and the TAC
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
    lNo[k]=atoi(lineNo);
    strcpy(l[k],line);
    k++;
    //printf("No: %s\t",lineNo);
    //printf("Line: %s",line);
    split2(lineNo,line);
}

int findLastLine(int t)
{
    int a=0;

    while(lNo[a]!=t)
        a++;
    return a;
}

int findBlock(int lno)
{
    int a,b,t;

    for(a=0;a<j;a++)
    {
        t=blocks[a][0];
        for(b=1;b<=t;b++)
        {
            if(blocks[a][b]==lno)
                return a;
        }
    }
}

//Prints the leaders
void printLeader()
{
    int a;
    sort();
    printf("\n\nLEADERS\n");
    for(a=0;a<i;a++)
        printf("%d\t",leaderPos[a]);
}

void printFlowGraph()
{
    int a,b;

    printf("\n\nFLOW GRAPH\n");
    for(a=0;a<j;a++)
    {
        for(b=0;b<j;b++)
        {
            printf("%d\t",graph[a][b]);
        }
        printf("\n");
    }
}


/*------------------------------------------------------------------------------------------------------------------------------------------------*/

//Reads from the file line by line and calls split1() for each line
void getLeader()
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    size_t read;
    int i, j, k, z, flag;

    fp = fopen("input.txt", "r");
    printf("CODE\n");
    while (read=getline(&line,&len,fp)!=-1)
        split1(line);
    fclose(fp);
    printLeader();
}

//Prints the blocks
//TODO - remove the TACs with goto statements and conditionals from the block
void getBlocks()
{
    int c,d,e;
    printf("\n\nBLOCKS");
    for(c=0;c<i-2;c++)
    {
        if(leaderPos[c]!=leaderPos[c+1] || leaderPos[c+1]==lNo[k])
        {
            printf("\nBlock %d:\t",j+1);
            for(e=1,d=leaderPos[c];d<leaderPos[c+1];e++,d++)
            {
                blocks[j][e]=d;
                printf("%d\t ",d);
            }
            blocks[j][0]=e-1;
            j++;
        }
    }
}

void makeFlowGraph()
{
    int a,s,t,n;
    char *b,*res,*tokens;;
    for(a=0;a<j;a++)
    {
        graph[a][a+1]=1;

        s=blocks[a][0];
        t=blocks[a][s];
        s=findLastLine(t);
        b=l[s];

        res=strstr(b,"goto");
        if(res!=NULL)
        {
            tokens=strtok(res," ");
            while(tokens!=NULL)
            {
                if(n>0)
                {
                    t=findBlock(atoi(tokens));
                    graph[a][t]=1;
                }
                n++;
                tokens=strtok(NULL," ");
            }
        }
    }
    printFlowGraph();
}

void findGen()
{
    int a,b,t,s=0,c;
    char *res;
    printf("\nGEN\n");

    for(a=0;a<j;a++)
    {
        c=1;
        t=blocks[a][0];
        for(b=1;b<=t;b++)
        {
            res=strstr(l[s],"goto");
            if(res==NULL)
            {
                gen[a][c]=lNo[s];
                c++;
            }
            s++;
        }
        gen[a][0]=c-1;
    }
    for(a=0;a<j;a++)
    {
        t=gen[a][0];
        printf("Block %d:\t\t",a+1);
        for(b=1;b<=t;b++)
            printf("%d\t",gen[a][b]);
        printf("\n");
    }

}

void findKill()
{
    int a,b,n=0,flag,t,killed[20][20],s=0;
    char *tokens,*var[20],*res,p=0,m=0;
    for(a=0;a<k;a++)
    {
        res=strstr(l[a],"goto");
        if(res==NULL && a!=k-1)
        {
            flag=0;
            tokens=strtok(l[a],"=");
            for(b=0;b<m;b++)
            {
                printf("\n%s %s\n",var[b],tokens);
                if(strcmp(var[b],tokens)==0)
                {
                    flag=1;
                    p=killed[b][0];
                    killed[b][p+1]=lNo[a];
                    killed[b][0]=p+1;
                }
            }
            if(flag==0)
            {
                var[m]=tokens;
                killed[m][1]=lNo[a];
                killed[m][0]=1;
                m++;
            }
        }
    }
    printf("\n\n");
    for(a=0;a<m;a++)
    {
        t=killed[a][0];
        for(b=1;b<=t;b++)
            printf("%d",killed[a][b]);
        printf("\n");
    }

    for(a=0;a<j;a++)
    {
        t=blocks[a][0];
        for(b=1;b<=t;b++)
        {
            res=strstr(l[a],"goto");
            if(res==NULL && a!=k-1)
            {
                tokens=strtok(l[s],"=");

            }
        }
    }

}

int main()
{
    getLeader();
    getBlocks();
    makeFlowGraph();
    findGen();
    findKill();
    return 0;
}
