#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;
// Lop SinhVien dai dien cho mot sinh vien voi cac thuoc tinh co ban
class SinhVien {
private:
    long long int msv;
    string ten;
    int tuoi;
    float diem;

public:
		//Tao 1 constructor co tham so de khoi tao ten,tuoi,diem va tu dong tang ma sinh vien
    SinhVien() {}
    SinhVien(long long int msv, string ten, int tuoi, float diem)
        : msv(msv), ten(ten), tuoi(tuoi), diem(diem) {}

    void HienThiThongTin() const {
        cout << "| " << setw(3) << msv << " | " << setw(22) << left << ten << " | " << setw(4) << tuoi
             << " | " << setw(4) << diem << " |" << endl;// Hien thi thong tin cua sinh vien theo dinh dang bang
    }

    // Các phuong thuc public de truy cap các thuoc tính private
    long long int GetMSV() const {
        return msv;
    }

    string GetTen() const {
        return ten;
    }

    int GetTuoi() const {
        return tuoi;
    }

    float GetDiem() const {
        return diem;
    }
   void SetTuoi(int newTuoi) {
        tuoi = newTuoi;
    }

    void SetDiem(float newDiem) {
        diem = newDiem;
    }
};

// Lop QuanLySinhVien voi chuc nang quan ly danh sach sinh vien
class QuanLySinhVien {
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

        do {
            cout << "Nhap ma sinh vien: ";
            cin >> msv;
            if (msv < 10000 || msv > 99999) {
                cout << "Ma sinh vien khong hop le! Vui long nhap lai!" << endl;// MSV quy dinh la so tu nhien co 5 chu so, neu nhap sai se nhap lai
            }
        } while (msv < 10000 || msv > 99999);

        cin.ignore();
        cout << "Nhap ten sinh vien: ";
        getline(cin, ten);

        cout << "Nhap tuoi sinh vien: ";
        cin >> tuoi;

        cout << "Nhap diem sinh vien: ";
        cin >> diem;

        ThemSinhVien(SinhVien(msv, ten, tuoi, diem));
        cout << "Da them sinh vien: " << ten << endl;
    }
	
		// Hien thi danh sach sinh vien
    void HienThiDanhSach() {
        if (danhSachSinhVien.empty()) {
            cout << "Chua co thong tin sinh vien." << endl;
        } else {
            cout << "| MSV   | Ten                    | Tuoi | Diem |" << endl;
            cout << setfill('-') << setw(46) << "" << setfill(' ') << endl;
            for (const auto& sv : danhSachSinhVien) {
                sv.HienThiThongTin();
            }
        }
    }
	
	// Sap xep danh sach sinh vien theo msv theo thu tu tang dan
    void SapXepTheoMSV() {
        sort(danhSachSinhVien.begin(), danhSachSinhVien.end(), [](const SinhVien& a, const SinhVien& b) {
        		// Lambda function de so sanh msv cua hai sinh vien
        	//Lambda function tra ve true neu msv cua a nho hon msv cua b de dam bao sap xep theo thu tu tang dan.
            return a.GetMSV() < b.GetMSV();
        });
    }
	
	// Sap xep danh sach sinh vien theo diem giam dan
    void SapXepTheoDiem() {
        sort(danhSachSinhVien.begin(), danhSachSinhVien.end(), [](const SinhVien& a, const SinhVien& b) {
            return a.GetDiem() > b.GetDiem();
        });
    }
	
	// Sap xep danh sach sinh vien theo tuoi tang dan
    void SapXepTheoTuoi() {
        sort(danhSachSinhVien.begin(), danhSachSinhVien.end(), [](const SinhVien& a, const SinhVien& b) {
            return a.GetTuoi() < b.GetTuoi();
        });
    }
	
	// Xoa sinh vien theo ma sinh vien (MSV) 
    void XoaSinhVien(int msv) {
    		// Su dung ham remove_if de di chuyen cac sinh vien có MSV trung khop den cuoi danh sach
        auto it = remove_if(danhSachSinhVien.begin(), danhSachSinhVien.end(),
                            [msv](const SinhVien& sv) { return sv.GetMSV() == msv; });
			// Kiem tra xem co sinh vien can xoa khong
        if (it != danhSachSinhVien.end()) {
        	// Thuc hien viec xoa sinh vien co MSV trung khop
            danhSachSinhVien.erase(it, danhSachSinhVien.end());
            cout << "Da xoa sinh vien co MSV: " << msv << endl;
        } else {
            cout << "Khong tim thay sinh vien co MSV: " << msv << endl;
        }
    }
	
	
		// Sua thong tin cua sinh vien có STT trung khop
    void SuaSinhVien(int msv) {
    		// Su dung ham find_if de tim sinh viên co STT trung khop
        auto it = find_if(danhSachSinhVien.begin(), danhSachSinhVien.end(),
                          [msv](const SinhVien& sv) { return sv.GetMSV() == msv; });
		// Kiem tra xem co sinh viên can sua không
        if (it != danhSachSinhVien.end()) {
            cout << "Nhap thong tin moi cho sinh vien :" << endl;

            int tuoiMoi;
            float diemMoi;

            cout << "Nhap tuoi sinh vien: ";
            cin >> tuoiMoi;

            cout << "Nhap diem sinh vien: ";
            cin >> diemMoi;

         // Cap nhat thong tin
        it->SetTuoi(tuoiMoi);
        it->SetDiem(diemMoi);

            cout << "Da cap nhat thong tin cho sinh vien co MSV: " << msv << endl;
        } else {
            cout << "Khong tim thay sinh vien co MSV: " << msv << endl;
        }
    }
	
	// Tim sinh vien co MSV trung khop voi tham so MSV
    void TimKiemTheoMSV(int msv) const {
        auto it = find_if(danhSachSinhVien.begin(), danhSachSinhVien.end(),
                          [msv](const SinhVien& sv) { return sv.GetMSV() == msv; });
		
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
            diemTrungBinh += sv.GetDiem();
			// Kiem tra va cap nhat sinh vien co diem cao nhat
            if (sv.GetDiem() > diemCaoNhat) {
                diemCaoNhat = sv.GetDiem();
                sinhVienDiemCaoNhat = sv.GetMSV();
            }
			// dem so luong sinh vien theo tung khoang diem
            if (sv.GetDiem() >= 8) {
                soSinhVienGioi++;
            } else if (sv.GetDiem() >= 5) {
                soSinhVienKha++;
            } else {
                soSinhVienTB++;
            }
        }
		
			// Tinh diem trung binh cua tat ca sinh vien
        diemTrungBinh /= danhSachSinhVien.size();
		
		 // In thong tin thong ke
        cout << "Diem trung binh cua cac sinh vien: " << diemTrungBinh << endl;
		
		// Kiem tra và in thong tin sinh vien co diem cao nhat
        if (sinhVienDiemCaoNhat != -1) {
            auto it = find_if(danhSachSinhVien.begin(), danhSachSinhVien.end(),
                              [sinhVienDiemCaoNhat](const SinhVien& sv) {
                                  return sv.GetMSV() == sinhVienDiemCaoNhat;
                              });

            if (it != danhSachSinhVien.end()) {
                cout << "Sinh vien co diem cao nhat: " << it->GetTen() << " (Diem: " << it->GetDiem() << ")" << endl;
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
    	// Mo mot tep tin de ghi thông tin
        ofstream outFile(tenFile);
         // Kiem tra xem viec mo tep co thanh cong hay khong
        if (!outFile.is_open()) {
            cout << "Khong the mo tao file " << tenFile << endl;
            return; // Tra ve neu không the mo tep
        }
		
			// Ghi thông tin ve sinh viên xuong tep
        for (const auto& sv : danhSachSinhVien) {
            outFile << sv.GetMSV() << " " << sv.GetTen() << " " << sv.GetTuoi() << " " << sv.GetDiem() << endl;
        }
		
		  // Ðóng tep tin sau khi ghi xong
        outFile.close();
    }
};

int show(int luaChon) {
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

    while (true) {
        int luaChon = show(luaChon);
        system("cls");
		
		// Thuc hien chuc nang tuong ung voi lua chon
        switch (luaChon) {
            case 1:
                quanLy.HienThiDanhSach();
                break;
            case 2:
                quanLy.NhapThongTinSinhVien();
                break;
            case 3:
                int msvSua;
                cout << "Nhap MSV sinh vien can sua: ";
                cin >> msvSua;
                quanLy.SuaSinhVien(msvSua);
                break;
            case 4:
                int msvXoa;
                cout << "Nhap MSV sinh vien can xoa: ";
                cin >> msvXoa;
                quanLy.XoaSinhVien(msvXoa);
                break;
            case 5:
                int msvTimKiem;
                cout << "Nhap MSV sinh vien can tim: ";
                cin >> msvTimKiem;
                quanLy.TimKiemTheoMSV(msvTimKiem);
                break;
            case 6:
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

        if (!tiep) {
            cout << "Ket thuc chuong trinh.";
            return 0;
        }
    }

    return 0;
}

