import math

output = "Treetop.mesh"

positions = []
colors = []
normals = []
botFan = []
triStrip = []

segCount = 100	#The higher this is, the smoother the circle
colorRepeatCount = 1  #How many times the colour patterns get repeated

angleDelta = 3.14159 * 2.0 / segCount
colorAngleDelta = 3.14159 * 2.0 / colorRepeatCount
highColor = (0.0, 0.8, 0.0, 1.0)
lowColor = (0.0, 0.5, 0.0, 1.0)

#Compute Bottom Cap
positions.append((0.0, -0.5, 0.0))
colors.append(lowColor)
normals.append((0.0, -1.0, 0.0))
botFan.append(0)

for iSeg in range(segCount):
	iAngle = iSeg * angleDelta
	
	positions.append(((0.5 * math.cos(iAngle)), -0.5, -0.5 * math.sin(iAngle)))
	
	normals.append((0.0, -1.0, 0.0))
	
	dist = math.fmod(iAngle, colorAngleDelta) / colorAngleDelta
	if (dist > 0.5):
		interp = (dist - 0.5) * 2.0
		colors.append(tuple(interp * x + (1.0 - interp) * y for x, y in zip(highColor, lowColor))) #grr python for not having tuple-scalar multiplication
	else:
		interp = dist * 2.0
		colors.append(tuple(interp * x + (1.0 - interp) * y for x, y in zip(lowColor, highColor)))
		
	botFan.append(1 + iSeg)

botFan.append(botFan[1])

#Compute Sides
positions.append((0.0, 0.5, 0.0))
positionIndex = len(positions) - 1
colors.append(highColor)
normals.append((0.0, 1.0, 0.0))

for iSeg in range(segCount):
	iAngle = iSeg * angleDelta

	triStrip.append(positionIndex)

	positions.append(((0.5 * math.cos(iAngle)), -0.5, 0.5 * math.sin(iAngle)))
	
	normals.append((math.cos(iAngle), 0, math.sin(iAngle)))
	
	dist = math.fmod(iAngle, colorAngleDelta) / colorAngleDelta
	if (dist > 0.5):
		interp = (dist - 0.5) * 2.0
		colors.append(tuple(interp * x + (1.0 - interp) * y for x, y in zip(highColor, lowColor)))
	else:
		interp = dist * 2.0
		colors.append(tuple(interp * x + (1.0 - interp) * y for x, y in zip(lowColor, highColor)))

	triStrip.append(len(positions) - 1)
	
triStrip.append(triStrip[0])
triStrip.append(triStrip[1])

with open("../" + output, "w") as text_file:
	print("position", file=text_file)
	for i in positions:
		print(i[0], i[1], i[2], file=text_file)
		
	print("", file=text_file)
	
	print ("color", file=text_file)
	for i in colors:
		print(i[0], i[1], i[2], i[3], file=text_file)

	print("", file=text_file)

	print("normal", file=text_file)
	for i in normals:
		print(i[0], i[1], i[2], file=text_file)

	print("", file=text_file)
	
	print("primitive\ntrifan", file=text_file)
	for i in botFan:
		print(i, end=" ", file=text_file)
		
	print("\n", file=text_file)
	
	print("primitive\ntristrip", file=text_file)
	for i in triStrip:
		print(i, end=" ", file=text_file)