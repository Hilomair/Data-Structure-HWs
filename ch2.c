#include <stdio.h>
#include <stdlib.h>

/*
    時間複雜度：
        1. 字串處理：O(n^2) 去掉重複的符號 n為字串長度
        2. 做postfix：O(m+n) m為stack top[0] 的pop次數  n為字串長度
        3.計算result：O(m) m為stack top[0] 的pop次數 因為每次pop都會算一次
*/

typedef struct stack *stackPointer;
typedef struct stack {
    double data;
    stackPointer link;
};
stackPointer top[2] = {NULL};

void push(int i,double item)
{
    stackPointer tmp;
    tmp = malloc(sizeof(*tmp));
    tmp->data = item;
    tmp->link = top[i];
    top[i] = tmp;
}

double pop(int i)
{
    stackPointer tmp = top[i];
    double item;
    if(!tmp)
        return -1;
    item = tmp->data;
    top[i] = tmp->link;
    free(tmp);
    return item;
}

char Input[10005];
/* ( , ) , + , - , * , / , % , eos */
int isp[] = {0,19,12,12,13,13,13,-1e7};
int icp[] = {20,19,12,12,13,13,13,-1e7};


double getInt(int *i)
{
    int sign = 1,tmp = Input[*i] - '0';
    if((*i)>=2 && Input[(*i)-1] == '-' && !(Input[(*i)-2]>='0' && Input[(*i)-2]<='9') && Input[*i-1] != Input[*i-2])
        sign = -1;
    else if( (*i)==1 && Input[(*i)-1] == '-')
        sign = -1;
    tmp *= sign;
    while(Input[(*i)+1]>='0' && Input[(*i)+1]<='9')
    {
        (*i)++;
        tmp*=10;
        tmp+=(Input[*i] - '0')*sign;
    }
    return tmp;
}

int getToken(char t)
{
    switch (t)
    {
        case '(' : return 0;
        case ')' : return 1;
        case '+' : return 2;
        case '-' : return 3;
        case '*' : return 4;
        case '/' : return 5;
        case '%' : return 6;
        case '\n' : return 7;
    }
}

int printToken(int t)
{
    switch (t)
    {
        case 0 : return '(';
        case 1 : return ')';
        case 2 : return '+';
        case 3 : return '-';
        case 4 : return '*';
        case 5 : return '/';
        case 6 : return '%';
        case 7 : return '\n';
    }
}

double cnt_sum(double a,double b,int t)
{
    //printf("%lf %lf %d\n",a,b,t);
    switch(t)
    {
        case 2 : return a+b;
        case 3 : return a-b;
        case 4 : return a*b;
        case 5 : return a/b;
    }
}

int main()
{
    int t,i,j;
    double b,a,sum;
    freopen("infix.txt","r",stdin);
    freopen("postfix.txt","w",stdout);
    while(fgets(Input,10005,stdin) != NULL)
    {
        if(Input[0] == '\n')    continue;
        for(i=0;i<strlen(Input)-1;i++)
        {

            if(Input[i] == Input[i+1] && Input[i] == '+')
            {
                Input[i] = '+';
                for(j=i+2;j<strlen(Input);j++)
                    Input[j-1] = Input[j];
                Input[strlen(Input)-1] = '\0';
            }
            else if(Input[i] == Input[i+1] && Input[i] == '-' && Input[i+2]>='0' && Input[i+2]<='9')
            {
                Input[i] = '+';
                for(j=i+2;j<strlen(Input);j++)
                    Input[j-1] = Input[j];
                Input[strlen(Input)-1] = '\0';
            }
            else if(Input[i] == Input[i+1] && Input[i] == '-')
            {
                for(j=i+2;j<strlen(Input);j++)
                    Input[j-2] = Input[j];
                Input[strlen(Input)-2] = '\0';
                i--;
            }
        }
        push(0,7);
        push(1,-1000.0);
        //for(i=0;i<strlen(Input);i++)
            //printf("%c ",Input[i]);
        for(i=0;i<strlen(Input);i++)
        {
            if(Input[i]>='0' && Input[i]<='9')
            {
                double tmp = getInt(&i);
                //printf("%lf ",tmp);
                printf("%d ",(int)tmp);
                push(1,tmp);
            }
            else
            {
                if(Input[i] == '-' && i==0) continue;
                if(Input[i] == '-' && i!=0 && !(Input[i-1]>='0' && Input[i-1]<='9') && Input[i-1] != Input[i]) continue;
                int token = getToken(Input[i]);
                if(token == 7)  break;
                if(token == 1)
                {
                    while(top[0]->data != 0)
                    {
                        t = pop(0);
                        b = pop(1) , a = pop(1);
                        sum = cnt_sum( a,b,t );
                        printf("%c ",printToken(t) );
                        push(1,sum);
                    }
                    pop(0);
                }
                else
                {
                    //printf("%d\n",top->data);
                    while(isp[(int)top[0]->data] >= icp[token])
                    {
                        t = pop(0);
                        b = pop(1) , a = pop(1);
                        sum = cnt_sum( a,b,t );
                        printf("%c ",printToken(t) );
                        push(1,sum );
                    }
                    push(0,token);

                }
            }
        }
        while(top[0]->data != 7)
        {
            t = pop(0);
            b = pop(1) , a = pop(1);
            sum = cnt_sum( a,b,t );
            printf("%c ",printToken(t) );
            push(1,sum );
        }
        printf(" %lf\n",pop(1));
        while(top[1]->data != -1000)
            pop(1);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
