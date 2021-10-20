// auto-generated file, do not modify! //

#include "test-command.h"

#define MIN_REBOL_VER 3
#define MIN_REBOL_REV 5
#define MIN_REBOL_UPD 4
#define VERSION(a, b, c) (a << 16) + (b << 8) + c
#define MIN_REBOL_VERSION VERSION(MIN_REBOL_VER, MIN_REBOL_REV, MIN_REBOL_UPD)
enum tst_commands {
	CMD_TST_INIT_WORDS,
	CMD_TST_INFO,
	CMD_TST_NEW,
};
enum tst_cmd_words {W_TST_CMD_0,
};
enum tst_arg_words {W_TST_ARG_0,
};

#define TST_EXT_INIT_CODE \
	"REBOL [Title: {Rebol Test Extension} Type: module Exports: []]\n"\
	"init-words: command [cmd-words [block!] arg-words [block!]]\n"\
	"info: command [\"Returns info about Test extension library\" /of handle [handle!] \"Test Extension handle\"]\n"\
	"new: command [\"Creates a new test context\"]\n"\
	"init-words words: [] []\n"\
	"protect/hide 'init-words\n"\
