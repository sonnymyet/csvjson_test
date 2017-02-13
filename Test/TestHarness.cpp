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
	string outputPath = "TestOutput/Files";
	string slash = "/";
	string parentFolder = "./";

	vector<string> testFiles;

public:

	TestHarness(){

		testFiles = vector<string>();
	}


	// Checks if files have specific extension
	// Code adapted from --- http://stackoverflow.com/questions/19189014/how-do-i-find-files-with-a-specific-extension-in-a-directory-that-is-provided-by
	bool hasExtenstion(const string& str, const string& ext){

	    return (str.size() >= ext.size()) && equal(ext.rbegin(), ext.rend(), str.rbegin());    
	}


	// Reads files from directory and stores 'csv' files in vector 
	// Code adapted from jtshaw --- http://www.linuxquestions.org/questions/programming-9/c-list-files-in-directory-379323/	
	int loadFiles(string dir, vector<string> &files){

	    DIR *directoryPath;
	    struct dirent *directoryFile;

	    if((directoryPath  = opendir(dir.c_str())) == NULL) {

	        cout << "Error opening folder: " << dir << endl;
	        return errno;
	    }

	    while ((directoryFile = readdir(directoryPath)) != NULL) {

	    	// Filters out files that are not test files
	    	if (hasExtenstion(directoryFile->d_name, "CMakeLists.txt")){
	        	//Do nothing
	    	}
	    	else if (hasExtenstion(directoryFile->d_name, ".txt")){
	        	//Do nothing
	        	files.push_back(string(directoryFile->d_name));
	    	}
	    	/*
	    	else if (hasExtenstion(directoryFile->d_name, "..")){
	        	//Do nothing
	    	}
	    	else if (hasExtenstion(directoryFile->d_name, ".cmake")){
	    		//Do nothing
	    	}
	    	else if (hasExtenstion(directoryFile->d_name, "Makefile")){
	    		//Do nothing
	    	}
	    	else if (hasExtenstion(directoryFile->d_name, "CMakeFiles")){
	    		//Do nothing
	    	}
	    	else if (hasExtenstion(directoryFile->d_name, "DummyData")){
	    		//Do nothing
	    	}
	    	else{
	        	files.push_back(string(directoryFile->d_name));

	    	}
	    	*/
	    }
	    closedir(directoryPath);

	    return 0;
	}


	string readCommand(const string &fileName){

		ifstream file (fileName);
		string fileContent;
		string line;

		while (getline(file, line)){

			fileContent = line;
		}
	    
		return fileContent;
	}



	void run(){


		loadFiles(inputPath, testFiles);
		cout << endl << "List of input files: " << endl;

		// Prints out all input test files
		for (auto &file : testFiles) {

	        cout << file << endl;
	    }

	    cout << endl;

	    // Runs csvjson with respect to input test files
		for (auto &testFile : testFiles) {

			string inputParameter = parentFolder + inputPath + slash + testFile;
			string fileName = testFile.substr(0, testFile.length() - 4);
			string outputParameter = parentFolder + outputPath + slash + fileName + ".json";

			string systemCall = readCommand(inputParameter) + " > " + outputParameter;

			cout << systemCall << endl;
			
			try {
				
				system(systemCall.c_str());
				cout << endl;
			}
			catch (int e){

			}
			if (errno != 0){
				
			}
	    }

	}
};



