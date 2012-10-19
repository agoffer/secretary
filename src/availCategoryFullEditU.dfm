object frmAvailCategoryFullEdit: TfrmAvailCategoryFullEdit
  Left = 388
  Top = 284
  BorderStyle = bsDialog
  Caption = #1056#1077#1076#1072#1082#1090#1086#1088' '#1076#1086#1087#1091#1089#1090#1080#1084#1099#1093' '#1082#1072#1090#1077#1075#1086#1088#1080#1081
  ClientHeight = 323
  ClientWidth = 566
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object grboxAvailCategory: TGroupBox
    Left = 0
    Top = 0
    Width = 566
    Height = 185
    Align = alTop
    Caption = #1044#1086#1087#1091#1089#1090#1080#1084#1099#1077' '#1082#1072#1090#1077#1075#1086#1088#1080#1080
    TabOrder = 0
    object lblSearchAge: TLabel
      Left = 8
      Top = 152
      Width = 45
      Height = 13
      Caption = #1042#1086#1079#1088#1072#1089#1090':'
    end
    object lblSearchWeight: TLabel
      Left = 240
      Top = 152
      Width = 22
      Height = 13
      Caption = #1042#1077#1089':'
    end
    object dbgrAvailCategories: TDBGrid
      Left = 8
      Top = 17
      Width = 545
      Height = 120
      DataSource = dmAvailCategoryDAO.dsAvailCategoryTable
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      Columns = <
        item
          Expanded = False
          FieldName = 'STARTAGE'
          Title.Caption = #1053#1072#1095#1072#1083#1100#1085#1099#1081' '#1074#1086#1079#1088#1072#1089#1090
          Width = 123
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ENDAGE'
          Title.Caption = #1050#1086#1085#1077#1095#1085#1099#1081' '#1074#1086#1079#1088#1072#1089#1090
          Width = 116
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'STARTWEIGHT'
          Title.Caption = #1053#1072#1095#1072#1083#1100#1085#1099#1081' '#1042#1077#1089
          Width = 105
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ENDWEIGHT'
          Title.Caption = #1050#1086#1085#1077#1095#1085#1099#1081' '#1074#1077#1089
          Width = 107
          Visible = True
        end>
    end
    object mskedtEndAge: TMaskEdit
      Left = 104
      Top = 144
      Width = 33
      Height = 21
      EditMask = '!999;1; '
      MaxLength = 3
      TabOrder = 2
      Text = '   '
    end
    object mskedtEndWeight: TMaskEdit
      Left = 360
      Top = 144
      Width = 33
      Height = 21
      EditMask = '!999,9;1; '
      MaxLength = 5
      TabOrder = 4
      Text = '   , '
    end
    object mskedtStartAge: TMaskEdit
      Left = 56
      Top = 144
      Width = 33
      Height = 21
      EditMask = '!999;1; '
      MaxLength = 3
      TabOrder = 1
      Text = '   '
    end
    object mskedtStartWeight: TMaskEdit
      Left = 280
      Top = 144
      Width = 33
      Height = 21
      EditMask = '!999,9;1; '
      MaxLength = 5
      TabOrder = 3
      Text = '   , '
    end
    object bbtnDeleteAvailCategory: TBitBtn
      Left = 480
      Top = 146
      Width = 75
      Height = 25
      Caption = #1059#1076#1072#1083#1080#1090#1100
      TabOrder = 5
      Kind = bkCancel
    end
  end
  object grboxAddNewAvailCategory: TGroupBox
    Left = 0
    Top = 185
    Width = 566
    Height = 138
    Align = alClient
    Caption = #1044#1086#1073#1072#1074#1083#1077#1085#1080#1077' '#1085#1086#1074#1086#1081' '#1082#1072#1090#1077#1075#1086#1088#1080#1080
    TabOrder = 1
    object grboxWeightRange: TGroupBox
      Left = 8
      Top = 82
      Width = 201
      Height = 49
      Caption = #1042#1077#1089#1086#1074#1086#1081' '#1076#1080#1072#1087#1072#1079#1086#1085
      TabOrder = 0
      object lblStartWeight: TLabel
        Left = 24
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
      end
    end
    object grboxAgeRange: TGroupBox
      Left = 8
      Top = 26
      Width = 201
      Height = 49
      Caption = #1042#1086#1079#1088#1072#1089#1090#1085#1086#1081' '#1076#1080#1072#1087#1072#1079#1086#1085
      TabOrder = 1
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
    object bbtnAddNew: TBitBtn
      Left = 472
      Top = 34
      Width = 83
      Height = 25
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      Default = True
      ModalResult = 1
      TabOrder = 2
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
    object grboxComments: TGroupBox
      Left = 216
      Top = 24
      Width = 241
      Height = 81
      Caption = #1050#1086#1084#1084#1077#1085#1090#1072#1088#1080#1080
      TabOrder = 3
      object memComments: TMemo
        Left = 2
        Top = 15
        Width = 237
        Height = 64
        Align = alClient
        TabOrder = 0
      end
    end
    object bbtnClose: TBitBtn
      Left = 472
      Top = 80
      Width = 83
      Height = 25
      Caption = #1042#1099#1081#1090#1080
      TabOrder = 4
      Kind = bkClose
    end
    object chboxMaleFemale: TCheckBox
      Left = 216
      Top = 112
      Width = 241
      Height = 17
      Caption = #1046#1077#1085#1089#1082#1072#1103' '#1082#1072#1090#1077#1075#1086#1088#1080#1103
      TabOrder = 5
    end
  end
end
