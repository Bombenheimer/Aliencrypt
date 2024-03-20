#!/usr/bin/env python3

# IMPORTING NECESSARY MODULES
from os import geteuid, system, path, walk, rename
from sys import exit
from time import sleep
from cryptography.fernet import Fernet as fernet

# CHECK IF SCRIPT IS BEING RAN AS ROOT
def IsRoot():
    return geteuid() == 0

# PRINT WELCOME MESSAGE
def PrintWelcome(COLOR_1, COLOR_2):
    MSG = f"""{COLOR_1}
    dBBBBBb     dBP    dBP dBBBP  dBBBBb  dBBBP dBBBBBb dBP dBP dBBBBBb dBBBBBBP
        BB                          dBP            dBP    dBP      dB'
    dBP BB   dBP    dBP dBBP   dBP dBP dBP     dBBBBK    dBP   dBBBP'   dBP
   dBP  BB  dBP    dBP dBP    dBP dBP dBP     dBP  BB   dBP   dBP      dBP
  dBBBBBBB dBBBBP dBP dBBBBP dBP dBP dBBBBP  dBP  dB'  dBP   dBP      dBP

                            {COLOR_2}Aliencrypt
                [Program designed by Bombenheimer]
                            {COLOR_1}Version 2.0.0{COLOR_2}

    Press {COLOR_1}ENTER{COLOR_2} to continue.
    """
    USER_OPTIONS = f"""
    Select an option:
    
        {COLOR_1}[0]{COLOR_2}- Encrypt Files
        {COLOR_1}[1]{COLOR_2}- Show Files
        {COLOR_1}[2]{COLOR_2}- File Information
        {COLOR_1}[3]{COLOR_2}- Change Colors
        {COLOR_1}[4]{COLOR_2}- Exit
    """
    PROMPT_PATH = """
    Enter the full path to the directory you wish to test.
    """
    system("clear")

    for char in MSG:
        print(char, end='', flush=True)
        sleep(0.01)

    userCont = input("")
    print()

    for char in USER_OPTIONS:
        print(char, end='', flush=True)
        sleep(0.01)

    print()
    userOption = input("    Option: ")
    print()

    for char in PROMPT_PATH:
        print(char, end='', flush=True)
        sleep(0.01)

    print()
    userPath = input("    Path: ")
    print()

    return userOption, userPath

# COLLECT ALL FILES
def CollectFiles(userPath):
    file_list = []

    for root, dirs, files in walk(userPath):
        for file in files:
            if (file == "Aliencrypt.py"):
                continue
            full_file_path = path.join(root, file)
            file_list.append(full_file_path)

    return file_list

# OPTION 0: ENCRYPT ALL FILES
def EncryptFiles(file_list, userPath, COLOR_1, COLOR_2):
    encryption_key = fernet.generate_key()
    f = fernet(encryption_key)

    WARN_MSG = f"""
    Are you sure you want to encrypt all {COLOR_1}{len(file_list)}{COLOR_2} files?
            Files may become damaged.

        Path: {COLOR_1}{userPath}

        {COLOR_1}[y]{COLOR_2} - Yes
        {COLOR_1}[n]{COLOR_2} - No
    """
    PROMPT_MSG = f"""
    Would you like to create a {COLOR_1}decryption key{COLOR_2} to decrypt the files later?

        {COLOR_1}[y]{COLOR_2} - Yes
        {COLOR_1}[n]{COLOR_2} - No
    """
    for char in WARN_MSG:
        print(char, end='', flush=True)
        sleep(0.01)

    print()

    userChoice = input("    Option: ")

    match (userChoice):
        case "y":
            for file in file_list:
                with open(file, 'rb') as readfile:
                    file_contents = readfile.read()
                encrypted_contents = f.encrypt(file_contents)
                with open(file, 'wb') as writefile:
                    writefile.write(encrypted_contents)

            for file in file_list:
                name, file_extention = path.splitext(file)
                byte_name = name.encode("utf-8")
                encrypted_name = f.encrypt(byte_name)
                encrypted_name_str = encrypted_name.decode("utf-8")
                rename(f"{name}{file_extention}", f"{userPath}/{encrypted_name_str}{file_extention}")
        case "n":
            exit(0)
        case _:
            print("Incorrect input. Try again.")

    for char in PROMPT_MSG:
        print(char, end='', flush=True)
        sleep(0.01)

    print()
    userChoice = input("    Option:")
    print()

    match (userChoice):
        case "y":
            with open('alien.key', 'wb') as decryption_key:
                decryption_key.write(encryption_key)
        case "n":
            exit(0)
        case _:
            print("Incorrect Input. Try again")

    return 0

# OPTION 1: SHOW ALL FILES
def ShowFiles(file_list, COLOR_1, COLOR_2):
    list_length = len(file_list)

    TITLE = f"""
                                    {COLOR_1}File List{COLOR_2}
    """

    system("clear")

    for char in TITLE:
        print(char, end='', flush=True)
        sleep(0.01)

    print()

    for i in range(list_length):
        print(f"{COLOR_1}{i + 1}{COLOR_2}...............{path.basename(file_list[i])}\n", end='', flush=True)
        sleep(0.01)
        print()

    return 0

# OPTION 2: SHOW FILE INFORMATION IN NUMBERS
def ShowFileInfo(file_list, COLOR_1, COLOR_2):
    archive = ['.7z','.ace','.alz','.arc','.arj','.bz','.bz2','.cab','.cpio','.deb','.dmg','.gz',
               '.img','.iso','.jar','.lha','.lz','.lzma','.lzo','.rar','.rpm','.rz','.tar','.tar.7z','.tar.bz',
               '.tar.bz2','tar.gz','.tar.lzo','.tar.xz','.tar.z','.tbz','.tbz2','.tgz','.tz','.tzo','.xz','.z','.zip']

    audio = ['.aac','.ac3','.aif','.aifc','.aiff','.amr','.au','.caf','.flac','.m4a','.m4b','.mp3','.oga','.voc','.wav','.weba','.wma']

    cad = ['.dwg','.dxf']

    document = ['.abw','.djvu','.doc','.docm','.docx','.dot','.dotx','.html','.hwp','.lwp','.md',
                '.odt','.pages','.pdf','.rst','.rtf','.tex','.txt','.wpd','.wps','.zabw']

    ebook = ['.azw','.azw3','.azw4','.cbc','.cbr','.cbz','.chm','.epub','.fb2','.htm','.htmlz','.lit',
             'lrf','mobi','.pdb','.pml','.prc','.rb','.snb','.tcr','.txtz']

    font = ['.eot','.otf','.ttf','.woff','.woff2']

    image = ['.3fr','.arw','.avif','.bmp','.cr2','.cr3','.crw','.dcr','.dng','.eps','.erf','.gif',
             '.heic','.heif','.icns','.ico','.jfif','.jpeg','.jpg','.mos','.mrw','.nef','.odd','.odg',
             '.orf','.pef','.png','.ppm','.ps','.psd','.raf','.raw','.rw2','.tif','.tiff','.webp','.x3f','.xcf','.xps']

    presentation = ['.dps','.key','.odp','.pot','.potx','.pps','.ppsx','.ppt','.pptm','pptx']

    spreadsheet = ['.csv','.et','.ods','.xls','.xlsm','.xlsx','.numbers']

    vector = ['.ai','.cdr','.cgm','.emf','.sk','.sk1','.svg','.svgz','.vsd','.wmf']

    video = ['.3g2','.3gp','.3gpp','.avi','.cavs','.dv','.dvr','.flv','.m2ts','.m4v','.mkv','.mod',
             '.mov','.mp4','.mpeg','.mpg','.mts','.mxf','.ogg','.rm','.rmvb','.swf','.ts','.vob','.webm','.wmv','.wtv']

    script = ['.py','.c','.java','.sh','.cpp','.lol','.js','.asm','.cmd','.bat','.php','.lua','.ps1', '.vbs','.swift','.sql','.cs']

    binary = ['.exe','.out','.dll','.bin','.elf','.app','.apk','.so','.class','.jar','']

    configuration = ['.ini','.cfg','.conf','.properties','.yaml','.yml']

    temporary = ['.tmp','.temp']

    metadata = ['.json','.meta','.xml']

    backup = ['.old', '.bkp', '.backup', '.bak']

    database = ['.db', '.sqlite', '.mdb']

    log = ['.log']

    file_extention_list = []

    TITLE = f"""
                                    {COLOR_1}File Information{COLOR_2}
    """

    for file in file_list:
        name, file_extention = path.splitext(file)
        file_extention.lower() == file_extention.upper()
        file_extention_list.append(file_extention)

        number_all_files = len(file_extention_list)
        number_archive = sum(file in archive for file in file_extention_list)
        number_audio = sum(file in audio for file in file_extention_list)
        number_cad = sum(file in cad for file in file_extention_list)
        number_document = sum(file in document for file in file_extention_list)
        number_ebook = sum(file in ebook for file in file_extention_list)
        number_font = sum(file in font for file in file_extention_list)
        number_image = sum(file in image for file in file_extention_list)
        number_presentation = sum(file in presentation for file in file_extention_list)
        number_spreadsheet = sum(file in spreadsheet for file in file_extention_list)
        number_vector = sum(file in vector for file in file_extention_list)
        number_video = sum(file in video for file in file_extention_list)
        number_script = sum(file in script for file in file_extention_list)
        number_binary = sum(file in binary for file in file_extention_list)
        number_configuration = sum(file in configuration for file in file_extention_list) 
        number_temporary = sum(file in temporary for file in file_extention_list)
        number_metadata = sum(file in metadata for file in file_extention_list)
        number_backup = sum(file in backup for file in file_extention_list)
        number_database = sum(file in database for file in file_extention_list)
        number_log = sum(file in log for file in file_extention_list)

    FILE_INFO = f"""
    All Files: {COLOR_1}{number_all_files}{COLOR_2}

    Archive and Package Files: {COLOR_1}{number_archive}{COLOR_2}

    Audio Files:  {COLOR_1}{number_audio}{COLOR_2}

    Cad Files:  {COLOR_1}{number_cad}{COLOR_2}

    Document Files:  {COLOR_1}{number_document}{COLOR_2}

    Ebook Files:  {COLOR_1}{number_ebook}{COLOR_2}

    Font Files:  {COLOR_1}{number_font}{COLOR_2}

    Image Files:  {COLOR_1}{number_image}{COLOR_2}

    Presentation Files:  {COLOR_1}{number_presentation}{COLOR_2}

    Spreadsheet Files:  {COLOR_1}{number_spreadsheet}{COLOR_2}

    Vector Files:  {COLOR_1}{number_vector}{COLOR_2}

    Video Files:  {COLOR_1}{number_video}{COLOR_2}

    Scripting Files:  {COLOR_1}{number_script}{COLOR_2}

    Binaries and Executable Files:  {COLOR_1}{number_binary}{COLOR_2}

    Configuration Files:  {COLOR_1}{number_configuration}{COLOR_2}

    Temporary Files:  {COLOR_1}{number_temporary}{COLOR_2}

    Metadata Files  {COLOR_1}{number_metadata}{COLOR_2}

    Backup Files:  {COLOR_1}{number_backup}{COLOR_2}

    Database Files:  {COLOR_1}{number_database}{COLOR_2}

    Log Files:  {COLOR_1}{number_log}{COLOR_2}
    """

    for char in TITLE:
        print(char, end='', flush=True)
        sleep(0.01)

    print()

    for char in FILE_INFO:
        print(char, end='', flush=True)
        sleep(0.01)

    return 0

# OPTION 3: CHANGE COLORS WHEN PROMPTED
def ChangeColors(COLOR_1, COLOR_2):
    MSG = f"""
    Pick a color option.

        {COLOR_1}[0]{COLOR_2} - Default
        {COLOR_1}[1]{COLOR_2} - Holiday Season
        {COLOR_1}[2]{COLOR_2} - Frozen Dark
        {COLOR_1}[3]{COLOR_2} - Happy Go Lucky
    """
    for char in MSG:
        print(char, end='', flush=True)
        sleep(0.01)

    userColorChoice = input("Option: ")

    match (userColorChoice):
        case "0":
            COLOR_1 = "\033[38;5;46m"
            COLOR_2 = "\033[38;5;231m"
        case "1":
            COLOR_1 = "\033[38;5;160m"
            COLOR_2 = "\033[38;5;46m"
        case "2":
            COLOR_1 = "\033[38;5;67m"
            COLOR_2 = "\033[38;5;244m"
        case "3":
            COLOR_1 = "\033[38;5;82m"
            COLOR_2 = "\033[38;5;220m"
        case _:
            print("Incorrect input, try again.")
            sleep(2)
            ChangeColors(COLOR_1, COLOR_2)

    return COLOR_1, COLOR_2

# PRINT EXIT MESSAGE
def PrintExit(COLOR_1, COLOR_2):
    print(f"     {COLOR_2}Exiting Aliencrypt...")
    sleep(3)
    exit(0)

    return 0

# MAIN FUNCTION
def main():
    # DEFAULT PROGRAM COLORS
    COLOR_1 = "\033[38;5;46m"
    COLOR_2 = "\033[38;5;231m"

    # SEQUENCE FOR PROGRAM TO FOLLOW INCLUDING USER INPUT AND LOGIC CONTROL
    def MainSequence(COLOR_1, COLOR_2):
        userOption, userPath = PrintWelcome(COLOR_1, COLOR_2)

        if (path.exists(userPath) == True and int(userOption) != 3 and int(userOption) != 4):
            # OPTION FOR WHEN THE USER DID NOT CHOOSE A COLOR OR EXIT AND PATH IS VALID
            file_list = CollectFiles(userPath)

            match(int(userOption)):
                case 0:
                    EncryptFiles(file_list, userPath, COLOR_1, COLOR_2)
                case 1:
                    ShowFiles(file_list, COLOR_1, COLOR_2)
                case 2:
                    ShowFileInfo(file_list, COLOR_1, COLOR_2)
                case _:
                    print("     Incorrect input, Try again.")
                    print()
                    sleep(2)
                    for char in "   Press {COLOR_1}ENTER{COLOR_2} to continue.":
                        print(char, end='', flush=True)
                        sleep(0.01)
                    userCont = input("")
                    MainSequence(COLOR_1, COLOR_2)

        elif ((path.exists(userPath) == True or path.exists(userPath) == False) and int(userOption) == 3):
            # OPTION FOR WHEN THE USER DID CHOOSE A COLOR, BUT PATH IS VALID
            COLOR_1, COLOR_2 = ChangeColors(COLOR_1, COLOR_2)
            MainSequence(COLOR_1, COLOR_2)

        elif (path.exists(userPath) == False and int(userOption) != 3 and int(userOption) != 4):
            # OPTION FOR WHEN THE USER DID NOT WANT TO EXIT OR CHOOSE A COLOR, BUT PATH IS NOT VALID
            print(f"    Sorry, the path {userPath} does not exist. Try again.")
            print()
            sleep(2)
            for char in "   Press {COLOR_1}ENTER{COLOR_2} to continue.":
                print(char, end='', flush=True)
                sleep(0.01)
            userCont = input("")
            MainSequence(COLOR_1, COLOR_2)

        elif (int(userOption) == 4 and (path.exists(userPath) == True or path.exists(userPath) == False)):
            # OPTION FOR WHEN USER CHOSES TO EXIT BUT PATH IS VALID
            PrintExit(COLOR_1, COLOR_2)

        return 0

    MainSequence(COLOR_1, COLOR_2)

    return 0

# CHECK MAIN EXECUTION
if __name__ == "__main__":
    if IsRoot():
        main()
    else:
        print("\033[38;5;46mWARNING: \033[38;5;231mAliencrypt MUST be run as root!")
        sleep(2)
        exit(0)
