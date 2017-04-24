from mido import MidiFile
from collections import defaultdict
from sys import argv

from DrumLangCompiler.drumLang import makeHeader


if not sys.arv:
	print('use files as command line arguements')
	print('for example: python MidiReader.py Jazz12 RythmAndDrums')

else:
	print('compiling to drumLang...')
	compile(sys.argv[0])
	print('file', arg, 'compiled')

	print('generating header file...')
	makeHeader('patterns/{}.txt'.format(sys.argv[0]))
	print('header generated')
	

def compile(filename):
	infile = 'Midi/{}.mid'.format(filename)
	outfile = 'Midi/' + '.'.join(infile.split('.')[:-1]) + '.txt'

	mid = MidiFile(infile)
	commands = defaultdict(lambda:[])
	for i, track in enumerate(mid.tracks):
	    print()
	    print('Track {}: {}'.format(i, track.name))
	    current_time = 0
	    for message in track:
	        print(message)
	        if message.time:
	            current_time += message.time

	        if message.type=='note_on' and message.velocity:  #if ur hitting
	            commands[message.note].append(current_time)

	for note, times in commands.items():
	    print(note, times)

	patterns = [commands[key] for key in sorted(commands.keys())]

	open(outfile, 'w').write('\n'.join(', '.join(map(str, pattern)) for pattern in patterns))
