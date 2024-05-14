//Writing to a text file
#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ofstream myfile ("LMSBooks.csv");
	if (myfile.is_open())
	{
		myfile << "Mardiyyah Apampa,m.apampa\n";
		myfile << "Meymunah Olajobi,m.olajobi\n";
	}
	else cout << "Unable to open file";
	return 0;
}