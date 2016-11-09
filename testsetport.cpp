/* Error Messages:
 * 2 - too many arguments
 * 7 - not enough arguments
 * 10 - incorrect flag
 * 8 - incorrect port
 * 9 - no environmental variable PORT
**/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

/* Checks to see if there were any errors, if so, it will find a print them out. */
void printFile();

/* test will take the arguments needed for portsetter tests and run the program with given arguments */
string test(string arguments, int expectedReturn);

int main(int argc, char* args[]) {
    ofstream outputFile;
    outputFile.open("textFiles/test_output.txt");
    
    outputFile << "Performing Test Cases, Results below:" << endl;
    
    /* Positive Tests */
    outputFile << "\nTesting Positive Scenarios..." << endl; 
    outputFile << test("",0);
    outputFile << test("-h",0);
    outputFile << test("--help",0);
    outputFile << test("-?",0);
    outputFile << test("-v",0);
    outputFile << test("--version",0);
    outputFile << test("-!",0);
    outputFile << test("--about",0);
    outputFile << test("-p 4040",0);
    outputFile << test("--port 4040",0);
    outputFile << test("-p -e 4040",0);
    outputFile << test("--port -e 4040",0);
    outputFile << test("-p -e 3114",0);                 // added line
    outputFile << test("--port -e 3114",0);             // added line
    outputFile << test("-p -e",0);                      // added line
    outputFile << test("--port -e",0);                  // added line
    outputFile << test("-p --environment",0);           // added line
    outputFile << test("--port --environment",0);       // added line
    outputFile << test("-p --environment 3114",0);      // added line
    outputFile << test("--port --environment 3114",0);  // added line
    outputFile << test("-p --environment 3116",0);      // added line
    outputFile << test("--port --environment 3116",0);  // added line
    
    /* Negative Tests */
    outputFile << "\n\nTesting Negative Scenarios..." << endl; 
    outputFile << test("help",10);
    outputFile << test("-help",10);
    outputFile << test("--h",10);
    outputFile << test("-hs",10);
    outputFile << test("-p --port 9",2);
    outputFile << test("-p 77 33",2);
    outputFile << test("-p -21",8);
    outputFile << test("-p 0",8);
    outputFile << test("--port",7);
    outputFile << test("-p 90642",8);
    outputFile << test("-x 45321",10);
    outputFile << test("-P 714",10);
    outputFile << test("-p -e hello",2);
    outputFile << test("-p -e 80000",8);
    outputFile << test("-v 8080",2);
    outputFile << test("-! 60",2);
    outputFile << test("-e",10);
    outputFile << test("?",10);
    outputFile << test("--about hi",2);
    outputFile << test("--port --environment 80000",8);     // added line
    outputFile << test("--port --environment bad",2);       // added line
    outputFile << test("-p --environment 80000",8);         // added line
    outputFile << test("-p --environment bad",2);           // added line
    outputFile << test("--environment",10);                 // added line
    
    outputFile.close();
    
    printFile();
    
    return 0;
}

string test(string arguments, int expectedReturn) {
    string commandLineArgs = "./portsetter.cpp.o " + arguments;
    const char* comLineArgCharP = commandLineArgs.c_str();
    string errorReason;
    int result = system(comLineArgCharP)/256;
    
    /* Get Reason behind the error to output to customer */
    switch (result) {
        case 2: 
            errorReason = "there are too many arguments";
        case 7:
            errorReason = "there aren't enough arguments";
        case 8:
            errorReason = "of an incorrect port number";
        case 10:
            errorReason = "of an incorrect flag";
    }
    
    if (result == expectedReturn) return "\n\"" + commandLineArgs + "\"...Passed!";
    return "\n\"" + commandLineArgs + "\"...Failed Miserably Because " + errorReason;
}

void printFile() {
    string line;
    string failString = "Failed Miserably";
    int failed = 0;
    /* print results from file */
    ifstream myfile ("textFiles/test_output.txt");
    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            if (strstr(line.c_str(),failString.c_str())) failed++;
            cout << line << '\n';
        }
        myfile.close();
    } else cout << "There was an error opening the test output file" << endl;
    
    if (failed > 0) cout << "\n\nNOTICE: " << failed << " errors occured, look at results to see what failed" << endl;
    else cout << "\n\nAll tests passed! Your program is working how it is supposed to!" << endl;
}
