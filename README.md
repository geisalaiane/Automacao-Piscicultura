# 🌻 Bem vindo a página do nosso projeto

#### Projeto realizado pelos alunos [Fabrício da Silva Selotto](https://gitlab.com/Selotto) e [Geísa Laiane Cardim](https://gitlab.com/geisa), da Fatec Shunji Nishimura, do curso de Big Data no Agronegócio.

## 📋 Introdução

O projeto consiste na criação de um protótipo voltado para a piscicultura, focando na área da alimentação. Trata-se de um alimentador automático para peixes, de baixo custo e uso doméstico, utlizando tecnologia IOT.

## 📌 Protótipo
### 🔨 Estrutural

Para a parte física do alimentador, utilizamos canos pvc de 4 polegadas, um motor 127V de prato de microondas e um motor 127V de ventilador, sendo um para o controle de vazão da ração e o outro para o lanço da mesma. Colocamos o cano PVC em pé onde a ração fica armazenada, e perfuramos a tampa na parte de baixo, onde fixamos o motor com um fio de aço transpassado, que ao girar, deixa cair a ração para o motor de ventilador, onde é lançada para o tanque de água.

![montagem](https://github.com/geisalaiane/automacao-piscicultura/blob/master/img/montagem.png?raw=true)
![cano](https://github.com/geisalaiane/automacao-piscicultura/blob/master/img/Cano.png?raw=true)
![joelho](https://github.com/geisalaiane/automacao-piscicultura/blob/master/img/joelho-pvc.png?raw=true)
![tampa](https://github.com/geisalaiane/automacao-piscicultura/blob/master/img/Tampa.png?raw=true)
![motor](https://github.com/geisalaiane/automacao-piscicultura/blob/master/img/motor%20ventilador.png?raw=true)
![motor2](https://github.com/geisalaiane/automacao-piscicultura/blob/master/img/motor-microonda.png?raw=true)




### 💻 Tecnologia 

Para o controle de ambos os motores, utilizamos um módulo relé 5v, junto a protoboard com uma fonte. Para acionamento utilizamos uma NodeMCU-V3, conectada à rede WIFI, se comunicando via protocólo MQTT, sendo tanto 'publish' quanto 'subscribe', utilizando o broker público 'broker.emqx.io'. Para visualização do histórico de ativação utilizamos o ThingSpeak. 
![rele](https://github.com/geisalaiane/automacao-piscicultura/blob/master/img/rele%20shield.png?raw=true)
![esp](https://github.com/geisalaiane/automacao-piscicultura/blob/master/img/esp8266-nodemcuv3%20-%20lolin.png?raw=true)
![fonte](https://github.com/geisalaiane/automacao-piscicultura/blob/master/img/fonteprotoboard.png?raw=true)
![esp_proto_rele](https://github.com/geisalaiane/automacao-piscicultura/blob/master/img/rele_proto.png?raw=true)
![fonte_proto](https://github.com/geisalaiane/automacao-piscicultura/blob/master/img/Placa-Fonte.png?raw=true)
![montagem](https://github.com/geisalaiane/automacao-piscicultura/blob/master/img/sistema.png?raw=true)

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
#### Implementação do MQTT
~~~~
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char *ssid = "Gilza";                 //WiFi name
const char *password = "gilmar91";          //WiFi password
const char *mqtt_broker = "broker.emqx.io"; //broker público
const int mqtt_port = 1883;                 //porta padrão de comunicação
WiFiClient espClient;
PubSubClient client(espClient);
void setup()
{   WiFi.begin(ssid, password); //conectando no wifi
    while (WiFi.status() != WL_CONNECTED)
    {   delay(500);
        Serial.println("Conectando no Wifi ...");
    }
    Serial.println("Conectado!");
    //connecting to a mqtt broker
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    while (!client.connected())
    {   Serial.println("Conectando no broker mqtt ...");
        Serial.println("");
        if (client.connect("esp8266-client"))
        {   Serial.println("Conectado no broker mqtt!");
        }
        else
        {   Serial.print("Falha de conexão ao mqtt");
            Serial.print(client.state());
            delay(2000);
        }
    }
    // publish and subscribe
    client.publish("IOTFGFatec/status", "Sistema Conectado");
    client.subscribe("IOTFGFatec/ativacao");
}
void callback(char *topic, byte *payload, unsigned int length)
{   payload[length] = '\0'; //armazena msg recebida em uma sring
    String strMSG = String((char *)payload);

#ifdef DEBUG
    Serial.print("Mensagem chegou do tópico: ");
    Serial.println(topic);
    Serial.print("Mensagem:");
    Serial.print(strMSG);
    Serial.println();
    Serial.println("-----------------------");
#endif
    Serial.print("STR:");
    Serial.println(strMSG);
}
~~~~
___
#### Temporizador do Lanço 
```
int motor = 5;
int ventilador = 4;
int cont = 0;
void setup() {
 pinMode(motor, OUTPUT);
 pinMode(ventilador, OUTPUT);
 Serial.begin(115200);
}
void ligarsistema()
{
    Serial.println("Aparelho Ligado!");
    client.publish("IOTFGFatec/status", "Aparelho Ligado!");
    digitalWrite(rele, HIGH);
    digitalWrite(rele2, HIGH);
    delay(1000);
    digitalWrite(rele, HIGH);
    digitalWrite(rele2, HIGH);
    Serial.println("(Desligado)");
    delay(2000);
    timeClient.update();
    horario = timeClient.getFormattedTime();
    Serial.println(horario);
    Serial.println("Primeiro lanço de ração");
    digitalWrite(rele, LOW);
    digitalWrite(rele2, LOW);
    delay(6000);
    digitalWrite(rele, HIGH);
    digitalWrite(rele2, HIGH);
    delay(2000);
    timeClient.update();
    horario = timeClient.getFormattedTime();
    Serial.println(horario);
    Serial.println("Segundo lanço de ração");
    digitalWrite(rele, LOW);
    digitalWrite(rele2, LOW);
    delay(6000);
    digitalWrite(rele, HIGH);
    digitalWrite(rele2, HIGH);
    delay(2000);
    timeClient.update();
    horario = timeClient.getFormattedTime();
    Serial.println(horario);
    Serial.println("Terceiro lanço de ração");
    digitalWrite(rele, LOW);
    digitalWrite(rele2, LOW);
    delay(6000);
    digitalWrite(rele, HIGH);
    digitalWrite(rele2, HIGH);
    delay(6000);

}
```
___
#### Função para lanço automático
```
void timerligar()
{
    timeClient.update();
    horario = timeClient.getFormattedTime();
    client.publish("IOTFGFatec/status", "Modo Automático Ligado");
    Serial.println(horario);
    Serial.println("Modo Automático Ligado");
    if (horario == "08:00:00")
    {        ligarsistema();    }
    else if (horario == "15:00:00")
    {        ligarsistema();    }
    delay(1000);
}
```
