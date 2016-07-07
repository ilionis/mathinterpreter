#include "parcer.h"

QUAD *parcer(char *str)
{
    char ch, ch_p = '(';
    QUAD *q = NULL;
    STACK1 *s = NULL;
    ch = getChar(&str);
    while (ch != '\0')
    {
        if (ch == '-' && !isDigit(ch_p))
        {
            returnChar(&str, ch);
            push_quad(&q, getValue(&str));
        }
        else if (isDigit(ch))
        {
            returnChar(&str, ch);
            push_quad(&q, getValue(&str));
        }
        else if (ch == '(')
        {
            char *t = (char*)malloc(2);
            t[0] = ch;
            t[1] = '\0';
            push1(&s, t, _true(ch, 0));
        }
        else if (ch == ')')
        {
            char temp;
            temp = *(pop1(&s));
            while (temp != '(')
            {
                char *t = (char*)malloc(2);
                t[0] = temp;
                t[1] = '\0';
                push_quad(&q, t);
                temp = *(pop1(&s));
            }
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            while ((s != NULL) && (_true(ch, s->a) <= 0))
            {
                push_quad(&q, pop1(&s));
            }
            char *t = (char*)malloc(2);
            t[0] = ch;
            t[1] = '\0';
            push1(&s, t, _true(ch, 0));
        }
        else if (ch == '^')
        {
            while ((s != NULL) && (_true(ch, s->a) < 0))
            {
                push_quad(&q, pop1(&s));
            }
            char *t = (char*)malloc(2);
            t[0] = ch;
            t[1] = '\0';
            push1(&s, t, _true(ch, 0));
        }
        ch_p = (ch == ')') ? '0' : ch;
        ch = getChar(&str);
    }
    while (s != NULL)
        push_quad(&q, pop1(&s));
    return q;
}

int isDigit(char ch)
{
    if (ch >= '0' && ch <= '9')
        return 1;
    return 0;
}

void returnChar(char **str, char ch)
{
    (*str)--;
}

char getChar(char **str)
{
    char t = (*str)[0];
    (*str)++;
    return t;
}

char *getValue(char **str)
{
    int i = 0;
    char *s = (*str);
    while (s[i] != '\0' && (isDigit(s[i]) || s[i] == '-'))
        i++;
    char *s_t = (char*)malloc(i);
    strcpy(s_t, *str);
    s_t[i] = '\0';
    (*str) += i;
    return s_t;
}

int _true(char ch, int i)
{
    switch (ch)
    {
    case '(':
    case ')':
        if (i == 1)
            return 0;
        if (i > 1)
            return -1;
        return 1;

    case '+':
    case '-':
        if (i == 2)
            return 0;
        if (i > 2)
            return -1;
        return 2;

    case '*':
    case '/':
        if (i == 3)
            return 0;
        if (i > 3)
            return -1;
        return 3;

    case '^':
        if (i == 4)
            return 0;
        if (i > 4)
            return -1;
        return 4;
    }
}
