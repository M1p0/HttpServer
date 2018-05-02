#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

class FileIO
{
public:
    FileIO()
    {
        std::ios::sync_with_stdio(false);   //�ر���stdio��ͬ�� �ӿ�I/O�ٶ�
    }
    void Create(string location);//����File.Create("c:\\test.txt")
    void Write(string location, string data);
    void Read(const char* location, char* buffer, int mode);  //0Ϊ�ı���ʽ 1Ϊ�����Ʒ�ʽ 
    void Copy(string SourceFile, string NewFile);
    void ListDir(const char* lpFileName);
    void Backup();
    void CopyFolder(string szPath, string szTarget);
};
