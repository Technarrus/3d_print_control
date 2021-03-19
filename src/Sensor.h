/***************************************************
 * ДАТЧИК
 **************************************************/

#include <OneWire.h>
#include <DallasTemperature.h>

OneWire  oneWire(D3); //  вход Wire шины датчиков 18b20
DallasTemperature ds(&oneWire);

byte qty; //кол-во далласов

// адреса подключенных далласов
DeviceAddress sensor1 = {0x28,0x4E,0x94,0x16,0xA8,0x1,0x3C,0xEB};  //ПОМЕНЯТЬ НА СВОЙ
DeviceAddress sensor2 = {0x28,0x26,0xC5,0x16,0xA8,0x1,0x3C,0xD1};  //ПОМЕНЯТЬ НА СВОЙ

//добавить аналогично, если нужно больше датчиков

void sensorStart(){
ds.begin();   
qty = ds.getDeviceCount(); // при включении сохраняем количество датчиков
}

void readTemp(){ // читаем температуру и заполняем массив
   ds.requestTemperatures();    
   tempSensor[0] = ds.getTempC(sensor1);
   tempSensor[1] = ds.getTempC(sensor2);
//.... и далее если нужно больше датчиков

  // Serial.print("Bed: ");
  // Serial.print(tempSensor[0]);
  // Serial.print(" C, ");
  // Serial.print("Kamera: ");
  // Serial.print(tempSensor[1]);
  // Serial.print(" C, ");
  // Serial.print("Hotend: ");
  // Serial.print(ntc);
  // Serial.print(" C, ");

//отключение при превышении порога

if (tempSensor[0] >= 90)            //сверяем установленную температуру
{
  digitalWrite(RELE1, HIGH);         //включаем реле, инвертируем если нужна обратная логика 
}

// else if (tempSensor[0] >=80)    //сверяем установленную температуру
// {
//   digitalWrite(RELE1, LOW);          //выключаем реле, инвертируем если нужна обратная логика  
// }



//Отключение при условии температуры термистора ниже 40

if(ntc < 40) {
if (millis() - zadergka >= 120000) {  // задержка на 2 мин       
  digitalWrite(RELE1, HIGH);          //включаем реле, инвертируем если нужна обратная логика 
  }
}

 //Подключаем уведомления (функция в отдельной вкладке, раскомментировать если нужны)
  Notifi(); 
}
