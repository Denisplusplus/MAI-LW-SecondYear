#include "FileProcessor.h"


int Filter(int argc, char const *argv[])
{
    if (argc < 2 || argc > 6) {
        printf("Bad agruments\n");
        Information();
        exit(0);
    } else 
    if (argc == 2) {
        if (!strcmp(argv[1], "-help")) {
            return 10;
        } else {
            return 11;
        }
    } else 
    if (argc == 3) {
        if (!strcmp(argv[2], "-info")) {
            return 1;
        }
    } else 
    if (argc == 4) {
        if (!strcmp(argv[2], "-print")) {
            return 2;
        } else 
        if (!strcmp(argv[3], "-info")) {
            return 3;
        } else 
        if (!strcmp(argv[2], "-search")) {
            return 5;
        }    
    } else 
    if (argc == 5) {
        if (!strcmp(argv[3], "-print")) {
           return 4;
        } else 
        if (!strcmp(argv[3], "-search")) {
           return 6;
        } else 
        if (!strcmp(argv[2], "-replace")) {
            return 7;
        }
    } else 
    if (argc == 6 ) {
        if (!strcmp(argv[3], "-replace")) {
            return 8;
        }
    }



}


void FixSize(int *userLimit)
{
    int pageSize = sysconf(_SC_PAGESIZE);

    if (*userLimit < pageSize) {
        *userLimit = pageSize;
    } else if ((*userLimit % pageSize) != 0) {
        int count = 0;
        while (*userLimit > pageSize) {
            *userLimit -= pageSize;
            ++count;
        }

        *userLimit = pageSize * count;
    }
}


void StringPrint(const int fd, const int fileSize, const int RAMLimit, const int stringNumber)
{
    if (stringNumber <= 0) {
        printf("Number of the string must be positive\n");
        exit(0);
    }

    int size = (RAMLimit > fileSize) ? fileSize : RAMLimit;
    int offset = 0, lineCnt = 1;
    char *addr;
    int printed = 0;

    while (offset < fileSize) {
        addr = (char *)mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, fd, offset);
        if (addr == MAP_FAILED) {
            printf("mmap");
            exit(1);
        }

        for (int i = 0; i < size; ++i) {
            if (stringNumber == lineCnt) {
                putchar(addr[i]);
                printed = 1;
            }
            if (addr[i] == '\n') {
                ++lineCnt;
            }
        }

        if (munmap(addr, size) == -1) {
           printf("munmap");
           exit(2);
        }

        if (printed) {
            return;
        }

        offset += size;
    }
    if (!printed) {
        --lineCnt;
        printf("Wrong number string. Number of strings: %d\n", lineCnt);
        return;
    }
}

void Info(const int fd, const int fileSize, const int RAMLimit)
{
    char *addr;
    int offset = 0, bytepos = 1, lines = 1;
    int size = (RAMLimit > fileSize) ? fileSize : RAMLimit;

    while(offset < fileSize) {
        addr = (char *)mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, fd, offset);
        if (addr == MAP_FAILED) {
            printf("mmap");
            exit(1);
        }

        for (int i = 0; i < size; ++i, ++bytepos) {
            if (addr[i] == '\n') {
                ++lines;
            }
        }

        if (munmap(addr, RAMLimit) == -1) {
            printf("munmap");
            exit(2);
        }

        offset += RAMLimit;
    }

    if (lines > 1) {
        --lines;
    }

    printf("Amount of symbols - %d\nAmount of lines - %d\n", fileSize, lines);
}

char* Process(char const* src) {
    char* dest = (char*) malloc(sizeof(char)*strlen(src));
    size_t len = strlen(src) + 1;
     
    for (size_t i = 0, k = i; i < len && k < len; i++, k++) {
        if (src[i] == '/') {
            switch(src[i+1]) {
                case 'a': {
                  dest[k] = '\a';
                  break;
                }
                case 'b': {
                  dest[k] = '\b';
                  break;
                }
                case 'f': {
                  dest[k] = '\f';
                  break;
                }
                case 'n': {
                  dest[k] = '\n';
                  break;
                }
                case 't': {
                  dest[k] = '\t';
                  break;
                }
                case 'v': {
                  dest[k] = '\v';
                  break;
                }
                case 's': {
                  dest[k] = ' ';
                  break;
                }
                case 'S': {
                  dest[k] = '\\';
                  break;
                }
                case 'q': {
                  dest[k] = '\'';
                  break;
                }
                case 'Q': {
                  dest[k] = '\"';
                  break;
                }
                default:
                  break;
            }
                if (i + 2 < len) {
                  i += 2;
                  k++;
                } 
            }
            dest[k] = src[i];      
    } 

    return(dest);
     
}  
 
     
void Search(const int fd, const int fileSize, const int RAMLimit, char const* subString)
{
      int ssSize = strlen(subString);
      int size = (RAMLimit > fileSize) ? fileSize : RAMLimit;
      int offset = 0, index = 0, bytepos = 1;
      char* addr;
     
      while(offset < fileSize) {
        addr = (char*)mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, fd, offset);
        if (addr == MAP_FAILED) {
          printf("mmap");
          exit(1);
        }
     
        for (int i = 0; i < size; i++, bytepos++) {
          if (addr[i] == subString[index]) {
            i++;
            index++;
     
            for (; (index < ssSize) && (i < size); index++, i++) {
              if (subString[index] != addr[i]) {
                index = 0;
                break;
              }
            }
     
            if (index == ssSize) {
              printf("first entry was found at %d byte\n", bytepos);
              return;
            }
     
          }
     
        }
     
        if (munmap(addr, size) == -1) {
          printf("munmap");
          exit(2);
        }
     
        offset += size;
      }
     
      printf("there is no entries in file\n");
     
}

void CheckFileSize(int fd, char const *filename)
{
    struct stat fileStat;
    fd = open(filename, O_RDWR);
    if (fd == -1) {
        printf("open\n");
        exit(3);
    }
    if (fstat(fd, &fileStat) == -1) {
        printf("fstat");
        exit(4);
    }
    if (fileStat.st_size <=0 || fileStat.st_size > 10000000000) {
        printf("Bad filesize\n");
        exit(10);
    }
}


void GetInfo(int fd, int size, char const* filename)    
{   
    CheckFileSize(fd, filename);
    struct stat fileStat;
    FixSize(&size);
    fd = open(filename, O_RDWR);
    if (fd == -1) {
        printf("open\n");
        exit(3);
    }
    if (fstat(fd, &fileStat) == -1) {
        printf("fstat");
        exit(4);
    }
    Info(fd, fileStat.st_size, size);
    
    close(fd);

}

void GetStringPrint(int fd, int size, char const* filename, int numStr)
{   
    CheckFileSize(fd, filename);
    struct stat fileStat;
    FixSize(&size);
    fd = open(filename, O_RDWR);
    if (fd == -1) {
        printf("open\n");
        exit(3);
    }
    if (fstat(fd, &fileStat) == -1) {
        printf("fstat");
        exit(4);
    }
    StringPrint(fd, fileStat.st_size, size, numStr);
    close(fd);
}

void GetStringSearch(int fd, int size, char const* filename, char const* subString)
{
    CheckFileSize(fd, filename);
    char* str = Process(subString); 
    struct stat fileStat;
    FixSize(&size);
    fd = open(filename, O_RDWR);
    if (fd == -1) {
        printf("open\n");
        exit(3);
    }
    if (fstat(fd, &fileStat) == -1) {
        printf("fstat");
        exit(4);
    }
    Search(fd, fileStat.st_size, size, str);
    close(fd);

}

int RemoveOldString(const int fd, const int fileSize, const int RAMLimit, const int start, const int end)
{
    if ((start < 0) || (end < 0) || (start > end) || (end - 1 > fileSize)) {
        printf("Incorrect bounds.\n");
        return 0;
    }
    int diff = (fileSize == end - 1) ? 1 : fileSize - end;
    char *old = (char *) malloc(sizeof(char) * diff);
    if (old == NULL) {
        printf("malloc");
        exit(5);
    }
    int size = (RAMLimit > fileSize) ? fileSize : RAMLimit;
    int offset = 0, bytepos = 1, k = 0;
    char *addr;

    while (offset < fileSize) {
        addr = (char *) mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, fd, offset);
        if (addr == MAP_FAILED) {
            printf("mmap");
            exit(1);
        }

        for (int i = 0; i < size; ++i, ++bytepos) {
            if (bytepos >= end) {
                old[k] = addr[i];
                ++k;
            }
        }

        if (munmap(addr, size) == -1) {
            printf("munmap");
            exit(2);
        }

        offset += size;
    }

    int newFileSize = fileSize - end + start;
    if (ftruncate(fd, newFileSize)) {
        printf("ftruncate");
        exit(6);
    }

    bytepos = 1, offset = 0, k = 0;
    size = (RAMLimit > newFileSize) ? newFileSize : RAMLimit;

    while(offset < newFileSize) {
        addr = (char *)mmap(NULL, (size_t)size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);
        if (addr == MAP_FAILED) {
            printf("mmap");
            exit(1);
        }

        for (int i = 0; i < size; ++i, ++bytepos) {
            if (bytepos >= start) {
                addr[i] = old[k];
                ++k;
            }
        }

        if (msync(addr, size, MS_SYNC) == -1) {
            printf("msync");
            exit(7);
        }

        if (munmap(addr, size) == -1) {
            printf("munmap");
            exit(2);
        }

        offset += size;
    }

    free(old);
    return newFileSize;
}

void InsertNewString(const int fd, const int fileSize, const int RAMLimit, char const *string, const int start, const int end)
{
    if ((start < 0) || (end < 0) || (start > end)) {
        printf("Incorrect bounds.\n");
        return;
    }

    char *old = (char*) malloc(sizeof(char) * (fileSize - start));
    if (old == NULL) {
        printf("malloc");
        exit(5);
    }
    int size = (RAMLimit > fileSize) ? fileSize : RAMLimit;
    int offset = 0, bytepos = 1, k = 0;
    char *addr;

    while (offset < fileSize) {
        addr = (char *)mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, fd, offset);
        if (addr == MAP_FAILED) {
            printf("mmap");
            exit(1);
        }

        for (int i = 0; i < size; ++i, ++bytepos) {
            if (bytepos >= start) {
                old[k] = addr[i];
                ++k;
            }
        }

        if (munmap(addr, size) == -1) {
            printf("munmap");
            exit(2);
        }

        offset += size;
    }

    int newFileSize = fileSize + end - start;
    if (ftruncate(fd, newFileSize)) {
        printf("ftruncate");
        exit(6);
    }

    int l = 0;
    bytepos = 1, offset = 0, k = 0;
    size = (RAMLimit > newFileSize) ? newFileSize : RAMLimit;

    while (offset < newFileSize) {
        addr = (char *)mmap(NULL, (size_t)size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);
        if (addr == MAP_FAILED) {
            printf("mmap");
            exit(1);
        }

        for (int i = 0; i < size; ++i, ++bytepos) {
            if ((bytepos >= start) && (bytepos < end)) {
                addr[i] = string[l];
                ++l;
            }

            if (bytepos >= end) {
                addr[i] = old[k];
                ++k;
            }
        }

        if (msync(addr, size, MS_SYNC) == -1) {
            printf("msync");
            exit(7);
        }

        if (munmap(addr, size) == -1) {
            printf("munmap");
            exit(2);
        }

        offset += size;
    }

    free(old);
}

void ReplaceString(const int fd, const int fileSize,  const int RAMLimit, char const *oldString, const int sizeOldStr, char const *newString, const int sizeNewStr)
{
    int size = (RAMLimit > fileSize) ? fileSize : RAMLimit;
    int offset = 0, index = 0, bytepos = 1, start = 0, end = 0;
    char *addr;
    int found = 0;


    while (offset < fileSize) {
        addr = (char *)mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, fd, offset);
        if (addr == MAP_FAILED) {
            printf("mmap");
            exit(1);
        }

        for (int i = 0; i < size; ++i, ++bytepos) {
            if (addr[i] == oldString[index]) {
                ++index;
                for (int j = i + 1; (index < sizeOldStr) && (j < size); ++index, ++j) {
                    if (oldString[index] != addr[j] || addr[j] == '\n') {
                        index = 0;
                        break;
                    }
                }

                if (index == sizeOldStr) {
                    start = bytepos;
                    found = 1;
                    index = 0;
                    break;
                }
            }
        }
        if (munmap(addr, size) == -1) {
            printf("munmap");
            exit(2);
        }
        offset += size;
    }


    if (!found) {
        printf("This substring no entries in file.\n");
        return;
    }

    int newFileSize = RemoveOldString(fd, fileSize, RAMLimit, start, start + sizeOldStr);
    InsertNewString(fd, newFileSize, RAMLimit, newString, start, start + sizeNewStr);
}

void GetStringReplace(int fd, int size, char const* filename, char const* oldString, char const* newString)
{
    CheckFileSize(fd, filename);
    struct stat fileStat;
    FixSize(&size);
    fd = open(filename, O_RDWR);
    if (fd == -1) {
        printf("open\n");
        exit(3);
    }
    if (fstat(fd, &fileStat) == -1) {
        printf("fstat");
        exit(8);
    }
    ReplaceString(fd, fileStat.st_size, size, oldString, strlen(oldString), newString, strlen(newString));

    close(fd);

}

void Information(void)
{
    printf("\nThis programm is realized for working with files\n");
    printf("You can use this programm to let you know:\n");
    printf("* quantity of the strings and signs in your file\n");
    printf("* print the determined string\n");
    printf("* launch the searching for some string in your file\n");
    printf("* replace certain string in your file\n");
    printf("------------------------------------------------\n");
    printf(" This programm can work in two modes:\n");
    printf(" 1. Interactive mode\n");
    printf(" 2. Single command mode\n");
    printf("------------------------------------------------\n");
    printf("Instruction:\n");
    printf("For launching programm in Interactive Mode you need to launch in this way:\n");
    printf("./TextProcessor -'RAM LIMIT' \n");
    printf("In Single Command Mode you have the following functions\n");
    printf("1) Gain information about the file(quantity of the strings and signs):\n");
    printf("./TextProcessor 'FILENAME ' -'RAM LIMIT' -info \n");
    printf("./TextProcessor 'FILENAME ' -info\n");
    printf("2) Gain the certain string by number:\n");
    printf("./TextProcessor 'FILENAME ' -'RAM LIMIT' -print 'NUMBER OF STRING' \n");
    printf("./TextProcessor 'FILENAME ' -print 'NUMBER OF STRING' \n");
    printf("3) Replace string: \n");
    printf("./TextProcessor 'FILENAME ' -'RAM LIMIT' -replace 'STRING TO REPLACE' 'NEW STRING'\n");
    printf("./TextProcessor 'FILENAME ' -replace 'STRING TO REPLACE' 'NEW STRING'\n");
    printf("Warning: if you do not define 'RAM LIMIT', programm does it by itself\n");
}

void Menu(void) {
    printf("Menu:\n");
    printf("1) Input the new file\n");
    printf("2) Get information about the file \n");
    printf("3) Print string by number\n");
    printf("4) Replace the string in the file\n");
    printf("0) Exit \n");
}