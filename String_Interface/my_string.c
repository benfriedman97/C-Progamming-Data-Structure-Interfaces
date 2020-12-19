#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "generic.h"

typedef struct my_string {
    int size,
    capacity;
    char* data;
} My_string;


MY_STRING my_string_init_default(void)
{
    My_string* pString = (My_string*)malloc(sizeof(My_string));

  /*Initialize string object with enough space to store 7 characters*/
  if (pString != NULL) {
    pString->size = 0;
    pString->capacity = INIT_STRING_CAPACITY;
    pString->data = (char*)malloc(sizeof(char) * pString->capacity);
    if (pString->data == NULL) {
      free(pString);
      return NULL;
    }
  }

  /*Return either NULL if first malloc failed or handle to new object*/
  return (MY_STRING)pString;
}


void my_string_destroy(ITEM *phItem)
{
  My_string* pString = (My_string*)*phItem;
  free(pString->data);//free the array
  free(pString);//free the memory footprint of the object
  *phItem = NULL;//null terminate the pointer to handle to prevent dangling pointer
}


MY_STRING my_string_init_c_string(const char* c_string)
{
  int i, len;
  
  My_string* pString = (My_string*)malloc(sizeof(My_string));	//memory footprint
  if (pString != NULL) {
  //get length of c_string and allocate corresponding space in string object
    for (i = 0, len = 0; c_string[i] != '\0'; i++)
      len++;
    pString->data = (char*)malloc(sizeof(char) * (len + 1));
    if (pString->data == NULL) {
      free(pString);
      return NULL;
    }
    /*Copy c_string into string object*/
    else {
      for (i = 0; i < len; i++)
	pString->data[i] = c_string[i];
      pString->size = len;
      pString->capacity = len + 1;
    }
  }

  return (MY_STRING)pString;
}


int my_string_get_capacity(MY_STRING hMy_string)
{
  My_string* pString = (My_string*)hMy_string;
  return pString->capacity;
}


int my_string_get_size(MY_STRING hMy_string)
{
  My_string* pString = (My_string*)hMy_string;
  return pString->size;
}


int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
  char *pLstring, *pRstring;
  int lSize, rSize, minSize, matches;

  //cast to known types
  pLstring = ((My_string*)hLeft_string)->data;
  pRstring = ((My_string*)hRight_string)->data;
  //Get string sizes and size of minimum string
  lSize = my_string_get_size(hLeft_string);
  rSize = my_string_get_size(hRight_string);
  minSize = (lSize < rSize) ? lSize : rSize;

  for (matches = 0; matches < minSize; matches++)
    if (*pLstring != *pRstring) {
      //printf("matches = %d, size of smallest string = %d", matches, minSize);
      break;
    } else {
      pLstring++;
      pRstring++;
    }
  
  if (matches == minSize){
    //printf("matches = %d, size of smallest string = %d", matches, minSize);
    if (lSize == rSize)
      return 0;
    else if (lSize < rSize)
      return -matches;
    else
      return matches;
  }
  else
    return *pLstring < *pRstring ? -1 : 1;
}

/*Better version
int my_string_compare(char* s1, char* s2)
{
	int s1Size = strlen(s1);
	int s2Size = strlen(s2);
	int smallestSize = (s1Size < s2Size) ? s1Size : s2Size;

	for (int i = 0; i < smallestSize; i++) {
		if (s1[i] < s2[i])
			return -1;
		else if (s1[i] > s2[i])
			return 1;
	}

	if (s1Size == s2Size)
		return 0;
	else if (s1Size == smallestSize)
		return -1;
	return 1;
}
*/


Status my_string_extraction(MY_STRING hMy_string, FILE *fp)
{
    //printf("CALLED\n");
    //cast to the known type
    My_string* pMy_string = (My_string*)hMy_string;
    int count = 0, ch;

    //get rid of leading whitespace in the file
    do
	ch = fgetc(fp);
    while (ch != EOF && ((char)ch == ' ' || (char)ch == '\t' || (char)ch == '\n'));

    //while still in the string (haven't reached EOF or trailing whitespace)
    while (ch != EOF && (char)ch != ' ' && (char)ch != '\t' && (char)ch != '\n') {
	//if there is space in the string, store the character
	if (pMy_string->capacity > count)
	    pMy_string->data[count++] = (char)ch;
	//there is not enough space to store another character
	else {
	    //copy the current string into a temporary string
	    char *temp = (char*)malloc(sizeof(char) * pMy_string->capacity * RESIZE);
	    if (temp == NULL)
		return FAILURE;
	    for (int i = 0; i < count; i++)
		temp[i] = pMy_string->data[i];
	    free(pMy_string->data);
	    pMy_string->data = temp;
	    pMy_string->data[count++] = (char)ch;
	    pMy_string->capacity *= 2;
	}
	//printf("%c\n", ch);
	ch = fgetc(fp);	//get the next character
    }
    //printf("%d\n", count);
    pMy_string->size = count;    
    //no more strings in file (either immediately hit EOF or went through whitespace then hit EOF)
    if (count == 0)  //return failure upon empty string
	return FAILURE;
    else {//either at EOF or hit whitespace. Put char back if it's whitespace
	if (ch != EOF)
	    ungetc(ch, fp);
	return SUCCESS;
    }
}


Status my_string_insertion(MY_STRING hMy_string, FILE *fp)
{
  My_string* pMy_string = (My_string*)hMy_string;
  int count;

  for (count = 0; count < pMy_string->size; count++)
    fputc(pMy_string->data[count], fp);
  return count != 0 ? SUCCESS : FAILURE;
}



Status my_string_push_back(MY_STRING hMy_string, char item)
{
    My_string* pMy_string = (My_string*)hMy_string;

    /*If no space is left in the string, make a copy array double the size*/
    if (pMy_string->size >= pMy_string->capacity) {
     char *temp = (char*)malloc(sizeof(char) * pMy_string->capacity * RESIZE); 
      if (temp == NULL)
	return FAILURE;
      for (int i = 0; i < pMy_string->size; i++)
	temp[i] = pMy_string->data[i];
      free(pMy_string->data);
      pMy_string->data = temp;
      pMy_string->capacity *= 2;
    }

    /*Either not full yet, or was full and properly resized*/
    pMy_string->data[pMy_string->size++] = item;
    return SUCCESS;
}


Status my_string_pop_back(MY_STRING hMy_string)
{
  My_string* pMy_string = (My_string*)hMy_string;
  if (pMy_string->size <= 0)
    return FAILURE;
  pMy_string->size--;
  return SUCCESS;
}


char *my_string_at(MY_STRING hMy_string, int index)
{
  My_string* pMy_string = (My_string*)hMy_string;
  if (index < 0 || index > pMy_string->size - 1)
    return NULL;
  return &(pMy_string->data[index]);
}


char* my_string_c_str(MY_STRING hMy_string)
{
  My_string* pMy_string = (My_string*)hMy_string;

  if (pMy_string->size <= 0)  //return NULL if empty string
    return NULL;
  
  /*If no space is left in the string, make a copy array double the size*/
    if (pMy_string->size >= pMy_string->capacity) {
      char *temp = (char*)malloc(sizeof(char) * pMy_string->capacity * RESIZE); 
      if (temp == NULL)
	return FAILURE;
      for (int i = 0; i < pMy_string->size; i++)
	temp[i] = pMy_string->data[i];
      free(pMy_string->data);
      pMy_string->data = temp;
      pMy_string->capacity *= 2;
    }

    /*Null terminate string without actually null terminating it in the object
      by not increasing the size*/
    pMy_string->data[pMy_string->size] = '\0';
    return &(pMy_string->data[0]);
}


Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
  My_string* pResult = (My_string*)hResult;
  My_string* pAppend = (My_string*)hAppend;
  
  //resize pResult object if concatenating it will go over capacity
  if (pResult->size + pAppend->size > pResult->capacity) {
    char *temp = (char*)malloc(sizeof(char) * (pResult->size + pAppend->size)); 
      if (temp == NULL)
	return FAILURE;
      for (int i = 0; i < pResult->size; i++)
	temp[i] = pResult->data[i];
      free(pResult->data);
      pResult->data = temp;
      pResult->capacity = pResult->size + pAppend->size;
  }

  for (int i = pResult->size, j = 0; j < pAppend->size; i++, j++)
    	pResult->data[i] = pAppend->data[j];
  pResult->size = pResult->size + pAppend->size;
  return SUCCESS;
}


Boolean my_string_empty(MY_STRING hMy_string)
{
  My_string* pMy_string = (My_string*)hMy_string;
  if (pMy_string->size <= 0)
    return TRUE;
  return FALSE;
}


Status my_string_assignment(ITEM *pLeft, ITEM Right)
{
    My_string *Right_casted = (My_string*)Right;

    /*The object where the copy will be stored doe snot exist so a new
    object must be made to stroe the copy in*/
    if (*pLeft == NULL) {
	My_string *temp_left = (My_string*)malloc(sizeof(My_string));    //memory foorprint
	if (temp_left == NULL)
	    return FAILURE;
	temp_left->data = (char*)malloc(sizeof(char) * Right_casted->capacity);
	if (temp_left->data == NULL) {	    
	    free(temp_left);
	    return FAILURE;
	}
	temp_left->size = 0;
	temp_left->capacity = Right_casted->capacity;
	*pLeft = (ITEM)temp_left;
    }

    /*Either a new string object has been created or it already existed.
    If it was an empty object, pLeft_casted will contain a new object with
    a data of the capacity of Right. If it was not empty, pLeft will just
    have whatever information was in the object passed*/
    My_string *pLeft_casted = (My_string*)*pLeft;
    //if it already existed it may need resizing
    if (pLeft_casted->capacity < Right_casted->size) {
	char *temp_data = (char*)malloc(sizeof(char) * Right_casted->size);
	if (temp_data == NULL)
	    return FAILURE;
	free(pLeft_casted->data);
	pLeft_casted->data = temp_data;
	pLeft_casted->capacity = Right_casted->size;
    }
    //copy array and size/capacity
    for (int i = 0; i < Right_casted->size; i++)
	pLeft_casted->data[i] = Right_casted->data[i];
    pLeft_casted->size = Right_casted->size;
    return SUCCESS;
}


void my_string_print_string(MY_STRING hMy_string)
{
    My_string *pString = (My_string*)hMy_string;
    for (int i = 0; i < pString->size; i++)
	printf("%c", pString->data[i]);
    printf("\n");
}




//current word family: the old key
//new_key: new key being generated
//word: word being considered
Status get_word_key_value(MY_STRING hCurrent_word_family, MY_STRING hNew_key, MY_STRING hWord, char guess)
{
    My_string *pCurrent_word_family = (My_string*)hCurrent_word_family,
	    *pNew_key = (My_string*)hNew_key,
	    *pWord = (My_string*)hWord;
    int i;
    char *temp, ch;

    //resize the new key if necessary
    if (pNew_key->capacity < pCurrent_word_family->size) {
	temp = (char*)malloc(sizeof(char) * pCurrent_word_family->size);
	if (temp == NULL) {
	    printf("Failed to allocate while resizing new key during key function\n");
	    return FAILURE;
	}
	free(pNew_key->data);
	pNew_key->data = temp;
	pNew_key->capacity = pCurrent_word_family->size;
    }

    //new key was either resized or didn't need resizing at this point. Copy old key into it
    for (i = 0; i < pCurrent_word_family->size; i++)
	pNew_key->data[i] = pCurrent_word_family->data[i];
    pNew_key->size = pCurrent_word_family->size;

    //add the new letter to new key where appropiate
    if (guess >= 65 && guess <= 90)
	guess += 32;
    for (i = 0; i < my_string_get_size(hWord); i++) {
	ch = pWord->data[i];
	if (ch >= 65 && ch <= 90)
	    ch += 32;
	if (ch == guess)
	    pNew_key->data[i] = guess;
    }
    return SUCCESS;
}
