object frmPersonFullEdit: TfrmPersonFullEdit
  Left = 296
  Top = 178
  BorderStyle = bsDialog
  Caption = #1055#1077#1088#1089#1086#1085#1072#1083#1100#1085#1099#1077' '#1076#1072#1085#1085#1099#1077' '#1091#1095#1072#1089#1090#1085#1080#1082#1086#1074
  ClientHeight = 415
  ClientWidth = 789
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
  object lblDOB: TLabel
    Left = 528
    Top = 271
    Width = 79
    Height = 13
    Caption = #1044#1072#1090#1072' '#1088#1086#1078#1076#1077#1085#1080#1103
  end
  object lblComments: TLabel
    Left = 192
    Top = 319
    Width = 70
    Height = 13
    Caption = #1050#1086#1084#1084#1077#1085#1090#1072#1088#1080#1080
  end
  object pnlPersonData: TPanel
    Left = 0
    Top = 0
    Width = 789
    Height = 265
    Align = alTop
    TabOrder = 0
    object grboxPersonToUseList: TGroupBox
      Left = 392
      Top = 1
      Width = 396
      Height = 221
      Align = alClient
      Caption = #1057#1087#1080#1089#1086#1082' '#1087#1077#1088#1089#1086#1085#1072#1083#1100#1085#1099#1093' '#1076#1072#1085#1085#1099#1093' '#1085#1072' '#1079#1072#1084#1077#1085#1091
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object dbgrdPersonToUseList: TDBGrid
        Left = 2
        Top = 19
        Width = 392
        Height = 200
        Align = alClient
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit]
        ReadOnly = True
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -15
        TitleFont.Name = 'Times New Roman'
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
            Width = 126
            Visible = True
          end>
      end
    end
    object grboxPersonEditList: TGroupBox
      Left = 1
      Top = 1
      Width = 391
      Height = 221
      Align = alLeft
      Caption = #1057#1087#1080#1089#1086#1082' '#1087#1077#1088#1089#1086#1085#1072#1083#1100#1085#1099#1093' '#1076#1072#1085#1085#1099#1093' '#1076#1083#1103' '#1088#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1103
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      object dbgrdPersonEditList: TDBGrid
        Left = 2
        Top = 19
        Width = 387
        Height = 198
        Align = alCustom
        DataSource = dmPersonDAO.dsPersonTable
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit]
        ReadOnly = True
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -15
        TitleFont.Name = 'Times New Roman'
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
            Width = 126
            Visible = True
          end>
      end
    end
    object GroupBox1: TGroupBox
      Left = 1
      Top = 222
      Width = 787
      Height = 42
      Align = alBottom
      TabOrder = 2
      object lbledtLeftPaneSurnameFilter: TLabeledEdit
        Left = 64
        Top = 11
        Width = 145
        Height = 21
        EditLabel.Width = 52
        EditLabel.Height = 13
        EditLabel.Caption = #1060#1072#1084#1080#1083#1080#1103':'
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 0
        OnChange = lbledtLeftPaneSurnameFilterChange
      end
      object lbledtRightPaneSurnameFilter: TLabeledEdit
        Left = 456
        Top = 11
        Width = 145
        Height = 21
        EditLabel.Width = 52
        EditLabel.Height = 13
        EditLabel.Caption = #1060#1072#1084#1080#1083#1080#1103':'
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 1
        OnChange = lbledtRightPaneSurnameFilterChange
      end
    end
  end
  object lbledtSurname: TLabeledEdit
    Left = 24
    Top = 288
    Width = 145
    Height = 21
    EditLabel.Width = 52
    EditLabel.Height = 13
    EditLabel.Caption = #1060#1072#1084#1080#1083#1080#1103':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 1
  end
  object lbledtName: TLabeledEdit
    Left = 192
    Top = 288
    Width = 145
    Height = 21
    EditLabel.Width = 25
    EditLabel.Height = 13
    EditLabel.BiDiMode = bdLeftToRight
    EditLabel.Caption = #1048#1084#1103':'
    EditLabel.ParentBiDiMode = False
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 2
  end
  object lbledtPatronymic: TLabeledEdit
    Left = 360
    Top = 288
    Width = 145
    Height = 21
    EditLabel.Width = 50
    EditLabel.Height = 13
    EditLabel.Caption = #1054#1090#1095#1077#1089#1090#1074#1086':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 3
  end
  object dtpDOB: TDateTimePicker
    Left = 528
    Top = 288
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
    TabOrder = 4
  end
  object chboxFemale: TCheckBox
    Left = 24
    Top = 328
    Width = 97
    Height = 17
    Caption = #1055#1086#1083' '#1078#1077#1085#1089#1082#1080#1081
    TabOrder = 5
  end
  object lbledtPhone: TLabeledEdit
    Left = 24
    Top = 368
    Width = 145
    Height = 21
    EditLabel.Width = 110
    EditLabel.Height = 13
    EditLabel.Caption = #1050#1086#1085#1090#1072#1082#1090#1085#1099#1081' '#1090#1077#1083#1077#1092#1086#1085':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 6
  end
  object memComments: TMemo
    Left = 192
    Top = 344
    Width = 425
    Height = 49
    TabOrder = 7
  end
  object bbtnUpdate: TBitBtn
    Left = 624
    Top = 280
    Width = 77
    Height = 25
    Caption = #1048#1079#1084#1077#1085#1080#1090#1100
    TabOrder = 8
    OnClick = bbtnUpdateClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000120B0000120B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00555555555555
      555555FFFFFFFFFF5F5557777777777505555777777777757F55555555555555
      055555555555FF5575F555555550055030555555555775F7F7F55555550FB000
      005555555575577777F5555550FB0BF0F05555555755755757F555550FBFBF0F
      B05555557F55557557F555550BFBF0FB005555557F55575577F555500FBFBFB0
      305555577F555557F7F5550E0BFBFB003055557575F55577F7F550EEE0BFB0B0
      305557FF575F5757F7F5000EEE0BFBF03055777FF575FFF7F7F50000EEE00000
      30557777FF577777F7F500000E05555BB05577777F75555777F5500000555550
      3055577777555557F7F555000555555999555577755555577755}
    NumGlyphs = 2
    Spacing = 1
  end
  object bbtnReplace: TBitBtn
    Left = 704
    Top = 280
    Width = 77
    Height = 25
    Caption = #1047#1072#1084#1077#1085#1080#1090#1100
    TabOrder = 9
    OnClick = bbtnReplaceClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000120B0000120B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00555555555555
      55555FFFFFFF5F55FFF5777777757559995777777775755777F7555555555550
      305555555555FF57F7F555555550055BB0555555555775F777F55555550FB000
      005555555575577777F5555550FB0BF0F05555555755755757F555550FBFBF0F
      B05555557F55557557F555550BFBF0FB005555557F55575577F555500FBFBFB0
      B05555577F555557F7F5550E0BFBFB00B055557575F55577F7F550EEE0BFB0B0
      B05557FF575F5757F7F5000EEE0BFBF0B055777FF575FFF7F7F50000EEE00000
      B0557777FF577777F7F500000E055550805577777F7555575755500000555555
      05555777775555557F5555000555555505555577755555557555}
    NumGlyphs = 2
    Spacing = 1
  end
  object bbtnDelete: TBitBtn
    Left = 672
    Top = 312
    Width = 75
    Height = 25
    Caption = #1059#1076#1072#1083#1080#1090#1100
    TabOrder = 10
    OnClick = bbtnDeleteClick
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
  object bbtnClose: TBitBtn
    Left = 672
    Top = 368
    Width = 75
    Height = 25
    Caption = '&'#1042#1099#1093#1086#1076
    TabOrder = 11
    Kind = bkClose
  end
end
