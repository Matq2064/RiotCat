#ifndef RIOTCAT_FILES_H
#define RIOTCAT_FILES_H

#include <fstream>
using namespace std;

class CWriteFiles {
private:
    ofstream m_File;
    bool m_Error;

public:
    CWriteFiles(const char* filepath);

    bool Error() const { return m_Error; }
    void Close();
    void AddInt(int Int);
};

class CReadFiles {
private:
    ifstream m_File;
    bool m_Error;

public:
    CReadFiles(const char* filepath);

    bool Error() const { return m_Error; }
    void Close();
    int GetInt();
};

#endif //RIOTCAT_FILES_H
