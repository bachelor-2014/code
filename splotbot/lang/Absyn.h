#ifndef ABSYN_H
#define ABSYN_H

#include<vector>

using namespace std;


class Statement {
    public:
        virtual string toString() {};
        //virtual vector<int> compile() {};
};

class Program {
    public:
        Program(vector<Statement> statements);
        vector<Statement> GetStatements();
    private:
        vector<Statement> statements;
};

class Block: public Statement {
    public:
        Block(vector<Statement> statements);
        Block(Statement statements);
        void AddStatement(Statement stmt);
        void AddBlock(Block b);
        vector<Statement> GetStatements();
        string toString();
    private:
        vector<Statement> statements;
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
