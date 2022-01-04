#include <Servo.h>
#include <LiquidCrystal_I2C.h>

/*display*/
#define endereco 0x27
#define colunas 16
#define linhas 2
LiquidCrystal_I2C lcd(endereco, colunas, linhas);

/*sensor de chuva*/
int PinSensor = 0;
int Porcentagem = 0;
int chuva; //variavel do sensor

/*servomotores*/
Servo servo1, servo2;
int posicaoInicial = 0;
int posicaoAcionada = 180;

#define UM_SEGUNDO 1000

void setup() {
  lcd.init(); //inicia a comunicação com o display
  servo1.attach(10); //servomotor na porta 10
  servo2.attach(9); //servomotor na porta 9
}

void loop() {
  chuva = analogRead(PinSensor);
  Porcentagem = map(chuva, 1023, 0, 0, 100);

  lcd.setBacklight(HIGH); //liga a iluminação do display

  lcd.setCursor(1, 0);
  lcd.println("Sensor de Chuva");

  lcd.setCursor(0, 1);
  lcd.print(Porcentagem);
  lcd.println("%");

  delay(UM_SEGUNDO);

  if (Porcentagem >= 20) {
    /*display*/
    lcd.setCursor(7, 1);
    lcd.println("Chovendo!");
    delay(1000);
    lcd.clear();

    /*servo*/
    servo1.write(posicaoAcionada);//Janela 1
    servo2.write(posicaoAcionada);//Janela 2
  } else {
    servo1.write(posicaoInicial);//Janela 1
    servo2.write(posicaoInicial);//Janela 2
  }
}
