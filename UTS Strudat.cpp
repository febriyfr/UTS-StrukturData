#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct paper {
    string judul;
    int tahun;
    string penulis;
};

string removeQuotes(const string& text) {
    string result = text;
    if (result.length() >= 2 && result[0] == '"' && result[result.length() - 1] == '"') {
        result = result.substr(1, result.length() - 2);
    }
    return result;
}

vector<paper> loadCSV(const string& filename) {
    vector<paper> data;
    ifstream file(filename.c_str());
    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        vector<string> fields;
        
        while (getline(ss, field, ',')) {
            fields.push_back(removeQuotes(field));
        }

        if (fields.size() >= 8) {
            paper p;
            p.judul = fields[5];
            p.tahun = atoi(fields[6].c_str());
            p.penulis = fields[7];
            data.push_back(p);
        }
    }
    return data;
}

void tampilkanpaper(const paper& p) {
    cout << "---------------------------------" << endl;
    cout << "Judul   : " << p.judul << endl;
    cout << "Tahun   : " << p.tahun << endl;
    cout << "Penulis : " << p.penulis << endl;
    cout << "---------------------------------" << endl;
}

bool compareByJudul(const paper& a, const paper& b) {
    return a.judul < b.judul;
}

int binarySearchByJudul(const vector<paper>& data, const string& judul) {
    int left = 0, right = data.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (data[mid].judul == judul) return mid;
        if (data[mid].judul < judul) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void cariByJudul(const vector<paper>& data, const string& judul, bool isBinary) {
    bool found = false;
    if (isBinary) {
        vector<paper> sortedData = data;
        sort(sortedData.begin(), sortedData.end(), compareByJudul); 
        int index = binarySearchByJudul(sortedData, judul);
        if (index != -1) {
            tampilkanpaper(sortedData[index]);
            found = true;
        }
    } else {
        for (int i = 0; i < data.size(); i++) {
            if (data[i].judul == judul) {
                tampilkanpaper(data[i]);
                found = true;
                break;
            }
        }
    }

    if (!found) {
        cout << "Judul tidak ditemukan." << endl;
    }
}

void cariByTahun(const vector<paper>& data, int tahun) {
    bool found = false;
    for (int i = 0; i < data.size(); i++) {
        if (data[i].tahun == tahun) {
            tampilkanpaper(data[i]);
            found = true;
        }
    }
    if (!found) {
        cout << "Tidak ada paper pada tahun ini." << endl;
    }
}


void cariByPenulis(const vector<paper>& data, const string& penulis) {
    bool found = false;
    for (int i = 0; i < data.size(); i++) {
        if (data[i].penulis.find(penulis) != string::npos) {
            tampilkanpaper(data[i]);
            found = true;
        }
    }
    if (!found) {
        cout << "Penulis tidak ditemukan." << endl;
    }
}


int main() {
    string filename = "Dataset.csv";
    vector<paper> data = loadCSV(filename);

    if (data.empty()) {
        cout << "Gagal membaca data atau data kosong." << endl;
        return 1;
    }

    int pilihan;
    do {
        cout << "\n======= MENU UTAMA =======" << endl;
        cout << "1. Gunakan Binary Search" << endl;
        cout << "2. Gunakan Linear Search" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1 || pilihan == 2) {
            bool isBinary = (pilihan == 1);
            int menu;
            do {
                cout << "\n=== PILIH KRITERIA PENCARIAN ===" << endl;
                cout << "1. Cari Berdasarkan Judul" << endl;
                cout << "2. Cari Berdasarkan Tahun" << endl;
                cout << "3. Cari Berdasarkan Penulis" << endl;
                cout << "4. Kembali ke Menu Utama" << endl;
                cout << "Pilih: ";
                cin >> menu;
                cin.ignore();

                if (menu == 1) {
                    string judul;
                    cout << "Masukkan judul lengkap paper: ";
                    getline(cin, judul);
                    cariByJudul(data, judul, isBinary);
                } else if (menu == 2) {
                    int tahun;
                    cout << "Masukkan tahun: ";
                    cin >> tahun;
                    cin.ignore();
                    cariByTahun(data, tahun);
                } else if (menu == 3) {
                    string penulis;
                    cout << "Masukkan nama penulis: ";
                    getline(cin, penulis);
                    cariByPenulis(data, penulis);
                } else if (menu == 4) {
                    cout << "Kembali ke menu utama..." << endl;
                } else {
                    cout << "Pilihan tidak valid." << endl;
                }               
            } while (menu != 4);
        } else if (pilihan == 3) {
            cout << "Keluar dari program. Sampai jumpa!" << endl;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 3);
    return 0;
}
