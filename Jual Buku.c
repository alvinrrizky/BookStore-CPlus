#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Untuk PROFIL */
struct Mahasiswa {
	char *Nama;
	long int NIM;
};


typedef struct {
	int codebuku;
	char judulbuku[50];
	char pengarang[30];
	int harga;
	int hargatotal;
	int kuota;
} Buku;

typedef struct {
	char nama[30];
	char jk[1];
	char tlp[15];
	char tgl;
	int jmlh;
	int kodebuku;
	int totalharga;
	int bayar;
	int kembalian;
} Pembeli ;
 

void sort (Buku dtbuku);

/* ===========================================================FUNCTION MENGECEK FILE ============================================================== */
int empty (Buku dtbuku){
	
	FILE *f_buku;
	int n;
	n=0;
	
	f_buku=fopen("DAFTAR_BUKU.txt", "rb");
	while (fread(&dtbuku, sizeof(dtbuku), 1, f_buku))
	n = 1;
	fclose(f_buku);
	return n;
}

/* ======================================================== FUNCTION MENGECEK KODE BUKU =========================================================== */
int cekcode (Buku dtbuku, int code){
	
	FILE *f_buku;
	int n;
	n=0;
	
	if (empty(dtbuku) == 1)
	{
		f_buku=fopen("DAFTAR_BUKU.txt", "rb");
		while(!feof(f_buku))
		{
			fread(&dtbuku, sizeof(dtbuku),1,f_buku);
			if( code == dtbuku.codebuku)
			{
				fclose(f_buku);
				return 1;
			}
		}					
		fclose(f_buku);
		return 0;
	}
	else
	{
		return 0;
	}
}

/* ====================================================== FUNCTION HEADER / JUDUL PLOGRAM ========================================================= */
int judul (){
	
	printf ("\t|-----------------------------------------------------------------------------------------------------------------|\n");
	printf ("\t|                                                PROGRAM PENJUALAN BUKU                                           |\n");
	printf ("\t|                                              DASAR  DASAR  PEMROGRAMAN                                          |\n");
	printf ("\t|-----------------------------------------------------------------------------------------------------------------|\n");
}

/* ====================================================== PROCEDURE INPUT BUKU PENJUALAN ========================================================== */
void inputdatabuku (Buku dtbuku){
	
	system ("cls");
	judul();
	printf ("\t|                                                   INPUT DATA BUKU                                               |\n");
	printf ("\t|-----------------------------------------------------------------------------------------------------------------|\n\n");
	
	int cek;
	
	FILE *f_buku;
	
	f_buku=fopen("DAFTAR_BUKU.txt", "ab+");
	
	input:
	do
	{
		printf("\tMasukan Kode Buku	= "); fflush (stdin); scanf("%d", &dtbuku.codebuku);
		
		cek = cekcode(dtbuku, dtbuku.codebuku); 
		
		if (cek == 1)
		{
			printf("\n Kode telah terdaftar, masukkan Kode yang berbeda !\n\n");
		}
		else if (dtbuku.codebuku > 20)
		{
			printf("\n Buku yang diinput melebihi batas !\n\n");
			goto input;
		}
		else if (dtbuku.codebuku < 1)
		{
			printf("\n ERROR!\n\n");
			goto input;
		}
		
	}while(cek == 1);
		
	printf("\tMasukan Judul Buku	= "); fflush (stdin); gets(dtbuku.judulbuku);
	printf("\tMasukan Pengarang	= "); fflush (stdin); gets(dtbuku.pengarang);
	printf("\tMasukan Harga Buku	= Rp. "); fflush (stdin); scanf("%d", &dtbuku.harga);
	printf("\tMasukan Kuota Buku	= "); fflush (stdin); scanf("%d", &dtbuku.kuota);
	printf("\n");
	
	printf("\tINPUT BUKU SUKSES");
			
	fwrite(&dtbuku, sizeof(dtbuku),1,f_buku);
	fclose(f_buku);

	_getch();
	system ("cls");
}

/* ======================================================= PROCEDURE TAMPIL DAFTAR BUKU =========================================================== */
void tampil (Buku dtbuku){
	
	system ("cls");
	judul();
	printf ("\t|                                                  TAMPIL DAFTAR BUKU                                             |\n");
	printf ("\t|-----------------------------------------------------------------------------------------------------------------|\n\n");
	
	FILE *f_buku;
	
	sort(dtbuku);
	f_buku=fopen("DAFTAR_BUKU.txt", "rb");
	printf(" \t  Kode Buku\t\tJudul Buku\t\t\t\tPengarang \t\tHarga\t\t  Kuota \n\n");			
	while(fread(&dtbuku, sizeof(dtbuku),1,f_buku))
	{
		printf("\t      %-15d %-40s %-23s Rp.%-17d %d\n ", dtbuku.codebuku, dtbuku.judulbuku, dtbuku.pengarang,
		dtbuku.harga, dtbuku.kuota);
	}
	fclose(f_buku);
	printf ("\n\n");
	printf ("\t                                             [ ENTER UNTUK KEMBALI KE MENU ]                                     \n\n");
	_getch();
	system ("cls");
}

/* ======================================================= PROCEDURE SORTING DAFTAR BUKU ========================================================== */
void sort(Buku dtbuku){
	
	int a[20];
	int count = 0;
	int i,j,t,c;
	FILE *f_buku;
	FILE *fpt;
	f_buku = fopen("DAFTAR_BUKU.txt","rb");
	fpt = fopen("Temp_BUKU.txt","wb");
	while (fread(&dtbuku, sizeof(dtbuku),1,f_buku)){
		a[count] = dtbuku.codebuku;
		count++;
	}
	
	c = count;
	for (i = 0; i<count -1;i++){
		for (j = i + 1; j<count; j++){
			if (a[i]>a[j]){
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
		}
	}
	count = c;
	for (i = 0; i<count; i++){
		rewind(f_buku);
		while (fread(&dtbuku, sizeof(dtbuku),1,f_buku)){
			if (a[i]==dtbuku.codebuku){
				fwrite(&dtbuku, sizeof(dtbuku),1,fpt);
			}
		}
	}
	fclose(f_buku);
  	fclose(fpt);
  		f_buku = fopen("DAFTAR_BUKU.txt","wb");
  		fpt = fopen("Temp_BUKU.txt","rb");
  		while (fread(&dtbuku,sizeof(dtbuku),1, fpt)){
  			fwrite(&dtbuku,sizeof(dtbuku),1,f_buku);
		  }
			fclose(f_buku);
			fclose(fpt);
}

/* ========================================================== PROCEDURE MENCARI BUKU ============================================================== */
void CariBuku(Buku dtbuku){
	
	FILE *f_buku;
	int codebuku,avl,s;
	char cl, jawab;
	
	cari:
	judul ();
	printf ("\t|                                                      CARI BUKU                                                  |\n");
	printf ("\t|-----------------------------------------------------------------------------------------------------------------|\n\n");
	
	printf(" \n\tMasukan Code Buku yang dicari   :  "); scanf("%d",&codebuku);
	avl = cekcode(dtbuku, codebuku);
	if(avl == 0){
		printf("\n \tCODE BUKU %d tidak ditemukan di dalam FILE\n\n",codebuku);
	}
	else{
		f_buku = fopen("DAFTAR_BUKU.txt","rb");
		while (fread(&dtbuku, sizeof(dtbuku),1, f_buku)){
			s = dtbuku.codebuku;
			if (s == codebuku){
				printf("  \n\tCODE BUKU \t\t   = %d\n",dtbuku.codebuku);
				printf("  \tJUDUL BUKU \t\t   = %s\n",dtbuku.judulbuku);
				printf("  \tPENGARANG\t	   = %s\n",dtbuku.pengarang);
				printf("  \tHARGA \t\t   	   = %d\n",dtbuku.harga);
			}
		}
		fclose(f_buku);
	}
	
	printf("\r\n\tCari data lagi [Y]? ");fflush(stdin);
 	jawab = toupper(getche()); /* Baca jawaban dari keyboard */
 	while (jawab == 'Y'){
 		system("cls");
 		goto cari;
	 }
	_getch();
	system("cls");
}

/* ======================================================= PROCEDURE MENGUBAH DAFTAR BUKU  ======================================================== */
void ubahdatabuku (Buku dtbuku){
	
	ubah :
	system ("cls");
	judul ();
	printf ("\t|                                                  UBAH DATA BUKU                                                 |\n");
	printf ("\t|-----------------------------------------------------------------------------------------------------------------|\n\n");
	
	int ubh;
	FILE *f_buku;
	FILE *fpt;
	int x,k,ppil;
	char jwb;
	
	printf("\tMasukan Kode Buku	= "); fflush (stdin); scanf("%d", &k);
	ubh=cekcode(dtbuku, k);
	
	if (ubh == 0 )
	{
		printf("\n CODE BUKU %d tidak ditemukan di dalam FILE!\n\n", k);
	}
	else
	{
		f_buku = fopen("DAFTAR_BUKU.txt","rb");
		fpt = fopen("Temp_BUKU.txt","wb");
		while (fread(&dtbuku,sizeof(dtbuku),1,f_buku))
		{
			x=dtbuku.codebuku;
			if (x != k)
			{
				fwrite(&dtbuku,sizeof(dtbuku),1,fpt);
			}
			else
			{
				printf("\t1. Ubah Judul Buku  \n");
				printf("\t2. Ubah Pengarang   \n");
				printf("\t3. Ubah Harga Buku  \n");
				printf("\t4. Ubah Kuota Buku  \n");
				printf("\t5. Ubah Keseluruhan \n");
				printf("\n\n");
				printf("\t Pilihan : "); scanf ("%d", &ppil);
				printf("\n\tSilahkan Masukan Data! \n");
				switch (ppil) {
					case 1 : 
						printf("\tMasukan Judul Buku	= "); fflush (stdin); gets(dtbuku.judulbuku);
							break;
					case 2 :
						printf("\tMasukan Pengarang	= "); fflush (stdin); gets(dtbuku.pengarang);
							break;
					case 3 : 
						printf("\tMasukan Harga Buku	= Rp. "); fflush (stdin); scanf("%d", &dtbuku.harga);
					case 4 :
						printf("\tMasukan Kuota Buku	= "); fflush (stdin); scanf("%d", &dtbuku.kuota);
						break;
					case 5 :
						printf("\tMasukan Judul Buku	= "); fflush (stdin); gets(dtbuku.judulbuku);
						printf("\tMasukan Pengarang	= "); fflush (stdin); gets(dtbuku.pengarang);
						printf("\tMasukan Harga Buku	= Rp. "); fflush (stdin); scanf("%d", &dtbuku.harga);
						printf("\tMasukan Kuota Buku	= "); fflush (stdin); scanf("%d", &dtbuku.kuota);
							break;
					default :
						printf("\n\t Anda Salah Memasukan Pilihan!\n\n");
							break;						
				}
				fwrite(&dtbuku,sizeof(dtbuku),1,fpt);
			}
		}
		fclose(f_buku);
  		fclose(fpt);
  		f_buku = fopen("DAFTAR_BUKU.txt","wb");
		fpt = fopen("Temp_BUKU.txt","rb");
  		while (fread(&dtbuku,sizeof(dtbuku),1, fpt)){
  			fwrite(&dtbuku,sizeof(dtbuku),1,f_buku);
		  }
			fclose(f_buku);
			fclose(fpt);
			printf("\n\t Anda Berhasil Memperbaharui!\n");
			printf("\r\n\tUbah data lagi [Y]? ");fflush(stdin);
 			jwb = toupper(getche()); /* Baca jawaban dari keyboard */
 			while (jwb == 'Y'){
 			system("cls");
 			goto ubah; }
	}
	printf ("\n\n");
	printf ("\t                                             [ ENTER UNTUK KEMBALI KE MENU ]                                     \n\n");
	_getch();
	system("cls");
}

/* ========================================================= PROCEDURE HAPUS DATA BUKU ============================================================ */
void hapusdatabuku (Buku dtbuku){ 
	
	hapus:
	system ("cls");
	judul ();
	printf ("\t|                                                   HAPUS DATA BUKU                                               |\n");
	printf ("\t|-----------------------------------------------------------------------------------------------------------------|\n\n");
	
	FILE *f_buku;
	FILE *fpt;
	int x,k,ppil;
	
	printf("\n\t1. Hapus Salah Satu Data Buku\n");
	printf("\t2. Hapus Seluruh Data Buku\n");
	printf("\n\n");				
	printf("\t Pilihan : "); scanf ("%d", &ppil);
	if (ppil == 1){
		
		printf(" Masukan Code Buku : ");
		scanf("%d",&k);
		if (cekcode(dtbuku, k) == 0){
			printf("\n\t CODE BUKU %d tidak ditemukan\n\n",k);
		}
		else{
			f_buku = fopen("DAFTAR_BUKU.txt","rb");
			fpt = fopen("Temp_BUKU.txt","wb");
			while (fread(&dtbuku, sizeof(dtbuku), 1, f_buku)){
				
				x = dtbuku.codebuku;
				if ( x != k){
					//Menyalin data file yang tidak ingin dihapus
					fwrite(&dtbuku, sizeof(dtbuku), 1, fpt);
				}
			}
			fclose(f_buku);
			fclose(fpt);
			f_buku = fopen("DAFTAR_BUKU.txt","wb");
			fpt = fopen("Temp_BUKU.txt","rb");
			while(fread(&dtbuku,sizeof(dtbuku),1,fpt)){
				fwrite(&dtbuku,sizeof(dtbuku),1,f_buku);
			}
			printf("\n\t Data Berhasil Dihapus\n");
			fclose(f_buku);
			fclose(fpt);
		}
	}
	else{
		f_buku = fopen("DAFTAR_BUKU.txt","wb");
		fclose(f_buku);
	}

	printf ("\n\n");
	printf ("\t                                             [ ENTER UNTUK KEMBALI KE MENU ]                                     \n\n");
	_getch();
	system("cls");	
}

/* ============================================================ PROCEDURE PEMBELIAN =============================================================== */
void pembelian (Buku dtbuku, Pembeli dtbeli){
		
	pembelian :	
	system ("cls");
	judul ();
	printf ("\t|                                                      PEMBELIAN                                                  |\n");
	printf ("\t|-----------------------------------------------------------------------------------------------------------------|\n\n");
	
	FILE *f_buku;
	FILE *fpt;
	FILE *f_beli;
	char jawab;
	
	f_beli=fopen("DATA_BELI.txt", "ab+");
	fpt = fopen("Temp_BUKU.txt","wb");
	
	printf("\n\n");
	printf("\t\t SILAHKAN MASUKAN DATA DIRI ANDA \n");
	//formulir data diri orang yang sewa buku
	printf("\t1. NAMA                = "); fflush (stdin); gets(dtbeli.nama);
	printf("\t2. JENIS KELAMIN [L/P] = "); fflush (stdin); scanf("%s", &dtbeli.jk);
	printf("\t3. NO.TLP              = "); fflush (stdin); gets(dtbeli.tlp);
	printf("\n\n");	
	
	printf("\t\t SILAHKAN ISI DATA PEMBELIAN  \n");
	printf("\t Contoh : TANGGAL PEMBELIAN      = 4/1/2020 \n");
	printf("\t TANGGAL PEMBELIAN      = "); fflush (stdin); scanf("%s", &dtbeli.tgl);
	printf("\t KODE BUKU              = "); fflush (stdin); scanf("%d", &dtbeli.kodebuku);
	printf("\t JUMLAH BUKU            = "); fflush (stdin); scanf("%d", &dtbeli.jmlh);
	
	f_buku = fopen("DAFTAR_BUKU.txt","rb");
	while(fread(&dtbuku, sizeof(dtbuku),1,f_buku)) {
		if (dtbuku.codebuku == dtbeli.kodebuku)
		{
			    	if(dtbeli.jmlh>dtbuku.kuota)
					{
						printf("\t\t JUMLAH BUKU YANG DIBELI MELEBIHI KUOTA BUKU\n");
						printf("\t SILAHKAN ULANGI!\n");
						printf("\t JUMLAH BUKU            = "); fflush (stdin); scanf("%d", &dtbeli.jmlh);
					}
					else 
					{
						dtbuku.kuota=dtbuku.kuota-dtbeli.jmlh;
						fwrite(&dtbuku, sizeof(dtbuku),1,fpt);
					}	

		} else if (dtbuku.codebuku != dtbeli.kodebuku)
		{
			fwrite(&dtbuku, sizeof(dtbuku),1,fpt);
		}
	}
	
	fclose(fpt);
	fclose(f_buku);
	
	fpt = fopen("Temp_BUKU.txt","rb");
	f_buku = fopen("DAFTAR_BUKU.txt","wb");
	while(fread(&dtbuku, sizeof(dtbuku),1,fpt))
	{
		fwrite(&dtbuku, sizeof(dtbuku),1,f_buku);
	}
	fclose(fpt);
	fclose(f_buku);
	
	dtbeli.totalharga=dtbeli.jmlh*dtbuku.harga;
	printf("\t TOTAL HARGA            = Rp. %d \n", dtbeli.totalharga); fflush (stdin);
	
	printf("\t\t TRANSAKSI HANYA BISA DILAKUKAN SECARA TUNAI \n");
	printf("\t NOMINAL UANG YANG DIBERIKAN = Rp. "); scanf("%d", &dtbeli.bayar);fflush (stdin);
	if (dtbeli.bayar<dtbeli.totalharga)
	{
		printf("\t\t TIDAK BISA MELAKUKAN TRANSAKSI \n");
		printf("\t SILAHKAN ULANGI!\n");
		printf("\t NOMINAL UANG YANG DIBERIKAN = Rp.  "); scanf("%d", &dtbeli.bayar);fflush (stdin);
		dtbeli.kembalian=dtbeli.bayar-dtbeli.totalharga;	
		printf("\t KEMBALIAN                   = Rp. %d \n", dtbeli.kembalian); fflush (stdin);
	}
	else
	{
		dtbeli.kembalian=dtbeli.bayar-dtbeli.totalharga;	
		printf("\t KEMBALIAN               = Rp. %d \n", dtbeli.kembalian); fflush (stdin);
	} 
	
		 		
	fwrite(&dtbeli, sizeof(dtbeli),1,f_beli);
	fclose(f_beli);
	
	printf("\n\t Pembelian Berhasil!\n");
	printf("\t\r\n Pembelian lagi [Y]? ");fflush(stdin);
 	jawab = toupper(getche()); /* Baca jawaban dari keyboard */
 	while (jawab == 'Y'){
	 	system("cls");
	 	goto pembelian; 
	}
	
	printf ("\n\n");
	printf ("\t                                             [ ENTER UNTUK KEMBALI KE MENU ]                                     \n\n");	
	_getch();
	system ("cls");
			
}

/* ============================================================= PROCEDURE LAPORAN ================================================================ */
void laporbuku(Buku dtbuku){ // belum selesai karena belum bisa dicoba
	
	system ("cls");
	judul ();
	printf ("\t|                                                  LAPORAN PEMBELIAN                                              |\n");
	printf ("\t|-----------------------------------------------------------------------------------------------------------------|\n\n");
	
	FILE *f_buku;
	
	f_buku=fopen("DATA_BELI.txt", "rb");
	while(fread(&dtbuku, sizeof(dtbuku),1,f_buku))
	{
		printf("\t      %d %s %d Rp.%d Rp.%d\n ", dtbuku.codebuku, dtbuku.judulbuku, dtbuku.kuota, dtbuku.harga, dtbuku.hargatotal);
	}
	fclose(f_buku);
	printf ("\n\n");
	printf ("\t                                             [ ENTER UNTUK KEMBALI KE MENU ]                                     \n\n");
	_getch();
	system ("cls");
	
}

/* ============================================================== PROCEDURE EXIT ================================================================== */
void EXIT(){

	judul ();
	printf ("\t|                                                          EXIT                                                   |\n");
	printf ("\t|                                                                                                                 |\n");
	printf ("\t|                                         TERIMA KASIH TELAH MEMBELI PRODUK KAMI                                  |\n");
	printf ("\t|                                          SEMOGA ANDA MENIKMATI PEMBELIAN ANDA                                   |\n");
	printf ("\t|                                                           >_<                                                   |\n");
	printf ("\t|                                         KEDATANGAN ANDA AKAN SELALU KAMI TERIMA                                 |\n");
	printf ("\t|-----------------------------------------------------------------------------------------------------------------|\n\n");

	_getch();
	exit(1);
}

/* ================================================================ MENU UTAMA ==================================================================== */
int main (){
	
	Buku dtbuku;
	Pembeli dtbeli;
	
	int pil;
	char jawab;
	
	struct Mahasiswa mhs1, mhs2;
	mhs1.Nama = "Alvin Andrian Rizki";
	mhs1.NIM = 201511003;
	mhs2.Nama = "Hasya Ayuni Sonia";
	mhs2.NIM = 201511011;
	
                 /*================================================== PROFIL ============================================*/
	
	PROFIL:
	judul ();
	printf ("\t|                                                        PROFIL                                                   |\n");
	printf ("\t|-----------------------------------------------------------------------------------------------------------------|\n");
	printf ("\t|                                                  PROGRAM PENJUALAN BUKU                                         |\n");
	printf ("\t|                                      MATA KULIAH DASAR DASAR PEMROGRAMAN PRAKTEK                                |\n");
	printf ("\t|                                                                                                                 |\n");
	printf ("\t|                                                  %s                                            |\n", mhs1.Nama);
	printf ("\t|                                                       %ld                                                 |\n", mhs1.NIM);
	printf ("\t|                                                                                                                 |\n");
	printf ("\t|                                                  %s                                              |\n", mhs2.Nama);
	printf ("\t|                                                       %ld                                                 |\n", mhs2.NIM);
	printf ("\t|-----------------------------------------------------------------------------------------------------------------|\n\n");
	printf ("\t                                                  [ ENTER UNTUK MASUK ]                                           ");
	_getch();
	system ("cls");
	

	
				/*==================================================== MENU ============================================*/

	menu:
	judul ();
	printf ("\t|                                                          MENU                                                   |\n");
	printf ("\t|                                                                                                                 |\n");
	printf ("\t| 1. INPUT DAFTAR BUKU                                                                                            |\n");
	printf ("\t| 2. TAMPIL DAFTAR BUKU                                                                                           |\n");
	printf ("\t| 3. CARI BUKU                                                                                                    |\n");
	printf ("\t| 4. PEMBELIAN                                                                                                    |\n");
	printf ("\t| 5. LAPORAN PEMBELIAN                                                                                            |\n");
	printf ("\t| 6. UBAH DATA BUKU                                                                                               |\n");
	printf ("\t| 7. HAPUS DATA BUKU                                                                                              |\n");		
	printf ("\t| 8. EXIT                                                                                                         |\n");
	printf ("\t|                                                                                                                 |\n");
	printf ("\t|-----------------------------------------------------------------------------------------------------------------|\n\n");
	
	printf ("\tPILIH [ 1 s/d 8] : "); scanf ("%d", &pil); // menjawab 
	
	switch (pil)
			{
			case 1 : {	
						CASE1:
						printf ("\n\t1. Lanjut input buku\n\t0. Kembali\n\n");
						printf ("\tPilihan : "); scanf ("%d",&jawab);
						if (jawab == 0){
 						system("cls");
 						goto menu;
	 					} else if (jawab == 1){
	 					system("cls");
						inputdatabuku(dtbuku);
						goto menu;
						} else{
						printf ("\n\tPilihan tidak tersedia");
						_getch();
						system("cls");
						goto CASE1;}
						break;}
			case 2 : {	
						system("cls");
						tampil(dtbuku);
						goto menu; // kembali / pergi ke menu
						break; }
			case 3 : {	
						CASE3:
						printf ("\n\t1. Lanjut mencari buku\n\t0. Kembali\n\n");
						printf ("\tPilihan : "); scanf ("%d",&jawab);
						if (jawab == 0){
 						system("cls");
 						goto menu;
	 					} else if (jawab == 1){
	 					system("cls");
						CariBuku(dtbuku);
						goto menu;
						} else{
						printf ("\n\tPilihan tidak tersedia");
						_getch();
						system("cls");
						goto CASE3;}
						break; }
			case 4 : {	
						CASE4:
						printf ("\n\t1. Lanjut membeli buku\n\t0. Kembali\n\n");
						printf ("\tPilihan : "); scanf ("%d",&jawab);
						if (jawab == 0){
 						system("cls");
 						goto menu;
	 					} else if (jawab == 1){
	 					system("cls");
						pembelian(dtbuku, dtbeli);
						goto menu;
						} else{
						printf ("\n\tPilihan tidak tersedia");
						_getch();
						system("cls");
						goto CASE4;}
						break;}
			case 5 : {	
						system("cls");
						laporbuku(dtbuku);
						goto menu; // kembali / pergi ke menu
						break;}
			case 6 : {	
						CASE6:
						printf ("\n\t1. Lanjut ubah daftar buku\n\t0. Kembali\n\n");
						printf ("\tPilihan : "); scanf ("%d",&jawab);
						if (jawab == 0){
 						system("cls");
 						goto menu;
	 					} else if (jawab == 1){
	 					system("cls");
						ubahdatabuku(dtbuku);
						goto menu;
						} else{
						printf ("\n\tPilihan tidak tersedia");
						_getch();
						system("cls");
						goto CASE6;}
						break;}
			case 7 : {	
						CASE7:
						printf ("\n\t1. Lanjut hapus data buku\n\t0. Kembali\n\n");
						printf ("\tPilihan : "); scanf ("%d",&jawab);
						if (jawab == 0){
 						system("cls");
 						goto menu;
	 					} else if (jawab == 1){
	 					system("cls");
						hapusdatabuku(dtbuku);
						goto menu;
						} else{
						printf ("\n\tPilihan tidak tersedia");
						_getch();
						system("cls");
						goto CASE7;}
						break;}
			case 8 : {
						CASE8:
						printf ("\n\t1. Lanjut keluar\n\t0. Kembali\n\n");
						printf ("\tPilihan : "); scanf ("%d",&jawab);
						if (jawab == 0){
 						system("cls");
 						goto menu;
	 					} else if (jawab == 1){
	 					system("cls");
						EXIT();
						} else{
						printf ("\n\tPilihan tidak tersedia");
						_getch();
						system("cls");
						goto CASE8;}
						break;}
			default: {	
						printf ("\n\tPilihan Tidak ada");
						_getch();
						system("cls");
						goto menu; // kembali / pergi ke menu
						break;}
			}
}
