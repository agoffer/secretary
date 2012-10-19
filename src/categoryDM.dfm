object dmCategoryDAO: TdmCategoryDAO
  OldCreateOrder = False
  Left = 188
  Top = 115
  Height = 419
  Width = 320
  object dsCategoryExtended: TDataSource
    DataSet = ibqCategoryExtendedTable
    Left = 224
    Top = 16
  end
  object ibqCategoryExtendedTable: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select '
      'competitor.id, '
      'competitor.weight, '
      ''
      'skill.shortdescription, '
      ''
      'person.id, '
      'person.surname, '
      'person.name, '
      'person.patronymic, '
      'person.dob'
      ''
      'from competitor, person, skill'
      ''
      'where '
      
        'person.id = competitor.personid and skill.id = competitor.skilli' +
        'd and competitor.requestId = :requestId')
    Left = 80
    Top = 16
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'requestId'
        ParamType = ptUnknown
      end>
  end
  object ibqCategoryAll: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from Category')
    Left = 80
    Top = 80
  end
  object ibqCategory: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from COMPETITOR')
    Left = 88
    Top = 136
  end
  object dsCategoryTable: TDataSource
    DataSet = ibqCategoryAll
    Left = 224
    Top = 80
  end
  object dsCategory: TDataSource
    DataSet = ibqCategory
    Left = 224
    Top = 144
  end
  object ibqCompetitorToCategory: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from COMPETITORTOFIGHTVERSION')
    Left = 96
    Top = 224
  end
end
