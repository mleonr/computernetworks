#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <string.h>
int llc(char trama[], int longitud, char resultado[],int longresultado);

int main(){
	
	int lng=100,lngr=100;

	char *tram,*res;
	tram = (char*)malloc(100);
	res = (char*)malloc(100);

	scanf("%s",tram);

	if(llc(tram,lng,res,lngr)==1){
		printf("%s",res);
	}


	return 0;
}
int llc(char trama[], int longitud, char resultado[],int longresultado){

	int cont_dA=0,cont_sA=0, cont_dsap=0,cont_ssap=0,cont_control=0,nibble=0,bytes;
	int cont=0,j,k,m,n,contRes=0,cont_bs=0,cont_bc=0,ns=0,nr=0, bin=6, cont_un=0;
	char *dA,*sA, *dsap,*ssap,*control,*bin_ssap,*bin_control,*ns_i,*nr_i,*nr_s,*inf;
	char *i,*h,*g,*f,*e,*d;
	char commandResponse,frameType;

	dA = (char*)malloc(13);
	sA = (char*)malloc(13);
	dsap = (char*)malloc(3);
	ssap = (char*)malloc(3);
	control = (char*)malloc(5);

	bin_ssap = (char*)malloc(9);
	bin_control = (char*)malloc(17);
	ns_i = (char*)malloc(3);
	nr_i = (char*)malloc(3);
	nr_s = (char*)malloc(3);
	inf = (char*)malloc(6); 

	for(i=trama;(*i)!='\0';i++){
		
		if((*i)!=32){

			if(cont<12)dA[cont_dA++]=(*i);
			if(cont>11 && cont<24)sA[cont_sA++]=(*i);
			if(cont>27 && cont<30)dsap[cont_dsap++]=(*i);
			if(cont>29 && cont<32)ssap[cont_ssap++]=(*i);
			if(cont>31 && cont<36)control[cont_control++]=(*i);

			cont++;
			nibble++;				
		}
	}

	dA[cont_dA]='\0';
	sA[cont_sA]='\0';
	dsap[cont_dsap]='\0';
	ssap[cont_ssap]='\0';
	control[cont_control]='\0';

	bytes=nibble/2;

	for(j=0;j<12;j++)resultado[contRes++]=dA[j];
	resultado[contRes++]=32;
	for(j=0;j<12;j++)resultado[contRes++]=sA[j];
	resultado[contRes++]=32;	
	resultado[contRes++]='L';
	resultado[contRes++]='L';
	resultado[contRes++]='C';
	resultado[contRes++]=32;


	//Obtencion de command|response

	for(h=ssap;(*h)!='\0';h++){
		switch(*h){
			case '0':
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='0';
			break;
			case '1':
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='1';
			break;
			case '2':
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='0';
			break;
			case '3':
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='1';
			break;
			case '4':
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='0';
			break;
			case '5':
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='1';
			break;
			case '6':
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='0';
			break;
			case '7':
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='1';
			break;
			case '8':
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='0';
			break;
			case '9':
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='1';
			break;
			case 'a':
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='0';
			break;
			case 'b':
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='1';
			break;
			case 'c':
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='0';
			break;
			case 'd':
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='0';
				bin_ssap[cont_bs++]='1';
			break;
			case 'e':
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='0';
			break;
			case 'f':
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='1';
				bin_ssap[cont_bs++]='1';
			break;
		}
	}
	bin_ssap[cont_bs]='\0';

	if(bin_ssap[7]=='0')commandResponse='C';
	else commandResponse='R';

	resultado[contRes++]=commandResponse;
	resultado[contRes++]=32;

	//ssap
	resultado[contRes++]='S';
	resultado[contRes++]='=';
	resultado[contRes++]=ssap[0];
	resultado[contRes++]=ssap[1];
	resultado[contRes++]=32;
	
	//dsap
	resultado[contRes++]='D';
	resultado[contRes++]='=';
	resultado[contRes++]=dsap[0];
	resultado[contRes++]=dsap[1];
	resultado[contRes++]=32;

	//Obtencion de tipo de frame

	for(g=control;(*g)!='\0';g++){
		switch(*g){
			case '0':
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='0';
			break;
			case '1':
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='1';
			break;
			case '2':
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='0';
			break;
			case '3':
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='1';
			break;
			case '4':
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='0';
			break;
			case '5':
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='1';
			break;
			case '6':
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='0';
			break;
			case '7':
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='1';
			break;
			case '8':
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='0';
			break;
			case '9':
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='1';
			break;
			case 'a':
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='0';
			break;
			case 'b':
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='1';
			break;
			case 'c':
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='0';
			break;
			case 'd':
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='0';
				bin_control[cont_bc++]='1';
			break;
			case 'e':
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='0';
			break;
			case 'f':
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='1';
				bin_control[cont_bc++]='1';
			break;
		}
	}

	bin_control[cont_bc]='\0';

	if(bin_control[7]=='0')frameType='I';
	if(bin_control[6]=='0' && bin_control[7]=='1')frameType='S';
	if(bin_control[6]=='1' && bin_control[7]=='1')frameType='U';

	if(frameType=='I'){
		resultado[contRes++]='I';
		//Obtencion bit P/F
		if(bin_control[15]=='1' && commandResponse=='C'){
			resultado[contRes++]='-';
			resultado[contRes++]='p';
			resultado[contRes++]=32;
		}else if(bin_control[15]=='1' && commandResponse=='R'){
			resultado[contRes++]='-';
			resultado[contRes++]='f';
			resultado[contRes++]=32;
		}else{
			resultado[contRes++]=32;
		}

		resultado[contRes++]='N';
		resultado[contRes++]='R';
		resultado[contRes++]='=';


		for(m=8;m<15;m++){
			if(bin_control[m]=='0'){
				nr+=(0*(pow(2,bin--)));
			}else{
				nr+=(1*(pow(2,bin--)));
			}
		}

		bin=6;
		
		sprintf(nr_i,"%d",nr);

		for(f=nr_i;(*f)!='\0';f++){
			resultado[contRes++]=(*f);
		}

		resultado[contRes++]=32;
		resultado[contRes++]='N';
		resultado[contRes++]='S';
		resultado[contRes++]='=';

		for(k=0;k<7;k++){
			if(bin_control[k]=='0'){
				ns+=(0*(pow(2,bin--)));
			}else{
				ns+=(1*(pow(2,bin--)));
			}
		}

		sprintf(ns_i,"%d",ns);

		for(e=ns_i;(*e)!='\0';e++){
			resultado[contRes++]=(*e);
		}

	}else if(frameType=='S'){

		if(bin_control[4]=='0' && bin_control[5]=='0'){
			resultado[contRes++]='R';
			resultado[contRes++]='R';
		}else if(bin_control[4]=='0' && bin_control[5]=='1'){
			resultado[contRes++]='R';
			resultado[contRes++]='N';
			resultado[contRes++]='R';
		}else if(bin_control[4]=='1' && bin_control[5]=='0'){
			resultado[contRes++]='R';
			resultado[contRes++]='E';
			resultado[contRes++]='J';
		}

		if(bin_control[15]=='1' && commandResponse=='C'){
			resultado[contRes++]='-';
			resultado[contRes++]='p';
			resultado[contRes++]=32;
		}else if(bin_control[15]=='1' && commandResponse=='R'){
			resultado[contRes++]='-';
			resultado[contRes++]='f';
			resultado[contRes++]=32;
		}else{
			resultado[contRes++]=32;
		}

		resultado[contRes++]='N';
		resultado[contRes++]='R';
		resultado[contRes++]='=';

		nr=0;
		for(m=8;m<15;m++){
			if(bin_control[m]=='0'){
				nr+=(0*(pow(2,bin--)));
			}else{
				nr+=(1*(pow(2,bin--)));
			}
		}
		
		sprintf(nr_s,"%d",nr);

		for(d=nr_s;(*d)!='\0';d++){
			resultado[contRes++]=(*d);
		}
	
	}else if(frameType=='U'){
		for(n=0;n<6;n++){
			if(n!=3)inf[cont_un++]=bin_control[n];
		}

		inf[cont_un]='\0';

		if(strcmp(inf,"00000")==0){
			resultado[contRes++]='U';
			resultado[contRes++]='I';
		}else if(strcmp(inf,"00011")==0){
			resultado[contRes++]='D';
			resultado[contRes++]='M';
		}else if(strcmp(inf,"01000")==0){
			resultado[contRes++]='D';
			resultado[contRes++]='I';
			resultado[contRes++]='S';
			resultado[contRes++]='C';
		}else if(strcmp(inf,"01100")==0){
			resultado[contRes++]='U';
			resultado[contRes++]='A';
		}else if(strcmp(inf,"01111")==0){
			resultado[contRes++]='S';
			resultado[contRes++]='A';
			resultado[contRes++]='B';
			resultado[contRes++]='M';
			resultado[contRes++]='E';
		}else if(strcmp(inf,"10001")==0){
			resultado[contRes++]='F';
			resultado[contRes++]='R';
			resultado[contRes++]='M';
			resultado[contRes++]='R';
		}else if(strcmp(inf,"10001")==0){
			resultado[contRes++]='F';
			resultado[contRes++]='R';
			resultado[contRes++]='M';
			resultado[contRes++]='R';
		}else if(strcmp(inf,"10111")==0){
			resultado[contRes++]='X';
			resultado[contRes++]='I';
			resultado[contRes++]='D';
		}else if(strcmp(inf,"11100")==0){
			resultado[contRes++]='T';
			resultado[contRes++]='E';
			resultado[contRes++]='S';
			resultado[contRes++]='T';
		}

		if(bin_control[3]=='1' && commandResponse=='C'){
			resultado[contRes++]='-';
			resultado[contRes++]='p';
		}else if(bin_control[3]=='1' && commandResponse=='R'){
			resultado[contRes++]='-';
			resultado[contRes++]='f';
		}


	}

	resultado[contRes]='\0';
	printf("dA: %s\n", dA);
	printf("sA: %s\n", sA);
	printf("dsap : %s\n",dsap);
	printf("ssap : %s\n",ssap);	
	printf("control : %s\n",control);	
	printf("Framse size: %d\n",bytes);
	printf("control field bin: %s\n",bin_control);
	printf("Type: %c\n",frameType);

	return 1;
}