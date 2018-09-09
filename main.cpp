#include "Preprocess.hpp"
int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Usage: <Translation Type> <Input File> <Output File>" << std::endl;
	}
	else
	{
		PreProcess pre(argv[2]);
		pre.Translate(argv[1]);
		pre.WriteOutput(argv[3]);
	}
	return 0;
}