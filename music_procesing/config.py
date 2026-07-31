

# config.py

# Audio capture

WINDOW_SIZE = 1024

# MQTT

MQTT_BROKER = "192.168.60.6"
MQTT_PORT = 1883
MQTT_USERNAME = "MusicBox"
MQTT_PASSWORD = "HilliardMusicBox"

# Processing

SMOOTHING = 0.7
BEAT_SENSITIVITY = 1.8
# config.py

# Audio capture

LOOPBACK_DEVICE = 2   # Change this to your loopback device index
WINDOW_SIZE = 2048

# MQTT

MQTT_BROKER = "192.168.60.6"
MQTT_PORT = 1883
MQTT_USERNAME = "MusicBox"
MQTT_PASSWORD = "HilliardMusicBox"




# =========================
# FFT Frequency Bands
# =========================

BASS_RANGE = (40, 180)

LOW_MID_RANGE = (180, 600)

MID_RANGE = (600, 3000)

TREBLE_RANGE = (3000, 10000)
