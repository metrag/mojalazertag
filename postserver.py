import requests
import json

# Путь к файлу
file_path = 'id.txt'

# URL сервера
url = 'http://172.20.10.4:3000//hit'

# Чтение числа из файла
with open(file_path, 'r') as file:
    number = file.read().strip()

# Подготовка JSON-данных
data = {"hit": int(number)}  # Преобразуем строку в число

# Заголовки запроса
headers = {'Content-Type': 'application/json'}

# Отправка POST-запроса
response = requests.post(url, data=json.dumps(data), headers=headers)

# Проверка ответа
if response.status_code == 200:
    print('Данные успешно отправлены!')
    print('Ответ сервера:', response.json())  # Если сервер возвращает JSON
else:
    print(f'Ошибка: {response.status_code}')
    print(response.text)