#include <LiquidCrystal.h>

LiquidCrystal lcd_1(12,11,5,4,3,2);

//LiquidCrystal lcd_1(8,9,4,5,6,7);

int pin = 13;

int tiempoespera;
int hora;
int minutos;
int segundos;
bool bandera;
String desactivar;
bool banderaDesactivar;
int contador;
int x;
int contSegundo;
int boton;
byte smiley[8] = {
  B10001,
  B01010,
  B01110,
  B00100,
  B10001,
  B01110,
  B00000,
};

void setup()
{				
  Serial.begin(9600);
  lcd_1.begin(16,2);
  bandera = 0;
  segundos = 0;
  contador = 0;
  tiempoespera=5;
  
  banderaDesactivar=true;
  
  pinMode(pin,OUTPUT);
  digitalWrite(pin,LOW);
 
  lcd_1.createChar(8, smiley);
  
  Serial.println("Ingrese la Hora y los segundos con un espacio de diferencia ");
   x=0;
contSegundo=0;

  
  

  
}


void loop()
{
  
 // Serial.println(segundos);
  if (Serial.available() > 0 && !bandera) {
    Serial.println("HORA CONFIGURADA");
    hora = Serial.parseInt();
    while (Serial.read() != ' ');
    minutos = Serial.parseInt();
    bandera = 1;
    
  }
  
  	lcd_1.setCursor(1, 0);
	lcd_1.print(hora/10); 
	lcd_1.print(hora%10); 
	lcd_1.print(":");
	lcd_1.print(minutos/10); 
	lcd_1.print(minutos%10);
  boton=analogRead(A0);
 // Serial.println(boton);
  
  if(boton >= 99&&127 >= boton)
  {
  tiempoespera++;
   Serial.println("Intervalo Incrementado en 1 minuto");
  }
  
   if(boton >= 255&&280 >= boton)
  {
   tiempoespera--;
     Serial.println("Intervalo Disminuido en 1 minuto");
  }
  
   if(boton >= 399&&435 >= boton)
  {
   banderaDesactivar=!banderaDesactivar;
   if(banderaDesactivar)
   {
   Serial.println("Aromatizador activado");
   }
    else
    {
    Serial.println("Aromatizador desactivado");
    }
     
  }
  
   if(boton >= 0&&60 >= boton)

  {
      contador = 0;
      digitalWrite(pin,HIGH);
      contSegundo=0;
      lcd_1.setCursor(8, 0);
  	  lcd_1.write((byte)8);
     Serial.println("4");
  }
  
  
  if (Serial.available() > 0 && bandera) {
    desactivar = Serial.readString();
     {
      if (bandera) {
        if (desactivar == "desactivar") {
          banderaDesactivar = false;
          Serial.println("AROMATIZADOR DESACTIVADO");
          
        } else if (desactivar == "activar") {
          banderaDesactivar = true;
          Serial.println("AROMATIZADOR ACTIVADO");
        } else {
          tiempoespera = desactivar.toInt();
          Serial.print("Intervalo configurado: ");
          Serial.println(tiempoespera);
        }
      }
      
     }}
 	
  if (contador == tiempoespera && banderaDesactivar) {
      contador = 0;
      digitalWrite(pin,HIGH);
      contSegundo=0;
      lcd_1.setCursor(8, 0);
  	  lcd_1.write((byte)8);
      
  	}

  	if((millis()/1000)>=x)
    {
    	segundos++;
      	contSegundo++;
      	x++;
    }
  
  
    if(contSegundo==1)
    {
 	
  		digitalWrite(pin,LOW);
    	lcd_1.setCursor(8,0);
    	lcd_1.print(" ");
  
    }
  
  
  if (segundos == 60){
    segundos=0;
    minutos++;
    contador++;

  }
  
  if (minutos == 60) {
    minutos = 0;
    segundos = 0;
    hora++;
  }
  if (hora == 24) {
    minutos = 0;
    segundos = 0;
    hora = 0;
  }
  //Serial.println(x);
//Serial.println(segundos);

}