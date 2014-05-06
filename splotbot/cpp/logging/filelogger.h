#ifndef FILELOGGER_H
#define FILELOGGER_H

#include <iostream>
#include <fstream>
#include <typeinfo>
#include "logger.h"

using namespace std;

class FileLogger : public Logger<string> {

    public:
        FileLogger(string componentType, string componentName);
        ~FileLogger();

        vector<Entry<string>> Read();

        bool Info(string);
        bool Error(string);
	bool Data(string);
	bool Clear();
	string identifier(Entry<string>);

	protected:
        bool Write(Entry<string>);
	Entry<string> entry();

	private:
		string filename;
		ofstream *dataOut;
};

#endif
