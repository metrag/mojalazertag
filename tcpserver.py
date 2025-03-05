import socket

#HOST = '172.20.10.3'  # IP сервера
HOST = '192.168.1.100'  # IP сервера
PORT = 12345          # Порт сервера

# Создаем сокет
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen(5)

print(f"Сервер запущен на {HOST}:{PORT}. Ожидание подключений...")

while True:
    # Принимаем подключение от клиента
    client_socket, client_address = server_socket.accept()
    print(f"Подключен клиент: {client_address}")

    while True:
        # Получаем данные от клиента
        data = client_socket.recv(1024)
        if not data:
            #print(f"Клиент {client_address} отключился.")
            client_socket.close()
            break

        # Декодируем данные и удаляем лишние пробелы
        received_data = data.decode().strip()
        #print(f"Получено от {client_address}: {received_data}")
        print(received_data)
        # Сохраняем данные в файл id.txt
        with open("id.txt", "w") as file:  # 'a' - режим добавления в файл
            file.write(received_data)  # Добавляем новую строку после каждого значения

    client_socket.close()