-- ����������� ��� ������ ���� (2006 ����), ��� ���������� �����������

alter table Result drop competitionEntryId;
alter table Result drop rank;
alter table Result drop score;

alter table Result add   crossTime varchar(25) default null;
alter table Result add shootScore smallint default -1;

	 

alter table CompetitorToCategory add fightWoKnifeRank smallint default null;
alter table CompetitorToCategory add fightWoKnifeScore smallint default null;
alter table CompetitorToCategory add fightWKnifeRank smallint default null;
alter table CompetitorToCategory add fightWKnifeScore smallint default null;
alter table CompetitorToCategory add shootRank smallint default null;
alter table CompetitorToCategory add commonRank smallint default null;

update Result set ShootScore = -1 where ShootScore is null;