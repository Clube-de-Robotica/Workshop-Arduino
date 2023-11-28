//...........................................................WORKSHOP_ARDUINO (Clube de Robótica)................................................
//...Author:Ângelo Rodrigues

//.........................................Definição dos Pins.....................

#define trigPin 13
#define echoPin 12
#define green_led 10
#define yellow_led 9
#define red_led 8



int distance;   //... variável global que vai guardar valor da distância...


//................................................ 1ª opção de função usando a constante da velocidade de propagação do som a 20ºC   .......

long measure_distance_velocity() {
  long duration, distance;

  //Send pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //Wait for edistanceho and measure time until it happens
  duration = pulseIn(echoPin, HIGH);
  distance = 344 * pow(10, 2) * ((duration * pow(10, -6)) / 2);              //.... distance = velocity * time, with time(microseconds) and velocity (m/s)
  return distance;
}


//........................................... ...............2ª opção de função dividindo a duração de propagação do pulso por 58 .......

long measure_distance() {
  long duration, distance;

  //Send pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //Wait for edistanceho and measure time until it happens
  duration = pulseIn(echoPin, HIGH);
  //distanceompute distandistancee
  distance = duration / 58;
  return distance;
}


//....................................................Declaração dos pins dentro da função SETUP..................


void setup() {
  Serial.begin (9600);        //... Definição do rating de comunicação e leitura do Serial Monitor
  pinMode(trigPin, OUTPUT);   //... Definição do pin do sensor de ultrassons que envia um pulso como OUTPUT
  pinMode(echoPin, INPUT);    //... Definição do pin do sensor de ultrassons que recebe um pulso como INPUT
  pinMode(green_led, OUTPUT); //... Definição do pin do LED VERDE como OUTPUT
  pinMode(yellow_led, OUTPUT); //... Definição do pin do LED AMARELO como OUTPUT
  pinMode(red_led, OUTPUT);   //... Definição do pin do LED VERMELHO como OUTPUT
}


//...............................................................................Função LOOP ............

void loop() {

  //distance=measure_distance_velocity();  //Atribuição do valor retornado pela 1ª opção função que determina a distância á variável distance

  distance = measure_distance(); //Atribuição do valor retornado pela 2ª opção função que determina a distância á variável distance

  Serial.print(distance);      //Print do valor de distance
  Serial.println("  cm");


  if (distance <= 20) {                   // .......Se a distância é menor ou igual que 20 cm apenas o led vermelho acende
    digitalWrite(green_led, LOW);
    digitalWrite(yellow_led, LOW);
    digitalWrite(red_led, HIGH);
  }
  else if (distance > 20 && distance < 70) {   //....... Se a distância é maior que 20 cm e menor que 70 cm apenas o led amarelo acende
    digitalWrite(green_led, LOW);
    digitalWrite(yellow_led, HIGH);
    digitalWrite(red_led, LOW);
  }
  else if (distance >= 70 && distance < 100) {  //....... Se a distância é maior igual que 70 cm e menor que 100 cm apenas o led verde acende
    digitalWrite(green_led, HIGH);
    digitalWrite(yellow_led, LOW);
    digitalWrite(red_led, LOW);
  }
  else {                                    //......Senão, caso nenhuma das condições anteriores, todos os leds se apagam
    for (int i = red_led; i <= green_led; i++) {
      digitalWrite(i, LOW);
    }
  }
  delay(60);
}
