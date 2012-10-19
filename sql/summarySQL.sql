select
fv.code,
avcat.startage, avcat.endage,
avcat.startweight, avcat.endweight,
comp_pers.surname, comp_pers.name, comp_pers.patronymic,
cl.city, sk.shortdescription,
ctc.commonrank,
comp_pers.surname
from
 competitor comp
 join person comp_pers on comp_pers.id = comp.personid
 join request req on req.id = comp.requestid
 join person req_pers on req_pers.id = req.personid
 join competitortocategory ctc on ctc.competitorid = comp.id
 join club  cl on cl.id = req.clubid
 join skill sk on sk.id = comp.skillid
 join category cat on cat.id = ctc.categoryid
 join fightversion fv on fv.id = cat.fightversionid
 join availablecategory avcat on avcat.id = cat.availablecategoryid
where
 cat.competitionid = 24 and avcat.female = 'F'
order by fv.code, avcat.startage, avcat.endage, ctc.commonrank
