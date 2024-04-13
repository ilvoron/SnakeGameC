#include <stdio.h>
#include <stdbool.h>
#include "test__close_interface.h"
#include "interface.h"
#include "output.h"

// private

void _TestCloseInterface1() {
	PrintSTATUS(false, false, "[close_interface]");
	printf(" Test 1. Calling function... ");
	close_interface();
	PrintOK(false, true);
}

// public

void TestCloseInterface() {
	printf("Testing ");
	PrintSTATUS(false, false, "close_interface()");
	printf("...\n");
	
	_TestCloseInterface1();
	
	printf("Testing ");
	PrintSTATUS(false, false, "close_interface()");
	printf("... ");
	PrintOK(false, true);	
};