oddNumbers = [1,3,5,7,9]
evenNumbers = [0,2,4,6,8]
decNum = []
binNum = []
counter = 0
keepGoing = 1
def isOddNumber(num):
	return oddNumbers.count(num)
def isEvenNumber(num):
	return evenNumbers.count(num)
def addCarry(num,carry):
	if carry == 0:
		num = num
	elif carry == 5:
		if num == 0:
			num = 5
		elif num == 1:
			num = 6
		elif num == 2:
			num = 7
		elif num == 3:
			num = 8
		elif num == 4:
			num = 9
	return num
def halving(num):
	if num == 0 or num == 1:
		return 0
	elif num == 2 or num == 3:
		return 1
	elif num == 4 or num == 5:
		return 2
	elif num == 6 or num == 7:
		return 3
	elif num == 8 or num == 9:
		return 4
def secondStep(numArray):
	for x in range(len(numArray)-2,-1,-1):
		if isOddNumber(numArray[x]):
			numArray[x] = halving(numArray[x])
			counter = 5
			numArray[x+1] = addCarry(numArray[x+1],counter)
		elif isEvenNumber(numArray[x]):
			numArray[x] = halving(numArray[x])
			counter = 0
			numArray[x+1] = addCarry(numArray[x+1],counter)

#Begin process
inp = raw_input("Ingresa un numero: ")
#First step
for x in inp:
	try:
		x = int(x)
		decNum.append(x)
	except ValueError:
		print("Eso no es un numero!")
		exit(0)
decNum.append(0)
#Second Step
while keepGoing:
	secondStep(decNum)
	if decNum[0] == 0:
		decNum.remove(0)
	if decNum[-1] == 0:
		binNum.append(0)
	elif decNum[-1] == 5:
		binNum.append(1)
	print ("Numero decimal (primera cinta): ", print(decNum))
	print ("Numero binario (segunda cinta): ", print(binNum))
	print ("")
	decNum[-1] = 0
	if len(decNum) == 1:
		keepGoing = 0