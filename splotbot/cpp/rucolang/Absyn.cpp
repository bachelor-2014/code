#include <string>
#include <iostream>
#include "Absyn.h"
#include "compileargs.h"
#include "../utils/errors.h"

using namespace std;
using namespace Rucola;

namespace Rucola{
    /**
     * Block Implementation
     */
    Block::Block() {
        statements = vector<Statement*>();
    }

    Block::Block(Statement *stmt) {
        statements = vector<Statement*>();
        statements.push_back(stmt);
    }

    void Block::AddStatement(Statement *stmt) {
        statements.push_back(stmt);
    }

    void Block::AddBlock(Block *b){
        vector<Statement*> bstmts = b->GetStatements();
        statements.insert(statements.end(), bstmts.begin(), bstmts.end()); 
    }

    vector<Statement*> Block::GetStatements(){
        return statements;
    }

    string Block::toString() {
        string s;
        s += "{\n";
        for(Statement *stmt : statements){
            s += stmt->toString() + "\n";
        }

        s += "}\n";
        return s;
    }

    void Block::Compile(map<string,map<string,CompileArgs>> componentCalls,
            map<string, int> *env, map<string, Statement*> *events, vector<int>
            *result){
        for(Statement* s: statements){
            s->Compile(componentCalls, env, events, result);
        }
    }
    /**
     * ComponentCall Implementations
     */
    ComponentCall::ComponentCall(string *component, string *action, vector<Expr*>
            *args): component(component), action(action), args(args) {
        //Empty
    }

    string ComponentCall::toString() {
        string a;
        for(auto arg : *args){
            a += arg->toString() + " ";
        }
        return "Component: " + *component + " Action: " + *action + " Args: " + a;
    }

    void ComponentCall::Compile(map<string,map<string,CompileArgs>>
            componentCalls, map<string,int> *env, map<string, Statement*>
            *events, vector<int> *result){

        if(!componentCalls.count((*component))){
            string err = "Component does not exist: " + (*component);
            throw RucolaException(err.c_str());
        }

        if(!componentCalls[(*component)].count((*action))){
            string err = (*component) + " does not have action: " + (*action);
            throw RucolaException(err.c_str());
        }


        CompileArgs ca = componentCalls[(*component)][(*action)];
        if((*args).size() == ca.NumberofArguments){
            result->push_back(ca.Action);

            for (auto e : *args) {
                e->Compile(componentCalls, env, result);
            }
        }else{
            string err = (*component) + " with action '" + (*action) + "' takes " + to_string(ca.NumberofArguments) + " arguments, you supplied " + to_string((*args).size());
            throw RucolaException(err.c_str());
        }
    }

    Assignment::Assignment(string *varName, Expr *expr): varName(varName), expr(expr) {
        // Empty constructor
    }

    string Assignment::toString() {
        return "Assignment(" + *varName + ", " + expr->toString() + ")";
    }

    void Assignment::Compile(map<string,map<string,CompileArgs>> componentCalls,
            map<string, int> *env, map<string, Statement*> *events,
            vector<int> *result) {
        expr->Compile(componentCalls, env, result);
        int val = result->back();
        result->pop_back();
        (*env)[(*varName)] = val;
    }

    Conditional::Conditional(Expr *condition, Block *block1, Block *block2): condition(condition), block1(block1), block2(block2) {
        // Empty constructor
    }

    string Conditional::toString() {
        return "Conditional(" + condition->toString() + ", " + block1->toString() + ", " + block2->toString() + ")";
    }

    void Conditional::Compile(map<string,map<string,CompileArgs>> componentCalls,
            map<string, int> *env, map<string, Statement*> *events,
            vector<int> *result) {
        condition->Compile(componentCalls, env, result);
        int val = result->back();
        result->pop_back();

        if (val) {
            block1->Compile(componentCalls, env, events, result);
        } else {
            block2->Compile(componentCalls, env, events, result);
        }
    }

    /**
     * Event
     */
    Event::Event(string *eventName, vector<string*> *argNames, Block *block):
        eventName(eventName), argNames(argNames), block(block) {
        //Empty
    }

    string Event::toString(){
        string s;
        s += "Event: " + *eventName + "-> \n";
        s += block->toString();
        return s;
    }

    void Event::Compile(map<string,map<string,CompileArgs>> componentCalls,
            map<string, int> *env, map<string, Statement*> *events, vector<int>
            *result){
        (*events)[(*eventName)] = this;
    }

    void Event::Call(vector<int> args, map<string,map<string,CompileArgs>>
            componentCalls, map<string, int> *env, map<string, Statement*>
            *events, vector<int> *result){
        if(args.size() < argNames->size()){
            string err = (*eventName) + " takes at most " +
                to_string(args.size()) + " arguments, you defined it as" +
                to_string(argNames->size());
            throw RucolaException(err.c_str());
        }
        int i = 0;
        for(string *argName : (*argNames)){
           (*env)[(*argName)] = args[i];
           i++;
        }
        block->Compile(componentCalls, env, events, result);
    }

    /**
     * Expre
     */
    
    IExpr::IExpr(int value): value(value) {
        // Empty constructor
    }

    string IExpr::toString() {
        return "IExpr(" + to_string(value) + ")";
    }

    void IExpr::Compile(map<string,map<string,CompileArgs>> componentCalls,
            map<string, int> *env, vector<int> *result) {
        result->push_back(value);
    }

    VExpr::VExpr(string *value): value(value) {
        // Empty constructor
    }

    string VExpr::toString() {
        return "VExpr(" + *value + ")";
    }

    void VExpr::Compile(map<string,map<string,CompileArgs>> componentCalls, map<string, int> *env, vector<int> *result) {
        if (env->count(*value)) {
            result->push_back((*env)[(*value)]);
        } else {
            throw RucolaException(("Can not get value of unassigned variable '" + (*value) + "'").c_str());
        }
    }

    AExpr::AExpr(string *op, Expr *expr1, Expr *expr2): op(op), expr1(expr1), expr2(expr2) {
        // Empty constructor
    }

    string AExpr::toString() {
        return "AExpr(" + (*op) + ", " + expr1->toString() + ", " + expr2->toString() + ")";
    }

    void AExpr::Compile(map<string,map<string,CompileArgs>> componentCalls, map<string, int> *env, vector<int> *result) {
        expr1->Compile(componentCalls, env, result);
        int val1 = result->back();
        result->pop_back();

        expr2->Compile(componentCalls, env, result);
        int val2 = result->back();
        result->pop_back();

        int resultVal;
        
        // Determine the operator type
        if (op->compare("+") == 0) {
            resultVal = val1 + val2;
        } else if (op->compare("-") == 0) {
            resultVal = val1 - val2;
        } else if (op->compare("*") == 0) {
            resultVal = val1 * val2;
        } else if (op->compare("/") == 0) {
            resultVal = val1 / val2;
        } else if (op->compare("%") == 0) {
            resultVal = val1 % val2;
        } else if (op->compare("==") == 0) {
            resultVal = val1 == val2;
        } else if (op->compare("!=") == 0) {
            resultVal = val1 != val2;
        } else if (op->compare("<") == 0) {
            resultVal = val1 < val2;
        } else if (op->compare("<=") == 0) {
            resultVal = val1 <= val2;
        } else if (op->compare(">") == 0) {
            resultVal = val1 > val2;
        } else if (op->compare(">=") == 0) {
            resultVal = val1 >= val2;
        } else if (op->compare("&&") == 0) {
            resultVal = val1 && val2;
        } else if (op->compare("||") == 0) {
            resultVal = val1 || val2;
        } else {
            throw RucolaException(("Unknown operator '" + (*op) + "'").c_str());
        }

        result->push_back(resultVal);
    }
}
