object frmClubEdit: TfrmClubEdit
  Left = 328
  Top = 222
  BorderStyle = bsDialog
  Caption = #1056#1077#1076#1072#1082#1090#1086#1088' '#1086#1088#1075#1072#1085#1080#1079#1072#1094#1080#1080
  ClientHeight = 318
  ClientWidth = 628
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
  object lblClubAdditions: TLabel
    Left = 1
    Top = 168
    Width = 156
    Height = 13
    Caption = #1044#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1072#1103' '#1080#1085#1092#1086#1088#1084#1072#1094#1080#1103':'
  end
  object lbledtClubName: TLabeledEdit
    Left = 1
    Top = 24
    Width = 273
    Height = 21
    EditLabel.Width = 79
    EditLabel.Height = 13
    EditLabel.Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 0
  end
  object lbledtClubCountry: TLabeledEdit
    Left = 1
    Top = 144
    Width = 273
    Height = 21
    EditLabel.Width = 39
    EditLabel.Height = 13
    EditLabel.Caption = #1057#1090#1088#1072#1085#1072':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 3
  end
  object lbledtClubCity: TLabeledEdit
    Left = 1
    Top = 104
    Width = 273
    Height = 21
    EditLabel.Width = 33
    EditLabel.Height = 13
    EditLabel.Caption = #1043#1086#1088#1086#1076':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 2
  end
  object memClubAdditions: TMemo
    Left = 1
    Top = 184
    Width = 273
    Height = 129
    TabOrder = 4
  end
  object grboxRepresentative: TGroupBox
    Left = 280
    Top = 0
    Width = 345
    Height = 257
    Caption = #1055#1088#1077#1076#1089#1090#1072#1074#1080#1090#1077#1083#1100
    TabOrder = 7
    object dbgrdPersonList: TDBGrid
      Left = 10
      Top = 15
      Width = 325
      Height = 178
      DataSource = dmPersonDAO.dsPersonTable
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
          ReadOnly = True
          Title.Caption = #1060#1072#1084#1080#1083#1080#1103
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'NAME'
          ReadOnly = True
          Title.Caption = #1048#1084#1103
          Width = 46
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'PATRONYMIC'
          ReadOnly = True
          Title.Caption = #1054#1090#1095#1077#1089#1090#1074#1086
          Width = 59
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'PHONE'
          ReadOnly = True
          Title.Caption = #1058#1077#1083#1077#1092#1086#1085
          Visible = True
        end>
    end
    object lbledtPersonQuickSearch: TLabeledEdit
      Left = 8
      Top = 216
      Width = 249
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
      Left = 264
      Top = 214
      Width = 75
      Height = 25
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100'...'
      TabOrder = 2
      OnClick = btnAddPersonClick
    end
  end
  object bbtnUpdateClub: TBitBtn
    Left = 352
    Top = 280
    Width = 75
    Height = 25
    TabOrder = 5
    Kind = bkOK
  end
  object bbtnCancelClub: TBitBtn
    Left = 496
    Top = 280
    Width = 75
    Height = 25
    TabOrder = 6
    Kind = bkCancel
  end
  object lbledtClubShortName: TLabeledEdit
    Left = 1
    Top = 64
    Width = 273
    Height = 21
    EditLabel.Width = 151
    EditLabel.Height = 13
    EditLabel.Caption = #1050#1086#1088#1086#1090#1082#1086#1077' '#1085#1072#1079#1074#1072#1085#1080#1077' '#1082#1086#1084#1072#1085#1076#1099':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    MaxLength = 15
    TabOrder = 1
  end
end
