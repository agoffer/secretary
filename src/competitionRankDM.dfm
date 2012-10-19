object dmCompetitionRankDAO: TdmCompetitionRankDAO
  OldCreateOrder = False
  Left = 216
  Top = 253
  Height = 310
  Width = 402
  object ibqCompetitionRank: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select COMMENTS, DESCRIPTION, ID from COMPETITIONRANK')
    Left = 40
    Top = 80
  end
  object dsCompetitionRankQuery: TDataSource
    DataSet = ibqCompetitionRank
    Left = 184
    Top = 80
  end
  object dsCompetitionRankTable: TDataSource
    DataSet = ibtCompetitionRank
    Left = 176
    Top = 24
  end
  object ibtCompetitionRank: TIBTable
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    AfterPost = ibtCompetitionRankAfterPost
    BeforeInsert = ibtCompetitionRankBeforeInsert
    OnPostError = ibtCompetitionRankPostError
    Active = True
    BufferChunks = 1000
    CachedUpdates = False
    FieldDefs = <
      item
        Name = 'ID'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'DESCRIPTION'
        Attributes = [faRequired]
        DataType = ftString
        Size = 255
      end
      item
        Name = 'COMMENTS'
        DataType = ftString
        Size = 1024
      end>
    IndexDefs = <
      item
        Name = 'RDB$PRIMARY1'
        Fields = 'ID'
        Options = [ixPrimary, ixUnique]
      end>
    StoreDefs = True
    TableName = 'COMPETITIONRANK'
    Left = 40
    Top = 24
  end
  object dsrcScoreRanking: TDataSource
    DataSet = ibtScoreRanking
    Left = 184
    Top = 176
  end
  object ibtScoreRanking: TIBTable
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    AfterInsert = ibtScoreRankingAfterInsert
    BeforeInsert = ibtScoreRankingBeforeInsert
    BeforePost = ibtScoreRankingBeforePost
    Active = True
    BufferChunks = 1000
    CachedUpdates = False
    FieldDefs = <
      item
        Name = 'RANK'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'SCORE'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'COMPETITIONRANKID'
        Attributes = [faRequired]
        DataType = ftInteger
      end>
    IndexDefs = <
      item
        Name = 'RDB$FOREIGN2'
        Fields = 'COMPETITIONRANKID'
      end>
    IndexFieldNames = 'COMPETITIONRANKID'
    MasterFields = 'ID'
    MasterSource = dsCompetitionRankTable
    StoreDefs = True
    TableName = 'SCORERANKING'
    Left = 32
    Top = 168
  end
end
