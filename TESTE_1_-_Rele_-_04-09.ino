eint motor = 5;
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

 Serial.println("#######################################");
 Serial.println(cont);

 cont= cont + 1;
 }
 
 else {
  Serial.println("ACABOU");
  delay(3000000);
 }
 }

 
