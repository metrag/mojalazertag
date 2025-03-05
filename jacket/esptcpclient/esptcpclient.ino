#include <WiFi.h>

const char* ssid = "Ttttt";         // Замените на ваш SSID
const char* password = "05artem14"; // Замените на ваш пароль
const char* serverIP = "172.20.10.3";  // IP-адрес сервера
const int serverPort = 12345;          // Порт сервера

#define ANALOG_PIN 34  // Пин для аналогового датчика (например, GPIO 34)

WiFiClient client;

void setup() {
  Serial.begin(9600);

  // Подключение к Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { // Ожидание подключения к Wi-Fi
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void loop() {
  // Чтение значения с аналогового пина
  int sensorValue = analogRead(ANALOG_PIN);

  // Отправка данных на сервер
  if (client.connect(serverIP, serverPort)) {
    client.println(sensorValue); // Отправляем значение на сервер
    client.stop();              // Закрываем соединение
    Serial.print("Data sent to server: ");
    Serial.println(sensorValue);
  } else {
    Serial.println("Failed to connect to server");
  }

  // Задержка перед следующим чтением
  delay(1000); // Отправляем данные каждую секунду
}