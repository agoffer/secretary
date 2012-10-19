object dmRequestDAO: TdmRequestDAO
  OldCreateOrder = False
  Left = 214
  Top = 114
  Height = 293
  Width = 212
  object dsRequestTable: TDataSource
    DataSet = ibqRequestAll
    Left = 136
    Top = 48
  end
  object ibqRequest: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    Active = True
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from REQUEST')
    Left = 56
    Top = 136
  end
  object dsRequestQuery: TDataSource
    DataSet = ibqRequest
    Left = 136
    Top = 136
  end
  object ibqRequestAll: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    Active = True
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from REQUEST')
    Left = 56
    Top = 80
  end
end
