//
// Test Rebol extension
// ====================================
// Use on your own risc!

#include "test-rebol-extension.h"

REBCHR *get_exec_path() {

	REBCHR *exec_path = NULL;
#ifdef TO_OSX
	REBCNT  exec_path_size = 0;
	_NSGetExecutablePath(NULL, &exec_path_size);
	if( exec_path_size > 0 ) {
		exec_path = malloc(exec_path_size);
		if (exec_path) {
			_NSGetExecutablePath(exec_path, &exec_path_size);
		}
	}
#elif TO_LINUX
	exec_path = malloc(PATH_MAX);
	CLEAR(exec_path, PATH_MAX); // readlink does not null terminate!
	if (readlink("/proc/self/exe", exec_path, PATH_MAX-1) == -1) {
		free(exec_path);
		exec_path = NULL;
	}
#elif TO_WINDOWS
	exec_path = malloc(MAX_FILE_NAME);
	if(!GetModuleFileName(0, *name, MAX_FILE_NAME)){
		free(exec_path);
		exec_path = NULL;
	}
#endif
	return exec_path;
} 

void tst_info(RXIFRM* frm, void* reb_ctx) {
	// return library info...
	REBI64  tail = 0;
	REBSER *str  = RL_MAKE_STRING(1000, FALSE); // 1024 bytes, latin1 (must be large enough!)
	REBCHR *exec_path = NULL;
	REBYTE rebol_version[8];


	if (RXT_HANDLE == RXA_TYPE(frm, 2)) {
		// Info about given handle...
		REBHOB* hob = RXA_HANDLE(frm, 2);

		if (hob->sym == Handle_TestExtensionCtx) {
			TST_CONTEXT* ctx = (TST_CONTEXT*)hob->data;
			tail = snprintf(
				SERIES_TEXT(str),
				SERIES_REST(str),
				"TestExtensionCtxPtr: <%p>\n"
				"TestExtensionCtxId:  %u\n",
				(void*)ctx,
				ctx->id
			);
		}
		else {
			// unsupported handle
		}
	}
	else {
		// Some system info...
		RL_VERSION(rebol_version);

		exec_path = get_exec_path();

		tail = snprintf(
			SERIES_TEXT(str),
			SERIES_REST(str),
			"ExtVersion:  %u.%u.%u\n"
			"RebVersion:  %u.%u.%u\n"
			"Executable:  %s\n",
			MIN_REBOL_VER, MIN_REBOL_REV, MIN_REBOL_UPD,
			rebol_version[1], rebol_version[2], rebol_version[3],
			(REBCHR*)(exec_path ? exec_path : "none")
		);
	}
	if (tail < 0) {
		RXA_TYPE(frm, 1) = RXT_NONE;
	}
	else {
		SERIES_TAIL(str) = tail;
		RXA_SERIES(frm, 1) = str;
		RXA_TYPE(frm, 1) = RXT_STRING;
		RXA_INDEX(frm, 1) = 0;
	}
	if (exec_path) free(exec_path);
}
