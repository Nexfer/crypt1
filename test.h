#include <stdio.h>
#define block 30000
int readd(unsigned char **number,char *file,unsigned char *znak);
int readb(unsigned char **number,char *file);
int cmpsub(unsigned char **numberOne,unsigned char **numberTwo);
int cmp(unsigned char **numberOne,unsigned char **numberTwo);
int cmpb(unsigned char **numberOne,unsigned char **numberTwo,int lenghtFirst,int lenghtSecond);
int turn(unsigned char **number);
int turnb(unsigned char **number,int lenght);
unsigned char *summ(unsigned char **numberOne,unsigned char **numberTwo);
unsigned char *summb(unsigned char **numberOne,unsigned char **numberTwo,int lenghtFirst,int lenghtSecond,int *lenghtSumm);
unsigned char *sub(unsigned char **numberOne,unsigned char** numberTwo);
unsigned char *subb(unsigned char **numberOne,unsigned char **numberTwo,int lenghtFirst,int lenghtSecond,int *lenghtSumm);
unsigned char *mul(unsigned char **numberOne,unsigned char **numberTwo);
unsigned char *mulb(unsigned char **numberOne,unsigned char **numberTwo,int lenghtFirst,int lenghtSecond,int *lenghtSumm);
unsigned char *divv(unsigned char **numberOne,unsigned char **numberTwo,unsigned char **ostatok);
unsigned char *divvb(unsigned char **numberOne,unsigned char **numberTwo,int lenghtFirst,int lenghtSecond,int *lenghtSumm,unsigned char **ostatok,int *lenghtOst);
unsigned char *stepen(unsigned char **numberOne,unsigned char **numberTwo,unsigned char *znak);
unsigned char *stepenb(unsigned char **numberOne,unsigned char **numberTwo,int lenghtFirst,int lenghtSecond,int *lenghtSumm);
