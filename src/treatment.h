#include "main.h"
void countmin(struct Text* text);

int compare(const void* a, const void* b);
void sortbyfirstword(struct Text* text);

struct Sentence replacesym(struct Sentence* sent);
void replacetext(struct Text* text);

void deletesentbylastword(struct Text* text);