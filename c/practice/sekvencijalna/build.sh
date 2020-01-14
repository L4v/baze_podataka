#! /bin/bash
CompilerFlags=(	-Wall -Werror -Wl,-rpath,'$ORIGIN'
		-Wno-unused-function -Wno-write-strings -Wno-unused-variable -g -Wno-null-dereference
		-Wno-unused-but-set-variable -Wno-implicit-function-declaration)
gcc ${CompilerFlags[*]} -std=c99 -o  main main.c
