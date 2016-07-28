#include"CommentConvert.h"

StateType state;

void DoNullState(FILE* read, FILE* write)
{
	int first = fgetc(read);
	int second = 0;
	switch (first)
	{
	 case '/':
		 second = fgetc(read);
		 if (second == '*')
		 {
			 fputc(first, write);
			 fputc('/', write);
			 state = C_State;
		 }
		 else if (second == '/')
		 {
			 fputc(first, write);
			 fputc(second, write);
			 state = Cpp_State;
		 }
		 else
		 {
			 fputc(first, write);
			 fputc(second, write);
		 }
		 break;
	 case '"':
	 {
			fputc(first,write);
			state = W_State;
			break;
	 }

	 case  EOF:
	 {
		  fputc(first, write);
		  state = End_State;
		  break;
	 }
	 default:
		 fputc(first, write);
		 break;
	}
}

void DoWState(FILE*read, FILE* write)
{
	int first = fgetc(read);
	if (first == '"')
	{
		fputc(first, write);
		state = Null_State;
	}
	else
		fputc(first, write);
}
void DoCState(FILE* read, FILE* write)
{
	int first = fgetc(read);
	int second = 0;
	switch (first)
	{
	case '*':
		second = fgetc(read);
		if (second == '/') 
		{
			int next = fgetc(read);
			if (next != '\n')
			{
				/*fseek(read,-1,1);*/
				ungetc(next, read);
			}
			fputc('\n', write);
			state = Null_State;
		}
		else
		{
			fputc(first, write);
			ungetc(second, read);
		}
		break;
	case '\n':
		fputc(first, write);
		fputc('/', write);
		fputc('/', write);
		break;
	case 'EOF':
		state = End_State;
		break;
	default:
		fputc(first, write);
		break;
	}
}
void DoCppState(FILE* read, FILE* write)
{
	int first = fgetc(read);
	int second = 0;
	switch (first)
	{	
	case '\n':
		fputc(first, write);
		state = Null_State;
		break;
	case EOF:
		state = End_State;
		break;
	default:
		fputc(first, write);
		break;
	}

}

void ConvertWork(FILE* read, FILE* write)
{
	state = Null_State;
	while (state != End_State)
	{
		switch (state)
		{
		case Null_State:
			DoNullState(read, write);
			break;
		case C_State:
			DoCState(read, write);
			break;
		case Cpp_State:
			DoCppState(read, write);
			break;
		case W_State:
			DoWState(read, write);
			break;
		}
	}
}


void CommentConvert()
{
	FILE* pRead =fopen(INPUTFNAME,"r");
	FILE* pWrite = NULL;
	if (NULL == pRead)
	{
		perror("open input.c");
		exit(EXIT_FAILURE);
	}
	pWrite = fopen(OUTPUTFNAME, "w");
	if (NULL == pWrite)
	{
		fclose(pRead);
		perror("open output.c");
		exit(EXIT_FAILURE);
	}
	ConvertWork(pRead, pWrite);
	fclose(pRead);
	fclose(pWrite);
}
