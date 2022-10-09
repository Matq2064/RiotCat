#ifndef RIOTCAT_FILES_H
#define RIOTCAT_FILES_H

#include <fstream>
using namespace std;

class CWriteFiles {
private:
    ofstream m_File;

public:
    CWriteFiles(const char* filepath);

    void Close();
    void AddInt(int Int);
};

class CReadFiles {
private:
    ifstream m_File;

public:
    CReadFiles(const char* filepath);

    void Close();
    int GetInt();
};

#endif //RIOTCAT_FILES_H
