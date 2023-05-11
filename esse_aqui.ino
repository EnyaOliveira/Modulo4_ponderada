int sequencia[32] = {};
int jogada = 0;
bool end_game = false;
int botoes[5] = {15,2, 21, 22, 23};
//int botao_reset = {23};
int leds[4] = {12, 14, 27, 26};
int lance = 0;

//definindo e relacionando os botões e leds
void setup() {
  Serial.begin(9600);
  // Leds
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
    // Botões
  pinMode(22, INPUT);
  pinMode(21, INPUT);
  pinMode(21, INPUT);
  pinMode(15, INPUT);
  pinMode(23, INPUT); 
}


void inicio_rodada() {
  int randomizar = random(4);
  sequencia[jogada] = randomizar;
  jogada = jogada + 1;
}

void repeticao() {
  for (int i = 0; i < jogada; i++) {
    digitalWrite(leds[sequencia[i]], HIGH);
    delay(500);
    digitalWrite(leds[sequencia[i]], LOW);
    delay(100);
  }
}

void pausa() {
  int escolhido = 0;
  for (int i = 0; i < jogada; i++) {
    bool jogou = false;
    while (!jogou) {
      for (int i = 0; i <= 3; i++) {
        if (digitalRead(botoes[i]) == HIGH) {
          escolhido = i;
          digitalWrite(leds[i], HIGH);
          delay(300);
          digitalWrite(leds[i], LOW);
          jogou = true;
        }
      }
    }

    if (sequencia[lance] != escolhido) {
      for (int i = 0; i <= 3; i++) {
        delay(200);
        digitalWrite(26, HIGH);
        digitalWrite(27, HIGH);
        digitalWrite(14, HIGH);
        digitalWrite(12, HIGH);
        delay(100);
        digitalWrite(26, LOW);
        digitalWrite(27, LOW);
        digitalWrite(14, LOW);
        digitalWrite(12, LOW);
   }
      end_game = true;
      break;
    }
          lance = lance + 1;
  }
  lance = 0;
}

void reset(){
    delay(200);
    digitalWrite(26, HIGH);
    digitalWrite(27, HIGH);
    digitalWrite(14, HIGH);
    digitalWrite(12, HIGH);
    delay(100);
    digitalWrite(26, LOW);
    digitalWrite(27, LOW);
    digitalWrite(14, LOW);
    digitalWrite(12, LOW);
    sequencia[32] = {};
    jogada = 0;
    lance = 0;
    end_game = false;
}

void definidor(){
  inicio_rodada();
  repeticao();
  pausa();

  if (end_game == true) {
    reset();// reinicia todas as variáveis
  }
  delay(1000);
}

void loop() {
  definidor();
}
