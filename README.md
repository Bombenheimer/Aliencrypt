<div id="header" align="center">

  [![3D fonts](https://see.fontimg.com/api/renderfont4/rg737/eyJyIjoiZnMiLCJoIjo2OCwidyI6MjAwMCwiZnMiOjM0LCJmZ2MiOiIjNkNGRjBFIiwiYmdjIjoiI0ZGRkZGRiIsInQiOjF9/QWxpZW5jcnlwdA/perdite-hollow-regular.png)](https://www.fontspace.com/category/3d)

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
  
  sᴇᴇ [**ᴄʜᴀɴɢᴇʟᴏɢ**](CHANGELOG.md) ғᴏʀ ᴅᴇᴛᴀɪʟs.

</div>

>[!CAUTION]
> Aliencrypt performs various operations on files, many of which can result in files being unrecoverable and / or destroyed, and can even render your system compromised. It is highly advisable that you ALWAYS use root permissions and ALWAYS check if you are using the correct file path.

# ＤＥＰＥＮＤＥＮＣＩＥＳ

  </br>

  **ʏᴏᴜ ᴄᴀɴ ɪɴsᴛᴀʟʟ ʟɪʙʀᴀʀɪᴇs ғʀᴏᴍ sᴏᴜʀᴄᴇ ᴏʀ ғʀᴏᴍ ʏᴏᴜʀ ᴅᴇᴅɪᴄᴀᴛᴇᴅ ᴘᴀᴄᴋᴀɢᴇ ᴍᴀɴᴀɢᴇʀ:**
  
  - ɢᴄᴄ (ᴄ99 ᴀɴᴅ ᴜᴘ)
  - [ʟɪʙsᴏᴅɪᴜᴍ](https://github.com/jedisct1/libsodium/releases/tag/1.0.19-RELEASE)
  - [ʟɪʙᴇxɪғ](https://github.com/libexif/libexif/releases/tag/v0.6.24)

  </br>

# ＩＮＳＴＡＬＬＡＴＩＯＮ

  </br>

  **ᴛᴏ ɪɴsᴛᴀʟʟ ᴀɴᴅ ʀᴜɴ ᴛʜᴇ ᴘʀᴏɢʀᴀᴍ, ʀᴜɴ:**
  ```bash
  sudo make
  sudo make install
  sudo make clean
  ```

  **ᴛᴏ ᴜɴɪɴsᴛᴀʟʟ, ʀᴜɴ:**
  ```bash
  sudo make uninstall
  ```

  </br>

# ＵＳＡＧＥ

</br>
<div id="header" align="center">
  
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
  **--logo** | sʜᴏᴡ ᴀʟɪᴇɴᴄʀʏᴘᴛ ʟᴏɢᴏ | N / A
  **--color=** | sʜᴏᴡ ᴘʀᴏɢʀᴀᴍ sᴛᴅᴏᴜᴛ ɪɴ ᴀ ᴅɪғғᴇʀᴇɴᴛ ᴄᴏʟᴏʀ sᴄʜᴇᴍᴇ | 1, 2, 3, 4, 5, 6, 7
  **--key=** | ᴘʀᴏᴠɪᴅᴇ ᴀ ɢᴇɴᴇʀᴀᴛᴇᴅ ᴅᴇᴄʀʏᴘᴛɪᴏɴ ᴋᴇʏ | ɴ / ᴀ
  **--version** | sʜᴏᴡ ᴘʀᴏɢʀᴀᴍ ᴠᴇʀsɪᴏɴ | ɴ / ᴀ

  **ғᴏʀ ᴍᴏʀᴇ ɪɴғᴏʀᴍᴀᴛɪᴏɴ ᴏɴ ᴘʀᴏɢʀᴀᴍ ᴜsᴀɢᴇ, ʀᴇғᴇʀᴇɴᴄᴇ ᴛʜᴇ ᴍᴀɴᴘᴀɢᴇ:**
  <div id="header" align="left">
    
  ```bash
  man alien
  ```
  </div>
</div>
