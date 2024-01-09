#jq_script.jq
{
  "player-name": ."player-name",
  "player-data": {
    "bio": .["player-data"].bio,
    "header": .["player-data"].header,
    "info": .["player-data"].info,
    "stats": .["player-data"].stats,
    "tokens": .["player-data"].tokens
  }
}
