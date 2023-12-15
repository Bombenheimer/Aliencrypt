#!/usr/bin/env python

import os
import time
from cryptography.fernet import Fernet as fernet

# USER INTERFACE

os.system("clear")

logo = """
  dBBBBBb     dBP    dBP dBBBP  dBBBBb  dBBBP dBBBBBb dBP dBP dBBBBBb dBBBBBBP
       BB                          dBP            dBP    dBP      dB'         
   dBP BB   dBP    dBP dBBP   dBP dBP dBP     dBBBBK    dBP   dBBBP'   dBP    
  dBP  BB  dBP    dBP dBP    dBP dBP dBP     dBP  BB   dBP   dBP      dBP     
 dBBBBBBB dBBBBP dBP dBBBBP dBP dBP dBBBBP  dBP  dB'  dBP   dBP      dBP      

                                ᴀʟɪᴇɴᴄʀʏᴘᴛ
                        [~ᴘʀᴏɢʀᴀᴍ ʙʏ ʙᴏᴍʙᴇɴʜᴇɪᴍᴇʀ~]
"""

options = """
  Select an option:

    [0] - Encrypt
    [1] - Show Files
    [2] - File Information
    [3] - Exit
"""

for char in logo:
    print(char, end='', flush=True)
    time.sleep(0.01)

print()

path = input("  Specify File Path: ")

print("\n")

# FIND ALL FILES THROUGH CHOSEN DIRECTORY AND ADD THEM TO A LIST

file_bin = []

for root, dirs, files in os.walk(path):
	for file in files:
		if file == "Aliencrypt.py" or file == "Aliencrypt":
			continue
		file_path = os.path.join(root, file)
		file_bin.append(file_path)

for char in options:
    print(char, end='', flush=True)
    time.sleep(0.01)

print()

# USER OPTIONS; ENCRYPT, SHOW FILES, SHOW FILE INFO, EXIT

def user_options():
    choice = input("root@aliencrypt:~#")
    if choice == "0":
        os.system("clear")
        time.sleep(3)
        encrypt_options = f"""
                                  Are you sure you want to encrypt?
                                    This action cannot be undone.
                        
            Path: {path}

            [y] - Yes
            [n] - No 
            [b] - Back to options

        """
        for char in encrypt_options:
            print(char, end='', flush=True)
            time.sleep(0.01)

        decision = input("root@aliencrypt:~#")
        if decision == "y":
            key = fernet.generate_key()
            f = fernet(key)
            for paper in file_bin:
                with open(paper, 'rb') as thefile:
                    contents = thefile.read()
                contents_encrypted = f.encrypt(contents)
                with open(paper, 'wb') as thefile:
                    thefile.write(contents_encrypted)
            os.system("clear")
            msg = """
            
                                                              
                                        Encryption Finished!!!
                                                              
            """
            for char in msg:
                print(char, end='', flush=True)
                time.sleep(0.01)
            print()
            exit()
        elif decision == "n":
            exit()
        elif decision == "b":
            os.system("clear")
            time.sleep(1)
            for char in options:
                print(char, end='', flush=True)
                time.sleep(0.01)
            print()
            user_options()
        else:
            print()
            print("\tIncorrect input, try again.")
            print()
            exit()

    elif choice == "1":
        os.system("clear")
        time.sleep(3)
        list_length = len(file_bin)
        increment = 0
        subtitle = """
                                            File List
        """
        for char in subtitle:
            print(char, end='', flush=True)
            time.sleep(0.01)
        print()
        while increment < list_length:
            print(f"{os.path.basename(file_bin[increment])}\n", end='', flush=True)
            time.sleep(0.01)
            increment += 1
        exit()

    elif choice == "2":
        os.system("clear")
        time.sleep(3)

        archive = ['.7z','.ace','.alz','.arc','.arj','.bz','.bz2','.cab','.cpio','.deb','.dmg','.gz','.img',
                '.iso','.jar','.lha','.lz','.lzma','.lzo','.rar','.rpm','.rz','.tar','.tar.7z','.tar.bz',
                '.tar.bz2','tar.gz','.tar.lzo','.tar.xz','.tar.z','.tbz','.tbz2','.tgz','.tz','.tzo','.xz',
                '.z','.zip']
        audio = ['.aac','.ac3','.aif','.aifc','.aiff','.amr','.au','.caf','.flac','.m4a','.m4b','.mp3',
                '.oga','.voc','.wav','.weba','.wma']
        cad = ['.dwg','.dxf']
        document = ['.abw','.djvu','.doc','.docm','.docx','.dot','.dotx','.html','.hwp','.lwp','.md',
                '.odt','.pages','.pdf','.rst','.rtf','.tex','.txt','.wpd','.wps','.zabw']
        ebook = ['.azw','.azw3','.azw4','.cbc','.cbr','.cbz','.chm','.epub','.fb2','.htm','.htmlz','.lit',
                'lrf','mobi','.pdb','.pml','.prc','.rb','.snb','.tcr','.txtz']
        font = ['.eot','.otf','.ttf','.woff','.woff2']
        image = ['.3fr','.arw','.avif','.bmp','.cr2','.cr3','.crw','.dcr','.dng','.eps','.erf','.gif',
                '.heic','.heif','.icns','.ico','.jfif','.jpeg','.jpg','.mos','.mrw','.nef','.odd','.odg',
                '.orf','.pef','.png','.ppm','.ps','.psd','.raf','.raw','.rw2','.tif','.tiff','.webp',
                '.x3f','.xcf','.xps']
        presentation = ['.dps','.key','.odp','.pot','.potx','.pps','.ppsx','.ppt','.pptm','pptx']
        spreadsheet = ['.csv','.et','.ods','.xls','.xlsm','.xlsx','.numbers']
        vector = ['.ai','.cdr','.cgm','.emf','.sk','.sk1','.svg','.svgz','.vsd','.wmf']
        video = ['.3g2','.3gp','.3gpp','.avi','.cavs','.dv','.dvr','.flv','.m2ts','.m4v','.mkv','.mod',
                '.mov','.mp4','.mpeg','.mpg','.mts','.mxf','.ogg','.rm','.rmvb','.swf','.ts','.vob','.webm',
                '.wmv','.wtv']
        script = ['.py','.c','.java','.sh','.cpp','.lol','.js','.asm']

        file_types = []

        for item in file_bin:
            name, file_extention = os.path.splitext(item)
            file_extention.lower() == file_extention.upper()
            file_types.append(file_extention)
    
            all_files_number = len(file_types)
            archive_number = sum(item in archive for item in file_types)
            audio_number = sum(item in audio for item in file_types)
            cad_number = sum(item in cad for item in file_types)
            document_number = sum(item in document for item in file_types)
            ebook_number = sum(item in ebook for item in file_types)
            font_number = sum(item in font for item in file_types)
            image_number = sum(item in image for item in file_types)
            presentation_number = sum(item in presentation for item in file_types)
            script_number = sum(item in script for item in file_types)
            spreadsheet_number = sum(item in spreadsheet for item in file_types)
            vector_number = sum(item in vector for item in file_types)
            video_number = sum(item in video for item in file_types)
    
        file_info = f"""
                                            File Information

        All Files: {all_files_number}
        Archive Files: {archive_number}
        Audio Files: {audio_number}
        Cad Files: {cad_number}
        Document Files: {document_number}
        Ebook Files: {ebook_number}
        Font Files: {font_number}
        Image Files: {image_number}
        Presentation Files: {presentation_number}
        Scripting Files: {script_number}
        Spreadsheet Files: {spreadsheet_number}
        Vector Files: {vector_number}
        Video Files: {video_number}
        """
        for char in file_info:
            print(char, end='', flush=True)
            time.sleep(0.01)

        print()
        exit()

    elif choice == "3":
        exit()

    else:
        print("Incorrect input, try again\n")
        user_options()
if __name__ == '__main__':
    user_options()
