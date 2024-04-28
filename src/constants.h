#ifndef _CONSTANTS_
#define _CONSTANTS_

#define MAX_CHAR 256
extern int DEBUG;

typedef enum Type
{
    FILE_TYPE,
    FOLDER_TYPE,
    BOTH_TYPE,
    NONE_TYPE
} Type;

typedef enum Action
{
    COMPRESS,
    DECOMPRESS,
    NOTHING
} Action;

#endif
