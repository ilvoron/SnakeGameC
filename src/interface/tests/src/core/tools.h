#ifndef TOOLS_H
#define TOOLS_H

bool CompareFiles(const char file1Path[], const char file2Path[]);
void SimulateKeyPress(int keyCode);
void SimulateKeyPressAssync(unsigned int keysCount, ...);
void ClearKeyInputBuffer();
void FreeTools();

#endif