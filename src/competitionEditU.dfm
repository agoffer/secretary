object frmCompetitionEdit: TfrmCompetitionEdit
  Left = 445
  Top = 338
  BorderStyle = bsDialog
  Caption = #1056#1077#1076#1072#1082#1090#1086#1088' '#1089#1086#1088#1077#1074#1085#1086#1074#1072#1085#1080#1103
  ClientHeight = 247
  ClientWidth = 410
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnHide = FormHide
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object lblBeginCompetitionDate: TLabel
    Left = 8
    Top = 8
    Width = 183
    Height = 19
    Caption = #1044#1072#1090#1072' '#1085#1072#1095#1072#1083#1072' '#1089#1086#1088#1077#1074#1085#1086#1074#1072#1085#1080#1103':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object lblEndCompetitionDate: TLabel
    Left = 8
    Top = 44
    Width = 209
    Height = 19
    Caption = #1044#1072#1090#1072' '#1086#1082#1086#1085#1095#1072#1085#1080#1103' '#1089#1086#1088#1077#1074#1085#1086#1074#1072#1085#1080#1103':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object lblCompetitionComments: TLabel
    Left = 8
    Top = 76
    Width = 97
    Height = 19
    Caption = #1050#1086#1084#1084#1077#1085#1090#1072#1088#1080#1080':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object lblCompetitionRank: TLabel
    Left = 8
    Top = 188
    Width = 240
    Height = 19
    Caption = #1057#1090#1072#1090#1091#1089' '#1087#1088#1086#1074#1086#1076#1080#1084#1099#1093' '#1089#1086#1088#1077#1074#1085#1086#1074#1072#1085#1080#1081':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object dtpBeginCompetitionDate: TDateTimePicker
    Left = 224
    Top = 4
    Width = 98
    Height = 23
    CalAlignment = dtaLeft
    Date = 38678.9833691319
    Time = 38678.9833691319
    DateFormat = dfShort
    DateMode = dmComboBox
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = [fsBold]
    Kind = dtkDate
    ParseInput = False
    ParentFont = False
    TabOrder = 0
  end
  object dtpEndCompetitionDate: TDateTimePicker
    Left = 224
    Top = 40
    Width = 97
    Height = 23
    CalAlignment = dtaLeft
    Date = 38678.9835228472
    Time = 38678.9835228472
    DateFormat = dfShort
    DateMode = dmComboBox
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = [fsBold]
    Kind = dtkDate
    ParseInput = False
    ParentFont = False
    TabOrder = 1
  end
  object memCompetitionComments: TMemo
    Left = 8
    Top = 104
    Width = 393
    Height = 73
    Lines.Strings = (
      '')
    TabOrder = 2
  end
  object bbtnUpdateCompetition: TBitBtn
    Left = 328
    Top = 8
    Width = 75
    Height = 25
    TabOrder = 4
    Kind = bkOK
  end
  object bbtnCancelCompetition: TBitBtn
    Left = 328
    Top = 40
    Width = 75
    Height = 25
    TabOrder = 5
    Kind = bkCancel
  end
  object cmboxCompetitionRank: TComboBox
    Left = 8
    Top = 216
    Width = 393
    Height = 21
    ItemHeight = 13
    TabOrder = 3
  end
end
