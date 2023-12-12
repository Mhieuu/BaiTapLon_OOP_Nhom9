#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;
// Lop SinhVien dai dien cho mot sinh vien voi cac thuoc tinh co ban
class SinhVien {
public:
    static int msvCounter;// Bien static de theo doi ma sinh vien 
    int msv;
    string ten;
    int tuoi;
    float diem;

    SinhVien() {
        msv = ++msvCounter; // Tang so thu tu moi khi tao doi tuong moi
    }
	//Tao 1 constructor co tham so de khoi tao ten,tuoi,diem va tu dong tang ma sinh vien
    SinhVien(string ten, int tuoi, float diem) : ten(ten), tuoi(tuoi), diem(diem) 
	{
	msv = ++msvCounter;
    }
	
    void HienThiThongTin() const {
        cout << "| " << setw(3) << msv << " | " << setw(22) << left << ten << " | " << setw(4) << tuoi
             << " | " << setw(4) << diem << " |" << endl;// Hien thi thong tin cua sinh vien theo dinh dang bang
    }
};

int SinhVien::msvCounter = 9998;// Khoi tao bien static

// Lop QuanLySinhVien ke thua tu lop SinhVien và them chuc nang quan ly danh sach sinh vien
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
        string ten;
        int tuoi;
        float diem;

        cout << "Nhap ten sinh vien: ";
        getline(cin, ten);

        cout << "Nhap tuoi sinh vien: ";
        cin >> tuoi;

        cout << "Nhap diem sinh vien: ";
        cin >> diem;

        ThemSinhVien(SinhVien(ten, tuoi, diem));
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


    void SapXepTheoTen() {
    	// Sap xep danh sach sinh vien theo ten theo thu tu tang dan
        sort(danhSachSinhVien.begin(), danhSachSinhVien.end(), [](const SinhVien& a, const SinhVien& b) {
        	// Lambda function de so sanh ten cua hai sinh vien
        	//Lambda function tra ve true neu ten cua a nho hon ten cua b de dam bao sap xep theo thu tu tang dan.
            return a.ten < b.ten;
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
    	// Su dung ham remove_if de di chuyen cac sinh vien có MSV trung khop den cuoi danh sach
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
	
	// Sua thong tin cua sinh vien có STT trung khop
    void SuaSinhVien(int msv) {
    	// Su dung ham find_if de tim sinh viên co STT trung khop
        auto it = find_if(danhSachSinhVien.begin(), danhSachSinhVien.end(),
                          [msv](const SinhVien& sv) { return sv.msv == msv; });

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
		
		// Kiem tra và in thong tin sinh vien co diem cao nhat
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
    	// Mo mot tep tin de ghi thông tin
        ofstream outFile(tenFile);
        // Kiem tra xem viec mo tep co thanh cong hay khong
    if (!outFile.is_open()) {
        cout << "Khong the mo tao file " << tenFile << endl;
        return; // Tra ve neu không the mo tep
    }
    	// Ghi thông tin ve sinh viên xuong tep
        for (const auto& sv : danhSachSinhVien) {
            outFile << sv.msv << " " << sv.ten << " " << sv.tuoi << " " << sv.diem << endl;
        }
        
         // Ðóng tep tin sau khi ghi xong
        outFile.close();
    }
};

int main() {
    QuanLySinhVien quanLy;
    int luaChon;

    do {
        // Hien thi menu
        cout << "MENU:" << endl;
        cout << "1. In danh sach sinh vien" << endl;
        cout << "2. Them sinh vien" << endl;
        cout << "3. Sua sinh vien" << endl;
        cout << "4. Xoa sinh vien" << endl;
        cout << "5. Tim kiem" << endl;
        cout << "6. Sap xep" << endl;
        cout << "7. Thong ke" << endl;
        cout << "8. Luu thong tin xuong file" << endl;
        cout << "0. Thoat" << endl;

        // Nhap lua chon tu nguoi dung
        cout << "Nhap lua chon cua ban: ";
        cin >> luaChon;
        cin.ignore(); // Ðoc ky tu Enter trong bo nho dem

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
                cout << "1. Sap xep theo ten" << endl;
                cout << "2. Sap xep theo diem" << endl;
                cout << "3. Sap xep theo tuoi" << endl;
                cout << "Nhap lua chon cua ban: ";
                cin >> luaChonSapXep;
                switch (luaChonSapXep) {
                    case 1:
                        quanLy.SapXepTheoTen();
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
                break;
            default:
                cout << "Lua chon khong hop le!" << endl;
        }
    } while (luaChon != 0);

    return 0;
}

