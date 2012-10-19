object frmAvailCategoryEdit: TfrmAvailCategoryEdit
  Left = 333
  Top = 185
  BorderStyle = bsDialog
  Caption = #1056#1077#1076#1072#1082#1090#1086#1088' '#1076#1086#1087#1091#1089#1090#1080#1084#1086#1081' '#1082#1072#1090#1077#1075#1086#1088#1080#1080
  ClientHeight = 231
  ClientWidth = 310
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object rdgrpGender: TRadioGroup
    Left = 0
    Top = 96
    Width = 201
    Height = 49
    Caption = #1055#1086#1083' '#1091#1095#1072#1089#1090#1085#1080#1082#1072
    Columns = 2
    ItemIndex = 0
    Items.Strings = (
      #1052#1091#1078#1089#1082#1086#1081
      #1046#1077#1085#1089#1082#1080#1081)
    TabOrder = 0
  end
  object grboxWeightRange: TGroupBox
    Left = 0
    Top = 0
    Width = 201
    Height = 49
    Caption = #1042#1077#1089#1086#1074#1086#1081' '#1076#1080#1072#1087#1072#1079#1086#1085
    TabOrder = 1
    object lblStartWeight: TLabel
      Left = 8
      Top = 20
      Width = 36
      Height = 13
      Caption = #1042#1077#1089' '#1086#1090':'
    end
    object lblEndWeight: TLabel
      Left = 122
      Top = 20
      Width = 15
      Height = 13
      Caption = #1076#1086':'
    end
    object medtStartWeight: TMaskEdit
      Left = 78
      Top = 16
      Width = 32
      Height = 25
      EditMask = '!999,9;1; '
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Times New Roman'
      Font.Style = []
      MaxLength = 5
      ParentFont = False
      TabOrder = 0
      Text = '   , '
      OnExit = medtStartWeightExit
    end
    object medtEndWeight: TMaskEdit
      Left = 142
      Top = 16
      Width = 33
      Height = 25
      EditMask = '!999,9;1; '
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Times New Roman'
      Font.Style = []
      MaxLength = 5
      ParentFont = False
      TabOrder = 1
      Text = '   , '
      OnExit = medtEndWeightExit
    end
  end
  object grboxAgeRange: TGroupBox
    Left = 0
    Top = 48
    Width = 201
    Height = 49
    Caption = #1042#1086#1079#1088#1072#1089#1090#1085#1086#1081' '#1076#1080#1072#1087#1072#1079#1086#1085
    TabOrder = 2
    object lblStartAge: TLabel
      Left = 8
      Top = 20
      Width = 59
      Height = 13
      Caption = #1042#1086#1079#1088#1072#1089#1090' '#1086#1090':'
    end
    object lblEndAge: TLabel
      Left = 122
      Top = 20
      Width = 15
      Height = 13
      Caption = #1076#1086':'
    end
    object medtStartAge: TMaskEdit
      Left = 80
      Top = 16
      Width = 32
      Height = 25
      EditMask = '!999;1; '
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Times New Roman'
      Font.Style = []
      MaxLength = 3
      ParentFont = False
      TabOrder = 0
      Text = '   '
    end
    object medtEndAge: TMaskEdit
      Left = 142
      Top = 16
      Width = 33
      Height = 25
      EditMask = '!999;1; '
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Times New Roman'
      Font.Style = []
      MaxLength = 3
      ParentFont = False
      TabOrder = 1
      Text = '   '
    end
  end
  object bbtnUpdate: TBitBtn
    Left = 216
    Top = 24
    Width = 75
    Height = 25
    TabOrder = 3
    Kind = bkOK
  end
  object bbtnCancel: TBitBtn
    Left = 216
    Top = 96
    Width = 75
    Height = 25
    TabOrder = 4
    Kind = bkCancel
  end
  object grboxComments: TGroupBox
    Left = 0
    Top = 144
    Width = 305
    Height = 81
    Caption = #1050#1086#1084#1084#1077#1085#1090#1072#1088#1080#1080
    TabOrder = 5
    object memComments: TMemo
      Left = 2
      Top = 15
      Width = 301
      Height = 64
      Align = alClient
      TabOrder = 0
    end
  end
end
