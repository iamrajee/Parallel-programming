#print("hi\n")

f = open("report/simple/simple.txt", "r")
data = f.read()
#print(type(data), len(data))
splitdata = data.split("\n")
#print(splitdata)
l = len(splitdata) - 1
#print("l=",l)
splitdata = splitdata[:l]
#print(((splitdata[0].split("[")[1]).split("]")[0]).split(","))
x = [float(b.strip()) for b in ((splitdata[0].split("[")[1]).split("]")[0]).split(",")]
print("x=", x)
