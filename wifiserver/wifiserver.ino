#include <ESP8266WiFi.h>

// Настройки Wi-Fi точки доступа
const char* ssid = "Mojalazertag";  // Имя Wi-Fi точки
const char* password = "12345678"; // Пароль (минимум 8 символов)

void setup() {
  Serial.begin(115200); // Инициализация Serial для отладки

  // Создание Wi-Fi точки доступа
  WiFi.softAP(ssid, password);

  // Вывод IP-адреса точки доступа
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point IP: ");
  Serial.println(IP);
}

void loop() {
  // Получаем количество подключенных устройств
  uint8_t clients = WiFi.softAPgetStationNum();

  // Если есть подключенные устройства
  if (clients > 0) {
    Serial.print("Connected devices: ");
    Serial.println(clients);

    // Получаем список MAC-адресов подключенных устройств
    struct station_info *station_list = wifi_softap_get_station_info();

    // Перебираем список устройств
    while (station_list != NULL) {
      // Преобразуем MAC-адрес в строку
      char macStr[18];
      snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
               station_list->bssid[0], station_list->bssid[1], station_list->bssid[2],
               station_list->bssid[3], station_list->bssid[4], station_list->bssid[5]);

      // Выводим MAC-адрес и IP-адрес устройства
      Serial.print("Device MAC: ");
      Serial.print(macStr);
      Serial.print(" | IP: ");
      Serial.println(IPAddress(station_list->ip));
      
      // Переходим к следующему устройству
      station_list = STAILQ_NEXT(station_list, next);
    }

    // Освобождаем память
    wifi_softap_free_station_info();
  } else {
    Serial.println("No devices connected.");
  }

  // Задержка перед следующим опросом
  delay(5000); // Проверяем каждые 5 секунд
}