#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "sl.h"

struct sl
{
    struct sl *prev;
    struct sl *next;
    char *string;
    int number;
    int type;
};

struct sl *create()
{
    struct sl *this = malloc(sizeof(struct sl));
    if (this)
    {
        this->next = this;
        this->prev = this;
    }
    return this;
};

void destroy(struct sl *s)
{
    while (!empty(s))
    {
        pop(s);
    }
    free(s);
};

int push_string(struct sl *s, const char *v)
{
    struct sl *this = malloc(sizeof(struct sl));
    if (this)
    {
        this->type = STRING_T;
        this->string = malloc(sizeof(char) * (strlen(v) + 1));
        strcpy(this->string, v);
        this->next = s;
        this->prev = s->prev;
        s->prev->next = this;
        s->prev = this;
        return 1;
    }
    return 0;
};

int push_integer(struct sl *s, int v)
{
    struct sl *this = malloc(sizeof(struct sl));
    if (this)
    {
        this->type = INTEGER_T;
        this->number = v;
        this->next = s;
        this->prev = s->prev;
        s->prev->next = this;
        s->prev = this;
        return 1;
    }
    return 0;
};

int add(struct sl *s)
{
    if (empty(s))
        return 0;

    if (get_type(s) == get_type(s->prev))
    {
        if (get_type(s) == INTEGER_T)
        {
            s->prev->prev->number += s->prev->number;
            return pop(s);
        }
        else
        {
            char *temp = s->prev->string;
            char *temp2 = s->prev->prev->string;
            pop(s);
            pop(s);
            strcat(temp2, temp);
            push_string(s, temp2);
            return 1;
        }
    }
    return 0;
};

int divide(struct sl *s)
{
    if (empty(s->next))
        return 0;

    struct sl *temp = s->prev;

    if (get_type(s) == get_type(temp))
    {
        if (get_type(s) == INTEGER_T)
        {
            if (temp->number == 0)
                return 0;

            int remainder = temp->prev->number % temp->number;
            int quotient = temp->prev->number / temp->number;
            temp->prev->number = quotient;
            temp->number = remainder;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 0;
};


int multiply(struct sl *s)
{
    if (s->prev == s->next)
        return 0;

    int n;
    const char *str;
    struct sl *temp = s->prev;

    if (get_type(s) == get_type(temp))
    {
        if (get_type(s) == STRING_T)
            return 0;

        if (get_type(s) == INTEGER_T)
        {
            n = get_integer(s);
            pop(s);
            s->prev->number = s->prev->number * n;
            return 1;
        }
    }
    else
    {
        if (get_type(s) == INTEGER_T)
        {
            n = get_integer(s);
            if (n == 0)
            {
                pop(s);
                s->prev->string = "";
                return 1;
            }
            else if (n == 1)
            {
                pop(s);
                return 1;
            }
            else if (n > 1)
            {
                pop(s);
                str = get_string(s);
                pop(s);

                size_t size = sizeof(str)*n;
                char *concat = malloc(size);
                strcpy(concat, str);

                while (n > 1)
                {  
                    strcat(concat, str);
                    --n;
                }
                push_string(s, concat);
                
                return 1;
            }
        }
        else
        {
            str = get_string(s);
            pop(s);
            n = get_integer(s);
            pop(s);

            if (n == 0)
            {
                push_string(s, "");
                return 1;
            }
            else if (n == 1)
            {
                push_string(s, str);
                return 1;
            }
            else if (n > 1)
            {
                size_t size = sizeof(str)*n;
                char *concat = malloc(size);
                strcpy(concat, str);

                while (n > 1)
                {
                    strcat(concat, str);
                    --n;
                }
                push_string(s, concat);
                //free(concat);
                return 1;
            }
        }
       
    } return 0;
};

int duplicate(struct sl *s)
{
    if (empty(s->next))
        return 0;

    if (get_type(s) == INTEGER_T)
    {
        return push_integer(s, s->prev->number);
    }
    else if (get_type(s) == STRING_T)
    {
        return push_string(s, s->prev->string);
    }

    return 0;
};

int swap(struct sl *s)
{
    if (s->prev == s->next)
        return 0;

    struct sl *temp1 = s->prev;
    struct sl *temp2 = s->prev->prev;

    temp1->prev = temp2->prev;
    temp1->next = temp2;
    temp2->prev->next = temp1;
    temp2->prev = temp1;
    temp2->next = s;
    s->prev = temp2;
    return 1;
};

int pop(struct sl *s)
{
    if (empty(s))
        return 0;
    else
    {
        struct sl *temp = s->prev;
        temp->prev->next = s;
        s->prev = s->prev->prev;
        free(temp);
        return 1;
    }
};

int empty(struct sl *s)
{
    return s->next == s && s->prev == s;
};

int get_type(struct sl *s)
{
    if (!empty(s))
        return s->prev->type;
};

int get_integer(struct sl *s)
{
    if (get_type(s) == INTEGER_T)
        return s->prev->number;
};

const char *get_string(struct sl *s)
{
    if (get_type(s) == STRING_T)
        return s->prev->string;
};
