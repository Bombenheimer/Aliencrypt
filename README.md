<div id="header" align="center">
  
  # <div style="text-align: center;"> **ＡＬＩＥＮＣＲＹＰＴ** </div>

  **"sᴡɪss ᴀʀᴍʏ ᴋɴɪғᴇ"** ғᴏʀ ғɪʟᴇ ʜᴀɴᴅʟɪɴɢ. :alien:

  | | sᴛᴀᴛᴜs
  -|-
  **ʟɪᴄᴇɴsᴇ** | ![GitHub Repo License](https://img.shields.io/github/license/bombenheimer/aliencrypt?style=flat&logo=github)
  **ᴄʀᴇᴀᴛɪᴏɴ ᴅᴀᴛᴇ** | ![GitHub Repo Creation Date](https://img.shields.io/github/created-at/bombenheimer/aliencrypt?style=flat&logo=github)
  **ᴡᴀᴛᴄʜᴇʀs** | ![GitHub watchers](https://img.shields.io/github/watchers/bombenheimer/aliencrypt?style=flat&logo=github)
  **sᴛᴀʀs** | ![GitHub Repo stars](https://img.shields.io/github/stars/bombenheimer/aliencrypt?style=flat&logo=github)
  **ᴠᴇʀsɪᴏɴ** | ![GitHub Release](https://img.shields.io/github/v/release/bombenheimer/aliencrypt?style=flat&logo=github&color=5D3FD3)
  **ʟᴀsᴛ ᴄᴏᴍᴍɪᴛ** | ![GitHub last commit](https://img.shields.io/github/last-commit/bombenheimer/aliencrypt?style=flat&logo=github)
  **ᴘʀᴏᴊᴇᴄᴛ sɪᴢᴇ** | ![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/bombenheimer/aliencrypt?style=flat&logo=github&color=orange)
  **ᴅᴏᴡɴʟᴏᴀᴅs** | ![GitHub Downloads (all assets, all releases)](https://img.shields.io/github/downloads/bombenheimer/aliencrypt/total?style=flat&logo=github)
  **sᴜᴘᴘᴏʀᴛᴇᴅ ᴏs** | ![Static Badge](https://img.shields.io/badge/Supported-green?style=flat&logo=linux&logoColor=white&label=GNU%20%2F%20Linux&color=0BDA51) </br> ![Static Badge](https://img.shields.io/badge/Supported-green?style=flat&logo=apple&logoColor=white&label=macOS&color=0BDA51) </br> ![Static Badge](https://img.shields.io/badge/Not%20Supported-red?style=flat&logo=windows&logoColor=white&label=Windows&color=FF3131)
  
  sᴇᴇ [**ᴄʜᴀɴɢᴇʟᴏɢ**](https://github.com/Bombenheimer/Aliencrypt/blob/main/CHANGELOG.md) ғᴏʀ ᴅᴇᴛᴀɪʟs.

</div>

>[!CAUTION]
> Aliencrypt performs various operations on files, many of which can result in files being unrecoverable and / or destroyed, and can even render your system compromised. It is highly advisable that you ALWAYS use root permissions and ALWAYS check if you are using the correct file path.

# ＤＥＰＥＮＤＥＮＣＩＥＳ
<details>
  </br>

  **ᴄ ᴠᴇʀsɪᴏɴ ᴅᴇᴘᴇɴᴅᴇɴᴄɪᴇs**
  - ɢᴄᴄ (ᴄ99 ᴀɴᴅ ᴜᴘ)
  - [ʟɪʙsᴏᴅɪᴜᴍ](https://github.com/jedisct1/libsodium/releases/tag/1.0.19-RELEASE)
  - [ʟɪʙᴇxɪғ](https://github.com/libexif/libexif/releases/tag/v0.6.24)

  **ᴘʏᴛʜᴏɴ ᴠᴇʀsɪᴏɴ ᴅᴇᴘᴇɴᴅᴇɴᴄɪᴇs**
  - [ᴘʏᴛʜᴏɴ 3+](https://www.python.org/)
  - ᴘɪᴘ
  - ᴄʀʏᴘᴛᴏɢʀᴀᴘʜʏ ʟɪʙʀᴀʀʏ (ɪɴsᴛᴀʟʟᴇᴅ ғʀᴏᴍ ᴘɪᴘ)
  
</details>

# ＩＮＳＴＡＬＬＡＴＩＯＮ
<details>
  </br>

  **ᴛᴏ ɪɴsᴛᴀʟʟ ᴀɴᴅ ʀᴜɴ ᴛʜᴇ ᴄ ᴠᴇʀsɪᴏɴ ᴏғ ᴛʜᴇ ᴘʀᴏɢʀᴀᴍ, ʀᴜɴ:**
  ```bash
  sudo make
  sudo make install
  sudo make clean
  ```
  
  **ᴛᴏ ɪɴsᴛᴀʟʟ ᴀɴᴅ ʀᴜɴ ᴛʜᴇ ᴘʏᴛʜᴏɴ ᴠᴇʀsɪᴏɴ ᴏғ ᴛʜᴇ ᴘʀᴏɢʀᴀᴍ, ʀᴜɴ:**
  ```bash
  pip3 install -r requirements.txt
  sudo python3 alien.py
  ```
</details>

# ＵＳＡＧＥ
<details>

</br>
<div id="header" align="center">

  ## Ｃ ＰＲＯＧＲＡＭ ＵＳＡＧＥ
  
  **ᴄᴏᴍᴍᴀɴᴅ ʟɪɴᴇ ᴀʀɢᴜᴍᴇɴᴛs**
  **ᴀʀɢᴜᴍᴇɴᴛ** | **ᴅᴇsᴄʀɪᴘᴛɪᴏɴ** | **ᴏᴘᴛɪᴏɴs**
  -|-|-
  **--encrypt** | ᴇɴᴄʀʏᴘᴛ ᴀ ғɪʟᴇ ᴏʀ ᴀʟʟ ғɪʟᴇs ɪɴ ᴀ ᴅɪʀᴇᴄᴛᴏʀʏ | ɴ / ᴀ
  **--decrypt** | ᴅᴇᴄʀʏᴘᴛ ᴀ ғɪʟᴇ ᴏʀ ᴀʟʟ ғɪʟᴇs ɪɴ ᴀ ᴅɪʀᴇᴄᴛᴏʀʏ | ɴ / ᴀ
  **--show-files** | sʜᴏᴡ ғɪʟᴇs ᴀɴᴅ ғɪʟᴇ ɪɴғᴏ ᴀʙᴏᴜᴛ ᴀ ғɪʟᴇ ᴏʀ ᴀʟʟ ғɪʟᴇs ɪɴ ᴀ ᴅɪʀᴇᴄᴛᴏʀʏ | ɴ / ᴀ
  **--show-file-types** | sʜᴏᴡ ᴛʜᴇ ᴛʏᴘᴇ ᴏғ ᴀ ғɪʟᴇ ᴏʀ ᴀʟʟ ғɪʟᴇs ɪɴ ᴀ ᴅɪʀᴇᴄᴛᴏʀʏ | ɴ / ᴀ
  **--remove-exif** | ʀᴇᴍᴏᴠᴇ ᴇxɪғ ᴍᴇᴛᴀᴅᴀᴛᴀ ғʀᴏᴍ ᴀ ғɪʟᴇ ᴏʀ ᴀʟʟ ғɪʟᴇs ɪɴ ᴀ ᴅɪʀᴇᴄᴛᴏʀʏ (ᴊᴘᴇɢ ɪᴍᴀɢᴇs ᴏɴʟʏ) | ɴ / ᴀ
  **--shred** | ᴏᴠᴇʀᴡʀɪᴛᴇ ᴀɴᴅ ᴀ ғɪʟᴇ ᴏʀ ᴀʟʟ ғɪʟᴇs ɪɴ ᴀ ᴅɪʀᴇᴄᴛᴏʀʏ | ɴ / ᴀ
  **--help** | sʜᴏᴡ ᴘʀᴏɢʀᴀᴍ ᴜsᴀɢᴇ ᴏᴘᴛɪᴏɴs | ɴ / ᴀ
  **--path=** | ᴘʀᴏᴠɪᴅᴇ ᴀ ғɪʟᴇ ᴘᴀᴛʜ ᴛᴏ ᴀ ᴅɪʀᴇᴄᴛᴏʀʏ ᴏʀ ғɪʟᴇ | ɴ / ᴀ
  **--key=** | ᴘʀᴏᴠɪᴅᴇ ᴀ ɢᴇɴᴇʀᴀᴛᴇᴅ ᴅᴇᴄʀʏᴘᴛɪᴏɴ ᴋᴇʏ | ɴ / ᴀ
  **--version** | sʜᴏᴡ ᴘʀᴏɢʀᴀᴍ ᴠᴇʀsɪᴏɴ | ɴ / ᴀ

  **ғᴏʀ ᴍᴏʀᴇ ɪɴғᴏʀᴍᴀᴛɪᴏɴ ᴏɴ ᴘʀᴏɢʀᴀᴍ ᴜsᴀɢᴇ, ʀᴇғᴇʀᴇɴᴄᴇ ᴛʜᴇ ᴍᴀɴᴘᴀɢᴇ:**
  <div id="header" align="left">
    
  ```bash
  man alien
  ```
  </div>
  
</br>

## ＰＹＴＨＯＮ ＰＲＯＧＲＡＭ ＵＳＡＧＥ
  
### ᴇɴᴄʀʏᴘᴛ ғɪʟᴇs (ᴏᴘᴛɪᴏɴ 0)
ᴡʜᴇɴ ᴛʜɪs ᴏᴘᴛɪᴏɴ ɪs ᴄʜᴏsᴇɴ, ɪᴛ ᴡɪʟʟ ᴇɴᴄʀʏᴘᴛ ᴀʟʟ ғɪʟᴇs ɪɴ ᴛʜᴇ ᴅɪʀᴇᴄᴛᴏʀʏ ʏᴏᴜ ʜᴀᴠᴇ ᴄʜᴏsᴇɴ ᴀɴᴅ ᴀsᴋ ɪғ ʏᴏᴜ ᴡᴏᴜʟᴅ ʟɪᴋᴇ ᴛᴏ ᴄʀᴇᴀᴛᴇ ᴀ ᴅᴇᴄʀʏᴘᴛɪᴏɴ ᴋᴇʏ ᴛᴏ ᴅᴇᴄʀʏᴘᴛ ᴛʜᴇ ғɪʟᴇs ᴀᴛ ᴀ ʟᴀᴛᴇʀ ᴛɪᴍᴇ

<img width="1280" alt="Option0-Demo" src="https://github.com/Bombenheimer/Aliencrypt/assets/145699702/cddb9414-f372-4c6b-8c1a-7b95ccfc2b41">


### sʜᴏᴡ ғɪʟᴇs (ᴏᴘᴛɪᴏɴ 1)
ᴡʜᴇɴ ᴛʜɪs ᴏᴘᴛɪᴏɴ ɪs ᴄʜᴏsᴇɴ, ɪᴛ ᴡɪʟʟ sʜᴏᴡ ᴀʟʟ ғɪʟᴇs ɪɴ ᴛʜᴇ ᴅɪʀᴇᴄᴛᴏʀʏ ʏᴏᴜ ʜᴀᴠᴇ ᴄʜᴏsᴇɴ ᴀs ᴡᴇʟʟ ᴀs ʜɪᴅᴅᴇɴ ᴏɴᴇs

<img width="1280" alt="Option1-Demo" src="https://github.com/Bombenheimer/Aliencrypt/assets/145699702/f64a4908-9333-433f-bfd6-c1d1f6a7ad78">


### ғɪʟᴇ ɪɴғᴏʀᴍᴀᴛɪᴏɴ (ᴏᴘᴛɪᴏɴ 2)
ᴡʜᴇɴ ᴛʜɪs ᴏᴘᴛɪᴏɴ ɪs ᴄʜᴏsᴇɴ, ɪᴛ ᴡɪʟʟ sʜᴏᴡ ʜᴏᴡ ᴍᴀɴʏ ᴏғ ᴇᴀᴄʜ ᴛʏᴘᴇ ᴏғ ғɪʟᴇ ɪs ɪɴsɪᴅᴇ ᴛʜᴇ ᴅɪʀᴇᴄᴛᴏʀʏ ʏᴏᴜ ʜᴀᴠᴇ ᴄʜᴏsᴇɴ

<img width="1280" alt="Option2-Demo" src="https://github.com/Bombenheimer/Aliencrypt/assets/145699702/26de83e8-1549-46b5-a590-4c4eaa63f427">


### ᴄʜᴀɴɢᴇ ᴄᴏʟᴏʀs (ᴏᴘᴛɪᴏɴ 3)
ᴡʜᴇɴ ᴛʜɪs ᴏᴘᴛɪᴏɴ ɪs ᴄʜᴏsᴇɴ, ɪᴛ ᴡɪʟʟ ᴀsᴋ ʏᴏᴜ ᴡʜᴀᴛ ᴄᴏʟᴏʀ sᴄʜᴇᴍᴇ ʏᴏᴜ ᴡᴏᴜʟᴅ ʟɪᴋᴇ ᴛᴏ ᴘɪᴄᴋ ᴀɴᴅ ɪᴛ ᴡɪʟʟ ʀᴇsᴛᴀʀᴛ ᴛʜᴇ ᴘʀᴏɢʀᴀᴍ ᴛᴏ ɪᴛ ᴄʜᴀɴɢᴇ ᴛᴏ ᴛʜᴏsᴇ ᴄᴏʟᴏʀs

<img width="1280" alt="Option3-Demo" src="https://github.com/Bombenheimer/Aliencrypt/assets/145699702/925f5f05-6d97-4be8-9a53-90e2296c96d8">

</div>
</details>
