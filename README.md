# 🌻 Bem vindo a página do nosso projeto

#### Projeto realizado pelos alunos [Fabrício da Silva Selotto](https://gitlab.com/Selotto) e [Geísa Laiane Cardim](https://gitlab.com/geisa), da Fatec Shunji Nishimura, do curso de Big Data no Agronegócio.

## 📋 Introdução

O projeto consiste na criação de um protótipo voltado para a piscicultura, focando na área da alimentação. Trata-se de um alimentador automático para peixes, de baixo custo e uso doméstico, utlizando tecnologia IOT.

## 📌 Protótipo
### 🔨 Estrutural

Para a parte física do alimentador, utilizamos canos pvc de 4 polegadas, um motor 127V de prato de microondas e um motor 127V de ventilador, sendo um para o controle de vazão da ração e o outro para o lanço da mesma. Colocamos o cano PVC em pé onde a ração fica armazenada, e perfuramos a tampa na parte de baixo, onde fixamos o motor com um fio de aço transpassado, que ao girar, deixa cair a ração para o motor de ventilador, onde é lançada para o tanque de água.

![cano](https://github.com/geisalaiane/automacao-piscicultura/blob/master/img/Cano.png?raw=true)
![cano](https://github.com/geisalaiane/automacao-piscicultura/blob/master/img/Cano.png?raw=true)
![cano](https://github.com/geisalaiane/automacao-piscicultura/blob/master/img/Cano.png?raw=true)
![cano](https://github.com/geisalaiane/automacao-piscicultura/blob/master/img/Cano.png?raw=true)

### 💻 Tecnologia 

Para o controle de ambos os motores, utilizamos um módulo relé 5v, junto a protoboard com uma fonte. Para acionamento utilizamos uma NodeMCU-V3, conectada à rede WIFI, se comunicando via protocólo MQTT, sendo tanto 'publish' quanto 'subscribe', utilizando o broker público 'broker.emqx.io'. Para visualização do histórico de ativação utilizamos o ThingSpeak. 

### 🔧 Teste

Para calibração do tempo de despejo de ração, fomos colocando determinado período de tempo, testando 5 vezes, e fazendo a média de pesos da ração dispensada. Conseguimos chegar em um tempo padrão, onde obtivemos 1KG de ração despejada.

### 📄 Código

#### Implementação do Horário
```
#include <WiFiUdp.h>
String horario;
void loop() {
  timeClient.update();
  horario = timeClient.getFormattedTime();
  Serial.println(horario);
  if(horario == "01:44:00")
  {
    Serial.println("condição funciona");
  }
  delay(1000);
}
```
___
#### Temporizador do Lanço 
```int motor = 5;
int ventilador = 4;
int cont = 0;
void setup() {
 pinMode(motor, OUTPUT);
 pinMode(ventilador, OUTPUT);
 Serial.begin(115200);
}
void loop() {
 if (cont <3){
 digitalWrite(motor, HIGH);
 digitalWrite(ventilador, HIGH);
 delay(1000);
 Serial.println(" de novo ");
 Serial.println(cont);
 Serial.println("Primeiro tempo de espera");
 digitalWrite(motor, HIGH);
 digitalWrite(ventilador, HIGH);
 Serial.println("(Desligado)");
 delay(20000);
 Serial.println("Primeiro lanço de ração");
 digitalWrite(motor, LOW);
 digitalWrite(ventilador, LOW);
 Serial.println("(Ligado)");
 delay(60000);
 Serial.println("-------------------");
 Serial.println("Segundo tempo de espera");
 digitalWrite(motor, HIGH);
 digitalWrite(ventilador, HIGH);
 Serial.println("(Desligado)");
 delay(20000);
 Serial.println("Segundo lanço de ração");
 digitalWrite(motor, LOW);
 digitalWrite(ventilador, LOW);
 Serial.println("(Ligado)");
 delay(60000);
 Serial.println("-------------------");
 Serial.println("Terceiro tempo de espera");
 digitalWrite(motor, HIGH);
 digitalWrite(ventilador, HIGH);
 Serial.println("(Desligado)");
 delay(20000);
 Serial.println("Terceiro lanço de ração");
 digitalWrite(motor, LOW);
 digitalWrite(ventilador, LOW);
 Serial.println("(Ligado)");
 delay(60000);
 digitalWrite(motor, HIGH);
 digitalWrite(ventilador, HIGH);
 Serial.println("-------------------");
 delay(60000);
 Serial.println(cont);
 cont= cont + 1;
 }
```
___
#### Implementação do MQTT
___
