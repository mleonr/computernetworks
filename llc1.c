int llc(char trama[], int longitud, char resultado[]){

	int ltrama=0,tipo_trama=0,aux=0,dividendo1=0,residuo=0,i=0;

	//Tramas no numeradas
	char c_bin1[9];
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

		if(tipo_trama==1){
			strcpy(resultado,"informacion\0");
		}
		//Trama de supervision
		if(tipo_trama==2){
			strcpy(resultado,"supervision\0");
		}
		//Trama no numerada
		if(tipo_trama==3){
			strcpy(resultado,"no numerada\0");
		}
	}
	return ltrama;
}