#jq_script.jq
{
  "player-name": ."player-name",
  "player-data": {
    "bio": .["player-data"].bio,
    "info": .["player-data"].info,
    "stats": .["player-data"].stats,
    "tokens": .["player-data"].tokens
  }
}
