select
  ct.id,
  cr.description,
  ac.female,
  ac.startweight,
  ac.endweight,
  ac.startage,
  ac.endage,
  cpt.begindate,
  cpt.enddate,
  fv.code
from
  competitionrank cr,
  availablecategory ac,
  competition cpt,
  fightversion fv,
  category ct
where
  cr.id = cpt.competitionrankid and
  ac.id = ct.availablecategoryid and
  fv.id = ct.fightversionid and
  ct.competitionid = competition.id and competition.id = :competitionId
  order  by  fv.code, ac.female, ac.startage,
  ac.startweight
