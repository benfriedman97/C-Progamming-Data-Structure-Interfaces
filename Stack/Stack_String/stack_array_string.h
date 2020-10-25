/*Header file for stack of strings interface using an array for the stack. 
The length of each string in the stack is limited to len (if len is 30, then a string of 
size 30 can fit in each spot in the stack*/

#ifndef STACK_STRING_H
#define STACK_STRING_H

#include "status.h"

typedef void* STACK_STRING;

STACK_STRING stackstringInitDefault(int capacity, int len);
Status stackstringPush(STACK_STRING hStack_string, char *str, int len);
Status stackstringPop(STACK_STRING hStack_string);
Boolean stackstringIsEmpty(STACK_STRING hStack_string);
char* stackstringGetTopItem(STACK_STRING hStack_string);
void stackstringDestroy(STACK_STRING *phStack_string);

#endif
