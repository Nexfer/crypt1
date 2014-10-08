#include "sso.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define block 30000


	veryLong::veryLong()
	{
		binary=false;
		znak='+';
		lenght=0;
		number=NULL;
	}

	int veryLong::rd(char *inputFile)
	{
		lenght=readd(&number,inputFile,&znak);
		return 0;
	}

	int veryLong::rdb(char *inputFile)
	{
		lenght=readb(&number,inputFile);
		return 0;
	}

	int veryLong::out(char *out)
	{
		FILE *inputFile;
		if (!binary)
		{
			inputFile=fopen(out,"a");
			if (znak=='+')
				fprintf(inputFile,"%s\n",number);
			else
				fprintf(inputFile,"-%s\n",number);
		}
		else
		{
			inputFile=fopen(out,"wb");
			fwrite(number,lenght,1,inputFile);
		}
		fclose(inputFile);
		return 0;
	}

	veryLong veryLong::operator+(veryLong n1)
	{
		veryLong n;
		unsigned char *del;
		if (!binary)
		{
			turn(&number);
			turn(&n1.number);
			del=n.number;
			if ((znak=='+')&&(n1.znak=='+'))
			{
				n.number = summ(&number,&n1.number);
				n.znak='+';
			}
			if ((znak=='-')&&(n1.znak=='-'))
			{
				n.number = summ(&number,&n1.number);
				n.znak='-';
			}
			if ((znak=='+')&&(n1.znak=='-'))
			{
				if (cmp(&number,&n1.number) == 1)
					{
						n.number = sub(&number,&n1.number);
						n.znak='+';
					}
					else
					{
						n.number = sub(&n1.number,&number);
						n.znak='-';
					}
			}
			if ((znak=='-')&&(n1.znak=='+'))
			{
				if (cmp(&number,&n1.number) == 1)
					{
						n.number = sub(&number,&n1.number);
						n.znak='-';
					}
					else
					{
						n.number = sub(&n1.number,&number);
						n.znak='+';
					}
			}
			n.lenght = strlenn(&n.number);
			n.binary=binary;
			turn(&number);
			turn(&n1.number);
			turn(&n.number);
			if (del != NULL)
				free(del);
		}
		else
		{
			n.number = summb(&number,&n1.number,lenght,n1.lenght,&n.lenght);
			n.binary=binary;
		}
		return n;
	}

	veryLong veryLong::operator-(veryLong n1)
	{
		veryLong n;
		if (!binary)
		{
			turn(&number);
			turn(&n1.number);
			if ((znak=='+')&&(n1.znak=='+'))
			{
				if (cmp/*sub*/(&number,&n1.number) == 1)
					{
						n.number = sub(&number,&n1.number);
						n.znak='+';
					}
					else
					{
						n.number = sub(&n1.number,&number);
						n.znak='-';
					}
			}
			if ((znak=='-')&&(n1.znak=='+'))
			{
				if (cmp(&number,&n1.number) == 1)
					{
						n.number = sub(&number,&n1.number);
						n.znak='-';
					}
					else
					{
						n.number = sub(&n1.number,&number);
						n.znak='+';
					}
			}
			if ((znak=='+')&&(n1.znak=='-'))
			{
				n.number = summ(&number,&n1.number);
				n.znak='+';
			}
			if ((znak=='-')&&(n1.znak=='+'))
			{
				n.number = summ(&number,&n1.number);
				n.znak='-';
			}
			n.lenght = strlenn(&n.number);
			n.binary=binary;
			turn(&number);
			turn(&n1.number);
			turn(&n.number);
		}
		else
		{
			n.number = subb(&number,&n1.number,lenght,n1.lenght,&n.lenght);
			n.binary=binary;
		}
		return n;
	}

	veryLong veryLong::operator*(veryLong n1)
	{
		veryLong n;
		if (!binary)
		{
			turn(&number);
			if (&number != &n1.number)
				turn(&n1.number);
			if (((znak=='+')&&(n1.znak=='+'))||((znak=='-')&&(n1.znak=='-')))
			{
				n.number = mul(&number,&n1.number);
				n.znak='+';
			}
			else
			{
				n.number = mul(&number,&n1.number);
				n.znak='-';
			}
			n.lenght = strlenn(&n.number);
			n.binary=binary;
			turn(&number);
			if (&number != &n1.number)
				turn(&n1.number);
			turn(&n.number);
		}
		else
		{
			n.number = mulb(&number,&n1.number,lenght,n1.lenght,&n.lenght);
			n.binary=binary;
		}
		return n;
	}

	veryLong veryLong::operator/(veryLong n1)
	{
		veryLong n;
		unsigned char *ostatok;
		int lenOst;
		if (!binary)
		{
			if (((znak=='+')&&(n1.znak=='+'))||((znak=='-')&&(n1.znak=='-')))
			{
				n.number = divv(&number,&n1.number,&ostatok);
				n.znak='+';
			}
			else
			{
				n.number = divv(&number,&n1.number,&ostatok);
				n.znak='-';
			}
			n.lenght = strlenn(&n.number);
			n.binary=binary;
		}
		else
		{
			turnb(&number,lenght);
			turnb(&n1.number,n1.lenght);
			n.number = divvb(&number,&n1.number,lenght,n1.lenght,&n.lenght,&ostatok,&lenOst);
			n.binary=binary;
			turnb(&number,lenght);
			turnb(&n1.number,n1.lenght);
			turnb(&n.number,n.lenght);
		}
		return n;
	}

	veryLong veryLong::operator%(veryLong n1)
	{
		veryLong n;
		unsigned char *ostatok;
		int lenOst;
		if (!binary)
		{
			divv(&number,&n1.number,&n.number);
			n.lenght = strlenn(&n.number);
			n.binary=binary;
		}
		else
		{
			turnb(&number,lenght);
			turnb(&n1.number,n1.lenght);
			divvb(&number,&n1.number,lenght,n1.lenght,&lenOst,&n.number,&n.lenght);
			n.binary=binary;
			turnb(&number,lenght);
			turnb(&n1.number,n1.lenght);
			turnb(&n.number,n.lenght);
		}
		return n;
	}

	veryLong veryLong::operator^(veryLong n1)
	{
		veryLong n;
		if (!binary)
		{
			turn(&number);
			turn(&n1.number);
			n.znak=znak;
			n.number = stepen(&number,&n1.number,&n.znak);
			n.lenght = strlenn(&n.number);
			n.binary=binary;
			turn(&number);
			turn(&n1.number);
			turn(&n.number);
		}
		else
		{
			n.number = stepenb(&number,&n1.number,lenght,n1.lenght,&n.lenght);
			n.binary=binary;
		}
		return n;
	}

	int veryLong::strlenn(unsigned char **s)
	{
		int i=0;
		while(true)
		{
			if ((*s)[i]=='\0')
				break;
			i++;
		}
		return i;
	}

	veryLong veryLong::operator=(veryLong n1)
	{
		if ((*this).number != NULL)
			free((*this).number);
		(*this).number = (unsigned char*) malloc(block);
		(*this).lenght=n1.lenght;
		for (int i=0;i<n1.lenght;i++)
			(*this).number[i]=n1.number[i];
		(*this).number[(*this).lenght]='\0';
		(*this).binary=n1.binary;
		(*this).znak=n1.znak;
		return *this;		
	}

	bool veryLong::operator==(veryLong n1)
	{
		int i;
		if (!n1.binary)
		{
			i=cmp(&(*this).number,&n1.number);
		}
		else
		{
			i=cmpb(&(*this).number,&n1.number,(*this).lenght,n1.lenght);
		}
		if (i==2)
			return true;
		else
			return false;				
	}

	bool veryLong::operator<(veryLong n1)
	{
		int i;
		if (!n1.binary)
		{
			i=cmp(&(*this).number,&n1.number);
		}
		else
		{
			turnb(&(*this).number,(*this).lenght);
			turnb(&n1.number,n1.lenght);
			i=cmpb(&(*this).number,&n1.number,(*this).lenght,n1.lenght);
			turnb(&(*this).number,(*this).lenght);
			turnb(&n1.number,n1.lenght);
		}
		if (i==0)
			return true;
		else
			return false;
	}

	bool veryLong::operator>(veryLong n1)
	{
		int i;
		if (!n1.binary)
		{
			i=cmp(&(*this).number,&n1.number);
		}
		else
		{
			turnb(&(*this).number,(*this).lenght);
			turnb(&n1.number,n1.lenght);
			i=cmpb(&(*this).number,&n1.number,(*this).lenght,n1.lenght);
			turnb(&(*this).number,(*this).lenght);
			turnb(&n1.number,n1.lenght);
		}
		if (i==1)
			return true;
		else
			return false;
	}

	bool veryLong::operator>=(veryLong n1)
	{
		int i;
		if (!n1.binary)
		{
			i=cmp(&(*this).number,&n1.number);
		}
		else
		{
			turnb(&(*this).number,(*this).lenght);
			turnb(&n1.number,n1.lenght);
			i=cmpb(&(*this).number,&n1.number,(*this).lenght,n1.lenght);
			turnb(&(*this).number,(*this).lenght);
			turnb(&n1.number,n1.lenght);
		}
		if (i>0)
			return true;
		else
			return false;
	}
	bool veryLong::operator<=(veryLong n1)
	{
		int i;
		if (!n1.binary)
		{
			i=cmp(&(*this).number,&n1.number);
		}
		else
		{
			turnb(&(*this).number,(*this).lenght);
			turnb(&n1.number,n1.lenght);
			i=cmpb(&(*this).number,&n1.number,(*this).lenght,n1.lenght);
			turnb(&(*this).number,(*this).lenght);
			turnb(&n1.number,n1.lenght);
		}
		if ((i==0) || (i==2))
			return true;
		else
			return false;
	}

	veryLong veryLong::operator=(const char* str)
	{
		int i;
		(*this).number=(unsigned char*)malloc(block);
		for (i=0;i<strlen(str);i++)
			(*this).number[i]=str[i];
		(*this).number[i]='\0';
		(*this).lenght=strlenn(&(*this).number);
		return *this;
	}

	veryLong::~veryLong()
	{
		free(number);
	}

	veryLong:: veryLong(const veryLong & n)
	{
		int i;
		(*this).binary=n.binary;
		(*this).znak=n.znak;
		(*this).lenght=n.lenght;
		(*this).number=(unsigned char*)malloc(block);
		for (i=0;i<n.lenght;i++)
			(*this).number[i]=n.number[i];
		(*this).number[i]='\0';
	}
