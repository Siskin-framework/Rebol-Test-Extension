REBOL [
	title: "Test module builder"
	type: module
]

cmd-words: []
arg-words: []

commands: [
	init-words: [cmd-words [block!] arg-words [block!]]
	;--------------------------

	info: [
		{Returns info about Test extension library}
		/of handle [handle!] {Test Extension handle}
	]
	new: [{Creates a new test context}]

	;--------------------------
]


header: {REBOL [Title: {Rebol Test Extension} Type: module Exports: []]}
enum-commands:  {enum tst_commands ^{}
enum-cmd-words: {enum tst_cmd_words ^{W_TST_CMD_0,}
enum-arg-words: {enum tst_arg_words ^{W_TST_ARG_0,}

foreach word cmd-words [
	word: uppercase form word
	replace/all word #"-" #"_"
	append enum-cmd-words ajoin ["^/^-W_TST_CMD_" word #","]
]
foreach word arg-words [
	word: uppercase form word
	replace/all word #"-" #"_"
	append enum-arg-words ajoin ["^/^-W_TST_ARG_" word #","]
]

foreach [name spec] commands [
	append header ajoin [lf name ": command "]
	new-line/all spec false
	append/only header mold spec

	name: uppercase form name
	replace/all name #"-" #"_"
	append enum-commands ajoin ["^/^-CMD_TST_" name #","]
]

new-line/all cmd-words false
new-line/all arg-words false
append header rejoin [{^/init-words words: } mold cmd-words #" " mold arg-words]
append header {^/protect/hide 'init-words}

;print header

out: make string! 2000
append out {// auto-generated file, do not modify! //

#include "test-command.h"

#define MIN_REBOL_VER 3
#define MIN_REBOL_REV 5
#define MIN_REBOL_UPD 4
#define VERSION(a, b, c) (a << 16) + (b << 8) + c
#define MIN_REBOL_VERSION VERSION(MIN_REBOL_VER, MIN_REBOL_REV, MIN_REBOL_UPD)
}
append out join enum-commands "^/};^/"
append out join enum-cmd-words "^/};^/"
append out join enum-arg-words "^/};^/"
append out {^/#define TST_EXT_INIT_CODE \}


foreach line split header lf [
	replace/all line #"^"" {\"}
	append out ajoin [{^/^-"} line {\n"\}] 
]
append out "^/"


;print out

write %test-rebol-extension.h out
