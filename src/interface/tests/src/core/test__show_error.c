#include <stdio.h>
#include "test__show_error.h"
#include "global.h"
#include "output.h"
#include "interface.h"
#include "tools.h"
#include "consts.h"

// private

bool _hasTestShowErrorBad = false;

void _GenerateError(enum ERROR_CODE errCode, struct Settings* Settings) {
	freopen(TEMP_FILE_ERR, "w", stdout);
	printf(Settings->skin.errorCodeLabels[errCode]);
	freopen(DEFAULT_OUT, "a", stdout);
}

void _TestShowError1(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_error]");
	printf(" Test 1. Testing errors... ");
	
	int testedErrors = 0;
	for (int i = 0; i < ERR__COUNT; i++) {
		PrintSTATUS(true, false, "[show_error]");
		printf(" Test 1.%d. Testing error \"%s\"... ", i + 1, Settings->skin.errorCodeLabels[i]);
		_GenerateError(i, Settings);
		freopen(TEMP_FILE, "w", stdout);
		show_error(i);
		freopen(DEFAULT_OUT, "a", stdout);
		if (CompareFiles(TEMP_FILE, TEMP_FILE_ERR)) { PrintOK(false, false); }
		else { PrintBAD(false, false); _hasTestShowErrorBad = true; }
		testedErrors++;
	}

	if (testedErrors == 0) {
		PrintOK(false, true);
	} else {
		PrintSTATUS(true, false, "[show_error]");
		printf(" Test 1. Testing errors... ");
		PrintOK(false, true);
	}
}

// public

bool TestShowError(struct Settings* Settings) {
	printf("Testing ");
	PrintSTATUS(false, false, "show_error()");
	printf("...\n");
	
	_TestShowError1(Settings);
	
	printf("Testing ");
	PrintSTATUS(false, false, "show_error()");
	printf("... ");
	if (_hasTestShowErrorBad) { PrintBAD(false, true); }
	else { PrintOK(false, true); }
	return _hasTestShowErrorBad;
};