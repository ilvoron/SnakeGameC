#ifndef TOOLS_H
#define TOOLS_H

const char* RemoveNewlines(char *str);
bool CompareFiles(const char file1Path[], const char file2Path[]);
void SimulateKeyPress(int keyCode);
void SimulateKeyPressAssync(unsigned int keysCount, ...);
void ClearKeyInputBuffer();
void FreeTools();

#endif