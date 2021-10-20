//
// Test Rebol extension
// ====================================
// Use on your own risc!

#include "test-rebol-extension.h"

void tst_new(RXIFRM* frm, void* reb_ctx) {
	// creates a structure as a test context

	REBHOB* hob = RL_MAKE_HANDLE_CONTEXT(Handle_TestExtensionCtx);
	if (hob == NULL) goto error;
	
	RXA_HANDLE(frm, 1) = hob;
	RXA_HANDLE_TYPE(frm, 1) = hob->sym;
	RXA_HANDLE_FLAGS(frm, 1) = hob->flags;
	RXA_TYPE(frm, 1) = RXT_HANDLE;

	return;
error:
	debug_print("Failed to create a context!\n", NULL);
	RXA_TYPE(frm, 1) = RXT_NONE;
}