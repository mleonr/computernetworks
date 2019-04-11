int llc(char trama[], int longitud, char resultado[]){

	int ltrama=0,tipo_trama=0,aux=0,dividendo1=0,residuo=0,i=0,cont_res=0;
	char tipo_t[6],com_resp,*ptr;

	//Tramas de supervision
	char codigo_ss[3];

	//Tramas no numeradas
	char c_bin1[9],codigo_nonum[6];

	if((trama[12]*256+trama[13])<1500){	
		ltrama=1;

		//Campo de control en binario
		dividendo1=trama[16];

		if(dividendo1!=0){
			while(dividendo1>1){
				residuo=dividendo1%2;
				c_bin1[aux]=residuo+48;
				aux++;
				dividendo1/=2;
			}

			c_bin1[aux]='1';
			aux++;
		}
		for(i=aux;i<8;i++){
			c_bin1[aux]='0';
			aux++;
		}

		//Tipo de trama
		if(c_bin1[0]=='0') tipo_trama=1;	
		else if(c_bin1[0]=='1' && c_bin1[1]=='0')tipo_trama=2;	
		else if(c_bin1[0]=='1' && c_bin1[1]=='1')tipo_trama=3;	


		//Comando o respuesta
		if(trama[15]&1)com_resp='r';
		else com_resp='c';

		//Trama de informacion
		if(tipo_trama==1){
			strcpy(resultado,"informacion\0");
		}
		//Trama de supervision
		if(tipo_trama==2){
			codigo_ss[0]=c_bin1[2];
			codigo_ss[1]=c_bin1[3];
			codigo_ss[2]='\0';

			if(strcmp(codigo_ss,"00")==0)strcpy(tipo_t,"RR\0");
			else if(strcmp(codigo_ss,"01")==0)strcpy(tipo_t,"REJ\0");
			else if(strcmp(codigo_ss,"10")==0)strcpy(tipo_t,"RNR\0");
			else if(strcmp(codigo_ss,"11")==0)strcpy(tipo_t,"SREJ\0");

			//respuesta[tipo]

			for(ptr=tipo_t;(*ptr)!='\0';ptr++){
				resultado[cont_res]=(*ptr);
				cont_res++;
			}
			//código extra
			resultado[cont_res]='\0';


		}
		//Trama no numerada
		if(tipo_trama==3){

			codigo_nonum[0]=c_bin1[2];
			codigo_nonum[1]=c_bin1[3];
			codigo_nonum[2]=c_bin1[5];
			codigo_nonum[3]=c_bin1[6];
			codigo_nonum[4]=c_bin1[7];
			codigo_nonum[5]='\0';
			
			//Trama no numerada comando/respuesta
			if(com_resp=='c'){
				if(strcmp(codigo_nonum,"00011")==0) strcpy(tipo_t,"SNRM\0");
				else if(strcmp(codigo_nonum,"11011")==0) strcpy(tipo_t,"SNRME\0");
				else if(strcmp(codigo_nonum,"11000")==0) strcpy(tipo_t,"SARM\0");
				else if(strcmp(codigo_nonum,"11010")==0) strcpy(tipo_t,"SARME\0");
				else if(strcmp(codigo_nonum,"11100")==0) strcpy(tipo_t,"SABM\0");
				else if(strcmp(codigo_nonum,"11110")==0) strcpy(tipo_t,"SABME\0");
				else if(strcmp(codigo_nonum,"00000")==0) strcpy(tipo_t,"UI\0");
				else if(strcmp(codigo_nonum,"00010")==0) strcpy(tipo_t,"DISC\0");
				else if(strcmp(codigo_nonum,"10000")==0) strcpy(tipo_t,"SIM\0");
				else if(strcmp(codigo_nonum,"00100")==0) strcpy(tipo_t,"UP\0");
				else if(strcmp(codigo_nonum,"11001")==0) strcpy(tipo_t,"RSET\0");
				else if(strcmp(codigo_nonum,"11101")==0) strcpy(tipo_t,"XID\0");
			}else if(com_resp=='r'){
				if(strcmp(codigo_nonum,"11000")==0) strcpy(tipo_t,"DM\0");
				else if(strcmp(codigo_nonum,"00000")==0) strcpy(tipo_t,"UI\0");
				else if(strcmp(codigo_nonum,"00110")==0) strcpy(tipo_t,"UA\0");
				else if(strcmp(codigo_nonum,"00010")==0) strcpy(tipo_t,"RD\0");
				else if(strcmp(codigo_nonum,"10000")==0) strcpy(tipo_t,"RIM\0");
				else if(strcmp(codigo_nonum,"11101")==0) strcpy(tipo_t,"XID\0");
				else if(strcmp(codigo_nonum,"10001")==0) strcpy(tipo_t,"FRMR\0");
			}


			//respuesta[tipo]

			for(ptr=tipo_t;(*ptr)!='\0';ptr++){
				resultado[cont_res]=(*ptr);
				cont_res++;
			}
			//código extra
			resultado[cont_res]='\0';
			
		}




	}
	return ltrama;
}