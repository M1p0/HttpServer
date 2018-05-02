#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>


using namespace std;

class FileIO
{
public:
    FileIO()
    {
        std::ios::sync_with_stdio(false);   //�ر���stdio��ͬ�� �ӿ�I/O�ٶ�
    }
    void Create(string location);//����File.Create("c:\\test.txt")
    void Write(string location, string data);
    void Read(string location, int mode = 0);  //0Ϊ�ı���ʽ 1Ϊ�����Ʒ�ʽ 
    void Copy(string SourceFile, string NewFile);
    void ListDir(LPCTSTR lpFileName);
    void Backup();
    void CopyFolder(string szPath, string szTarget);
};
