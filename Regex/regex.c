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


int match(int init, int fin, int arr[4][2], int temp[50], int n_inputs, int expr_len)
{
    int i,current=init,next;
    for(i=0;i<expr_len;i++)
    {
        if(arr[current-1][temp[i]-1])
        {
            next=arr[current-1][temp[i]-1];
            current=next;
        }
        else
            return 0;
    }
    if(current==fin)
        return 1;
    else
        return 0;
}

void check_escape()
{
    char esc;
    printf("Press X to escape:\t");
    scanf("%c",&esc);
    if(esc=='X')
        exit(0);
}

int main()
{
    int init=1,fin=3,n_inputs=2;
    int arr[4][2]={{1,2},{2,3},{2,4},{3,0}},temp[50],expr_len;
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
            if(match(init,fin,arr,temp,n_inputs,expr_len))
                printf("The expression satisfies the given automata\n");
            else
                printf("Expression does't satisfy the given automata\n");
        }
        check_escape();
    }

    return 0;
}
