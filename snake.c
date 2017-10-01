#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#define MAXSTR 16

struct point
{
	unsigned int x;
	unsigned int y;
};

struct snake
{
	unsigned int length;
	struct point head;
	struct point body[255];
} s0 ,st;

struct DataTag
{
	unsigned int maxSpeed;
	unsigned int rate;
	unsigned int record0;
	unsigned int record1;
};

const char heart[2]={3,0};

int isbody(struct snake *ps,struct point *pp,unsigned char e);
void prodfood(struct point *pf ,struct snake *ps);
void bodymove(struct snake *ps0 ,struct snake *pst);
void ReadData(struct DataTag *data);
void WriteData(struct DataTag *data);
void CreateData();
int load(struct snake *sn ,struct point *fud ,int *drt ,int *mod ,unsigned int *spd);
void save(struct snake *sn ,struct point *fud ,int *drt ,int *mod ,unsigned int *spd);
void encode(char fromfile[], char tofile[]);
int decode(char fromfile[], char tofile[]);

int main(){
	struct point food;
	struct point grp;
	struct DataTag dat0={0,0,0,0};
	int KeyStt ,direct ,direct0 ,model ,menu;
	unsigned int i ,speed ;
	unsigned int x ,y;
	char buffer[450]="";
start:	
	ReadData(&dat0);
	system("color 1f");
	printf("Menu:\n0=New Game.\n1=Load Game.\nPlease input(0 or 1):");
	scanf("%d",&menu);
	if(menu>1){
		printf("Wrong Input!\nPress Any Key to restart.\n");
		while((KeyStt=kbhit())==0);
		goto start;
	}
	else if(menu==1){
		printf("Loading...\n");
		if(load(&s0,&food,&direct,&model,&speed)==0){
			system("CLS");
			goto start;
		}
		st=s0;
		direct0=direct;
//		speed=dat0.maxSpeed-speed+1;
	}
	else {
		s0.length=1;
		s0.head.x=7;
		s0.head.y=7;
		s0.body[0].x=7;
		s0.body[0].y=8;
		st=s0;
		direct0=direct='w';
		system("CLS");
		printf("Choose model:\n0=Boundless model\n1=Limitary model\nInput(0 or 1):");
		scanf("%d",&model);
		if(model>1){
			printf("Wrong Input!\nPress Any Key to restart.\n");
			while((KeyStt=kbhit())==0);
			goto start;
		}
		system("CLS");
		printf("Input Speed(1~%d):",dat0.maxSpeed);
		scanf("%d",&speed);
		if(speed<1 || speed>dat0.maxSpeed){
			printf("Wrong Input!\nPress Any Key to restart.\n");
			while((KeyStt=kbhit())==0);
			goto start;
		}
		speed=dat0.maxSpeed-speed+1;
		prodfood(&food,&s0);
	}
	system("color 8a");
	while(1){
		while((KeyStt=kbhit())==0){
			int j=0;
			system("CLS");
			j+=sprintf(buffer+j,"Use \'W\',\'S\',\'A\',\'D\' Key to Change the Direction.\nPress \'ESC\' to options model.\n");
			j+=sprintf(buffer+j,"Score:%d\n",s0.length);
			j+=sprintf(buffer+j,"/----------------\\\n");
			for(y=0;y<16;y++){
				grp.y=y;
				j+=sprintf(buffer+j,"|");
				if(y!=s0.head.y &&(! isbody(&s0,&grp,0))&&(y!=food.y)){
					j+=sprintf(buffer+j,"                |\n");
					continue;
				}
				for(x=0;x<16;x++){
					grp.x=x;
					if(x==s0.head.x && y==s0.head.y)
						j+=sprintf(buffer+j,"*");
					else if(x==food.x && y==food.y)
						j+=sprintf(buffer+j,heart);  //shape heart
					else if(isbody(&s0,&grp,2))
						j+=sprintf(buffer+j,"+");
					else 
						j+=sprintf(buffer+j," ");
				}
				j+=sprintf(buffer+j,"|");
				j+=sprintf(buffer+j,"\n");
			}
			j+=sprintf(buffer+j,"\\----------------/");
			bodymove(&s0 ,&st);
			switch(direct){
				case 'd':
					s0.head.x++;
					break;
				case 'a':
					s0.head.x--;
					break;
				case 'w':
					s0.head.y--;
					break;
				case 's':
					s0.head.y++;
					break;
			}
			if(model==0){
				s0.head.x=s0.head.x %16;
				s0.head.y=s0.head.y %16;
			}
			st=s0;
			i=speed;
			puts(buffer);
			while((--i)&&((KeyStt=kbhit())==0)){
				j=100000*dat0.rate;
				while(--j);
			}
			if(s0.head.x==food.x && s0.head.y==food.y){
				prodfood(&food,&s0);
				s0.length++;
			}
			if((isbody(&s0,&s0.head,2))||(s0.length==255)||(s0.head.x>15)||(s0.head.y>15)){
				system("color 4c");
				printf("\nYour final score is %d.\n",s0.length);
				ReadData(&dat0);
				if(model==0){
					if(dat0.record0<s0.length){
						dat0.record0=s0.length;
						WriteData(&dat0);
					}
					printf("In boundless model,the record is %d.",dat0.record0);
				}
				else {
					if(dat0.record1<s0.length){
						dat0.record1=s0.length;
						WriteData(&dat0);
					}
					printf("In limitary model,the record is %d.",dat0.record1);
				}
				
				printf("\nPress Enter to replay.\nPress any other key to exit.");
				direct=getch();
				if(direct=='\r'){
					system("CLS");
					goto start;
				}
				else 
					return 0;
			}
		}
		direct=getch();
		switch(direct){
			case 'd':  //Right
//				s0.head.x++;
				if(direct0=='a')
					direct=direct0;
				break;
			case 'a':  //Left
//				s0.head.x--;
				if(direct0=='d')
					direct=direct0;
				break;
			case 'w':  //Up
//				s0.head.y--;
				if(direct0=='s')
					direct=direct0;
				break;
			case 's':  //Down
//				s0.head.y++;
				if(direct0=='w')
					direct=direct0;
				break;
			case 27 :  //Esc
				system("CLS");
				printf("Options:\n0=Return Game\n1=Save Game\nOther Number=Exit\nInput:");
				scanf("%d",&direct);
				if(direct==0){
					direct=direct0;
					break;
				}
				else if(direct==1){
					printf("Saving...\n");
					save(&s0,&food,&direct0,&model,&speed);
				}
				else {
					return 0;
				}
			default :  //Inertance
				direct=direct0;
				break;
		}
		direct0=direct;
	}
	
	return 0;
}

//输入：指向蛇（结构体）的指针，指向坐标的指针，标志数（0=y坐标|1=x坐标|2=xy坐标一起）
//输出：该坐标是否与蛇躯体某点坐标相同，是=1|否=0
int isbody(struct snake *ps,struct point *pp,unsigned char e){
	int bdFlag=0;
	unsigned int i;
	unsigned int coord;

	for(i=0;i<ps->length;i++){
		if(e==0){
			coord=ps->body[i].y;
		}
		else if(e==1){
			coord=ps->body[i].x;
			if(pp->x==coord){
				bdFlag=1;
				break;
			}
		}
		else {
			coord=ps->body[i].x;
			if(pp->x==coord)
				coord=ps->body[i].y;
			else 
				continue;
		}
		if(pp->y==coord){
			bdFlag=1;
			break;
		}
	}
	return bdFlag;
}


//输入：指向食物点的指针，指向蛇的指针；无输出
//用途：随机产生一个食物点
void prodfood(struct point *pf ,struct snake *ps){
	unsigned int i=0;
	do{
		srand(time(NULL));
		pf->x=(rand()+i)%16;
		i++;
		srand(clock());
		pf->y=(rand()+i)%16;
	}
	while((pf->x)==(ps->head.x)||(pf->y)==(ps->head.y)||(isbody(&s0,pf,2)));
}

//输入：指向蛇（结构体）的指针，指向dummy蛇（结构体）的指针；无输出
//用途：使身体跟上头
void bodymove(struct snake *ps0 ,struct snake *pst){
	unsigned int i;
	ps0->body[0].x=pst->head.x;
	ps0->body[0].y=pst->head.y;
	for(i=1;i<(ps0->length);i++){
		ps0->body[i].x=pst->body[i-1].x;
		ps0->body[i].y=pst->body[i-1].y;
	}
}

//输入：指向读取的数据类的指针；无输出
//用途：读取数据文件
void ReadData(struct DataTag *data){
	int ch ;
	char tag[4]={0,0,0,0};
	char name[MAXSTR];
	unsigned int num ,i;
	char source[]="snake.dat";
	char temp[]="snake.dat.tmp";
	FILE *fp;
	while(decode(source,temp)==0){
		printf("Initialize...\n");
		CreateData();  //无数据文件时，创建一个新的
	}
	fp=fopen(temp,"rb");
	if(fp==NULL){
		unsigned int i=400000000;
		printf("Error!\n");
		while(--i);
		exit(0);
	}
	do{
		for(i=0;i<MAXSTR;i++){
			name[i]=0;
		}
		num=0;
		i=0;
		while((ch=fgetc(fp))!='=' && ch!=EOF){
			name[i++]=ch;
		}
		while((ch=fgetc(fp))!=';' && isdigit(ch) && ch!=EOF){
			num=10*num+ch-48;
		}
		if(strncmp(name,"MaxSpeed",8)==0){
			data->maxSpeed=num;
			tag[0]=1;
		}
		if(strncmp(name,"Rate",4)==0){
			data->rate=num;
			tag[1]=1;
		}
		if(strncmp(name,"Record0",7)==0){
			data->record0=num;
			tag[2]=1;
		}
		if(strncmp(name,"Record1",7)==0){
			data->record1=num;
			tag[3]=1;
		}
		if(ch==EOF){
			unsigned int i=400000000;
			printf("Data Corruption, Reinitialize...\n");
			printf("Please restart soon.\n");
			CreateData();
			while(--i);
			exit(0);
		}
	}
	while((tag[0]==0 || tag[1]==0 || tag[2]==0));
	fclose(fp);
	remove(temp);
}

//无输入；无输出
//用途：创建/覆盖一个新的数据文件
void CreateData(){
	char temp[]="snake.dat.tmp";
	char gen[]="snake.dat";
	FILE *fp=fopen(temp,"wb");
	if(fp==NULL){
		unsigned int i=400000000;
		printf("Initialization Error!\n");
		while(--i);
		exit(0);
	}
	fprintf(fp,"MaxSpeed=5;");
	fprintf(fp,"Rate=900;");
	fprintf(fp,"Record0=1;");
	fprintf(fp,"Record1=1;");
//	fputc(EOF,fp);
	fclose(fp);
	encode(temp,gen);
	remove(temp);
}

//输入：指向读取的数据类的指针；无输出
//用途：写入数据
void WriteData(struct DataTag *data){
	char temp[]="snake.dat.tmp";
	char gen[]="snake.dat";
	FILE *fp=fopen(temp,"wb");
	if(fp==NULL){
		unsigned int i=400000000;
		printf("Error!\n");
		while(--i);
		exit(0);
	}
	fprintf(fp,"MaxSpeed=%d;",data->maxSpeed);
	fprintf(fp,"Rate=%d;",data->rate);
	fprintf(fp,"Record0=%d;",data->record0);
	fprintf(fp,"Record1=%d;",data->record1);
//	fputc(EOF,fp);
	fclose(fp);
	encode(temp,gen);
	remove(temp);
}


//输入：指向蛇（结构体）的指针，指向食物点的指针，指向方向的指针，指向模式的指针，指向速度的指针
//输出：整数，0=无文件|1=加载成功
//用途：读取储存文件
int load(struct snake *sn ,struct point *fud ,int *drt ,int *mod ,unsigned int *spd){
	int ch ;
	char tag[10]={0,0,0,0,0,0,0,0,0,0};
	char name[MAXSTR];
	char source[]="snake.sav";
	char temp[]="snake.sav.tmp";
	unsigned int num ,i ,xflag ,yflag ,blength;
	FILE *fp;
	if(decode(source,temp)==0){
		unsigned int i=400000000;
		remove(temp);
		printf("Load failure.No saved game.\n");
		while(--i);
		return 0;
	}
	fp=fopen(temp,"rb");
	if(fp==NULL){
		unsigned int i=400000000;
		printf("Error!\n");
		while(--i);
		exit(0);
	}
	blength=255;
	xflag=yflag=0;
	do{
		for(i=0;i<MAXSTR;i++){
			name[i]=0;
		}
		num=0;
		i=0;
		while((ch=fgetc(fp))!='=' && ch!=EOF){
			name[i++]=ch;
		}
		while((ch=fgetc(fp))!=';' && isdigit(ch) && ch!=EOF){
			num=10*num+ch-'0';
		}
		if(strncmp(name,"Length",6)==0){
			sn->length=num;
			blength=num;
			tag[0]=1;
		}
		if(strncmp(name,"Speed",5)==0){
			*spd=num;
			tag[1]=1;
		}
		if(strncmp(name,"Model",5)==0){
			*mod=num;
			tag[2]=1;
		}
		if(strncmp(name,"Direct",6)==0){
			*drt=num;
			tag[3]=1;
		}
		if(strncmp(name,"FoodX",5)==0){
			fud->x=num;
			tag[4]=1;
		}
		if(strncmp(name,"FoodY",5)==0){
			fud->y=num;
			tag[5]=1;
		}
		if(strncmp(name,"HeadX",5)==0){
			sn->head.x=num;
			tag[6]=1;
		}
		if(strncmp(name,"HeadY",5)==0){
			sn->head.y=num;
			tag[7]=1;
		}
		for(i=0;i<blength;i++){
			char bstr[8]={'B','o','d','y','0','0','0','X'};
			bstr[4]=i/100+48;
			bstr[5]=i%100/10+48;
			bstr[6]=i%10+48;
//			printf("loop x ,now is %s\n",bstr); //测试时留下的
			if(strncmp(name,bstr,8)==0){
				sn->body[i].x=num;
				xflag=xflag+1;
			}
			if(xflag==blength)
				tag[8]=1;
		}
		for(i=0;i<blength;i++){
			char bstr[8]={'B','o','d','y','0','0','0','Y'};
			bstr[4]=i/100+48;
			bstr[5]=i%100/10+48;
			bstr[6]=i%10+48;
//			printf("loop y ,now is %s\n",bstr);  //测试时留下的
			if(strncmp(name,bstr,8)==0){
				sn->body[i].y=num;
				yflag=yflag+1;
			}
			if(yflag==blength)
				tag[9]=1;
		}
		if(ch==EOF){
			unsigned int i=400000000;
			printf("Data Corruption!\n");
			printf("Please restart soon.\n");
			fclose(fp);
			remove("snake.sav");
			while(--i);
			exit(0);
		}
	}
	while(tag[0]==0||tag[1]==0||tag[2]==0||tag[3]==0||tag[4]==0||tag[5]==0||tag[6]==0||tag[7]==0||tag[8]==0||tag[9]==0);
	fclose(fp);
	remove(temp);
	return 1;
}

//输入：指向蛇（结构体）的指针，指向食物点的指针，指向方向的指针，指向模式的指针，指向速度的指针；无输出
//用途：保存储存文件
void save(struct snake *sn ,struct point *fud ,int *drt ,int *mod ,unsigned int *spd){
	unsigned int i;
	char temp[]="snake.sav.tmp";
	char gen[]="snake.sav";
	FILE *fp=fopen(temp,"wb");
	if(fp==NULL){
		i=400000000;
		printf("Error!\n");
		while(--i);
		exit(0);
	}
	fprintf(fp,"Length=%d;",sn->length);
	fprintf(fp,"Speed=%d;",*spd);
	fprintf(fp,"Model=%d;",*mod);
	fprintf(fp,"Direct=%d;",*drt);
	fprintf(fp,"FoodX=%d;",fud->x);
	fprintf(fp,"FoodY=%d;",fud->y);
	fprintf(fp,"HeadX=%d;",sn->head.x);
	fprintf(fp,"HeadY=%d;",sn->head.y);
	for(i=0;i<sn->length;i++){
		fprintf(fp,"Body%d%d%dX=%d;",i/100,i%100/10,i%10,sn->body[i].x);
		fprintf(fp,"Body%d%d%dY=%d;",i/100,i%100/10,i%10,sn->body[i].y);
	}
//	fputc(EOF,fp);
	fclose(fp);
	encode(temp,gen);
	remove(temp);
}

//输入：导入文件名，导出文件名；无输出
//用途：改变编码（强行装逼（雾））
void encode(char fromfile[], char tofile[]){
	int ch;
	FILE *fp=fopen(fromfile,"rb");
	FILE *fp0=fopen(tofile,"wb");
	if(fp==NULL){
		unsigned int i=400000000;
		fclose(fp0);
		printf("Error!\n");
		while(--i);
		exit(0);
	}
	if(fp0==NULL){
		unsigned int i=400000000;
		fclose(fp);
		printf("Error!\n");
		while(--i);
		exit(0);
	}
	while(1){
		ch=fgetc(fp);
		if(ch==EOF)
		break;
		ch=ch|0x80; //英文的ASCII码首位都是0，中文GBK码两字节首位都是1
		fputc(ch,fp0);
	}
	fclose(fp);
	fclose(fp0);
}

//输入：导入文件名，导出文件名
//输出：导入成功输出1，导入失败输出0
//用途：解码
int decode(char fromfile[], char tofile[]){
	int ch;
	FILE *fp=fopen(fromfile,"rb");
	FILE *fp0=fopen(tofile,"wb");
	if(fp==NULL){
		fclose(fp0);
		return 0;
	}
	if(fp0==NULL){
		unsigned int i=400000000;
		fclose(fp);
		printf("Error!\n");
		while(--i);
		exit(0);
	}
	while(1){
		ch=fgetc(fp);
		if(ch==EOF)
			break;
		ch=ch&0x7f; //英文的ASCII码首位都是0，中文GBK码两字节首位都是1
		fputc(ch,fp0);
	}
	fclose(fp);
	fclose(fp0);
	
	return 1;
}