#include <stdio.h>
#include <stdlib.h>

void printMatris(int **Matris,int N,char Renkler[8][10]){ // Matrisi Yazdýrýyorum
	int i=0,j=0,k;//i ve j dongu,k degiskeni ise arama yapmak icin tanimlaniyor.
	for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				for(k=0;k<8;k++){//Rengi ariyor.
						if(k==Matris[i][j]){//Renk bulunduysa
							printf("%s	<%d>	",Renkler[k],k);//Yazdiriyor.
						}
				}	
			}
		printf("\n");
	}
}

int checking(int **Matris,int satir,int N){//Satir parametresi elemanlarin sutundaki elemanlarla olan kontrolu.
	int i,j;
	while(satir!=0){ // Kontrol edilen satirdan baslayarak ilk satira kadar tüm matrisi kontrol ediyoruz. 
		for(i=0;i<satir;i++){  // Gelen satir parametresindeki satirin tüm elemanlarini diðer satýrdaki elemanlarla karþýlaþtýrýyoruz.
			for(j=0;j<N;j++){
				if(Matris[satir][j]==Matris[i][j]){ // Eger farkli satirlarin ayni sutununda ayni renk varsa uygun olmadigi icin -1 donduruyoruz. 
					return -1;	
				}
			}
		}
		satir--; //Bir ustteki(onceki) satiri kontrol etmeye gec.
	}
	return 0;
}

int backTracking(int **Matris,int satir,int N,int sayac,char Renkler[8][10]){//Backtracking islemlerini yapan fonksiyon.
	int i,j;//i ve j dongu degiskenlerimizdir.
	if(satir<N){ 
		if(checking(Matris,satir,N)==0){ // Satirdaki elemanlar matrise uyumlulugu acisindan kontrol edilir.
			//Her basarili islem sonucu mevcut adimi ekrana yazdirma islemi alttaki iki satirda yapilir.
			printf("	___%d.Adim___ \n",satir+1); //Adim bilgisi mevcut satir vasitasiyla yazdirilir.+1 denmesinin sebebi kullanici 0-7 araliginda degil,1-8 araliginda degerleri gormesi icindir. 
			printMatris(Matris,N,Renkler);//Ve matris yazdirilir.
			backTracking(Matris,satir+1,N,0,Renkler);// 36.Satirdaki kontrol edilen durum saglanmistir ve bir alt satira gecilir.
			
		}
		else{//Sag kaydirma islemi yapilmasi gerekiyor.
			//Saga kaydirma islemi
			int k=N-1,temp;
			temp=Matris[satir][k]; // En sagdaki elemani gecici degiskenimizde tutuyoruz.
			while(k>0){ // Sagdaki elemanýn bir solundan baþlanarak elemanlarý kaydiriyoruz.
				Matris[satir][k]=Matris[satir][k-1];
				k--;
			}
			Matris[satir][0]=temp; // Son islem olarak en soldaki elemanýn yerine sakladýðýmýz elemaný koyuyoruz.
			//Sag kaydirma islemi sonu.
			
			sayac++; // Sonsuz otelemeyi engellemek icin sayac koyuyoruz.
			if(sayac==N) // Sayac N'e ulaþýrsa o satir icin tum olasiliklar denenmis demektir.
				return -1; //-1 dondur.
			else
				backTracking(Matris,satir,N,sayac,Renkler); // Eger sayac N'e ulasmadiysa ayný satýrý tekrardan backtracking islemine gonderilir.
		}
	}
	else{
		printf("___Islemleri basariyla tamamlanmis matrisin son hali___\n"); // Tum kontroller bittikten sonra renk matrisimizi ekrana yazdiriyoruz.
		printMatris(Matris,N,Renkler);
	}
	return 0;
}


int main(int argc, char *argv[]) {
	int N;//kaca kac matris olucagini tutacak olan degiskenimiz.
	printf("N sayisini verin:");
	scanf("%d",&N);
	
	if(3<=N && N<=8){//3 ile 8 arasinda olmali.
		int i,j,k;//i ve j dongu,k degiskeni ise arama ve yazma yapmak icin tanimlaniyor.
		int **Matris=(int**)calloc(N,sizeof(int*));//Dinamik sekilde int matrisimiz tanimlanip yeri N kadar acilarak satirlari olusturuluyor.
		for(i=0;i<N;i++){//Matrisimizin sutunlarinida olusturuyoruz.
        	Matris[i] = (int*)calloc(N,sizeof(int));
    	}
    	
		char Renkler[8][10]={"Mavi","Mor","Sari","Yesil","Beyaz","Kirmizi","Pembe","Turkuaz"};//8 eleman,10 karakterli char matrisimizi(string dizisi) olusturuyoruz.
		//Mavi=0 Mor=1 Sari=2 Yesil=3 Beyaz=4 Kirmizi=5 Pembe=6 Turkuaz=7
		printf("Mavi Mor Sari Yesil Beyaz Kirmizi Pembe Turkuaz\n(*)Yalnizca bu renkleri birebir ayni formatta girin\n(*)Lutfen her satir icin farkli renkler girin.\n");
		
		char Renk[30];//Girilecek renkleri tutacak olan degisken.
		
		//Matrisi Olusturma.
		for(i=0;i<N;i++){//Satir
			printf("%d.Satirin degerlerini girin:\n",i+1);
			for(j=0;j<N;j++){//Sutun
				printf("%d.Renk:",j+1);//Kullanicidan Renk aliniyor.
				
				scanf("%s",&Renk);
				for(k=0;k<8;k++){//Girilen rengi ariyor.8e kadar gitmesinin sebebi toplamda 8 renk olmasi.
						if(strcmp(Renkler[k],Renk)==0){//Girilen renk bulunduysa
							Matris[i][j]=k;//Matrisimizin o gozune rengin numarasi(bulundugu indisi) yazdiriliyor.
						}
				}
				
			}
			printf("\n");
		}
		//Matrisin ilk halini yazdirma.
		printf("	___Matrisin ilk hali___\n");
		printMatris(Matris,N,Renkler);
		//Back Tracking islemine gönderiyoruz.
		backTracking(Matris,0,N,0,Renkler);
		
		if(checking(Matris,N-1,N)==-1){ // Eger tum sutunlarda farkli sayilar yoksa Matris istenilen formata gelemiyecegi icin kullaniciye bildirilir.
			printf("	___Sonuc olusmamaktadir___\n");
		}
		
	}
	else{
		printf("3 ile 8 arasinda bir sayi girmelisiniz.");
	}
	
	return 0;
}
