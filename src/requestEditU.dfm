object frmRequestEdit: TfrmRequestEdit
  Left = 152
  Top = 248
  BorderStyle = bsDialog
  Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100' '#1079#1072#1103#1074#1082#1091
  ClientHeight = 312
  ClientWidth = 692
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnClose = FormClose
  OnPaint = lbledtPersonQuickSearchChange
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object lblRequestComments: TLabel
    Left = 8
    Top = 192
    Width = 128
    Height = 13
    Caption = #1050#1086#1084#1084#1077#1085#1090#1072#1088#1080#1080' '#1080' '#1079#1072#1084#1077#1090#1082#1080':'
  end
  object grboxClub: TGroupBox
    Left = 0
    Top = 0
    Width = 345
    Height = 185
    Caption = #1055#1086#1076#1072#1090#1077#1083#1100' '#1079#1072#1103#1074#1082#1080
    TabOrder = 0
    object dbgrdClubList: TDBGrid
      Left = 10
      Top = 15
      Width = 325
      Height = 122
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ReadOnly = True
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      OnTitleClick = dbgrdClubListTitleClick
      Columns = <
        item
          Expanded = False
          FieldName = 'NAME'
          Title.Caption = #1054#1088#1075#1072#1085#1080#1079#1072#1094#1080#1103
          Width = 84
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'CITY'
          Title.Caption = #1043#1086#1088#1086#1076
          Width = 114
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'COUNTRY'
          Title.Caption = #1057#1090#1088#1072#1085#1072
          Width = 110
          Visible = True
        end>
    end
    object lbledtClubQuickSearch: TLabeledEdit
      Left = 8
      Top = 155
      Width = 225
      Height = 21
      EditLabel.Width = 103
      EditLabel.Height = 13
      EditLabel.Caption = #1055#1086#1080#1089#1082' '#1087#1086' '#1085#1072#1079#1074#1072#1085#1080#1102':'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 1
      OnChange = lbledtClubQuickSearchChange
    end
    object btnAddClub: TButton
      Left = 256
      Top = 152
      Width = 75
      Height = 25
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100'...'
      TabOrder = 2
      OnClick = btnAddClubClick
    end
  end
  object grboxRepresentative: TGroupBox
    Left = 346
    Top = 0
    Width = 345
    Height = 185
    Caption = #1055#1088#1077#1076#1089#1090#1072#1074#1080#1090#1077#1083#1100
    TabOrder = 1
    object dbgrdPersonList: TDBGrid
      Left = 10
      Top = 16
      Width = 325
      Height = 120
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ReadOnly = True
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      OnTitleClick = dbgrdPersonListTitleClick
      Columns = <
        item
          Expanded = False
          FieldName = 'SURNAME'
          Title.Caption = #1060#1072#1084#1080#1083#1080#1103
          Width = 69
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'NAME'
          Title.Caption = #1048#1084#1103
          Width = 75
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'PATRONYMIC'
          Title.Caption = #1054#1090#1095#1077#1089#1090#1074#1086
          Width = 82
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'PHONE'
          Title.Caption = #1058#1077#1083#1077#1092#1086#1085
          Visible = True
        end>
    end
    object lbledtPersonQuickSearch: TLabeledEdit
      Left = 8
      Top = 155
      Width = 225
      Height = 21
      EditLabel.Width = 99
      EditLabel.Height = 13
      EditLabel.Caption = #1055#1086#1080#1089#1082' '#1087#1086' '#1092#1072#1084#1080#1083#1080#1080':'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 1
      OnChange = lbledtPersonQuickSearchChange
    end
    object btnAddPerson: TButton
      Left = 256
      Top = 152
      Width = 75
      Height = 25
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100'...'
      TabOrder = 2
      OnClick = btnAddPersonClick
    end
  end
  object memRequestComments: TMemo
    Left = 8
    Top = 208
    Width = 537
    Height = 89
    TabOrder = 2
  end
  object bbtnUpdateRequest: TBitBtn
    Left = 584
    Top = 216
    Width = 75
    Height = 25
    TabOrder = 3
    Kind = bkOK
  end
  object bbtnCancelRequest: TBitBtn
    Left = 584
    Top = 256
    Width = 75
    Height = 25
    TabOrder = 4
    Kind = bkCancel
  end
end
