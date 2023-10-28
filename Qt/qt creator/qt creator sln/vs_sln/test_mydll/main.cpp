
#include "test1.h"
#include "test2.h"

int main(int argc, char* argv[])
{
	CTest1 t1;
	t1.echo_msg("huang");

	CTest2 t2;
	t2.echo_msg("huang weiwei");
}