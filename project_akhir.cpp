#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

struct produk{
    string nama;
    float harga;
    int stok;
};

struct penjualan{
    string namaProduk;
    int jumlahTerjual;
    float totalHarga;
};

vector<produk> Produk;
vector<penjualan> Penjualan;
int menu, menuPerbarui, urutanProduk, AscDesc = 0;
char kembali;

void bacaFilePenjualan(), bacaFileProduk();
void simpanFilePenjualan(), simpanFileProduk();
void kosong(), MENU(), menuAscDesc(); bool konfirmasiKembali();
void menuPerbaruiProduk(produk* prodToUpdate); // Meneruskan pointer ke produk
void menuTampilkanProduk(), tampilkanProduk(const vector<produk>* ProdukList), tampilkanHasilCariProduk();
produk* cariProdukPointer(); // Mengembalikan pointer ke produk yang ditemukan
void tambahProduk(), hapusProduk(), dataPenjualan(), laporanKeuangan(), reset(), perbaruiProduk(), keluar();
void swapProduk(produk *a, produk *b); // Meneruskan pointer untuk menukar produk pada proses pengurutan
void ascHarga(vector<produk>* ProdukList), ascNama(vector<produk>* ProdukList), ascStok(vector<produk>* ProdukList);
void descHarga(vector<produk>* ProdukList), descNama(vector<produk>* ProdukList), descStok(vector<produk>* ProdukList);
void perbaruiHarga(produk* p), perbaruiNama(produk* p), perbaruiStok(produk* p);

int main(){
    bacaFileProduk();
    bacaFilePenjualan();
    do{
        MENU();
        switch(menu){
            case 1: tambahProduk();                                                          break;
            case 2: if(!Produk.empty()){ menuTampilkanProduk();}else{ kosong();}             break;
            case 3: if(!Produk.empty()){ perbaruiProduk();}else{ kosong();}                  break;
            case 4: if(!Produk.empty()){ tampilkanHasilCariProduk();}else{ kosong();}        break;
            case 5: if(!Produk.empty()){ hapusProduk();}else{ kosong();}                     break;
            case 6: if(!Produk.empty()){ dataPenjualan();}else{ kosong();}                   break;
            case 7: if(!Penjualan.empty()){ laporanKeuangan();}else{ kosong();}              break; 
            case 8: if(!Produk.empty() || !Penjualan.empty()){ reset();}else{ kosong();}     break;
            case 0: keluar();                                                             return 0;
            default:
                system("cls");
                cout << "==================\n";
                cout << "| Menu tidak ada |\n";
                cout << "==================\n";
                break;
       }
   }while(konfirmasiKembali());
    return 0;
}

// ==========================================================================================================================

void MENU(){
    system("cls");
    cout << "============================\n";
    cout << "|          MENU            |\n";
    cout << "============================\n";
    cout << "| 1. Tambah Produk         |\n";
    cout << "| 2. Tampilkan Produk      |\n";
    cout << "| 3. Perbarui Data Produk  |\n";
    cout << "| 4. Cari Produk           |\n";
    cout << "| 5. Hapus Data Produk     |\n";
    cout << "| 6. Data Penjualan        |\n";
    cout << "| 7. Laporan Keuangan      |\n";
    cout << "| 8. Reset Semua Data      |\n";
    cout << "============================\n";
    cout << "| 0. Keluar                |\n";
    cout << "============================\n";
    cout << "Pilih menu : ";
    cin >> menu;
    cin.ignore(); 
}

// Tambah Data ==============================================================================================================

void tambahProduk(){
    system("cls");
    int jumlahInput = 0;
    cout << "Jumlah produk yang ingin diinput : ";
    cin >> jumlahInput;
    cin.ignore(); 

    system("cls");
    cout << "===================================\n";
    cout << "|          Tambah Produk          |\n";
    cout << "===================================\n";
    for(int i = 0; i < jumlahInput; i++){
        produk p;
        cout << "Nama produk   : "; getline(cin, p.nama);
        cout << "Harga         : Rp "; cin >> p.harga;
        cout << "Stok          : "; cin >> p.stok; cin.ignore(); 
        Produk.push_back(p);
        cout << "===================================\n";
   }
    simpanFileProduk();
}


// Tampilkan Produk ==============================================================================================================

void menuTampilkanProduk(){
    system("cls");
    cout << "============================\n";
    cout << "|   Urutkan Berdasarkan:   |\n";
    cout << "============================\n";
    cout << "| 1. Nama                  |\n";
    cout << "| 2. Harga                 |\n";
    cout << "| 3. Stok                  |\n";
    cout << "============================\n";
    cout << "Pilih menu : ";
    cin >> urutanProduk;
    cin.ignore(); 
    menuAscDesc();
}

void menuAscDesc(){
    system("cls");
    cout << "=============================\n";
    cout << "|        Urutkan Dari:      |\n";
    cout << "=============================\n";
    cout << "| 1. Terkecil ke terbesar   |\n";
    cout << "| 2. Terbesar ke terkecil   |\n";
    cout << "=============================\n";
    cout << "Pilih menu : ";
    cin >> AscDesc;
    cin.ignore();

    //nama
    if       (urutanProduk == 1 && AscDesc == 1){ascNama(&Produk);}
    else if (urutanProduk == 1 && AscDesc == 2){descNama(&Produk);}
    //harga
    else if (urutanProduk == 2 && AscDesc == 1){ascHarga(&Produk);}
    else if(urutanProduk == 2 && AscDesc == 2){descHarga(&Produk);}
    //stok
    else if  (urutanProduk == 3 && AscDesc == 1){ascStok(&Produk);}
    else if (urutanProduk == 3 && AscDesc == 2){descStok(&Produk);}
    else{
        cout << "==================\n";
        cout << "| Menu tidak ada |\n";
        cout << "==================\n";
   }
}

// Menerapkan bubble sort pada semua pengurutan
void ascNama(vector<produk>* ProdukList){
    for(size_t i = 0; i < ProdukList->size() - 1; ++i){
        for(size_t j = 0; j < ProdukList->size() - i - 1; ++j){
            if((*ProdukList)[j].nama >(*ProdukList)[j + 1].nama){
                swapProduk(&(*ProdukList)[j], &(*ProdukList)[j + 1]);
           }
       }
   }
    tampilkanProduk(ProdukList);
}

void descNama(vector<produk>* ProdukList){
    for(size_t i = 0; i < ProdukList->size() - 1; ++i){
        for(size_t j = 0; j < ProdukList->size() - i - 1; ++j){
            if((*ProdukList)[j].nama <(*ProdukList)[j + 1].nama){
                swapProduk(&(*ProdukList)[j], &(*ProdukList)[j + 1]);
           }
       }
   }
    tampilkanProduk(ProdukList);
}

void ascHarga(vector<produk>* ProdukList){
    for(size_t i = 0; i < ProdukList->size() - 1; ++i){
        for(size_t j = 0; j < ProdukList->size() - i - 1; ++j){
            if((*ProdukList)[j].harga >(*ProdukList)[j + 1].harga){
                swapProduk(&(*ProdukList)[j], &(*ProdukList)[j + 1]);
           }
       }
   }
    tampilkanProduk(ProdukList);
}

void descHarga(vector<produk>* ProdukList){
    for(size_t i = 0; i < ProdukList->size() - 1; ++i){
        for(size_t j = 0; j < ProdukList->size() - i - 1; ++j){
            if((*ProdukList)[j].harga <(*ProdukList)[j + 1].harga){
                swapProduk(&(*ProdukList)[j], &(*ProdukList)[j + 1]);
           }
       }
   }
    tampilkanProduk(ProdukList);
}

void ascStok(vector<produk>* ProdukList){
    for(size_t i = 0; i < ProdukList->size() - 1; ++i){
        for(size_t j = 0; j < ProdukList->size() - i - 1; ++j){
            if((*ProdukList)[j].stok >(*ProdukList)[j + 1].stok){
                swapProduk(&(*ProdukList)[j], &(*ProdukList)[j + 1]);
           }
       }
   }
    tampilkanProduk(ProdukList);
}

void descStok(vector<produk>* ProdukList){
    for(size_t i = 0; i < ProdukList->size() - 1; ++i){
        for(size_t j = 0; j < ProdukList->size() - i - 1; ++j){
            if((*ProdukList)[j].stok <(*ProdukList)[j + 1].stok){
                swapProduk(&(*ProdukList)[j], &(*ProdukList)[j + 1]);
           }
       }
   }
    tampilkanProduk(ProdukList);
}

void tampilkanProduk(const vector<produk>* ProdukList){
    system("cls");
    cout << "====================================\n";
    cout << "|          Daftar Produk           |\n";
    cout << "====================================\n";
    if(!ProdukList->empty()){
        for(const auto& p : *ProdukList){
            cout << "Nama Produk : " << p.nama << endl;
            cout << "Harga       : Rp " << p.harga << endl;
            cout << "Stok        : " << p.stok << endl;
            cout << "------------------------------------\n";
       }
   }else{
        cout << "|        Tidak ada produk          |\n";
        cout << "------------------------------------\n";
   }
}

void swapProduk(produk *a, produk *b){
    produk temp = *a;
    *a = *b;
    *b = temp;
}

// Cari Produk ==============================================================================================================
// Menggunakan metode sequential

produk* cariProdukPointer(){
    system("cls");
    string namaProduk;
    cout << "====================================\n";
    cout << "|           Cari Produk            |\n";
    cout << "====================================\n";
    cout << "Nama produk : ";
    getline(cin, namaProduk);

    for(size_t j = 0; j < Produk.size(); ++j){
        if(Produk[j].nama == namaProduk){
            return &Produk[j];
       }
   }
    return nullptr;
}

void tampilkanHasilCariProduk(){
    produk* foundProduct = cariProdukPointer();
    if(foundProduct != nullptr){
        system("cls");
        cout << "====================================\n";
        cout << "|         Hasil Pencarian          |\n";
        cout << "====================================\n";
        cout << "Nama Produk : " << foundProduct->nama << endl;
        cout << "Harga       : Rp " << foundProduct->harga << endl;
        cout << "Stok        : " << foundProduct->stok << endl;
        cout << "====================================\n";
   }else{
        cout << "====================================\n";
        cout << "------Produk tidak ditemukan!-------\n";
   }
}

// Perbarui ==============================================================================================================

void perbaruiNama(produk* p){
    if(p != nullptr){
        system("cls");
        cout << "============================================\n";
        cout << "|             Perbarui Nama                |\n";
        cout << "============================================\n";
        cout << "Nama produk saat ini : " << p->nama << endl;
        cout << "Masukkan nama baru   : ";
        getline(cin, p->nama);
        cout << "============================================\n";
        cout << "---------Nama berhasil diperbarui!---------\n";
   }else{
        cout << "============================================\n";
        cout << "----------Produk tidak ditemukan!-----------\n";
   }
}

void perbaruiHarga(produk* p){
    if(p != nullptr){
        system("cls");
        float hargaBaru;
        cout << "============================================\n";
        cout << "|             Perbarui Harga               |\n";
        cout << "============================================\n";
        cout << "Harga produk saat ini : Rp " << p->harga << endl;
        cout << "Masukkan harga baru   : Rp ";
        cin >> hargaBaru;
        cin.ignore();
        p->harga = hargaBaru;
        cout << "============================================\n";
        cout << "---------Harga berhasil diperbarui!---------\n";
   }else{
        cout << "============================================\n";
        cout << "----------Produk tidak ditemukan!-----------\n";
   }
}

void perbaruiStok(produk* p){
    if(p != nullptr){
        system("cls");
        cout << "============================================\n";
        cout << "|             Perbarui Stok                |\n";
        cout << "============================================\n";
        cout << "Stok produk saat ini : " << p->stok << endl;
        int stokBaru;
        cout << "Masukkan stok baru   : ";
        cin >> stokBaru;
        cin.ignore();
        p->stok = stokBaru;
        cout << "============================================\n";
        cout << "---------Stok berhasil diperbarui!----------\n";
   }else{
        cout << "============================================\n";
        cout << "----------Produk tidak ditemukan!-----------\n";
   }
}

void perbaruiProduk(){
    produk* prodToUpdate = cariProdukPointer(); // Cari produk yang ingin diperbarui/diedit
    if(prodToUpdate != nullptr){
        menuPerbaruiProduk(prodToUpdate);
   }else{
        cout << "====================================\n";
        cout << "-------Produk tidak ditemukan!------\n";
   }
}

void menuPerbaruiProduk(produk* prodToUpdate){
    system("cls");
    cout << "====================================\n";
    cout << "| Pilih Data yang Ingin Diperbarui |\n";
    cout << "====================================\n";
    cout << "| 1. Nama                          |\n";
    cout << "| 2. Harga                         |\n";
    cout << "| 3. Stok                          |\n";
    cout << "====================================\n";
    cout << "Pilih menu : ";
    cin >> menuPerbarui;
    cin.ignore(); 

    switch(menuPerbarui){
        case 1: perbaruiNama(prodToUpdate);   simpanFileProduk(); break;
        case 2: perbaruiHarga(prodToUpdate);  simpanFileProduk(); break;
        case 3: perbaruiStok(prodToUpdate);   simpanFileProduk(); break;
        default:
            system("cls");
            cout << "==================\n";
            cout << "| Menu tidak ada |\n";
            cout << "==================\n";
            break;
   }
}

// Hapus ==============================================================================================================

void hapusProduk(){
    system("cls");
    string namaProduk;
    bool found = false;
    size_t index = 0;

    cout << "Nama produk yang ingin dihapus : ";
    getline(cin, namaProduk);

    for(size_t j = 0; j < Produk.size(); ++j){
        if(Produk[j].nama == namaProduk){
            found = true;
            index = j;
            break;
       }
   }
    if(found){
        Produk.erase(Produk.begin() + index);
        cout << "============================================\n";
        cout << "-------Data produk berhasil dihapus!--------\n";
        simpanFileProduk();
   }else{
        cout << "============================================\n";
        cout << "----------Produk tidak ditemukan!-----------\n";
   }
}

// Reset ==============================================================================================================

void reset(){
    system("cls");
    char yakin;
    cout << "============================================\n";
    cout << "|            Reset Semua Data              |\n";
    cout << "============================================\n";
    cout << "Apakah Anda yakin ingin menghapus semua data\n(produk dan penjualan)? (y/t) : ";
    cin >> yakin;
    cin.ignore(); 

    if(yakin == 'y' || yakin == 'Y'){
        Produk.clear();
        Penjualan.clear();
        simpanFileProduk();
        simpanFilePenjualan();
        cout << "============================================\n";
        cout << "----------Semua data berhasil direset-------\n";
   }else{
        cout << "============================================\n";
        cout << "-----------------Dibatalkan-----------------\n";
   }
}

// Data Penjualan ==============================================================================================================

void dataPenjualan(){
    system("cls");
    string nama;
    int jumlah;
    bool ada = false;

    cout << "====================================\n";
    cout << "|          Data Penjualan          |\n";
    cout << "====================================\n";
    cout << "Nama produk    : ";
    getline(cin, nama);

    produk* prodToSell = nullptr;
    for(size_t i = 0; i < Produk.size(); ++i){
        if(Produk[i].nama == nama){
            prodToSell = &Produk[i];
            ada = true;
            break;
       }
   }

    if(ada){
        cout << "Jumlah terjual : ";
        cin >> jumlah;
        cin.ignore(); 

        if(jumlah > prodToSell->stok){
            system("cls");
            cout << "Stok tidak mencukupi!\n";
       }else{
            prodToSell->stok -= jumlah;

            penjualan pj;
            pj.namaProduk = prodToSell->nama;
            pj.jumlahTerjual = jumlah;
            pj.totalHarga = prodToSell->harga * jumlah;
            Penjualan.push_back(pj);

            cout << "====================================\n";
            cout << "-----Penjualan berhasil dicatat!----\n";
       }
   }else{
        cout << "====================================\n";
        cout << "-------Produk tidak ditemukan!------\n";
   }

    simpanFileProduk();   
    simpanFilePenjualan();
}

// Laporan Keuangan ==============================================================================================================

void laporanKeuangan(){
    system("cls");
    float totalPendapatan = 0;

    cout << "====================================\n";
    cout << "|          Laporan Keuangan        |\n";
    cout << "====================================\n";
    if(Penjualan.empty()){
        cout << "|      Tidak ada data penjualan    |\n";
        cout << "------------------------------------\n";
   }else{
        for(const auto& pj : Penjualan){
            cout << "Nama Produk    : " << pj.namaProduk << endl;
            cout << "Jumlah Terjual : " << pj.jumlahTerjual << endl;
            cout << "Total Harga    : Rp " << pj.totalHarga << endl;
            cout << "------------------------------------\n";
            totalPendapatan += pj.totalHarga;
       }
        cout << "Total Pendapatan : Rp " << totalPendapatan << endl;
        cout << "====================================\n";
   }
}

// File ==============================================================================================================

void simpanFileProduk(){
    ofstream file("dataProduk.txt");
    if(file.is_open()){
        for(const auto& p : Produk){
            file << p.nama << ", " << p.harga << ", " << p.stok << endl;
       }
        file.close();
   }else{
        cerr << "Error: Tidak dapat membuka file dataProduk.txt untuk menulis.\n";
   }
}

void bacaFileProduk(){
    ifstream file("dataProduk.txt");
    Produk.clear();
    string line;
    if(file.is_open()){
        while(getline(file, line)){
            produk p;
            size_t pos1 = line.find(", ");
            size_t pos2 = line.find(", ", pos1 + 2);
            if(pos1 != string::npos && pos2 != string::npos){
                try{ // Error handling untuk mengubah string ke angka
                    p.nama = line.substr(0, pos1);
                    p.harga = stof(line.substr(pos1 + 2, pos2 - pos1 - 2));
                    p.stok = stoi(line.substr(pos2 + 2));
                    Produk.push_back(p);
               }catch(const std::invalid_argument& e){
                    cerr << "Error membaca data produk(format tidak valid): " << line << " - " << e.what() << endl;
               }catch(const std::out_of_range& e){
                    cerr << "Error membaca data produk(nilai di luar jangkauan): " << line << " - " << e.what() << endl;
               }
           }
       }
        file.close();
   }else{
        kosong();
   }
}

void simpanFilePenjualan(){
    ofstream file("dataPenjualan.txt");
    if(file.is_open()){
        for(const auto& pj : Penjualan){
            file << pj.namaProduk << ", " << pj.jumlahTerjual << ", " << pj.totalHarga << endl;
       }
        file.close();
   }else{
        cerr << "Error: Tidak dapat membuka file dataPenjualan.txt untuk menulis.\n";
   }
}

void bacaFilePenjualan(){
    ifstream file("dataPenjualan.txt");
    Penjualan.clear();
    string line;
    if(file.is_open()){
        while(getline(file, line)){
            penjualan pj;
            size_t pos1 = line.find(", ");
            size_t pos2 = line.find(", ", pos1 + 2);
            if(pos1 != string::npos && pos2 != string::npos){
                try{
                    pj.namaProduk = line.substr(0, pos1);
                    pj.jumlahTerjual = stoi(line.substr(pos1 + 2, pos2 - pos1 - 2));
                    pj.totalHarga = stof(line.substr(pos2 + 2));
                    Penjualan.push_back(pj);
               }catch(const std::invalid_argument& e){
                    cerr << "Error membaca data penjualan(format tidak valid): " << line << " - " << e.what() << endl;
               }catch(const std::out_of_range& e){
                    cerr << "Error membaca data penjualan(nilai di luar jangkauan): " << line << " - " << e.what() << endl;
               }
           }
       }
        file.close();
   }else{
        kosong();
   }
}

//==============================================================================================================

void kosong(){
    system("cls");
    cout << "===============================\n";
    cout << "| Anda belum menambahkan data |\n";
    cout << "===============================\n";
}

void keluar(){
    simpanFileProduk(); 
    simpanFilePenjualan(); 
    system("cls");
    cout << "============================\n";
    cout << "|   Keluar dari program    |\n";
    cout << "============================\n\n";
}

bool konfirmasiKembali(){
    cout << "\nApakah Anda ingin kembali ke menu? (y/t) : ";
    char input;
    cin >> input;
    cin.ignore();

    if(input == 'y' || input == 'Y'){
        return true;
    }else if(input == 't' || input == 'T'){
        return false;
    }else{
        cout << "Input tidak valid. Silakan masukkan 'y' atau 't'.\n";
        return konfirmasiKembali(); // <--- Penerapan rekursif
    }
}
