#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <inttypes.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/file.h>
#include <errno.h>

int Filter(int argc, char const *argv[]);
void FixSize(int *userLimit);
void StringPrint(const int fd, const int fileSize, const int RAMLimit, const int stringNumber);
void GetStringPrint(int fd, int size, char const* filename, int numStr);
void Info(const int fd, const int fileSize, const int RAMLimit);
void GetInfo(int fd, int size, char const* filename);
void Search(const int fd, const int fileSize, const int RAMLimit, char const* subString);
void GetStringSearch(int fd, int size, char const* filename, char const* subString);
char* Process(char const* src);
int RemoveOldString(const int fd, const int fileSize, const int RAMLimit, const int start, const int end);
void InsertNewString(const int fd, const int fileSize, const int RAMLimit, char const *string, const int start, const int end);
void ReplaceString(const int fd, const int fileSize,  const int RAMLimit, char const *oldString, const int sizeOldStr, char const *newString, const int sizeNewStr);
void GetStringReplace(int fd, int size, char const* filename, char const* oldString, char const* newString);
void Information(void);
void Menu(void);
#endif