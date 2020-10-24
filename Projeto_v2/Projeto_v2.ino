#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "ThingSpeak.h"

// Update these with values suitable for your network.

const char *ssid = "IOT";
const char *password = "iot1234iot";
const char *mqtt_server = "mqtt.eclipse.org";

// Thinkspeak to upload data
unsigned long myChannelNumber = 1172259;
const char *myWriteAPIKey = "ASBZB5RPBRJVW33G";

const int rele2 = D1;
const int rele = D0;

const int ledazul = D8;
const int ledvermelho = D7;

String horario;
String STRmsg;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "a.st1.ntp.br", -3 * 3600, 60000);

WiFiClient espClient;
PubSubClient client(espClient);

void ligarsistema()
{
    ThingSpeak.writeField(myChannelNumber, 1, 1, myWriteAPIKey);

    Serial.println("Aparelho Ligado!");
    
    digitalWrite(rele, HIGH);
    digitalWrite(rele2, HIGH);
    delay(1000);

    Serial.println("Primeiro tempo de espera");
    digitalWrite(rele, HIGH);
    digitalWrite(rele2, HIGH);
    Serial.println("(Desligado)");
    delay(2000);

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
    Serial.println("");
    delay(1000);
}

void timerligar()
{
    Serial.println("Modo Automático Ligado");
    timeClient.update();
    horario = timeClient.getFormattedTime();
    Serial.println(horario);

    if (horario == "22:21:00")
    {
        ligarsistema();
    }
    else if (horario == "22:23:00")
    {
        ligarsistema();
    }
    delay(1000);
}

void setup_wifi()
{

    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length)
{
    payload[length] = '\0'; //armazena msg recebida em uma sring
    STRmsg = String((char *)payload);
}

void reconnect()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (client.connect(clientId.c_str()))
        {
            Serial.println("Conectado ao Broker");
            // Once connected, publish an announcement...
            client.publish("IOTFGFatec/status", "ON");
            // ... and resubscribe
            client.subscribe("IOTFGFatec/ativacao");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void setup()
{

    Serial.begin(115200);
    pinMode(rele, OUTPUT);
    pinMode(rele2, OUTPUT);
    pinMode(ledazul, OUTPUT);
    pinMode(ledvermelho, OUTPUT);

    digitalWrite(rele, HIGH);
    digitalWrite(rele2, HIGH);

    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
    timeClient.begin(); //horario
    ThingSpeak.begin(espClient);
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }

    client.loop();

    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println(STRmsg);
    Serial.println("");

    if (STRmsg == "AUT1")
    {
        digitalWrite(ledazul, HIGH);
        digitalWrite(ledvermelho, LOW);
        timerligar();
    }
    else if (STRmsg == "ATIVAR1")
    {
        ligarsistema();
        STRmsg = "M1";
        delay(1000);
    }
    else if (STRmsg == "M1")
    {
        digitalWrite(ledvermelho, HIGH);
        digitalWrite(ledazul, LOW);

        Serial.println("Modo Manual Ativado!");
        Serial.println("");
        Serial.println("Aparelho Desligado!");
        delay(1000);
    }
}
