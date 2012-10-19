object frmResultEnterEdit: TfrmResultEnterEdit
  Left = 416
  Top = 239
  BorderStyle = bsDialog
  Caption = #1042#1074#1086#1076' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1086#1074
  ClientHeight = 412
  ClientWidth = 572
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object grboxCompetitorSearch: TGroupBox
    Left = 0
    Top = 0
    Width = 572
    Height = 321
    Align = alTop
    Caption = #1055#1086#1080#1089#1082' '#1091#1095#1072#1089#1090#1085#1080#1082#1072' '
    TabOrder = 0
    object dbgrdCompetitorList: TDBGrid
      Left = 2
      Top = 15
      Width = 568
      Height = 146
      Align = alTop
      DataSource = dmCompetitorDAO.dsCompetitorExtended
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
          FieldName = 'SURNAME'
          Title.Caption = #1060#1072#1084#1080#1083#1080#1103
          Width = 95
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'PERS_NAME'
          Title.Caption = #1048#1084#1103
          Width = 72
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'PATRONYMIC'
          Title.Caption = #1054#1090#1095#1077#1089#1090#1074#1086
          Width = 95
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'SHORTNAME'
          Title.Caption = #1050#1086#1084#1072#1085#1076#1072
          Width = 72
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'SHORTDESCRIPTION'
          Title.Caption = #1059#1088#1086#1074#1077#1085#1100' '#1084#1072#1089#1090#1077#1088#1089#1090#1074#1072
          Width = 73
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'AGE'
          Title.Caption = #1042#1086#1079#1088#1072#1089#1090
          Width = 46
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'WEIGHT'
          Title.Caption = #1042#1077#1089
          Width = 45
          Visible = True
        end>
    end
    object grboxCompetitorInfo: TGroupBox
      Left = 202
      Top = 161
      Width = 368
      Height = 158
      Align = alRight
      Caption = #1048#1085#1092#1086#1088#1084#1072#1094#1080#1103' '#1086#1073' '#1091#1095#1072#1089#1090#1085#1080#1082#1077
      TabOrder = 1
      object lblCompetitorSurname: TLabel
        Left = 5
        Top = 20
        Width = 65
        Height = 16
        Caption = #1060#1072#1084#1080#1083#1080#1103' :'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object lblCompetitorClub: TLabel
        Left = 5
        Top = 100
        Width = 60
        Height = 16
        Caption = #1050#1086#1084#1072#1085#1076#1072':'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object blbCompetitorAge: TLabel
        Left = 5
        Top = 130
        Width = 58
        Height = 16
        Caption = #1042#1086#1079#1088#1072#1089#1090':'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object lblCompetitorWeight: TLabel
        Left = 141
        Top = 130
        Width = 27
        Height = 16
        Caption = #1042#1077#1089':'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object dbtxtCompetitorName: TDBText
        Left = 121
        Top = 44
        Width = 248
        Height = 17
        Color = clBtnFace
        DataField = 'PERS_NAME'
        DataSource = dmCompetitorDAO.dsCompetitorExtended
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentColor = False
        ParentFont = False
      end
      object dbtxtCompetitorPatronymic: TDBText
        Left = 121
        Top = 68
        Width = 248
        Height = 17
        Color = clBtnFace
        DataField = 'PATRONYMIC'
        DataSource = dmCompetitorDAO.dsCompetitorExtended
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentColor = False
        ParentFont = False
      end
      object dbtxtCompetitorClub: TDBText
        Left = 121
        Top = 100
        Width = 248
        Height = 17
        Color = clBtnFace
        DataField = 'SHORTNAME'
        DataSource = dmCompetitorDAO.dsCompetitorExtended
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold, fsItalic]
        ParentColor = False
        ParentFont = False
      end
      object dbtxtCompetitorSurname: TDBText
        Left = 121
        Top = 21
        Width = 248
        Height = 17
        Color = clBtnFace
        DataField = 'SURNAME'
        DataSource = dmCompetitorDAO.dsCompetitorExtended
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentColor = False
        ParentFont = False
      end
      object lblCompetitorName: TLabel
        Left = 5
        Top = 44
        Width = 32
        Height = 16
        Caption = #1048#1084#1103' :'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object lblCompetitorPatronymic: TLabel
        Left = 5
        Top = 68
        Width = 69
        Height = 16
        Caption = #1054#1090#1095#1077#1089#1090#1074#1086' :'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object dbtxtCompetitorAge: TDBText
        Left = 72
        Top = 130
        Width = 57
        Height = 17
        DataField = 'AGE'
        DataSource = dmCompetitorDAO.dsCompetitorExtended
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object dbtxtCompetitorWeight: TDBText
        Left = 176
        Top = 130
        Width = 57
        Height = 17
        DataField = 'WEIGHT'
        DataSource = dmCompetitorDAO.dsCompetitorExtended
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
    object grboxSearchCondition: TGroupBox
      Left = 2
      Top = 161
      Width = 200
      Height = 158
      Align = alClient
      Caption = #1059#1089#1083#1086#1074#1080#1103' '#1087#1086#1080#1089#1082#1072' '#1091#1095#1072#1089#1090#1085#1080#1082#1072
      TabOrder = 2
      object lbledtCompetitorSurname: TLabeledEdit
        Left = 32
        Top = 43
        Width = 121
        Height = 21
        EditLabel.Width = 52
        EditLabel.Height = 13
        EditLabel.Caption = #1060#1072#1084#1080#1083#1080#1103':'
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 1
        OnChange = lbledtCompetitorSurnameChange
      end
      object lbledtCompetitorClub: TLabeledEdit
        Left = 32
        Top = 107
        Width = 121
        Height = 21
        EditLabel.Width = 102
        EditLabel.Height = 13
        EditLabel.Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1082#1086#1084#1072#1085#1076#1099':'
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 0
        OnChange = lbledtCompetitorSurnameChange
      end
    end
  end
  object grboxResultEnter: TGroupBox
    Left = 0
    Top = 321
    Width = 572
    Height = 91
    Align = alClient
    Caption = #1042#1074#1086#1076' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1072
    TabOrder = 1
    object lblCompetitorShootScore: TLabel
      Left = 56
      Top = 21
      Width = 215
      Height = 20
      Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090' '#1089#1090#1088#1077#1083#1100#1073#1099' ('#1073#1072#1083#1099'):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object lblNewShootResult: TLabel
      Left = 344
      Top = 16
      Width = 12
      Height = 37
      Caption = '*'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -32
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      Visible = False
    end
    object lblCompetitorCrossTime: TLabel
      Left = 56
      Top = 61
      Width = 218
      Height = 20
      Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090' '#1082#1088#1086#1089#1089#1072' ('#1084#1084'.'#1089#1089'.'#1076#1089'):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object lblNewCrossResult: TLabel
      Left = 408
      Top = 56
      Width = 12
      Height = 37
      Caption = '*'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -32
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      Visible = False
    end
    object mskedtCompetitorShootScore: TMaskEdit
      Left = 288
      Top = 19
      Width = 54
      Height = 28
      EditMask = '999;1; '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      MaxLength = 3
      ParentFont = False
      TabOrder = 0
      Text = '   '
      OnChange = mskedtCompetitorShootScoreChange
    end
    object bbtnAddResult: TBitBtn
      Left = 472
      Top = 16
      Width = 75
      Height = 25
      Cancel = True
      Caption = #1042#1074#1086#1076
      Default = True
      TabOrder = 1
      OnClick = bbtnAddResultClick
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333300030003
        0003333377737773777333333333333333333FFFFFFFFFFFFFFF770000000000
        0000777777777777777733039993BBB3CCC3337F737F737F737F37039993BBB3
        CCC3377F737F737F737F33039993BBB3CCC33F7F737F737F737F77079997BBB7
        CCC77777737773777377330399930003CCC3337F737F7773737F370399933333
        CCC3377F737F3333737F330399933333CCC33F7F737FFFFF737F770700077777
        CCC77777777777777377330333333333CCC3337F33333333737F370333333333
        0003377F33333333777333033333333333333F7FFFFFFFFFFFFF770777777777
        7777777777777777777733333333333333333333333333333333}
      NumGlyphs = 2
    end
    object bbtnClose: TBitBtn
      Left = 472
      Top = 48
      Width = 75
      Height = 25
      Caption = #1042#1099#1093#1086#1076
      TabOrder = 2
      Kind = bkClose
    end
    object mskedtCompetitorCrossTime: TMaskEdit
      Left = 288
      Top = 60
      Width = 112
      Height = 21
      EditMask = '!99:99/99;1;0'
      MaxLength = 8
      TabOrder = 3
      Text = '  :  .  '
      OnChange = mskedtCompetitorCrossTimeChange
    end
  end
end
