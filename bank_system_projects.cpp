#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;
const string file_name = "Bank.txt";
const string delimiter = "/##/";
struct info {
    string id;
    string pin_code;
    string name;
    string phone;
    string balance;
    bool mark_for_delete = false;

};
bool one_more() {
    char ch;
    cout << "Do you want to ?\n";
    cin >> ch;
    return (tolower(ch) == 'y');

}
enum options {
    enum_show_all_clients = 1,
    enum_add_new_client = 2,
    enum_find_client = 3,
    enum_delete_client = 4,
    enum_update_client = 5,
    enum_transection = 6,
    enum_exit = 7,

};
enum option_trans {
    enu_deposit = 1,
    enu_withdrew = 2,
    enu_total = 3,
};
short read_postive() {
    short number;
    do {
        cout << "Enter what do you want to do ?\n";
        cin >> number;


    } while (number < 0 || number > 8);
    return number;
}
short read_postive_1_4() {
    short number;
    do {
        cout << "Enter what do you want to do ?\n";
        cin >> number;


    } while (number < 0 || number > 5);
    return number;
}
void show_main_screen();
bool find_account(info& found_client, string account_number, vector <info> clients);


vector<string > split(string line, string delim = delimiter) {

    vector<string > client;
    int len = delim.length();
    int pos = 0;
    string sword = "";
    while ((pos = line.find(delim)) != string::npos) {
        sword = line.substr(0, pos);
        if (sword != "") {
            client.push_back(sword);
        }
        line.erase(0, pos + len);
    }
    if (line != "") {
        client.push_back(line);
    }
    return client;

}
info convert_line_to_record(string  line) {
    info person;
    vector <string > cleint = split(line);
    person.id = cleint[0];
    person.pin_code = cleint[1];
    person.name = cleint[2];
    person.phone = cleint[3];
    person.balance = cleint[4];
    return person;
}
void display_one_client(info cleint) {
    cout << "\nClint's information \n";
    cout << "=========================================\n";
    cout << "Account :" << cleint.id;
    cout << "\npin cod:" << cleint.pin_code;
    cout << "\nname:" << cleint.name;
    cout << "\nPhone  :" << cleint.phone;
    cout << "\nbalance:" << cleint.balance;
    cout << "\n=========================================\n";
}

info read_client(string accoun_number) {
    info person;

    person.id = accoun_number;
    cout << "Enter Pin code : \n";
    getline(cin, person.pin_code);
    cout << "Enter Name :\n";
    getline(cin, person.name);
    cout << "Enter phone number :\n";
    getline(cin, person.phone);
    cout << "Enter the balance :\n";
    getline(cin, person.balance);
    return person;
}
string convert_to_line(info client, string delim) {
    string line = "";
    line += client.id + delim;
    line += client.pin_code + delim;
    line += client.name + delim;
    line += client.phone + delim;
    line += client.balance;
    return line;

}
void add_to_file(string client_line) {
    fstream file;
    file.open(file_name, ios::out | ios::app);
    if (file.is_open()) {
        file << client_line << endl;
        file.close();
    }
}

vector<info> load_client_data_to_vector() {
    fstream file;
    vector<info> clients;
    file.open(file_name, ios::in);

    if (file.is_open()) {
        string line;
        info cl;
        while (getline(file, line)) {
            cl = convert_line_to_record(line);
            clients.push_back(cl);
        }
        file.close();

    }
    return clients;

}
void print_vector_clients(info client) {
    cout << "|" << left << setw(15) << client.id;
    cout << "|" << left << setw(10) << client.pin_code;
    cout << "|" << left << setw(30) << client.name;
    cout << "|" << left << setw(15) << client.phone;
    cout << "|" << left << setw(15) << client.balance;
}
void print_all_clients_data(vector<info> clients) {
    cout << "\t\t\t\t Client list (" << clients.size() << ") clients\n\n";
    cout << "===========================================================================================\n\n";
    cout << "|" << left << setw(15) << "Account number";
    cout << "|" << left << setw(10) << "Pin cod";
    cout << "|" << left << setw(30) << "Name";
    cout << "|" << left << setw(15) << "Phone number";
    cout << "|" << left << setw(15) << "Balance";
    cout << "\n\n===========================================================================================\n";
    for (info& cl : clients) {
        print_vector_clients(cl);
        cout << endl;

    }
    cout << "===========================================================================================\n";
}
void show_client_function() {
    system("cls");
    vector <info> clients = load_client_data_to_vector();
    print_all_clients_data(clients);
} // this function to show all function


bool find_account(info& found_client, string account_number, vector <info> clients) {
    for (info& client : clients) {
        if (client.id == account_number) {
            found_client = client;
            return true;
        }

    }
    return false;
}
void find_account_function() {
    vector <info> clients = load_client_data_to_vector();
    info found_client;
    cout << "Enter your account number to find?\n";
    string account;
    getline(cin >> ws, account);
    if (find_account(found_client, account, clients)) {
        cout << "*****************************************\n";
        cout << "\t\tAccount found\n";
        cout << "*****************************************\n";
        display_one_client(found_client);

    }
    else
    {
        cout << "Account with number  " << account << " not found\n";
    }
    if (one_more()) {
        system("cls");
        find_account_function();
    }
    else
    {
        cout << "Exit....";
    }
} // this is to find account // this function to find account

bool mark_for_delet(vector <info>& cleint, string account_numnber) {
    for (info& cl : cleint) {
        if (cl.id == account_numnber) {
            cl.mark_for_delete = true;
            return true;
        }
    }
    return false;

}
vector<info> save_to_file(vector <info> clients) {
    fstream file;
    file.open(file_name, ios::out);
    string line;
    if (file.is_open()) {
        for (info cl : clients) {
            if (cl.mark_for_delete == false) {
                line = convert_to_line(cl, delimiter);
                file << line << endl;


            }
        }
        file.close();

    }
    return clients;
}
bool delete_client(string account_number, vector<info>& clients) {
    info client;
    char ch;
    if (find_account(client, account_number, clients)) {
        display_one_client(client);
        cout << "Are you sure do you want to delete this client?(Y or N)\n";
        cin >> ch;
        if (tolower(ch) == 'y') {
            mark_for_delet(clients, account_number);
            save_to_file(clients);
            // refresh
            clients = load_client_data_to_vector();
            cout << "Deleted successfully.....\n";
            return true;
        }
    }
    else
    {
        cout << "Account with number (" << account_number << ") not found\n";
    }
    return false;
}
void delete_function() {
    vector<info> clients;
    clients = load_client_data_to_vector();
    cout << "Enter the account number to delete\n";
    string account_number;
    getline(cin >> ws, account_number);
    delete_client(account_number, clients);

} // this is for delete function

info read_client_for_update(string account_number) {
    info client;
    client.id = account_number;
    cout << "Enter Pin code : \n";
    getline(cin >> ws, client.pin_code);
    cout << "Enter Name :\n";
    getline(cin, client.name);
    cout << "Enter phone number :\n";
    getline(cin, client.phone);
    cout << "Enter the balance :\n";
    getline(cin, client.balance);
    return client;


}
bool update_client(string account_number, vector<info>& clients) {
    info client;
    char ch;
    char a;
    if (find_account(client, account_number, clients)) {
        display_one_client(client);
        cout << "\nAre you sure do you want to update this client's information?(y or n)\n";
        cin >> ch;
        if (tolower(ch) == 'y') {
            for (info& cl : clients) {
                if (cl.id == account_number) {
                    cl = read_client_for_update(account_number);
                    break;
                }
            }
            clients = save_to_file(clients);
            cout << "\nUpdated successfully.....\n";
            return true;

        }
    }
    else {
        cout << "\nAccount with number(" << account_number << ") not found....\n";

    }

    return false;
}
void update_function() {
    vector<info> clients = load_client_data_to_vector();
    cout << "\nEnter Account Number to Update...\n";
    string account_number;
    getline(cin >> ws, account_number);
    update_client(account_number, clients);

} // this is for update function

void add_client_function() {
    info client;
    string line;
    string account_number;
    vector<info> clients;

    bool add_more = true;

    while (add_more) {
        system("cls");
        clients = load_client_data_to_vector();  // Always reload in case of updates

        cout << "Enter account number:\n";
        getline(cin >> ws, account_number);

        if (find_account(client, account_number, clients)) {
            cout << "This one already exists...\n";
            display_one_client(client);
            cout << "Press to try again\n";
            system("pause > 0");

            continue;  // Ask again
        }

        client = read_client(account_number);
        line = convert_to_line(client, delimiter);
        add_to_file(line);
        cout << "Added to file successfully\n";

        add_more = one_more();  // Ask if user wants to add another
    }

    cout << "Exit...\n";
}

void show_add_screen() {
    cout << "\n-----------------------------------\n";
    cout << "\tAdd a new client Screen";
    cout << "\n-----------------------------------\n";
    add_client_function();
}
void show_update_screen() {
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";
    update_function();
}
void show_delete_screen() {
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Info Screen";
    cout << "\n-----------------------------------\n";
    delete_function();
}
void show_find_screen() {
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Info Screen";
    cout << "\n-----------------------------------\n";
    find_account_function();
}
void Show_end() {
    cout << "***********************************\n\n";
    cout << "Program End :-)\n\n";
    cout << "***********************************\n\n";

}
void return_main_menu() {
    cout << "Press any key to go back to main menu....\n";
    system("pause>0");
    show_main_screen();
}

void show_trans_menu(); // declare show transactions
void return_trans_menu() {
    cout << "Press any key to go back to transaction menu....\n";
    system("pause>0");
    show_trans_menu();
}

string convert(string str, int amount) {
    int tem = stoi(str);
    tem = tem + amount;
    str = to_string(tem);
    return str;

}

void deposit(string account_number, vector<info>& clients) {
    info client;
    int amount = 0;
    if (find_account(client, account_number, clients))
    {
        int total_amount = 0;

        display_one_client(client);
        cout << "How much do you want to deposit\n";
        cin >> amount;
        cout << "\nAre you sure do you want to deposit to this account ?(Y or N)\n";
        char ch;
        cin >> ch;
        if (tolower(ch) == 'y') {
            for (info& cl : clients) {
                if (cl.id == account_number) {
                    total_amount = stoi(cl.balance) + amount;
                    cl.balance = convert(cl.balance, amount);
                    break;
                }
            }
            clients = save_to_file(clients);
            cout << "\nAmount has deposit successfully\n";
            cout << "\n***********************************\n\n";
            cout << "The total amount in this account is: " << total_amount << endl;


        }
        else
        {
            cout << "Deposit cancelled\n";
        }
    }
    else
    {
        cout << "Account with(" << account_number << ") not found";
    }
}
void deposit_screen() {
    cout << "-------------Deposit-------------------\n";
    vector<info> clients = load_client_data_to_vector();
    cout << "enter account number \n";
    string account;
    cin >> account;
    deposit(account, clients);
}

void withdrew(string account_number, vector<info>& clients) {
    info client;
    int amount = 0;
    if (find_account(client, account_number, clients))
    {
        int total_amount = 0;
        display_one_client(client);
        cout << "How much do you want to withdrew\n";
        cin >> amount;
        cout << "\nAre you sure do you want to withdrew from this account ?(Y or N)\n";
        char ch;
        cin >> ch;
        if (tolower(ch) != 'y') {
            cout << "Withdrew cancelled\n";
            return;
        }
        else {
            for (info& cl : clients) {
                if (cl.id == account_number) {
                    if ((stoi(cl.balance)) >= amount)
                    {
                        total_amount = stoi(cl.balance) - amount;
                        cl.balance = convert(cl.balance, (amount * -1));
                        break;

                    }
                    else
                    {
                        cout << "The amount you want to withdrew it is not enough\n";
                        break;
                    }

                }
            }
            clients = save_to_file(clients);
            cout << "The amount has withdrawn successfully\n";
            cout << "\n***********************************\n\n";
            cout << "The total amount in this account is: " << total_amount << endl;
            cout << "\n***********************************\n\n";
        }
    }
    else
    {
        cout << "Account with(" << account_number << ") not found";
    }

}
void withdrew_screen() {
    vector<info> clients = load_client_data_to_vector();
    string account_number;
    cout << "Enter the account number\n";
    cin >> account_number;
    withdrew(account_number, clients);
}

string total() {
    vector<info> clients = load_client_data_to_vector();
    long total_amount = 0;
    for (info cl : clients) {
        total_amount += stoi(cl.balance);
    }
    return (to_string(total_amount));

}
void print_total_balance(info client) {
    cout << "|" << left << setw(15) << client.id;
    cout << "|" << left << setw(30) << client.name;
    cout << "|" << left << setw(15) << client.balance << endl;
}
void show_total() {
    vector<info> clients = load_client_data_to_vector();
    cout << "\n---------------------------------------------------------------------\n";
    cout << "|" << left << setw(15) << "Account number";
    cout << "|" << left << setw(30) << "Name";
    cout << "|" << left << setw(15) << "Balance" << endl;
    cout << "\n---------------------------------------------------------------------\n";
    for (info cl : clients) {
        print_total_balance(cl);

    }
    cout << "\n---------------------------------------------------------------------\n";
    cout << "The Total balances for all accounts is :" << total() << endl;




}
void perform_trans(option_trans number) {
    switch (number)
    {
    case option_trans::enu_deposit:
        system("cls");
        deposit_screen();
        return_trans_menu();
        break;
    case option_trans::enu_withdrew:
        system("cls");
        withdrew_screen();
        return_trans_menu();
        break;
    case option_trans::enu_total:
        system("cls");
        show_total();
        return_trans_menu();
        break;
    default:
        system("cls");
        show_main_screen();
        break;
    }

}


void show_trans_menu() {
    system("cls");
    cout << "===============================================================================================\n\n";
    cout << "\t\t\tTranscation Screen \n";
    cout << "\n===============================================================================================\n\n";
    cout << "\t\t[1]. Deposit\n";
    cout << "\t\t[2]. Withdrew\n";
    cout << "\t\t[3]. Total\n";
    cout << "\t\t[4]. Go to Main Menu\n";
    cout << "===============================================================================================\n\n";
    perform_trans(option_trans(read_postive_1_4()));


}
void perform_main_menu(options chosen) {
    switch (chosen)
    {
    case options::enum_show_all_clients:
        system("cls");
        show_client_function();
        return_main_menu();
        break;
    case options::enum_add_new_client:
        system("cls");
        show_add_screen();
        return_main_menu();

        break;
    case options::enum_find_client:
        system("cls");
        show_find_screen();
        return_main_menu();

        break;
    case options::enum_delete_client:
        system("cls");
        show_delete_screen();
        return_main_menu();

        break;
    case options::enum_update_client:
        system("cls");
        show_update_screen();
        return_main_menu();
        break;
    case options::enum_transection:
        system("cls");
        show_trans_menu();
        break;

    default:
        Show_end();
        cout << "Exit.......\n";
        break;
    }

}

void show_main_screen() {
    system("cls");
    cout << "===============================================================================================\n\n";
    cout << "\t\t\tMain Screen \n";
    cout << "\n===============================================================================================\n\n";
    cout << "\t\t[1]. Show All Clients\n";
    cout << "\t\t[2]. Add a New Client\n";
    cout << "\t\t[3]. Find Client\n";
    cout << "\t\t[4]. Delete  Client\n";
    cout << "\t\t[5]. Update Client\n";
    cout << "\t\t[6]. transaction screen\n";
    cout << "\t\t[7]. Exit.....\n\n";
    cout << "===============================================================================================\n\n";
    perform_main_menu((options)read_postive());



}

int main()

{

    show_main_screen();
}
