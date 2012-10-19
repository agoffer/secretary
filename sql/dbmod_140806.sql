alter table Result drop fightWoKnifeRank;
alter table Result drop fightWoKnifeScore;
alter table Result drop fightWKnifeRank;
alter table Result drop fightWKnifeScore;

alter table CompetitorToCategory add fightWoKnifeRank smallint default null;
alter table CompetitorToCategory add fightWoKnifeScore smallint default null;
alter table CompetitorToCategory add fightWKnifeRank smallint default null;
alter table CompetitorToCategory add fightWKnifeScore smallint default null;
 
