#ifndef ABSYN_H
#define ABSYN_H

#include<vector>

using namespace std;

class Statement {
    public:
        virtual string toString() {};
};

class ComponentCall: public Statement {
    public:
       ComponentCall(string component, string action, vector<int> args); 
       string toString();

    private:
       string component;
       string action;
       vector<int> args;
};

#endif
