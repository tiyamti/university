import serial
import time
from langchain_openai import ChatOpenAI

class SerialCommunication:
    def __init__(self, port, baud_rate=115200):
        self.port = port
        self.baud_rate = baud_rate
        self.serial_conn = None

    def open_serial_port(self):
        try:
            self.serial_conn = serial.Serial(self.port, self.baud_rate, timeout=1)
            self.serial_conn.dtr = False
            self.serial_conn.rts = False
            print("Serial port opened successfully.")
            return True
        except serial.SerialException as e:
            print("Failed to open serial port:", e)
            return False

    def close_serial_port(self):
        if self.serial_conn and self.serial_conn.is_open:
            self.serial_conn.close()
            print("Serial port closed.")

    def write_data(self, data):
        if self.serial_conn and self.serial_conn.is_open:
            self.serial_conn.write(data.encode('utf-8'))
        else:
            print("Serial port is not open.")

    def read_data(self):
        if self.serial_conn and self.serial_conn.is_open:
            try:
                lines = self.serial_conn.readlines()
                return [line.decode('utf-8').strip() for line in lines]
            except Exception as e:
                print("Error reading data:", e)
                return []
        else:
            print("Serial port is not open.")
            return []

if __name__ == "__main__":
    # Configure ChatOpenAI
    llm = ChatOpenAI(
        model="gpt-3.5-turbo",
        base_url="https://api.avalai.ir/v1",
        api_key="aa-T4R8oAhtwgHWuW5f8pR6GEJW7monkuawil1yWlbq1olw5Wgn"
    )

    port_name = "COM3"  # Replace with your port name
    serial_comm = SerialCommunication(port_name)

    while not serial_comm.open_serial_port():
        print("Can't connect to serial, reconnecting in 5 seconds.")
        time.sleep(5)

    print("***************Connected*****************")

    try:
        while True:
            data = serial_comm.read_data()
            for line in data:
                print("ESP32 says:", line)
                if line.startswith("prompt="):
                    prompt = line.split("prompt=")[1]
                    gpt_response = llm.invoke(prompt)
                    if gpt_response:
                        content = gpt_response.content
                        if content:
                            print(content)
                            serial_comm.write_data(content)
    except KeyboardInterrupt:
        print("Exiting...")
    finally:
        serial_comm.close_serial_port()
