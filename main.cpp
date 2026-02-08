//
// Created by User on 06/02/2026.
//

#include <iostream>
#include "DailyLog.h"
#include "Activity.h"
#include "Time.h"
#include "Category.h"

int main() {
    // Creiamo un DailyLog
    DailyLog log("2026-02-06");

    // Aggiungiamo attività (NON in ordine apposta)
    log.addActivity(Activity(
            "Palestra",
            Time(18, 0),
            Time(19, 30),
            Category::Sport
    ));

    log.addActivity(Activity(
            "Studio C++",
            Time(9, 0),
            Time(11, 0),
            Category::Study
    ));

    log.addActivity(Activity(
            "Laboratorio",
            Time(11, 30),
            Time(13, 0),
            Category::Work
    ));

    log.addActivity(Activity(
            "Pranzo",
            Time(13, 0),
            Time(14, 0),
            Category::Leisure
    ));

    // Stampiamo la giornata (ordine cronologico)
    std::cout << "=== DAILY LOG ===\n";
    std::cout << log.toString() << std::endl;

    //-Controllo sovrapposizioni
    std::cout << "Has overlaps? "
              << (log.hasOverlaps() ? "YES" : "NO") << "\n";

    // Buchi
    auto gaps = log.getGapsInMinutes();
    std::cout << "Gaps:\n";
    for (int g : gaps) {
        std::cout << "- " << g << " minutes\n";
    }

    // Tempo per categoria
    std::cout << "\nTime by category:\n";
    std::cout << "Study: "
              << log.getTotalTimeByCategory(Category::Study)
              << " min\n";

    std::cout << "Work: "
              << log.getTotalTimeByCategory(Category::Work)
              << " min\n";

    std::cout << "Sport: "
              << log.getTotalTimeByCategory(Category::Sport)
              << " min\n";

    // Salvataggio su file
    log.saveToFile("dailylog.txt");
    std::cout << "\nSaved to dailylog.txt\n";

    // Caricamento da file
    DailyLog loaded = DailyLog::loadFromFile("dailylog.txt");

    std::cout << "\n=== LOADED FROM FILE ===\n";
    std::cout << loaded.toString() << std::endl;

    return 0;
}
