object Form1: TForm1
  Left = 387
  Top = 131
  Width = 348
  Height = 296
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Label3: TLabel
    Left = 120
    Top = 64
    Width = 32
    Height = 13
    Caption = 'Label3'
  end
  object Label4: TLabel
    Left = 160
    Top = 64
    Width = 32
    Height = 13
    Caption = 'Label4'
  end
  object bToExcel: TButton
    Left = 8
    Top = 8
    Width = 153
    Height = 25
    Caption = #1074' Excel'
    TabOrder = 0
    OnClick = bToExcelClick
  end
  object Button1: TButton
    Left = 8
    Top = 56
    Width = 105
    Height = 25
    Caption = 'formulaFromExcel'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 8
    Top = 88
    Width = 75
    Height = 25
    Caption = 'Graph'
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 88
    Top = 88
    Width = 75
    Height = 25
    Caption = 'Border'
    TabOrder = 3
    OnClick = Button3Click
  end
  object Button5: TButton
    Left = 8
    Top = 120
    Width = 75
    Height = 25
    Caption = 'Zoom'
    TabOrder = 4
    OnClick = Button5Click
  end
  object CSpinEdit1: TCSpinEdit
    Left = 88
    Top = 120
    Width = 73
    Height = 22
    MaxValue = 100
    MinValue = 10
    TabOrder = 5
    Value = 75
  end
  object Button4: TButton
    Left = 8
    Top = 232
    Width = 75
    Height = 25
    Caption = 'Save'
    TabOrder = 6
    OnClick = Button4Click
  end
  object Button6: TButton
    Left = 88
    Top = 232
    Width = 75
    Height = 25
    Caption = 'Print'
    TabOrder = 7
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 184
    Top = 232
    Width = 75
    Height = 25
    Caption = 'Close'
    TabOrder = 8
    OnClick = Button7Click
  end
  object Button8: TButton
    Left = 8
    Top = 152
    Width = 75
    Height = 25
    Caption = 'Macros'
    TabOrder = 9
    OnClick = Button8Click
  end
  object Button10: TButton
    Left = 256
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Name'
    TabOrder = 10
    OnClick = Button10Click
  end
  object Button11: TButton
    Left = 256
    Top = 40
    Width = 75
    Height = 25
    Caption = 'Rename'
    TabOrder = 11
    OnClick = Button11Click
  end
  object Edit2: TEdit
    Left = 256
    Top = 72
    Width = 73
    Height = 21
    TabOrder = 12
  end
end
