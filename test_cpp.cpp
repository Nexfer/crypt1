#include <stdio.h>
#include <string.h>
#include "test_cpp.h"

int main(int argc, char *argv[])
{
	char *inputFirst,*inputSecond,*output,*inputThird;
	veryLong n1,n2,n3,n4;
	int module;
	char znak;
        if (argc < 5 )
        {
            printf("\nEnter correct parameters\n");
            return 0;
        }
	if (argc == 7)
	{
		n1.binary=true;
		n2.binary=true;
		n4.binary=true;
		module = 1;
		inputThird=argv[6];
		n4.rdb(inputThird);		
	}
	if (argc == 6)
	{
		if (strcmp(argv[5],"-b") == 0)
		{
			n1.binary=true;
			n2.binary=true;
			module=0;
		}
		else
		{
			n1.binary=false;
			n2.binary=false;
			n4.binary=false;
			module=1;
			inputThird=argv[5];
			n4.rd(inputThird);
		}
	}
	if ( argc < 6)
	{
		n1.binary=false;
		n2.binary=false;
		module=0;
	}

	if (!n1.binary)
	{
		inputFirst = argv[1];
        inputSecond = argv[3];
        output = argv[4];
		n1.rd(inputFirst);
		n2.rd(inputSecond);
    }
    else
    {
        inputFirst = argv[1];
        inputSecond = argv[3];
        output =argv[4];
		n1.rdb(inputFirst);
		n2.rdb(inputSecond);
    }
	
	znak=argv[2][0];

	switch(znak)
	{
		case '+' :			
			n3=(n1+n2);
			if (module)
				n3=n3%n4;
			break;
		case '-' :
			n3=n1-n2;
			if (module)
				n3=n3%n4;
			break;
		case '*' :
			n3=n1*n2;
			if (module)
				n3=n3%n4;
			break;
		case '/' :
			n3=n1/n2;
			if (module)
				n3=n3%n4;
			break;
		case '%' :
			n3=n1%n2;
			if (module)
				n3=n3%n4;
			break;
		case '^' :
			n3=n1^n2;
			if (module)
				n3=n3%n4;
			break;

		default:
			break;
	}
	
	n3.out(output);

}
