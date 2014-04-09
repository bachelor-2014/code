#include <iostream>
#include <vector>
#include "dblogger.h"
#include <sqlite3.h>

using namespace std;

const string database = "data/experiments.db";
sqlite3 *db;
char *zErrMsg = 0;

DBLogger::DBLogger(string id) : Logger(id){
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

bool DBLogger::Write(string data){
    return write("none",data);
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

    out = data;
    return 0;
}

vector<string> DBLogger::Read(){
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

bool DBLogger::Info(string s){
    return write("info",s);
}
bool DBLogger::Error(string s){
    return write("error",s);
}
bool DBLogger::Clear(){
    string sql = "DELETE FROM data WHERE "\
                  "experiment='"+identifier+"'";

    int rc = sqlite3_exec(db,sql.c_str(),NULL,NULL,&zErrMsg);

    if( rc!=SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return false;
    }

    return true;
}

bool DBLogger::write(string type, string data){
    string sql = "INSERT INTO data (experiment,typ,string_data) VALUES" \
                "('"+identifier+"','"+type+"','"+data+"')";
    int rc = sqlite3_exec(db,sql.c_str(),NULL,0,&zErrMsg);
    if( rc!=SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return false;
    }
    return true;
}
