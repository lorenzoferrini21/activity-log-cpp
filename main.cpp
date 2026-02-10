//
// Created by User on 06/02/2026.
//

#include <iostream>
#include "DailyLog.h"
#include "Activity.h"
#include "Time.h"
#include "Category.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
#include <sys/stat.h>  // per _mkdir su Windows
#include <ctime>
#include <direct.h>

void createFolderIfNotExists(const std::string& folderName) {
    struct stat info;
    if (stat(folderName.c_str(), &info) != 0) {  // cartella non esiste
        _mkdir(folderName.c_str());             // crea cartella
    }
}

int main() {
    // Creiamo un DailyLog
    DailyLog log("2026-02-06");

    // Aggiungiamo attività (NON in ordine apposta)
    log.addActivity(Activity("Palestra", Time(18, 0), Time(20, 30), Category::Sport));
    log.addActivity(Activity("Studio C++", Time(9, 0), Time(11, 0), Category::Study));
    log.addActivity(Activity("Laboratorio", Time(11, 30), Time(13, 0), Category::Work));
    log.addActivity(Activity("Pranzo", Time(13, 0), Time(14, 0), Category::Leisure));

    // Stampiamo la giornata (ordine cronologico)
    std::cout << "=== DAILY LOG ===\n";
    std::cout << log.toString() << std::endl;

    // Controllo sovrapposizioni
    std::cout << "Has overlaps? " << (log.hasOverlaps() ? "YES" : "NO") << "\n";

    // Buchi
    auto gaps = log.getGapsInMinutes();
    std::cout << "Gaps:\n";
    for (int g : gaps) {
        std::cout << "- " << g << " minutes\n";
    }

    // Tempo per categoria
    std::cout << "\nTime by category:\n";
    std::cout << "Study: " << log.getTotalTimeByCategory(Category::Study) << " min\n";
    std::cout << "Work: " << log.getTotalTimeByCategory(Category::Work) << " min\n";
    std::cout << "Sport: " << log.getTotalTimeByCategory(Category::Sport) << " min\n";

    // ==================================================
    // SALVATAGGIO FILE AUTOMATICO CON DATA
    // ==================================================

    std::string projectFolder = "../"; // sale di una cartella dalla build (cmake-build-debug)
    std::string logsFolder = projectFolder + "dailylog";
    createFolderIfNotExists(logsFolder); // crea la cartella se non esiste

    //&createFolderIfNotExists("dailylog"); // crea la cartella dailylog se non esiste

    // Otteniamo la data odierna
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm;
    localtime_s(&local_tm, &now_time); // Windows

    std::ostringstream filenameStream;
    filenameStream << "dailylog_"
                   << std::put_time(&local_tm, "%Y-%m-%d")
                   << ".txt";

    std::string filePath = "../dailylog/" + filenameStream.str(); // percorso completo

    // Salvataggio e caricamento
    log.saveToFile(filePath);
    std::cout << "\nSaved to " << filePath << "\n";

    DailyLog loaded = DailyLog::loadFromFile(filePath);
    std::cout << "\n=== LOADED FROM FILE ===\n";
    std::cout << loaded.toString() << std::endl;

    return 0;
}
