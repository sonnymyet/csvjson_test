#include <iostream>
#include <fstream>

using namespace std;


/*********

Bonnie Ng


Kylie Loo


Swann (Sonny) Htet Myet
301103855

*********/

int main(){
	
	cout << "Hello World" << endl;

	string filePath = "./TestData/TestFiles/input1.csv";
	string outputPath = "./TestData/ExpectedOutput/output1.json";

	cout << filePath << endl;
	
	system("csvjson ./TestData/TestFiles/input1.csv > ./TestData/ExpectedOutput/output1.json");

}