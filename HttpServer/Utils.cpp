#include <string>
using namespace std;

void FindLast(const char* Source, const char* Target, size_t &Pos)
{
    string Src = Source;
    Pos = Src.find_last_of(Target);
}

void GetExtension(const char* Source, char* buffer)
{
    size_t Pos = 0;
    FindLast(Source, ".", Pos);
    size_t Length = strlen(Source);
    strncat(buffer, Source + Pos, Length - Pos);
}