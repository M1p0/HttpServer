#pragma once

class BitMap //default 1024*4*8 states
{
public:

    BitMap();
    BitMap(unsigned int size);
    int operator[](unsigned int pos);    //��ֵ�����޸�
    unsigned int Capacity();    //ʵ�ʿɴ�����
    unsigned int Size();    //�Ѵ�������
    int Insert(unsigned int val);
    bool Exist(unsigned int val);
    ~BitMap();
private:
    unsigned int* Data;
    unsigned int uCapacity;    //Data����Ĵ�С
    unsigned int uSize;         //�Ѵ�������
};

