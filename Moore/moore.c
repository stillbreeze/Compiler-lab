
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void take_expr(char expr[50])
{
    printf("Enter the expression:\t");
    gets(expr);
}

int change_expr_type(char expr[50], int n_inputs, int temp[50])
{
    int i;
    for(i=0;i<strlen(expr);i++)
    {
        if(expr[i]<=96+n_inputs)
            temp[i]=(int)expr[i]-96;
        else
            return 0;
    }
    return 1;
}


int match(int init, int fin, int arr[4][2], int temp[50], int n_inputs, int expr_len, int out[4], int output[50])
{
    int i,current=init,next,j=0;
    for(i=0;i<expr_len;i++)
    {
        if(arr[current-1][temp[i]-1])
        {
            next=arr[current-1][temp[i]-1];
            current=next;
            output[j]=out[current-1];
            j++;
        }
        else
            return 0;
    }
    if(current==fin)
        return j;
    else
        return 0;
}

void check_escape()
{
    char esc;
    printf("\n");
    printf("Press X to escape:\t");
    scanf("%c",&esc);
    if(esc=='X')
        exit(0);
}

int main()
{
    int init=1,fin=3,n_inputs=2,k,j;
    int arr[4][2]={{1,2},{2,3},{2,4},{3,0}}, out[4]={1,2,2,1}, output[50], temp[50], expr_len;
    char expr[50];

    while(1)
    {
        take_expr(expr);
        if(!change_expr_type(expr,n_inputs,temp))
        {
            printf("Input symbol not present. Try again\n");
            continue;
        }
        else
        {
            expr_len=strlen(expr);
            j=match(init,fin,arr,temp,n_inputs,expr_len,out,output);
            if(j)
            {
                printf("The expression satisfies the given automata\n");
                printf("The output is :\t");
                for(k=0;k<j;k++)
                    printf("%c",(char)output[k]+96);
            }
            else
                printf("Expression does't satisfy the given automata\n");
        }
        check_escape();
    }

    return 0;
}
