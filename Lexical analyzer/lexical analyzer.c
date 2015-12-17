#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


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
        if(isalpha(expr[i]) || expr[i]=='_')
        {
            temp[i] = 1;
        }
        else if(isdigit(expr[i]))
        {
            temp[i] = 2;
        }
        else
        {
            temp[i] = 3;
        }
    }
    if(temp[0]==1)
        return 1;
    else if(temp[0]==2)
        return 2;
    else if(temp[0]==3)
        return 3;
}


int match(int init, int arr[4][3], int temp[50], int n_inputs, int expr_len)
{
    int i,current=init,next;
    for(i=0;i<expr_len;i++)
    {
        if(arr[current][temp[i]-1]==3)
            return 0;
        else if(arr[current][temp[i]-1]==1 || arr[current][temp[i]-1]==2)
        {
            next=arr[current][temp[i]-1];
            current=next;
        }
    }
        return 1;
}

void check_escape()
{
    char esc;
    printf("\n");
    printf("Press X to escape:\t");
    scanf("%c",&esc);
    printf("\n");
    if(esc=='X')
        exit(0);
}

int main()
{
    int init=0,n_inputs=3;
    int arr[4][3]={{1,2,3},{1,1,3},{3,2,3},{3,3,3}},temp[50],expr_len,lex_type;
    char expr[50];

    while(1)
    {
        take_expr(expr);
        lex_type=change_expr_type(expr,n_inputs,temp);
        expr_len=strlen(expr);
        if(match(init,arr,temp,n_inputs,expr_len))
        {
            printf("ACCEPTED\t");
            if(lex_type==1)
                printf("Type: Identifier\n");
            else if(lex_type==2)
                printf("Type: Number\n");
        }
        else
            printf("INVALID\n");

        check_escape();
    }

    return 0;
}
