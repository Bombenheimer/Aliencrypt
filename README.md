<div id="header" align="center">
  
  # <div style="text-align: center;"> **Aliencrypt** </div>

  **"Swiss army knife"** for file handling. :alien:

  | | Status
  -|-
  **License** | ![GitHub Repo License](https://img.shields.io/github/license/bombenheimer/aliencrypt?style=flat&logo=github)
  **Creation Date** | ![GitHub Repo Creation Date](https://img.shields.io/github/created-at/bombenheimer/aliencrypt?style=flat&logo=github)
  **Watchers** | ![GitHub watchers](https://img.shields.io/github/watchers/bombenheimer/aliencrypt?style=flat&logo=github)
  **Stars** | ![GitHub Repo stars](https://img.shields.io/github/stars/bombenheimer/aliencrypt?style=flat&logo=github)
  **Version** | ![GitHub Release](https://img.shields.io/github/v/release/bombenheimer/aliencrypt?style=flat&logo=github&color=5D3FD3)
  **Last Commit** | ![GitHub last commit](https://img.shields.io/github/last-commit/bombenheimer/aliencrypt?style=flat&logo=github)
  **Project Size** | ![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/bombenheimer/aliencrypt?style=flat&logo=github&color=orange)
  **Downloads** | ![GitHub Downloads (all assets, all releases)](https://img.shields.io/github/downloads/bombenheimer/aliencrypt/total?style=flat&logo=github)
  **Supported OS** | ![Static Badge](https://img.shields.io/badge/Supported-green?style=flat&logo=linux&logoColor=white&label=GNU%20%2F%20Linux&color=0BDA51) </br> ![Static Badge](https://img.shields.io/badge/Supported-green?style=flat&logo=apple&logoColor=white&label=macOS&color=0BDA51) </br> ![Static Badge](https://img.shields.io/badge/Not%20Supported-red?style=flat&logo=windows&logoColor=white&label=Windows&color=FF3131)
  
  See [**changelog**](https://github.com/Bombenheimer/Aliencrypt/blob/main/CHANGELOG.md) for details.

</div>

>[!CAUTION]
> Aliencrypt performs various operations on files, many of which can result in files being unrecoverable and / or destroyed, and can even render your system compromised. It is highly advisable that you ALWAYS use root permissions and ALWAYS check if you are using the correct file path.

# Dependencies
<details>
  </br>

  **C version dependencies**
  - gcc (C99 and up)
  - [Libsodium](https://github.com/jedisct1/libsodium/releases/tag/1.0.19-RELEASE)
  - [Libexif](https://github.com/libexif/libexif/releases/tag/v0.6.24)

  **Python version dependencies**
  - [Python 3+](https://www.python.org/)
  - Pip
  - Cryptography Library (Installed from pip)
  
</details>

# Installation
<details>
  </br>

  **To install and run the C version of the program, run:**
  ```bash
  sudo make
  sudo make install
  sudo make clean
  ```
  
  **To install and run the python version of the program, run:**
  ```bash
  git clone https://github.com/Bombenheimer/Aliencrypt.git
  cd Aliencrypt
  pip3 install -r requirements.txt
  sudo python3 alien.py
  ```
</details>

# Usage
<details>

</br>
<div id="header" align="center">

  ## C Program Usage
  
  **Command Line Arguments**
  **Argument** | **Description** | **Options**
  -|-|-
  **--encrypt** | Encrypt a file or all files in a directory | N / A
  **--decrypt** | Decrypt a file or all files in a directory | N / A
  **--show-files** | Show files and file info about a file or all files in a directory | N / A
  **--show-file-types** | Show the type of a file or all files in a directory | N / A
  **--remove-exif** | Remove exif metadata from a file or all files in a directory (jpeg images only) | N / A
  **--shred** | Overwrite and a file or all files in a directory | N / A
  **--help** | Show program usage options | N / A
  **--path=** | Provide a file path to a directory or file | N / A
  **--key=** | Provide a generated decryption key | N / A
  **--version** | Show program version | N / A

  **For more information on program usage, reference the manpage:**
  <div id="header" align="left">
    
  ```bash
  man alien
  ```
  </div>
  
</br>

## Python Program Usage
  
### Encrypt Files (Option 0)
When this option is chosen, it will encrypt all files in the directory you have chosen and ask if you would like to create a decryption key to decrypt the files at a later time. This option also encrypts the names of the files as well (v2.0.0 and up), for extra security. The generated keys have a unique name as well, so you can keep track of each one that you use.

**Test Files**

<img width="1280" alt="Test-Files" src="https://github.com/Bombenheimer/Aliencrypt/assets/145699702/747c3bae-3767-4519-b551-758479e4ccdf">

**Option 0**

<img width="1280" alt="Option0-Demo" src="https://github.com/Bombenheimer/Aliencrypt/assets/145699702/cddb9414-f372-4c6b-8c1a-7b95ccfc2b41">

**Encrypted Files**

<img width="1280" alt="Encrypted-Files-Demo-1" src="https://github.com/Bombenheimer/Aliencrypt/assets/145699702/d87fb89b-f240-402e-bb6b-6d47e87d1d8c">


### Show Files (Option 1)
When this option is chosen, it will show all files in the directory you have chosen as well as hidden ones.

<img width="1280" alt="Option1-Demo" src="https://github.com/Bombenheimer/Aliencrypt/assets/145699702/f64a4908-9333-433f-bfd6-c1d1f6a7ad78">


### File Information (Option 2)
When this option is chosen, it will show how many of each type of file is inside the directory you have chosen based on the file extention.

<img width="1280" alt="Option2-Demo" src="https://github.com/Bombenheimer/Aliencrypt/assets/145699702/26de83e8-1549-46b5-a590-4c4eaa63f427">


### Change Colors (Option 3)
When this option is chosen, it will ask you what color scheme you would like to pick and it will restart the program to it change to those colors.

<img width="1280" alt="Option3-Demo" src="https://github.com/Bombenheimer/Aliencrypt/assets/145699702/925f5f05-6d97-4be8-9a53-90e2296c96d8">

</div>

</details>
