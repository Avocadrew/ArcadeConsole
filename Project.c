#include <regx51.h>
#include <stdlib.h>
sbit RS=P1^0;
sbit RW=P1^1;
sbit E=P1^2;



unsigned char idata table[16]={10,'0',11,12,'1','2','3',0X00,'4','5','6',0X00,'7','8','9',0X00};

#define Data P2
void beep(int a);
void LCD_Data(char WDLCD);
void LCD_CMD(char WCLCD);
void LCD_Init(int a);
char keyScan();
void delay(int x);
char detect=-1,remember = 0;
char pos=0xC0;
void LCD_GameAB();
void LCD_GameShip();
void LCD_Detete1();
int ans,inp,sit;
char fid,sed,thd,fod;
char inpfi,inpse,inpth,inpfo;
char a,b;
void Submit();
char bomb[6]={0x00,0x00,0x00,0x00,0x00,0x00};
void dis_answer();
void endcode();
int ranpivot;
char in[4]={0x99,0x99,0x99,0x99};
void reveal(char p);
int subtimes;
char mode;
char correct;
void randbomb();
void gamestart21();	//
void win();	//
void lose();	//
void draw();	//
char showcard(int );	//
int adjustpoint(int* ,int ,int );	//
void LCD_GameShip(){	
	char p = 0x80;
	int a=0,b=0;
	mode = 0;
	LCD_Init(3);
	randbomb();
	while(1){
		detect=keyScan();
		if(detect==-1){remember = 0;}
		if(detect == 5 && remember == 0 ){
			if(b!=1){
				p=p+0x40;
				b=1;
				LCD_CMD(p);
				remember = 1;
			}
		}
		if(detect == 13 && remember == 0 ){
			if(b!=0){
				b=0;
				p=p-0x40;
				LCD_CMD(p);
				remember = 1;
				}
		}
		if(detect == 10 && remember == 0){
			if(a!=15){
				p=p+1;
				a++;
				LCD_CMD(p);
				remember = 1;
			}
		}
		if(detect == 8 && remember == 0){
			if(a!=0){
				p=p-1;
				a--;
				LCD_CMD(p);
				remember = 1;
			}
		}
		if(detect == 9){
			reveal(p);
			LCD_CMD(p);}
}}
void randbomb(){
	char tam,bam,count,count1;
	subtimes=0;
	tam = rand() % 7;
	bam = 6 - tam;
	for(count = 0; count <= tam-1; count++){
		bomb[count]=0x80+rand()%16;
		if(count!=0){
			for(count1=0;count1<count;count1++){
				while(bomb[count]==bomb[count1]){
					bomb[count]=0x80+rand()%16;}}}}
		
	for(count = 0; count <= bam-1; count++){
		bomb[count+tam]=0xC0+rand()%16;
		if(count!=0){
			for(count1=0;count1<count;count1++){
				while(bomb[count]==bomb[count1]){
					bomb[count]=0x80+rand()%16;}}}}
}

void reveal(char p){
	int i,j=correct;
	subtimes=subtimes+1;
	for(i = 0;i<=5;i++){
		if(bomb[i]==p){
			LCD_Data(0x4F);
			correct++;
			bomb[i]=0x00;}}
		if(correct==6){
				delay(200);
				LCD_Init(2);}
		if(correct == j){
			LCD_Data(0x58);}}

char keyScan(){
	 char j=0;
	P0=0XF0;
		switch(P0){
			case 0XE0:
				j=3;
				break;
			case 0XD0:
				j=2;
				break;
			case 0XB0:
				j=1;
				break;
			case 0X70:
				j=0;
				break;
			case 0XF0:
				return -1;
				break;
			default:
				return -1;
		}
		P0=0X0F;
		switch(P0){
			case 0X0E:
				beep(1);
				return 4*j;
				break;
			case 0X0D:
				beep(1);
				return 4*j+1;
				break;
			case 0X0B:
				beep(1);
				return 4*j+2;
				break;
			case 0X07:
				beep(1);
				return 4*j+3;
				break;
			case 0X0F:
				return -1;
				break;
			default:
				return -1;
		}}


void LCD_Data(char WDLCD)
{
	Data = WDLCD;
	RS = 1;
	RW = 0;
	E = 1; 
	delay(70); 
	E = 0; 
	delay(70); 
}

void LCD_CMD(char WCLCD)
{
	Data = WCLCD;
	RS = 0;
	RW = 0; 
	E = 1;
	delay(70);
	E = 0;
	delay(70); 
}
void startcode(){
	char i;
	unsigned char idata start[15]={0x20,0x50,0x75,0x73,0x68,0x20,0x42,0x75,0x74,0x74,0x6F,0x6E,0x20,0x54,0x6F};
	unsigned char idata start1[5]={0x53,0x74,0x61,0x72,0x74};
	for(i=0;i<=14;i++){
		LCD_Data(start[i]);}
	LCD_CMD(0xC0);
	for(i=0;i<=5;i++){
		LCD_Data(0x20);}
	for(i=0;i<=4;i++){
		LCD_Data(start1[i]);}}

void incode(){
	char i;
	unsigned char idata ingame[15]={0x20,0x49,0x6E,0x70,0x75,0x74,0x20,0x34,0x20,0x64,0x69,0x67,0x69,0x74,0x73};
	for(i=0;i<=14;i++){
		LCD_Data(ingame[i]);}
	LCD_CMD(0xC0);
	for(i=0;i<=3;i++){
		LCD_Data(0x5F);}}

void endcode(){
	char i;
	unsigned char idata endgame[6]={0x42,0x69,0x6E,0x67,0x6F,0x21};
	unsigned char idata endgame2[6]={0x74,0x69,0x6D,0x65,0x73,0x3A};
	LCD_CMD(0x85);
	if(mode == 1){
		for(i=0;i<=5;i++){
			LCD_Data(endgame[i]);}}
	if(mode == 0){
		char code a[]="WIN!";
		LCD_CMD(0x8A);
		for(i=0;i<4;i++){
			LCD_Data(a[i]);
		}}
	LCD_CMD(0xC0);
	for(i=0;i<=5;i++){
		LCD_Data(endgame2[i]);}
	LCD_Data(0x30+subtimes/1000);
	LCD_Data(0x30+subtimes/100%10);
	LCD_Data(0x30+subtimes/10%10);
	LCD_Data(0x30+subtimes%10);
}

void LCD_GameAB(){
	int subtimes=0,i=0;
	sit=0;
	mode = 1;
	LCD_Init(1);
	ans	= rand()%10000;
	inp = 0;
	fid=ans/1000;
	sed=ans/100%10;
	thd=ans/10%10;
	fod=ans%10;
	while(fid == sed || fid == thd || fid == fod || sed == thd || sed == fod || thd == fod){
		ans	= rand()%10000;
		fid=ans/1000;
		sed=ans/100%10;
		thd=ans/10%10;
		fod=ans%10;}
	LCD_CMD(0xC0);
	while(1){
		detect = keyScan();
		if(detect==-1){remember =0;}
		if(remember==0){
			if(table[detect] == 10  &&i!=0){
				i--;
				LCD_Detete1();
				remember = 1;
				inp = inp/10;
				in[i]=0x00;
				sit=0;
				detect=-1;
				}
			if(table[detect] == 12 && i==4 && sit == 0){
				Submit();
				remember = 1;
				sit=1;
				detect=-1;
				}
			if(table[detect] == 11){
				dis_answer();
				remember = 1;
					detect=-1;
			}
			if(table[detect]==0x00);
			else if(detect!=-1){
				if(i==0){
					LCD_Data(table[detect]);
					i++;
					pos=pos+1;
					remember = 1;
					in[0]=table[detect];
					inp=inp*10+(table[detect]-'0');}
				if(i==1 && table[detect] != in[0]){
					i++;
					LCD_Data(table[detect]);
					pos=pos+1;
					remember = 1;
					in[1] = table[detect];
					inp=inp*10+(table[detect]-'0');}
				if(i==2 && table[detect] != in[0] && table[detect] != in[1]){
					i++;
					LCD_Data(table[detect]);
					pos=pos+1;
					remember = 1;
					in[2]= table[detect];
					inp=inp*10+(table[detect]-'0');}
				if(i==3 && table[detect] != in[0] && table[detect]!= in[1] && table[detect] != in[2]){
					i++;
					LCD_Data(table[detect]);
					pos=pos+1;
					remember = 1;
					in[3] = table[detect];
					inp=inp*10+(table[detect]-'0');}
				}
				if(i==4){
					;}
			delay(1);
		}
}}

void Submit(){
	char i,j;
	char inputs[4];
	char answers[4];
	a=0;b=0;
	inpfi=inp/1000;
	inpse=inp/100%10;
	inpth=inp/10%10;
	inpfo=inp%10;
	inputs[0] =inpfi;
	inputs[1] =inpse;
	inputs[2] =inpth;
	inputs[3] =inpfo;
	answers[0]=fid;
	answers[1]=sed;
	answers[2]=thd;
	answers[3]=fod;
	for(i=0;i<=3;i++){
		for(j=0;j<=3;j++){
			if(inputs[i]==answers[j] && i==j){
				a=a+1;}
			if(inputs[i]==answers[j] && i!=j){
				b=b+1;}}}
	subtimes++;
	if(a!=4){
		LCD_CMD(0xC6);
		LCD_Data(0x30+a);
		LCD_Data(0x41);
		LCD_Data(0x30+b);
		LCD_Data(0x42);
		LCD_CMD(pos);}
	if(a==4){
		LCD_Init(2);
}}

void LCD_Detete1(){
	pos=pos-1;
	LCD_CMD(pos);
	LCD_Data(0x5F);
	LCD_CMD(pos);
}
void dis_answer(){
	LCD_CMD(0xCC);
	LCD_Data(0x30+fid);
	LCD_Data(0x30+sed);
	LCD_Data(0x30+thd);
	LCD_Data(0x30+fod);
	LCD_CMD(pos);
}

void LCD_Init(int a){
	char i;
	LCD_CMD(0x38);
	delay(50);
	LCD_CMD(0x0C);
	delay(50);
	LCD_CMD(0x06); 
	delay(50);
	LCD_CMD(0x01);
	delay(50);
	if(a==0){
		startcode();
		beep(2);
	}
	if(a==1){
		incode();beep(2);}
	if(a==2){
		endcode();
		beep(2);
		if(mode==1){
				dis_answer();}}
	if(a==3){
		LCD_CMD(0x0F);
	}
	if(a==4){
	beep(2);}
}
void delay(int x){
	int i,j;
	for(i=0;i<x;i++){
		for(j=0;j<70;j++){
		}}}

void gamestart21(){
	int i,pp=0,ap=0,count=0,k,remember;
	int pcard[5],acard[5];
	char code A[]="CARDS:";
	char code B[]="POINT:";
	LCD_CMD(0X80);
	for(i=0;i<5;i++){
		pcard[i]=rand()%13+1;
		acard[i]=rand()%13+1;
	}
	for(i=0;i<6;i++){
		LCD_Data(A[i]);
	}
	LCD_Data(showcard(pcard[0]));
	LCD_CMD(0xC0);
	for(i=0;i<6;i++){
		LCD_Data(B[i]);
	}
	pp=adjustpoint(pcard,pp,count);
	LCD_Data('0'+(pp/10));
	LCD_Data('0'+(pp%10));
	LCD_CMD(0X8F);
	LCD_Data(showcard(acard[0]));
	do{
		k=keyScan();
		if(k==-1){remember=0;}
		if(remember==0){
				if(k==10){
					break;}
				if(k==9){
						count++;
						LCD_CMD(0X86+count);
						LCD_Data(showcard(pcard[count]));
						pp=adjustpoint(pcard,pp,count);
						LCD_CMD(0xC6);
						LCD_Data(0x10);
						LCD_Data(0x10);
						LCD_CMD(0xC6);
						LCD_Data('0'+(pp/10));
						LCD_Data('0'+(pp%10));
						remember=1;
				}
		}
	}while(count<4 && pp<=21);
	LCD_CMD(0x01);
	LCD_CMD(0x80);
	for(i=0;i<=count;i++){
		LCD_Data(showcard(pcard[i]));
	}
	LCD_CMD(0xC0);
	LCD_Data('0'+(pp/10));
	LCD_Data('0'+(pp%10));
	if(pp>21){
		lose();
	}else{
		int count1=0;
		ap=adjustpoint(acard,ap,count1);
		LCD_CMD(0x8F);
		LCD_Data(showcard(acard[0]));
		LCD_CMD(0xCE);
		LCD_Data('0'+ap/10);
		LCD_Data('0'+ap%10);
		delay(2000);
		while(ap<=21 && count1<4){
			count1++;
			LCD_CMD(0x8F-count1);
			LCD_Data(showcard(acard[count1]));
			ap=adjustpoint(acard,ap,count1);
			LCD_CMD(0xCE);
			LCD_Data('0'+ap/10);
			LCD_Data('0'+ap%10);
			delay(2000);
			if(ap>pp)break;
		}
		beep(2);
		if(ap>21){
			win();
		}
		else if(count==4){
			if(count1!=4){
				win();
			}
			else if(pp>ap){
				win();
			}
			else if(ap>pp){
				lose();
			}else draw();
		}
		else {
			lose();
		}
	}
	while(1);
}

char showcard(int i){
	switch(i){
		case 10:
			return '0';
			break;
		case 11:
			return 'J';
			break;
		case 12:
			return 'Q';
			break;
		case 13:
			return 'K';
			break;
		case 1:
			return 'A';
			break;
		case 0:
			return 'A';
			break;
		default:
			return '0'+i;
	}
}
int adjustpoint(int* card,int p,int count){
	int i=0;
	if(card[count]>9){
		p+=10;
	}else if(card[count]==1){
			p+=11;
	}else{
		p+=card[count];
	}
	if(p>21){
		for(i=0;i<=count;i++){
			if(card[i]==1){
				card[i]=0;
				p-=10;
			}
			if(p<=21){
				break;
			}
		}
	}
	return p;
}

void win(){
	char i;
	char code a[]="YOU";
		char code b[]="WIN!";
		LCD_CMD(0x87);
		for(i=0;i<3;i++){
			LCD_Data(a[i]);
		}
		LCD_CMD(0xC7);
		for(i=0;i<4;i++){
			LCD_Data(b[i]);
		}
}

void lose(){
	int i;
	char code c[]="YOU";
		char code d[]="LOSE!";
		LCD_CMD(0x87);
		for(i=0;i<3;i++){
			LCD_Data(c[i]);
		}
		LCD_CMD(0xC7);
		for(i=0;i<5;i++){
			LCD_Data(d[i]);
		}
}

void draw(){
	int i;
	char code a[]="draw";
	LCD_CMD(0x87);
	for(i=0;i<4;i++){
		LCD_Data(a[i]);
	}
}
int main(){
	int i,type=0,k,remember=0;
	char a[]=">Battleship";
	char b[]=" 21";
	char c[]=" 1A2B";
	LCD_Init(0);
	while(P3_2){
		ranpivot++;
	}
	srand(ranpivot);
	LCD_CMD(0x01);
	LCD_CMD(0x80);
	for(i=0;i<11;i++){
		LCD_Data(a[i]);
	}
	LCD_CMD(0xC0);
	for(i=0;i<3;i++){
		LCD_Data(b[i]);
	}
	while(!P3_2){
			k=keyScan();
			if(k!=9){
				remember=0;
			}
			if(remember==0){
				k=keyScan();
				if(k==9){
					if(type==0){
						LCD_CMD(0x01);
						type=1;
						a[0]=' ';
						b[0]='>';
						LCD_CMD(0x80);
						for(i=0;i<11;i++){
							LCD_Data(a[i]);
						}
						LCD_CMD(0xC0);
						for(i=0;i<3;i++){
							LCD_Data(b[i]);
						}
					}
					else if(type==1){
						LCD_CMD(0x01);
						type=2;
						b[0]=' ';
						c[0]='>';
						LCD_CMD(0x80);
						for(i=0;i<3;i++){
							LCD_Data(b[i]);
						}
						LCD_CMD(0xC0);
						for(i=0;i<5;i++){
							LCD_Data(c[i]);
						}
					}
					else if(type==2){
						LCD_CMD(0x01);
						type=0;
						a[0]='>';
						b[0]=' ';
						LCD_CMD(0x80);
						for(i=0;i<11;i++){
							LCD_Data(a[i]);
						}
						LCD_CMD(0xC0);
						for(i=0;i<3;i++){
							LCD_Data(b[i]);
						}
					}
							remember=1;
			}
		}
	}

	LCD_CMD(0x01);
	if(type==2){
		LCD_GameAB();
	}
	if(type==1){
		gamestart21();
	}
	if(type==0){
		LCD_GameShip();
	}
}

void beep(int a){
	int i;
	for(i=0;i<100;i++){
		P3_4=~P3_4;
		delay(a);
	}
}