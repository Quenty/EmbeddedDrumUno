from mido import MidiFile
from collections import defaultdict
import sys

from drumLang import makeHeader


def compile(filename):
	infile = 'Midi/{}.mid'.format(filename)
	outfile = 'Patterns/{}.txt'.format(filename)

	mid = MidiFile(infile)
	commands = defaultdict(lambda:[])
	for i, track in enumerate(mid.tracks):
	    print('Track {}: {}'.format(i, track.name))
	    current_time = 0
	    for message in track:
	        if message.time:
	            current_time += message.time

	        if message.type=='note_on' and message.velocity:  #if ur hitting
	            commands[message.note].append(current_time)

	patterns = [commands[key] for key in sorted(commands.keys())]

	open(outfile, 'w').write('\n'.join(', '.join(map(str, pattern)) for pattern in patterns))




if not sys.argv:
	print('use files as command line arguements')
	print('for example: python MidiReader.py Jazz12 RythmAndDrums')

else:
	print('compiling to drumLang...')
	compile(sys.argv[1])
	print()
	print('file', sys.argv[1], 'compiled')

	print('generating header file...')
	makeHeader('patterns/{}.txt'.format(sys.argv[1]))
	print('header generated')
	


