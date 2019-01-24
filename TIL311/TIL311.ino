//By liposlt
//TI TIL311测试程序

#define HC595_DS  10
#define HC595_RCK 9
#define HC595_SCK 8

#define HC595_DS_RESET    digitalWrite(HC595_DS, LOW)
#define HC595_DS_SET      digitalWrite(HC595_DS, HIGH)

#define HC595_ST_CP_RESET digitalWrite(HC595_RCK, LOW)    //RCK
#define HC595_ST_CP_SET   digitalWrite(HC595_RCK, HIGH)

#define HC595_SH_CP_RESET digitalWrite(HC595_SCK, LOW)    //SCK
#define HC595_SH_CP_SET   digitalWrite(HC595_SCK, HIGH)

/*-------------------------data format-------------------------------
signal-digit LED    3       2       1       0
Left Decimal    LP  
Right Decimal   RP
Blanking input  BI    BI == HIGH the display is blank BI == LOW display as determined by the data in the latches.

data0 == D1   C1    B1    A1    D0    C0    B0    A0
data1 == D3   C3    B3    A3    D2    C2    B2    A2
data2 == RP3  LP3   RP2   LP2   RP1   LP1   RP0   LP0
data3 == BI3  BI2   BI1   BI0   X     X     X     X
-------------------------------------------------------------------*/
void setup() {
  // put your setup code here, to run once:
  pinMode(HC595_DS, OUTPUT);
  pinMode(HC595_RCK, OUTPUT);
  pinMode(HC595_SCK, OUTPUT);
  HC595SendData_four(255, 255, 0, 0);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  HC595SendData_four(0xcd, 0xab, 0xff, 0x00);
}

void HC595SendData_four(uint8_t data0, uint8_t data1, uint8_t data2, uint8_t data3)
{
  uint8_t i = 0;
  for (i = 0; i < 8; i++)
  {
    if (data0 & 0x80) {HC595_DS_SET;}
    else              {HC595_DS_RESET;}
    data0 <<= 1;
    HC595_SH_CP_SET;  HC595_SH_CP_RESET;
  } 
  for (i = 0; i < 8; i++) 
  {   
    if (data1 & 0x80) {HC595_DS_SET;}
    else              {HC595_DS_RESET;}
    data1 <<= 1;
    HC595_SH_CP_SET;  HC595_SH_CP_RESET;
  }
  for (i = 0; i < 8; i++)
  {
    if (data2 & 0x80) {HC595_DS_SET;}
    else              {HC595_DS_RESET;}
    data2 <<= 1;
    HC595_SH_CP_SET;  HC595_SH_CP_RESET;
  }
  for (i = 0; i < 8; i++)
  {
    if (data3 & 0x80) {HC595_DS_SET;}
    else              {HC595_DS_RESET;}
    data3 <<= 1;
    HC595_SH_CP_SET;  HC595_SH_CP_RESET;
  }
  HC595_ST_CP_SET;
  HC595_ST_CP_RESET;
}
