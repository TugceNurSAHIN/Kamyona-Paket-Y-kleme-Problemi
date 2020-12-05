#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ister olarak sadece out.txt dosyasýna yazýlmasý istendiði için terminalde deðer çýkmayacaktýr.
int main(){
    ifstream dosyaOku("in.txt");
    ofstream output;
    output.open("out.txt");
    char ch;    
    int total_pocket = 0, vehicle_cap = 0, cost = 0;
    int vehicle_locate1=0, vehicle_locate2=0;
    int pocket_counter=0,vehicle_counter=0;
    int pocket_size = 0, vehicle_size= 0;
    int flag=0, flag2 = 0, flag3=0;
    int pocket[1000],vehicle[1000];
    int vehicle_no,revehicle=0;            
    int locate1[1000][2];
    int min_cost = 1000;
    int i=0,j=0,k=0,x=0;       
    int number = 0;    

    if (dosyaOku.is_open()) {        	  //Dosya okuma iþlemi gerçekleþtiriliyor
       while (dosyaOku.get(ch)) {
            if (ch=='#') { flag++; }                //Paketler ve araçlarý ayýrmak amacýyla '#' simgesine bakýyoruz. 
            if (flag == 1) {                    
                if (ch <= '9' && ch >= '0' ) {
		    pocket[pocket_counter] = ch - '0';
                    pocket_counter++;
                    }
                }
            else {
                if (ch <= '9' && ch >= '0') {
		    vehicle[vehicle_counter] = ch - '0';
                    vehicle_counter++; }
                } }  }
    for (i = 0;  i< pocket_counter; i=i+3) 							//Toplamda paketlerin kapladýðý alaný bulmak için (en*boy*adet)
       total_pocket += pocket[i] * pocket[i + 1] * pocket[i + 2];
    
    for (i= 0; i < vehicle_counter; i = i + 3) {				//Hangi aracý seçeceðimizi bulduðumuz fonksiyon
        vehicle_cap += vehicle[i] * vehicle[i+1];				//Tek araç yetmediðinde iki araçla maliyetine bakar ve bunu diðer araçlarla karþýlaþtýrýr.
        cost += vehicle[i + 2];           
        if (vehicle_cap >= total_pocket) {
            vehicle_cap = 0;
            if (cost<min_cost) {                    
               min_cost = cost;
               vehicle_no = i - (number * 3); 
               revehicle = 0;
               for (j = 0; j <= number; j++){
                   revehicle++;
                   for (k = 0; k < 2; k++) {
                       locate1[j][k] = vehicle[vehicle_no];
                       vehicle_no++;}
                   vehicle_no += 2; }
                   cost = 0;
                   number = 0;
                   continue;}   }
            number++;           }    
    output<< "# Toplam Maliyet" <<'\n'<< min_cost << '\n'; 
    output<<"# Yükleme Planý" << '\n'; 
    j=0; 
    for(i=0; i<revehicle;i++){					//Yerleþtirmenin yapýldýðý fonksiyon
	vehicle_locate1=0;
	vehicle_locate2=0;
	output<< locate1[i][x] << "x" << locate1[i][x+1] << ":" << "(" << revehicle << ")" << '\n';	
	if(flag3>0 && i>0){							
	while(flag3>0){								//Ýlk araç dolduktan sonra ikinci aracý doldurmaya baþlar 
		pocket_size=pocket[j]*pocket[j+1];
		if(pocket_size>0)
			output<<pocket[j]<<"x"<<pocket[j+1]<<" "<<">"<<" ";	
		while(pocket_size>0){
			flag2++;
			output<<"("<<vehicle_locate1<<"."<<vehicle_locate2<<")";
			output<<" ";
			pocket_size--;
			vehicle_locate2++;
		if(vehicle_locate2==(locate1[i][x])){
			vehicle_locate1++;
			vehicle_locate2=0;
				}  }  
		output<<'\n';
		flag3--;	}
	j=j+3;  }
	flag2=0;	
	vehicle_size = locate1[i][x] *locate1[i][x + 1];
	while(vehicle_size>0){
		if (j>=sizeof(pocket))   break;
		for(k=0; k<pocket[j+2];k++){
			vehicle_size-=(pocket[j]*pocket[j+1]);
			if(vehicle_size<0){
				vehicle_locate1=0;
				vehicle_locate2=0;
				flag3=pocket[j+2]-flag3;
				break;}
			else{	
				flag3++;
				pocket_size=pocket[j]*pocket[j+1];
				if(pocket_size>0){
					output<<pocket[j]<<"x"<<pocket[j+1]<<" "<<">"<<" ";}
				while(pocket_size>0){
					flag2++;
					output<<"("<<vehicle_locate1<<"."<<vehicle_locate2<<")"<<" ";
					pocket_size--;
					vehicle_locate2++;
					if(vehicle_locate2==(locate1[i][x])){
						vehicle_locate1++;
						vehicle_locate2=0;	}   }
				output<<'\n';		}	}
		if(vehicle_size<0)	break;
		j=j+3;   }
	output<<'\n'; }
dosyaOku.close();
output.close(); 
return 0;  }

