/* jdl34 C-subset SDK: standard stdio shim.
 *
 * The built-in compiler only supports the preprocessor forms listed in the
 * manifest (corecvrt): #include, object-like #define, #ifdef/#ifndef/#else/
 * #endif, #pragma once, and simple declarations of the C99 subset. Function
 * prototypes are not required: calls to CRT functions (printf, malloc, ...)
 * are resolved automatically against msvcrt.dll by the environmental linker.
 */
#ifndef STDIO_H
#define STDIO_H

#define NULL ((void*)0)
#define EOF (-1)

#define stdout ((void*)1)
#define stderr ((void*)2)
#define stdin ((void*)3)

#endif /* STDIO_H */