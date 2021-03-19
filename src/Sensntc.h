
/***************************************************
     Термистор
**************************************************/

#include  <Thermistor.h>
#include  <NTC_Thermistor.h>
#include  <AverageThermistor.h>

#define  SENSOR_PIN              A0
#define  REFERENCE_RESISTANCE    41000    //подбором значения по 1-2 тыс калибруем термистор
#define  NOMINAL_RESISTANCE      100000
#define  NOMINAL_TEMPERATURE     25
#define  B_VALUE                 3950

#define  READINGS_NUMBER  10

#define  DELAY_TIME  10

Thermistor* thermistor = NULL;
//const double celsius;


void ntcStart(){
      Serial.begin(9600);

  Thermistor* originThermistor = new NTC_Thermistor(
    SENSOR_PIN,
    REFERENCE_RESISTANCE,
    NOMINAL_RESISTANCE,
    NOMINAL_TEMPERATURE,
    B_VALUE
  );
  thermistor = new AverageThermistor(
    originThermistor,
    READINGS_NUMBER,
    DELAY_TIME
  );
}

void ntcRead(){
// Reads temperature
  ntc = thermistor->readCelsius();

  //Вывод в сериал для диагностики
  Serial.print("Hotend: ");
  Serial.print(ntc);
  Serial.print(" C, ");

  delay(100); // optionally, only to delay the output of information in the example.


//Условия работы реле по температуре термистора
if (ntc >= 190)                      //сверяем установленную температуру
{
  digitalWrite(RELE1, HIGH);         //включаем реле, инвертируем если нужна обратная логика 
}

//режим термостат
// else if (tempNtc >= 110)             //сверяем установленную температуру
// {
//   led1.off(); //гасим светодиод
//   digitalWrite(RELE1, LOW);          //выключаем реле, инвертируем если нужна обратная логика  
// }
}



  
