#jq_script.jq
{
  "player-data": {
    "bio": .["player-data"].bio,
    "stats": .["player-data"].stats
  },
  "player-name": ."player-name"
}
