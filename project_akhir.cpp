#include <iostream>
using namespace std;

int menu, i=0, menuPerbarui;
char kembali;
void MENU(), tambahProduk(), tampilkanProduk(), cariProduk();
void menuPerbaruiProduk(), perbaruiProduk(), perbaruiHarga();

struct produk{
    string nama;
    float harga;
    int stok;
}; produk Produk[1000];

int main(){
    do{
    MENU();
    switch(menu){
        case 1: tambahProduk(); break;
        case 2: tampilkanProduk(); break;
        case 3: perbaruiProduk(); break;
        case 4: cariProduk(); break;
        default: system("cls");
            cout << "==================\n";
            cout << "| Menu tidak ada |\n";
            cout << "==================\n";
        }
        cout << "\nApakah anda ingin kembali ke menu? (y/t) "; cin >> kembali;        
        }while (kembali == 'y' || kembali == 'Y');
}

void MENU(){
    system("cls");
    cout << "============================\n";
    cout << "|           MENU           |\n";
    cout << "============================\n";
    cout << "| 1. Tambah Produk         |\n";
    cout << "| 2. Tampilkan Produk      |\n";
    cout << "| 3. Perbarui Data Produk  |\n";
    cout << "| 4. Cari Produk           |\n";
    cout << "| 5. Hapus Data Produk     |\n";
    cout << "| 6. Data Penjualan        |\n";
    cout << "| 7. Laporan Keuangan      |\n";
    cout << "============================\n";    
    cout << "| 0. Keluar                |\n";
    cout << "============================\n";  
    cout << "Pilih menu : "; cin >> menu;      
}

void tambahProduk(){
    system("cls");
    cout << "===================================\n";
    cout << "|          Tambah Produk          |\n";    
    cout << "===================================\n";
    cout << "Nama Produk : ";
    cin >> Produk[i].nama;
    cout << "Harga : ";
    cin >> Produk[i].harga;
    cout << "Stok : ";
    cin >> Produk[i].stok;   
    i = i+1; 
}

void tampilkanProduk(){
    system("cls");
    cout << "====================================\n";
    cout << "|           Daftar Produk          |\n";    
    cout << "====================================\n";
    for(int j=0; j<i; j++){
        cout << "Nama Produk: " << Produk[j].nama << endl;
        cout << "Harga : " << Produk[j].harga << endl;
        cout << "Stok : " << Produk[j].stok << endl;
        cout << "------------------------------------" << endl;
    }
}

void menuPerbaruiProduk(){
    system("cls");
    cout << "====================================\n";
    cout << "| Pilih Data yang Ingin Diperbarui |\n";
    cout << "====================================\n";
    cout << "| 1. Harga                         |\n";
    cout << "| 2. Stok                          |\n";
    cout << "====================================\n";    
    cout << "| 0. Kembali                       |\n";
    cout << "====================================\n";  
    cout << "Pilih menu : "; cin >> menuPerbarui;    
}

void perbaruiHarga(){
    system("cls");
    string namaProduk;
    int j, index;
    bool ada = false;
    cout << "Nama produk : ";
    cin >> namaProduk;
    for(j=0; j<i; j++){
        if(namaProduk == Produk[j].nama){
            ada = true;
            index = j;
        }
    }
    if (ada){
        float hargaBaru;
        cout << "Masukkan harga baru : ";
        cin >> hargaBaru;
        Produk[index].harga = hargaBaru;
        cout << "============================================\n";
        cout << "---------Harga berhasil diperbarui!---------\n";
    }else{
        cout << "============================================\n";
        cout << "----------Produk tidak ditemukan!-----------\n";}   
}

void perbaruiStok(){
    system("cls");
    string namaProduk;
    int j, index;
    bool ada = false;
    cout << "Nama produk : ";
    cin >> namaProduk;
    for(j=0; j<i; j++){
        if(namaProduk == Produk[j].nama){
            ada = true;
            index = j;
        }
    }
    if (ada){
        int stokBaru;
        cout << "Masukkan stok baru : ";
        cin >> stokBaru;
        Produk[index].stok = stokBaru;
        cout << "============================================\n";
        cout << "---------Stok berhasil diperbarui!----------\n";
    }else{
        cout << "============================================\n";
        cout << "----------Produk tidak ditemukan!-----------\n";}   
}

void perbaruiProduk(){
    menuPerbaruiProduk();
    switch(menuPerbarui){
        case 1: perbaruiHarga(); break;
        case 2: perbaruiStok(); break;        
        default: break;
    }
}

void cariProduk(){

}