object frmManualDraw: TfrmManualDraw
  Left = 271
  Top = 184
  Width = 860
  Height = 615
  Caption = #1056#1091#1095#1085#1072#1103' '#1078#1077#1088#1077#1073#1100#1077#1074#1082#1072' '#1091#1095#1072#1089#1090#1085#1080#1082#1086#1074
  Color = clBtnFace
  Constraints.MinHeight = 600
  Constraints.MinWidth = 800
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnResize = FormResize
  OnShow = FormShow
  DesignSize = (
    844
    577)
  PixelsPerInch = 96
  TextHeight = 13
  object lblAvailCategoryFirst: TLabel
    Left = 0
    Top = 555
    Width = 90
    Height = 13
    Anchors = [akLeft, akBottom]
    Caption = #1042#1086#1079#1088#1072#1089#1090#1072' / '#1042#1077#1089#1072' :'
  end
  object lblFightVersionFirst: TLabel
    Left = 288
    Top = 556
    Width = 82
    Height = 13
    Anchors = [akLeft, akBottom]
    Caption = #1041#1086#1077#1074#1072#1103' '#1074#1077#1088#1089#1080#1103' :'
  end
  object grboxTree: TGroupBox
    Left = 296
    Top = 0
    Width = 556
    Height = 545
    Anchors = [akLeft, akTop, akRight, akBottom]
    Caption = #1056#1072#1089#1087#1086#1083#1086#1078#1077#1085#1080#1077' '#1091#1095#1072#1089#1090#1085#1080#1082#1086#1074' '#1074' "'#1076#1077#1088#1077#1074#1077'"'
    TabOrder = 0
  end
  object grboxDrawList: TGroupBox
    Left = 0
    Top = 0
    Width = 297
    Height = 545
    Anchors = [akLeft, akTop, akBottom]
    Caption = #1055#1086#1088#1103#1076#1086#1082' '#1074' '#1078#1077#1088#1077#1073#1100#1077#1074#1082#1077
    TabOrder = 1
    DesignSize = (
      297
      545)
    object bbtnSaveDraw: TBitBtn
      Left = 206
      Top = 512
      Width = 83
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = #1047#1072#1087#1080#1089#1072#1090#1100
      Enabled = False
      TabOrder = 0
      OnClick = bbtnSaveDrawClick
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
  end
  object cmboxAvailCategory: TComboBox
    Left = 96
    Top = 551
    Width = 185
    Height = 21
    Anchors = [akLeft, akBottom]
    ItemHeight = 13
    TabOrder = 2
    OnChange = changeCompetitorList
  end
  object cmboxFightVersion: TComboBox
    Left = 376
    Top = 551
    Width = 89
    Height = 21
    Anchors = [akLeft, akBottom]
    ItemHeight = 13
    TabOrder = 3
    OnChange = cmboxFightVersionChange
  end
  object chboxFemaleCategory: TCheckBox
    Left = 472
    Top = 553
    Width = 129
    Height = 17
    Anchors = [akLeft, akBottom]
    Caption = #1046#1077#1085#1089#1082#1080#1077' '#1082#1072#1090#1077#1075#1086#1088#1080#1080
    TabOrder = 4
    OnClick = chboxFemaleCategoryClick
  end
  object bbtnClose: TBitBtn
    Left = 756
    Top = 551
    Width = 83
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = '&'#1042#1099#1081#1090#1080
    TabOrder = 5
    Kind = bkClose
  end
end
