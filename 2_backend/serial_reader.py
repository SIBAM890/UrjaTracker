# Serial data reader 
import serial
import json
import threading
import time
import os

# This is a global variable (and a lock) to store the latest data
# The main Flask app will read from this.
latest_data = {}
data_lock = threading.Lock()

def read_from_port(port, baud):
    """
    Runs in a background thread to continuously read from the serial port.
    Updates the global 'latest_data' variable.
    """
    global latest_data, data_lock
    
    while True:
        print(f"Attempting to connect to serial port {port}...")
        try:
            with serial.Serial(port, baud, timeout=2) as ser:
                print(f"Successfully connected to {port}.")
                while True:
                    if not ser.is_open:
                        print("Serial port closed. Reconnecting...")
                        break
                    try:
                        line = ser.readline().decode('utf-8').strip()
                        if line:
                            # We expect a JSON string from the Arduino
                            data = json.loads(line)
                            with data_lock:
                                latest_data = data
                            # print(f"Received data: {data}") # Uncomment for debugging
                    except json.JSONDecodeError:
                        print(f"Warning: Received invalid JSON. Line: '{line}'")
                    except serial.SerialException as e:
                        print(f"Serial error: {e}. Reconnecting...")
                        break
                    except Exception as e:
                        print(f"An error occurred: {e}")
                        
        except serial.SerialException as e:
            print(f"Error: Could not connect to {port}. {e}. Retrying in 5 seconds...")
            with data_lock:
                latest_data = {"error": f"Failed to connect to {port}. Is it plugged in?"}
            time.sleep(5) # Wait before retrying