/* Error Messages:
 * 2 - too many arguments
 * 7 - not enough arguments
 * 8 - incorrect port
 * 9 - no environmental variable PORT
 * 10 - incorrect flag
**/

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;

const string VERSION_NUM = "1.0.3";
const int MAXPORT = 65000;
const int MINPORT = 0;

/* Purpose of Usage: print usage/help message */
void usage(string lang);
void about(string lang);

/* Purpose of isInt: check all of the port number to make sure it is soely an integer */
bool isInt(string str);

/* get the errors from the specific language specified */
void languageMessages(vector<string>& languageVector, string lang);

/* gets the environmental variable for language if it is set */
string language();

/* print all from specified file */
void printFromFile(string fileName);

int main(int argc, char* args[]) {
    /* Enum for errors, to later use for getting those codes out of vector */
    enum {TWO,SEVEN,EIGHT,NINE,TEN,LISTENING,VERSION};
    int port;
    string flag;
    char* portEnv;
    string lang = language();
    if (lang != "es" && lang != "en") {
        cout << "\nLanguage \"" << lang << "\" is not available, defaulting to English";
        lang = "en";
    }
    /* get the messages in specified language */
    vector<string> languageVector;
    languageMessages(languageVector, lang);
    
    string portOrEnv;
    if (argc >= 3) portOrEnv = args[2];
    
    /* checks initial errors caused by amount of input print usage */
    if (argc == 1) {
        usage(lang);
        return 0;
    } else if (argc > 3 && portOrEnv != "-e") { 
        cout << "\n" << languageVector[TWO] << endl;
        usage(lang);
        return 2;
    }
    
    /* set port and flag if available */
    if (argc >= 2) flag = args[1];
    
    /* Check for environmental variable PORT and do with it what is required */
    if (portOrEnv == "-e" && (flag == "-p" || flag == "--port")) {
        if (getenv("PORT") == "" || getenv("PORT") == nullptr) {
            cout << "\n" << languageVector[NINE] << endl;
            usage(lang);
            return 9;
        } else portEnv = getenv("PORT");
        if (argc == 4) {
            if (isInt(args[3])) {
                port = atoi(args[3]);
                if (port <= MINPORT || port >= MAXPORT) {
                    cout << "\n" << languageVector[EIGHT] << endl;
                    usage(lang);
                    return 8; 
                }
                cout << languageVector[LISTENING] << " " << args[3] << endl;
                return 0;
            } else {
                cout << "\n" << languageVector[TWO] << endl;
                usage(lang);
                return 2;
            }
        } else {
            cout << languageVector[LISTENING] << " " << portEnv << endl;
            return 0;
        }
    } else if (argc == 3) port = atoi(args[2]); 

    /* check the flags and flag paramaters */
    if (flag == "-p" || flag == "--port") {
        if (argc == 2) {
            cout << "\n" << languageVector[SEVEN] << endl;
            usage(lang);
            return 7;
         } else if (port <= MINPORT || port >= MAXPORT || isInt(args[2]) == false) {
            cout << "\n" << languageVector[EIGHT] << endl;
            usage(lang);
            return 8;
        } else if (argc == 3 && port) cout << languageVector[LISTENING] << " " << port << endl;
    } else if (flag == "-h" || flag == "--help" || flag == "-?") {
        if (argc == 2) usage(lang);
        else if (argc > 2) {
            cout << "\n" << languageVector[TWO] << endl;
            usage(lang);
            return 2;
        }
    } else if (flag == "-!" || flag == "--about") {
        if (argc == 2) about(lang);
        else if (argc > 2) {
            cout << "\n" << languageVector[TWO] << endl;
            usage(lang);
            return 2;
        }
    } else if (flag == "-v" || flag == "--version") {
        if (argc > 2) {
            cout << "\n" << languageVector[TWO] << endl;
            usage(lang);
            return 2;
        }
        cout << "\n" << languageVector[VERSION] << " " << VERSION_NUM  << "\n" << endl;
    } else {
        cout << "\n" << languageVector[TEN] << endl;
        usage(lang);
        return 10;
    }
    return 0;
}

/* Function Implementations */
void usage(string lang) {
    printFromFile("textFiles/portsetter.usage_" + lang + ".txt");
}

void about(string lang) {
    printFromFile("textFiles/portsetter.about_" + lang + ".txt");
}

string language() {
    string lang = "";
    /* These are all the Environmental variables you can set for language. check them! */
    vector<string> envVarLang;
    envVarLang.push_back("LANGUAGE");
    envVarLang.push_back("LC_ALL");
    envVarLang.push_back("LC_MESSAGES");
    envVarLang.push_back("LANG");
    
    for (int i = 0; i < envVarLang.size(); i++) {
        string envLang = getenv(envVarLang[i].c_str());
        /* Check ignored values */
        if (envLang != "" && envLang != "C" && envLang != "C.UTF-8" && envLang.size() > 0) {
            /* get the first 2 letters for language */
            for (int i = 0; i < 2; i++) {
                lang += envLang[i];
            }
            return lang;
        } 
        if (i == envVarLang.size()-1) {
            /* default language is english */
            return "en";
        }
    }
}

void languageMessages(vector<string>& languageVector, string lang){
    string line;
    cout << endl;
    
    /* print results from file */
    ifstream myfile ("textFiles/errors_" + lang + ".txt");
    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            languageVector.push_back(line);
        }
        myfile.close();
    } else cout << "There was an error opening the errors output file" << endl;
}


void printFromFile(string fileName) {
    string line;
    cout << endl;
    
    /* print results from file */
    ifstream myfile (fileName);
    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            cout << line << '\n';
        }
        myfile.close();
    } else cout << "There was an error opening the test output file" << endl;
    
    cout << endl;
}

bool isInt(string str) {
    if (str == "") return false;
    for (int i = 0; i < str.size(); i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}