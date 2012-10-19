object dmReportDataSource: TdmReportDataSource
  OldCreateOrder = False
  Left = 537
  Top = 128
  Height = 499
  Width = 595
  object ibqRepCompetitorDetail: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select (Date '#39'now'#39' - (Person.dob + 1)) / 365, '
      ' Person.id, '
      '       Person.surname, '
      '       Person.name, '
      '       Person.patronymic, '
      '       Person.dob, '
      '       Person.phone, '
      '       Person.female, '
      '       Person.additions, '
      '       Skill.id, '
      '       Skill.shortDescription, '
      '       Skill.fullDescription, '
      '       Skill.weight, '
      '       Skill.comments, '
      '       Request.id, '
      '       Request.personId, '
      '       Request.clubId, '
      '       Request.competitionId, '
      '       Request.comments, '
      '       Club.shortName,   '
      '       Competitor.id, '
      '       Competitor.weight, '
      '       CompetitorToCategory.sortion , '
      '       Result.shootscore, '
      '       Result.crosstime,'
      '       CompetitorToCategory.shootRank'
      
        '       from Competitor left outer join Result on Result.competit' +
        'orId = Competitor.id, Skill, Person, Request, Club, CompetitorTo' +
        'Category where '
      
        '       Person.id = Competitor.personId and Skill.id = Competitor' +
        '.skillId '
      
        '       and Club.id = Request.clubId and Request.id = Competitor.' +
        'requestId and        '
      '       Competitor.id = CompetitorToCategory.competitorId '
      
        '       and CompetitorToCategory.categoryId =  390 order by Compe' +
        'titorToCategory.sortion')
    Left = 80
    Top = 24
  end
  object ibqRepCategoryDetail: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    AfterScroll = CategoryDetailAfterScroll
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select'
      '  ct.id,'
      '  cr.description,'
      '  ac.female, '
      '  ac.startweight,'
      '  ac.endweight,'
      '  ac.startage,'
      '  ac.endage,'
      '  cpt.begindate,'
      '  cpt.enddate,'
      '  fv.code'
      'from'
      '  competitionrank cr,'
      '  availablecategory ac,'
      '  competition cpt,'
      '  fightversion fv,'
      '  category ct'
      'where'
      '  cr.id = cpt.competitionrankid and'
      '  ac.id = ct.availablecategoryid and'
      '  fv.id = ct.fightversionid and'
      
        '  ct.competitionid = 1 order  by ac.startage,   ac.startweight, ' +
        'fv.code ')
    Left = 264
    Top = 8
  end
  object ibqRepUncategoryListDetail: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select'
      '       Person.surname,'
      '       Person.name,'
      '       Person.patronymic,'
      '       Club.shortname,'
      '       Competitor.id'
      '       from Competitor, Person, Request, Club where'
      '       Person.id = Competitor.personId'
      '       and Request.id = Competitor.requestId'
      '       and Request.competitionId = 5 and'
      '       Club.id = Request.clubId and Competitor.id  in'
      
        '       (select distinct competitorId from CompetitorToFightVersi' +
        'on, Competitor,'
      
        '        Request where CompetitorToFightVersion.destributed = '#39'F'#39 +
        ' and'
      
        '        CompetitorToFightVersion.competitorId  = Competitor.id a' +
        'nd'
      '        Competitor.requestId = Request.id and'
      '        Request.competitionId = 5)'
      
        '        order by Club.name desc, Person.female, Person.surname d' +
        'esc')
    Left = 88
    Top = 88
  end
  object ibqRepUncategoryFV: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      
        'select fv.code from fightversion fv, competitortofightversion fv' +
        'ct '
      ' where fv.id = fvct.fightversionid and fvct.destributed ='#39'F'#39' '
      ' and fvct.competitorid = 90')
    Left = 48
    Top = 144
  end
  object ibqRepExtendedFV: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select fv.code from fightversion fv, extendedfightversion extfv '
      ' where fv.id = extfv.fightversionid '
      ' and extfv.competitorid = 90')
    Left = 248
    Top = 72
  end
  object ibqRepRequestClubListDetail: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select'
      'club.name,'
      'person.surname,'
      'person.name,'
      'person.patronymic,'
      'person.phone'
      'from'
      'club, person, request, competition'
      'where'
      
        'club.id = request.clubid and person.id = request.personid and re' +
        'quest.competitionid = competition.id'
      'and competition.id =  10 order by club.name')
    Left = 232
    Top = 136
  end
  object ibqRepCategoryFinalCompetitorDetail: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select'
      '  pers.surname,'
      '  pers.name,'
      '  pers.patronymic,'
      '  compToCat.shootrank,'
      '  compToCat.fightWOKnifeRank,'
      '  compToCat.fightWKnifeRank,'
      '  compToCat.commonRank , clb.shortname'
      'from'
      '  CompetitorToCategory compToCat'
      'join'
      '  Competitor comp on comp.id=compToCat.competitorid'
      'join'
      '  Person pers on pers.id=comp.personid'
      'join'
      '  Request req on req.id=comp.requestid'
      'join'
      '  Club clb on clb.id=req.clubid'
      'where'
      '  compToCat.categoryid=1409')
    Left = 80
    Top = 216
  end
  object ibqSummaryReport: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    BufferChunks = 1000
    CachedUpdates = False
    Left = 64
    Top = 296
  end
end
