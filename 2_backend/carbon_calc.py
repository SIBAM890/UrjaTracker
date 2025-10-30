# Emission factors (example data, in kg CO2 per unit)
# These should be researched for accuracy
EMISSION_FACTORS = {
    "drive_car_km": 0.17,    # kg CO2 per km (average petrol car)
    "use_ac_hour": 0.6,      # kg CO2 per hour (average 1.5-ton AC)
    "flight_hour": 90.0      # kg CO2 per hour of flying
}

def calculate_carbon(activity_type, value):
    """
    Calculates the CO2 emission for a given activity.
    Returns: co2_kg (float) or None if activity is unknown
    """
    factor = EMISSION_FACTORS.get(activity_type)
    if factor:
        return factor * float(value)
    return None