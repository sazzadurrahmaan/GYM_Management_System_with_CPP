#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#define Max 1000000

using namespace std;

struct GymMember {
    int id;
    string name;
    string address;
    string phone;
    string email;
    string payInfo;
};

int cnt = 1, in = 0;

GymMember G[Max];

int getInteger() {
    int n;
    cin >> n;
    while(!cin.good()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Incorrect Input, Please try again!\n";
        cin >> n;
    }
    return n;
}

void WriteData() {
    ofstream file("gymMember.dat");
    for(int i=0; i<cnt-2; ++i)
        file << G[i].id << "*" << G[i].name <<"*" << G[i].address << "*" << G[i].phone
        << " " << G[i].email << " " << G[i].payInfo << "\n";
    file.close();
    cout << "Data saved successfully\n";
}

void addMemeber() {
    int id;
    string name, address, phone, email, info;
    cout << "Enter ID: ";
    id = getInteger();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter Address: ";
    getline(cin, address);
    cout << "Enter Phone Number: ";
    cin >> phone;
    cout << "Enter Email Address: ";
    cin >> email;
    cout << "Enter Payment Info: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, info);
    ofstream file("gymMember.dat", ios::out|ios::app);
    file << id << "*" << name << "*" << address << "*" << phone << " " << email << " " << info << "\n";
    cout << "Data stored\n";
    file.close();
}

void StringSeperator(string Data) {
    int s = Data.size(), cnt1 = 0;
    G[in].id = 0;
    for(int i=0; i<s; ++i) {
        if(cnt1==0) {
            if(Data[i]!='*') {
                G[in].id *= 10;
                G[in].id += Data[i]-'0';
            }
            else {
                ++cnt1;
                continue;
            }
        }
        else if(cnt1==1) {
            if(Data[i]!='*') G[in].name += Data[i];
            else {
                ++cnt1;
                continue;
            }
        }
        else if(cnt1==2) {
            if(Data[i]!='*') G[in].address += Data[i];
            else {
                ++cnt1;
                continue;
            }
        }
        else if(cnt1==3) {
            if(Data[i]!=' ') G[in].phone += Data[i];
            else {
                ++cnt1;
                continue;
            }
        }
        else if(cnt1==4) {
            if(Data[i]!=' ') G[in].email += Data[i];
            else {
                ++cnt1;
                continue;
            }
        }
        else G[in].payInfo += Data[i];
    }
    ++in;
    ++cnt;
}

void dataRetrive() {
    ifstream file("gymMember.dat");
    string data;
    if(file.fail()) cout << "failed to open file\n";
    else {
        if(file.peek()==EOF) {
            cout << "No member found\n";
            file.close();
        }
        else {
            while(!file.eof()) {
                getline(file, data);
                StringSeperator(data);
            }
            file.close();
        }
    }
}

void display() {
    if(cnt==1) dataRetrive();
    for(int i=0; i<cnt-2; ++i) {
        cout << "ID: " << G[i].id << "\n" << "Name: " << G[i].name << "\n" <<
        "Address: " << G[i].address << "\n" <<
        "Phone: " << G[i].phone << "\n"
        << "Email: " << G[i].email << "\n"
        << "Payment Information: "
        << G[i].payInfo << "\n\n";
    }
}

void Delete_data() {
    ofstream file("gymMember.dat");
    if(file.fail()) cout << "unable to delete data file not found\n";
    else {
        file.close();
        cout << "Data deleted successfully\n";
    }
}

int Linear_Search(string n) {
    if(cnt==1) dataRetrive();
    for(int i=0; i<cnt-2; ++i) if(G[i].name==n) return i;
    return -1;
}

void Delete_Seperately() {
    string name;
    cout << "Enter the name to delete: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);
    if(cnt==1) dataRetrive();
    int index = Linear_Search(name);
    if(index==-1) cout << "Deletion failed, Data not found\n";
    else {
        for(int i=index; i<cnt-3; ++i) {
            G[i].id = G[i+1].id;
            G[i].name = G[i+1].name;
            G[i].address = G[i+1].address;
            G[i].phone = G[i+1].phone;
            G[i].email = G[i+1].email;
            G[i].payInfo = G[i+1].payInfo;
        }
        --cnt;
        WriteData();
        cout << "Successfully deleted member " << name << "\n";
    }
}

void selection_sort() {
    if(cnt>1) {
        for(int i=0; i<cnt-2; ++i)
            for(int j=i+1; j<cnt-2; ++j)
                if(G[i].id>G[j].id) {
                    swap(G[i], G[j]);
                }
        cout << "Successfully sorted\n";
    }
    else {
        dataRetrive();
        if(cnt>1) {
            for(int i=0; i<cnt-2; ++i)
                for(int j=i+1; j<cnt-2; ++j)
                    if(G[i].id>G[j].id) {
                        swap(G[i], G[j]);
                    }
            cout << "Successfully sorted\n";
        }
        else cout << "Sorting failed, data not found\n";
    }
}

void updateMember() {
    if(cnt==1) dataRetrive();
    string name, address, phone, email, payInfo;
    cout << "Enter name to search: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);
    int index = Linear_Search(name);
    cout << "Name: " << G[index].name << "\n" <<
    "Address: " << G[index].address << "\n" <<
    "Phone: " << G[index].address << "\n" <<
    "Payment: " << G[index].payInfo << "\n";
    cout << "Enter new name: ";
    getline(cin, name);
    cout << "Enter new Address: ";
    getline(cin, address);
    cout << "Enter Phone number: ";
    cin >> phone;
    cout << "Enter Email Address: ";
    cin >> email;
    cout << "Payment Info: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, payInfo);
    G[index].name = name;
    G[index].address = address;
    G[index].phone = phone;
    G[index].email = email;
    G[index].payInfo = payInfo;
    WriteData();
}

void profile(string name) {
    int index = Linear_Search(name);
    if(index!=-1)
        cout << "Name: " << G[index].name << "\n"
        << "Address: " << G[index].address << "\n"
        << "Phone: " << G[index].phone << "\n"
        << "Email: " << G[index].email << "\n"
        << "Payment Information: " << G[index].payInfo << "\n";
    else cout << "Information not found\n";
}

int main() {

    int c;
    string name;

    while(1) {
        cout << "Add member press 1\nShow all member's info press 2\n" <<
        "Delete all member's info press 3\nDelete member individually press 4\nSort the info press 5\n"
        << "For search press 6\nUpdate Member info press 7\nExit press 8\n";
        c = getInteger();
        switch(c) {
            case 1:
                addMemeber();
                break;
            case 2:
                display();
                break;
            case 3:
                Delete_data();
                break;
            case 4:
                Delete_Seperately();
                break;
            case 5:
                selection_sort();
                break;
            case 6:
                cout << "Enter name for search: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, name);
                profile(name);
                break;
            case 7:
                updateMember();
                break;
            case 8:
                exit(0);
            default:
                cout << "Wrong Input\n";
        }
    }

    return 0;

}
