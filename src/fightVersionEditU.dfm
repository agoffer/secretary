object frmFightVersionEdit: TfrmFightVersionEdit
  Left = 368
  Top = 263
  BorderStyle = bsDialog
  Caption = #1056#1077#1076#1072#1082#1090#1086#1088' '#1073#1086#1077#1074#1086#1081' '#1074#1077#1088#1089#1080#1080
  ClientHeight = 204
  ClientWidth = 401
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
  object lblComments: TLabel
    Left = 8
    Top = 88
    Width = 70
    Height = 13
    Caption = #1050#1086#1084#1084#1077#1085#1090#1072#1088#1080#1080
  end
  object lbledtCode: TLabeledEdit
    Left = 110
    Top = 8
    Width = 153
    Height = 21
    EditLabel.Width = 97
    EditLabel.Height = 13
    EditLabel.Caption = #1050#1086#1076' '#1073#1086#1077#1074#1086#1081' '#1074#1077#1088#1089#1080#1080
    LabelPosition = lpLeft
    LabelSpacing = 3
    TabOrder = 0
  end
  object lbledtDescription: TLabeledEdit
    Left = 8
    Top = 56
    Width = 297
    Height = 21
    EditLabel.Width = 128
    EditLabel.Height = 13
    EditLabel.Caption = #1054#1087#1080#1089#1072#1085#1080#1077' '#1073#1086#1077#1074#1086#1081' '#1074#1077#1088#1089#1080#1080
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 1
  end
  object memComments: TMemo
    Left = 8
    Top = 104
    Width = 385
    Height = 89
    TabOrder = 2
  end
  object bbtnUpdateFightVersion: TBitBtn
    Left = 320
    Top = 16
    Width = 75
    Height = 25
    TabOrder = 3
    Kind = bkOK
  end
  object bbtnCancelFightVersion: TBitBtn
    Left = 320
    Top = 56
    Width = 75
    Height = 25
    TabOrder = 4
    Kind = bkCancel
  end
end
