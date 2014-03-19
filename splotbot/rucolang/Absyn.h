#ifndef ABSYN_H
#define ABSYN_H

#include<vector>
#include<string>

using namespace std;


namespace Rucola {
    /**
     * A Statement Interface
     */
    class Statement {
        public:
            virtual string toString() {};
            //virtual vector<int> compile() {};
    };

    /**
     * A Block of Statements
     */
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

    /**
     * A call to a component's action
     */
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
