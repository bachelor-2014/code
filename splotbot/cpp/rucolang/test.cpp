#include <iostream>
#include <cstdio>
#include "rucola.h"
#include "compileargs.h"
using namespace std;
using namespace Rucola;

void prettyPrint(vector<int> result){
    cout << "[";
    for(int i :result){
        cout << to_string(i) << ",";
    }
    cout << "]" << endl;
}

main() {

    auto m = map<string,map<string,CompileArgs>>();
    CompileArgs module1;
    module1.Action = 1;
    module1.NumberofArguments = 2;

    CompileArgs module2;
    module2.Action = 2;
    module2.NumberofArguments = 2;

    m["module1"]["do"] = module1;
    m["module2"]["do"] = module2;

    Rucolang r = Rucolang();
    r.RegisterComponentCalls(m);

    string s = 
        "module1.do(-1,2)"
        " x = 2 "
        " a = 5 + x * 3 "
        " b = x * (3 + 5) "
        "module2.do(a,b)"
        "(event: a, b) -> { module1.do(a,b+x) }";

    auto result = r.Compile(s);
    
    cout << r.CodeToString(s);

    cout << "Result:" << endl;
    prettyPrint(result);

    vector<int> args = {1,2};
    auto event = r.Event("event", args);
    cout << "Event:" << endl;
    prettyPrint(event);
}

