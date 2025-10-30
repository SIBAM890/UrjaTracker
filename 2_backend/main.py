# Flask backend server 
import threading
import os
from flask import Flask, jsonify, request
from flask_cors import CORS
from dotenv import load_dotenv
import database
import serial_reader
import carbon_calc

# --- 1. INITIALIZATION ---

# Load environment variables from .env file
load_dotenv()

# Create Flask app
app = Flask(__name__)
# Enable CORS (Cross-Origin Resource Sharing) for our webapp
# This is ESSENTIAL for the frontend to talk to the backend.
CORS(app) 

# Initialize the SQLite database
database.init_db()

# --- 2. BACKGROUND THREAD (Hardware Link) ---

# Start the serial reader in a separate background thread.
# 'daemon=True' means the thread will exit when the main app exits.
print("Starting serial reader thread...")
serial_port = os.getenv('COM_PORT', 'COM3')
baud_rate = int(os.getenv('BAUD_RATE', 9600))
reader_thread = threading.Thread(
    target=serial_reader.read_from_port,
    args=(serial_port, baud_rate),
    daemon=True
)
reader_thread.start()
print(f"Background thread started for {serial_port} at {baud_rate} baud.")


# --- 3. API ENDPOINTS (Frontend Link) ---

@app.route('/')
def index():
    return "URJA-TRACKER Backend is running. Access /api/live_data for hardware status."

# [Requirement #2] API Endpoint for URJA TRACKER Dashboard
@app.route('/api/live_data', methods=['GET'])
def get_live_data():
    """Returns the latest data packet received from the Arduino."""
    with serial_reader.data_lock:
        # Return the globally updated 'latest_data'
        return jsonify(serial_reader.latest_data)

# [Requirement #1 & #3] API Endpoints for Personal Carbon Tracker
@app.route('/api/personal_carbon', methods=['GET'])
def get_personal_logs():
    """Returns all personal carbon logs."""
    logs = database.get_logs()
    return jsonify(logs)

@app.route('/api/personal_carbon', methods=['POST'])
def add_personal_log():
    """Adds a new personal carbon log."""
    data = request.get_json()
    
    activity = data.get('activity')
    value = data.get('value')
    unit = data.get('unit')

    # Calculate CO2
    co2_kg = carbon_calc.calculate_carbon(activity, value)
    if co2_kg is None:
        return jsonify({"error": "Invalid activity type"}), 400

    # Add to database
    database.add_log(activity, value, unit, co2_kg)
    return jsonify({"success": True, "message": "Log added."}), 201

@app.route('/api/personal_carbon/<int:log_id>', methods=['DELETE'])
def delete_personal_log(log_id):
    """Deletes a personal log by its ID."""
    database.delete_log(log_id)
    return jsonify({"success": True, "message": "Log deleted."})


# --- 4. RUN THE APPLICATION ---
if __name__ == '__main__':
    # 'debug=True' reloads the server on code changes
    # 'use_reloader=False' is important to prevent running the serial thread twice
    print("Starting Flask web server...")
    app.run(debug=True, use_reloader=False, host='127.0.0.1', port=5000)