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

	string inputFilePath = "TestData/TestFiles";
	string outputFilePath = "TestOutput/Files";
	string outputMessagePath = "TestOutput/Messages";
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

	        	files.push_back(string(directoryFile->d_name));
	    	}
	    }
	    closedir(directoryPath);

	    return 0;
	}


	string readCommand(const string &fileName){

		ifstream file (fileName);
		string fileContent;
		string lineBuffer;

		while (getline(file, lineBuffer)){

			fileContent += lineBuffer;
		}
	    
		return fileContent;
	}

	/*
	void GetStdoutFromCommand(string cmd, const string &fileName) {

		string data;
		FILE * stream;

		const int max_buffer = 256;
		char buffer[max_buffer];
		string outPutPath = parentFolder + outputMessagePath + slash + fileName + ".txt";
		cmd.append(" 2>" + outPutPath);

		stream = popen(cmd.c_str(), "r");
		if (stream) {
			while (!feof(stream)){

				if (fgets(buffer, max_buffer, stream) != NULL){
					data.append(buffer);
					cout << "Data: " << data << endl;
				} 
			pclose(stream);
			}
		}

		ofstream outPutFile;
		outPutFile.open (outPutPath);
		outPutFile << data;
		outPutFile.close();
		//return data;
	}
	*/

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

			string systemCall = readCommand(inputParameter) + " > " + outputParameter;

			cout << "|:: Command called: " << systemCall << " ::|" << endl;

			systemCall.append(" 2>" + outputMessage);
			
			try {
				system(systemCall.c_str());
			}
			catch (int e){

			}
			if (errno != 0){

			}
	    }

	}
};



