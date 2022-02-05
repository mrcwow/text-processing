#include "getputtext.h"


int getsent(struct Sentence* sent){
    sent->lensent=0;
    int size=100;
    wchar_t check=getwchar();
    sent->sent=calloc(size, sizeof(wchar_t));
    if (check!=L' ') {
        sent->sent[sent->lensent]=check;
        sent->lensent++;}
    wchar_t c;
    while((c=getwchar())!=L'.'){
        if (check==L' ' && c==L' ') return 0;
        check = L'o'; 
        sent->sent[sent->lensent]=c; 
        sent->lensent++;
        if (sent->lensent==size-5){
            sent->sent = realloc(sent->sent, (size+100)* sizeof(wchar_t));
            size=size+100;
        } 
    }
        sent->sent[sent->lensent]=L'.';
        sent->lensent++;
        sent->sent[sent->lensent]=L'\0';
        return 1;
}



void gettext(struct Text* text){
    int numb=50;
    text->textsent = (struct Sentence*) calloc(numb, sizeof(Sentence));
    text->amountsent=0;
    struct Sentence newsent;
    int check=0;
    int checksent;
    int same=0;
    while (getsent(&newsent)){
        for (int k = 0; k<text->amountsent; k++){
            for (int s = 0; s < text->textsent[k].lensent; s++){
                if(towlower(text->textsent[k].sent[s])==towlower(newsent.sent[s])){
                    same++;
                }
                else {break;}
                if (same==text->textsent[k].lensent) check++;
            }
        if (check>0) break;
        same = 0;
        }
        same=0;
        checksent =check;
        check = 0;
        if (checksent==0){
            text->textsent[text->amountsent]=newsent;
            text->amountsent++;
            if (text->amountsent==numb-5){
                text->textsent = realloc(text->textsent, (numb+30) * sizeof(Sentence));
                numb=numb+30;  
            } 
        }
    }
}



void printtext(struct Text* text){
    for (int k = 0; k<text->amountsent; k++){
       for (int j=0; j<text->textsent[k].lensent; j++){
            wprintf(L"%lc", text->textsent[k].sent[j]);
        }
        wprintf(L"\n"); 
}
}
