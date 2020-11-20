#ifndef __MINESWEEPER_H__
#define __MINESWEEPER_H__

#include "MineMap.h"
#include "DirectoryManager.h"
#include <cstring>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <termios.h>
#include <sys/time.h>
#include <unistd.h>
#include <vector>
#include <algorithm>

using namespace std;

#define SAVEFILE "save.mss"
#define SAVEMODE 0644

#define RANKFILE "rank.msr"
#define RANKFLAG (O_CREAT|O_RDWR|O_APPEND)
#define RANKMODE 0644

#define ARROW 27
#define UP 65
#define DOWN 66
#define LEFT 68
#define RIGHT 67
#define ENTER 10
#define SPACE 32
#define TAB 9
#define TILDE 96
#define ESCAPE 127

#define CHAR_MINE '*'
#define CHAR_FLAG '?'
#define CHAR_DEFAULT '+'
#define CHAR_ZERO '.'

#define MESSAGE_START "게임시작"
#define MESSAGE_LOAD "이어하기"
#define MESSAGE_RANK "랭킹"
#define MESSAGE_EXIT "게임종료"

#define MESSAGE_EASY "쉬움"
#define MESSAGE_NORMAL "보통"
#define MESSAGE_HARD "어려움"

#define MENU_LOGO_POSITION 3
#define MENU_MARGIN_SIZE 3
#define MENU_MODE_MARGIN_SIZE 5
#define MENU_DEFAULT_POSITION 5
#define MENU_MESSAGE_POSITION 7
#define MENU_MESSAGE_POSITION_X (MENU_MESSAGE_POSITION * 2 + MENU_MARGIN_SIZE)
#define TERMINAL_MESSAGE_SIZE 20
#define TERMINAL_RANK_SIZE (userNameMaxLength + 62 + MENU_MESSAGE_POSITION*2)

#define COLOR_BLACK 0
#define COLOR_RED 1
#define COLOR_GREEN 2
#define COLOR_BROWN 3
#define COLOR_BLUE 4
#define COLOR_MAGENTA 5
#define COLOR_CYAN 6
#define COLOR_WHITE 7
#define COLOR_DEFAULT 9

class MineSweeper {
  public:
    static const int MAP_SPAN_SIZE_Y = 3;
    static const int MAP_SPAN_SIZE_X = (MAP_SPAN_SIZE_Y - 1) * 2;
    static const int MAP_SIZE_MIN = 2;
    static const int MAP_SIZE_MAX = 30;
    static const int MAP_SIZE_EASY = 10;
    static const int MAP_SIZE_NORMAL = 20;
    static const int MAP_SIZE_HARD = 30;
    static const int MINE_PERCENT_EASY = 10;
    static const int MINE_PERCENT_NORMAL = 12;
    static const int MINE_PERCENT_HARD = 15;

    static const int RANK_PRINT_SIZE = 15;

    enum Difficulty { Easy, Normal, Hard };
    enum Type { None, Number, Mine, Flag, Open };
    enum Menu { Start, Load, Ranking, Exit };
    enum State { Menu, ModeSelect, LoadState, Rank, Game, ExitState };

    struct MineSweeperInfo {
        struct timeval time;
        int flagCount;  // Set Flag Count
        int clickCount; // Click Count
        int roundCount;
        int openCount;
    };

    struct RankInfo {
        uid_t uid;
        Difficulty diff;
        struct timeval time;
        int flagCount;
        int clickCount;
        int roundCount;
    };

    // X and Y
    struct Coordinate {
        int x;
        int y;
    };

  public:
    MineSweeper();

    void StartMineSweeper(); // Main Function

  private:
    void CreateMap(); // Create Map
    void CheckGameClear();

    // Menu
    void MenuControl();    // Get Input Keys and UI Movement
    void ModeControl();    // Get Input Keys and UI Movement
    void RankingControl(); // Get Input Keys and UI Movement

    void PrintLogo(); // Print Game Logo
    void PrintMenuMessage(enum Menu menuState, bool isJustPrint = false);
    void PrintMenu(bool printAll = false); // Print Menu UI
    void PrintModeMessage(enum Difficulty modeState, bool isJustPrint = false);
    void PrintMode(bool printAll = false);    // Print Mode Select UI
    void PrintRanking(Difficulty diff);       // Print Ranking UI
    void PrintMenuKeyInfo();

    // Rank
    void SaveRank();
    void LoadRank();
    void ResetRankInfo();
    vector<struct MineSweeper::RankInfo> &GetRankInfo(enum Difficulty diff);

    // Game
    void StartGame(); // Start Mine Sweeper Game
    void SaveGame();
    void LoadGame();
    void DeleteSave();

    void PrintMap(bool printAll = false); // Print Mine Sweeper Map
    void PrintInfo(bool isUpdate = true); // Print Infomation
    void PrintGameOver();                 // Print Game Over Message
    void PrintGameClear();                // Print Game Clear Message
    void PrintGameKeyInfo();

    // Initialize
    void Init(); // Initialize for start Game
    void InitInfo();

    // Timer
    void StartTimer(bool isGameLoaded);
    void StopTimer();
    double GetTime(struct timeval time);

    // Map
    MineMap &GetMap();           // Get Map Variable
    int &GetData(int x, int y);  // Get Map Element's Data
    int &GetData(Coordinate c);  // Get Map Element's Data
    Type GetType(int x, int y);  // Get Map Element's Type
    Type GetType(int data);      // Get Map Element's Type
    bool IsOpened(int x, int y); // Get Element are Opened
    bool IsOpened(int data);     // Get Element are Opened

    void MoveCursor(int x, int y); // Move Terminal Cursor
    void SetCursor();              // Update Cursor & Highlighting Cursor

    void HighlightColor(Coordinate hlPos, bool isHighlight, bool isHighlightAll = false); // Highlighting coordinate's Element
    void HighlightRound(Coordinate hlPos, bool isHighlight); // Highlighting coordinate's Element around

    void SetClick(); // Click Element like mouse click (Current coordinate)
    void SetClick(Coordinate clickPos, bool isCursorMove = false, bool isFindZero = false); // Click Element like mouse click (clickPos's coordinate)
    void SetFlag();                         // Set Flag to Element
    void SetRound(bool isOnlyHighlight = true); // Set Round to Element
    void CheckRound();

    void FindZero(Coordinate findPos); // Find Zero around 'findPos'
    void OpenAllMine();

    // Color
    void SetForegroundColor(int color);
    void SetBackgroundColor(int color);
    void SetMenuColor(enum Menu menuState);
    void SetModeColor(enum Difficulty modeState);
    void ResetColor();

    // terminal
    void SetTerminalSize(int row, int col);
    void SetTerminalSize_Menu();
    void SetTerminalSize_Game();
    void SetTerminalSize_Rank();
    int GetKey(); // Get Key

    void Terminal_Init(bool isStart);
    void Terminal_SaveNLoad(bool isSave);

    void Terminal_SetScrollHide(bool hide);
    void Terminal_SetCursorHide(bool hide); // Set Cursor Visible/Unvisible

    void Terminal_Scroll();
    void terminal_clear();
    void terminal_scroll_up();

    void clear();              // Clear Terminal text
    void gotoxy(int x, int y); // Set Cursor Move to x, y
    void gotoup(int count = 1);
    void gotodown(int count = 1);
    void gotoleft(int count = 1);
    void gotoright(int count = 1);

    void gotoMenu(State state, int index = 0, int move_x = 0); // Set Cursor To Stated Position


  private:
    MineMap map;
    MineSweeperInfo info;
    int totalMapSize;
    bool isGameClear;
    bool isMineClicked;
    bool isRound;

    bool isGameLoad;

    Coordinate pos;     // Cursor Position
    Coordinate lastPos; // Last Cursor Position

    enum State state;
    enum Menu menu;
    enum Menu lastMenu;
    enum Difficulty difficulty;
    enum Difficulty lastDifficulty;

    // Rank
    vector<struct RankInfo> rankInfo_Easy;
    vector<struct RankInfo> rankInfo_Normal;
    vector<struct RankInfo> rankInfo_Hard;
    enum Difficulty rankDifficulty;
    int userNameMaxLength;
    int startPrintRankIndex;

    int terminalSize_save_row;
    int terminalSize_save_col;
};

bool RankCompare(const struct MineSweeper::RankInfo& r1, const struct MineSweeper::RankInfo& r2);

#endif
