#include "NcursesUI.h"
#include <ncurses/ncurses.h>
#include <string>
#include <vector>

NcursesUI::NcursesUI(DailyLog& l) : log(l) {}

void NcursesUI::run() {

    initscr();            // avvia ncurses
    noecho();             // non mostrare input digitato
    cbreak();             // modalità line-buffering disabilitata
    keypad(stdscr, TRUE); // abilita frecce e tasti speciali

    const char* options[] = { "Show activities", "Add activity", "Quit" };
    int n_options = 3;
    int highlight = 0; // voce selezionata
    int ch;

    while (true) {
        clear();
        mvprintw(1, 2, "=== DAILY LOG (%s) ===", log.getDate().c_str());
        mvprintw(2, 2, "Use UP/DOWN arrows to navigate and ENTER to select");

        // stampa menu con evidenziazione
        for (int i = 0; i < n_options; ++i) {
            if (i == highlight)
                attron(A_REVERSE); // evidenziazione
            mvprintw(4 + i, 4, "%s", options[i]);
            if (i == highlight)
                attroff(A_REVERSE);
        }

        ch = getch();
        switch (ch) {
            case KEY_UP:
                highlight = (highlight - 1 + n_options) % n_options;
                break;
            case KEY_DOWN:
                highlight = (highlight + 1) % n_options;
                break;
            case '\n': // invio
                if (highlight == 0) showActivities();
                else if (highlight == 1) addActivityScreen();
                else if (highlight == 2) goto exit_loop;
                break;
        }
    }

    exit_loop:
    // salva automaticamente il log alla chiusura
    log.saveToFile("dailylog_" + log.getDate() + ".txt");
    endwin();
}

void NcursesUI::showActivities() {
    clear();

    int row = 1;
    mvprintw(row++, 2, "=== Activities for %s ===", log.getDate().c_str());
    row++;

    const auto& acts = log.getActivities();

    // =========================
    // ATTIVITIES
    // =========================
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

    row++;

    // =========================
    // OVERLAPS
    // =========================
    mvprintw(row++, 2, "=== OVERLAPS CHECK ===");

    if (acts.size() > 1 && log.hasOverlaps()) {
        attron(COLOR_PAIR(2)); // rosso
        mvprintw(row++, 4, "WARNING: There are overlapping activities!");
        attroff(COLOR_PAIR(2));
    } else {
        mvprintw(row++, 4, "No overlaps detected.");
    }

    row++;

    // =========================
    // GAPS
    // =========================
    mvprintw(row++, 2, "=== GAPS (in minutes) ===");

    auto gaps = log.getGapsInMinutes();

    if (gaps.empty()) {
        mvprintw(row++, 4, "No gaps detected.");
    } else {
        int totalGap = 0;
        for (size_t i = 0; i < gaps.size(); ++i) {
            const auto& prev = acts[i];
            const auto& curr = acts[i+1];
            mvprintw(row++, 4, "Gap between '%s' and '%s': %d minutes",
                     prev.getDescription().c_str(),
                     curr.getDescription().c_str(),
                     gaps[i]);
            totalGap += gaps[i];
        }
        row++;
        mvprintw(row++, 4, "Total gap time: %d minutes", totalGap);
    }

    row += 2;
    mvprintw(row++, 2, "Press any key to return...");
    getch();
}


// ========================

void NcursesUI::addActivityScreen() {
    echo();   // mostra input
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

    try {
        Activity a(desc, Time(sh, sm), Time(eh, em), Category::Other);
        log.addActivity(a);
        mvprintw(8, 2, "Activity added!");
    } catch (const std::exception& e) {
        mvprintw(8, 2, "Error: %s", e.what());
    }

    mvprintw(10, 2, "Press any key to return to menu...");
    getch();
}
