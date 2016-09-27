# Running Tests on PortSetter program #

**Without the files the program will not run correctly**

**NOTICE:**
If you want your program to run by only typing: `setport`
you will have to set an alias for the program name, This is done by:

1. opening command prompt
2. cd to the directory where "portsetter.cpp.o" is: `cd path/to/file/` 
* where `path/to/file` is the actual path to the folder where "portsetter.cpp.o" is
3. type in the command prompt: `alias setport="./portsetter.cpp.o"`

if this is not an issue for you, continue to type: `./portsetter.cpp.o`

## Setting an environmental variable ##

1. open command prompt
2. type `export PORT=NUMBER_YOU_WANT`
* i.e. : `export PORT=8080`
* this sets the environmental variable `PORT` to 8080.

## Setting language preference ##

1. open command prompt
2. type `export LANGUAGE=LANGUAGE_YOU_WANT`
* i.e. : `export LANGUAGE=es_MX`
* this sets the language to spanish.
* valid languages are english and spanish
* environmental variables to use: 
    * LANGUAGE
    * LC_ALL
    * LC_MESSAGES
    * LANG
* set one of these to the language you want 

## Running Tests ##

To run the tests on Portsetter:

1. open command prompt
2. cd to the directory where "testsetport.cpp.o" is same as ("portsetter.cpp.o"): `cd path/to/file/` 
* where `path/to/file` is the actual path to the folder where "testsetport.cpp.o" is
3. type in the command prompt: `./testsetport.cpp.o`
4. This will print out all test cases where you can see the results