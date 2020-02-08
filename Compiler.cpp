#include "Parser.h"
#include <iostream>

int main(int argc, char** argv)
{
	/*
	if(argc != 3) {
		cout << "Usage: " << argv[0] << " " << "nptfile inputfile" ;
		return 1;
	}
	
	Parser myParser(argv[1], argv[2]);
	*/
	cout << "here";
	Parser myParser("test.npt", "input.txt");

	myParser.Parse();
	return 0;
}
