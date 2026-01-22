#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void cs() {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}
int main() {
	int mi,pro,muup,miup,input,coins,gems,t,i,j,exist,k,l;
	long int loc,te;
	float mu;
	char a[50],b[50],c;
	unsigned long int st,et;
	FILE *fp,*temp;
	fp = fopen("Saves.txt","a");
	fclose(fp);
	fp = fopen("Temp.txt","w");
	fclose(fp);
	fp = fopen("Saves.txt","r");
	printf("-----< Welcome to Mines >-----\n\nEnter Player Name : ");
	scanf("%s",a);
	exist = 0;
	do{
		c = fgetc(fp);
		if(((c != EOF)&&(c == ':'))||(ftell(fp)==1)) {
			if(ftell(fp)==1) rewind(fp);
			fscanf(fp,"%s",b);
			loc = ftell(fp);
			if(strcmp(a,b) == 0) {
				exist = 1;
				printf("\n----------< Existing Player detected >----------\n");
				fscanf(fp,"%d",&mi);
				fscanf(fp,"%f",&mu);
				fscanf(fp,"%d",&coins);
				fscanf(fp,"%d",&gems);
				break;
			}
		}
	}while((c != EOF)&&(input == 0));
	fclose(fp);
	if(exist == 0) {
		printf("\n----------< New Player detected >----------\n");
		mi = 1;
		mu = 1;
		coins = 0;
		gems = 0;
	}
	st = time(NULL);
	do{
		printf("\n<-[ Enter any Number to continue ]->");
		scanf("%d",&i);
		cs();
		pro = mi * mu;
		printf("|> Coins = %d \n|> Gems = %d \n|> No. of mines = %d \n|> Multiplier = %.1f \n",coins,gems,mi,mu);
		printf("\n---< Select a Option (OR) Wait >---\n\n1. Withdraw Coins\n2. Convert Currency\n3. Upgrade Mines\n4. Save progress\n5. Exit\nOption : ");
		do{
			scanf("%d",&input);
			if((input < 1)||(input > 5)) printf("-< Wrong option >-\nOption : ");
		}while((input < 1)||(input > 5));
		switch(input){
			case 1:
				et = time(NULL);
				t = (int)(et-st);
				coins = coins + (pro * t);
				printf("Coins Withdrawed = %d\n",pro * t);
				st = time(NULL);
				break;
			case 2:
				printf("---< [ 100 coins = 1 Gem ] >---\n1. Coins to Gems\n2. Gems to Coins\nOption : ");
				do{
					scanf("%d",&i);
					if((i < 1)||(i > 2)) printf("-< Wrong option >-\nOption : ");
				}while((i < 1)||(i > 2));
				switch(i) {
					case 1:
						printf("Enter coins in Multiples of 100 ('0' to exit) : ");
						do{
							scanf("%d",&i);
							if(i > coins) printf("-< Can't Enter more than current Coins >-\nCoins : ");
							else if(i % 100 != 0) printf("-< Not Divisible by 100 >-\nCoins : ");
						}while((i > coins)||(i % 100 != 0));
						gems = gems + (i / 100);
						coins -= i;
						break;
					case 2:
						printf("Enter Gems ('0' to exit) : ");
						do{
							scanf("%d",&i);
							if(i > gems) printf("-< Can't Enter more than current Coins >-\nCoins : ");
						}while(i > gems);
						coins = coins + (i * 100);
						gems -= i;
					break;
				}
				if(i == 0) printf("-< No Conversion Made >-\n");
				else printf("-< Conversion Successful >-\nCurrent Coins : %d\nCurrent Gems : %d\n",coins,gems);
				break;
			case 3:
				printf("\n---< [ Upgrade Menu ] >---\n1. Increase Mines\n2. Upgrade Multiplier\n3. Exit\nOption : ");
				do{
					scanf("%d",&i);
					if((i < 1)||(i > 3)) printf("-< Wrong option >-\nOption : ");
				}while((i < 1)||(i > 3));
				switch(i) {
					case 1:
						miup = mi * mi;
						printf("\n||> Upgrade [ %d Mines => %d Mines ] |=> Cost : %d Gems <||\nWish to Upgrade [ 1. Yes | 2. No ]\nOption : ",mi,mi+1,miup);
						do{
							scanf("%d",&j);
							if((j < 1)||(j > 2)) printf("-< Wrong option >-\nOption : ");
						}while((j < 1)||(j > 2));
						if(j == 1) {
							if(miup > gems) {
								printf("\n-< Not Enough Gems >-\n");
								i = 3;
							}
							else {
								gems -= miup;
								mi++;
								printf("\n-< Upgrade Successful >-\nCurrent Gems : %d\n",gems);
							}
						}
						else i=3;
						break;
					case 2:
						muup = mu*mu*10;
						printf("\n||> Upgrade [ %.1f Multiplier => %.1f Multiplier ] |=> Cost : %d Coins <||\nWish to Upgrade [ 1. Yes | 2. No ]\nOption : ",mu,mu+0.1,muup);
						do{
							scanf("%d",&j);
							if((j < 1)||(j > 2)) printf("-< Wrong option >-\nOption : ");
						}while((j < 1)||(j > 2));
						if(j == 1) {
							if(muup > coins) {
								printf("\n-< Not Enough Coins >-\n");
								i = 3;
							}
							else {
								coins -= muup;
								mu += 0.1;
								printf("\n-< Upgrade Successful >-\nCurrent Coins : %d\n",coins);
							}
						}
						else i=3;
						break;
				}
				if(i == 3) printf("\n-< No Upgrading Made >-\n\n");
				break;
			case 4:
				switch(exist) {
					case 0:
						fp = fopen("Saves.txt","a");
						fseek(fp,0,2);
						fprintf(fp,"%s ",a);
						fprintf(fp,"%d ",mi);
						fprintf(fp,"%f ",mu);
						fprintf(fp,"%d ",coins);
						fprintf(fp,"%d :",gems);
						fclose(fp);
						printf("---< Save Sucessful >---\n");
						break;
					case 1:
						fp = fopen("Saves.txt","r");
						temp = fopen("Temp.txt","w");
						rewind(fp);
						while (fscanf(fp,"%s %d %f %d %d:",b,&i,&j,&k,&l) == 5) {
            				if (strcmp(b,a) == 0) fprintf(temp,"%s %d %.1f %d %d:\n",a,mi,mu,coins,gems);
            				else fprintf(temp,"%s %d %.1f %d %d:\n",b,i,j,k,l);
       					}
						fclose(fp);
						fclose(temp);
						remove("Saves.txt");
						rename("Temp.txt","Saves.txt");
						printf("---< Save Sucessful >---\n");
						break;
				}
				break;
		}
	}while(input != 5);
	return 0;
}
/*
mi = no. of mines
mu = multiplier per mine
pro = production per second
t = time taken
st = start time
et = end time
miup = mine upgrade
muup = multiplier upgrade
loc = location
te = temp location
*/