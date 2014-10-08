extern "C"
{
#include "test.h"
}

class veryLong
{
public:
	unsigned char *number;
	int lenght;
	bool binary;
	unsigned char znak;
	veryLong();
	veryLong(const veryLong &);
	~veryLong();
	int rd(char*);
	int rdb(char*);
	int out(char*);
	veryLong operator+(veryLong );
	veryLong operator-(veryLong );
    	veryLong operator*(veryLong );
	veryLong operator/(veryLong );
	veryLong operator%(veryLong );
	veryLong operator^(veryLong );
	veryLong operator=(veryLong );
	veryLong operator=(const char*);
	bool operator==(veryLong );
	bool operator<(veryLong );
	bool operator>(veryLong );
	bool operator<=(veryLong );
	bool operator>=(veryLong );
private:
	int strlenn(unsigned char**);
};
