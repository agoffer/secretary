object dmAvailCategoryDAO: TdmAvailCategoryDAO
  OldCreateOrder = False
  Left = 186
  Top = 114
  Height = 278
  Width = 359
  object ibqAvailCategoryAll: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from AvailableCategory')
    Left = 56
    Top = 16
  end
  object ibqAvailCategory: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from SKILL')
    Left = 56
    Top = 72
  end
  object dsAvailCategoryTable: TDataSource
    DataSet = ibqAvailCategoryAll
    Left = 240
    Top = 8
  end
  object dsAvailCategoryQuery: TDataSource
    DataSet = ibqAvailCategory
    Left = 248
    Top = 72
  end
end
