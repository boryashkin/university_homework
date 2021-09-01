unit dbBankForm;
interface
uses
 Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
 Dialogs, dbBankingDataModule, ExtCtrls, DBCtrls, Grids, DBGrids, ComCtrls,
 StdCtrls, Menus, Mask;
type
 TForm1 = class(TForm)
 dbgrdBanks: TDBGrid;
 dbnvgrBanks: TDBNavigator;
 pgcInvestment: TPageControl;
 tsBanks: TTabSheet;
 tsClients: TTabSheet;
 dbgrdClients: TDBGrid;
 dbnvgrClients: TDBNavigator;
 tsDeposits: TTabSheet;
 dbgrdDeposits: TDBGrid;
 dbnvgrDeposits: TDBNavigator;
 tsStocks: TTabSheet;
 dbgrdStocks: TDBGrid;
 dbnvgrStocks: TDBNavigator;
 pgcDeals: TPageControl;
 tsStockDeals: TTabSheet;
 dbmmoStocksAddInfo: TDBMemo;
 lblMemoStocks: TLabel;
 dbgrdStockInvestments: TDBGrid;
 PopupMenu1: TPopupMenu;
 tsDepositDeals: TTabSheet;
 lblDepositInvestmentsSearch: TLabel;
 lblDepositInvestmentsSearchNameClient: TLabel;
 lblDepositInvestmentsSearchNameBank: TLabel;
 lblDepositInvestmentDebugHint: TLabel;
 lblDepositInvestmentsCreateNameClient: TLabel;
 lblDepositInvestmentsCreateDateFrom: TLabel;
 lblDepositInvestmentsCreate: TLabel;
 dbgrdDepositInvestments: TDBGrid;
 edtDepositInvestmentsSearchNameClient: TEdit;
 btnDepositInvestmentsSearchClear: TButton;
 edtDepositInvestmentsSearchNameBank: TEdit;
 dtpDepositInvestmentsDateFrom: TDateTimePicker;
 cbbDepositInvestmentsNameClient: TComboBox;
 btnDepositInvestmentsCreateSubmit: TButton;
 btnDepositInvestmentsCreateCancel: TButton;
 dtpDepositInvestmentsCreateTimeFrom: TDateTimePicker;
 edtDepositInvestmentDepositId: TEdit;
 lblDepositInvestmentsDepositId: TLabel;
 edtDepositInvestmentsSum: TEdit;
 lblDepositInvestmentsSum: TLabel;
 procedure dbgrdDepositInvestmentsDrawColumnCell(Sender: TObject;
 const Rect: TRect; DataCol: Integer; Column: TColumn;
 State: TGridDrawState);
 procedure edtDepositInvestmentsSearchNameClientChange(Sender: TObject);
 procedure btnDepositInvestmentsSearchClearClick(Sender: TObject);
 procedure edtDepositInvestmentsSearchNameBankChange(Sender: TObject);
 procedure FormCreate(Sender: TObject);
 procedure cbbDepositInvestmentsNameClientChange(Sender: TObject);
 procedure edtDepositInvestmentsSumChange(Sender: TObject);
 procedure btnDepositInvestmentsCreateSubmitClick(Sender: TObject);
 procedure edtDepositInvestmentDepositIdChange(Sender: TObject);
 private
 { Private declarations }
 public
 function GetDepositInvestmentsSearchQuery(termClient, termBank: string): string;
 { Public declarations }
 end;
var
 Form1: TForm1;
 dbgrdDepositInvestments: TDBGrid;
 strDepositInvestmentsSearchQuery: string;
implementation
{$R *.dfm}
function TForm1.GetDepositInvestmentsSearchQuery(termClient, termBank: string): string;
var
 GlueStr: string;
begin
 strDepositInvestmentsSearchQuery := '';
 GlueStr := '' ;
 termClient := StringReplace(termClient, '''', '', [rfReplaceAll]);
 termBank := StringReplace(termBank, '''', '', [rfReplaceAll]);
 if termClient <> '' then
 begin
 strDepositInvestmentsSearchQuery := '[НазваниеКлиента] LIKE ''%' + termClient + '%''';
 GlueStr := ' AND ';
 end;
 if termBank <> '' then
 begin
 strDepositInvestmentsSearchQuery := strDepositInvestmentsSearchQuery + GlueStr + '[НазваниеБанка] LIKE ''%'
 end;
 lblDepositInvestmentDebugHint.Caption := strDepositInvestmentsSearchQuery;
 Result := strDepositInvestmentsSearchQuery;
end;
procedure TForm1.dbgrdDepositInvestmentsDrawColumnCell(Sender: TObject;
 const Rect: TRect; DataCol: Integer; Column: TColumn;
 State: TGridDrawState);
begin
if dbgrdDepositInvestments.Columns.Items[0].Width <> 100
then
begin
 dbgrdDepositInvestments.Columns.Items[0].Width := 100;
 dbgrdDepositInvestments.Columns.Items[1].Width := 100;
end;
end;
procedure TForm1.edtDepositInvestmentsSearchNameClientChange(Sender: TObject);
var
 srcStr: string;
begin
srcStr := GetDepositInvestmentsSearchQuery(edtDepositInvestmentsSearchNameClient.Text, edtDepositInvestmentsSearchNameBank
 if srcStr <> '' then
 begin
 dbgrdDepositInvestments.DataSource.DataSet.Filter := srcStr;
 dbgrdDepositInvestments.DataSource.DataSet.Filtered := True;
 end
 else
 begin
 dbgrdDepositInvestments.DataSource.DataSet.Filtered := False;
 end;
end;
procedure TForm1.btnDepositInvestmentsSearchClearClick(Sender: TObject);
begin
edtDepositInvestmentsSearchNameClient.Text := '';
edtDepositInvestmentsSearchNameBank.Text := '';
end;
procedure TForm1.edtDepositInvestmentsSearchNameBankChange(
 Sender: TObject);
var
 srcStr: string;
begin
 srcStr := GetDepositInvestmentsSearchQuery(edtDepositInvestmentsSearchNameClient.Text, edtDepositInvestmentsSearchNameBank
 if srcStr <> '' then
 begin
 dbgrdDepositInvestments.DataSource.DataSet.Filter := '';
 dbgrdDepositInvestments.DataSource.DataSet.Filtered := False;
 dbgrdDepositInvestments.DataSource.DataSet.Filter := srcStr;
 dbgrdDepositInvestments.DataSource.DataSet.Filtered := True;
 end
 else
 begin
 dbgrdDepositInvestments.DataSource.DataSet.Filtered := False;
 end;
end;
procedure TForm1.FormCreate(Sender: TObject);
var
 clientsSet, banksSet: TRecSet;
 i, l: Integer;
begin
 clientsSet := DataModule2.GetClients();
 l := Length(clientsSet);
 i := 0;
 while i < l do
 begin
 cbbDepositInvestmentsNameClient.AddItem(clientsSet[i].Name, TObject(clientsSet[i].Id));
 Inc(i);
 end;
end;
procedure TForm1.cbbDepositInvestmentsNameClientChange(Sender: TObject);
var
 i: Integer;
begin
 i := cbbDepositInvestmentsNameClient.ItemIndex;
 if i <> -1 then
 begin
 lblDepositInvestmentDebugHint.Caption := IntToStr(Integer(cbbDepositInvestmentsNameClient.Items.
 end;
end;
procedure TForm1.edtDepositInvestmentsSumChange(Sender: TObject);
var
 i: Integer;
begin
 try
 i := StrToInt(edtDepositInvestmentsSum.Text);
 except
 on Exception : EConvertError do
 i := 1;
 end;
 if i < 1 then
 begin
 i := 1;
 end;
 edtDepositInvestmentsSum.Text := IntToStr(i);
end;
procedure TForm1.btnDepositInvestmentsCreateSubmitClick(Sender: TObject);
var
 i, clientId, bankId, rate, sum, depositId: Integer;
 isPercentSet: Boolean;
 date, time: string;
begin
 i := cbbDepositInvestmentsNameClient.ItemIndex;
 if i < 0 then
 begin
 lblDepositInvestmentDebugHint.Caption := 'Название клиента обязательно';
 Exit;
 end;
 depositId := StrToInt(edtDepositInvestmentDepositId.Text);
 sum := StrToInt(edtDepositInvestmentsSum.Text);
 date := DateToStr(dtpDepositInvestmentsDateFrom.Date);
 time := TimeToStr(dtpDepositInvestmentsCreateTimeFrom.DateTime);
 clientId := Integer(cbbDepositInvestmentsNameClient.Items.Objects[i]);
 lblDepositInvestmentDebugHint.Caption := 'Сохранено: ' + edtDepositInvestmentDepositId.Text + IntToStr
 DataModule2.AddDepositInvestment(depositId, sum, clientId, dtpDepositInvestmentsDateFrom.Date, dtpDepositInvestmentsCreateTimeFrom
 dbgrdDepositInvestments.Refresh;
end;
procedure TForm1.edtDepositInvestmentDepositIdChange(Sender: TObject);
var
 i: Integer;
begin
try
 i := StrToInt(edtDepositInvestmentDepositId.Text);
 except
 on Exception : EConvertError do
 i := 1;
 end;
 if i < 1 then
 begin
 i := 1;
 end;
 edtDepositInvestmentDepositId.Text := IntToStr(i);
end;
end.
