#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test_cpp.h"

veryLong gcd (veryLong Enc1, veryLong Enc2, veryLong & x, veryLong & y) 
{
	veryLong zero, one;
	zero.rd("zero.txt");
	one.rd("one.txt");
	if (Enc1 == zero)
	{
		x = zero; 
		y = Enc2/Enc2;
		return Enc2;
	}
	veryLong xx, yy;
	veryLong res;
	res = gcd (Enc2%Enc1, Enc1, xx, yy);
	one=Enc2/Enc1;
	zero=one*xx;
	x=yy-zero;
	y = xx;
	return res;
}

veryLong doiT(veryLong yy, veryLong pp)
{
	veryLong g, x, y, one, zero;
	zero.rd("zero.txt");
	one.rd("one.txt");
	g=gcd(yy, pp, x, y);
	if (g==one)
	{
		x=x%pp;
		x=x+pp;
		x=x%pp;
		return x;
	}
	else
		return zero;
}

int main(int argc, char *argv[])
{	
	char *inputP,*inputX, *outMes, *inputEnc1, *inputEnc2;
	inputP=argv[1];
	inputX=argv[2];
	inputEnc1=argv[3];
	inputEnc2=argv[4];
	outMes=argv[5];
	veryLong p, Enc1, Enc2, x, y, msg;
	p.rd(inputP);
	x.rd(inputX);
	Enc1.rd(inputEnc1);
	Enc2.rd(inputEnc2);
	y=(Enc1^x)%p;
	Enc1=doiT(y, p);
	x=Enc2*Enc1;
	msg=x%p;
	msg.out(outMes);
	return 0;
}
