/***************************************************
 * БЛИНК
 **************************************************/


/* Закомментируйте это, чтобы отключить BLYNK_LOG и сэкономить место */
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "Connect.h" // Подключаем вкладку Connect.h

BlynkTimer timer; // Объявляем Таймер

// Отправка на сервер при подключении
BLYNK_CONNECTED() { //синхронизация виртуального порта для блинка (виджеты установки пределов сарабатывания реле)
  Blynk.virtualWrite(VPIN_TempIn0, String(tempSensor[0],1));
  Blynk.virtualWrite(VPIN_TempIn1, String(tempSensor[1],1));
  Blynk.virtualWrite(VPIN_TempIn2, ntc);
  //добавить аналогично, если нужно больше датчиков
}

// Отправляем данные в приложение
void SendBlynk(){
    Blynk.virtualWrite(VPIN_TempIn0, String(tempSensor[0],1));        // Температура от датчика 1 (1 задает 10-тые)
    Blynk.virtualWrite(VPIN_TempIn1, String(tempSensor[1],1));        // Температура от датчика 2 (1 задает 10-тые)
    Blynk.virtualWrite(VPIN_TempIn2, ntc);
   //добавить аналогично, если нужно больше датчиков 
  }

//ручное отключение реле из блинк
BLYNK_WRITE(V4){ //привязка виртуального пина к виджету
  off = param.asInt();
digitalWrite (RELE1, off);
}

void setupBlynk(){
// Вызываем функцию подключения к Blynk
  reconnectBlynk();

// Настраеваем таймеры  
  timer.setInterval(1000, SendBlynk);
  timer.setInterval(10000, reconnectBlynk);
}

void loopBlynk(){
  if (Blynk.connected()){ Blynk.run();} 
  timer.run();
}
