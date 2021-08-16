#include "menu.h"

void* CutString(char* beg, unsigned long len) {
    if (strlen(beg)>len) {
        return DeepCopy(beg, len);
    }
    return DeepCopy(beg, strlen(beg));
}

void* PrintError(void) {
    MenuColor(ALL_CLOSE);
    MenuColor(COLOR_RED);
    MenuColor(ALL_BOLD);
    printf("Error ");
    MenuColor(ALL_CLOSE);
    return 0;
}

void* Menu(coord* list, char* title, char* symbol, long sizx) {
    menu* men = malloc(sizeof(menu));
    men->list = NULL;
    men->tool = malloc(sizeof(menuTool));
    men->title = title;
    men->symbol = NULL;
    men->posi = NULL;
    MenuSetList(men, list);
    MenuSetPosition(men, 1, 1, sizx, 0);
    MenuSetSymbol(men, symbol);
    men->tool->is_num = 1;
    men->tool->is_safe = 1;
    return men;
}

void* MenuSetList(menu* men, coord* list) {
    if (men->list == NULL) {
        men->list = malloc(sizeof(coord));
    }
    if (men->posi==NULL) {
        men->posi = malloc(sizeof(position));
    }
    if (men->tool==NULL) {
        men->tool = malloc(sizeof(menuTool));
    }
    *men->list = *list;
    return 0;
}

void* MenuSetPosition(menu* men, long begx, long begy, long sizx, long sizy) {
    if (men==NULL) {
        return 0;
    }
    if (men->posi==NULL) {
        men->posi = malloc(sizeof(position));
    }
    if (men->posi==NULL) {
        men->posi = malloc(sizeof(position));
    }
    if (men->tool==NULL) {
        men->tool = malloc(sizeof(menuTool));
    }
    if (begx==0 || begy==0) {
        begx = begy = 1;
    }
    position cins = {begx, begy, sizx, sizy};
    *men->posi = cins;
    if (men->list!=NULL) {
        unsigned long llist = 0, lspac = 0;
        for (unsigned long i=0; i<(unsigned long)CoordLength(men->list); i++) {
            if (llist<strlen(*(char**)CoordArrget(men->list, i))) {
                llist = strlen(*(char**)CoordArrget(men->list, i));
            }
        }
        men->tool->li_llst = llist;
        if (men->posi->sizx>0) {
            for (unsigned long i=0; i<(unsigned long)men->posi->sizx; i++, lspac++) {
                if (2*i+llist>men->posi->sizx) {
                    break;
                }
            }
            men->tool->dt_spac = lspac;
        } else {
            men->tool->dt_spac = lspac = -men->posi->sizx;
        }
        men->tool->dt_entr = lspac/2;
    }
    return 0;
}

void* MenuSetSymbol(menu* men, char* symbol) {
    if (men==NULL) {
        return 0;
    }
    men->symbol = symbol;
    return 0;
}

void* MenuSetTitle(menu* men, char* title) {
    if (men==NULL) {
        return 0;
    }
    men->title = title;
    return 0;
}

struct winsize MenuWinSize(void) {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size;
}

void* MenuMove(long x, long y) {
    if (x>0 && y>0) {
        printf("\e[%ld;%ldH", y, x);
    }
    if (x<0 && y<0) {
        printf("\e[%ld;%ldH", MenuWinSize().ws_row+y, MenuWinSize().ws_col+x);
    }
    
    return 0;
}

void* MenuColor(long c) {
    printf("\e[%ldm", c);
    return 0;
}

void* MenuError(void) {
    MenuCClear();
    PrintError();
    printf("The Menu List Is Too High For The Screen\n");
    printf("Help Data:\n");
    printf("Screen COL: %d\n", MenuWinSize().ws_col);
    printf("Screen ROW: %d\n", MenuWinSize().ws_row);
    exit(0);
    return 0;
}

void* MenuRun(menu* men) {
    void* (*clearFunction)(void);
    if (men->tool->is_safe) {
        clearFunction = MenuCClear;
    } else {
        clearFunction = MenuSClear;
    }
    unsigned long sizx = 0;
    const unsigned long begx = men->posi->begx;
    unsigned long begy = men->posi->begy;
    const unsigned long nm_space = men->tool->dt_spac;
    const unsigned long nm_enter = men->tool->dt_entr;
    if (men->posi->sizx>0) {
        sizx = men->posi->sizx;
    }
    if (men->posi->sizx<0) {
        sizx = -(men->posi->sizx*2)+men->tool->li_llst;
    }
    if ((long)(sizx+begx)>(long)MenuWinSize().ws_col || (long)(2+2*nm_enter+CoordLength(men->list)+begx)>(long)MenuWinSize().ws_row) {
        MenuError();
    }
    clearFunction();
    MenuColor(ALL_BOLD);
    MenuMove(begx, begy);
    if (men->title!=NULL) {
        printf("%s", men->title);
        MenuMove(begx, ++begy);
    }
    for (long i=0; i<sizx; i++) printf("%s", men->symbol);
    for (long i=0; i<nm_enter; i++) MenuMove(begx, ++begy);
    for (long i=0; i<(long)CoordLength(men->list); i++) {
        MenuMove(begx+nm_space, ++begy);
        printf("%s", *(char**)CoordArrget(men->list, i));
        if (men->tool->is_num) {
            MenuMove(begx+sizx, begy);
            MenuColor(ALL_LOW);
            printf("[%ld", i+1);
            MenuColor(ALL_CLOSE);
            MenuColor(ALL_BOLD);
        }
    }
    for (long i=0; i<nm_enter+1; i++) MenuMove(begx, ++begy);
    for (long i=0; i<sizx; i++) printf("%s", men->symbol);
    MenuMove(begx, ++begy);
    MenuColor(ALL_CLOSE);
    return 0;
}

void* MenuLClear(int r) {
    MenuColor(ALL_CLOSE);
    if (r) {
        printf("\r");
    }
    printf("\e[K");
    return 0;
}

void* MenuCClear(void) {
    MenuColor(ALL_CLOSE);
    printf("\e[2J");
    MenuMove(1, 1);
    return 0;
}

void* MenuSClear(void) {
    MenuColor(ALL_CLOSE);
    for (long i=0; i<MenuWinSize().ws_row; i++) {
        MenuMove(1, i+1);
        MenuLClear(1);
    }
    MenuMove(1, 1);
    return 0;
}