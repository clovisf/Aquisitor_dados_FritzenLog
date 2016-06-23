/*
 
- Registrador de dados (datalogger) baseado em Arduino.
- Desenvolvido por Clovis Fritzen (clovisf @ gmail.com).
- Baseado em codigo aberto (exemplos) disponivel na
IDE do Arduino 1.6.9 

- Utiliza um cartão de memória tipo "SD" para
armazenar dados obtidos a partir de entradas
analógicas e digitais do microcontrolador
- Revisao r00 iniciada em 21/06/2016
- http://www.FritzenLab.com.br

*/

// Bibliotecas necesarias para o cartao de memoria
#include <SPI.h>
#include <SD.h>
#include "DHT.h"  
   
 // Fim do bloco de codigo das bibliotecas para o cartao de memoria

#define chaveMecanica 5 // chave mecanica para seleção de tempos/funcoes   
#define ledVermelho 4 // lampada Led cor vermelha, para indicacao de satus/funcoes
#define ledVerde 2 // lampada Led cor verde, para indicacao de status/funcoes
#define analogica1  A1 // entrada analogica/digital 1
#define analogica2  A2 // entrada analogica/digital 2
#define analogica3  A3 // entrada analogica/digital 3
#define analogica4  A4 // entrada analogica/digital 4
#define digital1 3 // entrada digital + interrupcao
#define DHTTYPE DHT11  // DHT 11 

// Bloco de definicao de variaveis para temporizacao no sketch
unsigned long timet;
unsigned long previousTime;
unsigned long tempoEntreExecs = 9999990;
boolean enterFunction= true;
// fim do bloco de definicoes de temporizacao

float entradaAnalogicaUm; //variavel para recer o valor (integer) da entrada analogica 1
float entradaAnalogicaDois; //variavel para recer o valor (integer) da entrada analogica 2
int entradaAnalogicaTres; //variavel para recer o valor (integer) da entrada analogica 3
int entradaAnalogicaQuatro; //variavel para recer o valor (integer) da entrada analogica 4

DHT dht(digital1, DHTTYPE);
boolean botaoPressionado = false; 

// Variaveis necessarias para o funcionamento do cartao SD
Sd2Card card;
SdVolume volume;
SdFile root;
const int chipSelect = 9; // pino utilizado pelo SD card como "Chip Select" 
// fim do bloco de variaveis para o funcionamento do cartao SD

void setup() {
  
  pinMode(chaveMecanica, INPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  // funcao para detectar a presenca/ausencia de um cartao SD card
  // liga o LED verde caso o cartao esteja presente
  // e desliga o LED verde caso o cartao SD nao esteja presente
  if (!SD.begin(chipSelect)) {
    ledIndicadorErro();
        
  } else {
    digitalWrite(ledVerde, HIGH);
  }
  // fim da funcao de deteccao do cartao SD

  Serial.begin(9600);
  dht.begin();

  File dataFile = SD.open("testeum.csv", FILE_WRITE);
  if (dataFile) {  
   dataFile.println("Tempo(s),Umidade(%),Temp_DHT11(C),Temp_Autocore,Temp_GBK");  
   dataFile.close();    
  }  
  
    }

void loop() {
       
  timet = micros();

  if (digitalRead(chaveMecanica) == HIGH) {
    botaoPressionado = true;
  }
  if ((enterFunction == true) && (botaoPressionado == true)){
    previousTime= timet;
    
    // Start your code below 
    //-----------------------
    digitalWrite(ledVermelho, HIGH);
    Serial.print("Tempo(s) = ");
    Serial.println(micros()/1000000);
    
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)  
    float h = dht.readHumidity();  
    // Read temperature as Celsius (the default)  
    float t = dht.readTemperature();  

    // Check if any reads failed and exit early (to try again).  
    if (isnan(h) || isnan(t)) {  
      Serial.println("Failed to read from DHT sensor!");  
    return;  
    }  

    Serial.print("Humidity: ");  
    Serial.print(h);  
    Serial.print(" %\t");  
    Serial.print("Temperature: ");  
    Serial.print(t);  
    Serial.println(" *C ");
  
    entradaAnalogicaUm = analogRead(analogica1);
    entradaAnalogicaDois = analogRead(analogica2);
    Serial.print("NTC Autocore = ");
    Serial.println(entradaAnalogicaUm,0);
    Serial.print("NTC GBK = ");
    Serial.println(entradaAnalogicaDois,0);

    File dataFile = SD.open("testeum.csv", FILE_WRITE);
    if (dataFile) { 
            
      dataFile.print(micros()/1000000);
      dataFile.print(",");
      dataFile.print(h);
      dataFile.print(",");
      dataFile.print(t);
      dataFile.print(",");
      dataFile.print(entradaAnalogicaUm);
      dataFile.print(",");
      dataFile.println(entradaAnalogicaDois);
      dataFile.close();    
    }  
    digitalWrite(ledVermelho, LOW);
     //-----------------------
    // End of your code
  }
  
  // The DELAY time is adjusted in the constant below >> 
  if (timet - previousTime < tempoEntreExecs){ // 1 million microsencods= 1 second delay
    /* I have actually used 0.999990 seconds, in a trial to compensate the time that
       this IF function takes to be executed. this is really a point that
       need improvement in my code */   
    enterFunction= false;
  } 
  else {
    enterFunction= true;
  }


}

void ledIndicadorErro(void){
  digitalWrite(ledVerde, LOW); // desliga o LED verde caso não haja erro
  return;
}

