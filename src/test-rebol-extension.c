//
// test Rebol extension
// ====================================
// Use on your own risc!

#include "test-rebol-extension.h"

RL_LIB *RL; // Link back to reb-lib from embedded extensions

//==== Globals ===============================//
u32*   tst_cmd_words;
u32*   tst_arg_words;
REBCNT Handle_TestExtensionCtx;

REBDEC doubles[DOUBLE_BUFFER_SIZE];
RXIARG arg[ARG_BUFFER_SIZE];
//============================================//

static const char* init_block = TST_EXT_INIT_CODE;


void* releaseTestExtensionCtx(void* ctx) {
	debug_print("releasing test extension context: %p\n", ctx);
	return NULL;
}


RXIEXT const char *RX_Init(int opts, RL_LIB *lib) {
    RL = lib;
	REBYTE ver[8];
	RL_VERSION(ver);
	debug_print("RXinit test-extension; Rebol v%i.%i.%i\n", ver[1], ver[2], ver[3]);

	if (MIN_REBOL_VERSION > VERSION(ver[1], ver[2], ver[3])) {
		debug_print("Needs at least Rebol v%i.%i.%i!\n", MIN_REBOL_VER, MIN_REBOL_REV, MIN_REBOL_UPD);
		return 0;
	}
    if (!CHECK_STRUCT_ALIGN) {
    	trace("CHECK_STRUCT_ALIGN failed!");
    	return 0;
    }
	Handle_TestExtensionCtx = RL_REGISTER_HANDLE((REBYTE*)"TestExtensionCtx", sizeof(TST_CONTEXT), releaseTestExtensionCtx);
    return init_block;
}


RXIEXT int RX_Call(int cmd, RXIFRM *frm, void *ctx) {
	switch (cmd) {
	case CMD_TST_INFO:
		tst_info(frm, ctx);
		return RXR_VALUE;

	case CMD_TST_NEW:
		tst_new(frm, ctx);
		return RXR_VALUE;

	case CMD_TST_INIT_WORDS:
		tst_cmd_words = RL_MAP_WORDS(RXA_SERIES(frm,1));
		tst_arg_words = RL_MAP_WORDS(RXA_SERIES(frm,2));
		goto done;
	} // end of commands

	if (ctx == NULL) {
		return RXR_ERROR;
	}

done:
    return RXR_NONE;
}

RXIEXT int RX_Quit(int opts) {
    return 0;
}
