#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;
// Lop SinhVien dai dien cho mot sinh vien voi cac thuoc tinh co ban
class SinhVien {
public:
   long long int msv;
    string ten;
    int tuoi;
    float diem;

    SinhVien (){}
	//Tao 1 constructor co tham so de khoi tao ten,tuoi,diem va tu dong tang ma sinh vien
    SinhVien(int msv,string ten, int tuoi, float diem) : msv(msv),ten(ten), tuoi(tuoi), diem(diem) {}

	
    void HienThiThongTin() const {
        cout << "| " << setw(3) << msv << " | " << setw(22) << left << ten << " | " << setw(4) << tuoi
             << " | " << setw(4) << diem << " |" << endl;// Hien thi thong tin cua sinh vien theo dinh dang bang
    }
};


// Lop QuanLySinhVien ke thua tu lop SinhVien v� them chuc nang quan ly danh sach sinh vien
class QuanLySinhVien:public SinhVien {
private:
    vector<SinhVien> danhSachSinhVien;// Danh sach sinh vien

public:
	// Them sinh vien vao danh sach
    void ThemSinhVien(const SinhVien& sv) {
        danhSachSinhVien.push_back(sv);
    }
	 // Nhap thong tin moi cho sinh vien va them vao danh sach
    void NhapThongTinSinhVien() {
    	long long int msv;
        string ten;
        int tuoi;
        float diem;
        do{
		cout<<"Nhap ma sinh vien: ";
		cin>>msv;
		if (msv<10000 || msv >99999){
			cout<<"Ma sinh vien khong hop le! Vui long nhap lai!"<<endl;// MSV quy dinh la so tu nhien co 5 chu so, neu nhap sai se nhap lai
		}}
		while(msv<10000 || msv >99999);
		cin.ignore();
        cout << "Nhap ten sinh vien: ";
        getline(cin, ten);

        cout << "Nhap tuoi sinh vien: ";
        cin >> tuoi;

        cout << "Nhap diem sinh vien: ";
        cin >> diem;

        ThemSinhVien(SinhVien(msv,ten, tuoi, diem));
        cout << "Da them sinh vien: " << ten << endl;
        
    }
	// Hien thi danh sach sinh vien

    void HienThiDanhSach()  {
    	if(danhSachSinhVien.empty()){
    		cout << "Chua co thong tin sinh vien." << endl;}
    	else {

     	cout << "| MSV   | Ten                    | Tuoi | Diem |" << endl;
        cout << setfill('-') << setw(46) << "" << setfill(' ') << endl;
        for (const auto& sv : danhSachSinhVien) {
            sv.HienThiThongTin();
        }

    	}
    }


    void SapXepTheoMSV() {
    	// Sap xep danh sach sinh vien theo msv theo thu tu tang dan
        sort(danhSachSinhVien.begin(), danhSachSinhVien.end(), [](const SinhVien& a, const SinhVien& b) {
        	// Lambda function de so sanh msv cua hai sinh vien
        	//Lambda function tra ve true neu msv cua a nho hon msv cua b de dam bao sap xep theo thu tu tang dan.
            return a.msv < b.msv;
        });
    }

    void SapXepTheoDiem() {
    	// Sap xep danh sach sinh vien theo diem giam dan
        sort(danhSachSinhVien.begin(), danhSachSinhVien.end(), [](const SinhVien& a, const SinhVien& b) {
            return a.diem > b.diem;
        });
    }

    void SapXepTheoTuoi() {
    	// Sap xep danh sach sinh vien theo tuoi tang dan
        sort(danhSachSinhVien.begin(), danhSachSinhVien.end(), [](const SinhVien& a, const SinhVien& b) {
            return a.tuoi < b.tuoi;
        });
    }

	// Xoa sinh vien theo ma sinh vien (MSV) 
    void XoaSinhVien(int msv) {
    	// Su dung ham remove_if de di chuyen cac sinh vien c� MSV trung khop den cuoi danh sach
        auto it = remove_if(danhSachSinhVien.begin(), danhSachSinhVien.end(),
                            [msv](const SinhVien& sv) { return sv.msv == msv; });
		// Kiem tra xem co sinh vien can xoa khong
        if (it != danhSachSinhVien.end()) {
        	// Thuc hien viec xoa sinh vien co MSV trung khop
            danhSachSinhVien.erase(it, danhSachSinhVien.end());
           
            cout << "Da xoa sinh vien co MSV: " << msv << endl;
        } else {
            cout << "Khong tim thay sinh vien co MSV: " << msv << endl;
        }
    }
	
	// Sua thong tin cua sinh vien c� STT trung khop
    void SuaSinhVien(int msv) {
    	// Su dung ham find_if de tim sinh vi�n co STT trung khop
        auto it = find_if(danhSachSinhVien.begin(), danhSachSinhVien.end(),
                          [msv](const SinhVien& sv) { return sv.msv == msv; });

		// Kiem tra xem co sinh vi�n can sua kh�ng
        if (it != danhSachSinhVien.end()) {
            cout << "Nhap thong tin moi cho sinh vien :" << endl;

            int tuoiMoi;
            float diemMoi;

            cout << "Nhap tuoi sinh vien: ";
            cin >> tuoiMoi;

            cout << "Nhap diem sinh vien: ";
            cin >> diemMoi;

            // Cap nhat thong tin
            it->tuoi = tuoiMoi;
            it->diem = diemMoi;

            cout << "Da cap nhat thong tin cho sinh vien co MSV: " << msv << endl;
        } else {
            cout << "Khong tim thay sinh vien co MSV: " << msv << endl;
        }
    }

    void TimKiemTheoMSV(int msv) const {
    	// Tim sinh vien co MSV trung khop voi tham so MSV
        auto it = find_if(danhSachSinhVien.begin(), danhSachSinhVien.end(),
                          [msv](const SinhVien& sv) { return sv.msv == msv; });
		
		 // Kiem tra xem co sinh vien nao co MSV trung khop hay khong
        if (it != danhSachSinhVien.end()) {
        	cout << "| MSV   | Ten                    | Tuoi | Diem |" << endl;
        cout << setfill('-') << setw(40) << "" << setfill(' ') << endl;
            it->HienThiThongTin();
        } else {
            cout << "Khong tim thay sinh vien co MSV: " << msv << endl;
        }
    }

    void ThongKe() const {
        float diemTrungBinh = 0;
        float diemCaoNhat = 0;
        int sinhVienDiemCaoNhat = -1;
        int soSinhVienGioi = 0;
        int soSinhVienKha = 0;
        int soSinhVienTB = 0;
		
		 // Tinh tong diem cua tat ca sinh vien
        for (const auto& sv : danhSachSinhVien) {
            diemTrungBinh += sv.diem;
			
			// Kiem tra va cap nhat sinh vien co diem cao nhat
            if (sv.diem > diemCaoNhat) {
                diemCaoNhat = sv.diem;
                sinhVienDiemCaoNhat = sv.msv;
            }
			
			 // dem so luong sinh vien theo tung khoang diem
            if (sv.diem >= 8) {
                soSinhVienGioi++;
            } else if (sv.diem >= 5) {
                soSinhVienKha++;
            } else {
                soSinhVienTB++;
            }
        }
		
		// Tinh diem trung binh cua tat ca sinh vien
        diemTrungBinh /= danhSachSinhVien.size();
		
		  // In thong tin thong ke
        cout << "Diem trung binh cua cac sinh vien: " << diemTrungBinh << endl;
		
		// Kiem tra v� in thong tin sinh vien co diem cao nhat
        if (sinhVienDiemCaoNhat != -1) {
            auto it = find_if(danhSachSinhVien.begin(), danhSachSinhVien.end(),
                              [sinhVienDiemCaoNhat](const SinhVien& sv) {
                                  return sv.msv == sinhVienDiemCaoNhat;
                              });

            if (it != danhSachSinhVien.end()) {
                cout << "Sinh vien co diem cao nhat: " << it->ten << " (Diem: " << it->diem << ")" << endl;
            }
        }
		
		 // Tinh ti le sinh vien theo tung khoang diem va in thong tin
        float tiLeGioi = static_cast<float>(soSinhVienGioi) / danhSachSinhVien.size() * 100;
        float tiLeKha = static_cast<float>(soSinhVienKha) / danhSachSinhVien.size() * 100;
        float tiLeTB = static_cast<float>(soSinhVienTB) / danhSachSinhVien.size() * 100;

        cout << "Ti le sinh vien gioi (>8): " << tiLeGioi << "%" << endl;
        cout << "Ti le sinh vien kha (5-8): " << tiLeKha << "%" << endl;
        cout << "Ti le sinh vien trung binh (<5): " << tiLeTB << "%" << endl;
    }

    void LuuThongTinXuongFile(const string& tenFile) {
    	// Mo mot tep tin de ghi th�ng tin
        ofstream outFile(tenFile);
        // Kiem tra xem viec mo tep co thanh cong hay khong
    if (!outFile.is_open()) {
        cout << "Khong the mo tao file " << tenFile << endl;
        return; // Tra ve neu kh�ng the mo tep
    }
    	// Ghi th�ng tin ve sinh vi�n xuong tep
        for (const auto& sv : danhSachSinhVien) {
            outFile << sv.msv << " " << sv.ten << " " << sv.tuoi << " " << sv.diem << endl;
        }
        
         // ��ng tep tin sau khi ghi xong
        outFile.close();
    }
};

int show(int luaChon){
	cout << "----------MENU----------" << endl;
    cout << "1. In danh sach sinh vien" << endl;
    cout << "2. Them sinh vien" << endl;
    cout << "3. Sua sinh vien" << endl;
    cout << "4. Xoa sinh vien" << endl;
    cout << "5. Tim kiem" << endl;
    cout << "6. Sap xep" << endl;
    cout << "7. Thong ke" << endl;
    cout << "8. Luu thong tin xuong file" << endl;
    cout << "0. Thoat" << endl;
    cout << "Nhap lua chon cua ban: ";
    cin >> luaChon;
    cin.ignore();
    return luaChon;
}


int main() {
    QuanLySinhVien quanLy;
    
    while (true){
		int luaChon = show(luaChon);
		system ("cls");
        // Thuc hien chuc nang tuong ung voi lua chon
        switch (luaChon) {
            case 1:
                quanLy.HienThiDanhSach();
                break;
            case 2:
                quanLy.NhapThongTinSinhVien();
                break;
            case 3:
                // Chuc nang sua sinh vien
                int msvSua;
                cout << "Nhap MSV sinh vien can sua: ";
                cin >> msvSua;
                quanLy.SuaSinhVien(msvSua);
                break;
            case 4:
                // Chuc nang xoa sinh vien
                int msvXoa;
                cout << "Nhap MSV sinh vien can xoa: ";
                cin >> msvXoa;
                quanLy.XoaSinhVien(msvXoa);
                break;
            case 5:
                // Chuc nang tim kiem
                int msvTimKiem;
                cout << "Nhap MSV sinh vien can tim: ";
                cin >> msvTimKiem;
                quanLy.TimKiemTheoMSV(msvTimKiem);
                break;
            case 6:
                // Hien thi menu sap xep va thuc hien sap xep
                int luaChonSapXep;
                cout << "1. Sap xep theo MSV" << endl;
                cout << "2. Sap xep theo diem" << endl;
                cout << "3. Sap xep theo tuoi" << endl;
                cout << "Nhap lua chon cua ban: ";
                cin >> luaChonSapXep;
                switch (luaChonSapXep) {
                    case 1:
                        quanLy.SapXepTheoMSV();
                        break;
                    case 2:
                        quanLy.SapXepTheoDiem();
                        break;
                    case 3:
                        quanLy.SapXepTheoTuoi();
                        break;
                    default:
                        cout << "Lua chon khong hop le!" << endl;
                }
                break;
            case 7:
                // Chuc nang thong ke
                quanLy.ThongKe();
                break;
            case 8:
                quanLy.LuuThongTinXuongFile("DanhSachSinhVien.txt");
                cout << "Da luu thong tin xuong file." << endl;
                break;
            case 0:
                cout << "Ket thuc chuong trinh." << endl;
                return 0;
            default:
                cout << "Lua chon khong hop le!" << endl;
        }
        
        cout << "Ban co muon tiep tuc! (1/0) "; 
        
        bool tiep;
        cin >> tiep;
        
        if (!tiep){
        	cout << "Ket thuc chuong trinh.";
        	return 0;
		}
        
    } 

    return 0;
}