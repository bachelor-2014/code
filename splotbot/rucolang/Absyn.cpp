#include <string>
#include <iostream>
#include "Absyn.h"

using namespace std;

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
    /**
     * ComponentCall Implementations
     */
    ComponentCall::ComponentCall(string *component, string *action, vector<int> *args): component(component), action(action), args(args) {
        //Empty
    }

    string ComponentCall::toString() {
        string a;
        for(int arg : *args){
            a += to_string(arg) + " ";
        }
        return "Component: " + *component + " Action: " + *action + " Args: " + a;
    }
}
