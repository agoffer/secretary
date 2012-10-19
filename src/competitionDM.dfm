object dmCompetitionDAO: TdmCompetitionDAO
  OldCreateOrder = False
  Left = 212
  Top = 237
  Height = 234
  Width = 374
  object dsCompetitoinQuery: TDataSource
    DataSet = ibqCompetition
    Left = 216
    Top = 72
  end
  object ibqCompetition: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from COMPETITION')
    Left = 32
    Top = 64
  end
  object dsCompetitionTable: TDataSource
    DataSet = ibqCompetitionAll
    Left = 208
    Top = 16
  end
  object ibqCompetitionAll: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    Active = True
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from COMPETITION order by begindate')
    Left = 32
    Top = 16
  end
  object ibqExtendedCompetitionAll: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      
        'select  competition.id cid,  competitionrank.id crid,  competiti' +
        'on.BEGINDATE, competition.ENDDATE, competition.comments ccomment' +
        's, competitionrank.description, competitionrank.comments crcomme' +
        'nts from COMPETITION, competitionrank where competitionrank.id =' +
        ' competition.competitionrankid')
    Left = 32
    Top = 128
  end
  object dsExtendedCompetitionTable: TDataSource
    DataSet = ibqExtendedCompetitionAll
    Left = 216
    Top = 128
  end
end
