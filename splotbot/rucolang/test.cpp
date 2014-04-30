#include <iostream>
#include <cstdio>
#include "rucola.h"
using namespace std;
using namespace Rucola;

main() {

    auto m = map<string,map<string,int>>();
    m["module1"]["do"] = 1;
    m["module2"]["do"] = 2;

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

