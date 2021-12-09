import mido
import serial

ser = serial.Serial('COM5')

mid = mido.MidiFile('\Raspberry_Pi\midi_examples\test_double_note.mid')

# checks for double notes in MIDI file
note_playing = False
double_note = False
for msg in mid:
    if msg.type == 'note_on':
        if note_playing:
            double_note = True
        else:
            note_playing = True
    elif msg.type == 'note_off':
        note_playing = False
    else:
        pass

print(f"More than 1 note playing at once: {double_note}")

# checks for out of range notes in MIDI file
out_of_range_note = False
for msg in mid:
    if msg.type == 'note_on':
        if msg.note < 72 or msg.note > 86:
            out_of_range_note = True

print(f"Notes out of range: {out_of_range_note}")

confirm_play = 'y'
if double_note or out_of_range_note:
    confirm_play = input("There are problems with the MIDI file, would you still like to continue? (y/n) \n").lower()

if confirm_play == 'y':
    print("Playing song now... great choice!")
    for msg in mid.play():
        ser.write(msg.bin())