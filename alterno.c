#include<stdio.h>
#include<stdlib.h>
#include <string.h>
void llc_frame(char *c);
char* bin_parser(char *c);
char comm_resp(char *c);
char frame_type(char *c);
char* subType_frame(char *c, char t);


int main(){

	char *cad;
	cad  	= (char *) malloc(201);

	scanf("%s",cad);

	llc_frame(cad);

	return 0;
}

void llc_frame(char *c){

	int cont=0,cont_dA=0,cont_sA=0, cont_dsap=0,cont_ssap=0,cont_control=0, frameSize=0;
	char comResp,ftype;
	char *i,*dA,*sA, *dsap,*ssap,*control, *bin_control,*bin_ssap,*bin_control_f,*overview;


	dA = (char*)malloc(13);
	sA = (char*)malloc(13);
	dsap = (char*)malloc(3);
	ssap = (char*)malloc(3);
	control = (char*)malloc(5);
	overview = (char*)malloc(101);


	for(i=c;(*i)!='\0';i++){
		if(cont<12){
			dA[cont_dA++]=(*i);
		}
		if(cont>11 && cont<24){
			sA[cont_sA++]=(*i);
		}
		if(cont>27 && cont<30){
			dsap[cont_dsap++]=(*i);
		}
		if(cont>29 && cont<32){
			ssap[cont_ssap++]=(*i);
		}
		if(cont>31 && cont<36){
			control[cont_control++]=(*i);
		}

		cont++;

		frameSize++;
	}

	dA[cont_dA]='\0';
	sA[cont_sA]='\0';
	dsap[cont_dsap]='\0';
	ssap[cont_ssap]='\0';
	control[cont_control]='\0';
	
	frameSize/=2;

	bin_ssap = bin_parser(ssap);
	comResp = comm_resp(bin_ssap);
	bin_control = bin_parser(control);	
	ftype = frame_type(bin_control);

	if(ftype=='u'){
		bin_control_f=(char*)malloc(9);
		for(int j=0;j<8;j++){
			bin_control_f=bin_control;
		}
		bin_control_f[8]='\0';
	}else{
		bin_control_f=(char*)malloc(17);
		for(int j=0;j<16;j++){
			bin_control_f=bin_control;
		}
		bin_control_f[16]='\0';
	}

	
	overview = subType_frame(bin_control_f,frame_type(bin_control));
	//char carr[9]={'h','l','o','a','s','t','d','\0'};
	//overview = subType_frame(carr,'u');


	//printf("dA: %s\n", dA);
	//printf("sA: %s\n", sA);
	//printf("dsap : %s\n",dsap);
	//printf("ssap : %s\n",ssap);	
	//printf("control : %s\n",control);	
	//printf("Framse size: %d\n",frameSize);
	
	//printf("Command/Response: %c\n",comResp);
	//printf("Binary control: %s\n",bin_control_f);
	//printf("Type: %c\n",ftype);
		
}
char* bin_parser(char *c){

	int cont=0;
	char *i,*ans;
	ans = (char*)malloc(17);

	for(i=c;(*i)!='\0';i++){
		switch(*i){
			case '0':
				ans[cont++]='0';
				ans[cont++]='0';
				ans[cont++]='0';
				ans[cont++]='0';
			break;
			case '1':
				ans[cont++]='0';
				ans[cont++]='0';
				ans[cont++]='0';
				ans[cont++]='1';
			break;
			case '2':
				ans[cont++]='0';
				ans[cont++]='0';
				ans[cont++]='1';
				ans[cont++]='0';
			break;
			case '3':
				ans[cont++]='0';
				ans[cont++]='0';
				ans[cont++]='1';
				ans[cont++]='1';
			break;
			case '4':
				ans[cont++]='0';
				ans[cont++]='1';
				ans[cont++]='0';
				ans[cont++]='0';
			break;
			case '5':
				ans[cont++]='0';
				ans[cont++]='1';
				ans[cont++]='0';
				ans[cont++]='1';
			break;
			case '6':
				ans[cont++]='0';
				ans[cont++]='1';
				ans[cont++]='1';
				ans[cont++]='0';
			break;
			case '7':
				ans[cont++]='0';
				ans[cont++]='1';
				ans[cont++]='1';
				ans[cont++]='1';
			break;
			case '8':
				ans[cont++]='1';
				ans[cont++]='0';
				ans[cont++]='0';
				ans[cont++]='0';
			break;
			case '9':
				ans[cont++]='1';
				ans[cont++]='0';
				ans[cont++]='0';
				ans[cont++]='1';
			break;
			case 'a':
				ans[cont++]='1';
				ans[cont++]='0';
				ans[cont++]='1';
				ans[cont++]='0';
			break;
			case 'b':
				ans[cont++]='1';
				ans[cont++]='0';
				ans[cont++]='1';
				ans[cont++]='1';
			break;
			case 'c':
				ans[cont++]='1';
				ans[cont++]='1';
				ans[cont++]='0';
				ans[cont++]='0';
			break;
			case 'd':
				ans[cont++]='1';
				ans[cont++]='1';
				ans[cont++]='0';
				ans[cont++]='1';
			break;
			case 'e':
				ans[cont++]='1';
				ans[cont++]='1';
				ans[cont++]='1';
				ans[cont++]='0';
			break;
			case 'f':
				ans[cont++]='1';
				ans[cont++]='1';
				ans[cont++]='1';
				ans[cont++]='1';
			break;
		}
	}
	ans[cont]='\0';
	return ans;
}

char comm_resp(char *c){
	char ans;
	char *i;

	for(i=c;(*i)!='\0';i++){
		ans=(*i);
	}
	if(ans=='0'){
		ans='c';
	}else{
		ans='r';
	}
	return ans;
}

char frame_type(char *c){
	char ans;
	if(c[6]=='0' && c[7]=='0'){
		ans = 'i';
	}else if(c[6]=='0' && c[7]=='1'){
		ans = 's';
	}else if(c[6]=='1' && c[7]=='1'){
		ans='u';
	}
	return ans;
}

char* subType_frame(char *c, char t){
	
	int i,cont=0;
	char pf;
	char *s,*inf;

	inf=(char*)malloc(6);

	s = (char*)malloc(101);


	switch(t){
		case 'i':
		break;
		case 's':
		break;
		case 'u':
			for(i=0;i<6;i++){
				if(i!=3){
					inf[cont++]=c[i];
				}
			}
			inf[cont]='\0';

			if(strcmp(inf,"00011")==0){
				s[0]='D';
				s[1]='M';
				s[2]='-';
			}else if(strcmp(inf,"01000")==0){

			}
			
		break;
	}
	
	

	return s;
	
}