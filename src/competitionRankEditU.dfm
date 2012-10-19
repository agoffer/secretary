object frmCompetitionRankEdit: TfrmCompetitionRankEdit
  Left = 278
  Top = 149
  BorderStyle = bsDialog
  Caption = #1056#1077#1076#1072#1082#1090#1086#1088' '#1089#1090#1072#1090#1091#1089#1072' '#1089#1086#1088#1077#1074#1085#1086#1074#1072#1085#1080#1103
  ClientHeight = 368
  ClientWidth = 802
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
  object lblHint: TLabel
    Left = 0
    Top = 329
    Width = 802
    Height = 13
    Align = alTop
    Caption = '  '#1055#1056#1048#1052#1045#1063#1040#1053#1048#1045': '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblHintDetail: TLabel
    Left = 0
    Top = 342
    Width = 802
    Height = 13
    Align = alTop
    Caption = 
      '  '#1044#1072#1085#1085#1099#1077' '#1074' '#1090#1072#1073#1083#1080#1094#1072#1093' '#1084#1086#1078#1085#1086' '#1080#1079#1084#1077#1085#1103#1090#1100'. '#1053#1086#1074#1072#1103' '#1079#1072#1087#1080#1089#1100' '#1076#1086#1073#1072#1074#1083#1103#1077#1090#1089#1103' '#1074' '#1082 +
      #1086#1085#1077#1094' '#1090#1072#1073#1083#1080#1094#1099'. '#1044#1083#1103' '#1091#1076#1072#1083#1077#1085#1080#1103' '#1090#1077#1082#1091#1097#1077#1081' '#1079#1072#1087#1080#1089#1080' - DEL'
  end
  object bbtnUpdateCompetitionRank: TBitBtn
    Left = 723
    Top = 336
    Width = 75
    Height = 25
    TabOrder = 0
    OnClick = bbtnUpdateCompetitionRankClick
    Kind = bkOK
  end
  object grboxCompetitionRank: TGroupBox
    Left = 0
    Top = 0
    Width = 802
    Height = 177
    Align = alTop
    Caption = #1056#1077#1076#1072#1082#1090#1086#1088' '#1089#1090#1072#1090#1091#1089#1086#1074' '#1089#1086#1088#1077#1074#1085#1086#1074#1072#1085#1080#1081
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    object dbgCompetitionRank: TDBGrid
      Left = 2
      Top = 18
      Width = 798
      Height = 157
      Align = alClient
      DataSource = dmCompetitionRankDAO.dsCompetitionRankTable
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit]
      ParentFont = False
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -13
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = [fsBold]
      OnKeyUp = dbgCompetitionRankKeyUp
      Columns = <
        item
          Expanded = False
          FieldName = 'DESCRIPTION'
          Title.Caption = #1057#1090#1072#1090#1091#1089' '#1089#1086#1088#1077#1074#1085#1086#1074#1072#1085#1080#1103
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -13
          Title.Font.Name = 'Arial'
          Title.Font.Style = [fsBold]
          Width = 300
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'COMMENTS'
          Title.Caption = #1055#1088#1080#1084#1077#1095#1072#1085#1080#1077
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -13
          Title.Font.Name = 'Arial'
          Title.Font.Style = [fsBold]
          Width = 454
          Visible = True
        end>
    end
  end
  object grboxRankScoring: TGroupBox
    Left = 0
    Top = 177
    Width = 802
    Height = 152
    Align = alTop
    Caption = #1056#1077#1076#1072#1082#1090#1086#1088' '#1088#1072#1089#1087#1088#1077#1076#1077#1083#1077#1085#1080#1103' '#1073#1072#1083#1086#1074' '#1087#1086' '#1084#1077#1089#1090#1072#1084
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    object dbgrScoreRanking: TDBGrid
      Left = 2
      Top = 18
      Width = 798
      Height = 132
      Align = alClient
      DataSource = dmCompetitionRankDAO.dsrcScoreRanking
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -13
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = [fsBold]
      OnKeyUp = dbgrScoreRankingKeyUp
      Columns = <
        item
          Expanded = False
          FieldName = 'RANK'
          Title.Caption = #1047#1072#1085#1080#1084#1072#1077#1084#1086#1077' '#1084#1077#1089#1090#1086
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -13
          Title.Font.Name = 'Arial'
          Title.Font.Style = [fsBold]
          Width = 301
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'SCORE'
          Title.Caption = #1053#1072#1095#1080#1089#1083#1103#1077#1084#1099#1077' '#1073#1072#1083#1099
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -13
          Title.Font.Name = 'Arial'
          Title.Font.Style = [fsBold]
          Width = 453
          Visible = True
        end>
    end
  end
end
