#include <stdlib.h>
#include <string.h>
#include "consts.h"

// public

const char TEMP_PATH[] = "tmp";
const char TEMP_FILE[] = "tmp/_out.tmp";
const char TEMP_FILE_SM_0[] = "tmp/_out_sm0.tmp";
const char TEMP_FILE_SM_1[] = "tmp/_out_sm1.tmp";
const char TEMP_FILE_SM_2[] = "tmp/_out_sm2.tmp";
const char TEMP_FILE_SM_3[] = "tmp/_out_sm3.tmp";
const char TEMP_FILE_SPEED[] = "tmp/_out_speed.tmp";
const char TEMP_FILE_RT[] = "tmp/_out_rt.tmp";
const char TEMP_FILE_MAP[] = "tmp/_out_map.tmp";
const char TEMP_FILE_EG_WIN[] = "tmp/_out_egWin.tmp";
const char TEMP_FILE_EG_LOSE[] = "tmp/_out_egLose.tmp";
const char TEMP_FILE_ERR[] = "tmp/_out_err.tmp";
const char DEFAULT_OUT[] = "CON";

char* Concat(const char* str1, const char* str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    size_t len_total = len1 + len2;
    char *result = (char *)malloc((len_total + 1) * sizeof(char));
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}