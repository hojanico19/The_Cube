// Libraries
#include <Arduino.h>
#include <screen.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// Variables
#define TFT_CS        2
#define TFT_RST       4 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC        5

#define PIN_PULSADOR 13
#define led_control1 14
#define led_control2 27

// Estados
// bool estadoBoton =  false; 
int count_menu = 0;
int max_menus = 6;
int last_menu_state = count_menu;
const int tiempoAntirebote =10;
int cuenta =0;          //Guarda el numero de veces que el boton ha sido presionado
int estadoBoton;
int estadoBotonAnterior;

int n;
static int xd=40;
static int espera=0;
static int step=0;
int x1,x2;
int xp=16;
int mood=6;


Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);


// Function
void testFace(uint16_t color);
void testdrawtext(char *text, uint16_t color, uint16_t size);
void testClock(uint16_t color);
void testGames(uint16_t color);
void testHealth(uint16_t color);
void testRoutines(uint16_t color);
void testGrowUp(uint16_t color); 
boolean antirebote(int pin );



// Setup
void setup(void) {
  Serial.begin(9600);
  Serial.print(F("HOLA EQUIPO METEORITO"));
  pinMode(PIN_PULSADOR, INPUT_PULLUP);

  // Use this initializer (uncomment) if using a 1.3" or 1.54" 240x240 TFT:
  tft.init(240, 320);           // Init ST7789 240x240
  tft.setRotation(1);  //  This code rotates the screen. 0=0 , 1=90, 2=180, 3=270 .

  // Init screen msg
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(100, 30);
  tft.setTextWrap(false);
  testdrawtext("HOLA", ST77XX_ORANGE, 3);
  tft.setCursor(80, 80);
  testdrawtext("EQUIPO", ST77XX_ORANGE, 3);
  tft.setCursor(60, 130);
  testdrawtext("METEORITO", ST77XX_ORANGE, 3);
  delay(2000);


}




// Loop
void loop() {
     // Leemos el estado del GPIO    
  estadoBoton = digitalRead(PIN_PULSADOR);   
  if (estadoBoton  != estadoBotonAnterior) {     //si hay cambio con respeto al estado 
    if (antirebote (PIN_PULSADOR)){                    //checamos  si esta preionado y si lo esta
      cuenta++;                                //aumentamos la cuenta
      Serial.println (cuenta);       
      if (count_menu == max_menus){
        Serial.println("reinicie el contador");
        count_menu=0;}
      else {
        Serial.println("else");
        count_menu++;};
      

    }
  }
  
  if (count_menu==0){tft.fillScreen(ST77XX_BLACK);}
  else if (count_menu==1){testFace(ST77XX_ORANGE);}
  else if (count_menu==2 && count_menu!= last_menu_state){testHealth(ST77XX_CYAN);}
  else if (count_menu==3 && count_menu!= last_menu_state){testGames(ST77XX_GREEN);}
  else if (count_menu==4 && count_menu!= last_menu_state){testRoutines(ST77XX_MAGENTA);}
  else if (count_menu==5 && count_menu!= last_menu_state){testClock(ST77XX_YELLOW);}
  else if (count_menu==6 && count_menu!= last_menu_state){testGrowUp(ST77XX_RED);}

  last_menu_state = count_menu;
  estadoBotonAnterior = estadoBoton;      // guardamos el estado del boton
}



void testFace(uint16_t color) {
  if (espera>0) {
    espera--;
    delay(1);
  }

  else {
    x1=   xd+ (xp>40? (40+2*(xp-40)):xp);
    x2=160+xd+ (xp<40? (-40+(xp*2))  :xp);
    switch (step){
      case 0:
        tft.fillScreen(ST77XX_BLACK);
        tft.drawBitmap(x1, 40, eyes[mood][0][0], 80, 80, color);
          tft.drawBitmap(x2, 40, eyes[mood][0][1], 80, 80, color);
          delay(100); 
        espera=random(250, 1000);
        n=random(0,7);
        if (n==6) {
            step=1;
        } else {
            step=2;
        }
        break;

      case 1:
      tft.fillScreen(ST77XX_BLACK);
       tft.drawBitmap(x1, 40, EYE0, 80, 80, color);
       tft.drawBitmap(x2, 40, EYE0, 80, 80, color);
       espera=1000;
       step=0;
       break;
      case 2:
        n=random(0,10);
        espera=0;
        step=0;
        break;
    }
  }
}

void testGames(uint16_t color) {
  int delay_game = 800;  
  Serial.println("Menu Games");
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(100, 20);
  tft.setTextWrap(false);
  testdrawtext("GAMES", color, 3); 
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(100, 20);
  tft.setTextWrap(false);
  testdrawtext("GAMES", color, 3);

  tft.drawBitmap(60, 60, gato0, 150, 150, color); 
   delay(delay_game);
  tft.drawBitmap(60, 60, gato5, 150, 150, color); 
   delay(delay_game);
  tft.drawBitmap(60, 60, gato6, 150, 150, color);
  delay(delay_game);
  tft.drawBitmap(60, 60, gato7, 150, 150, color); 
  delay(delay_game);
  tft.drawBitmap(60, 60, gato8, 150, 150, color);
  delay(delay_game);
  tft.drawBitmap(60, 60, gato3, 150, 150, color);
  delay(delay_game);
  tft.drawBitmap(60, 60, gato4, 150, 150, color); 
  delay(delay_game);
  tft.drawBitmap(60, 60, gato1, 150, 150, color);
  delay(delay_game);
  tft.drawBitmap(60, 60, gato2, 150, 150, color);
  delay(delay_game);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(100, 20);
  tft.setTextWrap(false);
  testdrawtext("GAMES", color, 3);
  tft.drawBitmap(70, 60, win, 150, 148, color);

}

void testHealth(uint16_t color) {
  Serial.println("Menu Health");
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(100, 20);
  tft.setTextWrap(false);
  testdrawtext("HEALTH", color, 3);
  tft.drawBitmap(80, 60, health, 150, 150, color); 
}

void testRoutines(uint16_t color) {
  Serial.println("Menu Routines");
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(100, 20);
  tft.setTextWrap(false);
  testdrawtext("ROUTINES", color, 3);
  tft.drawBitmap(80, 60, routines, 150, 150, color); 
}

void testClock(uint16_t color) {
  Serial.println("Menu Clock");
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(100, 20);
  tft.setTextWrap(false);
  testdrawtext("CLOCK", color, 3);
  tft.drawBitmap(80, 60, reloj, 150, 150, color); 
}

void testGrowUp(uint16_t color) {
  Serial.println("Menu GrowUp");
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(100, 20);
  tft.setTextWrap(false);
  testdrawtext("GROW UP", color, 3);
  tft.drawBitmap(80, 60, grow_up, 150, 150, color); 
}


void testdrawtext(char *text, uint16_t color, uint16_t size) {
  tft.setTextColor(color);
  tft.setTextSize(size);
  tft.println(text); 
}




// Función antirebote
boolean antirebote  (int pin ) {
  int  contador =0;
  boolean estado;            // guarda el estado del boton 
  boolean estadoAnterior;    // guarda el ultimo estado del boton 

  do {
    estado = digitalRead (pin);
    if (estado != estadoAnterior ){  // comparamos el estado actual 
      contador = 0;                   // reiniciamos el contador 
      estadoAnterior = estado;
    }
    else{
      contador = contador +1;       // aumentamos el contador en 1
    }
    delay (1);
  }
  while (contador < tiempoAntirebote);
  return estado;
}



