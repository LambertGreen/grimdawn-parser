#jq_script.jq
{
  "player-name": ."player-name",
  "player-data": {
    "bio": .["player-data"].bio,
    "factions": .["player-data"].factions,
    "info": .["player-data"].info,
    "inventory": .["player-data"].inventory,
    "skills": .["player-data"].skills,
    "stats": .["player-data"].stats,
    "tokens": .["player-data"].tokens
  }
}
