
/***************************************************
   СЕТЬ
**************************************************/

//#define USE_LOCAL_SERVER  //работа через локальный сервер

//#ifdef USE_LOCAL_SERVER
     // #define SERVER                  IPAddress(192, 168, 0, 100) // Свой IP пишите
      //#define SERVER                  "******.dlinkddns.com" // Имя своего хоста (Пример: "technarr.dlinkddns.com")
//#endif

/***************************************************
   Настройка сети
**************************************************/
#define WIFI_SSID               "*********"  //Имя точки доступа WIFI
#define WIFI_PASS               "*********" //пароль точки доступа WIFI
#define AUTH                    "*******************************"
 
/***************************************************
   Функции блинка
**************************************************/

void ConnectBlynk()
{
  //*******************************************************
  // Запускаем WiFi
    if (WiFi.status() != WL_CONNECTED)// Если нет WiFi, то коннектимся
    {
      BLYNK_LOG(WIFI_SSID);
//      Serial.println();
//      Serial.println();
//      Serial.print("Connecting to ");
//      Serial.println(WIFI_SSID);
      
      WiFi.begin(WIFI_SSID, WIFI_PASS);

      int8_t count=0;
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        Serial.print(WiFi.status());
        count++;
        if (count >= 5){break;Serial.println("WiFi not connected");}
      }
    }
  /*  Дисконект - для справки 
    WiFi.disconnect(); // отключаемся от сети
    Serial.println("Disconnect WiFi.");
  */
  
  //*******************************************************
  // Запускаем Blynk

  if (WiFi.status() == WL_CONNECTED)// Если нет WiFi, то не коннектимся
    {
          // CONNECT TO BLYNK
          #ifdef USE_LOCAL_SERVER // Если используются локальный сервер
            Blynk.config(AUTH, SERVER, 8080);
            Blynk.connect();
          #else // Иначе конектимся постаринке к блинку
            Blynk.config(AUTH);
            Blynk.connect();
          #endif
    }

  
  // До бесконечности будем оставаться в цикле while
  // пока не установим связь с сервером
  //  while (Blynk.connect() == false) {}
  
}//ConnectBlynk()


// Реконектимся если обрыв связи
void reconnectBlynk() {
  if (!Blynk.connected())
  {
    BLYNK_LOG("Disconnected now");
    ConnectBlynk();
    if (Blynk.connected()) 
    {
      BLYNK_LOG("Reconnected");      
    } 
    else 
    {
      BLYNK_LOG("Not reconnected");      
    }
  }
}//reconnectBlynk()
