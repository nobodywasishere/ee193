#!/usr/bin/env python

"""
## Data format for MQTT

| Bytes  | Description                  | If unused 
|--------|------------------------------|
| 0-7    | Time                         |
| 8-11   | Primary (sensor) temp        | -2^31
| 12-15  | Secondary (thermistor) temp  | -2^31
| 16     | Battery level                | 255
| 17-18  | Length of team data ()       | 0
| 19-22  | Latitude float               | 
| 23-26  | Longitude float              |
| 27-30  | String name of node          |
"""


import argparse
from numpy import int64
import serial
from paho.mqtt import client as mqtt
import time
from typing import List, Dict, Union
import struct
import toml
from pprint import pprint

def dataFormatter(line: bytes, mqtt_data: Union[dict, None] = None):
    l = str(line)[2:-5].split(' ')
    if len(l) < 2:
        return None, 255, 0.0, 0.0, ""
    node = str(l[0])
    temp = int(l[1])
    if mqtt_data is not None:
        try:
            d = mqtt_data['nodes'][node]
            lat = d["lat"]
            lng = d["long"]
            name = d["name"]
        except KeyError:
            print("\033[31;1mNode Not Found!\033[0m")
            lat, lng, name = 0.0, 0.0, ""
    else: 
        print("\033[31;1mDatabase Not Connected!\033[0m")
        lat, lng, name = 0.0, 0.0, ""
    return node, temp, lat, lng, name

def sendMQTTData(mqtt_cli, team, nodeID, temp, lat: float, lng: float, name):
    print("\n\033[33;1;4mSending Data To MQTT Server!\033[0m")
    # Set up the data formatting
    etime        = int(time.time())
    sec_temp     = -2**31
    batt         = -128
    team_length  = 8+len(name)
    formatd      = f"qiibhff{'s'*len(name)}"
    name_bytes   = [bytes(i, 'utf-8') for i in name]
    topic        = f"nodes/{team}/{nodeID} "

    print(f"Publishing to {topic}")
    
    # Pack the data that we just set up
    data = struct.pack(formatd, etime, temp, sec_temp, batt, team_length, lat, lng, *name_bytes)
    print("Unpacked data: ", struct.unpack(formatd, data))
    print("Packed data:", data)
    mqtt_cli.publish(topic, payload=data, qos=0, retain=False)
    print("\n")

def connectToMQTT(client_name, host_name, host_port=1883):
    mqtt_cli = mqtt.Client(client_name)
    print(f"Connecting to {host_name}")
    mqtt_cli.connect(host_name, port=host_port)
    return mqtt_cli

def main(args):
    line = b''
    
    while True:
        with serial.Serial(args.port, args.baud, timeout=1) as ser:
            line = ser.readline()
            if len(line) > 0:
                print(f"Received from UART: {line}")

        # get TOML file
        with open("data.toml","r") as datafile:
            data = toml.load(datafile)

        # process data
        node, temp, lat, lng, name = dataFormatter(line, data)
        if node is None: 
            continue

        print(f"\n\033[33;1;4mGot a valid message from node {name}!\033[0m")
        print(f"NodeID: \033[4m{node}\033[0m")
        print(f"Temperature: \033[4m{temp}ºC ({temp*1.8+32}ºF)\033[0m")
        print(f"\033[33mAppended From Database:\033[0m")
        print(f"Location: \033[4m{lat}, {lng}\033[0m")
        print(f"Node Name: \033[4m{name}\033[0m\n")

        client = connectToMQTT(args.client_name, args.server, args.server_port)
        # send data
        sendMQTTData(client, 'a', node, temp, lat, lng, name)

if __name__ == "__main__":
    
    parser = argparse.ArgumentParser()
    parser.add_argument('--port', type=str, help="Serial port", default="/dev/ttyACM0")
    parser.add_argument('--baud', type=int, help="Serial baud rate", default=115200)
    parser.add_argument('--client-name', type=str, help="Name for MQTT client", default="AA_BRIDGE")
    parser.add_argument('--server', type=str, default="127.0.0.1")
    parser.add_argument('--server-port', type=int, default=5000)
    parser.add_argument('--data-path', type=str, help="Path to .toml file containing node information", default="data.toml")
    args = parser.parse_args()
    main(args)
