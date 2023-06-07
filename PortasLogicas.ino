const int amper = A5;
const int variacao = 5;
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

bool comparar(int valorLido, int valorReferencia, int valorVariacao){
  return valorLido >= (valorReferencia - valorVariacao) && valorLido <= (valorReferencia + valorVariacao);
}

void setup(){
  pinMode(led, OUTPUT);
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop(){
  valorPot = analogRead(amper);
  //Serial.println(valorPot);

  if (comparar(valorPot, 28, variacao)){
    And();
    Serial.println("and");
  }
  else if (comparar(valorPot, 131, variacao)){
    Xor();
    Serial.println("xor");
  }
  else if (comparar(valorPot, 238, variacao)){
    Not();
    Serial.println("not");
  }
  else if (comparar(valorPot, 486, variacao)){
    Fio();
    Serial.println("fio");
  }
  else if (comparar(valorPot, 511, variacao)){
    Or();
    Serial.println("or");
  }
  else if (comparar(valorPot, 592, variacao)){
    Latch();
    Serial.println("latch");
  }
  else{
    digitalWrite(led, LOW);
    Serial.println(0);
  }
}