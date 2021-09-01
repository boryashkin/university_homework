unit dbBankingDataModule;
interface
uses
 SysUtils, Classes, DB, ADODB;
type
 TDicRec = record
 Id: Integer;
 Name: String;
 end;
type
 TRecSet = Array of TDicRec;
type
 TDataModule2 = class(TDataModule)
 conInvestmentDb: TADOConnection;
 tblBanks: TADOTable;
 dsBanks: TDataSource;
 tblClients: TADOTable;
 dsClients: TDataSource;
 tblDeposits: TADOTable;
 dsDeposits: TDataSource;
 tblStocks: TADOTable;
 dsStocks: TDataSource;
 tblDepositInvestments: TADOTable;
 dsDepositInvestments: TDataSource;
 tblStockInvestments: TADOTable;
 dsStockInvestments: TDataSource;
 dsqDepositInvestments: TADODataSet;
 private
 { Private declarations }
 public
 function GetClients(): TRecSet;
 function GetBanks(): TRecSet;
 function AddDepositInvestment(depositId, sum, clientId: Integer; date, time: TDateTime): Boolean
 { Public declarations }
 end;
const
 TblDIFieldCode = 0;//Код
 TblDIFieldCodeDeposit = 1;//КодВклада
 TblDIFieldCodeSum = 2;//Сумма
 TblDIFieldCodeNameClient = 3;//КодКлиента
var
 DataModule2: TDataModule2;
implementation
{$R *.dfm}
function TDataModule2.GetClients(): TRecSet;
var
 i: Integer;
 l: Integer;
 clients : TRecSet;
 rec: TDicRec;
begin
 SetLength(clients, tblClients.RecordCount);
 i := 0;
 l := tblClients.RecordCount;
 while i < l do
 begin
 rec.Id := tblClients.FieldByName('Код').Value;
 rec.Name := tblClients.FieldByName('Название').Value;
 clients[i] := rec;
 Inc(i);
 tblClients.Next;
 end;
 Result := clients;
end;
function TDataModule2.GetBanks(): TRecSet;
var
 i: Integer;
 l: Integer;
 banks : TRecSet;
 rec: TDicRec;
begin
 SetLength(banks, tblBanks.RecordCount);
 i := 0;
 l := tblBanks.RecordCount;
 while i < l do
 begin
 rec.Id := tblBanks.FieldByName('Код').Value;
 rec.Name := tblBanks.FieldByName('Название').Value;
 banks[i] := rec;
 Inc(i);
 tblBanks.Next;
 end;
 Result := banks;
end;
function TDataModule2.AddDepositInvestment(depositId, sum, clientId: Integer; date, time: TDateTime):
begin
 tblDepositInvestments.Insert;
 tblDepositInvestments.FieldByName('КодВклада').Value := depositId;
 tblDepositInvestments.FieldByName('Сумма').Value := sum;
 tblDepositInvestments.FieldByName('КодКлиента').Value := clientId;
 tblDepositInvestments.FieldByName('ДатаВклада').Value := DateToStr(date) + ' ' + TimeToStr(time);
 tblDepositInvestments.Post;
 dsqDepositInvestments.Close;
 dsqDepositInvestments.Open;
 Result := true;
end;
end.
