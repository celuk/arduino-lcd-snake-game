#include <LCD5110_Basic.h>

LCD5110 glcd(8, 9, 10, 11, 12);

extern uint8_t SmallFont[];

void NOKIA_Out(int y, int x, char *car){
  glcd.print(car, 6*x-6, 8*y-8);
  }
  
void HAL_Delay(int dd){
  delay(dd);
  }

int yilanx=7;
int yilany=3;
int yemx=4;
int yemy=2;
int yonx=0;
int yony=0;
int yilanoldumu=0;
int puan=0;
char str[11];
int oyunbittimi=0;
char inputKey = '0';

int tailCols[84];
int tailRows[84];

int zorluk = 600;

int sure = 0;

void yem(void)
{
  
  int x=rand()%14+1;
  while(x==yilanx)
  {
    x=rand()%14+1;
  }
  int y=rand()%6+1;
  while(y==yilany)
  {
    y=rand()%6+1;
  }
  yemx=x;
  yemy=y;
}


void yilanhareket(void)
{
  HAL_Delay(zorluk);
  if( (yilanx==1&&yonx==-1) || (yilanx==14&&yonx==+1) || (yilany==1&&yony==-1) || (yilany==6&&yony==1))
  {
    yilanoldumu=1;
  }
  else
  {
    yilanx=yilanx+yonx;
    yilany=yilany+yony;
    if(yilanx==yemx&&yilany==yemy)
    {
      puan++;
      yem();
    }
  }
}

/*
void printSquare(int xNOKIA, int yNOKIA){
    if(xNOKIA>0) xNOKIA-=1;
      if(yNOKIA>0) yNOKIA-=1;
        yNOKIA*=6;
        NOKIA_Goto_xy(xNOKIA,yNOKIA);
    
    for(int k=0;k<5;k++)
    {
      NOKIA_Write_Data(0xff);
    }
    NOKIA_Write_Data(0xff);
    NOKIA_Clear();
}
*/

void NOKIA_Clear(){
  glcd.clrScr();
  }

int oncekicol = 0;
int oncekirow = 0;

void GLCD (void)
{ 
  if(yilanoldumu==1)
  {
    int i;
    if(oyunbittimi!=1)
    {
    for(i=0;i<3;i++)
    {
      //NOKIA_Clear();
      NOKIA_Out(oncekicol, oncekirow," ");
      for(int j=0;j<=puan;j++)
      {
        NOKIA_Out(tailCols[j], tailRows[j]," ");
      }
      
      HAL_Delay(200);

      NOKIA_Out(oncekicol, oncekirow,"O");
      for(int j=0;j<=puan;j++)
      {
        NOKIA_Out(tailCols[j], tailRows[j],"O");
      }

      HAL_Delay(200);
    
    }
    }
    oyunbittimi=1;
    
    NOKIA_Clear();
    
    NOKIA_Out(2,2,"Oyun Bitti!");
    sprintf(str, "Puaniniz:%d", puan);
    NOKIA_Out(3,2,str);

    NOKIA_Out(5,1,"Oynanilan sure");
    sprintf(str, "%d s", sure);
    NOKIA_Out(6,1,str);
  }
  else
  {

    
    
    NOKIA_Out(1, 1, " ");

    tailCols[0]=yilany;
    tailRows[0]=yilanx;

    


for(int i=1;i<=puan;i++)
    {
      if((tailCols[0]==tailCols[i] && tailRows[0]==tailRows[i]))
            {
                yilanoldumu = 1;
                if(yilanoldumu==1)
                {
                  int k;
                  if(oyunbittimi!=1)
                  {
                  for(k=0;k<3;k++)
                  {
                    NOKIA_Out(oncekicol, oncekirow," ");
                    for(int j=0;j<=puan;j++)
                    {
                      NOKIA_Out(tailCols[j], tailRows[j]," ");
                    }
                    
                    HAL_Delay(200);

                    NOKIA_Out(oncekicol, oncekirow,"O");
                    for(int j=0;j<=puan+1;j++)
                    {
                      NOKIA_Out(tailCols[j], tailRows[j],"O");
                    }
                
                    HAL_Delay(200);
                  
                  }
                  }
                  oyunbittimi=1;
                  
                  NOKIA_Clear();
                  
                  NOKIA_Out(2,2,"Oyun Bitti!");
                  sprintf(str, "Puaniniz:%d", puan);
                  NOKIA_Out(3,2,str);

                  NOKIA_Out(5,1,"Oynanilan sure");
                  sprintf(str, "%d s", sure);
                  NOKIA_Out(6,1,str);
                }
                
            }
    }

    if(!oyunbittimi){

    NOKIA_Out(oncekicol, oncekirow," ");

    oncekicol = tailCols[puan];
    oncekirow = tailRows[puan];
    
    for(int i=puan;i>0;i--)
    {
        tailCols[i]=tailCols[i-1];
        tailRows[i]=tailRows[i-1];
    }
    
    for(int i=0;i<=puan;i++)
    {
      NOKIA_Out(tailCols[i], tailRows[i],"O");
    }
    
    NOKIA_Out(yemy,yemx,"*");
    }

    
    
  }
}

const int yukari = 18;
const int sag = 19;
const int sol = 20;
const int asagi = 21;

char readKeypad(){
  if(digitalRead(22)){
    return '2';
    }
  else if(digitalRead(23)){
    return '6';
    }
  else if(digitalRead(24)){
    return '4';
    }
  else if(digitalRead(25)){
    return '8';
    }
  else return '0';
  }

void setup(){

  //pinMode(yukari, INPUT);
  //pinMode(sag, INPUT);
  //pinMode(sol, INPUT);
  //pinMode(asagi, INPUT);

attachInterrupt(digitalPinToInterrupt(yukari), int1, RISING);
attachInterrupt(digitalPinToInterrupt(sag), int2, RISING);
attachInterrupt(digitalPinToInterrupt(sol), int3, RISING);
attachInterrupt(digitalPinToInterrupt(asagi), int4, RISING);
  
  glcd.InitLCD();
  glcd.setFont(SmallFont);

  NOKIA_Out(1,3,"Snake Game");
  NOKIA_Out(2,1,"Seyyid Hikmet");
  NOKIA_Out(3,1,"Celik");
  NOKIA_Out(4,1,"181201047");
  NOKIA_Out(5,1,"Murat Senturk");
  NOKIA_Out(6,1,"181201029");
  HAL_Delay(1000);
  NOKIA_Clear();

  while(inputKey != '2' && inputKey != '4' && inputKey != '6'){
    NOKIA_Out(1,1,"Zorluk Secimi");
    NOKIA_Out(2,2,"2 - Kolay");
    NOKIA_Out(4,2,"4 - Orta");
    NOKIA_Out(6,2,"6 - Zor");
    
    }
    if(inputKey == '2'){
      zorluk = 600;
      }
    else if(inputKey == '4'){
      zorluk = 300;
      }
    else if(inputKey == '6'){
      zorluk = 100;
      }
    
    NOKIA_Clear();

  yem();
  }

void int1(){
  
  if(!(yonx==0 && yony==1)){
    inputKey = '2';
      yonx=0;
      yony=-1;
  }
  }
  
void int2(){
  
  if(!(yonx==-1 && yony==0)){
    inputKey = '6';
      yonx=1;
      yony=0;
  }
  }
  
void int3(){
  
  if(!(yonx==1 && yony==0)){
    inputKey = '4';
      yonx=-1;
      yony=0;
  }
  }

void int4(){
  
  if(!(yonx==0 && yony==-1)){
    inputKey = '8';
      yonx=0;
      yony=1;
  }
  }

void loop(){
  glcd.setFont(SmallFont);
  //prints("", 6, 14);
  //glcd.print("H", 76, 42);

if(!oyunbittimi){
    GLCD();
    inputKey= readKeypad();
    
    if(inputKey=='4')
    {
      yonx=-1;
      yony=0;
    }
    else if(inputKey=='2')
    {
      yonx=0;
      yony=-1;
    }
    else if(inputKey=='6')
    {
      yonx=1;
      yony=0;
    }
    else if(inputKey=='8')
    {
      yonx=0;
      yony=1;
    }
    yilanhareket();
}
  
  }

  
