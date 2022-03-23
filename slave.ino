
/* 
ARDUINO ESCRAVO
----------------------------------------------------------------------------            

                                 I2C NETWORK
 Arduino UNO 1 | PINO A4 SDA <---|-------------> SDA PINO A4 | Arduino UNO 2
                 PINO A5 SCL <---|--|----------> SCL PINO A5 
                                 |  |
                                 Pull up 5V - 4K7
*/   

#include <Wire.h>                                                               //Biblioteca I2C necessária para fazer a comunicação

#define ENDERECO_DESTE_ARDUINO_NA_REDE 11                                       //Define o endereço deste escravo na rede

int dado_recebido = 0;                                                          //Variável que armazena o valor do dados que será enviado
int dado_a_ser_enviado = 0;                                                     //Define o endereço do primeiro arduino escravo

void setup()  //Inicia os ajustes iniciais
{
    Wire.begin(ENDERECO_DESTE_ARDUINO_NA_REDE);                                 //Inicia a comunicação I2C
    Serial.begin(9600);                                                         //Ajusta o baud rate da comunicação com o monitor serial
    Serial.println("--> DEBUG DE SINAIS RECEBIDOS PELO ESCRAVO");               //Envia para o monitor um label titulo constante
    delay(1000);                                                                //Aguarda 1 segundo para iniciar o laço loop
    Wire.onRequest(requestEvents);                                              //Inicia a interrupção para responder pergunta do mestre
    Wire.onReceive(receiveEvents);                                              //Inicia a interrupção para receber um dado novo do mestre
}

void loop() {   //Inicia o Loop infinito
 
}

//FUNÇÕES DE INTERRUPÇÃO LIGADOS A COMUNICAÇÃO I2C

void requestEvents()                                                            //Interrupção para responder a uma pergunta do mestre
{
 Serial.println(F("--> FOI RECEBIDA UMA REQUISIÇÃO DE DADOS DO MESTE"));        //Envia para o monitor um label titulo constante
 Serial.print(F("Valor enviado pelo mestre : "));                               //Envia para o monitor um label titulo constante
 Serial.println(dado_a_ser_enviado);                                            //Envia para o monitor serial o dados que será enviado ao mestre
 Wire.write(dado_a_ser_enviado);                                                //Envia a informação contida na variável "dado_a_ser_enviado"
}

void receiveEvents(int numero_de_bytes_recebido)                                //Interrupção para receber um dado enviado pelo mestre
{
 Serial.println(F("--> FOI RECEBIDO UM NOVO DADO ENVIADO PELO MESTRE"));        //Envia para o monitor um label titulo constante
 dado_recebido = Wire.read();                                                   //Faz a leitura do valor enviado pelo mestre
 Serial.print(numero_de_bytes_recebido);                                        //Envia para o monitor a quantidade de dados recebidos           
 Serial.println(F(" byte(s) Recebido"));                                        //Envia para o monitor um label titulo constante
 Serial.print(F("Valor Recebido : "));                                          //Envia para o monitor um label titulo constante
 Serial.println(dado_recebido);                                                 //Envia para o monitor o dado recebido do mestre
 dado_a_ser_enviado = (dado_recebido+1);                                        //Atualiza a variável "dado recebido" para ser enviado novamente durante a interrupção "requestEvents"
}
