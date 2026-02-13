#include "NcursesUI.h"
#include <ncurses/ncurses.h>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <direct.h>

// Utility per creare cartelle
void createFolderIfNotExists(const std::string& folderName) {
    struct stat info;
    if (stat(folderName.c_str(), &info) != 0) {
        _mkdir(folderName.c_str());
    }
}

NcursesUI::NcursesUI(DailyLog& l) : log(l) {}

void NcursesUI::run() {

    initscr();            // avvia ncurses
    noecho();             // non mostrare input digitato
    cbreak();             // modalità line-buffering disabilitata
    keypad(stdscr, TRUE); // abilita frecce e tasti speciali
    start_color();        // abilita colori

    // Inizializza coppie colori
    init_pair(1, COLOR_BLUE,   COLOR_BLACK);   // Study
    init_pair(2, COLOR_RED,    COLOR_BLACK);   // Work
    init_pair(3, COLOR_GREEN,  COLOR_BLACK);   // Sport
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);   // Leisure
    init_pair(5, COLOR_WHITE,  COLOR_BLACK);   // Other

    const char* options[] = { "Show activities", "Add activity", "Quit" };
    int n_options = 3;
    int highlight = 0;
    int ch;

    while (true) {
        clear();
        mvprintw(1, 2, "=== DAILY LOG (%s) ===", log.getDate().c_str());
        mvprintw(2, 2, "Use UP/DOWN arrows to navigate and ENTER to select");

        for (int i = 0; i < n_options; ++i) {
            if (i == highlight) attron(A_REVERSE);
            mvprintw(4 + i, 4, "%s", options[i]);
            if (i == highlight) attroff(A_REVERSE);
        }

        ch = getch();
        switch (ch) {
            case KEY_UP:
                highlight = (highlight - 1 + n_options) % n_options;
                break;
            case KEY_DOWN:
                highlight = (highlight + 1) % n_options;
                break;
            case '\n':
                if (highlight == 0) showActivities();
                else if (highlight == 1) addActivityScreen();
                else if (highlight == 2) goto exit_loop;
                break;
        }
    }

    exit_loop:
    saveDailyLog();
    endwin();
}

// ========================

void NcursesUI::showActivities() {
    clear();
    mvprintw(1, 2, "Activities for %s", log.getDate().c_str());

    int row = 3;
    const auto& acts = log.getActivities();
    if (acts.empty()) {
        mvprintw(row++, 4, "No activities yet!");
    } else {
        for (const auto& a : acts) {
            int color_pair = 5;
            switch(a.getCategory()) {
                case Category::Study:   color_pair = 1; break;
                case Category::Work:    color_pair = 2; break;
                case Category::Sport:   color_pair = 3; break;
                case Category::Leisure: color_pair = 4; break;
                default:                color_pair = 5; break;
            }
            attron(COLOR_PAIR(color_pair));
            mvprintw(row++, 4, "%s", a.toString().c_str());
            attroff(COLOR_PAIR(color_pair));
        }
    }

    // Mostra statistiche tempo totale per categoria
    row += 2;
    mvprintw(row++, 2, "=== Total time by category (minutes) ===");
    mvprintw(row++, 4, "Study: %d", log.getTotalTimeByCategory(Category::Study));
    mvprintw(row++, 4, "Work: %d", log.getTotalTimeByCategory(Category::Work));
    mvprintw(row++, 4, "Sport: %d", log.getTotalTimeByCategory(Category::Sport));
    mvprintw(row++, 4, "Leisure: %d", log.getTotalTimeByCategory(Category::Leisure));
    mvprintw(row++, 4, "Other: %d", log.getTotalTimeByCategory(Category::Other));

    mvprintw(row + 1, 2, "Press any key to return...");
    getch();
}

Category NcursesUI::stringToCategory(const std::string& str) {
    if (str == "Study") return Category::Study;
    if (str == "Work") return Category::Work;
    if (str == "Sport") return Category::Sport;
    if (str == "Leisure") return Category::Leisure;
    return Category::Other;
}

void NcursesUI::saveDailyLog() {
    createFolderIfNotExists("dailylog");  // crea la cartella se non esiste
    std::string fileName = "dailylog/dailylog_" + log.getDate() + ".txt";
    log.saveToFile(fileName);
}

// ========================

void NcursesUI::addActivityScreen() {
    echo();
    clear();

    char desc[100];
    int sh, sm, eh, em;

    mvprintw(2, 2, "Description: ");
    getnstr(desc, 99);

    mvprintw(3, 2, "Start hour (0-23): ");
    scanw("%d", &sh);
    mvprintw(4, 2, "Start minute (0-59): ");
    scanw("%d", &sm);
    mvprintw(5, 2, "End hour (0-23): ");
    scanw("%d", &eh);
    mvprintw(6, 2, "End minute (0-59): ");
    scanw("%d", &em);

    noecho();

    // Selezione categoria
    const char* categories[] = { "Study", "Work", "Sport", "Leisure", "Other" };
    int cat_index = 0;
    int ch;
    mvprintw(8, 2, "Select category (UP/DOWN + ENTER):");

    while (true) {
        for (int i = 0; i < 5; ++i) {
            int color_pair = 5; // default Other
            switch(i) {
                case 0: color_pair = 1; break; // Study
                case 1: color_pair = 2; break; // Work
                case 2: color_pair = 3; break; // Sport
                case 3: color_pair = 4; break; // Leisure
                case 4: color_pair = 5; break; // Other
            }

            if (i == cat_index) attron(A_REVERSE | COLOR_PAIR(color_pair));
            else attron(COLOR_PAIR(color_pair));

            mvprintw(10 + i, 4, "%-10s", categories[i]); // allineamento con spazi
            attroff(A_REVERSE | COLOR_PAIR(color_pair));
        }

        ch = getch();
        if (ch == KEY_UP) cat_index = (cat_index - 1 + 5) % 5;
        else if (ch == KEY_DOWN) cat_index = (cat_index + 1) % 5;
        else if (ch == '\n') break;
    }

    try {
        Category cat = stringToCategory(categories[cat_index]);
        Activity a(desc, Time(sh, sm), Time(eh, em), cat);
        log.addActivity(a);
        mvprintw(16, 2, "Activity added!");
    } catch (const std::exception& e) {
        mvprintw(16, 2, "Error: %s", e.what());
    }

    mvprintw(18, 2, "Press any key to return to menu...");
    getch();
}
