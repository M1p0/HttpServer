#pragma once
//��Ҫ�Լ����mysqlͷ�ļ�Ŀ¼
#include <iostream>
#include <mysql.h>
#include <string>
#include <vector>
using namespace std;
class MDatabase
{
public:
    MDatabase();
    ~MDatabase();
    int Connect(const char* IP,const char* User,const char* Password,const char* DbName,int Port);
    int SetEncoding(const char* Encoding);
    int ExecSQL(const char* SQL, vector<vector<string>> &Result, int &nRow);
    void Init();
private:
    MYSQL * pConn;
};
