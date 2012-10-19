object dmFightVersionDAO: TdmFightVersionDAO
  OldCreateOrder = False
  Left = 721
  Top = 310
  Height = 242
  Width = 293
  object ibqFightVersionAll: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    Active = True
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from FIGHTVERSION')
    Left = 80
    Top = 32
  end
  object ibqFightVersion: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    Active = True
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from FIGHTVERSION')
    Left = 72
    Top = 96
  end
  object dsFightVersionTable: TDataSource
    DataSet = ibqFightVersionAll
    Left = 184
    Top = 48
  end
  object dsFightVersionQuery: TDataSource
    DataSet = ibqFightVersion
    Left = 192
    Top = 112
  end
end
