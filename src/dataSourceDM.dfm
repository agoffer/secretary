object dmDataSource: TdmDataSource
  OldCreateOrder = False
  Left = 394
  Top = 295
  Height = 359
  Width = 319
  object ibdbSecretaryDB: TIBDatabase
    Connected = True
    DatabaseName = 'database\SECRETARYDB.GDB'
    Params.Strings = (
      'user_name=SYSDBA'
      'password=masterkey')
    LoginPrompt = False
    DefaultTransaction = ibtrSecretaryDB
    IdleTimer = 0
    SQLDialect = 3
    TraceFlags = []
    Left = 24
  end
  object ibtrSecretaryDB: TIBTransaction
    Active = True
    DefaultDatabase = ibdbSecretaryDB
    AutoStopAction = saCommit
    Left = 32
    Top = 56
  end
end
