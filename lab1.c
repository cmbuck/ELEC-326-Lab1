#define uint unsigned int
#define ulong unsigned long

#define uHelper(a,b,c,d)	luHelper(a,b,c & 0x00000000FFFFFFFF, d)
#define dHelper(a,b,c,d)	ldHelper(a,b,c & 0x00000000FFFFFFFF, d)
#define xHelper(a,b,c,d)	lxHelper(a,b,c & 0x00000000FFFFFFFF, d)

void ldHelper(char* buf, int* index, long int number, int base_call)
{
    if (number / 10)
		ldHelper(buf, index, number / 10, 0);
    //handle negative numbers
    if (number < 0)
    {
		number *= -1;
		if (*index == 0 && number < 10)
			buf[(*index)++] = '-';
    }
    buf[(*index)++] = (char)((int)'0')+abs((int)(number % 10));
    if (base_call)
		buf[(*index)++] = '\0';

}

/*
void dHelper(char* buf, int* index, int number, int base_call)
{
    if (number / 10)
		dHelper(buf, index, number / 10, 0);
    //handle negative numbers
    if (number < 0)
    {
		number *= -1;
		if (*index == 0 && number < 10)
			buf[(*index)++] = '-';
    }
    buf[(*index)++] = (char)((int)'0')+abs((int)(number % 10));
    if (base_call)
		buf[(*index)++] = '\0';

}
*/

/*
void uHelper(char* buf, int* index, unsigned long number, int base_call)
{
    if (number / 10)
		uHelper(buf, index, number / 10, 0);
    
    buf[(*index)++] = (char)((int)'0')+(number % 10);
    if (base_call)
		buf[(*index)++] = '\0';
	

}
*/

void luHelper(char* buf, int* index, unsigned long number, int base_call)
{
    if (number / 10)
		luHelper(buf, index, number / 10, 0);
    
    buf[(*index)++] = (char)((int)'0')+(number % 10);
    if (base_call)
		buf[(*index)++] = '\0';

}

void oHelper(char* buf, int* index, unsigned int number, int base_call)
{
	if (number >> 3)
		oHelper(buf, index, number >> 3, 0);
	
	uint c = number % 8;
	buf[(*index)++] = (char)(((int)'0')+c);
	if (base_call)
		buf[(*index)++] = '\0';
}

void loHelper(char* buf, int* index, unsigned long number, int base_call)
{
	if (number >> 3)
		loHelper(buf, index, number >> 3, 0);
	
	uint c = number % 8;
	buf[(*index)++] = (char)(((int)'0')+c);
	if (base_call)
		buf[(*index)++] = '\0';
}
/*
void xHelper(char* buf, int* index, unsigned int number, int base_call)
{
	if (number >> 4)
		xHelper(buf, index, number >> 4, 0);
	
	if (*index == 0)
	{
		buf[(*index)++] = '0';
		buf[(*index)++] = 'x';
	}
	uint c = number % 16;
	if (c > 9)	c += 7;
	buf[(*index)++] = (char)(((int)'0')+c);
	if (base_call)
		buf[(*index)++] = '\0';
}
*/

void lxHelper(char* buf, int* index, unsigned long number, int base_call)
{
	if (number >> 4)
		lxHelper(buf, index, number >> 4, 0);
	
	/*
	if (*index == 0)
	{
		buf[(*index)++] = '0';
		buf[(*index)++] = 'x';
	}
	*/
	
	uint c = number % 16;
	if (c > 9)	c += 39;
	buf[(*index)++] = (char)(((int)'0')+c);
	if (base_call)
		buf[(*index)++] = '\0';
}

void fHelper(char* buf, int* index, int number, int base_call)
{
	if (base_call)
		if ((number >> 16) < 0)  //if negative
		{
			buf[(*index)++] = '-';
			dHelper(buf, index, (number >> 16) + 1, 1);
		}
		else	//if positive
			dHelper(buf, index, number >> 16, 1);
	number &= 0x0000FFFF;
	buf[(*index)-1] = '.';
	while (number)
	{
		number *= 10;
		buf[(*index)++] = (char)( ((number & 0xFFFF0000) >> 16) + '0');
		number &= 0x0000FFFF;
	}
	buf[(*index)++] = '\0';
}

void printv(char *argv[], void (*print_char)(int))
{
    //comment
    char* fmt = argv[0];
    char buf[32];
    int element = 1;
    char* c = fmt;
	char* s_ptr; //for handling %s
    unsigned long tmp;
    unsigned int bogus = 22;
    unsigned int* index = &bogus;
    *index = 0;

    for (c = fmt; *c != 0 ; c++)
    {
		if (*c != '%')
			(*print_char)(*c);
		else switch (*++c)
		{
			case 'c':
				//tmp = (long)argv[element] + ((long)argv[++element] << 32);
				tmp = (ulong)argv[element++];
				(*print_char)(tmp);
				break;
				
			case 's':
				s_ptr = argv[element++];
				for (s_ptr; *s_ptr; s_ptr++)
					(*print_char)(*s_ptr);
				break;

			case 'd':
				//sprintf(buf, "%d", argv[element]);
				tmp = (ulong)argv[element++];
				*index = 0;
				dHelper(buf, index, tmp, 1);
				for (tmp = 0; buf[tmp]; tmp++)
					(*print_char)(buf[tmp]);
				break;
				
			case 'u':
				tmp = (ulong)argv[element++];
				*index = 0;
				uHelper(buf, index, tmp, 1);
				for (tmp = 0; buf[tmp]; tmp++)
					(*print_char)(buf[tmp]);
				break;
				
			case 'x':
				tmp = (ulong)argv[element++];
				*index = 0;
				xHelper(buf, index, tmp, 1);
				for (tmp = 0; buf[tmp]; tmp++)
					(*print_char)(buf[tmp]);
				break;
				
			case 'o':
				tmp = (ulong)argv[element++];
				*index = 0;
				oHelper(buf, index, tmp, 1);
				for (tmp = 0; buf[tmp]; tmp++)
					(*print_char)(buf[tmp]);
				break;
				
			case 'f':
				tmp = (ulong)argv[element++];
				*index = 0;
				fHelper(buf, index, tmp, 1);
				for (tmp = 0; buf[tmp]; tmp++)
					(*print_char)(buf[tmp]);
				break;

			case 'l':
				//ld, lu, lo, lx
				switch (*++c)
				{
					case 'd':
						tmp = (ulong)argv[element++];
						*index = 0;
						ldHelper(buf, index, tmp, 1);
						for (tmp = 0; buf[tmp]; tmp++)
							(*print_char)(buf[tmp]);
						break;
						
					case 'u':
						tmp = (ulong)argv[element++];
						*index = 0;
						luHelper(buf, index, tmp, 1);
						for (tmp = 0; buf[tmp]; tmp++)
							(*print_char)(buf[tmp]);
						break;
						
					case 'o':
						tmp = (ulong)argv[element++];
						*index = 0;
						loHelper(buf, index, tmp, 1);
						for (tmp = 0; buf[tmp]; tmp++)
							(*print_char)(buf[tmp]);
						break;
						
					case 'x':
						tmp = (ulong)argv[element++];
						*index = 0;
						lxHelper(buf, index, tmp, 1);
						for (tmp = 0; buf[tmp]; tmp++)
							(*print_char)(buf[tmp]);
						break;
					
				}
				
	}
    }
}

/*
int main()
{
  
}
*/

