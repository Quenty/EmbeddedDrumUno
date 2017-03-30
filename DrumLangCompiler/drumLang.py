inputFile = r"input.txt"
outputFile = r"output.txt"

stickHit = {1:65, 2:65}

fin = open(inputFile)
#ftemp = open('temp.txt', 'w')
fout = open(outputFile, 'w')

input = fin.readline().split(',')
beats = list(map(lambda x: int(x), input))

for i in range(len(beats) - 1):
    beats[i + 1] = beats[i] + beats[i + 1]
#ftemp.writelines(map(lambda x: str(x) + ', ',beats))


stick = 1
def switchStick():
    global stick
    stick = 2 if stick == 1 else 1

output = []
otherStickTime = 0
for i, beat in enumerate(beats):
    if(i == len(beats) - 1):
        hitDelay = stickHit[stick]
    else:
        hitDelay = beats[i + 1] - beat

    if(hitDelay >= stickHit[stick]):                                 #case beats far apart
        output.append(stick)                                        #stick down
        output.append(0)
        output.append(otherStickTime if otherStickTime else stickHit[stick])  

        if(otherStickTime):
            switchStick()

            output.append(stick)     #other stick up
            output.append(1)
            output.append(stickHit[stick] - otherStickTime)

            switchStick()
            otherStickTime = 0

        output.append(stick)         #stick up
        output.append(1)
        output.append(hitDelay - stickHit[stick])

        switchStick()
    else:                                                           #case beats close
        output.append(stick)                           #stick down
        output.append(0)
        output.append(hitDelay)

        otherStickTime = stickHit[stick] - hitDelay
        switchStick()


output = list(map(lambda x: str(x),output))
output = ', '.join(output)
output = '{' + output + '}'
fout.writelines(output)
