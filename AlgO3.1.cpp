#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

// EDDIT TEST
string ReaplaceWordsInString(string S1, string _ToChange, string _TheReplacement)
{
    size_t Pos;
    
    while ((Pos=S1.find(_ToChange)) != std::string::npos)
    {
        S1.replace(Pos, _ToChange.length(), _TheReplacement);   // to replace words in string : ( Position , length of the substetution , Newword )

        Pos = S1.find(_ToChange);
    }
    return S1;
}

// --------------- replace words in string Match Case or No match case {capital lettre or small lettre }

vector<string> SplitString(string Text, string Delim)
{
    vector<string> vText;
    size_t Position = Text.find(Delim);
    string Word = "";

    while (Position != std::string::npos)
    {
        Word = Text.substr(0, Position);
        if (Word !="")
        {
            vText.push_back(Word);
        }
        
        Text.erase(0, Position + Delim.length());
    }
    if (Text != "")
    {
        vText.push_back(Text);
    }
    return vText;
}

string JoinString(vector<string>Vstring, string Delim)
{
    string S1 = "";

    for (string& Rafik : Vstring)
    {
        S1 += Rafik + Delim;
    }
    S1.erase(S1.length() - Delim.length(), S1.length());
    return S1;
}

string LowerAllString(string S)
{
    for (int i = 0; i < S.length(); i++)
    {
        S[i] = tolower(S[i]);
    }
    return S;
}
// New solution create our replace fonctions \ not using .replace()
string ReaplaceWordsInStringsUsingSplitMatchingOrNot(string STR, string To_Change, string Prep, bool MAtchcase = 1)
{
    vector<string>VecString = SplitString(STR, " ");
     
    for (string& Raf : VecString)
    {
        if (MAtchcase)
        {
            if (Raf == To_Change)
            {
                Raf = Prep;
            }
        }
        else
        {
            Raf = LowerAllString(Raf);
            if (Raf == To_Change)
            {
                Raf = Prep;
            }
        }
    }
    return JoinString(VecString," ");
}

string RemouvePunctuations(string String)
{
    string S2 = "";
    for (size_t i = 0; i < String.length(); i++)
    {
        if (!ispunct(String[i]))
        {
            S2 += String[i];
        }
    }
    return S2;
}

/*
----------------------------------------------------------------------------------
                                Project Bank 1.0
----------------------------------------------------------------------------------
*/

const string UsersFileName = "Users.txt";   
const string ClientsFileName = "Clients.txt";   // --------- File Name -------------

struct User_Info {
    string userName;
    string password;
    short  permissions = 0;

    bool _MarkDelete = false;
    bool _Updated = false;
};
User_Info c_user;
struct Client_Info {
    string name;
    string acountNumb;
    string Code_pin;
    string Phone;
    int acount_amount = 0;
    bool MarkDelete = false;
    bool Updated = false;
};                   //  ------- struct Client info -------

enum Permissions {
    AllPerm = -1, Show_Client_List = 1 , Add_New_Client = 2 , Delete_Client = 4, Update_Client_Info = 8, Find_Client = 16, Transaction = 32, Manage_Users = 64
};

void Login();

vector<string> SplitStringToWords(string Data_Text, string Delimiter = "##")
{
    vector <string> vClient_Data;
    size_t Pos;
    string sWord = "";

    while ((Pos = Data_Text.find(Delimiter)) != std::string::npos)
    {
        sWord = Data_Text.substr(0, Pos);
        if (sWord != "")
        {
            vClient_Data.push_back(sWord);
        }

        Data_Text.erase(0, Pos + Delimiter.length());

    }
    if (Data_Text != "")
    {
        vClient_Data.push_back(Data_Text);
    }
    return vClient_Data;
}

User_Info LoadUsersData(string userlinetext, string Delimiter = "///")
{
    User_Info UserToLoad;
    vector <string> vLoadUser = SplitStringToWords(userlinetext, "///");

    UserToLoad.userName = vLoadUser[0];
    UserToLoad.password = vLoadUser[1];
    UserToLoad.permissions = stoi(vLoadUser[2]);

    return UserToLoad;
}

Client_Info LoadData(string Data_Text, string Delimitor = "##")
{
    Client_Info ClienLoaded;
    vector <string> vLoader = SplitStringToWords(Data_Text, Delimitor);
    ClienLoaded.acountNumb = vLoader[0];
    ClienLoaded.Code_pin = vLoader[1];
    ClienLoaded.name = vLoader[2];
    ClienLoaded.Phone = vLoader[3];
    ClienLoaded.acount_amount = stoi(vLoader[4]);

    return ClienLoaded;
}

void ShowTransactionMenuScreen();

string TronsformClientDataToLine(Client_Info TransData, string Delimiter = "##")
{
    string Data_Text = "";

    Data_Text = TransData.acountNumb + Delimiter;
    Data_Text += TransData.Code_pin + Delimiter;
    Data_Text += TransData.name + Delimiter;
    Data_Text += TransData.Phone + Delimiter;
    Data_Text += to_string(TransData.acount_amount);

    return Data_Text;
}

string TransformUserDataToLine(User_Info user, string Delim = "///")
{
    string Line = "";

    Line = user.userName + Delim;
    Line += user.password + Delim;
    Line += to_string (user.permissions);

    return Line;
}



bool ClientExistesByAccountNumber(string AccountNumb, string FileName)
{
    vector <Client_Info> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);   // read mod

    if (MyFile.is_open())
    {
        string Line;
        Client_Info Client;

        while (getline(MyFile, Line))
        {
            Client = LoadData(Line, "##");
            if (Client.acountNumb == AccountNumb)
            {
                MyFile.close();
                return true;
            }
        }
    }
    return false;
}

Client_Info ReadnewClientInfo()
{
    Client_Info ClientData;

    cout << "Enter Acount Number:\n";
    getline(cin >> ws, ClientData.acountNumb);
    while (ClientExistesByAccountNumber(ClientData.acountNumb, ClientsFileName))
    {
        cout << "\n Client With [" << ClientData.acountNumb << "] already Exists, Enter another Account Number";
        getline(cin >> ws, ClientData.acountNumb);
    }


    cout << "Enter Code Pin:\n";
    getline(cin, ClientData.Code_pin);
    cout << "Enter Name:\n";
    getline(cin, ClientData.name);
    cout << "Enter Phone Number:\n";
    getline(cin, ClientData.Phone);
    cout << "Etner Amount Of Client Acount:\n";
    cin >> ClientData.acount_amount;

    return ClientData;
}

vector <Client_Info> LoadClientDataFromFile(string FileName)
{
    fstream MyFile;              // file declaration
    string Line;
    vector <Client_Info> vAllClientsData;

    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {

        while (getline(MyFile, Line))
        {
            Client_Info Client = LoadData(Line);

            vAllClientsData.push_back(Client);
        }
    }

    MyFile.close();
    return vAllClientsData;
}

void PrintUserLineRecord(User_Info OneC)
{
    cout << "| " << left << setw(25) << OneC.userName << "| " << setw(25) << OneC.password << "| " << setw(15) << OneC.permissions << "| " << endl;

}

void PrintClientLineRecord(Client_Info OneC)
{
    cout << "| " << left << setw(15) << OneC.acountNumb << "| " << setw(10) << OneC.Code_pin << "| " << setw(35) << OneC.name << "| " << setw(20) << OneC.Phone << "| " << setw(15) << OneC.acount_amount << "|" << endl;

}

void PrintClientsBalances(Client_Info OneC)
{
    cout << "| " << left << setw(15) << OneC.acountNumb << "| " << setw(35) << OneC.name << "| " << setw(15) << OneC.acount_amount << "|" << endl;
}

void AddDataToFile(string FileName, string DataLine)
{
    fstream File;
    File.open(FileName, ios::out | ios::app);
    if (File.is_open())
    {
        File << DataLine << endl;
        File.close();
    }
}

short GetPermissions()
{
    char Answer;

    short Permissions = 0;
    short Perms = 1;


    cout << "\n Do you want to Give Full Access ? y/n ?";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        return -1;
    }

    cout << "\n Permissions is Like shown : Enter Nembers of Permission one by one (0 to Exite).\nShow_Client_List = 1.\nAdd_New_Client = 2.\nDelete_Client = 4.\nUpdate_Client_Info = 8.\nFind_Client = 16.\nTransaction = 32.\nManage_Users = 64." << endl;
    
    while (Perms != 0)
    {
        cin >> Perms;
        Permissions += Perms;
        
    }
    return Permissions;
}

/*
int ReadPermissionsToSet()
{
int Permissions = 0;
char Answer = 'n';
cout << "\nDo you want to give full access? y/n? ";
cin >> Answer;
if (Answer == 'y' || Answer == 'Y')
{
return -1;
}

cout << "\nDo you want to give access to : \n ";
cout << "\nShow Client List? y/n? ";
cin >> Answer;
if (Answer == 'y' || Answer == 'Y')
{
Permissions += enMainMenuePermissions::pListClients;
}
cout << "\nAdd New Client? y/n? ";
cin >> Answer;
if (Answer == 'y' || Answer == 'Y')
{
Permissions += enMainMenuePermissions::pAddNewClient;
}

cout << "\nDelete Client? y/n? ";
cin >> Answer;
if (Answer == 'y' || Answer == 'Y')
{
Permissions += enMainMenuePermissions::pDeleteClient;
}

cout << "\nUpdate Client? y/n? ";
cin >> Answer;
if (Answer == 'y' || Answer == 'Y')
{
Permissions += enMainMenuePermissions::pUpdateClients;
}

cout << "\nFind Client? y/n? ";
cin >> Answer;
if (Answer == 'y' || Answer == 'Y')
{
Permissions += enMainMenuePermissions::pFindClient;
}

cout << "\nTransactions? y/n? ";
cin >> Answer;
if (Answer == 'y' || Answer == 'Y')
{
Permissions += enMainMenuePermissions::pTranactions;
}

cout << "\nManage Users? y/n? ";
cin >> Answer;
if (Answer == 'y' || Answer == 'Y')
{
Permissions += enMainMenuePermissions::pManageUsers;
}
return Permissions;
}
*/  // Get Permmision

bool CheckAccessPermissions(Permissions perm)
{
    return (c_user.permissions == Permissions::AllPerm) ? true : (c_user.permissions & perm) ? true : false;
}

User_Info ReadNewUserInfo()
{
    User_Info user;
    cout << "\nEnter User Name: ";
    getline(cin >> ws, user.userName);
    cout << "\nEnter Pass Word: ";
    getline(cin >> ws, user.password);
    user.permissions = GetPermissions();
    return user;
}

void AddNewClient()
{
    Client_Info Client;
    Client = ReadnewClientInfo();
    AddDataToFile(ClientsFileName, TronsformClientDataToLine(Client, "##"));
}

void ADDNEWUSER()
{
    User_Info User;
    User = ReadNewUserInfo();
    AddDataToFile(UsersFileName, TransformUserDataToLine(User));

}

void AddClients()
{
    char Answer = 'Y';
    do
    {
        system("cls");
        cout << "Adding New Client :\n\n";

        AddNewClient();
        cout << "Adding a Client Successfully, Do You want to Add More ? \n \t \t Y : Yes / N : No" << endl;
        cin >> Answer;


    } while (toupper(Answer) == 'Y');

}

void PrintAllClientsDATA(vector<Client_Info>ClientsData)

{
    cout << "|--------------------------------------------------------------------------------------------------------|\n";
    cout << "|\t\t\t\t Current Clients Number : " << ClientsData.size() << " Client(s).                                   |" << endl;
    cout << "|--------------------------------------------------------------------------------------------------------|\n";
    cout << "| " << left << setw(15) << "Account Number" << "| " << setw(10) << "Pin Code" << "| " << setw(35) << "Owner Identity" << "| " << setw(20) << "Pnone Number" << "| " << setw(15) << "Current Amount" << "|" << endl;
    cout << "|--------------------------------------------------------------------------------------------------------|\n";
    for (Client_Info& PrintAll : ClientsData)
    {
        PrintClientLineRecord(PrintAll);
    }
    cout << "|--------------------------------------------------------------------------------------------------------|\n";


}

bool FindClientToDelete(string AccountNumber, vector<Client_Info> vClients, Client_Info& TheClient)
{
    for (Client_Info C : vClients)
    {
        if (AccountNumber == C.acountNumb)
        {
            TheClient = C;
           
            return true;
        }
    }
    return false;
}

string ReadAcountNumb()
{
    string AccNumb = "";
    cout << "Enter Account Numb To Search\n";
    cin >> AccNumb;
    return AccNumb;
}

void PrintOneClientRecords(Client_Info TheClient)
{
    cout << "Acount Number : " << TheClient.acountNumb << endl;
    cout << "Code_Pin : " << TheClient.Code_pin << endl;
    cout << "Client Name : " << TheClient.name << endl;
    cout << "Number Phone : " << TheClient.Phone << endl;
    cout << "Acount Balance = " << TheClient.acount_amount << endl;
}

vector <Client_Info> SaveClientsDataToFile(string FileName, vector<Client_Info> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out); // overWrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (Client_Info C : vClients)
        {
            if (C.MarkDelete == false)  // because we over write so we have to write just clients with false delete mark 
            {
                DataLine = TronsformClientDataToLine(C, "##");
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

bool MarkClientToDeleteIt(string AccountNumber, vector <Client_Info>& vClients)
{
    for (Client_Info& C : vClients)
    {
        if (C.acountNumb == AccountNumber)
        {
            C.MarkDelete = true;
            return true;
        }
    }
    return false;
}

Client_Info ChangeClientInfo(string AccountNumber)
{
    Client_Info Client;
    Client.acountNumb = AccountNumber;

    cout << "\n\n Enter PinCode:";
    getline(cin >> ws, Client.Code_pin);
    cout << "/Enter Name:";
    getline(cin, Client.name);
    cout << "Enter Phone Number:";
    getline(cin, Client.Phone);
    cout << "Enter Amount balance";
    cin >> Client.acount_amount;

    return Client;
}

bool DeleteClientByNumberAccount(string AccountNumber, vector<Client_Info>& vClients)
{
    Client_Info Client;
    char Answer = 'n';

    if (FindClientToDelete(AccountNumber, vClients, Client))
    {
        PrintOneClientRecords(Client);
        cout << "\nAre You Sure You Want Delete This Client ?\n";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientToDeleteIt(AccountNumber, vClients);
            SaveClientsDataToFile(ClientsFileName, vClients);
            vClients = LoadClientDataFromFile(ClientsFileName); // to refresh vector clients
            cout << "\n Client Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "Client With Account Number [" << AccountNumber << "] is Not Found!";
    }
    return false;
}

bool UpdateClientByAccNumb(string AccountNumber, vector <Client_Info>& vClients)
{
    Client_Info Client;
    char Answer = 'n';
    if (FindClientToDelete(AccountNumber, vClients, Client))
    {
        PrintOneClientRecords(Client);
        cout << "\n\n Updating Client ? Y/N\n";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (Client_Info& C : vClients)
            {
                if (C.acountNumb == AccountNumber)
                {
                    C = ChangeClientInfo(AccountNumber);
                    break;
                }
            }

        }
        SaveClientsDataToFile(ClientsFileName, vClients);

        cout << "\n\nClient Apdated Successfully!";
        return true;
    }

    return false;
}

void DepositByClientAmount(string AccountNumb, vector <Client_Info>& vClients)
{
    Client_Info TheClient;
    int depo = 0;
    char anwser = 'n';
    int NewSold = 0;
 
        cout << "\nPlease Enter Deposit amount ? " << endl;
        cin >> depo;
        cout << "\nAre you sure you want Deposit [" << depo << "] ? Y/N";
        cin >> anwser;
        if (anwser == 'Y' || anwser == 'y')
        {
            for (Client_Info& C : vClients) {
                if (C.acountNumb == AccountNumb)
                {
                    C.acount_amount += depo;
                    NewSold = C.acount_amount;
                    cout << "\n Your deposit is done succsesfully. Your Sold Now is: " << NewSold << endl;
                    break;
                }
                
            }
            SaveClientsDataToFile(ClientsFileName, vClients);
        }
    
}

void WithdrowByClientAmount(string AccountNumb, vector <Client_Info>& vClients)
{
    Client_Info TheClient;
    int Withdr = 0;
    char anwser = 'n';
    int NewSold = 0;

    cout << "\nPlease Enter Withdrow amount ? " << endl;
    cin >> Withdr;
    cout << "\nAre you sure you want Withdrow [" << Withdr << "] ? Y/N";
    cin >> anwser;
    if (anwser == 'Y' || anwser == 'y')
    {
        for (Client_Info& C : vClients) {
            if (C.acountNumb == AccountNumb)
            {
                if(C.acount_amount >= Withdr){
                C.acount_amount -= Withdr;
                NewSold = C.acount_amount;
                cout << "\n Your Withdrow is done succsesfully. Your Sold Now is: " << NewSold << endl;
                }
                else
                {
                    cout << "\nYou don't have this Amount in your balance!";
                }
                break;
            }

        }
        SaveClientsDataToFile(ClientsFileName, vClients);
    }

}

void ShowFindClientScreen()
{
    cout << "________________________________________\n";
    cout << "          Update Clients Screen\n";
    cout << "----------------------------------------\n";

    vector<Client_Info> vClient = LoadClientDataFromFile(ClientsFileName);
    Client_Info TheClient;
    string AccountNumber = ReadAcountNumb();
    
    if (FindClientToDelete(AccountNumber,vClient,TheClient))
    {
        PrintOneClientRecords(TheClient);
    }
    else
    
        cout << "\n Client With Account Number [" << AccountNumber << "] is not found!";
}

void ShowUpdateClientsScreen()
{
    cout << "________________________________________\n";
    cout << "          Update Clients Screen\n";
    cout << "----------------------------------------\n";

    vector <Client_Info> vClients = LoadClientDataFromFile(ClientsFileName);
    string AccountNumber = ReadAcountNumb();
    UpdateClientByAccNumb(AccountNumber, vClients);

}
void GoBackToMainMenu();
void ShowDeleteClientsScreen()
{
    if (!CheckAccessPermissions(Permissions::Delete_Client))
    {
        system("cls");
        cout << " Access Denied. Contact Admin or Supervisor...";

        GoBackToMainMenu();
    }


    cout << "________________________________________\n";
    cout << "          Delete Clients Screen\n";
    cout << "----------------------------------------\n";

    vector<Client_Info> vClients = LoadClientDataFromFile(ClientsFileName);
    string AccNumber = ReadAcountNumb();
    DeleteClientByNumberAccount(AccNumber, vClients);
}

void ShowAllClientScreen()
{
    vector<Client_Info>ClientsData = LoadClientDataFromFile(ClientsFileName);

    
        cout << "|--------------------------------------------------------------------------------------------------------|\n";
        cout << "|\t\t\t\t Current Clients Number : " << ClientsData.size() << " Client(s).                                   |" << endl;
        cout << "|--------------------------------------------------------------------------------------------------------|\n";
        cout << "| " << left << setw(15) << "Account Number" << "| " << setw(10) << "Pin Code" << "| " << setw(35) << "Owner Identity" << "| " << setw(20) << "Pnone Number" << "| " << setw(15) << "Current Amount" << "|" << endl;
        cout << "|--------------------------------------------------------------------------------------------------------|\n";
        for (Client_Info& PrintAll : ClientsData)
        {
            PrintClientLineRecord(PrintAll);
        }
        cout << "|--------------------------------------------------------------------------------------------------------|\n";
}

void ShowTotalBalances()
{
    vector<Client_Info>ClientsData = LoadClientDataFromFile(ClientsFileName);
    int TotalBalances = 0;

    cout << "|--------------------------------------------------------------------------------------------------------|\n";
    cout << "|\t\t\t\t       Balances List of : " << ClientsData.size() << " Client(s).                                   |" << endl;
    cout << "|--------------------------------------------------------------------------------------------------------|\n";
    cout << "| " << left << setw(15) << "Account Number" << "| " << setw(35) << "Owner Identity" << "| " << setw(15) << "Current Amount" << "|" << endl;
    cout << "|--------------------------------------------------------------------------------------------------------|\n";
    for (Client_Info& PrintAll : ClientsData)
    {
        PrintClientsBalances(PrintAll);
        TotalBalances += PrintAll.acount_amount;
    }
    cout << "|--------------------------------------------------------------------------------------------------------|\n";
    cout << "\t\t TOTAL BALANCES = ( " << TotalBalances << " )." << endl;
}

void ShowMainMenu();

enum enMainManueOptions {
    eListClient = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4,eMngUsers = 7, eFindClient = 5, eLogout = 8,eTransaction = 6
};         //------------- enum Operations ---------

enum enTransactions
{
    enDeposit = 1,enWithdrow =2,enTotalBalances = 3,enMainMenue=4
};

enum enUsers {
    enList = 1, enAddUSers = 2, enDeleteUSers = 3, enUpdateUSer = 4, enFindUser = 5, enMainMenueu = 6
};

User_Info LoadUsData(string Data_Text, string Delimitor = "///")
{
    User_Info USer;
    vector <string> vLoader = SplitStringToWords(Data_Text, Delimitor);
    USer.userName = vLoader[0];
    USer.password = vLoader[1];
    USer.permissions = stoi(vLoader[2]);

    return USer;
}

vector <User_Info> LoadUsersFromFile(string FileNM)
{
    fstream MyFile;
    string LINE;
    vector<User_Info> vUsers;

    MyFile.open(FileNM, ios::in);

    if (MyFile.is_open())
    {
        while (getline(MyFile,LINE)&& LINE != "")
        {
            User_Info USer = LoadUsData(LINE);
            
            vUsers.push_back(USer);
        }
    }
    MyFile.close();
    return vUsers;
}

bool DeleteUser(string username, vector<User_Info>& vUSers); // deff

void ShowAllUsersScreen()
{
    vector <User_Info> vecuser = LoadUsersFromFile(UsersFileName);

    cout << "|---------------------------------------------------------------------------------|\n";
    cout << "|\t\t\t\t Current  Users Number : " << vecuser.size() << " User(s).                                   |" << endl;
    cout << "|---------------------------------------------------------------------------------|\n";
    cout << "| " << left << setw(25) << "User Name" << "| " << setw(25) << "Pass Word" << "| " << setw(15) << "Permission"  << endl;
    cout << "|---------------------------------------------------------------------------------|\n";
    for (User_Info& PrintAll : vecuser)
    {
        PrintUserLineRecord(PrintAll);
    }
    cout << "|---------------------------------------------------------------------------------|\n";

}

void GoBackToMainMenu()
{
    cout << "\n Press any Key to go back to main menue...";
    system("Pause>0");
    ShowMainMenu();
}

void GobackToTransMenu()
{
    cout << "\nPress any key to go back ...";
    system("pause>0");
    system("cls");

    ShowTransactionMenuScreen();
}

void ShowAddNewClientsScreen()
{
    cout << "________________________________________\n";
    cout << "          Add New Clients Screen\n";
    cout << "----------------------------------------\n";

    AddClients();
}

void ShowDepositScreen()
{
    cout << "________________________________________\n";
    cout << "          Deposit Screen\n";
    cout << "----------------------------------------\n";

    Client_Info TheClient;
    vector<Client_Info>vClients = LoadClientDataFromFile(ClientsFileName);
    string AccNumb = ReadAcountNumb();
    

    if (FindClientToDelete(AccNumb, vClients, TheClient))
    {
        PrintOneClientRecords(TheClient);
        DepositByClientAmount(AccNumb, vClients);
    }
    else
        cout << "\n Client With Account Number [" << AccNumb << "] is not found!";
}

void ShowWithdrowScreen()
{
    cout << "________________________________________\n";
    cout << "          Withdrow Screen\n";
    cout << "----------------------------------------\n";

    Client_Info TheClient;
    vector<Client_Info>vClients = LoadClientDataFromFile(ClientsFileName);
    string AccNumb = ReadAcountNumb();


    if (FindClientToDelete(AccNumb, vClients, TheClient))
    {
        PrintOneClientRecords(TheClient);
        WithdrowByClientAmount(AccNumb, vClients);
    }
    else
        cout << "\n Client With Account Number [" << AccNumb << "] is not found!";


}

short ReadMainMenuOption()
{
    cout << "Choose what do you want to do? [1 - 7]";
    short OptionNumb;
    cin >> OptionNumb;
   
    return OptionNumb;
}

short ReadTransactionMenue()
{
    cout << "Choose What Do want to do? [1 to 4]" << endl;
    short TransOptionNumb;
    cin >> TransOptionNumb;

    return TransOptionNumb;
}

short ReadUserMenue()
{
    cout << "Choose What Do want to do? [1 to 6]" << endl;
    short userNumb;
    cin >> userNumb;

    return userNumb;
}

void ShowExitScreen()
{
    cout << "________________________________________\n";
    cout << "          Program Ends ^_^\n";
    cout << "----------------------------------------\n";
    exit(0);
}

void AddingNewUSer()
{
    char Answr = 'Y';
    do
    {
        cout << "\n Adding New User :\n";
        ADDNEWUSER();
        cout <<"\n Adding User sucssesfully , Add more ? Type : 'Y' or 'N' ? \n";
        cin >> Answr;

    } while (toupper(Answr) == 'Y');
}

void ShowAddUserScreen()
{
    cout << "________________________________________\n";
    cout << "          Add New USER Screen\n";
    cout << "----------------------------------------\n";
    AddingNewUSer();
}

void ShowUserManagmentMenu();

User_Info ChangeUserInfo(string username)
{
    User_Info ChngUser;
    ChngUser.userName = username;
    cout << "\nEnter New Pass Word :\n";
    getline(cin >> ws, ChngUser.password);
    cout << "Enter New Permissions :";
    ChngUser.permissions = GetPermissions();

        return ChngUser;
}

void GobacktoUserManagMenue()
{
    cout << "\n Press any Key to Go Back To User Manag Menue...";

    system("pause>0");
    ShowUserManagmentMenu();

}

string ReadUserName()
{
    string username;
    cout << "Enter a User Name to Searsh" << endl;
    getline(cin >> ws, username);
    return username;
}

void ShowDeleteUserScreen()
{
    cout << "________________________________________\n";
    cout << "          Delete  USER Screen\n";
    cout << "----------------------------------------\n";
    vector<User_Info>vUSers = LoadUsersFromFile(UsersFileName);
    string User_toSearch= ReadUserName();
    DeleteUser(User_toSearch, vUSers);
}

bool MarkUserToDelete(string username, vector<User_Info>& vUsers )
{
    for (User_Info& U: vUsers)
    {
        if (U.userName == username)
        {
            U._MarkDelete = true;
            return true;
        }

    }
    return false;
}

void PrintUSerRecord(User_Info TheUser)
{
    cout << "\nUser Info:\nUser Name : " << TheUser.userName << "\tPassWord : " << TheUser.password << "\tPermissions : " << TheUser.permissions;
}

bool FindUser(string username, vector<User_Info> vUSers,User_Info& TheUser)
{

    for (User_Info Us : vUSers)
    {
        if (Us.userName == username)
        {
            TheUser = Us;
            return true;
        }
    }
    return false;
}

vector<User_Info> SaveUsersDataToFile(string FileName, vector<User_Info>& vUSers)
{
    fstream File; string usData;
    File.open(FileName, ios::out);
    if (File.is_open())
    {
        for (User_Info U: vUSers )
        {
            if (!U._MarkDelete)
            {
                usData = TransformUserDataToLine(U);
                File << usData << endl;
            }

        }
        File.close();
    }
    return vUSers;
}

bool DeleteUser(string username, vector<User_Info>& vUSers)
{
    User_Info TheUser;
    char Answr = 'm';

    if (FindUser(username,vUSers,TheUser))
    {
        PrintUSerRecord(TheUser);
        
        cout << "\nAre you sue You want to delete User with Name " << TheUser.userName << " ? Y : Yes / N : No\n";
        cin >> Answr;
        if (toupper(Answr) == 'Y')
        {
            MarkUserToDelete(username, vUSers);
            SaveUsersDataToFile(UsersFileName, vUSers);
            vUSers = LoadUsersFromFile(UsersFileName);
            cout << "\n Client Deleted Successfully.";
            return true;
        } 

    }
    else
    {
        cout << "USer With USer Name [" << username << "] is Not Found!";
    }
    return false;
}

bool UpdateUser(string username, vector<User_Info>& vUSers)
{
    User_Info Updtuser;
    char answer = 'n';

    if (FindUser(username, vUSers, Updtuser))
    {
        PrintUserLineRecord(Updtuser);
        cout << "Excute Udating user ?: Y:yes / N:No .\n";
        cin >> answer;

        if (toupper(answer) == 'Y')
        {
            cout << "---- Updating User Info ----:\n";
            for (User_Info& CH : vUSers)
            {
                if (CH.userName == username)
                {
                    CH = ChangeUserInfo(username);
                    break;
                }

            }

        }
        SaveUsersDataToFile(UsersFileName, vUSers);
        return true;
    }
    else
    {
        cout << " \n\t  -_- USer Not Founded -_- ";
    }
    return false;
}

void ShowUpdateUserScreen()
{
    cout << "________________________________________\n";
    cout << "          Update USER Screen\n";
    cout << "----------------------------------------\n";

    string username = ReadUserName();
    vector <User_Info> vUSers = LoadUsersFromFile(UsersFileName);
    UpdateUser(username, vUSers);
}

void ShowFindUSerScrenn()
{
    cout << "________________________________________\n";
    cout << "          Find USER Screen\n";
    cout << "----------------------------------------\n\n";

    string username = ReadUserName();
    vector <User_Info> vUSers = LoadUsersFromFile(UsersFileName);
    User_Info UsrToFind;
    if (FindUser(username,vUSers,UsrToFind))
    {
        PrintUSerRecord(UsrToFind);
    }
    else
    {
        cout << "\t-_-  User Not Fonded  -_-" << endl;
    }

}

void PErformUserManagMenue(enUsers UsersMenue)
{
    switch (UsersMenue)
    {
    case enList:
        system("cls");
        ShowAllUsersScreen();
        GobacktoUserManagMenue();
        break;

    case enAddUSers:
        system("cls");
        ShowAddUserScreen();
        GobacktoUserManagMenue();
        break;

    case enDeleteUSers:
        system("cls");
        ShowDeleteUserScreen();
        GobacktoUserManagMenue();
        break;
    case enUpdateUSer:
        system("cls");
        ShowUpdateUserScreen();
        GobacktoUserManagMenue();
        break;
    case enFindUser:
        ShowFindUSerScrenn();
        GobacktoUserManagMenue();
        break;
    case enMainMenueu:
        ShowMainMenu();
        break;
    default:
        
        break;
    }

}

void ShowUserManagmentMenu()
{
    system("cls");
    cout << "****************************************\n";
    cout << "    Users Management Menue Screen\n";
    cout << "****************************************\n";
    cout << "\t[1] List Users.\n\t[2] Add New User.\n\t[3] Delete User.\n\t[4] Update User.\n\t[5] Find User.\n\t[6] Main Menue." << endl;
    cout << "****************************************\n";
    PErformUserManagMenue((enUsers)ReadUserMenue());
}

void PerformMainMenueOption(enMainManueOptions MainManueOption)
{
    switch (MainManueOption)
    {
    case eListClient:
    {
        system("cls");
        if (CheckAccessPermissions(Permissions::Show_Client_List))      // FIRST METHOD TO GET PERMMISION
        {
            ShowAllClientScreen();
        }
        else
        {
            cout << "You Have No Permmission Please Contact Admin.\n";
        }
        GoBackToMainMenu();
        break;
    }
    case eAddNewClient:
    {
        system("cls");
        if (c_user.permissions == -1 || (c_user.permissions & Permissions::Add_New_Client))  // SECOND METHOD TO GET PERMISSION
        {
            ShowAddNewClientsScreen();
        }
        else
        {
            cout << "You Have No Permmission Please Contact Admin.\n";
        }
        GoBackToMainMenu();

        break;
    }
        
    case eDeleteClient:
    {
        system("cls");
        ShowDeleteClientsScreen();      // THIRD METHOD IS TO GET THE CHECK INSIDE THE FUNCTION 
        GoBackToMainMenu();
        break;
     }
    case eUpdateClient:
    {
        system("cls");
        if (c_user.permissions == -1 || (c_user.permissions & Permissions::Update_Client_Info))
        {
            ShowUpdateClientsScreen();
        }
        else
        {
            cout << "You Have No Permmission Please Contact Admin.\n";
        }

        GoBackToMainMenu();
        break;
    }
    case eMngUsers:
    {
        system("cls");
        if (c_user.permissions == Permissions::AllPerm || (c_user.permissions & Permissions::Manage_Users))
        {
            ShowUserManagmentMenu();
        }
        else
        {
            cout << "You Have No Permmission Please Contact Admin.\n";
        }
        GoBackToMainMenu();
        break;
        
    }
    case eFindClient:
    {
        system("cls");
        if (c_user.permissions == -1 || (c_user.permissions & Permissions::Find_Client))
        {
            ShowFindClientScreen();
        }      
        else
        {
            cout << "You Have No Permmission Please Contact Admin.\n";
        }
        
        GoBackToMainMenu();
        break;
    }

    case eLogout:
        system("cls");
        Login();

        break;

    case enMainManueOptions::eTransaction:
        system("cls");
        if (c_user.permissions == -1 || (c_user.permissions & Permissions::Transaction))
        {
            ShowTransactionMenuScreen();
        }
        else
        {
            cout << "You Have No Permmission Please Contact Admin.\n";
        }
        GoBackToMainMenu();
        break;
    default:
        break;
    }
}

void PerformTransactionsMenue(enTransactions TransactionMenue)
{
    switch (TransactionMenue)
    {
    case enDeposit:
        system("cls");
        ShowDepositScreen();
        GobackToTransMenu();
        break;
    case enWithdrow:
        system("cls");
        ShowWithdrowScreen();
        GobackToTransMenu();
        break;
    case enTotalBalances:
        system("cls");
        ShowTotalBalances();
        GobackToTransMenu();
        break;
    case enMainMenue:
        system("cls");
        ShowMainMenu();
        break;
    default:
        break;
    }
}

void ShowTransactionMenuScreen()
{
    cout << "****************************************\n";
    cout << "       Transactions Menue Screen\n";
    cout << "****************************************\n";
    cout << "\t[1] Deposit.\n\t[2] Withdrow.\n\t[3] Total Balances.\n\t[4] Main Menue." << endl;
    cout << "****************************************\n";

    PerformTransactionsMenue((enTransactions)ReadTransactionMenue());
}
 
void ShowMainMenu()
{
    system("cls");
    cout << "****************************************\n";
    cout << "          Main Menue Screen\n";
    cout << "****************************************\n";
    cout << "\t[1] Show Client List.\n\t[2] Add New Client.\n\t[3] Delete Client.\n\t[4] Update Client Info.\n\t[5] Find Client.\n\t[6] Transaction.\n\t[7] Manage Users.\n\t[8] Logout." << endl;
    cout << "****************************************\n";
    
    PerformMainMenueOption((enMainManueOptions)ReadMainMenuOption());
}

bool UserChekName_Password(string username, string password, User_Info& c_user)
{
    vector<User_Info>vUser = LoadUsersFromFile(UsersFileName);

    for (User_Info U : vUser)
    {
        if (U.userName == username && U.password == password)
        {
            c_user = U;
            return true;
        }

    }
    return false;
}

bool LoadUSerInfo(string username, string password)
{

    if (UserChekName_Password(username, password, c_user)) // =========
    {
        return true;
    }
    else
    {
        return false;
    }
}


void Login()
{
    string username, Password;
    bool LoginFaild = 0;

    do
    {    
    system("cls");
    cout << "****************************************\n";
    cout << "            Login      Screen\n";
    cout << "****************************************\n";

       if (LoginFaild)
       {
        cout << "\n Invalide User Informations";
       }
    cout << "\nEnter User Name :" << endl;
    getline(cin >> ws, username);
    cout << "Enter PassWord :" << endl;
    getline(cin >> ws, Password);

    LoginFaild = !LoadUSerInfo(username, Password);


    
    } while (LoginFaild);
    ShowMainMenu();
}

int main()
{
    Login();

    system("pause>0");
    return 0;
}
