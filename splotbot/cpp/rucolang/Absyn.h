#ifndef ABSYN_H
#define ABSYN_H

#include<vector>
#include<string>
#include<map>
#include<functional>
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
           string toString();
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
     * An arithmetic expression
     */
    class AExpr: public Expr {
        public:
           AExpr(string *op, Expr *expr1, Expr *expr2);
           string toString();
           void Compile(map<string,map<string,CompileArgs>> componentCalls,
                    map<string, int> *env, 
                    vector<int> *result);

        private:
           string *op;
           Expr *expr1;
           Expr *expr2;
    };

    /**
     * A Statement Interface
     */
    class Statement {
        public:
            virtual string toString() {};
            virtual void Compile(map<string,map<string,CompileArgs>>
                    componentCalls, map<string, int> *env, map<string, Statement*>
                    *events, vector<int> *result, function<void(string, string, vector<int>)> eventCallback){};
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
                    vector<int> *result, function<void(string, string, vector<int>)> eventCallback);
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
                   vector<int> *result, function<void(string, string, vector<int>)> eventCallback);

        private:
           string *component;
           string *action;
           vector<Expr*> *args;
    };

    class Event: public Statement {
        public:
            Event(string *eventName, vector<string*> *argNames, Block *block);
            string toString(); 
            void Compile(map<string,map<string,CompileArgs>> componentCalls,
                    map<string, int> *env, map<string, Statement*> *events,
                    vector<int> *result, function<void(string, string, vector<int>)> eventCallback);
            void Call(vector<int> args, map<string,map<string,CompileArgs>> componentCalls,
                    map<string, int> *env, map<string, Statement*> *events,
                    vector<int> *result, function<void(string, string, vector<int>)> eventCallback);
        private:
            string *eventName;
            Block *block;
            vector<string*> *argNames;
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
                   vector<int> *result, function<void(string, string, vector<int>)> eventCallback);

        private:
           string *varName;
           Expr *expr;
    };

    /**
     * Conditional statement
     */
    class Conditional: public Statement {
        public:
           Conditional(Expr *condition, Block *block1, Block *block2);
           string toString();
           void Compile(map<string,map<string,CompileArgs>> componentCalls,
                    map<string, int> *env, map<string, Statement*> *events,
                   vector<int> *result, function<void(string, string, vector<int>)> eventCallback);

        private:
           Expr *condition;
           Block *block1;
           Block *block2;
    };

    class Print: public Statement {
        public:
            Print(string *str, vector<Expr*> *args);
            void Compile(map<string,map<string,CompileArgs>> componentCalls,
                    map<string, int> *env, map<string, Statement*> *events,
                    vector<int> *result, function<void(string, string, vector<int>)> eventCallback);
        private:
            string *str;
            vector<Expr*> *args;
    };
}

#endif
