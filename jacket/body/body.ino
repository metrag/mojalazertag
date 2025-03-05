// #include <WiFi.h>

// const char* ssid = "ttttt";         // Замените на ваш SSID
// const char* password = "00000000"; // Замените на ваш пароль

// const char* serverIP = "192.168.1.101";  // IP-адрес сервера
// const int serverPort = 12345;          // Порт сервера

// WiFiClient client;

// #define sensor_1 34  // Пин первого фоторезистора
// #define sensor_2 35  // Пин второго фоторезистора
// #define led 16       // Пин светодиода

// int val1, val2;
// int baseline1, baseline2; // Базовые значения для датчиков

// // Временные параметры (мс)
// #define BLINK_INTERVAL 200  // Интервал мигания светодиода
// #define LED_DURATION 3000   // Длительность мигания (3 секунды)
// #define DIF_LEVEL 100       // Порог разницы для попадания
// #define ENV_CHANGE_THRESHOLD 200 // Порог для изменения обстановки
// #define SIMILARITY_THRESHOLD 200 // Порог схожести датчиков для калибровки
// #define CALIBRATION_TIME 1000   // Время калибровки (5 секунд)

// bool ledState = false;      // Состояние светодиода
// bool isBlinking = false;    // Флаг мигания
// unsigned long blinkStartTime = 0; // Время начала мигания
// unsigned long lastBlinkTime = 0;  // Время последнего изменения состояния светодиода

// void setup() {
//   Serial.begin(9600);       // Инициализация Serial для отладки

//   // Подключение к Wi-Fi
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) { // Ожидание подключения к Wi-Fi
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("\nConnected to WiFi");

//   IPAddress ip = WiFi.localIP();
//   Serial.print("IP Address: ");
//   Serial.println(ip);

//   pinMode(led, OUTPUT);     // Настройка пина светодиода как выход
//   digitalWrite(led, LOW);   // Выключение светодиода

//   // Первоначальная калибровка
//   calibrateSensors();
// }

// void loop() {
//   // Чтение значений с фоторезисторов
//   val1 = analogRead(sensor_1);
//   val2 = analogRead(sensor_2);

//   // Для отладки
//   Serial.println("Сенсор 1: " + String(val1) + "(" + String(baseline1) + ")" + " | Сенсор 2: " + String(val2) + "(" + String(baseline2) + ")");

//   // Проверка изменения обстановки
//   if (abs(val1 - baseline1) > ENV_CHANGE_THRESHOLD && abs(val2 - baseline2) > ENV_CHANGE_THRESHOLD) {
//     // Если оба датчика показывают значения, значительно отличающиеся от базовых
//     if (abs(val1 - val2) < SIMILARITY_THRESHOLD) {
//       Serial.println("Обстановка изменилась, повторная калибровка...");
//       calibrateSensors(); // Повторная калибровка
//     } else {
//       Serial.println("Обстановка изменилась, но датчики не схожи. Калибровка отменена.");
//     }
//   }

//   // Проверка попадания (уменьшение значения)
//   int difference1 = baseline1 - val1; // Разница для сенсора 1
//   int difference2 = baseline2 - val2; // Разница для сенсора 2

//   // Если разница превышает порог и мигание еще не начато
//   if ((difference1 > DIF_LEVEL || difference2 > DIF_LEVEL) && !isBlinking) {
//     isBlinking = true;            // Активируем флаг мигания
//     blinkStartTime = millis();    // Запоминаем время начала мигания
//     Serial.println("Попадание!");
//     // Отправляем '1' на сервер
//     sendToServer('1');
//   }

//   // Если мигание активно
//   if (isBlinking) {
//     // Мигание светодиода
//     if (millis() - lastBlinkTime >= BLINK_INTERVAL) {
//       ledState = !ledState;              // Меняем состояние светодиода
//       digitalWrite(led, ledState);       // Применяем новое состояние
//       lastBlinkTime = millis();          // Обновляем время последнего изменения
//     }

//     // Если прошло время LED_DURATION, выключаем светодиод и сбрасываем флаг
//     if (millis() - blinkStartTime >= LED_DURATION) {
//       digitalWrite(led, LOW);            // Выключаем светодиод
//       isBlinking = false;                // Сбрасываем флаг мигания

//       // Отправляем '0' на сервер
//       sendToServer('0');
//     }
//   }

//   // Небольшая задержка для стабилизации измерений
//   delay(50);
// }

// // Функция калибровки
// void calibrateSensors() {
//   unsigned long startTime = millis();
//   int sum1 = 0, sum2 = 0;
//   int count = 0;

//   Serial.println("Калибровка...");

//   while (millis() - startTime < CALIBRATION_TIME) {
//     sum1 += analogRead(sensor_1); // Суммируем показания сенсора 1
//     sum2 += analogRead(sensor_2); // Суммируем показания сенсора 2
//     count++; // Увеличиваем счетчик
//     delay(10); // Небольшая задержка
//   }

//   // Вычисляем средние значения
//   baseline1 = sum1 / count;
//   baseline2 = sum2 / count;

//   Serial.println("Калибровка завершена.");
//   Serial.println("Базовое значение сенсора 1: " + String(baseline1));
//   Serial.println("Базовое значение сенсора 2: " + String(baseline2));
// }

// // Функция отправки данных на сервер
// void sendToServer(char data) {
//   if (client.connect(serverIP, serverPort)) {
//     client.print(data); // Отправляем данные на сервер
//     client.stop();       // Закрываем соединение
//     Serial.print("Data sent to server: ");
//     Serial.println(data);
//   } else {
//     Serial.println("Failed to connect to server");
//   }
// }
#include <WiFi.h>

const char* ssid = "ttttt";         // Замените на ваш SSID
const char* password = "00000000"; // Замените на ваш пароль

const char* serverIP = "192.168.1.101";  // IP-адрес сервера
const int serverPort = 12345;          // Порт сервера

WiFiClient client;

#define sensor_1 34  // Пин первого фоторезистора
#define sensor_2 35  // Пин второго фоторезистора
#define led 16       // Пин светодиода

int val1, val2;
int baseline1, baseline2; // Базовые значения для датчиков

// Временные параметры (мс)
#define BLINK_INTERVAL 200  // Интервал мигания светодиода
#define LED_DURATION 3000   // Длительность мигания (3 секунды)
#define DIF_LEVEL 100       // Порог разницы для попадания
#define ENV_CHANGE_THRESHOLD 200 // Порог для изменения обстановки
#define SIMILARITY_THRESHOLD 200 // Порог схожести датчиков для калибровки
#define CALIBRATION_TIME 1000   // Время калибровки (5 секунд)

bool ledState = false;      // Состояние светодиода
bool isBlinking = false;    // Флаг мигания
unsigned long blinkStartTime = 0; // Время начала мигания
unsigned long lastBlinkTime = 0;  // Время последнего изменения состояния светодиода

bool wifiConnected = false; // Флаг подключения к Wi-Fi

void setup() {
  Serial.begin(9600);       // Инициализация Serial для отладки

  // Подключение к Wi-Fi
  WiFi.begin(ssid, password);
  
  unsigned long startAttemptTime = millis(); // Время начала попытки подключения
  
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) { // Ожидание подключения к Wi-Fi в течение 10 секунд
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    wifiConnected = true;
    Serial.println("\nConnected to WiFi");

    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
  } else {
    Serial.println("\nFailed to connect to WiFi. Continuing without WiFi.");
  }

  pinMode(led, OUTPUT);     // Настройка пина светодиода как выход
  digitalWrite(led, LOW);   // Выключение светодиода

  // Первоначальная калибровка
  calibrateSensors();
}

void loop() {
  if (!wifiConnected) {
    // Если Wi-Fi не подключен, просто читаем значения с датчиков и выводим их в Serial
    val1 = analogRead(sensor_1);
    val2 = analogRead(sensor_2);

    Serial.println("Сенсор 1: " + String(val1) + "(" + String(baseline1) + ")" + " | Сенсор 2: " + String(val2) + "(" + String(baseline2) + ")");

    // Проверка попадания (уменьшение значения)
    int difference1 = baseline1 - val1; // Разница для сенсора 1
    int difference2 = baseline2 - val2; // Разница для сенсора 2

    // Если разница превышает порог и мигание еще не начато
    if ((difference1 > DIF_LEVEL || difference2 > DIF_LEVEL) && !isBlinking) {
      isBlinking = true;            // Активируем флаг мигания
      blinkStartTime = millis();    // Запоминаем время начала мигания
      Serial.println("Попадание!");
    }

    // Если мигание активно
    if (isBlinking) {
      // Мигание светодиода
      if (millis() - lastBlinkTime >= BLINK_INTERVAL) {
        ledState = !ledState;              // Меняем состояние светодиода
        digitalWrite(led, ledState);       // Применяем новое состояние
        lastBlinkTime = millis();          // Обновляем время последнего изменения
      }

      // Если прошло время LED_DURATION, выключаем светодиод и сбрасываем флаг
      if (millis() - blinkStartTime >= LED_DURATION) {
        digitalWrite(led, LOW);            // Выключаем светодиод
        isBlinking = false;                // Сбрасываем флаг мигания
      }
    }

    // Небольшая задержка для стабилизации измерений
    delay(50);
    return; // Выходим из loop, чтобы не выполнять код ниже
  }

  // Чтение значений с фоторезисторов
  val1 = analogRead(sensor_1);
  val2 = analogRead(sensor_2);

  // Для отладки
  Serial.println("Сенсор 1: " + String(val1) + "(" + String(baseline1) + ")" + " | Сенсор 2: " + String(val2) + "(" + String(baseline2) + ")");

  // Проверка изменения обстановки
  if (abs(val1 - baseline1) > ENV_CHANGE_THRESHOLD && abs(val2 - baseline2) > ENV_CHANGE_THRESHOLD) {
    // Если оба датчика показывают значения, значительно отличающиеся от базовых
    // if (abs(val1 - val2) < SIMILARITY_THRESHOLD) {
      Serial.println("Обстановка изменилась, повторная калибровка...");
      calibrateSensors(); // Повторная калибровка
    // } else {
      Serial.println("Обстановка изменилась, но датчики не схожи. Калибровка отменена.");
    // }
  }

  // Проверка попадания (уменьшение значения)
  int difference1 = baseline1 - val1; // Разница для сенсора 1
  int difference2 = baseline2 - val2; // Разница для сенсора 2

  // Если разница превышает порог и мигание еще не начато
  if ((difference1 > DIF_LEVEL || difference2 > DIF_LEVEL) && !isBlinking) {
    isBlinking = true;            // Активируем флаг мигания
    blinkStartTime = millis();    // Запоминаем время начала мигания
    Serial.println("Попадание!");
    // Отправляем '1' на сервер
    sendToServer('1');
  }

  // Если мигание активно
  if (isBlinking) {
    // Мигание светодиода
    if (millis() - lastBlinkTime >= BLINK_INTERVAL) {
      ledState = !ledState;              // Меняем состояние светодиода
      digitalWrite(led, ledState);       // Применяем новое состояние
      lastBlinkTime = millis();          // Обновляем время последнего изменения
    }

    // Если прошло время LED_DURATION, выключаем светодиод и сбрасываем флаг
    if (millis() - blinkStartTime >= LED_DURATION) {
      digitalWrite(led, LOW);            // Выключаем светодиод
      isBlinking = false;                // Сбрасываем флаг мигания

      // Отправляем '0' на сервер
      sendToServer('0');
    }
  }

  // Небольшая задержка для стабилизации измерений
  delay(50);
}

// Функция калибровки
void calibrateSensors() {
  unsigned long startTime = millis();
  int sum1 = 0, sum2 = 0;
  int count = 0;

  Serial.println("Калибровка...");

  while (millis() - startTime < CALIBRATION_TIME) {
    sum1 += analogRead(sensor_1); // Суммируем показания сенсора 1
    sum2 += analogRead(sensor_2); // Суммируем показания сенсора 2
    count++; // Увеличиваем счетчик
    delay(10); // Небольшая задержка
  }

  // Вычисляем средние значения
  baseline1 = sum1 / count;
  baseline2 = sum2 / count;

  Serial.println("Калибровка завершена.");
  Serial.println("Базовое значение сенсора 1: " + String(baseline1));
  Serial.println("Базовое значение сенсора 2: " + String(baseline2));
}

// Функция отправки данных на сервер
void sendToServer(char data) {
  if (wifiConnected && client.connect(serverIP, serverPort)) {
    client.print(data); // Отправляем данные на сервер
    client.stop();       // Закрываем соединение
    Serial.print("Data sent to server: ");
    Serial.println(data);
  } else {
    Serial.println("Failed to connect to server");
  }
}