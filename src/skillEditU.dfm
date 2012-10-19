object frmSkillEdit: TfrmSkillEdit
  Left = 851
  Top = 247
  BorderStyle = bsDialog
  Caption = #1056#1077#1076#1072#1082#1090#1086#1088' '#1091#1088#1086#1074#1085#1103' '#1084#1072#1089#1090#1077#1088#1089#1090#1074#1072
  ClientHeight = 234
  ClientWidth = 340
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
  object lblWeight: TLabel
    Left = 8
    Top = 90
    Width = 115
    Height = 13
    Caption = #1042#1077#1089#1086#1074#1086#1081' '#1082#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090
  end
  object lblComments: TLabel
    Left = 8
    Top = 120
    Width = 70
    Height = 13
    Caption = #1050#1086#1084#1084#1077#1085#1090#1072#1088#1080#1080
  end
  object lbledtShortDescription: TLabeledEdit
    Left = 120
    Top = 8
    Width = 121
    Height = 21
    EditLabel.Width = 110
    EditLabel.Height = 13
    EditLabel.Caption = #1050#1088#1072#1090#1082#1086#1077' '#1086#1073#1086#1079#1085#1072#1095#1077#1085#1080#1077
    LabelPosition = lpLeft
    LabelSpacing = 3
    TabOrder = 0
  end
  object lbledtFullDescription: TLabeledEdit
    Left = 8
    Top = 56
    Width = 241
    Height = 21
    EditLabel.Width = 106
    EditLabel.Height = 13
    EditLabel.Caption = #1055#1086#1083#1085#1086#1077' '#1086#1073#1086#1079#1085#1072#1095#1077#1085#1080#1077
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 1
  end
  object medtWeight: TMaskEdit
    Left = 128
    Top = 88
    Width = 40
    Height = 21
    EditMask = '999;1; '
    MaxLength = 3
    TabOrder = 2
    Text = '   '
  end
  object memComments: TMemo
    Left = 8
    Top = 136
    Width = 321
    Height = 89
    TabOrder = 3
  end
  object bbtnUpdateSkill: TBitBtn
    Left = 256
    Top = 8
    Width = 75
    Height = 25
    TabOrder = 4
    Kind = bkOK
  end
  object bbtnCancelSkill: TBitBtn
    Left = 256
    Top = 48
    Width = 75
    Height = 25
    TabOrder = 5
    Kind = bkCancel
  end
end
