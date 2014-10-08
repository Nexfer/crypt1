#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define block 200

int readd(unsigned char **number,char *file,unsigned char *znak)
{
    unsigned char Char;
    FILE *inputFile=fopen(file,"r");
    int i = 0,it;
    int k = 1;
	(*number) = (unsigned char *)malloc(block);
	fscanf(inputFile,"%c",&Char);
	if (Char == '-')
		(*znak)='-';
	else
	{
		(*znak)='+';
		fseek(inputFile,0,SEEK_SET);
	}
    while (fscanf(inputFile,"%c",&Char) > 0)
    {
          if (i == block*k-5)
          {
            k++;
            (*number) = (unsigned char *)realloc((*number),block*k*sizeof(char));
          }
          if ((Char <48) || (Char > 57))
              break;
          (*number)[i] = Char;
          i++;
    }
    (*number)[i]='\0';
    fclose(inputFile);
    return i;
}

int readb(unsigned char **number,char *file)
{
    FILE *inputFile=fopen(file,"rb");
    int i = 0;
    int k = 1;
	(*number) = (unsigned char *)malloc(block);
    while (fread(&(*number)[i],1,1,inputFile) > 0)
    {
        if (i == block*k-5)
        {
            k++;
            (*number) = (unsigned char *)realloc((*number),block*k*sizeof(char));
        }
        i++;
    }
    fclose(inputFile);
    return i;
}

int cmp(unsigned char **numberOne,unsigned char **numberTwo) //1 - ïåðâîå ÷èñëî áîëüøå, 0 - âòîðîå ÷èñëî áîëüøå èëè ðàâíû
{
	int i;
	if (strlen((*numberOne)) > strlen ((*numberTwo)))
		return 1;
	if (strlen((*numberOne)) < strlen ((*numberTwo)))
		return 0;
	for(i=0;i<strlen((*numberOne));i++)
	{
		if ((*numberOne)[i] > (*numberTwo)[i])
			return 1;
		if ((*numberOne)[i] < (*numberTwo)[i])
			return 0;
	}
	return 2;	
}

int cmpb(unsigned char **numberOne,unsigned char **numberTwo,int lenghtFirst,int lenghtSecond)
{
	int i;
	if (lenghtFirst > lenghtSecond)
		return 1;
	if (lenghtFirst < lenghtSecond)
		return 0;
	for(i=0;i<lenghtFirst;i++)
	{
		if ((*numberOne)[i] > (*numberTwo)[i])
			return 1;
		if ((*numberOne)[i] < (*numberTwo)[i])
			return 0;
	}
	return 2;
}

int turn(unsigned char **number)
{
	char Char;
	int it,len=strlen((*number))-1;
	for (it=0;it<=len/2;it++)
		{
			Char = (*number)[it];
			(*number)[it] = (*number)[len-it];
			(*number)[len-it] = Char;
		}
	return 0;
}

int turnb(unsigned char **number,int lenght)
{
	char Char;
	int it,len=lenght-1;
	for (it=0;it<=len/2;it++)
		{
			Char = (*number)[it];
			(*number)[it] = (*number)[len-it];
			(*number)[len-it] = Char;
		}
	return 0;
}

unsigned char *summ(unsigned char **numberOne,unsigned char **numberTwo)
{
    unsigned char *result;
    int temp,i,carry = 0;
    int k = 1;
    result = (unsigned char*) malloc(block*sizeof(char));
    i=0;
    while(1)
    {
        if ((*numberOne)[i] == '\0')
        {
            temp=1;
            break;
        }
        if ((*numberTwo)[i] == '\0')
        {
            temp=2;
            break;
        }
        temp = (*numberOne)[i] + (*numberTwo)[i]-96;
        result[i] = (temp+carry) % 10+48;
        carry = (temp+carry) / 10;
        i++;
        if (i == block*k-5)
        {
          k++;
          result = (unsigned char *)realloc(result,block*k*sizeof(char));
        }
    }
    if (temp == 1)
        while(1)
        {
            if ((*numberTwo)[i] == '\0')
            {
                break;
            }
            result[i] = ((*numberTwo)[i]+carry-48) % 10 + 48;
            carry = ((*numberTwo)[i]+carry-48) / 10;
            i++;
            if (i == block*k-5)
            {
              k++;
              result = (unsigned char *)realloc(result,block*k*sizeof(char));
            }
        }
    else
        while(1)
        {
            if ((*numberOne)[i] == '\0')
            {
                break;
            }
            result[i] = ((*numberOne)[i]+carry-48) % 10 + 48;
            carry = ((*numberOne)[i]+carry-48) / 10;
            i++;
            if (i == block*k-5)
            {
              k++;
              result = (unsigned char *)realloc(result,block*k*sizeof(char));
            }
        }
    if (carry != 0)
    {
        result[i]=carry+48;
        result[i+1]='\0';
    }
    else
        result[i]='\0';
    return result;
}


unsigned char *summb(unsigned char **numberOne,unsigned char **numberTwo,int lenghtFirst,int lenghtSecond,int *lenghtSumm)
{
    unsigned char *result;
    int temp,i,carry = 0;
    int k = 1;
    result = (unsigned char*) malloc(block*sizeof(char));
    i=0;
    while(1)
    {
        if (i == lenghtFirst)
        {
            temp=1;
            break;
        }
        if (i == lenghtSecond)
        {
            temp=2;
            break;
        }
        temp = (*numberOne)[i] + (*numberTwo)[i];
        result[i] = (temp+carry) % 256;
        carry = (temp+carry)/256;
        i++;
        if (i == block*k-5)
        {
          k++;
          result = (unsigned char *)realloc(result,block*k*sizeof(char));
        }
    }
    if (temp == 1)
        while(1)
        {
            if (i == lenghtSecond)
            {
                break;
            }
            result[i] = ((*numberTwo)[i]+carry) % 256;
            carry = ((*numberTwo)[i]+carry) / 256;
            i++;
            if (i == block*k-5)
            {
              k++;
              result = (unsigned char *)realloc(result,block*k*sizeof(char));
            }
        }
    else
        while(1)
        {
            if (i == lenghtFirst)
            {
                break;
            }
            result[i] = ((*numberOne)[i]+carry) % 256;
            carry = ((*numberOne)[i]+carry) / 256;
            i++;
            if (i == block*k-5)
            {
              k++;
              result = (unsigned char *)realloc(result,block*k*sizeof(char));
            }
        }
    if (carry != 0)
    {
        result[i]=carry;
        *lenghtSumm=i+1;
    }
    else
    {
        *lenghtSumm=i;
    }

    return result;
}

unsigned char *sub(unsigned char **numberOne,unsigned char **numberTwo)
{
    unsigned char *result;
    int i = 0, carry = 0;
    result = (unsigned char*) malloc(strlen(*numberOne)+5);
    while(1)
    {
        if((*numberTwo)[i] == '\0')
        {
            break;
        }
        if (((*numberOne)[i] - carry) >= (*numberTwo)[i])
        {
            result[i] = (*numberOne)[i]-carry-(*numberTwo)[i] +48;
            carry = 0;
        }
        else
        {
            result[i] = (*numberOne)[i]-carry-(*numberTwo)[i] +58;
            carry = 1;
        }
        i++;
    }
    while(1)
    {
        if((*numberOne)[i] == '\0')
        {
            break;
        }
        if (((*numberOne)[i] - carry) >= 48)
        {
            result[i] = (*numberOne)[i]-carry;
            carry = 0;
        }
        else
        {
            result[i] = (*numberOne)[i]-carry+10;
            carry = 1;
        }
        i++;
    }
    for (i=i-1;i>0;i--)
        if (result[i] != '0')
            break;
    result[i+1]='\0';
    return result;
}

unsigned char *subb(unsigned char **numberOne,unsigned char **numberTwo,int lenghtFirst,int lenghtSecond,int *lenghtSumm)
{
    unsigned char *result;
    int i = 0, carry = 0,temp1, temp2;
    result = (unsigned char*) malloc(lenghtFirst+5);
    while(1)
    {
        if(i == lenghtSecond)
        {
            break;
        }
        temp1 = (*numberOne)[i] - carry+500;
        temp2 = (*numberTwo)[i]+500;
        if (temp1 >= temp2)
        {
            result[i] = (*numberOne)[i]-carry-(*numberTwo)[i];
            carry = 0;
        }
        else
        {
            result[i] = (*numberOne)[i]-carry-(*numberTwo)[i];
            carry = 1;
        }
        i++;
    }
    while(1)
    {
        if(i == lenghtFirst)
        {
            break;
        }
        temp1 = (*numberOne)[i] - carry+500;
        temp2 = 500;
        if (temp1 >= temp2)
        {
            result[i] = (*numberOne)[i]-carry;
            carry = 0;
        }
        else
        {
            result[i] = (*numberOne)[i]-carry;
            carry = 1;
        }
        i++;
    }
    for (i=i-1;i>0;i--)
        if (result[i] != 0)
            break;
    *lenghtSumm = i+1;
    return result;
}

unsigned char *mul(unsigned char **numberOne,unsigned char **numberTwo)
{
    unsigned char *result,*help,*del;
    int i,j,carry,temp;
    result = (unsigned char*)malloc(block);
	for (i=0;i<strlen((*numberOne))*strlen((*numberTwo))+5;i++)
		result[i]='0';
	i=0;
    help = (unsigned char*)malloc(strlen((*numberOne))*strlen((*numberTwo))+5);
    while (1)
    {
        if ((*numberTwo)[i] == '\0')
            break;
        for (j=0;j<i;j++)
            help[j]='0';
        j=0;carry=0;
        while(1)
        {
            if ((*numberOne)[j] == '\0')
                break;
            temp = ((*numberTwo)[i]-48)*((*numberOne)[j]-48);
            help[i+j] = (temp+carry)%10+48;
            carry = (temp+carry) / 10;
            j++;
        }
		if (carry != 0)
		{
			help[i+j] = carry+48;
			help[i+j+1]='\0';
		}
		else
			help[i+j] = '\0';
		if (i != 0)
		{
			del=result;
			result = summ(&result,&help);
			free(del);
		}
		else
			strncpy(result,help,strlen(help)+1);
        i++;
    }
	free(help);
    return result;
}

unsigned char *mulb(unsigned char **numberOne,unsigned char **numberTwo,int lenghtFirst,int lenghtSecond,int *lenghtSumm)
{
    unsigned char *result,*help;
    int i,j,carry,temp,resultLenght,it;
    result = (unsigned char*)malloc(lenghtFirst*lenghtSecond+5);
    for (i=0;i<lenghtFirst*lenghtSecond+5;i++)
        result[i]=0;
    i=0;
    help = (unsigned char*)malloc(lenghtFirst*lenghtSecond+5);
    while (1)
    {
        if (i == lenghtSecond)
            break;
        for (j=0;j<i;j++)
            help[j]=0;
        j=0;carry=0;
        while(1)
        {
            if (j == lenghtFirst)
                break;
            temp = (*numberTwo)[i]*(*numberOne)[j];
            help[i+j] = (temp+carry)%256;
            carry = (temp+carry)/256;
            j++;
        }
        if (carry != 0)
		{
            help[i+j] = carry;
			if (i != 0)
				result = summb(&result,&help,resultLenght,i+j+1,&resultLenght);
			else
			{
				for (it=0;it<i+j+1;it++)
					result[it]=help[it];;
				resultLenght=i+j+1;
			}
		}
		else
		{
			if (i != 0)
				result = summb(&result,&help,resultLenght,i+j,&resultLenght);
			else
			{
				for (it=0;it<i+j;it++)
					result[it]=help[it];;
				resultLenght=i+j;
			}
		}
        i++;
    }
    *lenghtSumm = resultLenght;
    return result;
}

unsigned char *divv(unsigned char **numberOne,unsigned char **numberTwo,unsigned char **ostatok)
{
	int i,j,k,q;
	unsigned char *delimoe,*delitel,*answer;
	delimoe = (unsigned char*)malloc(2*strlen((*numberOne)));
	delitel = (unsigned char*)malloc(2*strlen((*numberTwo)));
	answer = (unsigned char*)malloc(2*strlen((*numberOne)));
	q=0;
	i=0;j=0;
	while(1)
	{
		if ((*numberOne)[i]=='\0')
			break;
		if ((j != 0) || ((*numberOne)[i] != '0'))
		{
			delimoe[j]=(*numberOne)[i];
			delimoe[j+1]='\0';
		}
		else
			j--;
		if (cmp(&delimoe,&(*numberTwo)) > 0)
		{
			for (k=0;k<=strlen((*numberTwo));k++)
				delitel[k]=(*numberTwo)[k];
			k=1;
			while(1)
			{
				if (cmp(&delitel,&delimoe) > 0)
				{
					if (strcmp(delitel,delimoe) != 0)
					{
					if (strlen(delitel) != 1)
						turn(&delitel);
					if ((strlen(*numberTwo)) != 1)
						turn(&(*numberTwo));
					delitel = sub(&delitel,&(*numberTwo));
					if (strlen(delitel) != 1)
						turn(&delitel);
					if ((strlen(*numberTwo)) != 1)
						turn(&(*numberTwo));
					k--;
					}
					answer[q]=k+48;
					q++;
					break;
				}
				else
				{
					if (strlen(delitel) != 1)
						turn(&delitel);
					if ((strlen(*numberTwo)) != 1)
						turn(&(*numberTwo));
					delitel=summ(&delitel,&(*numberTwo));
					if (strlen(delitel) != 1)
						turn(&delitel);
					if ((strlen(*numberTwo)) != 1)
						turn(&(*numberTwo));
					k++;
				}
			}
			if (strlen(delimoe) != 1)
				turn(&delimoe);
			if (strlen(delitel) != 1)
				turn(&delitel);
			delimoe = sub(&delimoe,&delitel);
			if (strlen(delimoe) != 1)
				turn(&delimoe);
			if (strlen(delitel) != 1)
				turn(&delitel);
			j=strlen(delimoe);
			if ((strlen(delimoe) == 1) && (delimoe[0]=='0'))
				j=0;
			i++;
		}
		else
		{
			if (q != 0)
			{
				answer[q]='0';
				q++;
			}
			j++;
			i++;
		}

	}
	if (q != 0)
		answer[q]='\0';
	else
	{
		answer[0]='0';
		answer[1]='\0';
	}
	if (j != 0)
		(*ostatok)=delimoe;
	else
	{
		(*ostatok)=delimoe;
		(*ostatok)[1]='\0';
	}

	return answer;
}

unsigned char *divvb(unsigned char **numberOne,unsigned char **numberTwo,int lenghtFirst,int lenghtSecond,int *lenghtSumm,unsigned char **ostatok,int *lenghtOst)
{
	int i,j,k,q,lenghtDelitel,c;
	unsigned char *delimoe,*delitel,*answer;
	delimoe = (unsigned char*)malloc(2*lenghtFirst);
	delitel = (unsigned char*)malloc(2*lenghtSecond);
	answer = (unsigned char*)malloc(2*lenghtFirst);
	q=0;
	i=0;j=0;
	while(1)
	{
		if (i == lenghtFirst)
			break;
		if ((j != 0) || ((*numberOne)[i] != 0))
			delimoe[j]=(*numberOne)[i];
		else
			j--;
		j++;
		if (cmpb(&delimoe,&(*numberTwo),j,lenghtSecond) > 0)
		{
			for (k=0;k<lenghtSecond;k++)
				delitel[k]=(*numberTwo)[k];
			lenghtDelitel=k;
			k=1;
			while(1)
			{
				c=cmpb(&delitel,&delimoe,lenghtDelitel,j);
				if (c >0)
				{
					if (c == 1)
					{
						if (lenghtDelitel != 1)
							turnb(&delitel,lenghtDelitel);
						if (lenghtSecond != 1)
							turnb(&(*numberTwo),lenghtSecond);
						delitel = subb(&delitel,&(*numberTwo),lenghtDelitel,lenghtSecond,&lenghtDelitel);
						if (lenghtDelitel != 1)
							turnb(&delitel,lenghtDelitel);
						if (lenghtSecond != 1)
							turnb(&(*numberTwo),lenghtSecond);
						k--;
					}
					answer[q]=k;
					q++;
					break;
				}
				else
				{
					if (lenghtDelitel != 1)
						turnb(&delitel,lenghtDelitel);
					if (lenghtSecond != 1)
						turnb(&(*numberTwo),lenghtSecond);
					delitel=summb(&delitel,&(*numberTwo),lenghtDelitel,lenghtSecond,&lenghtDelitel);
					if (lenghtDelitel != 1)
						turnb(&delitel,lenghtDelitel);
					if (lenghtSecond != 1)
						turnb(&(*numberTwo),lenghtSecond);
					k++;
				}
			}
			if (j != 1)
				turnb(&delimoe,j);
			if (lenghtDelitel != 1)
				turnb(&delitel,lenghtDelitel);
			delimoe = subb(&delimoe,&delitel,j,lenghtDelitel,&j);
			if (j != 1)
				turnb(&delimoe,j);
			if (lenghtDelitel != 1)
				turnb(&delitel,lenghtDelitel);;
			if ((j == 1) && (delimoe[0]==0))
				j=0;
			i++;
		}
		else
		{
			if (q != 0)
			{
				answer[q]=0;
				q++;
			}
			i++;
		}

	}
	if (q == 0)
	{
		answer[0]='0';
		q++;
	}
	*lenghtSumm=q;
	if (j != 0)
	{
		(*ostatok)=delimoe;
		*lenghtOst=j;
	}
	else
	{
		(*ostatok)=delimoe;
		*lenghtOst=1;
	}
	return answer;
}

unsigned char *stepen(unsigned char **numberOne,unsigned char **numberTwo,unsigned char *znak)
{
	int i,flag;
	unsigned  char *firstNumber,*st,*incr;
	firstNumber = (unsigned char*)malloc(strlen((*numberOne)+2));
	st = (unsigned char*)malloc(block);
	incr = (unsigned char*)malloc(4);
	st[0]='0';
	st[1]='\0';
	incr[0]='1';
	incr[1]='\0';
	if ((*znak)=='+')
		flag=0;
	else
		flag=1;
	strcpy(firstNumber,(*numberOne));
	while(1)
	{
		st = summ(&st,&incr);
		if (strcmp(st,(*numberTwo)) == 0)
			break;
		if (flag==1)
			if ((*znak)=='+')
				(*znak)='-';
			else
				(*znak)='+';
		firstNumber = mul(&(*numberOne),&firstNumber);
	}
	return firstNumber;
}

unsigned char *stepenb(unsigned char **numberOne,unsigned char **numberTwo,int lenghtFirst,int lenghtSecond,int *lenghtSumm)
{
	int i,lenght,lenghtSt;
	unsigned  char *firstNumber,*st,*incr;
	firstNumber = (unsigned char*)malloc(lenghtFirst+2);
	st = (unsigned char*)malloc(block);
	incr = (unsigned char*)malloc(4);
	st[0]=1;
	incr[0]=1;
	lenghtSt=1;
	for (i=0;i<lenghtFirst;i++)
		firstNumber[i]=(*numberOne)[i];
	lenght=lenghtFirst;
	while(1)
	{
		if (cmpb(&st,&(*numberTwo),lenghtSt,lenghtSecond) == 2)
			break;
		firstNumber = mulb(&firstNumber,&(*numberOne),lenght,lenghtFirst,&lenght);
		st=summb(&st,&incr,lenghtSt,1,&lenghtSt);
	}
	*lenghtSumm=lenght;
	return firstNumber;
}
