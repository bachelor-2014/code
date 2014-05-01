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
    module1.NumberofArguments = 2;

    CompileArgs module2;
    module2.Action = 2;
    module2.NumberofArguments = 2;

    m["module1"]["do"] = module1;
    m["module2"]["do"] = module2;

    Rucolang r = Rucolang();
    r.RegisterComponentCalls(m);

    string s = 
        "module1.do(1,2)"
        " hej = 3 "
        "module2.do(1,hej)";

    auto result = r.Compile(s);

    cout << "[";
    for(int i :result){
        cout << to_string(i) << ",";
    }
    cout << "]" << endl;

}

