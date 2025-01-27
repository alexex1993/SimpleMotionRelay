#define Sensor 0
#define Relay 1

TaskHandle_t SensorReadTask;
TaskHandle_t RelayHandlerTask;

float duration_on = 0.0;
float duration_off = 0.0;
bool Detection = false;


void setup() 
{
  Serial.begin(115200);

  pinMode(Sensor, INPUT_PULLDOWN);        // Указываем вывод, как вход  
  pinMode(Relay, OUTPUT_OPEN_DRAIN);

  xTaskCreatePinnedToCore(
                  SensorReadTaskCode,   /* Task function. */
                  "SensorReadTask",     /* name of task. */
                  10000,       /* Stack size of task */
                  NULL,        /* parameter of the task */
                  1,           /* priority of the task */
                  &SensorReadTask,      /* Task handle to keep track of created task */
                  0);          /* pin task to core 0 */  

  xTaskCreatePinnedToCore(
                    RelayHandlerTaskCode,   /* Task function. */
                    "RelayHandlerTask",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &RelayHandlerTask,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */

}

  void SensorReadTaskCode(void * pvParameters )
  {
    Serial.print("SensorReadTask running on core ");
    Serial.println(xPortGetCoreID());
    for(;;)
    {
      Detection = digitalRead(Sensor); // Считываем показания с порта
      delay(1000);
    }
  }

  void RelayHandlerTaskCode(void * pvParameters )
  {
    Serial.print("RelayHandlerTask running on core ");
    Serial.println(xPortGetCoreID());
    
    for(;;)
    {
      if(Detection == HIGH){
        Serial.println("Motion detected! Duration: " + String(duration_on) + " sec"); 
        digitalWrite(Relay, LOW);
        duration_on = duration_on + 0.1;
        duration_off = 0.0;
      }                    

      if(Detection == LOW){                  
        Serial.println("Clear");
        duration_on = 0.0;
        duration_off = duration_off + 0.1;
        if (duration_off > 120.0) digitalWrite(Relay, HIGH);
      }             
      delay(100);
    }

  }

void loop() {}
