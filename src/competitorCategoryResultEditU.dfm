object frmCompetitorCategoryResultEdit: TfrmCompetitorCategoryResultEdit
  Left = 264
  Top = 136
  BorderStyle = bsDialog
  Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090#1099' '#1091#1095#1072#1089#1090#1085#1080#1082#1086#1074' '#1074' '#1082#1072#1090#1077#1075#1086#1088#1080#1080
  ClientHeight = 474
  ClientWidth = 792
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object grboxCompetitorSelection: TGroupBox
    Left = 0
    Top = 0
    Width = 792
    Height = 474
    Align = alClient
    Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1091#1095#1072#1089#1090#1085#1080#1082#1072
    TabOrder = 0
    object lblFightWKnifeRank: TLabel
      Left = 62
      Top = 400
      Width = 317
      Height = 20
      Caption = #1052#1077#1089#1090#1086'  '#1087#1086' '#1073#1086#1103#1084' '#1089' '#1093#1086#1083#1086#1076#1085#1099#1084' '#1086#1088#1091#1078#1080#1077#1084':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lblFightWOKnifeRank: TLabel
      Left = 48
      Top = 360
      Width = 329
      Height = 20
      Caption = #1052#1077#1089#1090#1086'  '#1087#1086' '#1073#1086#1103#1084' '#1073#1077#1079' '#1093#1086#1083#1086#1076#1085#1086#1075#1086' '#1086#1088#1091#1078#1080#1103':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lblModifiedShootRank: TLabel
      Left = 544
      Top = 316
      Width = 12
      Height = 29
      Caption = '*'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -24
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lblShootRank: TLabel
      Left = 96
      Top = 320
      Width = 282
      Height = 20
      Caption = #1052#1077#1089#1090#1086'  '#1087#1086' '#1089#1090#1088#1077#1083#1100#1073#1077' '#1080#1079' '#1074#1080#1085#1090#1086#1074#1082#1080':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lblCommonRank: TLabel
      Left = 102
      Top = 440
      Width = 276
      Height = 20
      Caption = #1054#1073#1097#1077#1077' '#1084#1077#1089#1090#1086' '#1079#1072' '#1089#1086#1088#1077#1074#1085#1086#1074#1072#1085#1080#1077':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
    end
    object lblModifiedFightWOKnifeRank: TLabel
      Left = 544
      Top = 356
      Width = 12
      Height = 29
      Caption = '*'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -24
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lblModifiedFightWKnifeRank: TLabel
      Left = 544
      Top = 396
      Width = 12
      Height = 29
      Caption = '*'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -24
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lblModifiedCommonRank: TLabel
      Left = 544
      Top = 436
      Width = 12
      Height = 29
      Caption = '*'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -24
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object dbgrdCompetitors: TDBGrid
      Left = 2
      Top = 15
      Width = 788
      Height = 210
      Align = alTop
      DataSource = dmResultDAO.dsCompetitorToCategoryResult
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit]
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      Columns = <
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'COMMONRANK'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clRed
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          Title.Alignment = taCenter
          Title.Caption = #1054#1073#1097#1077#1077' '#1084#1077#1089#1090#1086
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -11
          Title.Font.Name = 'MS Sans Serif'
          Title.Font.Style = [fsBold, fsItalic]
          Width = 85
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'SURNAME'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Title.Alignment = taCenter
          Title.Caption = #1060#1072#1084#1080#1083#1080#1103
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -11
          Title.Font.Name = 'MS Sans Serif'
          Title.Font.Style = [fsBold]
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'NAME'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Title.Alignment = taCenter
          Title.Caption = #1048#1084#1103
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -11
          Title.Font.Name = 'MS Sans Serif'
          Title.Font.Style = [fsBold]
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'NAME1'
          Title.Alignment = taCenter
          Title.Caption = #1050#1083#1091#1073
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -11
          Title.Font.Name = 'MS Sans Serif'
          Title.Font.Style = [fsBold]
          Width = 80
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'FIGHTWOKNIFERANK'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          Title.Alignment = taCenter
          Title.Caption = #1056#1041' '#1073#1077#1079' '#1061#1054
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -11
          Title.Font.Name = 'MS Sans Serif'
          Title.Font.Style = [fsBold]
          Width = 65
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'FIGHTWKNIFERANK'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          Title.Alignment = taCenter
          Title.Caption = #1056#1041' '#1089' '#1061#1054
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -11
          Title.Font.Name = 'MS Sans Serif'
          Title.Font.Style = [fsBold]
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'CROSSTIME'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsItalic]
          Title.Alignment = taCenter
          Title.Caption = #1050#1088#1086#1089#1089
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -11
          Title.Font.Name = 'MS Sans Serif'
          Title.Font.Style = [fsBold, fsItalic]
          Width = 70
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'SHOOTSCORE'
          Title.Alignment = taCenter
          Title.Caption = #1057#1090#1088#1077#1083#1100#1073#1072
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -11
          Title.Font.Name = 'MS Sans Serif'
          Title.Font.Style = [fsBold, fsItalic]
          Width = 90
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'SHOOTRANK'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          Title.Caption = #1052#1077#1089#1090#1086
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -11
          Title.Font.Name = 'MS Sans Serif'
          Title.Font.Style = [fsBold]
          Width = 51
          Visible = True
        end>
    end
    object grboxSelectCategory: TGroupBox
      Left = 2
      Top = 225
      Width = 788
      Height = 48
      Align = alTop
      Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1082#1072#1090#1077#1075#1086#1088#1080#1102
      TabOrder = 1
      object lblAvailCategoryFirst: TLabel
        Left = 8
        Top = 20
        Width = 90
        Height = 13
        Caption = #1042#1086#1079#1088#1072#1089#1090#1072' / '#1042#1077#1089#1072' :'
      end
      object lblFightVersionFirst: TLabel
        Left = 296
        Top = 21
        Width = 82
        Height = 13
        Caption = #1041#1086#1077#1074#1072#1103' '#1074#1077#1088#1089#1080#1103' :'
      end
      object cmboxAvailCategory: TComboBox
        Left = 104
        Top = 16
        Width = 185
        Height = 21
        ItemHeight = 13
        TabOrder = 0
        OnChange = changeCompetitorList
      end
      object cmboxFightVersion: TComboBox
        Left = 384
        Top = 16
        Width = 89
        Height = 21
        ItemHeight = 13
        TabOrder = 1
        OnChange = cmboxFightVersionChange
      end
      object chboxFemaleCategory: TCheckBox
        Left = 488
        Top = 18
        Width = 129
        Height = 17
        Caption = #1046#1077#1085#1089#1082#1080#1077' '#1082#1072#1090#1077#1075#1086#1088#1080#1080
        TabOrder = 2
        OnClick = chboxFemaleCategoryClick
      end
      object bbtnPrintCurrentCategory: TBitBtn
        Left = 688
        Top = 16
        Width = 83
        Height = 25
        Caption = #1055#1088#1086#1090#1086#1082#1086#1083
        TabOrder = 3
        OnClick = bbtnPrintCurrentCategoryClick
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000120B0000120B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00555555555555
          5555555FFFFFFFFFF5555550000000000555557777777777F5555550FFFFFFFF
          0555557F5FFFF557F5555550F0000FFF0555557F77775557F5555550FFFFFFFF
          0555557F5FFFFFF7F5555550F000000F0555557F77777757F5555550FFFFFFFF
          0555557F5FFFFFF7F5555550F000000F0555557F77777757F5555550FFFFFFFF
          0555557F5FFF5557F5555550F000FFFF0555557F77755FF7F5555550FFFFF000
          0555557F5FF5777755555550F00FF0F05555557F77557F7555555550FFFFF005
          5555557FFFFF7755555555500000005555555577777775555555555555555555
          5555555555555555555555555555555555555555555555555555}
        NumGlyphs = 2
      end
    end
    object cmboxFightWOKnifeRank: TComboBox
      Left = 384
      Top = 357
      Width = 65
      Height = 28
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ItemHeight = 20
      ParentFont = False
      TabOrder = 2
      OnChange = cmboxFightWOKnifeRankChange
      Items.Strings = (
        ''
        '1'
        '2'
        '3'
        '4'
        '5'
        '6')
    end
    object cmboxFightWKnifeRank: TComboBox
      Left = 384
      Top = 397
      Width = 65
      Height = 28
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ItemHeight = 20
      ParentFont = False
      TabOrder = 3
      OnChange = cmboxFightWKnifeRankChange
      Items.Strings = (
        ''
        '1'
        '2'
        '3'
        '4'
        '5'
        '6')
    end
    object bbtnClose: TBitBtn
      Left = 688
      Top = 440
      Width = 83
      Height = 25
      Cancel = True
      Caption = '&'#1042#1099#1081#1090#1080
      TabOrder = 4
      OnClick = bbtnCloseClick
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00388888888877
        F7F787F8888888888333333F00004444400888FFF444448888888888F333FF8F
        000033334D5007FFF4333388888888883338888F0000333345D50FFFF4333333
        338F888F3338F33F000033334D5D0FFFF43333333388788F3338F33F00003333
        45D50FEFE4333333338F878F3338F33F000033334D5D0FFFF43333333388788F
        3338F33F0000333345D50FEFE4333333338F878F3338F33F000033334D5D0FFF
        F43333333388788F3338F33F0000333345D50FEFE4333333338F878F3338F33F
        000033334D5D0EFEF43333333388788F3338F33F0000333345D50FEFE4333333
        338F878F3338F33F000033334D5D0EFEF43333333388788F3338F33F00003333
        4444444444333333338F8F8FFFF8F33F00003333333333333333333333888888
        8888333F00003333330000003333333333333FFFFFF3333F00003333330AAAA0
        333333333333888888F3333F00003333330000003333333333338FFFF8F3333F
        0000}
      NumGlyphs = 2
    end
    object bbtnEnterResult: TBitBtn
      Left = 560
      Top = 440
      Width = 83
      Height = 25
      Caption = #1047#1072#1087#1080#1089#1072#1090#1100
      TabOrder = 5
      OnClick = bbtnEnterResultClick
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333000000
        000033333377777777773333330FFFFFFFF03FF3FF7FF33F3FF700300000FF0F
        00F077F777773F737737E00BFBFB0FFFFFF07773333F7F3333F7E0BFBF000FFF
        F0F077F3337773F3F737E0FBFBFBF0F00FF077F3333FF7F77F37E0BFBF00000B
        0FF077F3337777737337E0FBFBFBFBF0FFF077F33FFFFFF73337E0BF0000000F
        FFF077FF777777733FF7000BFB00B0FF00F07773FF77373377373330000B0FFF
        FFF03337777373333FF7333330B0FFFF00003333373733FF777733330B0FF00F
        0FF03333737F37737F373330B00FFFFF0F033337F77F33337F733309030FFFFF
        00333377737FFFFF773333303300000003333337337777777333}
      NumGlyphs = 2
    end
    object grboxCompetitorResult: TGroupBox
      Left = 2
      Top = 273
      Width = 788
      Height = 40
      Align = alTop
      Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090#1099' '#1076#1083#1103' '#1091#1095#1072#1089#1090#1085#1080#1082#1072':'
      TabOrder = 6
      object dbtxtSurname: TDBText
        Left = 148
        Top = 10
        Width = 137
        Height = 23
        DataField = 'SURNAME'
        DataSource = dmResultDAO.dsCompetitorToCategoryResult
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object dbtxtName: TDBText
        Left = 300
        Top = 10
        Width = 137
        Height = 23
        DataField = 'NAME'
        DataSource = dmResultDAO.dsCompetitorToCategoryResult
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object dbtxtClubName: TDBText
        Left = 8
        Top = 15
        Width = 137
        Height = 17
        DataField = 'NAME1'
        DataSource = dmResultDAO.dsCompetitorToCategoryResult
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsItalic]
        ParentFont = False
      end
    end
    object cmboxShootRank: TComboBox
      Left = 384
      Top = 320
      Width = 65
      Height = 28
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ItemHeight = 20
      ParentFont = False
      TabOrder = 7
      OnChange = cmboxShootRankChange
      Items.Strings = (
        ''
        '1'
        '2'
        '3'
        '4'
        '5'
        '6')
    end
    object cmboxCommonRank: TComboBox
      Left = 384
      Top = 437
      Width = 65
      Height = 28
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold, fsItalic]
      ItemHeight = 20
      ParentFont = False
      TabOrder = 8
      OnChange = cmboxCommonRankChange
      Items.Strings = (
        ''
        '1'
        '2'
        '3'
        '4'
        '5'
        '6')
    end
    object bbtnAutoCalculateCommonRank: TBitBtn
      Left = 560
      Top = 384
      Width = 209
      Height = 33
      Caption = #1056#1072#1089#1095#1080#1090#1072#1090#1100' '#1084#1077#1089#1090#1072' '#1079#1072' '#1089#1086#1088#1077#1074#1085#1086#1074#1072#1085#1080#1077
      TabOrder = 9
      OnClick = bbtnAutoCalculateCommonRankClick
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00337000000000
        73333337777777773F333308888888880333337F3F3F3FFF7F33330808089998
        0333337F737377737F333308888888880333337F3F3F3F3F7F33330808080808
        0333337F737373737F333308888888880333337F3F3F3F3F7F33330808080808
        0333337F737373737F333308888888880333337F3F3F3F3F7F33330808080808
        0333337F737373737F333308888888880333337F3FFFFFFF7F33330800000008
        0333337F7777777F7F333308000E0E080333337F7FFFFF7F7F33330800000008
        0333337F777777737F333308888888880333337F333333337F33330888888888
        03333373FFFFFFFF733333700000000073333337777777773333}
      NumGlyphs = 2
    end
    object bbtnAtoCalculateShootRank: TBitBtn
      Left = 560
      Top = 336
      Width = 209
      Height = 33
      BiDiMode = bdLeftToRight
      Caption = #1056#1072#1089#1095#1080#1090#1072#1090#1100' '#1084#1077#1089#1090#1072' '#1087#1086' '#1089#1090#1088#1077#1083#1100#1073#1077'        '
      ParentBiDiMode = False
      TabOrder = 10
      OnClick = bbtnAtoCalculateShootRankClick
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00337000000000
        73333337777777773F333308888888880333337F3F3F3FFF7F33330808089998
        0333337F737377737F333308888888880333337F3F3F3F3F7F33330808080808
        0333337F737373737F333308888888880333337F3F3F3F3F7F33330808080808
        0333337F737373737F333308888888880333337F3F3F3F3F7F33330808080808
        0333337F737373737F333308888888880333337F3FFFFFFF7F33330800000008
        0333337F7777777F7F333308000E0E080333337F7FFFFF7F7F33330800000008
        0333337F777777737F333308888888880333337F333333337F33330888888888
        03333373FFFFFFFF733333700000000073333337777777773333}
      NumGlyphs = 2
    end
    object sttxtShootScore: TStaticText
      Left = 464
      Top = 320
      Width = 70
      Height = 24
      Alignment = taCenter
      AutoSize = False
      BevelInner = bvSpace
      BevelKind = bkSoft
      BiDiMode = bdRightToLeftReadingOnly
      Caption = '000000'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentBiDiMode = False
      ParentFont = False
      TabOrder = 11
    end
    object sttxtFightWOKnifeScore: TStaticText
      Left = 464
      Top = 360
      Width = 70
      Height = 24
      Alignment = taCenter
      AutoSize = False
      BevelInner = bvSpace
      BevelKind = bkSoft
      BiDiMode = bdRightToLeftReadingOnly
      Caption = '000000'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentBiDiMode = False
      ParentFont = False
      TabOrder = 12
    end
    object sttxtFightWKnifeScore: TStaticText
      Left = 464
      Top = 400
      Width = 70
      Height = 24
      Alignment = taCenter
      AutoSize = False
      BevelInner = bvSpace
      BevelKind = bkSoft
      BiDiMode = bdRightToLeftReadingOnly
      Caption = '000000'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentBiDiMode = False
      ParentFont = False
      TabOrder = 13
    end
    object sttxtCommonScore: TStaticText
      Left = 464
      Top = 438
      Width = 70
      Height = 24
      Alignment = taCenter
      AutoSize = False
      BevelInner = bvSpace
      BevelKind = bkSoft
      BiDiMode = bdRightToLeftReadingOnly
      Caption = '000000'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold, fsItalic]
      ParentBiDiMode = False
      ParentFont = False
      TabOrder = 14
    end
  end
end
