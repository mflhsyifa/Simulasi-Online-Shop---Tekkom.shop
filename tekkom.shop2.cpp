#include <iostream>
#include <iomanip>
using namespace std;

struct Akun {
    string nama;
    string alamat;
    string username;
    string password;
};
int pilihmode=0;
string modebayar,jawab;

// Registrasi — tanda & berfungsi agar Data tersimpan di main()
void registrasi(Akun &user) {
cout << "\n\n                <3 REGISTRASI AKUN <3                 \n";
cout << "______________________________________________________\n";
cout << "Masukkan Nama     : "; getline(cin, user.nama);
cout << "Masukkan Alamat   : "; getline(cin, user.alamat);
cout << "Masukkan Username : "; getline(cin, user.username);
cout << "Masukkan Password : "; getline(cin, user.password);
cout << "______________________________________________________\n";
cout << "Registrasi berhasil, Silahkan Login!                   \n";
cin.get();    // tunggu user tekan Enter
system("cls");
}

// Login
void login(const Akun user) {
    string username, password;
    bool loginstatus = false;

    while (loginstatus==false) {
        cout << "                  <3 LOGIN AKUN <3                    \n";
        cout << "______________________________________________________\n";
        cout << "Masukkan Username : "; cin  >> username;
        cout << "Masukkan Password : "; cin  >> password;
        cin.ignore(); // membersihkan buffer
        cin.get();    // tunggu user tekan Enter

        if (username == user.username && password == user.password) {
            system("cls");
            cout <<"Login berhasil, selamat datang " << user.nama << " !!  \n";
            cout << "______________________________________________________\n";
            loginstatus = true;
        } else {
            system("cls");
            cout << "Username atau password salah! Silakan coba lagi.\n\n";
        }
    }
}


// Fungsi menampilkan daftar keranjang
int daftarkeranjang(string produkkeranjang[], int jumlah[], string produk[], double harga[], int maxProduk) {
    int total = 0;
        cout << left << setw(20) << "Produk"
             << setw(8) << "Jumlah"
             << setw(11) << "Harga/item"
             << "   Subtotal" << endl;
        cout << "------------------------------------------------------\n";

    for (int i = 0; i < maxProduk; i++) {
        if (produkkeranjang[i] == "") continue;
        int indexProduk = -1;
        for (int j = 0; j < maxProduk; j++) {
            if (produkkeranjang[i] == produk[j]) {
                indexProduk = j;
                break;
            }
        }
        double subtotal = jumlah[i] * harga[indexProduk];
        total += subtotal;
        cout << left << setw(20) << produkkeranjang[i]
             << setw(8) << jumlah[i]
             << "Rp. "  << right << setw(7)  << harga[indexProduk]
             << "   Rp. "  << right << setw(8) << subtotal
             << endl;
    }

    cout << "------------------------------------------------------\n";
    cout << left << setw(42) << "TOTAL : "
         << "Rp. " << right << setw(8) << total << endl;
    return total;
}

// Fungsi belanja
void belanja(string produk[], int stok[], double harga[], string produkkeranjang[], int jumlah[], int maxProduk) {
    while (true) {
        cout << "\n                    DAFTAR PRODUK                     \n";
        cout << "______________________________________________________\n";
        cout << left << setw(6) << "No" 
             << setw(20) << "Nama Produk" 
             << setw(16) << "Stok" 
             << setw(15) << "Harga" << endl;
        cout << "------------------------------------------------------\n";

for (int i = 0; i < maxProduk; i++) {
    cout << left << setw(6) << i + 1
         << setw(20) << produk[i]
         << setw(16) << stok[i]
         << "Rp. "  << right << setw(8) << harga[i] << endl;
}
        cout << "------------------------------------------------------\n";
        cout << "\nMasukkan nomor produk (0 untuk selesai): ";
        int pilih;
        cin >> pilih;
        

        if (pilih == 0) {
            // cek keranjang kosong
            bool kosong = true;
            for (int i = 0; i < maxProduk; i++) {
                if (produkkeranjang[i] != "") {
                    kosong = false;
                    break;
                }
            }
            if (kosong) {
                system("cls");
                cout << "Keranjang masih kosong! Silakan pilih barang minimal 1.\n";
                continue;
            } else {
                break;
            }
        }

        if (pilih < 1 || pilih > maxProduk) {
            cout << "Produk tidak tersedia!\n";
            continue;
        }

        cout << "Jumlah yang ingin dibeli: ";
        int jml;
        cin >> jml;
        system("cls");

        if (jml <= 0) {
            cout << "Jumlah harus lebih dari 0!\n";
            continue;
        }

        if (jml > stok[pilih - 1]) {
            cout << "Stok tidak cukup!\n";
            continue;
        }

        stok[pilih - 1] -= jml;

        // Masukkan ke keranjang
        bool sudahAda = false;
        for (int i = 0; i < maxProduk; i++) {
            if (produkkeranjang[i] == produk[pilih - 1]) {
                jumlah[i] += jml;
                sudahAda = true;
                break;
            }
        }
        if (!sudahAda) {
            for (int i = 0; i < maxProduk; i++) {
                if (produkkeranjang[i] == "") {
                    produkkeranjang[i] = produk[pilih - 1];
                    jumlah[i] = jml;
                    break;
                }
            }
        }

        cout << "Produk ditambahkan ke keranjang.\n";
    }
}


int main() {
    Akun user;
    int maxProduk = 5;
    string produk[maxProduk] = {"Kaos", "Celana", "Jaket", "Topi", "Sepatu"};
    int stok[maxProduk] = {10, 8, 5, 15, 6};
    double harga[maxProduk] = {20000, 30000, 50000, 15000, 120000};
    string produkkeranjang[maxProduk] = {""};
    int jumlah[maxProduk] = {0};// <- sekarang variabelnya jelas ada karena ada tambahan & di funtion registrasi

    cout <<"|======================================================|\n";
    cout <<"|~~~        Selamat Datang di Tekkom.shop           ~~~|\n";
    cout <<"|======================================================|\n";
    
    //proses registrasi
    registrasi(user);

    //proses login
    login(user);

    // Proses belanja
    belanja(produk, stok, harga, produkkeranjang, jumlah, maxProduk);

    // Tampilkan keranjang
    system("cls");
    cout << "\n                  KERANJANG BELANJA                     \n";
    cout <<   "______________________________________________________\n";
    
    
    daftarkeranjang(produkkeranjang, jumlah, produk, harga, maxProduk);

    //Tampilkan mode pembayaran
    cout<<"\nPilih mode pembayaran [1.COD atau 2.Transfer] :";
    cin>>pilihmode;
    
    while (pilihmode < 1 || pilihmode > 2) {
        cout << "Pilihan tidak tersedia, silakan pilih kembali.\n";
        cout << "Pilih mode pembayaran [1. COD atau 2. Transfer] : ";
        cin >> pilihmode;
    }

    if (pilihmode == 1) modebayar = "COD"; else modebayar = "Transfer";

    cout << "\nApakah Anda yakin untuk checkout ? (ya/tidak) : ";
    cin >> jawab;
        if (jawab == "ya" || jawab == "Ya" || jawab == "YA") {
        system("cls");
        cout <<"\n|======================================================|\n";
        cout << "==================>| STRUK BELANJA |<==================\n";
        cout <<"|======================================================|\n";
        cout << "Nama Penerima   : " << user.nama << endl;
        cout << "Alamat          : " << user.alamat << endl;
        cout << "Mode Pembayaran : " << modebayar << endl;
        cout << "______________________________________________________\n\n";
        daftarkeranjang(produkkeranjang, jumlah, produk, harga, maxProduk);
        cout << "\n______________________________________________________\n\n";
        cout << "                 Pesanan sedang diproses. \n";
        cout << "       Terima kasih telah berbelanja di Tekkom.shop!\n";
    } else {
        system("cls");
        cout << "______________________________________________________\n\n";
        cout << "       Checkout dibatalkan. Keranjang tidak diproses.\n";
        cout << "            Terima kasih sudah berkunjung.           \n";}
        cout << "______________________________________________________\n";
    return 0;
}

