object frmCategoryFinalReport: TfrmCategoryFinalReport
  Left = 238
  Top = 155
  Width = 820
  Height = 827
  Caption = 'categoryFinalReportU'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  PixelsPerInch = 96
  TextHeight = 13
  object qrCategory: TQuickRep
    Left = 0
    Top = -5
    Width = 794
    Height = 1123
    Frame.Color = clBlack
    Frame.DrawTop = False
    Frame.DrawBottom = False
    Frame.DrawLeft = False
    Frame.DrawRight = False
    DataSet = dmReportDataSource.ibqRepCategoryDetail
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    Functions.Strings = (
      'PAGENUMBER'
      'COLUMNNUMBER'
      'REPORTTITLE'
      'QRSTRINGSBAND1')
    Functions.DATA = (
      '0'
      '0'
      #39#39
      #39#39)
    Options = [FirstPageHeader, LastPageFooter]
    Page.Columns = 1
    Page.Orientation = poPortrait
    Page.PaperSize = A4
    Page.Values = (
      50
      2970
      50
      2100
      100
      100
      0)
    PrinterSettings.Copies = 1
    PrinterSettings.Duplex = False
    PrinterSettings.FirstPage = 0
    PrinterSettings.LastPage = 0
    PrinterSettings.OutputBin = Auto
    PrintIfEmpty = False
    SnapToGrid = True
    Units = MM
    Zoom = 100
    object qrdbsdCompetitor: TQRSubDetail
      Left = 38
      Top = 298
      Width = 718
      Height = 18
      Frame.Color = clBlack
      Frame.DrawTop = False
      Frame.DrawBottom = False
      Frame.DrawLeft = False
      Frame.DrawRight = False
      AlignToBottom = False
      Color = clWhite
      ForceNewColumn = False
      ForceNewPage = False
      Size.Values = (
        47.625
        1899.70833333333)
      Master = qrCategory
      DataSet = dmReportDataSource.ibqRepCategoryFinalCompetitorDetail
      HeaderBand = qrhbTableHeader
      PrintBefore = False
      PrintIfEmpty = False
      object qrdbtSurname: TQRDBText
        Left = 37
        Top = 0
        Width = 98
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = False
        Size.Values = (
          52.9166666666667
          97.8958333333333
          0
          259.291666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = False
        AutoStretch = True
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryFinalCompetitorDetail
        DataField = 'SURNAME'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = False
        FontSize = 10
      end
      object qrdbtName: TQRDBText
        Left = 134
        Top = 0
        Width = 75
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          52.9166666666667
          354.541666666667
          0
          198.4375)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = False
        AutoStretch = True
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryFinalCompetitorDetail
        DataField = 'NAME'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = False
        FontSize = 10
      end
      object qrdbtPatronymic: TQRDBText
        Left = 208
        Top = 0
        Width = 92
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = False
        Frame.DrawRight = True
        Size.Values = (
          52.9166666666667
          550.333333333333
          0
          243.416666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = False
        AutoStretch = True
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryFinalCompetitorDetail
        DataField = 'PATRONYMIC'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = False
        FontSize = 10
      end
      object qrdbtSortion: TQRDBText
        Left = 8
        Top = 0
        Width = 30
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = False
        Size.Values = (
          52.9166666666667
          21.1666666666667
          0
          79.375)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = True
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryFinalCompetitorDetail
        DataField = 'COMMONRANK'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Times New Roman'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 11
      end
      object qrdbtShootRank: TQRDBText
        Left = 298
        Top = 0
        Width = 52
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          52.9166666666667
          788.458333333333
          0
          137.583333333333)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = True
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryFinalCompetitorDetail
        DataField = 'SHOOTRANK'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Times New Roman'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = False
        FontSize = 9
      end
      object qrdbtComments: TQRDBText
        Left = 672
        Top = 0
        Width = 41
        Height = 18
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          47.625
          1778
          0
          108.479166666667)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = True
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryFinalCompetitorDetail
        DataField = 'SHORTNAME'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = 10
        Font.Name = 'Times New Roman'
        Font.Style = []
        Mask = '###.#'
        ParentFont = False
        Transparent = False
        WordWrap = False
        FontSize = -8
      end
      object qrdbtFightWOKRank: TQRDBText
        Left = 392
        Top = 0
        Width = 52
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          52.9166666666667
          1037.16666666667
          0
          137.583333333333)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = True
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryFinalCompetitorDetail
        DataField = 'FIGHTWOKNIFERANK'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Times New Roman'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = False
        FontSize = 9
      end
      object qrdbtFightWKRank: TQRDBText
        Left = 486
        Top = 0
        Width = 52
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          52.9166666666667
          1285.875
          0
          137.583333333333)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = True
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryFinalCompetitorDetail
        DataField = 'FIGHTWKNIFERANK'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Times New Roman'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = False
        FontSize = 9
      end
      object qrdbtFightWKScore: TQRDBText
        Left = 537
        Top = 0
        Width = 44
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          52.9166666666667
          1420.8125
          0
          116.416666666667)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = True
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryFinalCompetitorDetail
        DataField = 'FIGHTWKNIFERANK'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Times New Roman'
        Font.Style = []
        OnPrint = qrdbtScorePrint
        ParentFont = False
        Transparent = False
        WordWrap = False
        FontSize = 11
      end
      object qrdbtCommonScore: TQRDBText
        Left = 580
        Top = 0
        Width = 52
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          52.9166666666667
          1534.58333333333
          0
          137.583333333333)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = True
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryFinalCompetitorDetail
        DataField = 'COMMONRANK'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Times New Roman'
        Font.Style = []
        OnPrint = qrdbtCommonScorePrint
        ParentFont = False
        Transparent = False
        WordWrap = False
        FontSize = 9
      end
      object qrdbtCommonRank: TQRDBText
        Left = 631
        Top = 0
        Width = 44
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          52.9166666666667
          1669.52083333333
          0
          116.416666666667)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = True
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryFinalCompetitorDetail
        DataField = 'COMMONRANK'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Times New Roman'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = False
        FontSize = 11
      end
      object qrdbtFightWOKScore: TQRDBText
        Left = 443
        Top = 0
        Width = 44
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          52.9166666666667
          1172.10416666667
          0
          116.416666666667)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = True
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryFinalCompetitorDetail
        DataField = 'FIGHTWOKNIFERANK'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Times New Roman'
        Font.Style = []
        OnPrint = qrdbtScorePrint
        ParentFont = False
        Transparent = False
        WordWrap = False
        FontSize = 11
      end
      object qrdbtShootScore: TQRDBText
        Left = 349
        Top = 0
        Width = 44
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          52.9166666666667
          923.395833333333
          0
          116.416666666667)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = True
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryFinalCompetitorDetail
        DataField = 'SHOOTRANK'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Times New Roman'
        Font.Style = []
        OnPrint = qrdbtScorePrint
        ParentFont = False
        Transparent = False
        WordWrap = False
        FontSize = 11
      end
    end
    object qrhbTableHeader: TQRBand
      Left = 38
      Top = 198
      Width = 718
      Height = 100
      Frame.Color = clBlack
      Frame.DrawTop = False
      Frame.DrawBottom = False
      Frame.DrawLeft = False
      Frame.DrawRight = False
      AlignToBottom = False
      Color = clWhite
      ForceNewColumn = False
      ForceNewPage = True
      Size.Values = (
        264.583333333333
        1899.70833333333)
      BandType = rbGroupHeader
      object qrmCategorySNP: TQRMemo
        Left = 37
        Top = 0
        Width = 261
        Height = 100
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          264.583333333333
          97.8958333333333
          0
          690.5625)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Color = clWhite
        Lines.Strings = (
          ''
          ''
          #1055#1088#1110#1079#1074#1080#1097#1077', '#1110#1084#39#1103', '#1087#1086' '#1073#1072#1090#1100#1082#1086#1074#1110)
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object qrmCategorySortion: TQRMemo
        Left = 8
        Top = 0
        Width = 30
        Height = 100
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          264.583333333333
          21.1666666666667
          0
          79.375)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Color = clWhite
        Lines.Strings = (
          ''
          #8470' '#1079#1072' '#1087#1086#1088'.')
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object qrmShootResult: TQRMemo
        Left = 298
        Top = 0
        Width = 95
        Height = 57
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          150.8125
          788.458333333333
          0
          251.354166666667)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Color = clWhite
        Lines.Strings = (
          #1056#1077#1079#1091#1083#1100#1090#1072#1090
          #1079#1072' '#1088#1086#1079#1076#1110#1083#1086#1084
          '"'#1057#1090#1088#1110#1083#1100#1073#1072'"')
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object qrmShootRank: TQRMemo
        Left = 298
        Top = 56
        Width = 52
        Height = 44
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          116.416666666667
          788.458333333333
          148.166666666667
          137.583333333333)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Color = clWhite
        Lines.Strings = (
          ''
          #1052#1110#1089#1094#1077)
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object qrmShootScore: TQRMemo
        Left = 349
        Top = 56
        Width = 44
        Height = 44
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          116.416666666667
          923.395833333333
          148.166666666667
          116.416666666667)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Color = clWhite
        Lines.Strings = (
          #1057#1091#1084#1072
          #1073#1072#1083#1110#1074)
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object qrmComments: TQRMemo
        Left = 672
        Top = 0
        Width = 41
        Height = 100
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          264.583333333333
          1778
          0
          108.479166666667)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Color = clWhite
        Lines.Strings = (
          ''
          ''
          #1055#1088#1080'-'
          #1084#1110#1090'-'
          #1082#1080)
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object qrmFightWOKResult: TQRMemo
        Left = 392
        Top = 0
        Width = 95
        Height = 57
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          150.8125
          1037.16666666667
          0
          251.354166666667)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Color = clWhite
        Lines.Strings = (
          #1056#1077#1079#1091#1083#1100#1090#1072#1090
          #1079#1072' '#1088#1086#1079#1076#1110#1083#1086#1084
          '"'#1056#1041' '#1073#1077#1079' '#1061#1047'"')
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object qrmFightWOKRank: TQRMemo
        Left = 392
        Top = 56
        Width = 52
        Height = 44
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          116.416666666667
          1037.16666666667
          148.166666666667
          137.583333333333)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Color = clWhite
        Lines.Strings = (
          ''
          #1052#1110#1089#1094#1077)
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object qrmFightWOKScore: TQRMemo
        Left = 443
        Top = 56
        Width = 44
        Height = 44
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          116.416666666667
          1172.10416666667
          148.166666666667
          116.416666666667)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Color = clWhite
        Lines.Strings = (
          #1057#1091#1084#1072
          #1073#1072#1083#1110#1074)
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object qrmFightWKResult: TQRMemo
        Left = 486
        Top = 0
        Width = 95
        Height = 57
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          150.8125
          1285.875
          0
          251.354166666667)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Color = clWhite
        Lines.Strings = (
          #1056#1077#1079#1091#1083#1100#1090#1072#1090
          #1079#1072' '#1088#1086#1079#1076#1110#1083#1086#1084
          '"'#1056#1041' '#1079' '#1061#1047'"')
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object qrmFightWKRank: TQRMemo
        Left = 486
        Top = 56
        Width = 52
        Height = 44
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          116.416666666667
          1285.875
          148.166666666667
          137.583333333333)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Color = clWhite
        Lines.Strings = (
          ''
          #1052#1110#1089#1094#1077)
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object qrmFightWKScore: TQRMemo
        Left = 537
        Top = 56
        Width = 44
        Height = 44
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          116.416666666667
          1420.8125
          148.166666666667
          116.416666666667)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Color = clWhite
        Lines.Strings = (
          #1057#1091#1084#1072
          #1073#1072#1083#1110#1074)
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object qrmCommonResult: TQRMemo
        Left = 580
        Top = 0
        Width = 95
        Height = 57
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          150.8125
          1534.58333333333
          0
          251.354166666667)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Color = clWhite
        Lines.Strings = (
          #1047#1072#1075#1072#1083#1100#1085#1080#1081
          #1088#1077#1079#1091#1083#1100#1090#1072#1090' '#1079#1072
          #1090#1088#1100#1086#1084#1072' '#1088#1086#1079#1076'.')
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object qrmCommonScore: TQRMemo
        Left = 580
        Top = 56
        Width = 52
        Height = 44
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          116.416666666667
          1534.58333333333
          148.166666666667
          137.583333333333)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Color = clWhite
        Lines.Strings = (
          #1057#1091#1084#1072
          #1073#1072#1083#1110#1074)
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
      object qrmCommonRank: TQRMemo
        Left = 631
        Top = 56
        Width = 44
        Height = 44
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          116.416666666667
          1669.52083333333
          148.166666666667
          116.416666666667)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Color = clWhite
        Lines.Strings = (
          ''
          #1052#1110#1089#1094#1077)
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
    end
    object qrbCategoryFooter: TQRBand
      Left = 38
      Top = 316
      Width = 718
      Height = 125
      Frame.Color = clBlack
      Frame.DrawTop = False
      Frame.DrawBottom = False
      Frame.DrawLeft = False
      Frame.DrawRight = False
      AlignToBottom = False
      Color = clWhite
      ForceNewColumn = False
      ForceNewPage = False
      Size.Values = (
        330.729166666667
        1899.70833333333)
      BandType = rbPageFooter
      object qrmCategoryFooter: TQRMemo
        Left = 0
        Top = 0
        Width = 681
        Height = 121
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          320.145833333333
          0
          0
          1801.8125)
        Alignment = taLeftJustify
        AlignToBand = True
        AutoSize = False
        AutoStretch = False
        Color = clWhite
        Lines.Strings = (
          #1047#1072#1089#1090#1091#1087#1085#1080#1082' '#1075#1086#1083#1086#1074#1085#1086#1075#1086' '#1089#1091#1076#1076#1110'____________________________________'
          ''
          #1043#1086#1083#1086#1074#1085#1080#1081' '#1089#1077#1082#1088#1077#1090#1072#1088'___________________________________________'
          ''
          #1047#1072#1090#1074#1077#1088#1078#1091#1102
          #1043#1086#1083#1086#1074#1085#1080#1081' '#1089#1091#1076#1076#1103' '#1079#1084#1072#1075#1072#1085#1100'______________________________________')
        Transparent = False
        WordWrap = True
        FontSize = 10
      end
    end
    object qrbCategoryTitle: TQRBand
      Left = 38
      Top = 19
      Width = 718
      Height = 179
      Frame.Color = clBlack
      Frame.DrawTop = False
      Frame.DrawBottom = False
      Frame.DrawLeft = False
      Frame.DrawRight = False
      AlignToBottom = False
      Color = clWhite
      ForceNewColumn = False
      ForceNewPage = False
      Size.Values = (
        473.604166666667
        1899.70833333333)
      BandType = rbPageHeader
      object qrlCategoryOrgTitle: TQRLabel
        Left = 59
        Top = 8
        Width = 599
        Height = 23
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          60.8541666666667
          156.104166666667
          21.1666666666667
          1584.85416666667)
        Alignment = taCenter
        AlignToBand = True
        AutoSize = True
        AutoStretch = False
        Caption = #1042#1057#1045#1059#1050#1056#1040#1031#1053#1057#1068#1050#1040' '#1060#1045#1044#1045#1056#1040#1062#1030#1071' '#1042#1030#1049#1057#1068#1050#1054#1042#1054'-'#1057#1055#1054#1056#1058#1048#1042#1053#1048#1061' '#1041#1040#1043#1040#1058#1054#1041#1054#1056#1057#1058#1042
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 12
      end
      object qrdbtCategoryCompRank: TQRDBText
        Left = 302
        Top = 32
        Width = 114
        Height = 24
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          63.5
          799.041666666667
          84.6666666666667
          301.625)
        Alignment = taCenter
        AlignToBand = True
        AutoSize = True
        AutoStretch = False
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryDetail
        DataField = 'DESCRIPTION'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 12
      end
      object qrlCategoryProtTitle: TQRLabel
        Left = 86
        Top = 56
        Width = 545
        Height = 41
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          108.479166666667
          227.541666666667
          148.166666666667
          1441.97916666667)
        Alignment = taCenter
        AlignToBand = True
        AutoSize = False
        AutoStretch = False
        Caption = 
          '       '#1047#1074#1077#1076#1077#1085#1080#1081'   '#1087#1088#1086#1090#1086#1082#1086#1083'   '#8470' 2   '#1079#1084#1072#1075#1072#1085#1100' '#1079' "'#1041#1086#1081#1086#1074#1086#1075#1086' '#1073#1072#1075#1072#1090#1086#1073#1086#1088 +
          #1089#1090#1074#1072'"        ('#1079#1072' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1072#1084#1080' '#1079#1084#1072#1075#1072#1085#1100'  '#1079'  '#1090#1088#1100#1086#1093'  '#1088#1086#1079#1076'i'#1083'i'#1074')'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 12
      end
      object qrlCategoryDate: TQRLabel
        Left = 112
        Top = 104
        Width = 191
        Height = 19
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          50.2708333333333
          296.333333333333
          275.166666666667
          505.354166666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = #1044#1072#1090#1072' '#1087#1088#1086#1074#1077#1076#1077#1085#1103' '#1079#1084#1072#1075#1072#1085#1100' :'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 12
      end
      object qrdbtCategoryEndDate: TQRDBText
        Left = 464
        Top = 104
        Width = 80
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          52.9166666666667
          1227.66666666667
          275.166666666667
          211.666666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryDetail
        DataField = 'ENDDATE'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsItalic]
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 12
      end
      object qrdbtCategoryCompBegDate: TQRDBText
        Left = 320
        Top = 104
        Width = 95
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          52.9166666666667
          846.666666666667
          275.166666666667
          251.354166666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryDetail
        DataField = 'BEGINDATE'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsItalic]
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 12
      end
      object qrlCategoryDateDefis: TQRLabel
        Left = 432
        Top = 96
        Width = 8
        Height = 25
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          66.1458333333333
          1143
          254
          21.1666666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = '-'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -21
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 16
      end
      object qrlCategoryAge: TQRLabel
        Left = 73
        Top = 128
        Width = 101
        Height = 23
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          60.8541666666667
          193.145833333333
          338.666666666667
          267.229166666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = #1042#1110#1082#1086#1074#1072' '#1075#1088#1091#1087#1072' :'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 12
      end
      object qrlCategoryWeight: TQRLabel
        Left = 257
        Top = 128
        Width = 135
        Height = 23
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          60.8541666666667
          679.979166666667
          338.666666666667
          357.1875)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = #1042#1072#1075#1086#1074#1072' '#1082#1072#1090#1077#1075#1086#1088#1110#1103' :'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 12
      end
      object qrdbCategoryStartAge: TQRDBText
        Left = 48
        Top = 152
        Width = 49
        Height = 23
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          60.8541666666667
          127
          402.166666666667
          129.645833333333)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryDetail
        DataField = 'STARTAGE'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 14
      end
      object qrdbtCategoryEndAge: TQRDBText
        Left = 128
        Top = 152
        Width = 82
        Height = 23
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          60.8541666666667
          338.666666666667
          402.166666666667
          216.958333333333)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryDetail
        DataField = 'ENDAGE'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 14
      end
      object qrdbtCategoryStartWeight: TQRDBText
        Left = 240
        Top = 152
        Width = 78
        Height = 23
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          60.8541666666667
          635
          402.166666666667
          206.375)
        Alignment = taRightJustify
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryDetail
        DataField = 'STARTWEIGHT'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 14
      end
      object qrdbtCategoryEndWeight: TQRDBText
        Left = 352
        Top = 152
        Width = 117
        Height = 23
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          60.8541666666667
          931.333333333333
          402.166666666667
          309.5625)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryDetail
        DataField = 'ENDWEIGHT'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 14
      end
      object qrlCategoryFightVersion: TQRLabel
        Left = 449
        Top = 128
        Width = 116
        Height = 19
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          50.2708333333333
          1187.97916666667
          338.666666666667
          306.916666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = #1041#1086#1081#1086#1074#1072' '#1074#1077#1088#1089#1110#1103' :'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 12
      end
      object qrdbtCategoryFightVersion: TQRDBText
        Left = 472
        Top = 152
        Width = 57
        Height = 23
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          60.8541666666667
          1248.83333333333
          402.166666666667
          150.8125)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryDetail
        DataField = 'CODE'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 14
      end
      object qrlCategoryAgeDefis: TQRLabel
        Left = 104
        Top = 152
        Width = 16
        Height = 25
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          66.1458333333333
          275.166666666667
          402.166666666667
          42.3333333333333)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Caption = '-'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -21
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 16
      end
      object qrlCategoryWeightDefis: TQRLabel
        Left = 328
        Top = 152
        Width = 16
        Height = 25
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          66.1458333333333
          867.833333333333
          402.166666666667
          42.3333333333333)
        Alignment = taCenter
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Caption = '-'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -21
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 16
      end
      object qrdbtFemale: TQRDBText
        Left = 600
        Top = 152
        Width = 57
        Height = 23
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          60.8541666666667
          1587.5
          402.166666666667
          150.8125)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = False
        AutoStretch = False
        Color = clWhite
        DataSet = dmReportDataSource.ibqRepCategoryDetail
        DataField = 'FEMALE'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        OnPrint = qrdbtFemalePrint
        ParentFont = False
        Transparent = False
        WordWrap = True
        FontSize = 14
      end
    end
  end
end
