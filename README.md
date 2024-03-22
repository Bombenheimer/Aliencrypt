# Aliencrypt
"Swiss army knife" for file handling. Compatable with GNU/Linux and macOS.

Big update!!! Version ```2.0.0```. See changelog for details.

<img width="1280" alt="Logo-Display v2.0.0" src="https://github.com/Bombenheimer/Aliencrypt/assets/145699702/e8c286f6-ff69-4b45-8ce5-b6468c7ef78f">

>[!CAUTION]
> Aliencrypt performs various operations on files, many of which can result in files being unrecoverable and / or destroyed, and can even render your system compromised. It is highly advisable that you ALWAYS use root permissions and ALWAYS check if you are using the correct file path.

# Installation

## 1: Install python3
To check if ```python3``` is installed, run:
```
python3 --version
```

If ```python3``` is not installed, you must [install](https://www.python.org) it first for your system.

## 2: Install pip
If ```python3``` is installed run:
```
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
python3 get-pip.py
```

This will install the ```pip``` package manager. However, if this does not work, you can install pip via your package manager:

### GNU/Linux

Debian
```
sudo apt update
sudo apt upgrade -y
sudo apt install python3-pip
```

### macOS

Homebrew
```
brew update
brew upgrade
brew install python3-pip
```

To check if pip installation was successful, run:
```
pip --version
```

## 2: Clone Repo
To install, run:
```
git clone https://github.com/Bombenheimer/Aliencrypt.git
cd Aliencrypt
pip3 install -r requirements.txt
sudo ./install.sh
```

> [!IMPORTANT]
> Once installed, Aliencrypt MUST be ran using root permissions.
> If you do not use ```sudo```, Aliencrypt will refuse to run.
```
sudo Aliencrypt
```
This is an example of what will happen when you don't use ```sudo```:
<img width="1280" alt="Root-Permissions-Demo" src="https://github.com/Bombenheimer/Aliencrypt/assets/145699702/a4dcd2ab-f06a-469a-a515-6905114c1d03">

# Demonstration
> [!TIP]
> It is recommended to check if you are using the correct path you are testing with either option 1 or 2, and then use option 0.

## Encrypt Files (Option 0)
When this option is chosen, it will encrypt[^1] all files in the directory you have chosen and ask if you would like to create a decryption key to decrypt the files at a later time. This option also encrypts the names of the files as well (v2.0.0 and up), for extra security. The generated keys have a unique name as well, so you can keep track of each one that you use.

Test Files
<img width="1280" alt="Test-Files" src="https://github.com/Bombenheimer/Aliencrypt/assets/145699702/747c3bae-3767-4519-b551-758479e4ccdf">

Option 0
<img width="1280" alt="Option0-Demo" src="https://github.com/Bombenheimer/Aliencrypt/assets/145699702/cddb9414-f372-4c6b-8c1a-7b95ccfc2b41">

Encrypted Files
<img width="1280" alt="Encrypted-Files-Demo-1" src="https://github.com/Bombenheimer/Aliencrypt/assets/145699702/d87fb89b-f240-402e-bb6b-6d47e87d1d8c">


## Show Files (Option 1)
When this option is chosen, it will show all files in the directory you have chosen as well as hidden ones.

<img width="1280" alt="Option1-Demo" src="https://github.com/Bombenheimer/Aliencrypt/assets/145699702/f64a4908-9333-433f-bfd6-c1d1f6a7ad78">


## File Information (Option 2)
When this option is chosen, it will show how many of each type of file is inside the directory you have chosen based on the file extention.

<img width="1280" alt="Option2-Demo" src="https://github.com/Bombenheimer/Aliencrypt/assets/145699702/26de83e8-1549-46b5-a590-4c4eaa63f427">


## Change Colors (Option 3)
When this option is chosen, it will ask you what color scheme you would like to pick and it will restart the program to it change to those colors.

<img width="1280" alt="Option3-Demo" src="https://github.com/Bombenheimer/Aliencrypt/assets/145699702/925f5f05-6d97-4be8-9a53-90e2296c96d8">

<details>
<summary> Details </summary>
Author: <strong><a href="https://github.com/Bombenheimer">Bombenheimer</a></strong>
Programming Languages: Python, Bash

Software Version: v2.0.0
</details>

[^1]: Using the Fernet symmetric encryption algorithm; Using 128 bit AES.
