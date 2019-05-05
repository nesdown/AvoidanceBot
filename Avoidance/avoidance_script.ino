// Виконавчий програмний код, що реалізує обхід перешкод пристроєм.
// Застосовує 6 пінів ініціалізації та 7й допоміжний пін генерації показників.
// Набір даних регулюється подачею прямих даних та константних показників.

// Ініціалізація виконавчих бібліотек, класичне поєднання методів ООП та Функціональної розробки із застосування парадигми реактивного програмування на етапі генерації вихідного коду.

#include <Servo.h> 
#include <Oscillator.h>
#include <US.h>
#include <Otto.h>

// Ініціалізація об'єкту обробки даниз приладом
Otto Otto;  

// Ідентифікація пінів сервоприводів
  #define PIN_YL 2 //servo[2]
  #define PIN_YR 3 //servo[3]
  #define PIN_RL 4 //servo[4]
  #define PIN_RR 5 //servo[5]

// Ідентифікація пінів обробки даних датчиком
  #define ECHOPIN 9        // Pin to receive echo pulse
  #define TRIGPIN 8        // Pin to send trigger pulse

// Блок створення глобальних змінних загального контексту
// Параметри руху
int T=1000;              //Початкова затримка руху
int moveId=0;            //Ідентифікатор руху
int moveSize=15;         //Асоційована висота рухів

bool obstacleDetected = false;

// Блок ініціалізації програмнох компоненти
void setup(){
  Serial.begin(19200);
  //Set the servo pins
  Otto.init(PIN_YL,PIN_YR,PIN_RL,PIN_RR,true, -1, 13, 8, 9);
  Otto.sing(S_connection); 
  Otto.home();
  delay(50);
  Otto.sing(S_happy); // a happy Otto :)

  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
}

// Блок ініціалізації виконавчої компоненти
void loop() {
  if(obstacleDetected){ 
               Otto.sing(S_surprise); 
               Otto.playGesture(OttoFretful); 
               Otto.sing(S_fart3); 
               Otto.walk(2,1300,-1); 
               Otto.turn(2,1000,-1);                
             delay(50); 
             obstacleDetector(); 
             }        
         else{ 
            Otto.walk(1,1000,1); 
            obstacleDetector(); 
        }           
  }  

// Функція зчитування даних з датчика відстані
void obstacleDetector(){

// Початок відліку
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);

// Розрахунок дистанції в систему СІ
  float distance = pulseIn(ECHOPIN, HIGH);
  distance= distance/58;
  Serial.print(distance);
  Serial.println("cm");
 if(distance<15){
          obstacleDetected = true;

          // Логування даних
          Serial.println ("Obstacle Detected! Avoid collision");
        }else{
          obstacleDetected = false;

          // Логування
          Serial.println ("No Obstacle detected! - Keep on walking");
        }
  
}
