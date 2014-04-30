#include <string>
#include <iostream>
#include "Absyn.h"
#include "compileargs.h"

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
            vector<int> *result){
        for(Statement* s: statements){
            s->Compile(componentCalls, result);
        }
    }
    /**
     * ComponentCall Implementations
     */
    ComponentCall::ComponentCall(string *component, string *action, vector<int>
            *args): component(component), action(action), args(args) {
        //Empty
    }

    string ComponentCall::toString() {
        string a;
        for(int arg : *args){
            a += to_string(arg) + " ";
        }
        return "Component: " + *component + " Action: " + *action + " Args: " + a;
    }

    void ComponentCall::Compile(map<string,map<string,CompileArgs>>
            componentCalls, vector<int> *result){
        result->push_back(componentCalls[(*component)][(*action)].Action);
        result->insert(result->end(),args->begin(),args->end());
    }
}
