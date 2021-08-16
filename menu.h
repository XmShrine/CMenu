#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include "coord.h"

#define ALL_CLOSE           0
#define ALL_BOLD            1
#define ALL_LOW             2
#define ALL_INTALIC         3
#define ALL_UNDERLINE       4
#define ALL_BLINK           5
#define ALL_INVERT          7
#define COLOR_BLACK         30
#define COLOR_RED           31
#define COLOR_GREEN         32
#define COLOR_YELLOW        33
#define COLOR_BLUE          34
#define COLOR_PURPLE        35
#define COLOR_DGREEN        36
#define COLOR_WHITE         37
#define OPEN_UNDERLINE      38
#define CLOSE_UNDERLINE     39
#define BACK_BLACK          40
#define BACK_DRED           41
#define BACK_GREEN          42
#define BACK_YELLOW         43
#define BACK_BLUE           44
#define BACK_PURPLE         45
#define BACK_DGREEN         46
#define BACK_WHITE          47

struct _position_;

typedef struct _position_ position;

struct _position_ {
    long begx;   // start from 1
    long begy;   // start from 1
    long sizx;   // start from 1
    long sizy;   // start from 1
};

struct _menu_;

struct _menu_tool_;

typedef struct _menu_ menu;

typedef struct _menu_tool_ menuTool;

struct _menu_ {
    coord*      list;
    char*       title;
    char*       symbol;
    menuTool*   tool;
    position*   posi;
};

struct _menu_tool_ {
    long         dt_entr;
    long         dt_spac;
    long         li_llst;
    long         is_num;
    long         is_safe;
};

void* CutString(char* beg, unsigned long len);

void* PrintError(void);

void* Menu(coord* list, char* title, char* symbol, long sizx);

void* MenuSetList(menu* men, coord* list);

void* MenuSetPosition(menu* men, long begx, long begy, long sizx, long sizy);

void* MenuSetSymbol(menu* men, char* symbol);

void* MenuSetTitle(menu* men, char* title);

struct winsize MenuWinSize(void);

void* MenuMove(long x, long y); // Start With 1

void* MenuColor(long c); // Special Word

void* MenuRun(menu* men);

void* MenuLClear(int r);

void* MenuCClear(void);

void* MenuSClear(void);