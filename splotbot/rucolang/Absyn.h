#ifndef ABSYN_H
#define ABSYN_H

#include<vector>
#include<string>

using namespace std;


namespace Rucola {
    class Statement {
        public:
            virtual string toString() {};
            //virtual vector<int> compile() {};
    };

    class Block: public Statement {
        public:
            Block();
            Block(Statement *stmt);
            void AddStatement(Statement *stmt);
            void AddBlock(Block *b);
            vector<Statement*> GetStatements();
            string toString();
        private:
            vector<Statement*> statements;
    }; 

    class ComponentCall: public Statement {
        public:
           ComponentCall(string *component, string *action, vector<int> *args); 
           string toString();

        private:
           string *component;
           string *action;
           vector<int> *args;
    };
}

#endif
