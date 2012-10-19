insert into ScoreRanking(rank, score, competitionrankid)
  select rank, score, 7 from ScoreRanking where competitionrankid=2
