#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <typeinfo>
#include <vector>

using namespace std;

template <typename U>
struct Entry {
	string Timestamp;
	string ComponentType;
	string ComponentName;
	string ActivityType;
	U Data;

	Entry(string time, string comType, string comName,
			string activityType, U data):
		Timestamp(time),
		ComponentType(comType),
		ComponentName(comName),
		ActivityType(activityType),
		Data(data){}
};

template <typename T>
class Logger {

    public:
        Logger(){
		directory = "./data/logs/";
	};
        ~Logger(){};

        virtual vector<Entry<T>> Read(){};

	/**
	* Different types of message
	*/
        virtual bool Info(T t){};
        virtual bool Error(T t){};
	virtual bool Data (T t){};

	// In lieu of constructur (requires specific type or header implementation)
	// TODO: Revisit
	virtual bool Init(string componentType, string componentName){};
	virtual string identifier(Entry<T> entry){};
	virtual bool Clear(){};

	protected:
		string directory;
		string componentType;
		string componentName;
		Entry<T> entry(); // Get a "base" entry with the common fields defined

		virtual bool Write(Entry<T> e){};
};

string getTimeStamp();

#endif
