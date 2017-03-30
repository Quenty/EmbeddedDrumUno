from mido import MidiFile

mid = MidiFile('RhythmAndDrums.mid')
commands = []
for i, track in enumerate(mid.tracks):
    # print('Track {}: {}'.format(i, track.name))
    for msg in track:
        print(msg)
        if not msg.is_meta:
            #print(msg)
            #print(msg.type)
            if msg.type == 'note_on':
                commands += [msg.time]

print('{' + ','.join(map(str, commands)) + '}')