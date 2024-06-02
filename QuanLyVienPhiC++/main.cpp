#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <regex>
#include <conio.h>
using namespace std;

class VienPhi {
public:
    string code;    //Mã viện phí
    string name;    //Tên viện phí
    unsigned long fee;  //Giá viện phí

    void display() const {  //Hiển thị các thuộc tính
        cout << "Ma: " << code;
        cout << ", Ten: " << name;
        cout << ", Gia: " << fee << endl;
    }
};

void menu();
void readFromFile(vector<VienPhi>&);
void writeToFile(const vector<VienPhi>&);
bool kiemTraMaVienPhi(string);
bool kiemTraTrungMa(const vector<VienPhi>&, string);
void add(vector<VienPhi>&);
void display(const vector<VienPhi>&);
void modify(vector<VienPhi>&);
void deleteVP(vector<VienPhi>&);
void arrange(vector<VienPhi>&);
void findVP(const vector<VienPhi>&);
void cal(const vector<VienPhi>&);
void exitVP(const vector<VienPhi>&);

void menu() {      //Hiển thị màn hình lựa chọn
        system("cls");
        cout << "1. Tao vien phi\n";
        cout << "2. Hien thi vien phi\n";
        cout << "3. Sua vien phi\n";
        cout << "4. Xoa vien phi\n";
        cout << "5. Sap xep vien phi\n";
        cout << "6. Tim vien phi\n";
        cout << "7. In hoa don vien phi\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
}

void readFromFile(vector<VienPhi>& dsVienPhi) {
    ifstream file("vienphi.dat");
    if (!file) {
        cout << "Khong the mo file vienphi.dat!\n";
        return;
    }
    dsVienPhi.clear(); // Xóa dữ liệu hiện có trong vector trước khi đọc từ file.
    string code, name;
    int fee;
    while (file >> code >> ws && getline(file, name) && file >> fee) {
        VienPhi vp;
        vp.code = code;
        vp.name = name;
        vp.fee = fee;
        dsVienPhi.push_back(vp);
    }
    file.close();
}

void writeToFile(const vector<VienPhi>& dsVienPhi) {
    ofstream file("vienphi.dat");
    if (!file.is_open()) {
        cout << "Khong the mo file vienphi.dat de ghi!\n";
        return;
    }
    for (const auto& vp : dsVienPhi) {
        file << vp.code << endl << vp.name << endl << vp.fee << endl;
    }
    file.close();
}

bool kiemTraMaVienPhi(string code) {
    if (code.length() != 3)
        return false;
    if (code[0] != 'T' && code[0] != 'D' && code[0] != 'P')
        return false;
    for (int i = 1; i < code.length(); ++i) {
        if (!isdigit(code[i]))
            return false;
    }
    return true;
}

bool kiemTraTrungMa(const vector<VienPhi>& dsVienPhi, string code) {
    for (const auto& item : dsVienPhi) {
        if (item.code == code) {
            return true; // Mã đã tồn tại
        }
    }
    return false; // Mã chưa tồn tại
}

void add(vector<VienPhi>& dsVienPhi) {
    int n;
    while (true) {
        cout << "Nhap so luong vien phi can them: ";
        if (!(cin >> n)) {
            cout << "Loi: Ban phai nhap mot so nguyen. Vui long thu lai.\n";
            cin.clear(); // Xóa trạng thái lỗi của cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ nhớ đệm của cin
        }
        else {
            break; // Thoát khỏi vòng lặp nếu nhập thành công
        }
    }
    for (int i = 0; i < n; ++i) {
        VienPhi vp;
        do {
        cout << "Nhap ma vien phi: ";
        cin >> vp.code;

        if (!kiemTraMaVienPhi(vp.code)) {
            cout << "Ma vien phi khong hop le. Vui long nhap lai." << endl;
            continue;
        }

        if (kiemTraTrungMa(dsVienPhi, vp.code)) {
            cout << "Ma vien phi da ton tai. Vui long nhap lai." << endl;
            continue;
        }
        break;
    } while (true);
        cout << "Nhap ten vien phi: ";
        cin.ignore();
        getline(cin, vp.name);
        while (true) {
        cout << "Nhap gia vien phi: ";
        if (!(cin >> vp.fee)) {
            cout << "Loi: Ban phai nhap mot so nguyen. Vui long nhap lai.\n";
            cin.clear(); // Xóa trạng thái lỗi của cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
        dsVienPhi.push_back(vp);
    }
}

void display(const vector<VienPhi>& dsVienPhi) {
    for (const auto& vp : dsVienPhi) {
        vp.display();
    }
}

void modify(vector<VienPhi>& dsVienPhi) {
    string code;
    cout << "Nhap ma vien phi can sua: ";
    cin >> code;
    bool found = false;
    for (auto& vp : dsVienPhi) {
        if (vp.code == code) {
            cout << "Nhap thong tin moi:\n";
            cout << "Nhap ten vien phi moi: ";
            cin.ignore();
            getline(cin, vp.name);
            cout << "Nhap gia vien phi moi: ";
            cin >> vp.fee;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Khong tim thay ma vien phi!\n";
    }
}

void deleteVP(vector<VienPhi>& dsVienPhi) {
    string code;
    cout << "Nhap ma vien phi can xoa: ";
    cin >> code;
    auto it = remove_if(dsVienPhi.begin(), dsVienPhi.end(), [&code](VienPhi& vp) {
        return vp.code == code;
    });
    if (it != dsVienPhi.end()) {
        dsVienPhi.erase(it, dsVienPhi.end());
        cout << "Xoa thanh cong!\n";
    } else {
        cout << "Khong tim thay ma vien phi!\n";
    }
}

void arrange(vector<VienPhi>& dsVienPhi) {
    int choice;
    cout << "1. Sap xep theo ma\n";
    cout << "2. Sap xep theo ten\n";
    cout << "3. Sap xep theo gia\n";
    cout << "Nhap lua chon: ";
    if (!(cin >> choice)) {
        cout << "Nhap khong hop le!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
        cout << "Enter any key to continue...";
        getch();
    }
    switch (choice) {
        case 1:
            sort(dsVienPhi.begin(), dsVienPhi.end(), [](const VienPhi& a, const VienPhi& b) {
                return a.code < b.code;
            });
            break;
        case 2:
            sort(dsVienPhi.begin(), dsVienPhi.end(), [](const VienPhi& a, const VienPhi& b) {
                return a.name < b.name;
            });
            break;
        case 3:
            sort(dsVienPhi.begin(), dsVienPhi.end(), [](const VienPhi& a, const VienPhi& b) {
                return a.fee < b.fee;
            });
            break;
        default:
            cout << "Lua chon khong hop le!\n";
            break;
    }
}

void findVP(const vector<VienPhi>& dsVienPhi){
	int choice;
    cout << "1. Tim kiem bang ma\n";
    cout << "2. Tim kiem bang ten\n";
    cout << "Nhap lua chon: ";
    if (!(cin >> choice)) {
        cout << "Nhap khong hop le!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
        cout << "Enter any key to continue...";
        getch();
    }
    bool found = false;
    string code;
    string name;
    switch (choice) {
        case 1:
            cout << "Nhap ma vien phi muon tim kiem: ";
            cin >> code;
            for (auto& vp : dsVienPhi) {
                if (vp.code == code) {
                    vp.display();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Khong tim thay ma vien phi nay!\n";
            }
            break;
        case 2:
            cout << "Nhap ten vien phi muon tim kiem: ";
            cin >> name;
            for (auto& vp : dsVienPhi) {
                if (vp.name == name) {
                    vp.display();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Khong tim thay ten vien phi nay!\n";
            }
            break;
        default:
            cout << "Lua chon khong hop le!\n";
            break;
    }
}

void cal(const vector<VienPhi>& dsVienPhi){
    string ten, address, date;
    cout << "Nhap ten benh nhan: ";
    cin.ignore();
    getline(cin,ten);
    cout << "Nhap ngay thang nam sinh: ";
    getline(cin,date);
    cout << "Nhap dia chi: ";
    getline(cin,address);
    int x,y,z;
    unsigned long tongTien = 0;
    while (true) {
        cout << "So luong ma thuoc: ";
        if (!(cin >> x)) {
            cout << "Loi: Ban phai nhap mot so nguyen. Vui long thu lai.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
    string* thuoc;
    thuoc = new string[x];
    int* s;
    s = new int[x];
    if(x!=0){
        cout << "Nhap ma thuoc: ";
        for(int i = 0; i < x; i++){
            cin >> thuoc[i];
        }
        for(int i = 0; i < x; i++){
            for (auto& vp : dsVienPhi) {
                if (vp.code == thuoc[i]) {
                    cout << "So luong " << vp.name << ":";
                    cin >> s[i];
                    tongTien += s[i]*vp.fee;
                }
            }
        }
    }
    while (true) {
        cout << "So luong ma dich vu: ";
        if (!(cin >> y)) {
            cout << "Loi: Ban phai nhap mot so nguyen. Vui long thu lai.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
    string* dichvu;
    dichvu = new string[y];
    if(y!=0){
        cout << "Nhap ma dich vu: ";
        for(int i = 0; i < y; i++){
            cin >> dichvu[i];
        }
        for(int i = 0; i < y; i++){
            for (auto& vp : dsVienPhi) {
                if (vp.code == dichvu[i]) {
                    tongTien += vp.fee;
                }
            }
        }
    }
    string phong;
    cout << "Nhap ma phong da su dung: ";
    cin >> phong;
    VienPhi v;
    for (auto& vp : dsVienPhi) {
                if (vp.code == phong) {
                    v=vp;
                    while (true) {
                        cout << "So ngay su dung " << vp.name << ":";
                        if (!(cin >> z)) {
                            cout << "Loi: Ban phai nhap mot so nguyen. Vui long thu lai.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        else {
                            break;
                        }
                    }
                    tongTien += z*vp.fee;
                }
    }
    system("cls");
    cout << "**\t\tHOA DON VIEN PHI\t\t**" << endl;
    cout << "Ten benh nhan: " << ten << endl;
    cout << "Ngay thang nam sinh: " << date << endl;
    cout << "Dia chi: " << address << endl;
    cout << "Ma vien phi\tTen vien phi\tGia vien phi\tSo luong\tThanh tien\n";
    for(int i = 0; i < x; i++){
        for (auto& vp : dsVienPhi) {
            if (vp.code == thuoc[i]) {
            cout << vp.code << "\t\t" << vp.name << "\t\t" << vp.fee << "\t\t" << s[i] << "\t\t" << s[i]*vp.fee << endl;
            }
        }
    }
    for(int i = 0; i < y; i++){
        for (auto& vp : dsVienPhi) {
            if (vp.code == dichvu[i]) {
                cout << vp.code << "\t\t" << vp.name << "\t\t" << vp.fee << "\t\t" << 1 << "\t\t" << vp.fee << endl;
            }
        }
    }
    cout << v.code << "\t\t" << v.name << "\t\t" << v.fee << "\t\t" << z << "\t\t" << z*v.fee << endl;
    cout << "So tien can thanh toan: " << tongTien << endl;
    delete[]thuoc;
    delete[]s;
    delete[]dichvu;
}

void exitVP(const vector<VienPhi>& dsVienPhi){
    string s;
    cout << "Ban co chac chan muon thoat chuong trinh ?\nCo/khong ? ";
    cin.ignore();
    getline(cin, s);
    if (s == "co"||s == "Co") {
        writeToFile(dsVienPhi);
        printf("Ban da thoat chuong trinh!");
        exit(0);
    }
}
int main() {
	char choice;
	vector<VienPhi> dsVienPhi;
    readFromFile(dsVienPhi);
	while(1) {
		menu();
		cin >> choice;
		switch(choice) {
			case '1':
			    cout << "**\t\tTao vien phi\t\t**"<<endl;
                add(dsVienPhi);
                cout << "Enter any key to continue...";
				getch();
                break;
            case '2':
                cout << "**\t\tHien thi vien phi\t\t**"<<endl;
                display(dsVienPhi);
                cout << "Enter any key to continue...";
				getch();
                break;
            case '3':
                cout << "**\t\tSua vien phi\t\t**"<<endl;
                modify(dsVienPhi);
                cout << "Enter any key to continue...";
				getch();
                break;
            case '4':
                cout << "**\t\tXoa vien phi\t\t**"<<endl;
                deleteVP(dsVienPhi);
                cout << "Enter any key to continue...";
				getch();
                break;
            case '5':
                cout << "**\t\tSap xep vien phi\t\t**"<<endl;
                arrange(dsVienPhi);
                cout << "Enter any key to continue...";
				getch();
                break;
            case '6':
                cout << "**\t\tTim kiem vien phi\t\t**"<<endl;
                findVP(dsVienPhi);
                cout << "Enter any key to continue...";
				getch();
                break;
            case '7':
                cout << "**\t\tIn hoa don vien phi\t\t**"<<endl;
                cal(dsVienPhi);
                cout << "Enter any key to continue...";
				getch();
                break;
            case '0':
                exitVP(dsVienPhi);
                cout << "Enter any key to continue...";
                getch();
                break;
            default:
                cout << "Lua chon khong hop le!\n";
                getch();
                break;
		}
	}
	return 0;
}
