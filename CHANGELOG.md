# Changelog

# [3.0.0] - 2024-4-23
### Added
- C version: Aliencrypt has now been rewritten in C with an manpage and a Makefile for installation
  * More colors
  * Program can be ran with command line options
  * Safety checks
  * Better performance
  * Status checks
  * Decrypt files option
  * Remove Exif Metadata option
- Both versions: Overwrite passes to the shred in both program versions have been upgraded to 5
- Both versions: Show files option shows more files up to 9999

### Fixed
- Python version: Fixed an issue where ebook file extentions were not being checked (.lrf, .mobi)
- Python version: Fixed key length

### Removed
- Python version: Removed feature to encrypt filenames as it made filenames too long on some systems and caused errors
- Python version: Removed lowercase options to generate keynames
- Python version: Removed install.sh script
- Python version: Removed File check from where it would check if Aliencrypt.py is one of the files

# [2.2.2] - 2024-4-8
### Changed
- Minor change to filename and README file

# [2.2.1] - 2024-3-23
### Added
- "Show files" option now shows file permissions
- Fixed a bug where Aliencrypt collected files when the user input an invald option

# [2.1.1] - 2024-3-22
### Added
- Names for decryption keys are now unique each time they are generated

# [2.1.0] - 2024-3-22
### Added
- New option to overwrite files with random data and delete them
- "Show files" option now shows file sizes including B, KiB, MiB, GiB, and TiB
- New color: Dark Tech
- Minor changes

# [2.0.0] - 2024-3-20
### Added
- Alienscrypt must now be ran as root to protect files from tampering. See README for details
- Aliencrypt can now be ran as a compiled binary by running the install script
- Code redesign and logic
- New colors and new option to change colors
- Encrypt option now encrypts names of files for maximum protections
- Aliencrypt creates a decryption key when needed
- 18 new file extentions and 5 new file categories for file information
- 3 new colors including Frozen Dark, Holiday Season, and Happy Go Lucky

## [1.3.1] - 2023-12-14
### Added
- After entering in your chosen path, you can show file information to see how many of a different type of file that you have. These include:
  * Archive files (.tar, .zip, .7z, .iso, etc...)
  * Audio files (.mp3, .m4a, .wav, .wma, etc...)
  * Document files (.pages, .docx, .pdf, .txt, etc...)
  * Font files (.tff, .otf, .eot, .woff, etc...)
  * Image files (.png, .heic, .jepg, .jpg, etc...)
  * Scripting / Programming files (.py, .c, .java, .js, etc...)
  * And much MUCH MORE!!!
- You can also show the list of files in the directory that you are encrypting after chooisng a path encrypt files, or exit for another time
- Made don't want to encrypt files? that's okay! You can choose to go back to the options or exit as well
- More efficient code to improve user experience

## [1.2.1] - 2023-12-8
### Removed
- The lines ```with open('alien.key', 'wb') as alien:``` and ```alien.write(key)``` to remove the function of making an unecessary decryption key

## [1.2.0] - 2023-12-6
### Added
- New logo and byline for program

## [1.1.0] - 2023-12-4
### Added
- Clears command line interface before running with ```os.system("clear")```.

## [1.0.0] - 2023-12-2
### Initial release
- First release
