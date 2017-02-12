#include <iostream>
#include <fstream>
#include <dirent.h>
#include <vector>

using namespace std;

/*********

Bonnie Ng


Kylie Loo


Swann (Sonny) Htet Myet
301103855

*********/

class TestHarness{

private:
	string inputPath = "TestData/TestFiles";
	string outputPath = " ./TestData/ExpectedOutput";
	string slash = "/";
	string parentFolder = "./";

	vector<string> testFiles;

public:

	TestHarness(){
		testFiles = vector<string>();

	}


	bool has_suffix(const string& s, const string& suffix)
	{
	    return (s.size() >= suffix.size()) && equal(suffix.rbegin(), suffix.rend(), s.rbegin());    
	}


	int loadFiles(string dir, vector<string> &files){

	    DIR *directoryPath;
	    struct dirent *directoryFile;

	    if((directoryPath  = opendir(dir.c_str())) == NULL) {

	        cout << "Error opening folder: " << dir << endl;
	        return errno;
	    }

	    while ((directoryFile = readdir(directoryPath)) != NULL) {

	    	if (has_suffix(directoryFile->d_name, ".csv")){

	        	files.push_back(string(directoryFile->d_name));
	    	}
	    }
	    closedir(directoryPath);

	    return 0;
	}



	void run(){


		loadFiles(inputPath, testFiles);

		for (auto &file : testFiles) {

	        cout << file << endl;
	    }


		for (auto &file : testFiles) {

			string inputParameter = parentFolder + inputPath + slash + file;
			string outfile = file.substr(0, file.length() - 4);
			string outputParameter = outputPath + slash + outfile + ".json";
			
			string systemCall = "csvjson " + inputParameter + " >" + outputParameter;
			cout << systemCall << endl;
			system(systemCall.c_str());
	    }


	}


};







int main(){
	
	cout << "Hello World" << endl;


	TestHarness t;
	t.run();






}


