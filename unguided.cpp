#include <iostream>
#include <vector>
#include <list>
using namespace std;

struct Mahasiswa {
    string nim;
    int nilai;
};

const int hashTableSize = 100;

class HashTable {
private:
    vector<list<Mahasiswa>> table;

    int hashFunction(const string& key) {
        int sum = 0;
        for (char c : key) {
            sum += c;
        }
        return sum % hashTableSize;
    }

public:
    HashTable() {
        table.resize(hashTableSize);
    }

    // Fungsi untuk menambahkan data baru
    void tambahData(const string& nim, int nilai) {
        Mahasiswa mahasiswa;
        mahasiswa.nim = nim;
        mahasiswa.nilai = nilai;
        int index = hashFunction(nim);
        table[index].push_back(mahasiswa);
    }

    // Fungsi untuk menghapus data
    void hapusData(const string& nim) {
        int index = hashFunction(nim);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if ((*it).nim == nim) {
                table[index].erase(it);
                break;
            }
        }
    }

    // Fungsi untuk mencari data berdasarkan NIM
    void cariByNIM(const string& nim) {
        int index = hashFunction(nim);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if ((*it).nim == nim) {
                cout << "Data ditemukan - NIM: " << (*it).nim << ", Nilai: " << (*it).nilai << endl;
                return;
            }
        }
        cout << "Data tidak ditemukan" << endl;
    }

    // Fungsi untuk mencari data berdasarkan rentang nilai 80-90
    void cariByRange() {
        for (int i = 0; i < hashTableSize; ++i) {
            for (auto it = table[i].begin(); it != table[i].end(); ++it) {
                if ((*it).nilai >= 80 && (*it).nilai <= 90) {
                    cout << "NIM: " << (*it).nim << ", Nilai: " << (*it).nilai << endl;
                }
            }
        }
    }
};

int main() {
    HashTable hashTable;
    int choice, nilai;
    string nim;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Data\n";
        cout << "2. Delete Data\n";
        cout << "3. Search data by NIM\n";
        cout << "4. Search data by score 80 - 90\n";
        cout << "Input Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Masukkan NIM: ";
                cin >> nim;
                cout << "Masukkan Nilai: ";
                cin >> nilai;
                hashTable.tambahData(nim, nilai);
                break;
            case 2:
                cout << "Masukkan NIM untuk dihapus: ";
                cin >> nim;
                hashTable.hapusData(nim);
                break;
            case 3:
                cout << "Masukkan NIM yang ingin dicari: ";
                cin >> nim;
                hashTable.cariByNIM(nim);
                break;
            case 4:
                cout << "Mahasiswa dengan nilai antara 80 - 90:\n";
                hashTable.cariByRange();
                break;
            default:
                cout << "Pilihan tidak ada.\n";
        }
    } while (choice != 5);

    return 0;
}
