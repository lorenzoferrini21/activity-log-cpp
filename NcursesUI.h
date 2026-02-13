//
// Created by User on 13/02/2026.
//

#ifndef ACTIVITY_LOG_CPP_NCURSESUI_H
#define ACTIVITY_LOG_CPP_NCURSESUI_H

#pragma once
#include "DailyLog.h"
#include "Activity.h"
#include "Time.h"
#include "Category.h"
#include <string>

class NcursesUI {
public:
    NcursesUI(DailyLog& l);

    // Loop principale della UI
    void run();

    void static createFolderIfNotExists(const std::string& folderName);
private:
    DailyLog& log;

    // Mostra tutte le attività
    void showActivities();

    // Schermata per aggiungere una nuova attività
    void addActivityScreen();

    // Funzione helper: converte stringa in Category
    Category stringToCategory(const std::string& str);

    void saveDailyLog();


};

#endif //ACTIVITY_LOG_CPP_NCURSESUI_H
