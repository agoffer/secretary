object Form1: TForm1
  Left = 192
  Top = 103
  Width = 614
  Height = 480
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 256
    Width = 127
    Height = 13
    Caption = #1055#1088#1086#1076#1091#1082#1094#1080#1103' '#1087#1086' '#1085#1072#1082#1083#1072#1076#1085#1086#1081
  end
  object Label2: TLabel
    Left = 8
    Top = 112
    Width = 64
    Height = 13
    Caption = #1055#1086#1089#1090#1072#1074#1097#1080#1082#1080
  end
  object bToExcel: TButton
    Left = 8
    Top = 80
    Width = 145
    Height = 25
    Caption = #1054#1090#1095#1077#1090' '#1074' Excel'
    TabOrder = 0
    OnClick = bToExcelClick
  end
  object Grid: TDBGrid
    Left = 8
    Top = 128
    Width = 585
    Height = 120
    DataSource = dsSaleMan
    ReadOnly = True
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
  end
  object GGrid: TDBGrid
    Left = 8
    Top = 272
    Width = 585
    Height = 120
    DataSource = dsGoods
    ReadOnly = True
    TabOrder = 2
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
  end
  object bOpen: TButton
    Left = 8
    Top = 48
    Width = 145
    Height = 25
    Caption = #1054#1090#1082#1088#1099#1090#1100' '#1090#1072#1073#1083#1080#1094#1099
    TabOrder = 3
    OnClick = bOpenClick
  end
  object SaleMan: TTable
    DatabaseName = 'DBEPrim'
    FieldDefs = <
      item
        Name = 'ID'
        DataType = ftInteger
      end
      item
        Name = 'Org'
        DataType = ftString
        Size = 30
      end
      item
        Name = 'Addr'
        DataType = ftString
        Size = 50
      end
      item
        Name = 'Inn'
        DataType = ftString
        Size = 13
      end>
    ReadOnly = True
    StoreDefs = True
    TableName = 'SaleMan.db'
    TableType = ttParadox
    Left = 48
    Top = 8
    object SaleManID: TIntegerField
      FieldName = 'ID'
    end
    object SaleManOrg: TStringField
      FieldName = 'Org'
      Size = 30
    end
    object SaleManAddr: TStringField
      FieldName = 'Addr'
      Size = 50
    end
    object SaleManInn: TStringField
      FieldName = 'Inn'
      Size = 13
    end
  end
  object Goods: TTable
    DatabaseName = 'DBEPrim'
    FieldDefs = <
      item
        Name = 'ID'
        DataType = ftInteger
      end
      item
        Name = 'IDSale'
        DataType = ftInteger
      end
      item
        Name = 'Name'
        DataType = ftString
        Size = 40
      end
      item
        Name = 'Izmer'
        DataType = ftString
        Size = 5
      end
      item
        Name = 'Count'
        DataType = ftFloat
      end
      item
        Name = 'Price'
        DataType = ftCurrency
      end>
    IndexName = 'IDSale'
    MasterFields = 'ID'
    MasterSource = dsSaleMan
    ReadOnly = True
    StoreDefs = True
    TableName = 'Goods.db'
    TableType = ttParadox
    Left = 128
    Top = 8
    object GoodsID: TIntegerField
      FieldName = 'ID'
    end
    object GoodsIDSale: TIntegerField
      FieldName = 'IDSale'
    end
    object GoodsName: TStringField
      FieldName = 'Name'
      Size = 40
    end
    object GoodsIzmer: TStringField
      FieldName = 'Izmer'
      Size = 5
    end
    object GoodsCount: TFloatField
      FieldName = 'Count'
    end
    object GoodsPrice: TCurrencyField
      FieldName = 'Price'
    end
  end
  object DBase: TDatabase
    Connected = True
    DatabaseName = 'DBEPrim'
    DriverName = 'STANDARD'
    Params.Strings = (
      'PATH='
      'DEFAULT DRIVER=PARADOX'
      'ENABLE BCD=FALSE')
    SessionName = 'Default'
    Left = 8
    Top = 8
  end
  object dsSaleMan: TDataSource
    DataSet = SaleMan
    Left = 80
    Top = 8
  end
  object dsGoods: TDataSource
    DataSet = Goods
    Left = 160
    Top = 8
  end
end
