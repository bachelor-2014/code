#include <iostream>
#include <vector>
#include "dblogger.h"
#include <sqlite3.h>

using namespace std;

const string database = "data/test.db";
sqlite3 *db;
char *zErrMsg = 0;

DBLogger::DBLogger(string id) : Logger(identifier){
    identifier = id;

    if(sqlite3_open(database.c_str(),&db)){
        fprintf(stderr,"can't open database %s\n",sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

}

DBLogger::~DBLogger(){
    sqlite3_close(db);
}

bool DBLogger::writeStringData(string data){
    string sql = "INSERT INTO data (experiment,string_data) VALUES" \
                "('"+identifier+"','"+data+"')";
    int rc = sqlite3_exec(db,sql.c_str(),NULL,0,&zErrMsg);
    if( rc!=SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return false;
    }
    return true;
}

int readData(void *out, int argc, char **argv, char **azColName){

    vector<string> *data = static_cast<vector<string>*>(out);

    int i;
    for(i=0; i<argc; i++){
        if(argv[i] &&
            string("string_data").compare(string(azColName[i])) == 0){
                (*data).push_back(argv[i]);

        }
    }

    for(string s : (*data)){
        cout << "Here was" << s << endl;
    }
    out = data;
    return 0;
}

vector<string> DBLogger::readStringData(){
    string sql = "SELECT * FROM data WHERE " \
                 "experiment='"+identifier+"'";

    vector<string> *data = new vector<string>();

    int rc = sqlite3_exec(db,sql.c_str(),readData,(void*)data,&zErrMsg);
    if( rc!=SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    return (*data);
}
