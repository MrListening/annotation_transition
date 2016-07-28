#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#define INPUTFNAME "input.c"
#define OUTPUTFNAME "output.c"
typedef enum tates
{
	Null_State,
	C_State,
	Cpp_State,
	W_State,
	End_State
}StateType;

void CommentConvert();

void ConvertWork(FILE* read, FILE* write);

void DoNullState(FILE* read, FILE* write);
void DoCState(FILE* read, FILE* write);
void DoCppState(FILE* read, FILE* write);
void DoEndState(FILE* read, FILE* write);



