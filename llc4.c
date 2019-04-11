int llc(char trama[], int longitud, char resultado[]){

	int ltrama=0,tipo_trama=0,aux=0,dividendo1=0,residuo=0,i=0,n_s=0,n_r=0,cont_res=0,potencia=0;
	char tipo_t[6],com_resp,p_f,cn_s[3],cn_r[3],*ptr;

	//Tramas de supervision
	char codigo_ss[3];

	//Tramas no numeradas
	char c_bin1[9],c_bin2[9],codigo_nonum[6];

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
	
		aux=0;

		dividendo1=trama[17];

		if(dividendo1!=0){


			while(dividendo1>1){
				residuo=dividendo1%2;
				c_bin2[aux]=residuo+48;
				aux++;
				dividendo1/=2;
			}
			c_bin2[aux]='1';
			aux++;
		}

		for(i=aux;i<8;i++){
			c_bin2[aux]='0';
			aux++;
		}
		//Tipo de trama
		if(c_bin1[0]=='0') tipo_trama=1;	
		else if(c_bin1[0]=='1' && c_bin1[1]=='0')tipo_trama=2;	
		else if(c_bin1[0]=='1' && c_bin1[1]=='1')tipo_trama=3;	


		//Comando o respuesta
		if(trama[15]&1)com_resp='r';
		else com_resp='c';

		//Poll/final
		p_f=c_bin2[0];

		//N(R) tanto para trama de informacion como de supervision
		for(i=1;i<8;i++){
			
			if(c_bin2[i]=='1')n_r+=(1<<potencia);
			potencia++;
		}

		//Conversion del N(R) a arreglo
		sprintf(cn_r,"%d",n_r);

		//Trama de informacion
		if(tipo_trama==1){
			strcpy(tipo_t,"I\0");

			//N(S)
			potencia=0;
			for(i=1;i<8;i++){
				if(c_bin1[i]=='1')n_s+=(1<<potencia);
				potencia++;
			}

			//Conversion del N(s) a arreglo
			sprintf(cn_s,"%d",n_s);

			//respuesta[tipo]

			for(ptr=tipo_t;(*ptr)!='\0';ptr++){
				resultado[cont_res]=(*ptr);
				cont_res++;
			}

			//respuesta[N(s)]

			resultado[cont_res]=',';
			cont_res++;
			resultado[cont_res]=' ';
			cont_res++;
			resultado[cont_res]='N';
			cont_res++;
			resultado[cont_res]='(';
			cont_res++;
			resultado[cont_res]='S';
			cont_res++;
			resultado[cont_res]=')';
			cont_res++;
			resultado[cont_res]='=';
			cont_res++;

			if(n_s<10){
				resultado[cont_res]=cn_s[0];
				cont_res++;
			}else{
				for(i=0;i<2;i++){
					resultado[cont_res]=cn_s[i];
					cont_res++;	
				}
			}

			//respuesta[N(R)]

			resultado[cont_res]=',';
			cont_res++;
			resultado[cont_res]=' ';
			cont_res++;

			resultado[cont_res]='N';
			cont_res++;
			resultado[cont_res]='(';
			cont_res++;
			resultado[cont_res]='R';
			cont_res++;
			resultado[cont_res]=')';
			cont_res++;
			resultado[cont_res]='=';
			cont_res++;

			if(n_r<10){
				resultado[cont_res]=cn_r[0];
				cont_res++;
			}else{
				for(i=0;i<2;i++){
					resultado[cont_res]=cn_r[i];
					cont_res++;	
				}
			}

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


			//respuesta[N(R)]

			resultado[cont_res]=',';
			cont_res++;
			resultado[cont_res]=' ';
			cont_res++;
			resultado[cont_res]='N';
			cont_res++;
			resultado[cont_res]='(';
			cont_res++;
			resultado[cont_res]='R';
			cont_res++;
			resultado[cont_res]=')';
			cont_res++;
			resultado[cont_res]='=';
			cont_res++;

			if(n_r<10){
				resultado[cont_res]=cn_r[0];
				cont_res++;
			}else{
				for(i=0;i<2;i++){
					resultado[cont_res]=cn_r[i];
					cont_res++;	
				}
			}

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
			
		}


		//respuesta[p/f]

		if(p_f=='1'){
			resultado[cont_res]=',';
			cont_res++;
			resultado[cont_res]=' ';
			cont_res++;

			if(com_resp=='c'){
				resultado[cont_res]='p';
				cont_res++;
				resultado[cont_res]=' ';
				cont_res++;
				resultado[cont_res]='(';
				cont_res++;
				resultado[cont_res]='C';
				cont_res++;
				resultado[cont_res]=')';
				cont_res++;
			}else if(com_resp=='r'){
				resultado[cont_res]='f';
				cont_res++;
				resultado[cont_res]=' ';
				cont_res++;
				resultado[cont_res]='(';
				cont_res++;
				resultado[cont_res]='R';
				cont_res++;
				resultado[cont_res]=')';
				cont_res++;
			}

			resultado[cont_res]='\0';
		}else{
			resultado[cont_res]='\0';
		}

	}
	return ltrama;
}