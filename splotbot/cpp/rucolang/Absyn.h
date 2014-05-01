#ifndef ABSYN_H
#define ABSYN_H

#include<vector>
#include<string>
#include<map>
#include "compileargs.h"

using namespace std;


namespace Rucola {

    /**
     * An expression such as an integer or a variable
     */
    class Expr {
        public:
           virtual string toString() {};
           virtual void Compile(map<string,map<string,CompileArgs>>
                   componentCalls, map<string, int> *env, vector<int> *result){};
    };

    /**
     * An integer expression
     */
    class IExpr: public Expr {
        public:
           IExpr(int value);
           string toString() override;
           void Compile(map<string,map<string,CompileArgs>> componentCalls,
                    map<string, int> *env, 
                    vector<int> *result);

        private:
           int value;
    };

    /**
     * A variable
     */
    class VExpr: public Expr {
        public:
           VExpr(string *value);
           string toString();
           void Compile(map<string,map<string,CompileArgs>> componentCalls,
                    map<string, int> *env, 
                    vector<int> *result);

        private:
           string *value;
    };

    /**
     * A Statement Interface
     */
    class Statement {
        public:
            virtual string toString() {};
            virtual void Compile(map<string,map<string,CompileArgs>>
                    componentCalls, map<string, int> *env, map<string, Statement*>
                    *events, vector<int> *result){};
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
            void Compile(map<string,map<string,CompileArgs>> componentCalls,
                    map<string, int> *env, map<string, Statement*> *events,
                    vector<int> *result);
        private:
            vector<Statement*> statements;
    }; 

    /**
     * A call to a component's action
     */
    class ComponentCall: public Statement {
        public:
           ComponentCall(string *component, string *action, vector<Expr*> *args); 
           string toString();
           void Compile(map<string,map<string,CompileArgs>> componentCalls,
                    map<string, int> *env, map<string, Statement*> *events,
                   vector<int> *result);

        private:
           string *component;
           string *action;
           vector<Expr*> *args;
    };

    class Event: public Statement {
        public:
            Event(string *eventName, Block *block);
            string toString(); 
            void Compile(map<string,map<string,CompileArgs>> componentCalls,
                    map<string, int> *env, map<string, Statement*> *events,
                    vector<int> *result);
            void Call(map<string,map<string,CompileArgs>> componentCalls,
                    map<string, int> *env, map<string, Statement*> *events,
                    vector<int> *result);
        private:
            string *eventName;
            Block *block;
    };

    /**
     * Assignment of a value to a variable
     */
    class Assignment: public Statement {
        public:
           Assignment(string *varName, Expr * expr); 
           string toString();
           void Compile(map<string,map<string,CompileArgs>> componentCalls,
                    map<string, int> *env, map<string, Statement*> *events,
                   vector<int> *result);

        private:
           string *varName;
           Expr *expr;
    };

}

#endif
