# URJA TRACKER Full-Stack IoT System 
# URJA-TRACKER: Smart Classroom & Carbon Monitor

This is the source code for a full-stack IoT project that monitors and controls a smart classroom prototype, tracks energy consumption, and provides a web-based dashboard for live data and personal carbon tracking.

This project is built on a 3-tier architecture.

## Architecture

1.  **`1_firmware/` (Embedded C++)**
    * **Device:** Arduino Uno
    * **Code:** Reads from PIR, LDR, DHT11, and ACS712 sensors.
    * **Logic:** Controls light and fan relays based on sensor thresholds.
    * **Output:** Sends a complete JSON data packet over the USB Serial port every 2 seconds.

2.  **`2_backend/` (Python)**
    * **Framework:** Flask
    * **Code:** A multi-threaded web server that:
        1.  Runs a background thread to continuously read JSON from the Arduino's serial port.
        2.  Provides a web API for the frontend.
        3.  Manages a SQLite database for the personal carbon tracker.

3.  **`3_webapp/` (HTML/CSS/JavaScript)**
    * **Framework:** Vanilla JS, HTML5, CSS3 (with Chart.js)
    * **Code:** A static website that runs in the user's browser.
    * **Features:**
        * **Live Dashboard:** Polls the backend's `/api/live_data` endpoint to show real-time sensor readings and energy charts.
        * **Personal Tracker:** Provides a full CRUD (Create, Read, Delete) interface for a personal carbon log, saving data to the backend's database.

## How to Run

You must run all three parts simultaneously.

### 1. Run the Firmware

1.  Assemble the circuit according to `docs/circuit_diagram.png` and `docs/pin_mapping.txt`.
2.  Open the `1_firmware/` folder in the Arduino IDE.
3.  Install the required libraries (ArduinoJson, DHT library, Adafruit Unified Sensor).
4.  Connect your Arduino and upload the `urja_tracker.ino` sketch.
5.  **DO NOT** open the Serial Monitor (the Python backend needs access to the port).

### 2. Run the Backend

1.  Open a terminal and navigate to the `2_backend/` directory.
2.  **Setup (First time only):**
    * Create a virtual environment: `python -m venv venv`
    * Activate it: `.\venv\Scripts\activate` (Windows) or `source venv/bin/activate` (Mac/Linux)
    * Install dependencies: `pip install -r requirements.txt`
3.  **Find your Arduino Port:**
    * Check your Arduino IDE or Windows Device Manager to find its COM port (e.g., `COM3`, `COM4`).
4.  **Configure:**
    * Open the `.env` file and change `COM_PORT=COM3` to match your port.
5.  **Run:**
    * While in your activated virtual environment, run: `python main.py`
    * You should see output indicating the Flask server is running and the serial thread has started.

### 3. Run the Frontend

1.  No server is needed for the frontend.
2.  Navigate to the `3_webapp/` folder.
3.  **Double-click `index.html`** to open it in your default web browser (e.g., Chrome, Firefox).
4.  Navigate to the "Live Dashboard" to see data streaming from your Arduino, or "My Tracker" to log your personal footprint.