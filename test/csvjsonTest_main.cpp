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


// Code adapted from below link
// http://stackoverflow.com/questions/19189014/how-do-i-find-files-with-a-specific-extension-in-a-directory-that-is-provided-by
	bool hasExtenstion(const string& str, const string& ext){

	    return (str.size() >= ext.size()) && equal(ext.rbegin(), ext.rend(), str.rbegin());    
	}


// Code adapted from jtshaw
// http://www.linuxquestions.org/questions/programming-9/c-list-files-in-directory-379323/	
	int loadFiles(string dir, vector<string> &files){

	    DIR *directoryPath;
	    struct dirent *directoryFile;

	    if((directoryPath  = opendir(dir.c_str())) == NULL) {

	        cout << "Error opening folder: " << dir << endl;
	        return errno;
	    }

	    while ((directoryFile = readdir(directoryPath)) != NULL) {

	    	if (hasExtenstion(directoryFile->d_name, ".csv")){

	        	files.push_back(string(directoryFile->d_name));
	    	}
	    }
	    closedir(directoryPath);

	    return 0;
	}


	void inputOption(){

		
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


