#include <iostream>
using namespace std;

struct produk{
    string nama;
    float harga;
    int stok;
}; produk Produk[1000];

int menu, jumlahProduk=0, menuPerbarui, urutanProduk, AscDesc;
char kembali;
void MENU(), tambahProduk(), tampilkanProduk(produk Produk[], int jumlahProduk), cariProduk(), hapusProduk(), kosong();
void menuPerbaruiProduk(), perbaruiProduk(), perbaruiHarga(), menuTampilkanProduk(), swapProduk(produk &a, produk &b);
void menuAscDesc(), ascNama(produk Produk[], int jumlahProduk), descNama(produk Produk[], int jumlahProduk);
void ascHarga(produk Produk[], int jumlahProduk), descHarga(produk Produk[], int jumlahProduk);
void ascStok(produk Produk[], int jumlahProduk), descStok(produk Produk[], int jumlahProduk);

int main(){
    do{
    MENU();
    switch(menu){
        case 1  : tambahProduk();                               break;
        case 2  : if(jumlahProduk>0){menuTampilkanProduk();} 
                  else{kosong();}                               break;
        case 3  : if(jumlahProduk>0){perbaruiProduk();} 
                  else{kosong();}                               break;
        case 4  : if(jumlahProduk>0){cariProduk();} 
                  else{kosong();}                               break;
        case 5  : if(jumlahProduk>0){hapusProduk();} 
                  else{kosong();}                               break;
        default : system("cls");
            cout << "==================\n";
            cout << "| Menu tidak ada |\n";
            cout << "==================\n";                     break;    
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
    cout << "Pilih menu : "; cin >> menu;      
}

void tambahProduk(){
    system("cls");
    cout << "===================================\n";
    cout << "|          Tambah Produk          |\n";    
    cout << "===================================\n";
    cout << "Nama Produk : ";
    cin >> Produk[jumlahProduk].nama;
    cout << "Harga : ";
    cin >> Produk[jumlahProduk].harga;
    cout << "Stok : ";
    cin >> Produk[jumlahProduk].stok;   
    jumlahProduk = jumlahProduk+1; 
}

void menuTampilkanProduk(){
    system("cls");
    cout << "============================\n";
    cout << "|   Urutkan Berdasarkan:   |\n";
    cout << "============================\n";
    cout << "| 1. Nama                  |\n";
    cout << "| 2. Harga                 |\n";
    cout << "| 3. Stok                  |\n";
    cout << "============================\n";  
    cout << "Pilih menu : "; cin >> urutanProduk;
    menuAscDesc();
}

void menuAscDesc(){
    system("cls");
    cout << "============================\n";
    cout << "|       Urutkan Dari:      |\n";
    cout << "============================\n";
    cout << "| 1. Terkecil ke terbesar  |\n";
    cout << "| 2. Terbesar ke terkecil  |\n";
    cout << "============================\n";  
    cout << "Pilih menu : "; cin >> AscDesc;
    
    if(urutanProduk==1 && AscDesc==1){
        ascNama(Produk, jumlahProduk);
    }else if(urutanProduk==1 && AscDesc==2){
        descNama(Produk, jumlahProduk);
    }else if(urutanProduk==2 && AscDesc==1){
        ascHarga(Produk, jumlahProduk);
    }else if(urutanProduk==2 && AscDesc==2){
        descHarga(Produk, jumlahProduk);
    }else if(urutanProduk==3 && AscDesc==1){
        ascStok(Produk, jumlahProduk);
    }else if(urutanProduk==3 && AscDesc==2){
        descStok(Produk, jumlahProduk);
    }else{
        cout << "==================\n";
        cout << "| Menu tidak ada |\n";
        cout << "==================\n"; 
    }
}

void ascNama(produk Produk[], int jumlahProduk){
    for (int i=0; i<jumlahProduk-1;i++){
        for (int j=0; j<jumlahProduk-1-i; j++){
            if (Produk[j].nama>Produk[j+1].nama){
                swapProduk(Produk[j], Produk[j+1]);
            }
        }
    }
    tampilkanProduk(Produk, jumlahProduk);
}

void descNama(produk Produk[], int jumlahProduk){
    for(int i=0; i<jumlahProduk-1; i++){
        for(int j=0; j<jumlahProduk-1-i; j++){
            if(Produk[j].nama<Produk[j+1].nama){
                swapProduk(Produk[j], Produk[j+1]);
            }
        }
    }
    tampilkanProduk(Produk, jumlahProduk);
}

void ascHarga(produk Produk[], int jumlahProduk){
    for (int i=0; i<jumlahProduk-1;i++){
        for (int j=0; j<jumlahProduk-1-i; j++){
            if (Produk[j].harga>Produk[j+1].harga){
                swapProduk(Produk[j], Produk[j+1]);
            }
        }
    }
    tampilkanProduk(Produk, jumlahProduk);
}

void descHarga(produk Produk[], int jumlahProduk){
    for(int i=0; i<jumlahProduk-1; i++){
        for(int j=0; j<jumlahProduk-1-i; j++){
            if(Produk[j].harga<Produk[j+1].harga){
                swapProduk(Produk[j], Produk[j+1]);
            }
        }
    }
    tampilkanProduk(Produk, jumlahProduk);
}

void ascStok(produk Produk[], int jumlahProduk){
    for (int i=0; i<jumlahProduk-1;i++){
        for (int j=0; j<jumlahProduk-1-i; j++){
            if (Produk[j].stok>Produk[j+1].stok){
                swapProduk(Produk[j], Produk[j+1]);
            }
        }
    }
    tampilkanProduk(Produk, jumlahProduk);
}

void descStok(produk Produk[], int jumlahProduk){
    for(int i=0; i<jumlahProduk-1; i++){
        for(int j=0; j<jumlahProduk-1-i; j++){
            if(Produk[j].stok<Produk[j+1].stok){
                swapProduk(Produk[j], Produk[j+1]);
            }
        }
    }
    tampilkanProduk(Produk, jumlahProduk);
}

void tampilkanProduk(produk Produk[], int jumlahProduk){
    system("cls");
    cout << "====================================\n";
    cout << "|           Daftar Produk          |\n";    
    cout << "====================================\n";
    for(int j=0; j<jumlahProduk; j++){
        cout << "Nama Produk : " << Produk[j].nama << endl;
        cout << "Harga       : " << Produk[j].harga << endl;
        cout << "Stok        : " << Produk[j].stok << endl;
        cout << "------------------------------------" << endl;
    }
}

void swapProduk(produk &a, produk &b){
    produk temp = a;
    a = b;
    b = temp;
}

void cariProduk(){
    system("cls");
    string namaProduk;
    int index = -1;
    bool ada = false;

    cout << "Nama produk : ";
    cin >> namaProduk;

    for(int j=0; j<jumlahProduk; j++){
        if(Produk[j].nama == namaProduk){
            ada = true;
            index = j;
            break;
        }
    }

    if(ada){
        system("cls");
        cout << "Nama Produk : " << Produk[index].nama << endl;
        cout << "Harga       : " << Produk[index].harga << endl;
        cout << "Stok        : " << Produk[index].stok << endl;
    }else{
        cout << "============================================\n";
        cout << "----------Produk tidak ditemukan!-----------\n";}  
}

void menuPerbaruiProduk(){
    system("cls");
    cout << "====================================\n";
    cout << "| Pilih Data yang Ingin Diperbarui |\n";
    cout << "====================================\n";
    cout << "| 1. Harga                         |\n";
    cout << "| 2. Stok                          |\n";
    cout << "====================================\n";   
    cout << "Pilih menu : "; cin >> menuPerbarui;    
}

void perbaruiHarga(){
    system("cls");
    string namaProduk;
    int j, index;
    bool ada = false;
    cout << "Nama produk         : ";
    cin >> namaProduk;
    for(j=0; j<jumlahProduk; j++){
        if(namaProduk == Produk[j].nama){
            ada = true;
            index = j;
        }
    }
    if(ada){
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
    cout << "Nama produk        : ";
    cin >> namaProduk;
    for(j=0; j<jumlahProduk; j++){
        if(namaProduk == Produk[j].nama){
            ada = true;
            index = j;
        }
    }
    if(ada){
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
        case 1  : perbaruiHarga(); break;
        case 2  : perbaruiStok();  break;        
        default : system("cls");
            cout << "==================\n";
            cout << "| Menu tidak ada |\n";
            cout << "==================\n";
        break;  
    }
}

void hapusProduk(){
    system("cls");
    string namaProduk;
    int j, index;
    bool ada = false;
    cout << "Nama produk : ";
    cin >> namaProduk;
    for(j=0; j<jumlahProduk; j++){
        if(namaProduk == Produk[j].nama){
            ada = true;
            index = j;
            break;
        }
    }
    if(ada){
        for (int k=index; k<jumlahProduk-1; k++){
            Produk[k] = Produk[k+1];
        }
        jumlahProduk--; 
        cout << "============================================\n";
        cout << "-------Data produk berhasil dihapus!--------\n";
    }else{
        cout << "============================================\n";
        cout << "----------Produk tidak ditemukan!-----------\n";
    }
}

void kosong(){
    system("cls");
    cout << "===============================\n";
    cout << "| Anda belum menambahkan data |\n";
    cout << "===============================\n";
}