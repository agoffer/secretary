object frmPersonEdit: TfrmPersonEdit
  Left = 437
  Top = 224
  BorderStyle = bsDialog
  Caption = #1056#1077#1076#1072#1082#1090#1086#1088' '#1089#1091#1073#1098#1077#1082#1090#1072
  ClientHeight = 332
  ClientWidth = 280
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
  object lblDOB: TLabel
    Left = 8
    Top = 120
    Width = 82
    Height = 13
    Caption = #1044#1072#1090#1072' '#1088#1086#1078#1076#1077#1085#1080#1103':'
  end
  object lblAdditions: TLabel
    Left = 8
    Top = 192
    Width = 156
    Height = 13
    Caption = #1044#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1072#1103' '#1080#1085#1092#1086#1088#1084#1072#1094#1080#1103':'
  end
  object lbledtSurname: TLabeledEdit
    Left = 8
    Top = 16
    Width = 265
    Height = 21
    EditLabel.Width = 52
    EditLabel.Height = 13
    EditLabel.Caption = #1060#1072#1084#1080#1083#1080#1103':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 0
  end
  object lbledtName: TLabeledEdit
    Left = 8
    Top = 56
    Width = 265
    Height = 21
    EditLabel.Width = 25
    EditLabel.Height = 13
    EditLabel.Caption = #1048#1084#1103':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 1
  end
  object lbledtPatronymic: TLabeledEdit
    Left = 8
    Top = 96
    Width = 265
    Height = 21
    EditLabel.Width = 50
    EditLabel.Height = 13
    EditLabel.Caption = #1054#1090#1095#1077#1089#1090#1074#1086':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 2
  end
  object lbledtPhone: TLabeledEdit
    Left = 136
    Top = 136
    Width = 137
    Height = 21
    EditLabel.Width = 48
    EditLabel.Height = 13
    EditLabel.Caption = #1058#1077#1083#1077#1092#1086#1085':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 3
  end
  object dtpDOB: TDateTimePicker
    Left = 8
    Top = 136
    Width = 113
    Height = 21
    CalAlignment = dtaLeft
    Date = 38682.6809266319
    Time = 38682.6809266319
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 4
  end
  object memAdditions: TMemo
    Left = 8
    Top = 208
    Width = 265
    Height = 81
    TabOrder = 6
  end
  object bbtnUpdatePerson: TBitBtn
    Left = 32
    Top = 296
    Width = 75
    Height = 25
    TabOrder = 7
    Kind = bkOK
  end
  object bbtnCancelPerson: TBitBtn
    Left = 176
    Top = 296
    Width = 75
    Height = 25
    TabOrder = 8
    Kind = bkCancel
  end
  object chboxFemale: TCheckBox
    Left = 8
    Top = 165
    Width = 97
    Height = 17
    Caption = #1055#1086#1083' '#1078#1077#1085#1089#1082#1080#1081
    TabOrder = 5
  end
end
