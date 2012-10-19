object dmCompetitorDAO: TdmCompetitorDAO
  OldCreateOrder = False
  Left = 480
  Top = 271
  Height = 312
  Width = 371
  object dsCompetitorExtended: TDataSource
    DataSet = ibqCompetitorExtendedTable
    Left = 224
    Top = 16
  end
  object ibqCompetitorExtendedTable: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    AfterScroll = ibqCompetitorExtendedTableAfterScroll
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select (Date '#39'now'#39' - Person.dob) / 365 age, '
      '       Person.id pers_id, '
      '       Person.surname, '
      '       Person.name pers_name, '
      '       Person.patronymic, '
      '       Person.female, '
      '       Skill.id skill_id, '
      '       Skill.shortDescription, '
      '       Club.shortName, '
      '       Competitor.id comp_id, '
      '       Competitor.weight '
      'from '
      '       Competitor, Skill, Person, Request, Club, Competition '
      'where '
      
        '       Person.id = Competitor.personId and Skill.id = Competitor' +
        '.skillId '
      
        '       and Club.id = Request.clubId and Competitor.requestId = R' +
        'equest.id and '
      '       Request.competitionId = Competition.id')
    Left = 80
    Top = 16
  end
  object ibqCompetitorAll: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from COMPETITOR')
    Left = 80
    Top = 80
  end
  object ibqCompetitor: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from COMPETITOR')
    Left = 88
    Top = 136
  end
  object dsCompetitorTable: TDataSource
    DataSet = ibqCompetitorAll
    Left = 224
    Top = 80
  end
  object dsCompetitor: TDataSource
    DataSet = ibqCompetitorAll
    Left = 224
    Top = 144
  end
  object ibqCompetitorToFightVersion: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from COMPETITORTOFIGHTVERSION')
    Left = 96
    Top = 208
  end
end
