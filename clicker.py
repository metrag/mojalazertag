import time
from selenium import webdriver
from selenium.webdriver.common.by import By

# Настройка браузера
options = webdriver.ChromeOptions()
# Убрали --headless, чтобы браузер был виден
driver = webdriver.Chrome(options=options)  # ChromeDriver автоматически ищется в PATH или текущей папке

# URL страницы
url = "http://localhost:3000/"
driver.get(url)

# Функция для чтения значения из файла
def read_id():
    with open("id.txt", "r") as file:
        return file.read().strip()

# Основной цикл
try:
    while True:
        # Чтение значения из файла
        current_id = read_id()

        # Если значение равно 1, нажимаем кнопку
        if current_id == "1":
            try:
                # Находим кнопку по её ID, классу или другому селектору
                button = driver.find_element(By.ID, "hit_but")  # Замените "hit_but" на реальный ID кнопки
                button.click()  # Имитируем нажатие кнопки
                print("Кнопка нажата успешно!")
            except Exception as e:
                print("Ошибка при нажатии кнопки:", e)

        # Пауза перед следующей проверкой
        time.sleep(1)  # Проверяем каждую секунду

except KeyboardInterrupt:
    print("Скрипт остановлен.")

finally:
    # Закрываем браузер
    driver.quit()