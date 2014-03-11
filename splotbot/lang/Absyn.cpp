#include <string>
#include "Absyn.h"

using namespace std;

ComponentCall::ComponentCall(string component, string action, vector<int> args): component(component), action(action), args(args) {
    //Empty
}

string ComponentCall::toString() {
    return "Component: " + component + " Action: " + action;
}
