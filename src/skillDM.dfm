object dmSkillDAO: TdmSkillDAO
  OldCreateOrder = False
  Left = 214
  Top = 114
  Height = 187
  Width = 229
  object ibqSkillAll: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    Active = True
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from SKILL')
    Left = 56
    Top = 16
  end
  object ibqSkill: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    Active = True
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from SKILL')
    Left = 56
    Top = 72
  end
  object dsSkillTable: TDataSource
    DataSet = ibqSkillAll
    Left = 128
    Top = 24
  end
  object dsSkillQuery: TDataSource
    DataSet = ibqSkill
    Left = 136
    Top = 80
  end
end
