#include <stdlib.h>
#include <string.h>
#include "consts.h"

// public

const char TEMP_PATH[] = "temp";
const char TEMP_FILE[] = "temp/_out.tmp";
const char TEMP_FILE_SM_0[] = "temp/_out_sm0.tmp";
const char TEMP_FILE_SM_1[] = "temp/_out_sm1.tmp";
const char TEMP_FILE_SM_2[] = "temp/_out_sm2.tmp";
const char TEMP_FILE_SPEED[] = "temp/_out_speed.tmp";
const char TEMP_FILE_MAP[] = "temp/_out_map.tmp";
const char TEMP_FILE_EG_WIN[] = "temp/_out_egWin.tmp";
const char TEMP_FILE_EG_LOSE[] = "temp/_out_egLose.tmp";
const char TEMP_FILE_ERR[] = "temp/_out_err.tmp";
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