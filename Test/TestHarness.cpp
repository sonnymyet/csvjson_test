#include <iostream>
#include <fstream>
#include <dirent.h>
#include <vector>

using namespace std;



/*********

Bonnie Ng
301223584

Kylie Loo
301170345

Swann (Sonny) Htet Myet
301103855

*********/



class TestHarness{

private:

	string slash = "/";
	string parentFolder = "./";

	string inputFilePath = "TestData/TestFiles";
	string inputMessagePath = "TestData/ExpectedMessages";

	string outputFilePath = parentFolder + "TestOutput/Files";
	string outputMessagePath = parentFolder + "TestOutput/Messages";


	vector <string> testFiles;
	vector <string> inputMessages;
	vector <string> outputMessages;

public:

	TestHarness(){

		testFiles = vector <string>();
		inputMessages = vector <string>();
		outputMessages = vector <string>();
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

	        	files.push_back(string(directoryFile->d_name));
	    	}
	    }
	    closedir(directoryPath);

	    return 0;
	}


	string readFile(const string &fileName){

		ifstream file (fileName);
		string fileContent;
		string lineBuffer;

		while (getline(file, lineBuffer)){

			fileContent += lineBuffer;
		}
	    
		return fileContent;
	}


	void compareFiles(){

		loadFiles(inputMessagePath, inputMessages);
		loadFiles(outputMessagePath, outputMessages);

		cout << "|:: Expected Message Files ::|" << endl;
		for (auto &file : inputMessages) {

	        cout << file << endl;
	    }

	    cout << endl;

	    cout << "|:: Actual Message Files ::|" << endl;
	    for (auto &file : outputMessages) {

	        cout << file << endl;
	    }

	    cout << endl;

	    for (auto &expectedFile : inputMessages) {

	    	string expectedFilePath = parentFolder + inputMessagePath + slash + expectedFile;
	    	string expected = readFile(expectedFilePath);

	    	for (auto &actualFile : outputMessages) {

	    		string actualFilePath = parentFolder + outputMessagePath + slash + actualFile;
	    		string actual = readFile(actualFilePath);

	    		if (expectedFile == actualFile){
	    			if (expected != actual){

	    				cout << "|:: Expected and Actual not matched for: '" << expectedFile << "' ::|" << endl;
	    			}
	    			else if (expected == actual){
	    				cout << "|:: Expected and Actual matched for: '" << expectedFile << "' ::|" << endl;
	    			}
	    		} 
	    	}
	    }

	}

	void run(){


		loadFiles(inputFilePath, testFiles);
		cout << endl << "|:: List of input files ::|" << endl;

		// Prints out all input test files
		for (auto &file : testFiles) {

	        cout << file << endl;
	    }

	    cout << endl;

	    // Runs csvjson with respect to input test files
		for (auto &testFile : testFiles) {

			string fileName = testFile.substr(0, testFile.length() - 4);
			
			string inputParameter = parentFolder + inputFilePath + slash + testFile;
			string outputParameter = parentFolder + outputFilePath + slash + fileName + ".json";
			
			string outputMessage = parentFolder + outputMessagePath + slash + fileName + ".txt";

			string systemCall = readFile(inputParameter) + " > " + outputParameter;

			cout << "|:: Command called: " << systemCall << " ::|" << endl;

			systemCall.append(" 2>" + outputMessage);
			
			system(systemCall.c_str());

			cout << endl;
	    }

	    compareFiles ();
	}



}; // END class



