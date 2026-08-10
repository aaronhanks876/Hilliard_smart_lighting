import soundcard as sc

for speaker in sc.all_speakers():
    print(speaker)
    print("ID:", speaker.id)