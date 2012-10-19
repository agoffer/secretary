object frmRequestCompetitorsListEdit: TfrmRequestCompetitorsListEdit
  Left = 293
  Top = 176
  Width = 790
  Height = 477
  Caption = #1057#1087#1080#1089#1086#1082' '#1091#1095#1072#1089#1090#1085#1080#1082#1086#1074' ""'
  Color = clBtnFace
  Constraints.MinHeight = 477
  Constraints.MinWidth = 790
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnHide = FormHide
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object grboxCompetitorsList: TGroupBox
    Left = 385
    Top = 0
    Width = 389
    Height = 439
    Align = alClient
    Caption = #1059#1095#1072#1089#1090#1085#1080#1082#1080' ""'
    TabOrder = 0
    object strgrdCompetitorsList: TStringGrid
      Left = 2
      Top = 15
      Width = 385
      Height = 381
      Align = alClient
      Ctl3D = False
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goRowSelect]
      ParentCtl3D = False
      TabOrder = 0
      ColWidths = (
        115
        58
        74
        80
        59)
      RowHeights = (
        24
        24)
    end
    object pnlButtons: TPanel
      Left = 2
      Top = 396
      Width = 385
      Height = 41
      Align = alBottom
      TabOrder = 1
      DesignSize = (
        385
        41)
      object bbtnEdit: TBitBtn
        Left = 16
        Top = 8
        Width = 84
        Height = 25
        Anchors = [akLeft]
        Caption = #1048#1079#1084#1077#1085#1080#1090#1100
        TabOrder = 0
        OnClick = bbtnEditClick
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000120B0000120B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00555775777777
          57705557757777775FF7555555555555000755555555555F777F555555555550
          87075555555555F7577F5555555555088805555555555F755F75555555555033
          805555555555F755F75555555555033B05555555555F755F75555555555033B0
          5555555555F755F75555555555033B05555555555F755F75555555555033B055
          55555555F755F75555555555033B05555555555F755F75555555555033B05555
          555555F75FF75555555555030B05555555555F7F7F75555555555000B0555555
          5555F777F7555555555501900555555555557777755555555555099055555555
          5555777755555555555550055555555555555775555555555555}
        NumGlyphs = 2
      end
      object bbtnDelete: TBitBtn
        Left = 120
        Top = 8
        Width = 84
        Height = 25
        Anchors = [akRight]
        Caption = #1059#1076#1072#1083#1080#1090#1100
        TabOrder = 1
        OnClick = bbtnDeleteClick
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000130B0000130B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
          333333333333333333FF33333333333330003333333333333777333333333333
          300033FFFFFF3333377739999993333333333777777F3333333F399999933333
          3300377777733333337733333333333333003333333333333377333333333333
          3333333333333333333F333333333333330033333F33333333773333C3333333
          330033337F3333333377333CC3333333333333F77FFFFFFF3FF33CCCCCCCCCC3
          993337777777777F77F33CCCCCCCCCC399333777777777737733333CC3333333
          333333377F33333333FF3333C333333330003333733333333777333333333333
          3000333333333333377733333333333333333333333333333333}
        NumGlyphs = 2
      end
      object bbtnPrintRequest: TBitBtn
        Left = 304
        Top = 8
        Width = 75
        Height = 25
        Anchors = [akTop, akRight]
        Caption = #1055#1077#1095#1072#1090#1100
        TabOrder = 2
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000130B0000130B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00300000000000
          00033FFFFFFFFFFFFFFF0888888888888880777777777777777F088888888888
          8880777777777777777F0000000000000000FFFFFFFFFFFFFFFF0F8F8F8F8F8F
          8F80777777777777777F08F8F8F8F8F8F9F0777777777777777F0F8F8F8F8F8F
          8F807777777777777F7F0000000000000000777777777777777F3330FFFFFFFF
          03333337F3FFFF3F7F333330F0000F0F03333337F77773737F333330FFFFFFFF
          03333337F3FF3FFF7F333330F00F000003333337F773777773333330FFFF0FF0
          33333337F3FF7F3733333330F08F0F0333333337F7737F7333333330FFFF0033
          33333337FFFF7733333333300000033333333337777773333333}
        NumGlyphs = 2
      end
    end
  end
  object pnlCompetitor: TPanel
    Left = 0
    Top = 0
    Width = 385
    Height = 439
    Align = alLeft
    TabOrder = 1
    object grboxCompetitorEdit: TGroupBox
      Left = 1
      Top = 168
      Width = 383
      Height = 270
      Align = alClient
      Caption = #1044#1072#1085#1085#1099#1077' '#1086#1073' '#1091#1095#1072#1089#1090#1085#1080#1082#1077
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object lblDOB: TLabel
        Left = 8
        Top = 160
        Width = 84
        Height = 15
        Caption = #1044#1072#1090#1072' '#1088#1086#1078#1076#1077#1085#1080#1103
      end
      object lblWeight: TLabel
        Left = 120
        Top = 160
        Width = 23
        Height = 15
        Caption = #1042#1077#1089' '
      end
      object lblSkill: TLabel
        Left = 176
        Top = 14
        Width = 112
        Height = 15
        Caption = #1059#1088#1086#1074#1077#1085#1100' '#1084#1072#1089#1090#1077#1088#1089#1090#1074#1072
      end
      object lblFightVersion: TLabel
        Left = 176
        Top = 62
        Width = 79
        Height = 15
        Caption = #1041#1086#1077#1074#1072#1103' '#1074#1077#1088#1089#1080#1103
      end
      object lblFullAge: TLabel
        Left = 8
        Top = 244
        Width = 63
        Height = 15
        Caption = #1055#1086#1083#1085#1099#1093' '#1083#1077#1090
      end
      object lbledtSurname: TLabeledEdit
        Left = 10
        Top = 32
        Width = 153
        Height = 25
        EditLabel.Width = 51
        EditLabel.Height = 15
        EditLabel.Caption = #1060#1072#1084#1080#1083#1080#1103
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Times New Roman'
        Font.Style = []
        LabelPosition = lpAbove
        LabelSpacing = 3
        ParentFont = False
        TabOrder = 0
        OnChange = lbledtSurnameChange
      end
      object lbledtName: TLabeledEdit
        Left = 10
        Top = 80
        Width = 153
        Height = 25
        EditLabel.Width = 24
        EditLabel.Height = 15
        EditLabel.Caption = #1048#1084#1103
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Times New Roman'
        Font.Style = []
        LabelPosition = lpAbove
        LabelSpacing = 3
        ParentFont = False
        TabOrder = 1
      end
      object lbledtPatronymic: TLabeledEdit
        Left = 8
        Top = 128
        Width = 153
        Height = 25
        EditLabel.Width = 51
        EditLabel.Height = 15
        EditLabel.Caption = #1054#1090#1095#1077#1089#1090#1074#1086
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Times New Roman'
        Font.Style = []
        LabelPosition = lpAbove
        LabelSpacing = 3
        ParentFont = False
        TabOrder = 2
      end
      object dtpDOB: TDateTimePicker
        Left = 8
        Top = 176
        Width = 89
        Height = 25
        CalAlignment = dtaLeft
        Date = 38690.0497270949
        Format = 'MM.yyyy'
        Time = 38690.0497270949
        DateFormat = dfShort
        DateMode = dmComboBox
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Times New Roman'
        Font.Style = []
        Kind = dtkDate
        ParseInput = False
        ParentFont = False
        TabOrder = 3
        OnChange = dtpDOBChange
      end
      object medtWeight: TMaskEdit
        Left = 120
        Top = 176
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
        TabOrder = 4
        Text = '   , '
        OnExit = medtWeightExit
      end
      object cmboxSkill: TComboBox
        Left = 176
        Top = 32
        Width = 121
        Height = 25
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Times New Roman'
        Font.Style = []
        ItemHeight = 17
        ParentFont = False
        TabOrder = 6
        Items.Strings = (
          '1-'#1081' '#1088#1072#1079#1088#1103#1076
          '2-'#1081' '#1088#1072#1079#1088#1103#1076
          '3-'#1081' '#1088#1072#1079#1088#1103#1076
          #1050#1052#1057
          #1052#1057
          #1052#1057#1052#1050)
      end
      object btnAddSkill: TButton
        Left = 302
        Top = 32
        Width = 75
        Height = 25
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100'...'
        TabOrder = 10
        OnClick = btnAddSkillClick
      end
      object btnAddFightVersion: TButton
        Left = 302
        Top = 80
        Width = 75
        Height = 25
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100'...'
        TabOrder = 11
        OnClick = btnAddFightVersionClick
      end
      object chlstboxFightVersion: TCheckListBox
        Left = 176
        Top = 80
        Width = 119
        Height = 145
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Times New Roman'
        Font.Style = []
        ItemHeight = 13
        Items.Strings = (
          #1041' - 1 '
          #1041' - 2'
          #1041' - 3'
          #1041' - 4'
          #1041' - 5')
        ParentFont = False
        Style = lbOwnerDrawVariable
        TabOrder = 7
      end
      object bbtnAddCompetitor: TBitBtn
        Left = 164
        Top = 240
        Width = 97
        Height = 25
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100
        Default = True
        TabOrder = 8
        OnClick = bbtnAddCompetitorClick
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000130B0000130B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
          33333333FF33333333FF333993333333300033377F3333333777333993333333
          300033F77FFF3333377739999993333333333777777F3333333F399999933333
          33003777777333333377333993333333330033377F3333333377333993333333
          3333333773333333333F333333333333330033333333F33333773333333C3333
          330033333337FF3333773333333CC333333333FFFFF77FFF3FF33CCCCCCCCCC3
          993337777777777F77F33CCCCCCCCCC3993337777777777377333333333CC333
          333333333337733333FF3333333C333330003333333733333777333333333333
          3000333333333333377733333333333333333333333333333333}
        NumGlyphs = 2
      end
      object bbtnCloseList: TBitBtn
        Left = 275
        Top = 240
        Width = 97
        Height = 25
        Caption = '&'#1042#1099#1093#1086#1076
        TabOrder = 9
        Kind = bkClose
      end
      object sttxtFullAge: TStaticText
        Left = 88
        Top = 240
        Width = 41
        Height = 25
        Alignment = taCenter
        AutoSize = False
        BorderStyle = sbsSunken
        Caption = '  '
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 12
      end
      object bbtnUpdateCompetitor: TBitBtn
        Left = 164
        Top = 240
        Width = 97
        Height = 25
        Caption = #1047#1072#1087#1086#1084#1085#1080#1090#1100
        Default = True
        TabOrder = 13
        Visible = False
        OnClick = bbtnUpdateCompetitorClick
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000130B0000130B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
          333333333333333333FF33333333333330003FF3FFFFF3333777003000003333
          300077F777773F333777E00BFBFB033333337773333F7F33333FE0BFBF000333
          330077F3337773F33377E0FBFBFBF033330077F3333FF7FFF377E0BFBF000000
          333377F3337777773F3FE0FBFBFBFBFB039977F33FFFFFFF7377E0BF00000000
          339977FF777777773377000BFB03333333337773FF733333333F333000333333
          3300333777333333337733333333333333003333333333333377333333333333
          333333333333333333FF33333333333330003333333333333777333333333333
          3000333333333333377733333333333333333333333333333333}
        NumGlyphs = 2
      end
      object bbtnCancelCompetitor: TBitBtn
        Left = 275
        Top = 240
        Width = 97
        Height = 25
        Cancel = True
        Caption = 'Cancel'
        TabOrder = 14
        Visible = False
        OnClick = bbtnCancelCompetitorClick
        Glyph.Data = {
          DE010000424DDE01000000000000760000002800000024000000120000000100
          0400000000006801000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
          333333333333333333333333000033338833333333333333333F333333333333
          0000333911833333983333333388F333333F3333000033391118333911833333
          38F38F333F88F33300003339111183911118333338F338F3F8338F3300003333
          911118111118333338F3338F833338F3000033333911111111833333338F3338
          3333F8330000333333911111183333333338F333333F83330000333333311111
          8333333333338F3333383333000033333339111183333333333338F333833333
          00003333339111118333333333333833338F3333000033333911181118333333
          33338333338F333300003333911183911183333333383338F338F33300003333
          9118333911183333338F33838F338F33000033333913333391113333338FF833
          38F338F300003333333333333919333333388333338FFF830000333333333333
          3333333333333333333888330000333333333333333333333333333333333333
          0000}
        NumGlyphs = 2
      end
      object chboxFemale: TCheckBox
        Left = 8
        Top = 208
        Width = 97
        Height = 17
        Caption = #1055#1086#1083' '#1078#1077#1085#1089#1082#1080#1081
        TabOrder = 5
      end
    end
    object grboxPersonQuickSearch: TGroupBox
      Left = 1
      Top = 1
      Width = 383
      Height = 167
      Align = alTop
      Caption = #1041#1099#1089#1090#1088#1099#1081' '#1087#1086#1080#1089#1082' '#1087#1086' '#1092#1072#1084#1080#1083#1080#1080
      TabOrder = 1
      object dbgrdPersonList: TDBGrid
        Left = 2
        Top = 15
        Width = 379
        Height = 114
        Align = alTop
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit]
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
            Width = 82
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'NAME'
            Title.Caption = #1048#1084#1103
            Width = 84
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'PATRONYMIC'
            Title.Caption = #1054#1090#1095#1077#1089#1090#1074#1086
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'DOB'
            Title.Caption = #1044#1072#1090#1072' '#1088#1086#1078#1076#1077#1085#1080#1103
            Visible = True
          end>
      end
      object bbtnToEditBox: TBitBtn
        Left = 147
        Top = 134
        Width = 89
        Height = 25
        Caption = #1055#1077#1088#1077#1076#1072#1090#1100
        TabOrder = 1
        OnClick = bbtnToEditBoxClick
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000120B0000120B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333393333
          333333333337F3333333333333397333333333333337FF333333333333C94333
          3333333333737F333333333333C9473333333333337373F3333333333CC94433
          3333333337F7F7F3333333333CC94473333333333737F73F33333333CCC94443
          333333337F37F37F33333333CCC94447333333337337F373F333333CCCC94444
          33333337F337F337F333333CCCC94444733333373337F3373F3333CCCCC94444
          4333337F3337FF337F3333CCCCC94444473333733F7773FF73F33CCCCC393444
          443337F37737F773F7F33CCC33393374447337F73337F33737FFCCC333393333
          444377733337F333777FC3333339333337437333333733333373}
        NumGlyphs = 2
      end
    end
  end
end
