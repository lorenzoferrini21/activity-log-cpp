# Activity Log C++ 📝

**Activity Log** è un’applicazione console scritta in C++ per gestire le attività giornaliere.  
Permette di aggiungere, visualizzare e salvare attività, tenendo traccia del tempo per categoria e dei buchi tra le attività. L’interfaccia grafica è realizzata con **Ncurses**, con menu a colori per rendere l’esperienza più chiara e interattiva.

---

## Caratteristiche principali

- Aggiunta attività con:
  - Descrizione
  - Orario di inizio e fine
  - Categoria: **Study, Work, Sport, Leisure, Other**
- Ordinamento automatico delle attività per orario di inizio
- Verifica di sovrapposizioni tra attività
- Calcolo dei buchi tra attività in minuti
- Statistiche: tempo totale per categoria
- Salvataggio automatico giornaliero in file `dailylog/dailylog_YYYY-MM-DD.txt`
- Interfaccia a menu con **Ncurses**:
  - Colori per categorie (Study=blu, Work=rosso, Sport=verde, Leisure=giallo, Other=bianco)
  - Menu per aggiungere, visualizzare e salvare attività
  - Navigazione tramite frecce e conferma con Enter

---

## Struttura del progetto

activity-log-cpp/
├─ main.cpp # Entry point
├─ NcursesUI.h/.cpp # Interfaccia grafica con Ncurses
├─ Time.h/.cpp # Classe Time
├─ Activity.h/.cpp # Classe Activity
├─ DailyLog.h/.cpp # Classe DailyLog
├─ Utils.h/.cpp # Funzioni di utilità
├─ CMakeLists.txt
└─ external/ # GoogleTest

## Requisiti

- C++17
- CMake >= 3.21
- Compilatore MinGW (Windows)
- MSYS2 consigliato su Windows per la compatibilità Ncurses

---

## Compilazione su Windows con MSYS2

1. Apri il terminale MSYS2 MinGW 64-bit
2. Installa Ncurses (se non già installato):
   pacman -S mingw-w64-x86_64-ncurses

   
1)Clona il repository e entra nella cartella:
git clone https://github.com/lorenzoferrini21/activity-log-cpp.git
cd activity-log-cpp

2)Crea cartella build e genera makefile con CMake:
mkdir build
cd build
cmake -G "MinGW Makefiles" ..

3)Compila:
cmake --build .

4)Avvia l’app:
./activity_log_cpp.exe

Nota: L’applicazione funziona solo da terminale compatibile con Ncurses (MSYS2, Git Bash o WSL). Non funziona direttamente da CLion console su Windows.
