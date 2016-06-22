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
// Fim do bloco de codigo das bibliotecas para o cartao de memoria

#define chaveMecanica 5 // chave mecanica para seleção de tempos/funcoes   
#define ledVermelho 4 // lampada Led cor vermelha, para indicacao de satus/funcoes
#define ledVerde 2 // lampada Led cor verde, para indicacao de status/funcoes
#define analogica1  A1 // entrada analogica/digital 1
#define analogica2  A2 // entrada analogica/digital 2
#define analogica3  A3 // entrada analogica/digital 3
#define analogica4  A4 // entrada analogica/digital 4
#define digital1 3 // entrada digital + interrupcao

// Bloco de definicao de variaveis para temporizacao no sketch
unsigned long timet;
unsigned long previousTime;
unsigned long tempoEntreExecs = 999990;
boolean enterFunction= true;
// fim do bloco de definicoes de temporizacao

int entradaAnalogicaUm; //variavel para recer o valor (integer) da entrada analogica 1
int entradaAnalogicaDois; //variavel para recer o valor (integer) da entrada analogica 2
int entradaAnalogicaTres; //variavel para recer o valor (integer) da entrada analogica 3
int entradaAnalogicaQuatro; //variavel para recer o valor (integer) da entrada analogica 4

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
    }

void loop() {

  entradaAnalogicaQuatro = analogRead(analogica4);
       
  timet = micros();
  if (enterFunction == true){
    previousTime= timet;
    Serial.println(entradaAnalogicaQuatro); // for debugging

    // Start your code below 
    //-----------------------

      
    

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

