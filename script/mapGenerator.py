from random import randint

dirPath = "../music/"

songId = input("ID : ")
songName = input("Name : ")
songComposer = input("Composer : ")
songPath = input("Path : ")
BPM = int(input("BPM : "))
offset = float(input("offset : "))
s = input("Length : ")
speed = int(input("Speed : "))

sl = s.split(':')
songLength = float(sl[0]) + float(sl[1])/60 - offset/60

fichier = open(dirPath + songId + "/" + songId + ".mnm", "w")

fichier.write("Name=" + songName + "\n")
fichier.write("Composer=" + songComposer + "\n")
fichier.write("Path=" + songPath + "\n")
fichier.write("BPM=" + str(BPM) + "\n")
fichier.write("Length=" + s + "\n")

fichier.write("DATA\n")

for i in range(int(BPM * songLength)):
  fichier.write(str(offset + 60/BPM * i) + " " + str(offset + 60/BPM * (i+0.5)) + " " + str(speed) + " " + str(randint(0,7)) + "\n")
 