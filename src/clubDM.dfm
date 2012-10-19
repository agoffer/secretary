object dmClubDAO: TdmClubDAO
  OldCreateOrder = False
  Left = 291
  Top = 224
  Height = 210
  Width = 266
  object ibqClub: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from CLUB')
    Left = 40
    Top = 72
  end
  object dsClubTable: TDataSource
    DataSet = ibqClubAll
    Left = 120
    Top = 16
  end
  object dsClubQuery: TDataSource
    DataSet = ibqClub
    Left = 128
    Top = 80
  end
  object ibqClubAll: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    AfterScroll = ibqClubAllAfterScroll
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from CLUB')
    Left = 40
    Top = 16
  end
end
