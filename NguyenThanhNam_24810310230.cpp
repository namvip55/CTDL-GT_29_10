
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Cau 1: Dinh nghia cau truc ngay thang nam
struct Ngay {
    int ngay, thang, nam;
};

// Cau 1: Dinh nghia cau truc hang hoa
struct HangHoa {
    string maHang;
    string tenHang;
    Ngay ngayXuat;
    double giaXuat;
};

// Cau 2: Nhap mot hang hoa
void nhapHangHoa(HangHoa &h) {
    cin.ignore();

    cout << "Nhap ma hang: ";
    getline(cin, h.maHang);

    cout << "Nhap ten hang: ";
    getline(cin, h.tenHang);

    cout << "Nhap ngay xuat (dd/mm/yyyy): ";

char dau1, dau2;

cin >> h.ngayXuat.ngay >> dau1
    >> h.ngayXuat.thang >> dau2
    >> h.ngayXuat.nam;

    cout << "Nhap gia xuat (trieu dong): ";
    cin >> h.giaXuat;
}

// Cau 2: Nhap mang n hang hoa
void nhapMang(HangHoa a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "\nNhap hang hoa thu " << i + 1 << ":\n";
        nhapHangHoa(a[i]);
    }
}

// Cau 3: Xuat mot hang hoa
void xuatHangHoa(HangHoa h) {
    cout << left
         << setw(12) << h.maHang
         << setw(22) << h.tenHang;

    cout << setfill('0')
         << setw(2) << h.ngayXuat.ngay << "/"
         << setw(2) << h.ngayXuat.thang << "/"
         << setw(4) << h.ngayXuat.nam
         << setfill(' ');

    cout << right
         << setw(15) << h.giaXuat << endl;
}

// Cau 3: Xuat mang n hang hoa
void xuatMang(HangHoa a[], int n) {
    cout << "\n========== DANH SACH HANG HOA ==========\n";

    cout << left
         << setw(12) << "Ma hang"
         << setw(22) << "Ten hang"
         << setw(12) << "Ngay xuat"
         << right
         << setw(15) << "Gia (trieu)" << endl;

    for (int i = 0; i < n; i++) {
        xuatHangHoa(a[i]);
    }
}

// Hoan doi hai hang hoa
void hoanDoi(HangHoa &a, HangHoa &b) {
    HangHoa temp = a;
    a = b;
    b = temp;
}

// Cau 4: Quick Sort tang dan theo gia xuat
int partition(HangHoa a[], int left, int right) {
    double pivot = a[right].giaXuat;
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (a[j].giaXuat <= pivot) {
            i++;
            hoanDoi(a[i], a[j]);
        }
    }

    hoanDoi(a[i + 1], a[right]);

    return i + 1;
}

void quickSort(HangHoa a[], int left, int right) {
    if (left < right) {
        int pi = partition(a, left, right);

        quickSort(a, left, pi - 1);
        quickSort(a, pi + 1, right);
    }
}

// Cau 5: Tim kiem nhi phan hang hoa co gia bang X
void timKiemNhiPhan(HangHoa a[], int n, double X) {
    int left = 0;
    int right = n - 1;
    int viTri = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (a[mid].giaXuat == X) {
            viTri = mid;
            break;
        }
        else if (a[mid].giaXuat < X) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    if (viTri == -1) {
        cout << "\nKhong tim thay hang hoa co gia xuat bang "
             << X << endl;
        return;
    }

    // Tim tat ca hang hoa co gia bang X
    int i = viTri;

    while (i >= 0 && a[i].giaXuat == X) {
        i--;
    }

    int j = viTri;

    while (j < n && a[j].giaXuat == X) {
        j++;
    }

    cout << "\nCac hang hoa co gia xuat bang "
         << X << ":\n";

    cout << left
         << setw(12) << "Ma hang"
         << setw(22) << "Ten hang"
         << setw(12) << "Ngay xuat"
         << right
         << setw(15) << "Gia (trieu)" << endl;

    for (int k = i + 1; k < j; k++) {
        xuatHangHoa(a[k]);
    }
}

// Cau 6: Ham main
int main() {
    int n;
    HangHoa a[100];

    cout << "Nhap so luong hang hoa: ";
    cin >> n;

    if (n <= 0 || n > 100) {
        cout << "So luong khong hop le!";
        return 0;
    }

    // Nhap va xuat mang
    nhapMang(a, n);

    cout << "\nDANH SACH HANG HOA VUA NHAP:";
    xuatMang(a, n);

    // Sap xep Quick Sort
    quickSort(a, 0, n - 1);

    cout << "\nDANH SACH SAU KHI SAP XEP TANG DAN:";
    xuatMang(a, n);

    // Tim kiem nhi phan
    double X;
    cout << "\nNhap gia xuat X can tim: ";
    cin >> X;

    timKiemNhiPhan(a, n, X);

    return 0;
}

