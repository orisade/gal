
#include "Client.h"
#include "Functions.h"
#include "../Shared/HardCodedData.h"
int main(int argc , const char* argv [] )
{
	CheakArgs(argc, 4); 
	if (CheakIsAnumber(argv[2] )!= SUCCESS)
	{
		printf( " port is not a valid number , exit! ");
	}

	MainClient( argc, argv);
}