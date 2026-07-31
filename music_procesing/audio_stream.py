# audio_stream.py

import soundcard as sc
import numpy as np
import queue
import threading


class AudioStream:
    
    #Captures the computer's output audio using SoundCard loopback.


    def __init__(self, chunk_size, sample_rate=48000):

        self.sample_rate = sample_rate
        self.chunk_size = chunk_size

        self.audio_queue = queue.Queue(maxsize=2)

        self.running = False
        self.thread = None

        speaker = sc.default_speaker()

        self.loopback = sc.get_microphone(
            id=speaker.id,
            include_loopback=True
        )


    def _capture_audio(self):

        with self.loopback.recorder(
            samplerate=self.sample_rate
        ) as recorder:

            while self.running:

                data = recorder.record(
                    numframes=self.chunk_size
                )

                # Stereo → Mono
                mono = np.mean(
                    data,
                    axis=1
                ).astype(np.float32)

                # Keep newest audio only
                if self.audio_queue.full():
                    try:
                        self.audio_queue.get_nowait()
                    except queue.Empty:
                        pass

                self.audio_queue.put(mono)


    def start(self):

        self.running = True

        self.thread = threading.Thread(
            target=self._capture_audio,
            daemon=True
        )

        self.thread.start()


    def stop(self):

        self.running = False

        if self.thread:
            self.thread.join(timeout=1)


    def is_active(self):

        return self.running


    def get_chunk(self):

        try:
            return self.audio_queue.get(timeout=1)
        except queue.Empty:
            return None