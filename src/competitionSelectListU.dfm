object frmCompetitionSelectList: TfrmCompetitionSelectList
  Left = 224
  Top = 210
  BorderStyle = bsDialog
  Caption = #1057#1087#1080#1089#1086#1082' '#1089#1086#1088#1077#1074#1085#1086#1074#1072#1085#1080#1081
  ClientHeight = 205
  ClientWidth = 655
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
  object lblBeginDate: TLabel
    Left = 456
    Top = 8
    Width = 124
    Height = 13
    Caption = #1053#1072#1095#1072#1083#1086' '#1089#1086#1088#1077#1074#1085#1086#1074#1072#1085#1080#1103' '#1089':'
  end
  object lblEndDate: TLabel
    Left = 456
    Top = 72
    Width = 130
    Height = 13
    Caption = #1053#1072#1095#1072#1083#1086' '#1089#1086#1088#1077#1074#1085#1086#1074#1072#1085#1080#1103' '#1076#1086':'
  end
  object dbgrdCompetitionList: TDBGrid
    Left = 0
    Top = 0
    Width = 449
    Height = 205
    Align = alLeft
    DataSource = dmCompetitionDAO.dsExtendedCompetitionTable
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ReadOnly = True
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'BEGINDATE'
        Title.Caption = #1044#1072#1090#1072' '#1085#1072#1095#1072#1083#1072
        Width = 79
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'ENDDATE'
        Title.Caption = #1044#1072#1090#1072' '#1086#1082#1086#1085#1095#1072#1085#1080#1103
        Width = 92
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'DESCRIPTION'
        Title.Caption = #1057#1090#1072#1090#1091#1089' '#1089#1086#1088#1077#1074#1085#1086#1074#1072#1085#1080#1103
        Width = 200
        Visible = True
      end>
  end
  object dtpBeginDate: TDateTimePicker
    Left = 456
    Top = 32
    Width = 98
    Height = 21
    CalAlignment = dtaLeft
    Date = 38704.8637215972
    Time = 38704.8637215972
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 1
    OnChange = dtpDateChange
  end
  object dtpEndDate: TDateTimePicker
    Left = 456
    Top = 96
    Width = 97
    Height = 21
    CalAlignment = dtaLeft
    Date = 38704.8637404051
    Time = 38704.8637404051
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 2
    OnChange = dtpDateChange
  end
  object bbtnSelect: TBitBtn
    Left = 456
    Top = 168
    Width = 75
    Height = 25
    TabOrder = 3
    Kind = bkOK
  end
  object bbtnCancel: TBitBtn
    Left = 576
    Top = 168
    Width = 75
    Height = 25
    TabOrder = 4
    Kind = bkCancel
  end
  object bbtnDeleteCompetition: TBitBtn
    Left = 520
    Top = 128
    Width = 75
    Height = 25
    Caption = #1059#1076#1072#1083#1080#1090#1100
    TabOrder = 5
    OnClick = bbtnDeleteCompetitionClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000120B0000120B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333000000000
      3333333777777777F3333330F777777033333337F3F3F3F7F3333330F0808070
      33333337F7F7F7F7F3333330F080707033333337F7F7F7F7F3333330F0808070
      33333337F7F7F7F7F3333330F080707033333337F7F7F7F7F3333330F0808070
      333333F7F7F7F7F7F3F33030F080707030333737F7F7F7F7F7333300F0808070
      03333377F7F7F7F773333330F080707033333337F7F7F7F7F333333070707070
      33333337F7F7F7F7FF3333000000000003333377777777777F33330F88877777
      0333337FFFFFFFFF7F3333000000000003333377777777777333333330777033
      3333333337FFF7F3333333333000003333333333377777333333}
    NumGlyphs = 2
  end
end
