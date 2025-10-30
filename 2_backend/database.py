# Database CRUD operations 
import sqlite3
import os

DB_FILE = os.path.join(os.path.dirname(__file__), 'db', 'personal_tracker.db')
DB_DIR = os.path.join(os.path.dirname(__file__), 'db')

# Ensure the 'db' directory exists
os.makedirs(DB_DIR, exist_ok=True)

def get_db_connection():
    """Establishes a connection to the SQLite database."""
    conn = sqlite3.connect(DB_FILE)
    conn.row_factory = sqlite3.Row
    return conn

def init_db():
    """Initializes the database and creates the table if it doesn't exist."""
    print(f"Initializing database at {DB_FILE}")
    try:
        conn = get_db_connection()
        with conn:
            conn.execute('''
                CREATE TABLE IF NOT EXISTS personal_logs (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                    activity_type TEXT NOT NULL,
                    value REAL NOT NULL,
                    unit TEXT NOT NULL,
                    co2_kg REAL NOT NULL
                )
            ''')
        print("Database initialized successfully.")
    except sqlite3.Error as e:
        print(f"An error occurred during DB initialization: {e}")

def add_log(activity_type, value, unit, co2_kg):
    """Adds a new personal log to the database."""
    conn = get_db_connection()
    with conn:
        conn.execute(
            'INSERT INTO personal_logs (activity_type, value, unit, co2_kg) VALUES (?, ?, ?, ?)',
            (activity_type, value, unit, co2_kg)
        )
    return True

def get_logs():
    """Fetches all personal logs from the database."""
    conn = get_db_connection()
    with conn:
        logs = conn.execute('SELECT * FROM personal_logs ORDER BY created_at DESC').fetchall()
        # Convert sqlite3.Row objects to standard dicts for JSON serialization
        return [dict(log) for log in logs]

def delete_log(log_id):
    """Deletes a specific log by its ID."""
    conn = get_db_connection()
    with conn:
        conn.execute('DELETE FROM personal_logs WHERE id = ?', (log_id,))
    return True