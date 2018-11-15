/** @file mainpage.h
* @brief Beschreibung der Aufgabe Process List.
*/
/** @mainpage Process List -- Die Pflicht
*
* @author Peter Bauer
*
* @section intro Einführung
* Sie haben die Aufgabe eine Prozessliste, wie sie in den modernen Betriebssystemen
* üblich ist, zu implementieren. Wir beschränken uns auf Verwaltungsfunktionen
* (Initialisieren, Prozesse in die Liste einzutragen) und kleine Überblicksfunktionen
* (Länge der Liste, Auflisten von Prozessen mit bestimmten Merkmalen, etc.).
*
* @section datastructures Die Datenstrukturen
* @subsection ProcessList
* Die ProcessList hat eine maximale Anzahl von 13 Einträgen.
* Die ProcessList ist ein struct mit den Feldern
* - length (int)
* - processes (Array von Pointern auf ein struct ProcessListEntry): siehe unten
*
* @subsection ProcessListEntry
* Ein ProcessListEntry hält alle Daten, die zu einem Prozess gehören, welche sind:
* - pid (int): Die Process id.
* - process_name (const Pointer auf ein char (const char* process_name))
* - cpu_usage (int): Aktuelle CPU Nutzung in Prozent
* - time (int): Die bisher beanspruchte Prozessorzeit des Prozesses seit Prozessstart
*   in Millisekunden
* - threads (int): Die Anzahl der Threads
* - vsize (long): Gesamtspeicherbedarf des Prozesses in Kilobyte
* - state (enum ProcessState): Der Status des Prozesses (siehe unten)
*
* @subsection ProcessState
* ProcessState ist ein enum mit folgenden Werten: RUNNING, SLEEPING, IDLE, ZOMBIE,
* SWAPPEDOUT, STOPPED.
*
* @section Die Funktionen
* - init_process_list(): Setzt die Anzahl der Einträge auf 0.
* - get_length(): Gibt die Anzahl der Einträge zurück.
* - add_entry(): Fügt einen Eintrag hinzu.
* - add_entries(): Fügt mehrere Einträge hinzu.
* - get_process_with_id(): Sucht einen Prozess mit einer bestimmten id.
* - get_processes_with_state(): Sucht Prozesse in einem bestimmten Zustand.
* - get_process_with_highest_cpu_consumption(): Sucht die Prozesse mit der
* höchsten aktuellen Prozessorzeit.
* - get_process_with_lowest_cpu_consumption(): Sucht die Prozesse mit der
* niedrigsten aktuellen Prozessorzeit.
* - get_top_n_processes_cpu(): Sucht die n Prozesse mit der höchsten aktuellen Prozessorzeit.
* - get_bottom_n_processes_cpu(): Sucht die n Prozesse mit der niedrigsten aktuellen Prozessorzeit
*
*/
