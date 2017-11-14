#include "U8glib.h"

U8GLIB_DOGM128 u8g(10, 9, 4);  // SPI Com(Software): CS=10, A0=9, RESET=4

float potencia = 0;
float intensidad = 0;
float voltaje = 0;
int limitemw = 0;
int limite = 0;
float Arrayvseg[79]; //Array para guardar los valores cada 1 segundo
float Arrayvms[79]; //Array para guardar los valores cada 50 ms
int Arrayseg[] = {10, 20, 30, 40, 50, 60, 10, 20};
int Arrayms[] = {2, 4, 6, 8, 10, 12, 14, 16};
int xseg = 0;            //variable que limita final de grafica
int xmseg = 0;
int pixel = 0;          //toma valor grafica
int ts = 0;           //Variable para las posiciones del tiempo
int tms = 0;
int posxseg = 0;      //posicion cursor eje x
int posxms = 0;   //posicion cursor eje x
float maxi = 0;       //variable valor maximo
float mini = 0;       //variable valor minimo
float maxiseg = 0;       //variable valor maximo
float miniseg = 0;       //variable valor minimo
int conts = 0;
int pulsacion = 0;
int pulsacion2 = 0;
int escalaseg = 0;
int pantalla = 0;

const uint8_t rook_bitmap[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x8C, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x8C, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0E, 0x31, 0x8C, 0x63, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x8F, 0x31, 0x8C, 0x63, 0x88, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xC7, 0x11, 0x8C, 0x47, 0x18, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xE3, 0x00, 0x00, 0x06, 0x38, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x30, 0x63, 0x80, 0x00, 0x0E, 0x30, 0xC0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x38, 0x31, 0x80, 0x00, 0x0C, 0x21, 0xC0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x1C, 0x01, 0x80, 0x00, 0x0C, 0x03, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x06, 0x0C, 0x00, 0x80, 0x00, 0x08, 0x03, 0x06, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00,
  0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00,
  0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00,
  0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00,
  0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00,
  0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00,
  0x00, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00,
  0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00,
  0x00, 0x60, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x30, 0x00,
  0x00, 0x70, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x70, 0x00,
  0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00,
  0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00,
  0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00,
  0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00,
  0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80,
  0x0F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x80,
  0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xE0,
  0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xE0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x7F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xE0,
  0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xF0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  };

  const uint8_t logo_bitmap[] PROGMEM = {
  0xFF, 0xE0, 0x00, 0x03, 0xFF, 0x80,                 
  0xFF, 0xE0, 0x00, 0x03, 0xFF, 0xC0,                 
  0xFF, 0xE0, 0x00, 0x03, 0xFF, 0xFC,                 
  0xFF, 0xFE, 0x00, 0x00, 0x7F, 0xFE,                 
  0xFF, 0xFF, 0xE0, 0x00, 0x07, 0xFE,                 
  0xFF, 0xFF, 0xF0, 0x00, 0x07, 0xFE,                 
  0xFF, 0xFF, 0xF0, 0x00, 0x07, 0xFE,                 
  0xFF, 0xE7, 0xE0, 0x07, 0x83, 0xFE,                 
  0xFF, 0xE1, 0xE0, 0x07, 0xC3, 0xFE,                 
  0xFF, 0xC0, 0xC0, 0x07, 0xC3, 0xFE,                 
  0xFF, 0xC0, 0x00, 0x07, 0xC3, 0xFE,                 
  0xFF, 0x80, 0x00, 0x07, 0xFF, 0xFE,                 
  0xFF, 0x8E, 0x00, 0x03, 0xFF, 0xFE,                 
  0xFF, 0xFE, 0x1F, 0x00, 0xFF, 0xFE,                 
  0xFF, 0xFE, 0x1F, 0xE0, 0xFF, 0xFC,                 
  0x7F, 0xFE, 0x1F, 0xE3, 0xFE, 0x30,                 
  0x3F, 0xFC, 0x07, 0xFF, 0xFE, 0x00,                 
  0x03, 0xF0, 0x07, 0xFF, 0xFC, 0x00,                 
  0x03, 0xF0, 0x07, 0xFF, 0xF8, 0x00,                 
  0x03, 0xFF, 0x87, 0xFF, 0x00, 0x00,                 
  0x03, 0xFF, 0x87, 0xE0, 0x00, 0x00,                 
  0x01, 0xFF, 0x87, 0xC0, 0x00, 0x00,                 
  0x00, 0xFF, 0xE7, 0xC0, 0x00, 0x00,                 
  0x00, 0x0F, 0xFF, 0xC0, 0x00, 0x00,                 
  0x00, 0x0F, 0xFF, 0xC0, 0x00, 0x00,                 
  0x00, 0x0F, 0xFF, 0xC0, 0x00, 0x00,                 
  0x00, 0x0F, 0xFF, 0xC0, 0x00, 0x00,                 
  0x00, 0x0F, 0xFF, 0xC0, 0x00, 0x00,                 
  0x00, 0x0F, 0xFF, 0x80, 0x00, 0x00,                 
  };


void setup() {
  
  pantalla_inicio();

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  attachInterrupt(0, pulsador0, CHANGE);
  attachInterrupt(1, pulsador1, CHANGE);

  set_timer1_interrupt(); // lo último antes de ejecutar loop()
}

void pulsador0() {
  //Pulsador zoom grafica
  if(pulsacion == 0) {
    pulsacion = 1;
    if(pantalla == 1){
      pantalla = 2;
    }
    else if(pantalla == 2) {
      pantalla = 1;
    }
  }
  else if(pulsacion == 1) {
    pulsacion = 0;
  }
  delay(10);
}

void pulsador1() {
  //Pulsador cambio pantalla
  if(pulsacion2 == 0) {
    pulsacion2 = 1;
    if(pantalla == 0) {
      pantalla = 1;
    }
    else {
    pantalla = 0;
    }
  }
  else if(pulsacion2 == 1) {
    pulsacion2 = 0;
  }
  delay(10);
}

void set_timer1_interrupt() {
  cli();

  // Timer1 clk/256 --> t_BIT_TCNT1: 1 / (16*10^6 / 256) = 16us
  // OCR1A? --> OCR1A * 16us = 0.2s --> OCR1A = 12500

  // Table 16-4. Waveform Generation Mode Bit Description
  // Mode WGM13 WGM12 WGM11 WGM10 Timer/Counter_Mode_of_Operation  TOP
  // 4    0     1     0     0     CTC                              OCR1A

  // 16.11.1 TCCR1A – Timer/Counter1 Control Register A
  // COM1A1 COM1A0 COM1B1 COM1B0 - - WGM11 WGM10
  // Table 16-1. Compare Output Mode, non-PWM
  // COM1A1 COM1A0 Description
  // 0      0      Normal port operation, OC2A disconnected
  TCCR1A &= (~(_BV(COM1A1)) & ~(_BV(COM1A0)));
  TCCR1A &= (~(_BV(WGM11)) & ~(_BV(WGM10)));

  // 16.11.2 TCCR1B – Timer/Counter1 Control Register B
  // X X - WGM13 WGM12 CS12 CS11 CS10
  TCCR1B &= ~(_BV(WGM13));
  TCCR1B |= _BV(WGM12);

  // Table 20-9. Clock Select Bit Description
  // CS12 CS11 CS10 Description
  // 1    0    0    clk/256
  TCCR1B &= (~(_BV(CS11)) & ~(_BV(CS10)));
  TCCR1B |= _BV(CS12);

  OCR1A = 12500;
  TCNT1 = 0;
  TIMSK1 |= 1 << OCIE1A;

  sei();
}

ISR(TIMER1_COMPA_vect) {
  TCNT1 = 0;
  conts++;
  
  tomar_valores();

  Arrayvms[xmseg] = potencia; //Toma un valor cada 200ms
  xmseg++;

  if(conts == 5) {
    conts = 0;
    Arrayvseg[xseg] = potencia; //Toma un valor cada 1seg
    xseg++;
  }

  //Desplazamiento del valor en ms
  if(xmseg > 79) {
    for(int i=0; i < 79; i++) {
      Arrayvms[i] = Arrayvms[i + 1];
    }
    tms++;
    xmseg = 79;
  }

  //Desplazamiento del valor en seg
  if(xseg > 79) {
    for(int i=0; i < 79; i++) {
      Arrayvseg[i] = Arrayvseg[i + 1];
    }
    ts++;
    xseg = 79;
  }
  
  //Desplazamiento eje x en ms
  if(tms > 9) {
    for(tms = 0; tms < 7; tms++) {
      Arrayms[tms] = Arrayms[tms + 1];
    }
    Arrayms[7] = Arrayms[6] + 2;
    if(Arrayms[7] == 62) {
      Arrayms[7] = 2;
    }
    tms = 0;
  }

  //Desplazamiento eje x en seg
  if(ts > 9) {
    for(ts = 0; ts < 7; ts++) {
      Arrayseg[ts] = Arrayseg[ts + 1];
    }
    Arrayseg[7] = Arrayseg[6] + 10;
    if(Arrayseg[7] == 70) {
      Arrayseg[7] = 10;
    }
    ts = 0;
  }

  max_min();
  
  // picture loop
  u8g.firstPage();
  do {
    draw();
  }
  while ( u8g.nextPage() );
}

void loop() {

}

void draw(void) {
  switch (pantalla) {
    case 0: medidor(); break;
    case 1: graficams(); break;
    case 2: graficaseg(); break;
  }
}

void graficams() {
  int limiteyms = 0;
  int cocientems = 0;
  int multims = 0;
  float coef_convms = 0;

  //Leyendas
  u8g.setFont(u8g_font_4x6r);
  if(maxi < 0.95) {
    u8g.drawStr(10, 5, F("GRAFICA MILIVATIOS/SEGUNDOS"));
  }else {
    u8g.drawStr(17, 5, F("GRAFICA VATIOS/SEGUNDOS"));
  }

  //MAXIMO
  u8g.drawBox(101, 6, 27, 7);
  u8g.setColorIndex(0);
  u8g.drawStr(109, 12, F("MAX"));
  u8g.setColorIndex(1);
  u8g.drawFrame(101, 13, 27, 9);
  u8g.setPrintPos(104, 20);
  if(maxi < 0.95) {
    u8g.print(int(maxi*1000));
  }else {
    u8g.print(maxi);
  }

  //MINIMO
  u8g.drawBox(101, 23, 27, 7);
  u8g.setColorIndex(0);
  u8g.drawStr(109, 29, F("MIN"));
  u8g.setColorIndex(1);
  u8g.drawFrame(101, 30, 27, 9);
  u8g.setPrintPos(104, 37);
  if(maxi < 0.95) {
    u8g.print(int(mini*1000));
  }else {
    u8g.print(mini);
  }

  //ACTUAL
  u8g.drawBox(101, 40, 27, 7);
  u8g.setColorIndex(0);
  u8g.drawStr(103, 46, F("ACTUAL"));
  u8g.setColorIndex(1);
  u8g.drawFrame(101, 47, 27, 9);
  u8g.setPrintPos(104, 54);
  if(maxi < 0.95) {
    u8g.print(int(potencia*1000));
  }else {
  u8g.print(potencia);
  }
  
  //Eje Y

  //Fijar multiplicadores de cada grafica
  if(maxi < 0.95) {
    multims = 1000;
  }else {
    multims = 1;
  }

  //Calculo limites de grafica
  if(maxi < 0.95) {
    
    //Limite grafica milivatios/milisegundos
    if(maxi > 0.72){
      limiteyms = 950;
    }
    else {
      limiteyms = ((maxi+0.01)*multims*5)/4;
    }
    while(limiteyms % 50 != 0) {
      limiteyms++;
    }
    cocientems = limiteyms/5;
  }else {

    //Limite grafica vatios/milisegundos
    limiteyms = ((maxi+0.3)*multims*5)/4;
    while(limiteyms % 5 != 0) {
      limiteyms++;
    }
    cocientems = limiteyms/5;
  }
  
  u8g.drawLine(14, 6, 14, 56);
  u8g.drawLine(13, 6, 15, 6);
  u8g.drawLine(13, 16, 15, 16);
  u8g.drawLine(13, 26, 15, 26);
  u8g.drawLine(13, 36, 15, 36);
  u8g.drawLine(13, 46, 15, 46);
  u8g.setFont(u8g_font_micro);
  u8g.setPrintPos(0, 50);
  u8g.print(cocientems);
  u8g.setPrintPos(0, 40);
  u8g.print(cocientems + cocientems);
  u8g.setPrintPos(0, 30);
  u8g.print(cocientems + 2*cocientems);
  u8g.setPrintPos(0, 20);
  u8g.print(cocientems + 3*cocientems);
  u8g.setPrintPos(0, 10);
  u8g.print(limiteyms);

  //Calculo coeficientes para pasar valores a la grafica
  coef_convms = 25/(limiteyms*0.5);

  //Eje X
  
  //En milisegundos
  u8g.drawLine(14, 56, 94, 56);
  u8g.drawLine(24 - tms, 55, 24 - tms, 57);
  u8g.drawLine(34 - tms, 55, 34 - tms, 57);
  u8g.drawLine(44 - tms, 55, 44 - tms, 57);
  u8g.drawLine(54 - tms, 55, 54 - tms, 57);
  u8g.drawLine(64 - tms, 55, 64 - tms, 57);
  u8g.drawLine(74 - tms, 55, 74 - tms, 57);
  u8g.drawLine(84 - tms, 55, 84 - tms, 57);
  u8g.drawLine(94 - tms, 55, 94 - tms, 57);
  u8g.setFont(u8g_font_micro);
  for(int i=0; i < 8; i++) {
    u8g.setPrintPos(((20 - tms) + posxms), 63);
    u8g.print(Arrayms[i]);
    posxms = posxms + 10;
  }
  for(int i=1; i < xmseg; i++) {
    int a = ((i - 1) + 14);
    int b = 56-Arrayvms[i-1]*multims*coef_convms;
    int c = (i + 14);
    int d = 56-Arrayvms[i]*multims*coef_convms;
    u8g.drawLine(a, b, c, d);
  }
  posxms = 0;
}

void graficaseg() {
  int limiteyseg = 0;
  int cocienteseg = 0;
  int multiseg = 0;
  float coef_convseg = 0;

  //Leyendas
  u8g.setFont(u8g_font_4x6r);
  if(maxiseg < 0.95) {
    u8g.drawStr(10, 5, F("GRAFICA MILIVATIOS/SEGUNDOS"));
  }else {
    u8g.drawStr(17, 5, F("GRAFICA VATIOS/SEGUNDOS"));
  }

  //MAXIMO
  u8g.drawBox(101, 6, 27, 7);
  u8g.setColorIndex(0);
  u8g.drawStr(109, 12, F("MAX"));
  u8g.setColorIndex(1);
  u8g.drawFrame(101, 13, 27, 9);
  u8g.setPrintPos(104, 20);
  if(maxiseg < 0.95) {
    u8g.print(int(maxiseg*1000));
  }else {
    u8g.print(maxiseg);
  }

  //MINIMO
  u8g.drawBox(101, 23, 27, 7);
  u8g.setColorIndex(0);
  u8g.drawStr(109, 29, F("MIN"));
  u8g.setColorIndex(1);
  u8g.drawFrame(101, 30, 27, 9);
  u8g.setPrintPos(104, 37);
  if(maxiseg < 0.95) {
    u8g.print(int(miniseg*1000));
  }else {
    u8g.print(miniseg);
  }

  //ACTUAL
  u8g.drawBox(101, 40, 27, 7);
  u8g.setColorIndex(0);
  u8g.drawStr(103, 46, F("ACTUAL"));
  u8g.setColorIndex(1);
  u8g.drawFrame(101, 47, 27, 9);
  u8g.setPrintPos(104, 54);
  if(maxiseg < 0.95) {
    u8g.print(int(potencia*1000));
  }else {
  u8g.print(potencia);
  }
  
  //Eje Y

  //Fijar multiplicadores de cada grafica
  if(maxiseg < 0.95) {
    multiseg = 1000;
  }else {
    multiseg = 1;
  }

  //Calculo limites de grafica
  if(maxiseg < 0.95) {
    
    //Limite grafica segundos
    if(maxiseg > 0.72){
      limiteyseg = 950;
    }
    else {
    limiteyseg = ((maxiseg+0.01)*multiseg*5)/4;
    }
    while(limiteyseg % 50 != 0) {
      limiteyseg++;
    }
    cocienteseg = limiteyseg/5;
  }else {

    //Limite grafica milisegundos
    limiteyseg = ((maxiseg+0.3)*multiseg*5)/4;
    while(limiteyseg % 5 != 0) {
      limiteyseg++;
    }
    cocienteseg = limiteyseg/5;
  }
  
  u8g.drawLine(14, 6, 14, 56);
  u8g.drawLine(13, 6, 15, 6);
  u8g.drawLine(13, 16, 15, 16);
  u8g.drawLine(13, 26, 15, 26);
  u8g.drawLine(13, 36, 15, 36);
  u8g.drawLine(13, 46, 15, 46);
  u8g.setFont(u8g_font_micro);
  u8g.setPrintPos(0, 50);
  u8g.print(cocienteseg);
  u8g.setPrintPos(0, 40);
  u8g.print(cocienteseg + cocienteseg);
  u8g.setPrintPos(0, 30);
  u8g.print(cocienteseg + 2*cocienteseg);
  u8g.setPrintPos(0, 20);
  u8g.print(cocienteseg + 3*cocienteseg);
  u8g.setPrintPos(0, 10);
  u8g.print(limiteyseg);

  //Calculo coeficientes para pasar valores a la grafica
  coef_convseg = 25/(limiteyseg*0.5);

  //Eje X
  
  //En milisegundos
  u8g.drawLine(14, 56, 94, 56);
  u8g.drawLine(24 - ts, 55, 24 - ts, 57);
  u8g.drawLine(34 - ts, 55, 34 - ts, 57);
  u8g.drawLine(44 - ts, 55, 44 - ts, 57);
  u8g.drawLine(54 - ts, 55, 54 - ts, 57);
  u8g.drawLine(64 - ts, 55, 64 - ts, 57);
  u8g.drawLine(74 - ts, 55, 74 - ts, 57);
  u8g.drawLine(84 - ts, 55, 84 - ts, 57);
  u8g.drawLine(94 - ts, 55, 94 - ts, 57);
  u8g.setFont(u8g_font_micro);
  for(int i=0; i < 8; i++) {
    u8g.setPrintPos(((20 - ts) + posxseg), 63);
    u8g.print(Arrayseg[i]);
    posxseg = posxseg + 10;
  }
  for(int i=2; i < xseg; i++) {
    int a = ((i - 1) + 14);
    int b = 56-Arrayvseg[i-1]*multiseg*coef_convseg;
    int c = (i + 14);
    int d = 56-Arrayvseg[i]*multiseg*coef_convseg;
    u8g.drawLine(a, b, c, d);
  }
  posxseg = 0;
}

//Funcion que dibuja la grafica de aguja analógica
void medidor() {

  int aguja = 0; //Extremo de la aguja en función de la potencia
  float indicador = 0; //Valor digital de la potencia
  int posini = 6; //Posición del primer valor de la gráfica


  //Abscisas de la variable aguja
  int Arrayposx[] = {16, 16, 16, 16, 17, 17, 17, 18, 18, 18, 19, 19, 20, 20, 21,
                     21, 22, 22, 23, 24, 24, 25, 26, 27, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
                     38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
                     58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77,
                     78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97,
                     98, 99, 99, 100, 101, 102, 102, 103, 104, 104, 105, 105, 106, 106, 107, 107, 108,
                     108, 108, 109, 109, 109, 110, 110, 110, 110
                    };
  //Ordenadas de la variable aguja
  int Arrayposy[] = {60, 59, 58, 57, 56 , 55 , 54 , 53, 52, 51, 50, 49, 48, 47, 46,
                     45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 31, 30, 29, 29, 28,
                     27, 27, 26, 26, 25, 25, 24, 24, 23, 23, 23, 22, 22, 22, 21, 21, 21, 21, 20, 20,
                     20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22,
                     23, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 29, 29, 30, 31, 31, 32, 33, 34,
                     35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54,
                     55, 56, 57, 58, 59, 60
                    };
  //Cálculo del limite en milivatios
  if(potencia < 1) {
    if(potencia <= 0.2) {
      limitemw = 200;
    }
    //Recalcular limite
    else if(potencia*1000 >= limitemw-20 || potencia*1000 <= limitemw-180) {
      limitemw = potencia*1000 + 100;
    }
    if(potencia*1000 > 799) {
      limitemw = 999;
    }
    indicador = potencia*1000;
    aguja = ((indicador-(limitemw-200))*0.6);
    //Saturar limite para potencia entre 799 y 999 milivatios
    if(limitemw-200 > 99) {
      posini = 1;
    }
  }

  //Cálculo del límite en vatios
  if(potencia >= 1) {
    if(potencia < 5) {
      limite = 5;
    }
    //Recalcular límite
    else if(potencia >= limite-0.5 || potencia <= limite-4.5) {
      limite = potencia + 2.5;
  }
    indicador = potencia;
    aguja = ((potencia-(limite-5))*24);
  }
  
  //Representación de la gráfica
  u8g.drawBitmapP( 13, 18, 13, 43, rook_bitmap);
  u8g.setFont(u8g_font_4x6r);
  if(potencia >= 1) {
    u8g.drawStr(12, 5, F("MEDIDOR POTENCIA EN VATIOS"));
    u8g.setFont(u8g_font_micro);
    u8g.setPrintPos(6, 62);
    u8g.print(limite-5);
    u8g.setPrintPos(18, 34);
    u8g.print(limite-4);
    u8g.setPrintPos(42, 18);
    u8g.print(limite-3);
    u8g.setPrintPos(79, 18);
    u8g.print(limite-2);
    u8g.setPrintPos(102, 34);
    u8g.print(limite-1);
    u8g.setPrintPos(115, 62);
    u8g.print(limite);
  } else {
    u8g.drawStr(5, 5, F("MEDIDOR POTENCIA EN MILIVATIOS"));
    u8g.setFont(u8g_font_micro);
    u8g.setPrintPos(posini, 62);
    u8g.print(limitemw-200);
    u8g.setPrintPos(18, 34);
    u8g.print(limitemw-160);
    u8g.setPrintPos(42, 18);
    u8g.print(limitemw-120);
    u8g.setPrintPos(79, 18);
    u8g.print(limitemw-80);
    u8g.setPrintPos(102, 34);
    u8g.print(limitemw-40);
    u8g.setPrintPos(115, 62);
    u8g.print(limitemw);
  }
  u8g.drawLine(61, 60, Arrayposx[aguja], Arrayposy[aguja]);
  u8g.drawLine(65, 60, Arrayposx[aguja], Arrayposy[aguja]);
  u8g.setColorIndex(0);
  u8g.drawDisc(63, 66, 26, U8G_DRAW_UPPER_RIGHT);
  u8g.drawDisc(63, 66, 26, U8G_DRAW_UPPER_LEFT);
  u8g.setColorIndex(1);
  u8g.drawCircle(63, 66, 26, U8G_DRAW_UPPER_RIGHT);
  u8g.drawCircle(63, 66, 26, U8G_DRAW_UPPER_LEFT);
  u8g.drawFrame(46, 51, 36, 10);
  u8g.setFont(u8g_font_5x7);
  if(potencia >= 1) {
    u8g.setPrintPos(51, 59);
    u8g.print(indicador);
  }else {
    u8g.setPrintPos(57, 59);
    u8g.print(int(indicador));
  }
}
//Función que recoge valores análogicos del medidor y calcula el consumo
void tomar_valores() {
  const int NUM_MUESTRAS = 100; //Muestras recogidas en cada medición
  int imedida = 0; //Recoge el valor digital de la tensión
  int vmedida = 0; //Recoge el valor digital de la intensidad

  //Cálculo del voltaje
  voltaje = 0;
  for(int i=0; i< NUM_MUESTRAS; i++) {
    vmedida = analogRead(A2);
    voltaje += vmedida/60;
  }
  voltaje /= NUM_MUESTRAS;

  //Cálculo de la intensidad
  intensidad = 0;
  for(int i=0; i< NUM_MUESTRAS; i++) {
    imedida = analogRead(A1);
    intensidad += imedida/170.5;
  }
  intensidad /= NUM_MUESTRAS;

  potencia = intensidad*voltaje;  //Cálculo de la potencia
}

//Función que calcula los valores máximos y mínimos de cada gráfica
void max_min() {
  
    //Calculo valor maximo/minimo
    maxi = Arrayvms[0];
    mini = Arrayvms[0];
  
  for(int i=0; i < xmseg; i++) {
    if(Arrayvms[i] > maxi) {
      maxi = Arrayvms[i];
    }
    if(Arrayvms[i] < mini) {
      mini = Arrayvms[i];
    }
  }
  if(xseg > 0) {
    maxiseg = Arrayvseg[0];
    miniseg = Arrayvseg[0];
  }
  for(int i=0; i < xseg; i++) {
    if(Arrayvseg[i] > maxiseg) {
      maxiseg = Arrayvseg[i];
    }
    if(Arrayvseg[i] < miniseg) {
      miniseg = Arrayvseg[i];
    }
  }
}

void pantalla_inicio() {

  // picture loop
  u8g.firstPage();
  do {
    u8g.drawBitmapP(39, 10, 6, 29, logo_bitmap);
    u8g.setFont(u8g_font_04b_03);
    u8g.drawStr(13, 49, F("Universidad"));
    u8g.drawStr(0, 59, F("del Pais Vasco"));
    u8g.drawStr(66, 49, F("Euskal Herriko"));
    u8g.drawStr(66, 59, F("Unibertsitatea"));
  }
  while ( u8g.nextPage() );
  delay(3000);
}

