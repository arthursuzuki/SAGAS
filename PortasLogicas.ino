const int amper = A5;
const int variacao = 3;
int valorPot;

const int led = 13;
const int botao1 = 12;
const int botao2 = 11;

bool estadoLed = LOW;
bool botao2Pressionado = false;

void Fio(){
  digitalWrite(led, LOW);
  while (digitalRead(botao1) == LOW){
    digitalWrite(led, HIGH);
  }
}

void Not(){
  digitalWrite(led, HIGH);
  while (digitalRead(botao1) == LOW){
    digitalWrite(led, LOW);
  }
}

void Or(){
  digitalWrite(led, LOW);
  while ((digitalRead(botao1) == LOW) || (digitalRead(botao2) == LOW)){
    digitalWrite(led, HIGH);
  }
}

void And(){
  digitalWrite(led, LOW);
  while ((digitalRead(botao1) == LOW) && (digitalRead(botao2) == LOW)){
    digitalWrite(led, HIGH);
  }
}

void Xor(){
  digitalWrite(led, LOW);
  while (((digitalRead(botao1) == LOW) || (digitalRead(botao2) == LOW)) && (digitalRead(botao1) != digitalRead(botao2))){
    delay(50);
    digitalWrite(led, HIGH);
  }
}

void Latch(){
  digitalWrite(led, estadoLed);

  if ((digitalRead(botao2) == LOW) && (botao2Pressionado == false)){
    botao2Pressionado = true;
    estadoLed = HIGH;
  }
  if ((digitalRead(botao1) == LOW) && (botao2Pressionado == true)){
    botao2Pressionado = false;
    estadoLed = LOW;
  }
}

void setup(){
  pinMode(led, OUTPUT);
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop(){
  valorPot = analogRead(amper);
  Serial.println(valorPot);

  if ((valorPot >= (28 - variacao)) && (valorPot <= (28 + variacao))){
    Fio();
  }
  else if ((valorPot >= (131 - variacao)) && (valorPot <= (131 + variacao))){
    Not();
  }
  else if ((valorPot >= (238 - variacao)) && (valorPot <= (238 + variacao))){
    Or();
  }
  else if ((valorPot >= (486 - variacao)) && (valorPot <= (486 + variacao))){
    And();
  }
  else if ((valorPot >= (511 - variacao)) && (valorPot <= (511 + variacao))){
    Xor();
  }
  else if ((valorPot >= (592 - variacao)) && (valorPot <= (592 + variacao))){
    Latch();
  }
}