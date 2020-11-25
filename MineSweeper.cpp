#include "MineSweeper.h"

MineSweeper::MineSweeper() {
    state = State::Menu;
    menu = Menu::Start;
    difficulty = Difficulty::Easy;
    rankDifficulty = Difficulty::Easy;

    Init();
    InitInfo();

    terminalSize_save_row = 0;
    terminalSize_save_col = 0;
}

void MineSweeper::StartMineSweeper() {
    Terminal_Init(true);
    SetTerminalSize_Menu();

    state = State::Menu;
    GetKey();

    while (true) {
        clear();

        if (state == State::Menu || state == State::ModeSelect) {
            PrintLogo();
            PrintMenuKeyInfo();
        }

        switch (state) {
        case State::Menu:
            PrintMenu(true);
            MenuControl();
            break;
        case State::ModeSelect:
            PrintMode(true);
            ModeControl();
            break;
        case State::LoadState:
            LoadGame();
            state = State::Game;
            break;
        case State::Rank:
            LoadRank();
            RankingControl();
            break;
        case State::Game:
            if (!isGameLoad) {
                CreateMap();
            }
            StartGame();
            state = State::Menu;
            break;
        case State::ExitState:
            Terminal_Init(false);
            return;
        }
    }
}

void MineSweeper::MenuControl() {
    while (true) {
        switch (GetKey()) {
        case UP:
        case LEFT:
            lastMenu = menu;
            switch (menu) {
            case Menu::Start:
                menu = Menu::Exit;
                break;
            case Menu::Load:
                menu = Menu::Start;
                break;
            case Menu::Ranking:
                menu = Menu::Load;
                break;
            case Menu::Exit:
                menu = Menu::Ranking;
                break;
            }
            break;
        case DOWN:
        case RIGHT:
            lastMenu = menu;
            switch (menu) {
            case Menu::Start:
                menu = Menu::Load;
                break;
            case Menu::Load:
                menu = Menu::Ranking;
                break;
            case Menu::Ranking:
                menu = Menu::Exit;
                break;
            case Menu::Exit:
                menu = Menu::Start;
                break;
            }
            break;
        case ENTER:
        case SPACE:
            switch (menu) {
            case Menu::Start:
                state = State::ModeSelect;
                break;
            case Menu::Load:
                state = State::LoadState;
                break;
            case Menu::Ranking:
                state = State::Rank;
                break;
            case Menu::Exit:
                state = State::ExitState;
                break;
            }
            return;
        case ESCAPE:
            break;
        }
        PrintMenu();
    }
}

void MineSweeper::ModeControl() {
    while (true) {
        switch (GetKey()) {
        case UP:
        case LEFT:
            lastDifficulty = difficulty;
            switch (difficulty) {
            case Difficulty::Easy:
                difficulty = Difficulty::Hard;
                break;
            case Difficulty::Normal:
                difficulty = Difficulty::Easy;
                break;
            case Difficulty::Hard:
                difficulty = Difficulty::Normal;
                break;
            }
            break;
        case DOWN:
        case RIGHT:
            lastDifficulty = difficulty;
            switch (difficulty) {
            case Difficulty::Easy:
                difficulty = Difficulty::Normal;
                break;
            case Difficulty::Normal:
                difficulty = Difficulty::Hard;
                break;
            case Difficulty::Hard:
                difficulty = Difficulty::Easy;
                break;
            }
            break;
        case ENTER:
        case SPACE:
            switch (difficulty) {
            case Difficulty::Easy:
            case Difficulty::Normal:
            case Difficulty::Hard:
                state = State::Game;
                break;
            }
            return;
        case ESCAPE:
            state = State::Menu;
            return;
        }
        PrintMode();
    }
}
void MineSweeper::RankingControl() {
    while (true) {
        clear();
        PrintRanking(rankDifficulty);

        switch (GetKey()) {
        case UP:
            startPrintRankIndex--;
            if (startPrintRankIndex < 0) {
                startPrintRankIndex = GetRankInfo(rankDifficulty).size() - RANK_PRINT_SIZE;
                if (startPrintRankIndex < 0)
                    startPrintRankIndex = 0;
            }
            break;
        case DOWN:
            startPrintRankIndex++;
            if (startPrintRankIndex + RANK_PRINT_SIZE > GetRankInfo(rankDifficulty).size()) {
                startPrintRankIndex = 0;
            }
            break;
        case LEFT:
            startPrintRankIndex = 0;

            switch (rankDifficulty) {
            case Difficulty::Easy:
                rankDifficulty = Difficulty::Hard;
                break;
            case Difficulty::Normal:
                rankDifficulty = Difficulty::Easy;
                break;
            case Difficulty::Hard:
                rankDifficulty = Difficulty::Normal;
                break;
            }
            break;
        case RIGHT:
            startPrintRankIndex = 0;

            switch (rankDifficulty) {
            case Difficulty::Easy:
                rankDifficulty = Difficulty::Normal;
                break;
            case Difficulty::Normal:
                rankDifficulty = Difficulty::Hard;
                break;
            case Difficulty::Hard:
                rankDifficulty = Difficulty::Easy;
                break;
            }
            break;
        case ESCAPE:
            state = State::Menu;
            return;
        }
    }
}

void MineSweeper::CreateMap() {
    isGameLoad = false;

    switch (difficulty) {
    case Difficulty::Easy:
        GetMap().CreateMap(MAP_SIZE_EASY, MINE_PERCENT_EASY);
        break;
    case Difficulty::Normal:
        GetMap().CreateMap(MAP_SIZE_NORMAL, MINE_PERCENT_NORMAL);
        break;
    case Difficulty::Hard:
        GetMap().CreateMap(MAP_SIZE_HARD, MINE_PERCENT_HARD);
        break;
    }
}

void MineSweeper::StartGame() {
    if (!isGameLoad)
        InitInfo();
    Init();
    StartTimer(isGameLoad);

    SetTerminalSize_Game();
    lastPos.y = lastPos.x = pos.y = pos.x = (GetMap().MapSize() - 1) / 2;
    PrintMap(true);
    PrintInfo(false);
    PrintGameKeyInfo();

    while (true) {
        if (isMineClicked) {
            DeleteSave();
            OpenAllMine();
            PrintGameOver();
            return;
        } else if (isGameClear) {
            DeleteSave();
            StopTimer();
            SaveRank();
            PrintGameClear();
            return;
        }

        switch (GetKey()) {
        case UP:
            MoveCursor(0, -1);
            break;
        case LEFT:
            MoveCursor(-1, 0);
            break;
        case DOWN:
            MoveCursor(0, 1);
            break;
        case RIGHT:
            MoveCursor(1, 0);
            break;
        case ENTER:
            SetClick();
            break;
        case SPACE:
            SetFlag();
            break;
        case TAB:
            SetRound();
            break;
        case TILDE:
            SetRound(false);
            break;
        case ESCAPE:
            SaveGame();
            isGameLoad = false;
            return;
        }
    }
}

// Save

void MineSweeper::SaveGame() {
    int fd = DirManager::CreateFile(SAVEFILE, SAVEMODE);

    // Map Size
    int mapSize = GetMap().MapSize();
    write(fd, &mapSize, sizeof(int));

    // Map Data
    for (int i = 0; i < totalMapSize; i++) {
        write(fd, &GetMap().Map()[i], sizeof(int));
    }

    // Info Data
    write(fd, &difficulty, sizeof(enum Difficulty));
    write(fd, &info, sizeof(struct MineSweeperInfo));
    close(fd);
}

void MineSweeper::LoadGame() {
    isGameLoad = true;

    int fd = DirManager::OpenFile(SAVEFILE, O_RDONLY);
    if (fd == -1) {
        isGameLoad = false;
        return;
    }

    // Map Size
    int mapSize;
    read(fd, &mapSize, sizeof(int));
    GetMap().SetMap(mapSize);

    totalMapSize = mapSize * mapSize;
    for (int i = 0; i < totalMapSize; i++) {
        read(fd, &GetMap().Map()[i], sizeof(int));
    }

    // Info Data
    read(fd, &difficulty, sizeof(enum Difficulty));
    read(fd, &info, sizeof(struct MineSweeperInfo));

    switch(difficulty) {
        case Difficulty::Easy:
            GetMap().SetMineSize(mapSize, MINE_PERCENT_EASY);
            break;
        case Difficulty::Normal:
            GetMap().SetMineSize(mapSize, MINE_PERCENT_NORMAL);
            break;
        case Difficulty::Hard:
            GetMap().SetMineSize(mapSize, MINE_PERCENT_HARD);
            break;
    }

    close(fd);
}

void MineSweeper::DeleteSave() {
    isGameLoad = false;
    DirManager::DeleteFile(SAVEFILE);
}

// Rank

void MineSweeper::SaveRank() {
    RankInfo rank;
    rank.uid = getuid();
    rank.diff = difficulty;
    rank.time = info.time;
    rank.flagCount = info.flagCount;
    rank.clickCount = info.clickCount;
    rank.roundCount = info.roundCount;

    int fd = DirManager::OpenFile(RANKFILE, RANKFLAG, (mode_t)RANKMODE);

    write(fd, &rank, sizeof(struct RankInfo));

    close(fd);
}

void MineSweeper::LoadRank(){
    RankInfo rank;

    ResetRankInfo();

    struct passwd *pw;
    while ((pw = getpwent()) != nullptr){
        if (pw->pw_uid >= 1000){
            string userPath = pw->pw_dir;
            userPath.append("/");
            userPath.append(DirManager::CHATBOT_PATH);
            userPath.append(RANKFILE);

            int fd = open(userPath.c_str(), O_RDONLY);
            if (fd == -1)
                continue;

            while (read(fd, &rank, sizeof(struct RankInfo)) > 0) {
                GetRankInfo(rank.diff).push_back(rank);
            }

            close(fd);

            int nameLength = strlen(pw->pw_name);
            userNameMaxLength = (userNameMaxLength < nameLength) ? nameLength:userNameMaxLength;
        }
    }

    endpwent();

    std::sort(rankInfo_Easy.begin(), rankInfo_Easy.end(), RankCompare);
    std::sort(rankInfo_Normal.begin(), rankInfo_Normal.end(), RankCompare);
    std::sort(rankInfo_Hard.begin(), rankInfo_Hard.end(), RankCompare);
}

void MineSweeper::ResetRankInfo() {
    rankInfo_Easy.clear();
    rankInfo_Normal.clear();
    rankInfo_Hard.clear();

    startPrintRankIndex = 0;
    userNameMaxLength = 0;
}

vector<struct MineSweeper::RankInfo>& MineSweeper::GetRankInfo(enum Difficulty diff) {
    switch(diff) {
        case Difficulty::Easy:
            return rankInfo_Easy;
        case Difficulty::Normal:
            return rankInfo_Normal;
        case Difficulty::Hard:
            return rankInfo_Hard;
        default:
            return rankInfo_Easy;
    }
}

bool RankCompare(const struct MineSweeper::RankInfo& r1, const struct MineSweeper::RankInfo& r2) {
    return timercmp(&r1.time, &r2.time, <);
}

void MineSweeper::CheckGameClear() {
    if (info.openCount + GetMap().MineSize() == totalMapSize)
        isGameClear = true;
}

// Print

void MineSweeper::PrintLogo() {
    gotoMenu(state, -1);
    SetForegroundColor(COLOR_RED);
    printf("** 지뢰찾기 **");
    ResetColor();
}

void MineSweeper::PrintMenuMessage(enum Menu menuState, bool isJustPrint) {
    switch (menuState) {
    case Menu::Start:
        if (!isJustPrint)
            gotoMenu(state, menuState, MENU_MARGIN_SIZE);
        printf(MESSAGE_START);
        break;
    case Menu::Load:
        if (!isJustPrint)
            gotoMenu(state, menuState, MENU_MARGIN_SIZE);
        printf(MESSAGE_LOAD);
        break;
    case Menu::Ranking:
        if (!isJustPrint)
            gotoMenu(state, menuState, MENU_MARGIN_SIZE + 2);
        printf(MESSAGE_RANK);
        break;
    case Menu::Exit:
        if (!isJustPrint)
            gotoMenu(state, menuState, MENU_MARGIN_SIZE);
        printf(MESSAGE_EXIT);
        break;
    }
}

void MineSweeper::PrintMenu(bool printAll) {
    if (printAll) {
        PrintMenuMessage(Menu::Start);
        PrintMenuMessage(Menu::Load);
        PrintMenuMessage(Menu::Ranking);
        PrintMenuMessage(Menu::Exit);
    }

    ResetColor();
    PrintMenuMessage(lastMenu);

    ResetColor();
    SetMenuColor(menu);
    PrintMenuMessage(menu);

    ResetColor();
}

void MineSweeper::PrintModeMessage(enum Difficulty modeState, bool isJustPrint) {
    switch (modeState) {
    case Difficulty::Easy:
        if (!isJustPrint)
            gotoMenu(state, modeState, MENU_MODE_MARGIN_SIZE);
        printf(MESSAGE_EASY);
        break;
    case Difficulty::Normal:
        if (!isJustPrint)
            gotoMenu(state, modeState, MENU_MODE_MARGIN_SIZE);
        printf(MESSAGE_NORMAL);
        break;
    case Difficulty::Hard:
        if (!isJustPrint)
            gotoMenu(state, modeState, MENU_MODE_MARGIN_SIZE - 1);
        printf(MESSAGE_HARD);
        break;
    }
}

void MineSweeper::PrintMode(bool printAll) {
    if (printAll) {
        PrintModeMessage(Difficulty::Easy);
        PrintModeMessage(Difficulty::Normal);
        PrintModeMessage(Difficulty::Hard);
    }

    ResetColor();
    PrintModeMessage(lastDifficulty);

    ResetColor();
    SetModeColor(difficulty);
    PrintModeMessage(difficulty);

    ResetColor();
}

void MineSweeper::PrintRanking(Difficulty diff) {
    SetTerminalSize_Rank();

    gotoMenu(state, 0, TERMINAL_RANK_SIZE / 3);
    SetMenuColor(menu);
    PrintMenuMessage(menu, true);
    ResetColor();
    printf(" : ");
    SetModeColor(diff);
    PrintModeMessage(diff, true);
    ResetColor();

    int printLimit = startPrintRankIndex + RANK_PRINT_SIZE;
    if (printLimit > GetRankInfo(diff).size())
        printLimit = GetRankInfo(diff).size();

    if (printLimit == 0) {
        gotoMenu(state, 2, TERMINAL_RANK_SIZE / 4 + 1);
        printf("저장된 랭킹이 없습니다");
    }
    else {
        for (int i = 0, index = startPrintRankIndex; index < printLimit; i++, index++) {
            gotoMenu(state, i+2);
            printf("%3d | %*s | 시간: %11.6lf | 클릭: %3d | 🚩: %3d | 주변확인: %3d", index + 1, userNameMaxLength, getpwuid(GetRankInfo(diff)[index].uid)->pw_name, GetTime(GetRankInfo(diff)[index].time), GetRankInfo(diff)[index].clickCount, GetRankInfo(diff)[index].flagCount, GetRankInfo(diff)[index].roundCount);
        }
    }
}

void MineSweeper::PrintMap(bool printAll) {
    int yCount = 0;
    if (printAll) {
        gotoMenu(state, 0, 5);
        SetModeColor(difficulty);
        PrintModeMessage(difficulty, true);
        ResetColor();

        Coordinate coor;
        for (coor.y = 0; coor.y < GetMap().MapSize(); coor.y++) {
            gotoxy(MAP_SPAN_SIZE_X, MAP_SPAN_SIZE_Y + coor.y);
            for (coor.x = 0; coor.x < GetMap().MapSize(); coor.x++) {
                HighlightColor(coor, false, true);
            }
        }
    }

    SetCursor();
}

void MineSweeper::PrintInfo(bool isUpdate) {
    if (!isUpdate) {
        gotoMenu(state, 2, 2);
        printf("총 크기 : %3d", totalMapSize);

        gotoMenu(state, 3, 5);
        printf("지뢰 : %3d", GetMap().MineSize());
    }

    gotoMenu(state, 5, 7);
    printf("🚩 : %3d", info.flagCount);

    gotoMenu(state, 6);
    printf("남은 개수 : %3d", totalMapSize - GetMap().MineSize() - info.openCount);
}

void MineSweeper::PrintGameOver() {
    gotoMenu(state, 8, 2);
    SetForegroundColor(COLOR_RED);
    printf("게임 오버!!");
    ResetColor();
    gotoMenu(state, 9);
    SetModeColor(difficulty);
    printf("엔터를 누르세요...");
    ResetColor();

    while (GetKey() != ENTER) { ; }
}

void MineSweeper::PrintGameClear() {
    gotoMenu(state, 8, 2);
    SetForegroundColor(COLOR_CYAN);
    printf("게임 클리어!!");
    ResetColor();
    gotoMenu(state, 9);
    SetModeColor(difficulty);
    printf("엔터를 누르세요...");
    ResetColor();

    while (GetKey() != ENTER) { ; }
}

void MineSweeper::PrintGameKeyInfo() {
    int yPos = 11;

    gotoMenu(state, yPos, 4);
    printf("이동 : 방향키");

    gotoMenu(state, yPos + 1, 4);
    printf("클릭 : 엔터");

    gotoMenu(state, yPos + 2, 4);
    printf("깃발 : 스페이스바");

    gotoMenu(state, yPos + 3);
    printf("주변확인 : 탭");

    gotoMenu(state, yPos + 4);
    printf("주변클릭 : ~");

    gotoMenu(state, yPos + 6);
    printf("뒤로가기 : BackSpace");
}

void MineSweeper::PrintMenuKeyInfo() {
    int xPos = MENU_MESSAGE_POSITION_X;
    int yPos = 1;

    gotoMenu(state, yPos, xPos + 4);
    printf("이동 : 방향키");

    gotoMenu(state, yPos + 1, xPos + 4);
    printf("클릭 : 엔터, 스페이스바");

    gotoMenu(state, yPos + 2, xPos);
    printf("뒤로가기 : BackSpace");
}

void MineSweeper::SetForegroundColor(int color) {
    printf("\033[%dm", 30 + color);
}
void MineSweeper::SetBackgroundColor(int color) {
    printf("\033[%dm", 40 + color);
}
void MineSweeper::SetMenuColor(enum Menu menuState) {
    switch (menuState) {
    case Menu::Start:
        SetForegroundColor(COLOR_BROWN);
        break;
    case Menu::Load:
        SetForegroundColor(COLOR_BLUE);
        break;
    case Menu::Ranking:
        SetForegroundColor(COLOR_CYAN);
        break;
    case Menu::Exit:
        SetForegroundColor(COLOR_RED);
        break;
    }
}
void MineSweeper::SetModeColor(enum Difficulty modeState) {
    switch (modeState) {
    case Difficulty::Easy:
        SetForegroundColor(COLOR_GREEN);
        break;
    case Difficulty::Normal:
        SetForegroundColor(COLOR_MAGENTA);
        break;
    case Difficulty::Hard:
        SetForegroundColor(COLOR_RED);
        break;
    }
}
void MineSweeper::ResetColor() { printf("\033[39m\033[49m"); }


// Initialize

void MineSweeper::Init() {
    totalMapSize = GetMap().MapSize() * GetMap().MapSize();
    isGameClear = false;
    isMineClicked = false;
    isRound = false;

    lastPos.x = pos.x = 0;
    lastPos.y = pos.y = 0;
}

void MineSweeper::InitInfo() {
    info.flagCount = 0;
    info.clickCount = 0;
    info.roundCount = 0;
    info.openCount = 0;
}


// Timer

void MineSweeper::StartTimer(bool isGameLoaded) {
    if (isGameLoaded) {
        StopTimer();
    }
    else {
        gettimeofday(&info.time, NULL);
    }
}

void MineSweeper::StopTimer() {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    struct timeval start;
    start.tv_sec = info.time.tv_sec;
    start.tv_usec = info.time.tv_usec;

    timersub(&tv, &start, &info.time);
}

double MineSweeper::GetTime(struct timeval time) {
    return (double)time.tv_sec + (double)time.tv_usec / CLOCKS_PER_SEC;
}


// Map

MineMap &MineSweeper::GetMap() { return map; }

int &MineSweeper::GetData(int x, int y) { return GetMap().GetData(x, y); }

int &MineSweeper::GetData(Coordinate c) { return GetMap().GetData(c.x, c.y); }

MineSweeper::Type MineSweeper::GetType(int x, int y) {
    int data = GetData(x, y);
    if (data < 0)
        return Type::Flag;
    else if (data == MineMap::NONE || data == MineMap::OPENED_NONE)
        return Type::None;
    else if (data == MineMap::MINE)
        return Type::Mine;
    else
        return Type::Number;
}

MineSweeper::Type MineSweeper::GetType(int data) {
    if (data < 0)
        return Type::Flag;
    else if (data == MineMap::NONE || data == MineMap::OPENED_NONE)
        return Type::None;
    else if (data == MineMap::MINE || data == MineMap::OPENED_MINE)
        return Type::Mine;
    else
        return Type::Number;
}

bool MineSweeper::IsOpened(int x, int y) { return (GetData(x, y) >= 10); }
bool MineSweeper::IsOpened(int data) { return (data >= 10); }

// Cursor
void MineSweeper::MoveCursor(int x, int y) {
    x += pos.x;
    y += pos.y;

    if (x == -1)
        x = GetMap().MapSize() - 1;
    else if (x == GetMap().MapSize())
        x = 0;
    else if (y == -1)
        y = GetMap().MapSize() - 1;
    else if (y == GetMap().MapSize())
        y = 0;

    CheckRound();

    lastPos.x = pos.x;
    lastPos.y = pos.y;
    pos.x = x;
    pos.y = y;

    SetCursor();
}

void MineSweeper::SetCursor() {
    CheckRound();
    HighlightColor(lastPos, false);
    HighlightColor(pos, true);
}

void MineSweeper::HighlightColor(Coordinate hlPos, bool isHighlight, bool isHighlightAll) {
    int color;
    int data = GetData(hlPos);
    Type dataType = GetType(data);
    gotoxy(MAP_SPAN_SIZE_X + hlPos.x * 2, MAP_SPAN_SIZE_Y + hlPos.y);

    if (hlPos.x == 0)
        isHighlightAll = false;

    if (isHighlight) { // High Light Number
        if (IsOpened(data)) {
            switch (GetType(data)) {
            case Type::None:
                if (isHighlightAll)
                    printf("\033[30m\033[45m %c\033[39m\033[49m", CHAR_ZERO);
                else
                    printf(" \033[30m\033[45m%c\033[39m\033[49m", CHAR_ZERO);
                break;
            case Type::Number:
                color = 31 + data / 10;
                if (color == 35)
                    color = 29;
                if (isHighlightAll)
                    printf("\033[%dm\033[45m %d\033[39m\033[49m",
                           (color < 37) ? color : 31, data / 10);
                else
                    printf(" \033[%dm\033[45m%d\033[39m\033[49m",
                           (color < 37) ? color : 31, data / 10);
                break;
            case Type::Mine:
                if (isHighlightAll)
                    printf("\033[39m\033[45m "
                           "\033[33m\033[41m%c\033[39m\033[49m",
                           CHAR_MINE);
                else
                    printf(" \033[33m\033[41m%c\033[39m\033[49m", CHAR_MINE);
                break;
            }
        } else if (dataType == Type::Flag) {
            if (isHighlightAll)
                printf("\033[31m\033[45m %c\033[39m\033[49m", CHAR_FLAG);
            else
                printf(" \033[31m\033[45m%c\033[39m\033[49m", CHAR_FLAG);
        } else {
            if (isHighlightAll)
                printf("\033[30m\033[45m %c\033[39m\033[49m", CHAR_DEFAULT);
            else
                printf(" \033[30m\033[45m%c\033[39m\033[49m", CHAR_DEFAULT);
        }
    } else { // Disable High Light Number
        if (IsOpened(data)) {
            switch (dataType) {
            case Type::None:
                if (isHighlightAll)
                    printf("\033[37m %c\033[39m", CHAR_ZERO);
                else
                    printf(" \033[37m%c\033[39m", CHAR_ZERO);
                break;
            case Type::Number:
                color = 31 + data / 10;
                if (isHighlightAll)
                    printf("\033[%dm %d\033[39m", (color < 37) ? color : 31,
                           data / 10);
                else
                    printf(" \033[%dm%d\033[39m", (color < 37) ? color : 31,
                           data / 10);
                break;
            case Type::Mine:
                if (isHighlightAll)
                    printf("\033[31m %c\033[39m", CHAR_MINE);
                else
                    printf(" \033[31m%c\033[39m", CHAR_MINE);
                break;
            }
        } else if (dataType == Type::Flag) {
            printf(" \033[37m\033[44m%c\033[39m\033[49m", CHAR_FLAG);
        } else {
            if (isHighlightAll)
                printf("\033[37m %c\033[39m", CHAR_DEFAULT);
            else
                printf(" \033[37m%c\033[39m", CHAR_DEFAULT);
        }
    }
}

void MineSweeper::HighlightRound(Coordinate hlPos, bool isHighlight) {
    Coordinate findPos = hlPos;
    HighlightColor(findPos, isHighlight, true);
    for (int i = 0; i < 8; i++) {
        switch (i) {
        case 0: //상
            findPos.y--;
            break;
        case 1: //우상
            findPos.x++;
            break;
        case 2: //우
            findPos.y++;
            break;
        case 3: //우하
            findPos.y++;
            break;
        case 4: //하
            findPos.x--;
            break;
        case 5: //좌하
            findPos.x--;
            break;
        case 6: //좌
            findPos.y--;
            break;
        case 7: //좌상
            findPos.y--;
            break;
        }
        if (findPos.x >= 0 && findPos.x < GetMap().MapSize() && findPos.y >= 0 && findPos.y < GetMap().MapSize()) {
            bool isHLAll = (i < 5) ? true : false;
            HighlightColor(findPos, isHighlight, isHLAll);
        }
    }
}

void MineSweeper::SetClick() {
    int &data = GetData(pos);
    if (IsOpened(data))
        return;

    Type dType = GetType(data);
    if (dType == Type::Flag)
        return;
    else if (dType == Type::Mine) {
        data = MineMap::OPENED_MINE;
        isMineClicked = true;
    } else if (dType == Type::None) {
        data = MineMap::OPENED_NONE;
        FindZero(pos);
    } else {
        data *= 10;
    }

    info.clickCount++;
    info.openCount++;
    SetCursor();

    PrintInfo();
    CheckGameClear();
}

void MineSweeper::SetClick(Coordinate clickPos, bool isCursorMove,
                           bool isFindZero) {
    int &data = GetData(clickPos);
    if (IsOpened(data))
        return;

    Type dType = GetType(data);
    if (dType == Type::Flag)
        return;
    else if (dType == Type::Mine) {
        data = MineMap::OPENED_MINE;
        isMineClicked = true;
    } else if (dType == Type::None) {
        data = MineMap::OPENED_NONE;
        if (isFindZero)
            FindZero(clickPos);
    } else {
        data *= 10;
    }

    if (isCursorMove) {
        info.clickCount++;
        SetCursor();
    } else {
        HighlightColor(clickPos, false);
    }

    info.openCount++;
    PrintInfo();
    CheckGameClear();
}

void MineSweeper::SetFlag() {
    int &data = GetData(pos);
    if (IsOpened(data))
        return;

    if (data >= 0)
        info.flagCount++;
    else
        info.flagCount--;

    if (data == MineMap::NONE)
        data = MineMap::FLAGED_NONE;
    else if (data == MineMap::FLAGED_NONE)
        data = MineMap::NONE;
    else
        data = -data;

    SetCursor();
    PrintInfo();
}

void MineSweeper::SetRound(bool isOnlyHighlight) {
    Coordinate findPos = pos;
    if (!isOnlyHighlight)
        SetClick(findPos, true, true);
    HighlightColor(findPos, true, true);
    for (int i = 0; i < 8; i++) {
        switch (i) {
        case 0: //상
            findPos.y--;
            break;
        case 1: //우상
            findPos.x++;
            break;
        case 2: //우
            findPos.y++;
            break;
        case 3: //우하
            findPos.y++;
            break;
        case 4: //하
            findPos.x--;
            break;
        case 5: //좌하
            findPos.x--;
            break;
        case 6: //좌
            findPos.y--;
            break;
        case 7: //좌상
            findPos.y--;
            break;
        }
        if (findPos.x >= 0 && findPos.x < GetMap().MapSize() && findPos.y >= 0 && findPos.y < GetMap().MapSize()) {
            if (!isOnlyHighlight)
                SetClick(findPos, false, true);
            bool isHLAll = (i < 5) ? true : false;
            HighlightColor(findPos, true, isHLAll);
        }
    }

    isRound = true;
    info.roundCount++;
}

void MineSweeper::CheckRound() {
    if (isRound) {
        isRound = false;
        HighlightRound(pos, false);
    }
}

void MineSweeper::FindZero(Coordinate findPos) {
    SetClick(findPos);
    for (int i = 0; i < 8; i++) {
        switch (i) {
        case 0: //상
            findPos.y--;
            break;
        case 1: //우상
            findPos.x++;
            break;
        case 2: //우
            findPos.y++;
            break;
        case 3: //우하
            findPos.y++;
            break;
        case 4: //하
            findPos.x--;
            break;
        case 5: //좌하
            findPos.x--;
            break;
        case 6: //좌
            findPos.y--;
            break;
        case 7: //좌상
            findPos.y--;
            break;
        }
        if (findPos.x >= 0 && findPos.x < GetMap().MapSize() && findPos.y >= 0 && findPos.y < GetMap().MapSize()) {
            if (IsOpened(findPos.x, findPos.y) == false) {
                Type findType = GetType(findPos.x, findPos.y);
                if (findType == Type::None) {
                    FindZero(findPos);
                } else if (findType == Type::Number) {
                    SetClick(findPos);
                }
            }
        }
    }
}

void MineSweeper::OpenAllMine() {
    Coordinate minePos;
    for (minePos.y = 0; minePos.y < GetMap().MapSize(); minePos.y++) {
        for (minePos.x = 0; minePos.x < GetMap().MapSize(); minePos.x++) {
            if (GetType(minePos.x, minePos.y) == Type::Mine) {
                GetData(minePos) = MineMap::OPENED_MINE;
                HighlightColor(minePos, true);
            }
        }
    }
}

// Terminal
void MineSweeper::SetTerminalSize(int row, int col) {
    printf("\e[8;%d;%dt", row, col);
}

void MineSweeper::SetTerminalSize_Menu() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    terminalSize_save_row = w.ws_row;
    terminalSize_save_col = w.ws_col;

    int terminalSize_r = TERMINAL_MESSAGE_SIZE;
    int terminalSize_c = (MAP_SPAN_SIZE_X + MENU_MESSAGE_POSITION + MENU_MESSAGE_POSITION_X) * 2;
    terminalSize_r = (terminalSize_r > w.ws_row) ? terminalSize_r : w.ws_row;
    terminalSize_c = (terminalSize_c > w.ws_col) ? terminalSize_c : w.ws_col;

    SetTerminalSize(terminalSize_r, terminalSize_c);
}

void MineSweeper::SetTerminalSize_Game() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    int terminalSize_r = GetMap().MapSize() + MAP_SPAN_SIZE_Y * 2;
    int terminalSize_c = GetMap().MapSize() * 2 + MAP_SPAN_SIZE_X * 3 + TERMINAL_MESSAGE_SIZE;
    terminalSize_r = (terminalSize_r > w.ws_row) ? terminalSize_r : w.ws_row;
    terminalSize_c = (terminalSize_c > w.ws_col) ? terminalSize_c : w.ws_col;

    SetTerminalSize(terminalSize_r, terminalSize_c);
}

void MineSweeper::SetTerminalSize_Rank() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    int terminalSize_r = RANK_PRINT_SIZE + MENU_MESSAGE_POSITION * 2;
    int terminalSize_c = (TERMINAL_RANK_SIZE > w.ws_col) ? TERMINAL_RANK_SIZE : w.ws_col;

    terminalSize_r = (terminalSize_r > w.ws_row) ? terminalSize_r : w.ws_row;

    SetTerminalSize(terminalSize_r, terminalSize_c);
}

int MineSweeper::GetKey() {
    int c;
    struct termios oldattr, newattr;

    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    newattr.c_cc[VMIN] = 1;
    newattr.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    c = getchar();
    if (c == ARROW) {
        getchar();
        c = getchar();
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return c;
}

void MineSweeper::Terminal_Init(bool isStart) {
    if (!isStart) {
        SetTerminalSize(terminalSize_save_row, terminalSize_save_col);
        signal(SIGINT, SIG_DFL);
    }
    else {
        signal(SIGINT, SIG_IGN);
    }

    Terminal_SetCursorHide(isStart);
    Terminal_SaveNLoad(isStart);
    Terminal_SetScrollHide(isStart);
}

void MineSweeper::Terminal_SetCursorHide(bool hide) {
    if (hide) {
        printf("\e[?25l");
    } else {
        printf("\e[?25h");
    }
}

void MineSweeper::Terminal_SetScrollHide(bool hide) {
    if (!hide) {
        printf("\e[?30l");
    } else {
        printf("\e[?30h");
    }
}

void MineSweeper::Terminal_SaveNLoad(bool isSave) {
    if (isSave) {
        printf("\e[?1049h");
    } else {
        printf("\e[?1049l");
    }
}

void MineSweeper::terminal_clear() { printf("\033[J"); }
void MineSweeper::terminal_scroll_up() { printf("\033[S"); }
void MineSweeper::clear() { printf("\033[H\033[J"); }
void MineSweeper::gotoxy(int x, int y) { printf("\033[%d;%dH", y, x); }
void MineSweeper::gotoup(int count) { printf("\033[%dA", count); }
void MineSweeper::gotodown(int count) { printf("\033[%dB", count); }
void MineSweeper::gotoleft(int count) { printf("\033[%dD", count); }
void MineSweeper::gotoright(int count) { printf("\033[%dC", count); }

void MineSweeper::gotoMenu(State state, int index, int move_x) {
    switch (state) {
    case State::Menu:
        gotoxy(MENU_MESSAGE_POSITION + move_x, MENU_MESSAGE_POSITION + index * 2);
        break;
    case State::ModeSelect:
        gotoxy(MENU_MESSAGE_POSITION + move_x, MENU_MESSAGE_POSITION + index * 2);
        break;
    case State::Rank:
        gotoxy(MENU_MESSAGE_POSITION + move_x, MENU_DEFAULT_POSITION + index);
        break;
    case State::Game:
        gotoxy((GetMap().MapSize() + MAP_SPAN_SIZE_X) * 2 + move_x, MAP_SPAN_SIZE_Y + 1 + index);
        break;
    }
}
