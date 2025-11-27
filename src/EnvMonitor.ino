#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define LUZ A0
#define CHUVA A1
#define MQ135 A2
#define POT A3
#define TRIG 3
#define ECHO 4
#define LED_VERDE 12
#define LED_AMARELO 11
#define LED_VERMELHO 10
#define BUZZER 13
#define BOTAO 8

bool sistemaLigado = true;
bool ultimoEstadoBotao = HIGH;
unsigned long ultimoDebounce = 0;
unsigned long delayDebounce = 200;
bool standby = false;

void setup() {
  Serial.begin(9600);
  pinMode(LUZ, INPUT);
  pinMode(CHUVA, INPUT);
  pinMode(MQ135, INPUT);
  pinMode(POT, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BOTAO, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  dht.begin();
}

long medirDistancia() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long duracao = pulseIn(ECHO, HIGH, 20000);
  if (duracao == 0) return 999;
  long distancia = duracao * 0.034 / 2;
  return distancia;
}

void loop() {
  int leituraBotao = digitalRead(BOTAO);
  if (leituraBotao != ultimoEstadoBotao) {
    ultimoDebounce = millis();
  }
  if ((millis() - ultimoDebounce) > delayDebounce) {
    if (leituraBotao == LOW) {
      sistemaLigado = !sistemaLigado;
      standby = false;
      tone(BUZZER, 1500, 150);
      delay(200);
    }
  }
  ultimoEstadoBotao = leituraBotao;

  if (!sistemaLigado) {
    lcd.clear();
    lcd.setCursor(0,0); lcd.print(" Sistema OFF ");
    lcd.setCursor(0,1); lcd.print("Toggle p/ ON ");
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, LOW);
    noTone(BUZZER);
    return;
  }

  long distancia = medirDistancia();
  if (distancia > 150 || distancia == 999) {
    if (!standby) {
      standby = true;
      tone(BUZZER, 1500, 200);
    }
  } else {
    standby = false;
  }

  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();
  int luzValor = analogRead(LUZ);
  String luzEstado = (luzValor < 500 ? "Escuro" : "Claro");
  int chuvaValor = analogRead(CHUVA);
  int chuvaPercent = map(chuvaValor, 0, 1023, 100, 0);
  int gasValor = analogRead(MQ135);
  int gasPercent = map(gasValor, 0, 1023, 0, 100);
  int pot = analogRead(POT);
  int modoLCD = 0;
  if (pot < 384) modoLCD = 0;
  else if (pot < 717) modoLCD = 1;
  else modoLCD = 2;

  lcd.clear();
  if (standby) {
    lcd.setCursor(0,0); lcd.print(" Standby ativo ");
    lcd.setCursor(0,1); lcd.print(" Sem movimento ");
  } else {
    switch (modoLCD) {
      case 0:
        lcd.setCursor(0,0); lcd.print("Temp:"); lcd.print(temperatura); lcd.print("C");
        lcd.setCursor(0,1); lcd.print("Umid:"); lcd.print(umidade); lcd.print("% Gas:"); lcd.print(gasPercent); lcd.print("%");
        break;
      case 1:
        lcd.setCursor(0,0); lcd.print("Luz: "); lcd.print(luzEstado);
        lcd.setCursor(0,1); lcd.print("Chuva:"); lcd.print(chuvaPercent); lcd.print("% Gas:"); lcd.print(gasPercent); lcd.print("%");
        break;
      case 2:
        lcd.setCursor(0,0); lcd.print("Gas:"); lcd.print(gasPercent); lcd.print("%");
        lcd.setCursor(0,1); lcd.print("Chuva:"); lcd.print(chuvaPercent); lcd.print("%");
        break;
    }
  }

  if (!standby) {
    if (gasPercent > 70 || chuvaPercent > 50) {
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_AMARELO, LOW);
      digitalWrite(LED_VERMELHO, HIGH);
      tone(BUZZER, 1000);
    } else if (temperatura > 30 || umidade < 30) {
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_AMARELO, HIGH);
      digitalWrite(LED_VERMELHO, LOW);
      noTone(BUZZER);
    } else {
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_AMARELO, LOW);
      digitalWrite(LED_VERMELHO, LOW);
      noTone(BUZZER);
    }
  } else {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, LOW);
    noTone(BUZZER);
  }

  Serial.println("----- SENSORES -----");
  Serial.print("Temp: "); Serial.println(temperatura);
  Serial.print("Umidade: "); Serial.println(umidade);
  Serial.print("Luz raw: "); Serial.println(luzValor);
  Serial.print("Chuva raw: "); Serial.println(chuvaValor);
  Serial.print("Chuva %: "); Serial.println(chuvaPercent);
  Serial.print("Gases raw: "); Serial.println(gasValor);
  Serial.print("Gases %: "); Serial.println(gasPercent);
  Serial.print("Pot: "); Serial.println(pot);
  Serial.print("Modo LCD: "); Serial.println(modoLCD);
  Serial.print("Distancia: "); Serial.println(distancia);
  Serial.println("---------------------");

  delay(600);
}
