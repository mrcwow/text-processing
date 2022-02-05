#include "treatment.h"

void countmin(struct Text* text){
    int sec = 0;
    wchar_t num[12]=L"0123456789\0";
    int added;
    int checkspace;
    for (int k = 0; k<text->amountsent; k++){
        for (int j = 1; j<text->textsent[k].lensent - 4; j++){
            if (wcschr(num, text->textsent[k].sent[j-1])!=NULL && text->textsent[k].sent[j]==L' ' && text->textsent[k].sent[j+1]==L's' && text->textsent[k].sent[j+2]==L'e'&& text->textsent[k].sent[j+3]==L'c' && text->textsent[k].sent[j+4]==L' ') {
                    added = 1;
                    checkspace = j;
                    for (int s = checkspace-1; s!=0; s--){
                        if (wcschr(num, text->textsent[k].sent[s]) != NULL) {
                            sec += added*((int)(text->textsent[k].sent[s])-(int)('0'));
                            added*=10;
                        }
                        if (s==L' ') break;
                    }
            }        
        }
    }
    float  min = (float)(sec) / 60;
    wprintf(L"Количество минут: %f\n", min);
}



int compare(const void* a, const void* b){
    return ((struct Sentence*)a)->wordsymsum > ((struct Sentence*)b)->wordsymsum;
}

void sortbyfirstword(struct Text* text){
    for (int k = 0; k<text->amountsent; k++){
        text->textsent[k].wordsymsum=0;
        for (int j = 0; ; j++){
            if (text->textsent[k].sent[j] != ' ' && text->textsent[k].sent[j] != ','){
                text->textsent[k].wordsymsum += (int)(text->textsent[k].sent[j]);
            }
            else break;
        }
    }
    qsort(text->textsent, text->amountsent, sizeof(Sentence), compare);
}



struct Sentence replacesym(struct Sentence* sent){
    struct Sentence newsent;
    newsent.lensent=0;
    int size=100;
    newsent.sent=calloc(size, sizeof(wchar_t));
    newsent.sent[0]=L'\0';
    for (int k = 0; k<sent->lensent; k++){
        if (sent->sent[k]!=L'@'&&sent->sent[k]!=L'%'&&sent->sent[k]!=L'#'){
            newsent.sent[newsent.lensent]=sent->sent[k];
            newsent.lensent++;
            if (newsent.lensent==size-10) {
                newsent.sent=realloc(newsent.sent, (size+100)*sizeof(wchar_t));
                size+=100;}
        }
        if (sent->sent[k]=='@'){
            newsent.sent = wcscat(newsent.sent, L"(at)");
            newsent.lensent+=4;
            if (newsent.lensent==size-10) {
                newsent.sent=realloc(newsent.sent, (size+100)*sizeof(wchar_t));
                size+=100;}
        }
        if (sent->sent[k]=='%'){
            newsent.sent = wcscat(newsent.sent, L"<persent>");
            newsent.lensent+=9;
            if (newsent.lensent==size-10) {
                newsent.sent=realloc(newsent.sent, (size+100)*sizeof(wchar_t));
                size+=100;}
        }
        if (sent->sent[k]=='#'){
            newsent.sent = wcscat(newsent.sent, L"<решетка>");
            newsent.lensent+=9;
            if (newsent.lensent==size-10) {
                newsent.sent=realloc(newsent.sent, (size+100)*sizeof(wchar_t));
                size+=100;}
        }
    }
    return newsent;
}
void replacetext(struct Text* text){
    for (int k = 0; k < text->amountsent; k++){
        text->textsent[k] = replacesym(&text->textsent[k]);
    }
}



void deletesentbylastword(struct Text* text){
    wchar_t cons[43]= L"bcdfghjklmnpqrstvwxzбвгджзйклмнпрстфхцчшщ\0";
    int numb=50;
    struct Text newtext;
    newtext.textsent = (struct Sentence*) calloc(numb, sizeof(Sentence));
    newtext.amountsent=0;
    int* check = calloc(text->amountsent, sizeof(int));
    int checknum;
    for (int k=0; k<text->amountsent; k++){
        checknum = 0;
        for (int j=text->textsent[k].lensent-1; j>1; j--){
            if (text->textsent[k].sent[j] == L' '||text->textsent[k].sent[j] == L',') break;
            if (wcschr(cons, towlower(text->textsent[k].sent[j])) != NULL && wcschr(cons, towlower(text->textsent[k].sent[j-1]))!= NULL && wcschr(cons, towlower(text->textsent[k].sent[j-2]))!= NULL) { 
                checknum = 1;
                break;
            }  
        }
        check[k] = checknum;
    }
    for (int k=0; k < text->amountsent; k++){
        if (check[k]==0){
            newtext.textsent[newtext.amountsent]=text->textsent[k];
            newtext.amountsent++;
            if (newtext.amountsent==numb-5) {
                newtext.textsent=realloc(newtext.textsent, (numb+30)*sizeof(wchar_t));
                numb+=30;
            }
        }
    }
    *text = newtext;
}