#ifndef SL_H_INCLUDED
#define SL_H_INCLUDED

#define STRING_T  1
#define INTEGER_T 2

struct sl;

struct sl * create();
void destroy(struct sl * s);

int push_string (struct sl * s, const char * v);
int push_integer (struct sl * s, int v);

int add (struct sl * s);
int divide (struct sl * s);
int multiply (struct sl * s);

int duplicate (struct sl * s);
int swap (struct sl * s);

int pop (struct sl * s);
int empty (struct sl * s);

int get_type (struct sl * s);
int get_integer (struct sl * s);
const char * get_string (struct sl * s);

#endif
