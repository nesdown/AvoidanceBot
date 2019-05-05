// Приклад використання коду відрізняється тим, що зупиняє пристрій при знаходженні перешкоди

#define PIN_LEFT_LEG   2   
#define PIN_RIGHT_LEG  3  
#define PIN_LEFT_FOOT  4  
#define PIN_RIGHT_FOOT 5 
 

#define TRIM_LEFT_LEG   0 
#define TRIM_RIGHT_LEG  0
#define TRIM_LEFT_FOOT  0 
#define TRIM_RIGHT_FOOT 0

Otto Otto;  

void setup()
{
  Serial.begin(9600);
  Serial.println("hello");
  
  //Set the servo pins
  Otto.init(PIN_LEFT_LEG,PIN_RIGHT_LEG,PIN_LEFT_FOOT,PIN_RIGHT_FOOT,true);
  Otto.setTrims(TRIM_LEFT_LEG,TRIM_RIGHT_LEG, TRIM_LEFT_FOOT, TRIM_RIGHT_FOOT);

  Otto.sing(S_connection);
  Otto.home();

}

void loop() 
{
  bool obstacleDetected = false;
  
  obstacleDetected = obstacleDetector(); 
  
  if(obstacleDetected)
  { 
        Otto.sing(S_surprise); 
        Otto.walk(7,1000,BACKWARD); 
        delay(1000);
        Otto.sing(S_happy);
        Otto.turn(10,1000,RIGHT);                
        delay(2000); 
          
   }        
   else
   { 
          Otto.walk(1,1000,FORWARD);  
    }          
 }  


bool obstacleDetector()
{
   int distance = Otto.getDistance();
   
   Serial.println(distance);
   
   if(distance<15)
   {
      return true;
   }
   else
   {
      return false;
   }

}
