#ifndef HEAD
#define HEAD
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
struct Sentence{
    int lensent;
    wchar_t* sent;
    int wordsymsum;
}Sentence;
struct Text{
    int amountsent;
    struct Sentence* textsent;
}Text;
#endif