object frmTestReport: TfrmTestReport
  Left = 261
  Top = 183
  Width = 783
  Height = 540
  Caption = 'frmTestReport'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object dbgrdCompetitorToCategory: TDBGrid
    Left = 0
    Top = 0
    Width = 320
    Height = 386
    Align = alLeft
    DataSource = dmReportDataSource.dsRepCompetitorToCategory
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
  end
  object dbgrdCompetitor: TDBGrid
    Left = 320
    Top = 0
    Width = 455
    Height = 386
    Align = alClient
    DataSource = dmReportDataSource.dsTest
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
  end
  object dbgrdCategory: TDBGrid
    Left = 0
    Top = 386
    Width = 775
    Height = 120
    Align = alBottom
    DataSource = dmReportDataSource.dsRepCategory
    TabOrder = 2
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
  end
end
