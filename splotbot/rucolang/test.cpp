#include <iostream>
#include <cstdio>
#include "rucola.h"
#include "compileargs.h"
using namespace std;
using namespace Rucola;

main() {

    auto m = map<string,map<string,CompileArgs>>();
    CompileArgs module1;
    module1.Action = 1;
    module1.NumberofArguments = 1;

    CompileArgs module2;
    module2.Action = 1;
    module2.NumberofArguments = 1;

    m["module1"]["do"] = module1;
    m["module2"]["do"] = module2;

    Rucolang r = Rucolang();
    r.RegisterComponentCalls(m);

    string s = 
        "module1.do(1,2)"
        "module2.do(1,2)";

    auto result = r.Compile(s);

    cout << "[";
    for(int i :result){
        cout << to_string(i) << ",";
    }
    cout << "]" << endl;

}

