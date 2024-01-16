#!/usr/bin/env python3

import json
import sqlite3
import sys


def process_json_file(playerFilename, dbFilename):
    # Load JSON data from the specified file
    with open(playerFilename, "r", encoding="utf-8") as file:
        data = json.load(file)

    # Connect to SQLite database (this creates the file if it doesn't exist)
    conn = sqlite3.connect(dbFilename)
    cursor = conn.cursor()

    # Create tables
    # PlayerHeader, PlayerBio, PlayerInfo, PlayerStats (simplified for this example)
    cursor.execute(
        """
    CREATE TABLE IF NOT EXISTS PlayerHeader (
        name TEXT PRIMARY KEY,
        classId TEXT,
        expansionStatus INTEGER,
        hardcore INTEGER,
        level INTEGER,
        sex INTEGER
    )
    """
    )

    cursor.execute(
        """
    CREATE TABLE IF NOT EXISTS PlayerBio (
        name TEXT,
        cunning REAL,
        devotionPoints INTEGER,
        energy REAL,
        experience INTEGER,
        health REAL,
        level INTEGER,
        modifierPoints INTEGER,
        physique REAL,
        skillPoints INTEGER,
        spirit REAL,
        totalDevotion INTEGER,
        FOREIGN KEY(name) REFERENCES PlayerHeader(name)
    )
    """
    )

    cursor.execute(
        """
    CREATE TABLE IF NOT EXISTS PlayerInfo (
        name TEXT,
        alternateConfig INTEGER,
        alternateConfigEnabled INTEGER,
        compassState INTEGER,
        currentTribute INTEGER,
        difficulty INTEGER,
        greatestDifficulty INTEGER,
        hasBeenInGame INTEGER,
        isInMainQuest INTEGER,
        money INTEGER,
        skillWindowShowHelp INTEGER,
        texture TEXT,
        FOREIGN KEY(name) REFERENCES PlayerHeader(name)
    )
    """
    )

    cursor.execute(
        """
    CREATE TABLE IF NOT EXISTS PlayerStats (
        name TEXT,
        championKills INTEGER,
        criticalHitsInflicted INTEGER,
        criticalHitsReceived INTEGER,
        deaths INTEGER,
        difficultySkip INTEGER,
        experienceFromKills INTEGER,
        greatestDamageInflicted REAL,
        greatestDamageReceived REAL,
        healthPotionsUsed INTEGER,
        heroKills INTEGER,
        hitsInflicted INTEGER,
        hitsReceived INTEGER,
        itemsCrafted INTEGER,
        kills INTEGER,
        lastHit REAL,
        lastHitBy REAL,
        loreNotesCollected INTEGER,
        manaPotionsUsed INTEGER,
        maxLevel INTEGER,
        mythicalRelicsCrafted INTEGER,
        oneShotChestsOpened INTEGER,
        playTime INTEGER,
        relicsCrafted INTEGER,
        shrinesRestored INTEGER,
        survivalDefensesBuilt INTEGER,
        survivalGreatestScore INTEGER,
        survivalGreatestWave INTEGER,
        survivalPowerUpsActivated INTEGER,
        transcendentRelicsCrafted INTEGER,
        unknown1 INTEGER,
        unknown2 INTEGER,
        FOREIGN KEY(name) REFERENCES PlayerHeader(name)
    )
    """
    )

    # Insert data into PlayerHeader
    header = data["player-data"]["header"]
    cursor.execute(
        """
    INSERT OR REPLACE INTO PlayerHeader (name, classId, expansionStatus, hardcore, level, sex)
    VALUES (?, ?, ?, ?, ?, ?)
    """,
        (
            header["name"],
            header["classId"],
            header["expansionStatus"],
            header["hardcore"],
            header["level"],
            header["sex"],
        ),
    )

    # Insert data into PlayerBio
    bio = data["player-data"]["bio"]
    cursor.execute(
        """
    INSERT OR REPLACE INTO PlayerBio (name, cunning, devotionPoints, energy, experience, health, level, modifierPoints, physique, skillPoints, spirit, totalDevotion)
    VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    """,
        (
            header["name"],
            bio["cunning"],
            bio["devotionPoints"],
            bio["energy"],
            bio["experience"],
            bio["health"],
            bio["level"],
            bio["modifierPoints"],
            bio["physique"],
            bio["skillPoints"],
            bio["spirit"],
            bio["totalDevotion"],
        ),
    )

    # Insert data into PlayerInfo
    info = data["player-data"]["info"]
    cursor.execute(
        """
    INSERT OR REPLACE INTO PlayerInfo (name, alternateConfig, alternateConfigEnabled, compassState, currentTribute, difficulty, greatestDifficulty, hasBeenInGame, isInMainQuest, money, skillWindowShowHelp, texture)
    VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    """,
        (
            header["name"],
            info["alternateConfig"],
            info["alternateConfigEnabled"],
            info["compassState"],
            info["currentTribute"],
            info["difficulty"],
            info["greatestDifficulty"],
            info["hasBeenInGame"],
            info["isInMainQuest"],
            info["money"],
            info["skillWindowShowHelp"],
            info["texture"],
        ),
    )

    # Insert data into PlayerStats
    stats = data["player-data"]["stats"]
    cursor.execute(
        """
    INSERT OR REPLACE INTO PlayerStats (name, championKills, criticalHitsInflicted, criticalHitsReceived, deaths, difficultySkip, experienceFromKills, greatestDamageInflicted, greatestDamageReceived, healthPotionsUsed, heroKills, hitsInflicted, hitsReceived, itemsCrafted, kills, lastHit, lastHitBy, loreNotesCollected, manaPotionsUsed, maxLevel, mythicalRelicsCrafted, oneShotChestsOpened, playTime, relicsCrafted, shrinesRestored, survivalDefensesBuilt, survivalGreatestScore, survivalGreatestWave, survivalPowerUpsActivated, transcendentRelicsCrafted, unknown1, unknown2)
    VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    """,
        (
            header["name"],
            stats["championKills"],
            stats["criticalHitsInflicted"],
            stats["criticalHitsReceived"],
            stats["deaths"],
            stats["difficultySkip"],
            stats["experienceFromKills"],
            stats["greatestDamageInflicted"],
            stats["greatestDamageReceived"],
            stats["healthPotionsUsed"],
            stats["heroKills"],
            stats["hitsInflicted"],
            stats["hitsReceived"],
            stats["itemsCrafted"],
            stats["kills"],
            stats["lastHit"],
            stats["lastHitBy"],
            stats["loreNotesCollected"],
            stats["manaPotionsUsed"],
            stats["maxLevel"],
            stats["mythicalRelicsCrafted"],
            stats["oneShotChestsOpened"],
            stats["playTime"],
            stats["relicsCrafted"],
            stats["shrinesRestored"],
            stats["survivalDefensesBuilt"],
            stats["survivalGreatestScore"],
            stats["survivalGreatestWave"],
            stats["survivalPowerUpsActivated"],
            stats["transcendentRelicsCrafted"],
            stats["unknown1"],
            stats["unknown2"],
        ),
    )

    # Commit changes and close the connection
    conn.commit()
    conn.close()

    playerName = header["name"]
    print(f"Imported player: {playerName}")


def main():
    if len(sys.argv) != 3:
        print("Usage: python import_player_json_to_db.py <playerFilename> <dbFilename>")
        sys.exit(1)

    playerFilename = sys.argv[1]
    dbFilename = sys.argv[2]
    process_json_file(playerFilename, dbFilename)


if __name__ == "__main__":
    main()
