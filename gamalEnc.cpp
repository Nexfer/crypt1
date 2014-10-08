#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test_cpp.h"

int main(int argc, char *argv[])
{	
	char *inputP,*inputG,*inputMes, *inputK, *inputX;
	inputP=argv[1];
	inputG=argv[2];
	inputX=argv[3];
	inputK=argv[4];
	inputMes=argv[5];
	veryLong p, g, k, x, msg, y;
	p.rd(inputP);
	g.rd(inputG);
	k.rd(inputK);
	x.rd(inputX);
	msg.rd(inputMes);
	y=(g^x)%p;
	veryLong enc1, enc2;
	enc1=(g^k)%p;
	enc1.out("enc1.txt");
	veryLong tmp;
	tmp=(y^k)%p;
	y=tmp*msg;
	enc2=y%p;
	enc2.out("enc2.txt");
	return 0;
}
