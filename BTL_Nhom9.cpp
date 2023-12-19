#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

class SinhVien {
private:
    long long int msv;
    string ten;
    int tuoi;
    float diem;

public:
    SinhVien() {}
    SinhVien(long long int msv, string ten, int tuoi, float diem)
        : msv(msv), ten(ten), tuoi(tuoi), diem(diem) {}

    void HienThiThongTin() const {
        cout << "| " << setw(3) << msv << " | " << setw(22) << left << ten << " | " << setw(4) << tuoi
             << " | " << setw(4) << diem << " |" << endl;
    }

    // Các phuong th?c public d? truy c?p các thu?c tính private
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

class QuanLySinhVien {
private:
    vector<SinhVien> danhSachSinhVien;

public:
    void ThemSinhVien(const SinhVien& sv) {
        danhSachSinhVien.push_back(sv);
    }

    void NhapThongTinSinhVien() {
        long long int msv;
        string ten;
        int tuoi;
        float diem;

        do {
            cout << "Nhap ma sinh vien: ";
            cin >> msv;
            if (msv < 10000 || msv > 99999) {
                cout << "Ma sinh vien khong hop le! Vui long nhap lai!" << endl;
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

    void SapXepTheoMSV() {
        sort(danhSachSinhVien.begin(), danhSachSinhVien.end(), [](const SinhVien& a, const SinhVien& b) {
            return a.GetMSV() < b.GetMSV();
        });
    }

    void SapXepTheoDiem() {
        sort(danhSachSinhVien.begin(), danhSachSinhVien.end(), [](const SinhVien& a, const SinhVien& b) {
            return a.GetDiem() > b.GetDiem();
        });
    }

    void SapXepTheoTuoi() {
        sort(danhSachSinhVien.begin(), danhSachSinhVien.end(), [](const SinhVien& a, const SinhVien& b) {
            return a.GetTuoi() < b.GetTuoi();
        });
    }

    void XoaSinhVien(int msv) {
        auto it = remove_if(danhSachSinhVien.begin(), danhSachSinhVien.end(),
                            [msv](const SinhVien& sv) { return sv.GetMSV() == msv; });

        if (it != danhSachSinhVien.end()) {
            danhSachSinhVien.erase(it, danhSachSinhVien.end());
            cout << "Da xoa sinh vien co MSV: " << msv << endl;
        } else {
            cout << "Khong tim thay sinh vien co MSV: " << msv << endl;
        }
    }

    void SuaSinhVien(int msv) {
        auto it = find_if(danhSachSinhVien.begin(), danhSachSinhVien.end(),
                          [msv](const SinhVien& sv) { return sv.GetMSV() == msv; });

        if (it != danhSachSinhVien.end()) {
            cout << "Nhap thong tin moi cho sinh vien :" << endl;

            int tuoiMoi;
            float diemMoi;

            cout << "Nhap tuoi sinh vien: ";
            cin >> tuoiMoi;

            cout << "Nhap diem sinh vien: ";
            cin >> diemMoi;

         
        it->SetTuoi(tuoiMoi);
        it->SetDiem(diemMoi);

            cout << "Da cap nhat thong tin cho sinh vien co MSV: " << msv << endl;
        } else {
            cout << "Khong tim thay sinh vien co MSV: " << msv << endl;
        }
    }

    void TimKiemTheoMSV(int msv) const {
        auto it = find_if(danhSachSinhVien.begin(), danhSachSinhVien.end(),
                          [msv](const SinhVien& sv) { return sv.GetMSV() == msv; });

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

        for (const auto& sv : danhSachSinhVien) {
            diemTrungBinh += sv.GetDiem();

            if (sv.GetDiem() > diemCaoNhat) {
                diemCaoNhat = sv.GetDiem();
                sinhVienDiemCaoNhat = sv.GetMSV();
            }

            if (sv.GetDiem() >= 8) {
                soSinhVienGioi++;
            } else if (sv.GetDiem() >= 5) {
                soSinhVienKha++;
            } else {
                soSinhVienTB++;
            }
        }

        diemTrungBinh /= danhSachSinhVien.size();

        cout << "Diem trung binh cua cac sinh vien: " << diemTrungBinh << endl;

        if (sinhVienDiemCaoNhat != -1) {
            auto it = find_if(danhSachSinhVien.begin(), danhSachSinhVien.end(),
                              [sinhVienDiemCaoNhat](const SinhVien& sv) {
                                  return sv.GetMSV() == sinhVienDiemCaoNhat;
                              });

            if (it != danhSachSinhVien.end()) {
                cout << "Sinh vien co diem cao nhat: " << it->GetTen() << " (Diem: " << it->GetDiem() << ")" << endl;
            }
        }

        float tiLeGioi = static_cast<float>(soSinhVienGioi) / danhSachSinhVien.size() * 100;
        float tiLeKha = static_cast<float>(soSinhVienKha) / danhSachSinhVien.size() * 100;
        float tiLeTB = static_cast<float>(soSinhVienTB) / danhSachSinhVien.size() * 100;

        cout << "Ti le sinh vien gioi (>8): " << tiLeGioi << "%" << endl;
        cout << "Ti le sinh vien kha (5-8): " << tiLeKha << "%" << endl;
        cout << "Ti le sinh vien trung binh (<5): " << tiLeTB << "%" << endl;
    }

    void LuuThongTinXuongFile(const string& tenFile) {
        ofstream outFile(tenFile);
        if (!outFile.is_open()) {
            cout << "Khong the mo tao file " << tenFile << endl;
            return;
        }

        for (const auto& sv : danhSachSinhVien) {
            outFile << sv.GetMSV() << " " << sv.GetTen() << " " << sv.GetTuoi() << " " << sv.GetDiem() << endl;
        }

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

