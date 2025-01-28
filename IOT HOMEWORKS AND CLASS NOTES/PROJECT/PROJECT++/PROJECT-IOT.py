import serial
import time
import face_recognition
import cv2
import os
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
                return [self.serial_conn.readline().decode('utf-8').strip()]
            except Exception as e:
                print("Error reading data:", e)
                return []
        else:
            print("Serial port is not open.")
            return []

def load_known_faces(known_faces_dir):
    known_face_encodings = []
    known_face_names = []

    for filename in os.listdir(known_faces_dir):
        if filename.endswith(".jpg") or filename.endswith(".png"):
            image_path = os.path.join(known_faces_dir, filename)
            try:
                image = face_recognition.load_image_file(image_path)
                encoding = face_recognition.face_encodings(image)[0]
                known_face_encodings.append(encoding)
                known_face_names.append(os.path.splitext(filename)[0])
            except Exception as e:
                print(f"Error processing image {filename}: {e}")
    return known_face_encodings, known_face_names

def is_face_recognized(known_face_encodings, known_face_names):
    with cv2.VideoCapture(0) as cap:
        ret, frame = cap.read()
        if not ret:
            print("Failed to capture image")
            return None

        rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        face_locations = face_recognition.face_locations(rgb_frame)
        face_encodings = face_recognition.face_encodings(rgb_frame, face_locations)

        for face_encoding in face_encodings:
            matches = face_recognition.compare_faces(known_face_encodings, face_encoding)
            if True in matches:
                first_match_index = matches.index(True)
                return known_face_names[first_match_index]
    return None

def process_message_with_gpt(message, llm):
    try:
        gpt_response = llm.invoke(message)
        if gpt_response and gpt_response.content:
            return gpt_response.content.strip()
    except Exception as e:
        print("Error communicating with GPT:", e)
    return None

def main():
    llm = ChatOpenAI(
        model="gpt-3.5-turbo",
        base_url="https://api.avalai.ir/v1",
        api_key="aa-T4R8oAhtwgHWuW5f8pR6GEJW7monkuawil1yWlbq1olw5Wgn"
    )

    port_name = "COM3"
    serial_comm = SerialCommunication(port_name)

    while not serial_comm.open_serial_port():
        print("Can't connect to serial, reconnecting in 5 seconds.")
        time.sleep(5)

    print("***************Connected*****************")
    known_faces_dir = "known_faces"
    known_face_encodings, known_face_names = load_known_faces(known_faces_dir)

    system_message = {
        "role": "system",
        "content": """You are an assistant for an IoT system that 
                      controls LED lights. Based on the user's prompt, you must decide which 
                      function to call for controlling the lights. 
                      The function options are: 
                      A: turning on the light number 1, 
                      B: turning off the light number 1, 
                      C: turning on the light number 2, 
                      D: turning off the light number 2.
                      E: turning on the light number 1 and 2,
                      F: turning off the light number 1 and 2.
                      You must only respond with a single character (A, B, C, D, E, or F) 
                      corresponding to the function. DO NOT add any other information or text."""
    }

    recognized_name = is_face_recognized(known_face_encodings, known_face_names)
    if recognized_name:
        print(f"Face recognized: {recognized_name}")

    try:
        while True:
            data = serial_comm.read_data()
            for line in data:
                if line.startswith("Prompt received:"):
                    prompt = line.split("Prompt received:")[1].strip()
                    user_message = {"role": "user", "content": prompt}
                    message = [system_message, user_message]

                    gpt_response = process_message_with_gpt(message, llm)

                    if gpt_response in ["A", "B", "C", "D", "E", "F"]:
                        serial_comm.write_data(gpt_response)
                    else:
                        print(f"Invalid GPT response: {gpt_response}")

            time.sleep(1)
    except KeyboardInterrupt:
        print("Exiting...")
    finally:
        serial_comm.close_serial_port()

if __name__ == "__main__":
    main()
