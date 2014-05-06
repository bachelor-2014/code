#include <iostream>
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

    function<void(string,string,vector<int>)> fun = [](string eventName, string
            data, vector<int> v){
        cout << eventName << ": " << data << endl;
    };

    Rucolang r = Rucolang();
    r.RegisterComponentCalls(m);
    r.RegisterEventCallback(&fun);

    string s = 
        "module1.do(-1,2)"
        " x = 3 "
        " if (x == 2) { a = 5 } else { a = 7 } "
        " b = 1 <= 2 && 3 == 3 "
        "if(1){module2.do(a,b)}else{ a = 2}"
        "print \"hello world\" (a,b)"
        "(event1: a, b) -> { module1.do(a,x) x=4 }"
        "(event2: a, b) -> { module1.do(a,x) }"
        "(event: a_, _b) -> { module1.do(a_,_b+x) }";

    auto result = r.Compile(s);
    
    cout << r.CodeToString(s);

    cout << "Result:" << endl;
    prettyPrint(result);

    vector<int> args = {1,2};
    auto event = r.Event("event", args);
    auto event1 = r.Event("event1", args);
    auto event2 = r.Event("event2", args);
    cout << "Event:" << endl;
    prettyPrint(event);
    cout << "Event1:" << endl;
    prettyPrint(event1);
    cout << "Event2:" << endl;
    prettyPrint(event2);
}

