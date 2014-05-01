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
                e->Compile(componentCalls, result);
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

    void Assignment::Compile(map<string,map<string,CompileArgs>> componentCalls, vector<int> *result) {
        //TODO
    }

    /**
     * Event
     */
    Event::Event(string *eventName, Block *block): eventName(eventName),
    block(block) {
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
        //TODO: Event Mapping
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

    void IExpr::Compile(map<string,map<string,CompileArgs>> componentCalls, vector<int> *result) {
        result->push_back(value);
    }

    VExpr::VExpr(string *value): value(value) {
        // Empty constructor
    }

    string VExpr::toString() {
        return "VExpr(" + *value + ")";
    }

    void VExpr::Compile(map<string,map<string,CompileArgs>> componentCalls, vector<int> *result) {
        //TODO
        //result->push_back(value);
    }
}
