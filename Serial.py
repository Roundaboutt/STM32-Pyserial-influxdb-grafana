import serial
from influxdb import InfluxDBClient

host, port = "192.168.1.101", 8086
# 如果没有开启用户名和密码，则不需要填写这两个参数

username, password = "admin", "symantec9098"
database = "STM32"
client = InfluxDBClient(host=host, username=username, port=port, database=database, password=password)
client.drop_database(database)
client.create_database('STM32')
# 连接串口
serial = serial.Serial('COM5', 9600, timeout=2)
if serial.isOpen():
    print('串口已打开')

    while True:
        i = 0
        data = serial.read(5)
        if data[0] == 84:
            Temperature = (data[1] - 48) * 10 + (data[2] - 48) + (data[3] - 48) * 0.1
            points = [
                {
                    'measurement': 'table2',
                    'time': '2024-4-18T14:12:00Z',
                    'fields': {
                        'Temperature': Temperature
                    }
                },
            ]

            client.write_points(points, database=database)
            print(f"Temperature is :", Temperature)
        if data[0] == 72:
            AirHumidity = (data[1] - 48) * 10 + (data[2] - 48) + (data[3] - 48) * 0.1
            points = [
                {
                    'measurement': 'table2',
                    'time': '2024-4-11T20:55:00Z',
                    'fields': {
                        'AirHumidity': AirHumidity
                    }
                },
            ]

            client.write_points(points, database=database)
            print("AirHumidity is :", AirHumidity)
        if data[0] == 83:
            SoilHumidity = (data[1] - 48) * 10 + (data[2] - 48) + (data[3] - 48) * 0.1 + (data[3] - 48)*0.01
            points = [
                {
                    'measurement': 'table2',
                    'time': '2024-4-11T12:37:00Z',
                    'fields': {
                        'SoilHumidity': SoilHumidity
                    }
                },
            ]
            client.write_points(points, database=database)
            print("SoilHumidity is :", SoilHumidity)
else:
    print('串口未打开')

# 关闭串口
serial.close()

if serial.isOpen():
    print('串口未关闭')
else:
    print('串口已关闭')
