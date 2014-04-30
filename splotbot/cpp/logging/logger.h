#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <typeinfo>
#include <vector>

using namespace std;

template <typename U>
struct Entry {
	long Timestamp;
	string ComponentType;
	string ComponentName;
	string ActivityType;
	U Data;

	Entry(long time, string comType, string comName,
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
        Logger(){};
        ~Logger(){};

        virtual vector<Entry<T>> Read(){};

		/**
		 * Different types of message
		 */
        virtual bool Info(T t){ cout << "Whoops" << endl; };
        virtual bool Error(T t){};
		virtual bool Data (T t){};

		// In lieu of constructur (requires specific type or header implementation)
		// TODO: Revisit
		virtual bool Init(string componentType, string componentName){};

	protected:
		string directory = "./data/logs/";
		string componentType;
		string componentName;
		Entry<T> entry(); // Get a "base" entry with the common fields defined

        virtual bool Write(Entry<T> e){};
		virtual string identifier(Entry<T> entry){};

		bool Clear();
};

#endif
