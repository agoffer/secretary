object dmResultDAO: TdmResultDAO
  OldCreateOrder = False
  Left = 448
  Top = 368
  Height = 259
  Width = 279
  object ibqResult: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select * from result')
    Left = 24
    Top = 24
  end
  object ibqCompetitorToCategoryResultTable: TIBQuery
    Database = dmDataSource.ibdbSecretaryDB
    Transaction = dmDataSource.ibtrSecretaryDB
    AfterScroll = ibqCompetitorToCategoryResultTableAfterScroll
    BufferChunks = 1000
    CachedUpdates = False
    SQL.Strings = (
      'select'
      '   comp.id,'
      '  pers.surname, pers.name,'
      '  club.name,'
      '  ctc.fightwkniferank,'
      '  ctc.fightwokniferank,'
      '  res.crosstime,'
      '  res.shootscore, '
      '  ctc.shootrank,'
      '  ctc.commonrank'
      'from'
      '  competitor comp'
      '  left outer join person pers on pers.id = comp.personId'
      
        '  left outer join competitortocategory ctc on ctc.competitorid =' +
        ' comp.id'
      '  left outer join request req on req.id = comp.requestid'
      '  left outer join club on club.id = req.clubid'
      '  left outer join result res on res.competitorid = comp.id'
      'where'
      'ctc.categoryid = :categoryId'
      'order by ctc.commonrank')
    Left = 160
    Top = 24
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'categoryId'
        ParamType = ptUnknown
      end>
  end
  object dsCompetitorToCategoryResult: TDataSource
    DataSet = ibqCompetitorToCategoryResultTable
    Left = 128
    Top = 104
  end
end
