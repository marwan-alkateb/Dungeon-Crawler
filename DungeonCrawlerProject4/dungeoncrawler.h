/*
 * DungeonCrawler stellt die „Managerklasse“ für das gesamte Spiel dar.
 * Das DungeonCrawler-Objekt enthält einen vector aus Character Pointern
 * sowie einem Pointer auf das aktueller Level.
 * Auch findet hier die Verarbeitung der Spielzüge statt.
 * Prinzipiell werden hier die Mechaniken implementiert,
 * allerdings werden viele Verarbeitungsschritte in den anderen Klassen implementiert.
 * So bleibt das Spiel an sich flexibel und erweiterbar.
*/

#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H
#include "userinterface.h"
#include "level.h"
#include "character.h"
#include <vector>
#include "logger.h"

class DungeonCrawler
{
private:
    logging::Logger& logger {logging::Logger::Get("foo.txt")};
    UserInterface* ui;
    Level* currentLevel;

public:
    DungeonCrawler();
    bool friendsAreDead() const;
    bool enemiesAreDead() const;
    ~DungeonCrawler();
    void play();
    bool deleteCharacter(int i);
    bool playersAreDead() const;
};

#endif // DUNGEONCRAWLER_H
