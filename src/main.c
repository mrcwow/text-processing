#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include "getputtext.h"
#include "treatment.h"
#include "main.h"

int main(){
    setlocale(LC_ALL, "");
    struct Text text;
    gettext(&text);
    wprintf(L"Вывод разных предложений:\n");
    printtext(&text);
    wprintf(L"Введите кодовое значение от 1 до 4 (для выхода нажмите 5):\n");
    wchar_t codevalue;
    while(1){
    codevalue = getwchar();
    switch (codevalue){
        case L'1':
            wprintf(L"Результат кодового значения - 1:\n");
            countmin(&text);
            wprintf(L"Введите кодовое значение от 1 до 4 (для выхода нажмите 5):\n");
            break;
        case L'2':
            wprintf(L"Результат кодового значения - 2:\n");
            sortbyfirstword(&text);
            printtext(&text);
            wprintf(L"Введите кодовое значение от 1 до 4 (для выхода нажмите 5):\n");
            break;
        case L'3':
            wprintf(L"Результат кодового значения - 3:\n");
            replacetext(&text);
            printtext(&text);
            wprintf(L"Введите кодовое значение от 1 до 4 (для выхода нажмите 5):\n");
            break;
        case L'4':
            wprintf(L"Результат кодового значения - 4:\n");
            deletesentbylastword(&text);
            printtext(&text);
            wprintf(L"Введите кодовое значение от 1 до 4 (для выхода нажмите 5):\n");
            break;
        case L'5':
            wprintf(L"Выход из программы.\n");
            for (int i=0; i<text.amountsent; i++){
                free(text.textsent[i].sent);
            }
            free(text.textsent);
            return 0;
        case L'\n':
            break;
        default:
            wprintf(L"Вы ввели неверное кодовое значение. Введите кодовое значение от 1 до 4 (для выхода нажмите 5):\n");
        }
    }
    return 0;
}
    