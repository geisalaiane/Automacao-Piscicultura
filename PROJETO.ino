#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

//========== SISTEMA FÍSICO ============
const int led = D3;
const int rele2 = D7;
const int rele = D8;
int cont = 0;

//=============== MQTT =================
const char *ssid = "Gilza";                 //WiFi name
const char *password = "gilmar91";          //WiFi password
const char *mqtt_broker = "broker.emqx.io"; //broker público
const int mqtt_port = 1883;                 //porta padrão de comunicação
String horario;

String minha;

int ativacao = 0;

WiFiClient espClient;
PubSubClient client(espClient);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "a.st1.ntp.br", -3 * 3600, 60000);

void setup()
{

    //========== SISTEMA FÍSICO ============
    Serial.begin(115200);
    pinMode(led, OUTPUT);
    pinMode(rele, OUTPUT);
    pinMode(rele2, OUTPUT);

    //=============== MQTT =================

    WiFi.begin(ssid, password); //conectando no wifi
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Conectando no Wifi ...");
    }
    Serial.println("Conectado!");
    //connecting to a mqtt broker
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    while (!client.connected())
    {
        Serial.println("Conectando no broker mqtt ...");
        Serial.println("");
        if (client.connect("esp8266-client"))
        {
            Serial.println("Conectado no broker mqtt!");
        }
        else
        {
            Serial.print("Falha de conexão ao mqtt");
            Serial.print(client.state());
            delay(2000);
        }
    }
    // publish and subscribe
    client.publish("IOTFGFatec/status", "Sistema Conectado");
    client.subscribe("IOTFGFatec/ativacao");

    timeClient.begin(); //horario
}

void callback(char *topic, byte *payload, unsigned int length)
{

    payload[length] = '\0'; //armazena msg recebida em uma sring
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
    minha = strMSG;


        
/*
    if (strMSG == "AUT1")
    {
        timerligar();
    }

    if (strMSG == "ATIVAR1")
    {
        client.publish("IOTFGFatec/status", "Aparelho Ligou");
        Serial.println("Aparelho Ligado!");
        ligarsistema();
        Serial.println("Acabou");
        delay(1000);
    }

    if (strMSG == "M1")
    {
        Serial.println("Modo Manual Ativado!");
        Serial.println("");
        client.publish("IOTFGFatec/status", "Aparelho Desligado");
        Serial.println("Aparelho Desligado!");
        delay(1000);
    }
*/
}

void ligarsistema()
{
    Serial.println("Aparelho Ligado!");
    client.publish("IOTFGFatec/status", "Aparelho Ligado");

    digitalWrite(rele, HIGH);
    digitalWrite(rele2, HIGH);
    delay(1000);

    Serial.println(" de novo ");
    Serial.println("Primeiro tempo de espera");
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
    Serial.println("(Ligado)");
    delay(6000);

    Serial.println("-------------------");

    Serial.println("Segundo tempo de espera");
    digitalWrite(rele, HIGH);
    digitalWrite(rele2, HIGH);
    Serial.println("(Desligado)");
    delay(2000);

    timeClient.update();
    horario = timeClient.getFormattedTime();
    Serial.println(horario);
    Serial.println("Segundo lanço de ração");
    digitalWrite(rele, LOW);
    digitalWrite(rele2, LOW);
    Serial.println("(Ligado)");
    delay(6000);

    Serial.println("-------------------");

    Serial.println("Terceiro tempo de espera");
    digitalWrite(rele, HIGH);
    digitalWrite(rele2, HIGH);
    Serial.println("(Desligado)");
    delay(2000);

    timeClient.update();
    horario = timeClient.getFormattedTime();
    Serial.println(horario);
    Serial.println("Terceiro lanço de ração");
    digitalWrite(rele, LOW);
    digitalWrite(rele2, LOW);
    Serial.println("(Ligado)");
    delay(6000);

    digitalWrite(rele, HIGH);
    digitalWrite(rele2, HIGH);
    Serial.println("-------------------");

    delay(6000);

    Serial.println("###################################");
}

void timerligar()
{
    timeClient.update();
    horario = timeClient.getFormattedTime();
    client.publish("IOTFGFatec/status", "Modo Automático Ligado");
    Serial.println(horario);
    Serial.println("Modo Automático Ligado");

    if (horario == "15:30:00")
    {
        ligarsistema();
    }
    else if (horario == "15:38:00")
    {
        ligarsistema();
    }

    delay(1000);
}

void loop()
{
    client.loop();

    if (minha == "AUT1")
    {
        timerligar();
    }

    while (minha == "ATIVAR1")
    {
        client.publish("IOTFGFatec/status", "Aparelho Ligou");
        Serial.println("Aparelho Ligado!");
        ligarsistema();
        Serial.println("Acabou");
        delay(1000);
        minha=" ";
    }       

    while (minha == "M1")
    {
        Serial.println("Modo Manual Ativado!");
        Serial.println("");
        client.publish("IOTFGFatec/status", "Aparelho Desligado");
        Serial.println("Aparelho Desligado!");
        delay(1000);
        minha=" ";
       
    }


    
}
