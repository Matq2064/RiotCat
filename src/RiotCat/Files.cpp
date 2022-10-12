#include "Files.h"

CWriteFiles::CWriteFiles(const char* filepath) {
    m_File.open(filepath, ios::binary);
    m_Error = !m_File.is_open();
    if (m_Error)
        printf("Couldn't open file: %s\n", filepath);
}

void CWriteFiles::Close() {
    if (m_File.is_open())
        m_File.close();
}

void CWriteFiles::AddInt(int Int) {
    m_File.write((char*)&Int, sizeof(int));
}

CReadFiles::CReadFiles(const char* filepath) {
    m_File.open(filepath, ios::binary);
    m_Error = !m_File.is_open();
    if (m_Error)
        printf("Couldn't open file: %s\n", filepath);
}

void CReadFiles::Close() {
    m_File.close();
}

int CReadFiles::GetInt() {
    int Int;
    m_File.read((char*)&Int, sizeof(int));
    return Int;
}
