#include <string>
#include "Absyn.h"

using namespace std;

/**
 * Program Implementation
 */
Program::Program(vector<Statement> statements): statements(statements) {
    //Empty
}

vector<Statement> Program::GetStatements(){
    return statements;
}

/**
 * Block Implementation
 */
Block::Block(vector<Statement> statements): statements(statements) {
    //Empty
}

Block::Block(Statement stmt) {
    statements.push_back(stmt);
}

void Block::AddStatement(Statement stmt) {
    statements.push_back(stmt);
}

void Block::AddBlock(Block b){
    vector<Statement> bstmts = b.GetStatements();
    statements.insert(statements.end(), bstmts.begin(), bstmts.end()); 
}

vector<Statement> Block::GetStatements(){
    return statements;
}

string Block::toString() {
    string s;
    for(Statement stmt : statements){
        s += stmt.toString();
    }
}
/**
 * ComponentCall Implementations
 */
ComponentCall::ComponentCall(string component, string action, vector<int> args): component(component), action(action), args(args) {
    //Empty
}

string ComponentCall::toString() {
    return "Component: " + component + " Action: " + action;
}
