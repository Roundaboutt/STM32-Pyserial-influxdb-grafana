## 1.简介

本项目使用STM32检测空气与土壤温湿度，控制空气加湿器与水泵，并将数据通过串口与python通信。使用pyserial读取数据并将其写入influxdb，上传至grafana实现实时监控



当空气湿度低于70时打开空气加湿器，当土壤湿度低于70时打开水泵

## 2.开启influxdb

在命令行窗口输入

D:\Graduation Project\influxdb_grafana_python_stm32\influxdb-1.8.9-1 

influxd -config influxdb.conf

D:\Graduation Project\influxdb_grafana_python_stm32\influxdb-1.8.9-1 

influx

注意:要一直保持命令行窗口开启

## 3.开启Grafana

D:\Graduation Project\influxdb_grafana_python_stm32\grafana-10.0.0\bin 

grafana-server.exe

登录 http://本机ip:3000
