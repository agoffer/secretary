object dmPersonDAO: TdmPersonDAO
  OldCreateOrder = False
  Left = 486
  Top = 276
  Height = 276
  Width = 223
  object ibqPersonAll: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    AfterScroll = ibqPersonAllAfterScroll
    Active = True
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from PERSON order by surname')
    Left = 24
    Top = 8
  end
  object ibqPerson: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    Active = True
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from PERSON')
    Left = 24
    Top = 72
  end
  object dsPersonTable: TDataSource
    DataSet = ibqPersonAll
    Left = 104
    Top = 8
  end
  object dsPersonQuery: TDataSource
    DataSet = ibqPerson
    Left = 112
    Top = 72
  end
  object dsPersonSlaveTable: TDataSource
    DataSet = ibqPersonSlaveTable
    Left = 104
    Top = 144
  end
  object ibqPersonSlaveTable: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    Active = True
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from PERSON order by surname')
    Left = 24
    Top = 144
  end
end
