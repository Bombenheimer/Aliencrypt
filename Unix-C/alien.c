/*
 * INTRODUCTION:
 * 	This program was designed by Bombenheimer.
 * 	Follow me on GitHub for more projects like these and collaborate.
 *
 * SOCIALS:
 * 	- GitHub: https://github.com/Bombenheimer/
 * 	- Linkedin: https://www.linkedin.com/in/bruce-smith-4a4941296/
 * 	- Discord: https://discord.com/channels/@arrgs8
 *	- Spotify: https://open.spotify.com/user/31i7hr5eqfinn6ricygtgsywuthu?si=6150908ac8814b04
 *
 * IMPORTANT NOTES:
 * 	(1) This Program MUST be ran as root!
 * 	(2) This Program also requires Libexif and Libsodium for file I/O operations. See repo for details.
 */

// DEFINE MACRO FOR GNU SOURCE
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

// STANDARD LIBRARIES
#include <stdio.h> // FUNCTIONS: printf(), fflush() fprintf()
#include <errno.h> // MACROS: errno
#include <time.h> // FUNCTIONS: clock(), time()
#include <stdbool.h> // MACROS: bool, true, false
#include <sys/stat.h> // FUNCTIONS, MACROS, AND STRUCTS: stat(), S_ISREG(), S_IRWXU, S_IRWXG, S_IRWXO, mode_t, struct stat
#include <math.h> // FUNCTIONS: pow()
#include <stdlib.h> // FUNCTIONS AND MACROS: free(), malloc(), realloc(), size_t, NULL

// EXTERNAL LIBRARIES
#include <sodium.h> // FUNCTIONS AND MACROS: crypto_secretbox_KEYBYTES, crypto_secretbox_NONCEBYTES, crypto_secretbox_MACBYTES, sodium_init()
		    // randombytes_buf(), crypto_secretbox_detached(), crypto_secretbox_open_detached()
#include <libexif/exif-data.h> // FUNCTIONS AND MACROS: exif_data_new_from_file(), exif_data_unref(), ExifData

// HEADER GUARDS TO DETECT OPERATING SYSTEM
#ifndef _WIN32

// UNIX SPECIFIC LIBRARIES
#include <string.h> // FUNCTIONS: strcmp(), strstr(), strlen(), strrchr(), strcpy(), strcat(), strdup()
#include <unistd.h> // FUNCTIONS: geteuid(), unlink()
#include <dirent.h> // FUNCTIONS, MACROS, AND STRUCTS: DIR, opendir() readdir(), closedir(), struct dirent
#include <iso646.h> // MACROS: and, or, not

#endif // END OF HEADER GUARD

// DEFAULT COLORS
#define DEFAULT_COLOR_1 "\033[38;5;46m" // GREEN
#define DEFAULT_COLOR_2 "\033[38;5;231m" // WHITE
#define DEFAULT_COLOR_3 "\033[38;5;231m" // WHITE

// HOLIDAY SEASON COLORS
#define HOLIDAY_COLOR_1 "\033[38;5;160m" // RED
#define HOLIDAY_COLOR_2 "\033[38;5;46m" // GREEN
#define HOLIDAY_COLOR_3 "\033[38;5;231m" // WHITE

// CYBERPUNK COLORS
#define CYBER_COLOR_1 "\033[38;5;87m" // CYAN
#define CYBER_COLOR_2 "\033[38;5;184m" // YELLOW
#define CYBER_COLOR_3 "\033[38;5;93m" // PURPLE

// FROZEN DARK COLORS
#define FROZEND_COLOR_1 "\033[38;5;111m" // ICE BLUE 
#define FROZEND_COLOR_2 "\033[38;5;102m" // LIGHT SLATE GREY
#define FROZEND_COLOR_3 "\033[38;5;67m" // STEEL BLUE

// PROTANOPIA COLORS
#define PROTAN_COLOR_1 "\033[38;5;71m" // GREEN
#define PROTAN_COLOR_2 "\033[38;5;255m" // WHITE
#define PROTAN_COLOR_3 "\033[38;5;255m" // WHITE

// DEUTERANOPIA COLORS
#define DEUTER_COLOR_1 "\033[38;5;70m" // GREEN
#define DEUTER_COLOR_2 "\033[38;5;255m" // WHITE
#define DEUTER_COLOR_3 "\033[38;5;255m" // WHITE

// TRITANOPIA COLORS
#define TRITAN_COLOR_1 "\033[38;5;82m" // GREEN
#define TRITAN_COLOR_2 "\033[38;5;255m" // WHITE
#define TRITAN_COLOR_3 "\033[38;5;255m" // WHITE

// GREYSCALE COLORS
#define GREYSC_COLOR_1 "\033[38;5;249m" // GREEN
#define GREYSC_COLOR_2 "\033[38;5;231m" // WHITE
#define GREYSC_COLOR_3 "\033[38;5;231m" // WHITE

// MAX PATH LENGTH
#define MAX_PATH_LEN 1024

// KEY NAME LENGTH
#define KEY_NAME_LEN 13

// KEY SIZE, NONCE SIZE, AND TAG SIZE
#define KEY_SIZE crypto_secretbox_KEYBYTES
#define NONCE_SIZE crypto_secretbox_NONCEBYTES
#define TAG_SIZE crypto_secretbox_MACBYTES

// SHRED FILES BUFFER SIZE AND NUMBER OF PASSES
#define BUFFER_SIZE 4096
#define NUM_PASSES 5

// DEFINE NUMBER OF CURRENT SUPPORTED FILE EXTENTIONS FOR EACH FILE TYPE
#define ARCHIVE_NUM 38
#define AUDIO_NUM 17
#define CAD_NUM 2
#define DOC_NUM 21
#define EBOOK_NUM 21
#define FONT_NUM 5
#define IMAGE_NUM 39
#define PRESENT_NUM 10
#define SSHEET_NUM 7
#define VECTOR_NUM 10
#define VIDEO_NUM 27
#define SCRIPT_NUM 17
#define BINARY_NUM 10
#define CONFIG_NUM 6
#define TEMP_NUM 2
#define META_NUM 3
#define BACKUP_NUM 4
#define DB_NUM 3
#define LOG_NUM 1

// VERSION NUMBER
#define VER_NUM "3.0.1"

// FUNCTION PROTOTYPES FOR OPERATIONS
int PrintLogo(bool showLogo, char* color1, char* color2);
void PrintUsage(bool showHelp);
void PrintVersion(bool showVersion, char* versionNum);
char* KeyNameGen(bool encryptFiles, char* color1, char* color2);

// FUNCTION PROTOTYPES FOR OPTIONS
void RemoveExif(bool removeExif, char** fileList, char* pathToDir, unsigned int numFiles, char* color2);
int EncryptFiles(bool encryptFiles, unsigned int numFiles, char** fileList, char* pathToDir, char* keyName, char* color1, char* color2);
void ShowFiles(bool showFiles, char** fileList, char* pathToDir, unsigned int numFiles, char* color1, char* color2, char* color3);
void ShowFileTypes(bool showFileTypes, char** fileList, unsigned int numFiles, char* color1, char* color2, char* color3);
int ShredFiles(bool shredFiles, char** fileList, unsigned int numFiles, char* pathToDir, char* color1, char* color2);
int DecryptFiles(bool decryptFiles, unsigned int numFiles, char** fileList, char* pathToDir, char* keyPath, char* color1, char* color2);

// DEFINED TYPE FOR RESTRICTED DIRECTORIES
typedef const char* BadDir;

// STRUCTURE FOR NUMBER OF EACH FILE TYPE
struct NumFileTypes
{
	unsigned int archive;
	unsigned int audio;
	unsigned int cad;
	unsigned int document;
	unsigned int ebook;
	unsigned int font;
	unsigned int image;
	unsigned int presentation;
	unsigned int spreadsheet;
	unsigned int vector;
	unsigned int video;
	unsigned int script;
	unsigned int binary;
	unsigned int configuration;
	unsigned int temporary;
	unsigned int metadata;
	unsigned int backup;
	unsigned int database;
	unsigned int log;
};

// GLOBAL VARIABLE FOR ALL FUNCTIONS TO USE
unsigned int numFunctionCalls = 0;

// MAIN FUCNTION
int main(int argc, char* argv[])
{
	// CLOCK TIME VARIABLES
	clock_t CLOCK_START, CLOCK_END;
	double CLOCK_TIME;

	// START CLOCK TO TIME PROGRAM
	CLOCK_START = clock();

	// CHECK OPERATING SYSTEM. IF ITS NOT MACOS OR LINUX, RAISE AN ERROR
	#if !(defined(__linux__)) && !(defined(__APPLE__) && defined(__MACH__))
		errno = 1;
		fprintf(stderr, "%sERROR%s: Unknown Operating System.\n", color1, color2);
		fprintf(stderr, "aliencrypt : %s\n", strerror(errno));
		return errno;
	#endif
	
	// VARIABLES FOR WORKING WITH FILES
	// SUBJECT TO CHANGE BASED ON USER PREFERENCES
	char* keyName = NULL;
	char* keyPath = NULL;
	char* pathToDir = ".";
	char fullPath[MAX_PATH_LEN];
	char** fileList = NULL;
	unsigned int numFiles = 0;
	DIR *directory;
	struct dirent *entry;
	struct stat statbuf;

	// VARIABLES FOR COLORS
	// SUBJECT TO CHANGE BASED ON USER PREFERENCES
	char* color1 = DEFAULT_COLOR_1;
	char* color2 = DEFAULT_COLOR_2;
	char* color3 = DEFAULT_COLOR_3;

	// VARIABLES FOR USER OPTIONS
	// SUBJECT TO CHANGE BASED ON USER PREFERENCES
	bool showLogo = false;
	bool encryptFiles = false;
	bool decryptFiles = false;
	bool showFiles = false;
	bool showFileTypes = false;
	bool removeExif = false;
	bool shredFiles = false;
	bool showHelp = false;
	bool showVersion = false;

	// VERSION NUMBER
	char* versionNum = VER_NUM;

	// CHECK IF USER IS RUNNING THE PROGRAM AS ROOT. IF NOT, RAISE AN ERROR
	if (geteuid() != 0)
	{
		errno = 1;
		fprintf(stderr, "%sWARNING%s: Aliencrypt MUST be run as root!\n", color1, color2);
		fprintf(stderr, "aliencrypt : Operation not permitted\n");
		return errno;
	}
	else
	{

		// INITIALIZE LIBSODIUM
		if (sodium_init() == -1)
		{
			fprintf(stderr, "%sERROR%s: Initialzation of Libsodium Failed.\n", color1, color2);
			return 1;
		}

		// PARSE ARGUMENTS
		for (int i = 1; i < argc; i++)
		{
			// PROGRAM OPTIONS
			if (strcmp(argv[i], "--encrypt") == 0)
			{
				encryptFiles = true; // ENCRYPT FILES
			}
			if (strcmp(argv[i], "--decrypt") == 0)
			{
				decryptFiles = true; // DECRYPT FILES
			}
			if (strcmp(argv[i], "--show-files") == 0)
			{
				showFiles = true; // SHOW FILES
			}
			if (strcmp(argv[i], "--show-file-types") == 0)
			{
				showFileTypes = true; // SHOW FILE TYPES
			}
			if (strcmp(argv[i], "--remove-exif") == 0)
			{
				removeExif = true; // REMOVE EXIF METADATA
			}
			if (strcmp(argv[i], "--shred") == 0)
			{
				shredFiles = true; // SHRED FILES
			}
			if (strcmp(argv[i], "--help") == 0)
			{
				showHelp = true; // SHOW HELP MESSAGE
			}
			if (strcmp(argv[i], "--logo") == 0)
			{
				showLogo = true; // SHOW LOGO
			}
			if (strcmp(argv[i], "--version") == 0)
			{
				showVersion = true;
			}

			// IF THE USER CHOOSES A COLOR PARSE THROUGH THE INPUT TO FIND THE COLOR NUMBER
			// IF ITS AN INVALID COLOR, RAISE AN ERROR
			if (strstr(argv[i], "--color=") != NULL)
			{	
				switch (argv[i][8])
				{
					case '1':
						color1 = HOLIDAY_COLOR_1;
						color2 = HOLIDAY_COLOR_2;
						color3 = HOLIDAY_COLOR_3;
						break;
					case '2':
						color1 = CYBER_COLOR_1;
						color2 = CYBER_COLOR_2;
						color3 = CYBER_COLOR_3;
						break;
					case '3':
						color1 = FROZEND_COLOR_1;
						color2 = FROZEND_COLOR_2;
						color3 = FROZEND_COLOR_3;
						break;
					case '4':
						color1 = PROTAN_COLOR_1;
						color2 = PROTAN_COLOR_2;
						color3 = PROTAN_COLOR_3;
						break;
					case '5':
						color1 = DEUTER_COLOR_1;
						color2 = DEUTER_COLOR_2;
						color3 = DEUTER_COLOR_3;
						break;
					case '6':
						color1 = TRITAN_COLOR_1;
						color2 = TRITAN_COLOR_2;
						color3 = TRITAN_COLOR_3;
						break;
					case '7':
						color1 = GREYSC_COLOR_1;
						color2 = GREYSC_COLOR_2;
						color3 = GREYSC_COLOR_3;
						break;
					default:
						errno = 1;
						showHelp = true;
						fprintf(stderr, "%sERROR%s: Color %c does not exist.\n", color1, color2, argv[i][8]);
						PrintUsage(showHelp);
						return errno;
						break;
				}
			}

			// IF THE USER PROVIDES A PATH, PARSE THROUGH THE INPUT TO FIND THE PATH AND COLLECT FILES FROM THAT DIRECTORY
			// IF ITS AN INVALID PATH ARGUMENT, RAISE AN ERROR
			// IF THE USER PROVIDED NO PATH, COLLECT FILES FROM CURRENT DIRECTORY
			if ((strstr(argv[i], "--path=") != NULL))
			{
				if (argv[i][7] != '/')
				{
					errno = 1;
					showHelp = true;
					fprintf(stderr, "%sERROR%s: Invalid path argument.\n", color1, color2);
					PrintUsage(showHelp);
					return errno;
				}
				else
				{
					// EXTRACT FILE PATH
					pathToDir = argv[i] + strlen("--path=");

					// EXTRACT LAST SLASH AND WILDCARD OPERATOR IN PATH ARGUMENT
					char* searchLastSlash = strrchr(pathToDir, '/');
					char* searchWildCard = strrchr(searchLastSlash, '*');

					if (searchWildCard != NULL)
					{
						// EXTRACT THE PATH FROM THE WILDCARD TO PREVENT AN ERROR
						pathToDir[searchLastSlash - pathToDir] = '\0';

						// OPEN DIRETCORY. IF IT IS NULL, RAISE AN ERROR
						if ((directory = opendir(pathToDir)) != NULL)
						{
							// EXTRACT THE SEACH PATTERN
							for (int i = 0; searchWildCard[i] != '\0'; i++)
							{
								searchWildCard[i] = searchWildCard[i + 1];
							}

							while ((entry = readdir(directory)) != NULL)
							{
								char* filename = strdup(entry->d_name);
								snprintf(fullPath, sizeof(fullPath), "%s/%s", pathToDir, filename);
								if (stat(fullPath, &statbuf) == -1)
								{
									continue;
								}
								if ((not( S_ISREG(statbuf.st_mode))) or (strstr(filename, searchWildCard) == NULL))
								{
									free(filename);
									continue;
								}
								fileList = (char **)realloc(fileList, (numFiles + 1) * sizeof(char *));

								// CHECK IF MEMORY WAS ALLOCATED
								if (not(fileList))
								{
									errno = 1;
									fprintf(stderr, "%sERROR%s: Unable to retrive memory.\n", color1, color2);
									fprintf(stderr, "aliencrypt : MEMFAIL\n");
									return errno;
								}
								fileList[numFiles++] = filename;
							}
							closedir(directory);
						}
					}
					else if (searchWildCard == NULL)
					{
						if ((directory = opendir(pathToDir)) != NULL)
						{
							while ((entry = readdir(directory)) != NULL)
							{
								char* filename = strdup(entry->d_name);
								snprintf(fullPath, sizeof(fullPath), "%s/%s", pathToDir, filename);
								if (stat(fullPath, &statbuf) == -1)
								{
									continue;
								}
								if (not(S_ISREG(statbuf.st_mode)))
								{
									free(filename);
									continue;
								}
								fileList = (char **)realloc(fileList, (numFiles + 1) * sizeof(char *));

								// CHECK IF MEMORY WAS ALLOCATED
								if (not(fileList))
								{
									errno = 1;
									fprintf(stderr, "%sERROR%s: Unable to retrive memory.\n", color1, color2);
									fprintf(stderr, "aliencrypt : MEMFAIL\n");
									return errno;
								}
								fileList[numFiles++] = filename;
							}
							closedir(directory);
						}
						else if ((directory = opendir(pathToDir)) == NULL)
						{
							errno = 2;
							fprintf(stderr, "%sERROR%s: Directory or file does not exist or cannot be accessed.\n", color1, color2);
							fprintf(stderr, "aliencrypt : No such file or directory\n");
							return errno;

						} // END OF DIRECTORY CHECK
					} // END OF PATH PARSING
				} // END OF VALID PATH CHECKING
			} // END OF PATH ARGUMENT PARSING

			// IF THE USER CHOOSES THE DECRYPT OPTION, PARSE THROUGH THE INPUT TO FIND THE PATH
			// IF ITS AN INVALID PATH ARGUMENT, RAISE AN ERROR
			if (strstr(argv[i], "--key=") != NULL)
			{
				keyPath = strchr(argv[i], '/');

				if (keyPath != NULL)
				{
					// EXTRACT KEY PATH
					keyPath = argv[i] + strlen("--key=");

					// CHECK IF FILE EXISTS
					FILE *fileCheck = fopen(keyPath, "rb");

					if (fileCheck == NULL)
					{
						errno = 2;
						fprintf(stderr, "%sERROR%s: Key file does not exist.", color1, color2);
						fprintf(stderr, "aliencrypt : Operation not permitted\n");
						return errno;
					}
					else
					{
						fclose(fileCheck);
					}
				}
				else
				{
					errno = 1;
					showHelp = true;
					fprintf(stderr, "%sERROR%s: Invalid key path argument.\n", color1, color2);
					PrintUsage(showHelp);
					return errno;
				}
			}

			// CHECK IF ANYTHING THAT THE USER ENTERS IN STDIN IS NOT A VALID ARGUMENT. IF SO, RAISE AN ERROR
			if ((strstr(argv[i], "--encrypt") == NULL) and (strstr(argv[i], "--decrypt") == NULL) and
			   (strstr(argv[i], "--remove-exif") == NULL) and (strstr(argv[i], "--shred") == NULL) and
			   (strstr(argv[i], "--help") == NULL) and (strstr(argv[i], "--path=") == NULL) and
			   (strstr(argv[i], "--logo") == NULL) and (strstr(argv[i], "--color=") == NULL) and
			   (strstr(argv[i], "--show-file-types") == NULL) and (strstr(argv[i], "--show-files") == NULL) and
			   (strstr(argv[i], "--key=") == NULL) and (strstr(argv[i], "--version") == NULL))
			{
				errno = 1;
				showHelp = true;
				fprintf(stderr, "%sERROR%s: Illegal option %s\n", color1, color2, argv[i]);
				PrintUsage(showHelp);
				return errno;

			}// END OF INVALID ARGUMENT CHECKING

			// CHECK IF THE USER GAVE THE DECRYPT OPTION, BUT DID NOT HAVE THE KEY OPTION. IF SO, RAISE AN ERROR
			if ((strstr(argv[i], "--decrypt") != NULL) and (strstr(argv[i], "--key=") == NULL))
			{
				errno = 1;
				showHelp = true;
				fprintf(stderr, "%sERROR%s: No key option provided.\n", color1, color2);
				PrintUsage(showHelp);
				return errno;

			}// END OF DECRYPT AND KEY OPTION CHECK
		}// END OF ARGUMENT PARSING

		// CHECK IF THE USER PROVIDED NO ARGUMENTS AT ALL, OR TOO MANY. IF SO, RAISE AN ERROR
		if (argc == 1)
		{
			errno = 1;
			showHelp = true;
			fprintf(stderr, "%sERROR%s: No arguments provided.\n", color1, color2);
			PrintUsage(showHelp);
			return errno;
		}
		else if (argc >= 12)
		{
			errno = 1;
			showHelp = true;
			fprintf(stderr, "%sERROR%s: Too many arguments.\n", color1, color2);
			PrintUsage(showHelp);
			return errno;
		}

		// CHECK IF ANY FILES WERE ADDED. IF NOT, THIS WOULD MEAN THAT THE USER
		// DID NOT PROVIDE A PATH. IF SO, GET THE FILES FROM THE CURRENT DIRECTORY.
		if (numFiles == 0)
		{
			if ((directory = opendir(pathToDir)) != NULL)
			{
				while ((entry = readdir(directory)) != NULL)
				{
					char* filename = strdup(entry->d_name);
					snprintf(fullPath, sizeof(fullPath), "%s/%s", pathToDir, filename);
					if (stat(fullPath, &statbuf) == -1)
					{
						continue;
					}
					if (not( S_ISREG(statbuf.st_mode)))
					{
						free(filename);
						continue;
					}
					fileList = (char **)realloc(fileList, (numFiles + 1) * sizeof(char *));

					// CHECK IF MEMORY WAS ALLOCATED
					if (not(fileList))
					{
						errno = 1;
						fprintf(stderr, "%sERROR%s: Unable to retrive memory.\n", color1, color2);
						fprintf(stderr, "aliencrypt : MEMFAIL\n");
						return errno;
					}
					fileList[numFiles++] = filename;
				}
				closedir(directory);
			}
		}
		
		// HANDLE BOOLEAN VALUES BASED ON OPTIONS
		if (decryptFiles == true)
		{
			shredFiles = false;
			removeExif = false;
			encryptFiles = false;
		}
		if (showFiles == true)
		{
			encryptFiles = false;
			decryptFiles = false;
			showFileTypes = false;
			removeExif = false;
			shredFiles = false;
		}
		if (showFileTypes == true)
		{
			encryptFiles = false;
			decryptFiles = false;
			showFiles = false;
			removeExif = false;
			shredFiles = false;
		}
		if (showHelp == true)
		{
			encryptFiles = false;
			decryptFiles = false;
			showFiles = false;
			showFileTypes = false;
			removeExif = false;
			shredFiles = false;
			showLogo = false;
			showVersion = false;
		}
		if (showLogo == true)
		{
			encryptFiles = false;
			decryptFiles = false;
			showFiles = false;
			showFileTypes = false;
			removeExif = false;
			shredFiles = false;
			showHelp = false;
			showVersion = false;
		}
		if (showVersion == true)
		{
			encryptFiles = false;
			decryptFiles = false;
			showFiles = false;
			showFileTypes = false;
			removeExif = false;
			shredFiles = false;
			showLogo = false;
		}

		// EXECUTE FUNCTIONS BASED ON BOOLEAN VALUES
		PrintVersion(showVersion, versionNum);
		PrintUsage(showHelp);
		PrintLogo(showLogo, color1, color2);

		// CHECK OPERATING SYSTEM FOR BAD DIRS. IF THERE IS ONE, WARN THE USER
		#if defined(__linux__)
			
			// FUNCTIONS THAT DON'T NEED TO BE CHECKED FOR BAD DIRS CAN
			// BE EXECUTED BASED ON BOOLEAN VALUES
			ShowFiles(showFiles, fileList, pathToDir, numFiles, color1, color2, color3);
			ShowFileTypes(showFileTypes, fileList, numFiles, color1, color2, color3);

			// ITERATOR FOR WHILE LOOP
			int i = 0;

			// LIST OF BAD DIRECTORIES
			BadDir LinuxDirs[11] = {"/etc", "/bin", "/lib", "/boot", "/root", "/var", "/sys", "/proc", "/sbin",
			                        "/usr/bin", "/usr/sbin"};

			// CHECK THE USER PROVIDED PATH TO SEE IF IT MATCHES THE ONE OF THE BAD DIRECTORES. IF SO, RAISE AN ERROR
			while (i < 11)
			{
				if ((strstr(pathToDir, LinuxDirs[i]) != NULL) and ((showFiles == false) and showFileTypes == false))
				{
					errno = 1;
					fprintf(stderr, "%sWARNING%s: The directory you have entered is a sensitive directory.\n", color1, color2);
					fprintf(stderr, "aliencrypt : %s : %s\n", LinuxDirs[i], strerror(errno));
					return errno;
				}
				
				// INCREMENT
				i++;
			}

			// EXECUTE OPTIONS BASED ON BOOLEAN VALUES
			RemoveExif(removeExif, fileList, pathToDir, numFiles, color2);
			keyName = KeyNameGen(encryptFiles, color1, color2);
			EncryptFiles(encryptFiles, numFiles, fileList, pathToDir, keyName, color1, color2);
			ShredFiles(shredFiles, fileList, numFiles, pathToDir, color1, color2);
			DecryptFiles(decryptFiles, numFiles, fileList, pathToDir, keyPath, color1, color2);

		#elif defined(__APPLE__) and defined(__MACH__)

			// FUNCTIONS THAT DON'T NEED TO BE CHECKED FOR BAD DIRS CAN
			// BE EXECUTED BASED ON BOOLEAN VALUES
			ShowFiles(showFiles, fileList, pathToDir, numFiles, color1, color2, color3);
			ShowFileTypes(showFileTypes, fileList, numFiles, color1, color2, color3);

			// ITERATOR FOR WHILE LOOP
			int i = 0;

			// LIST OF BAD DIRECTORIES
			BadDir MacDirs[8] = {"/System", "/usr", "/bin", "/Library", "/Applications", "/private", "/var", "/sbin"};

			// CHECK THE USER PROVIDED PATH TO SEE IF IT MATCHES THE ONE OF THE BAD DIRECTORES. IF SO, RAISE AN ERROR
			while (i < 8)
			{
				if ((strstr(pathToDir, MacDirs[i]) != NULL) and ((showFiles == false) and showFileTypes == false))
				{
					errno = 1;
					fprintf(stderr, "%sWARNING%s: The directory you have entered is a sensitive directory.\n", color1, color2);
					fprintf(stderr, "aliencrypt : %s : %s\n", MacDirs[i], strerror(errno));
					return errno;
				}

				// INCREMENT
				i++;
			}

			// EXECUTE OPTIONS BASED ON BOOLEAN VALUES
			RemoveExif(removeExif, fileList, pathToDir, numFiles, color2);
			keyName = KeyNameGen(encryptFiles, color1, color2);
			EncryptFiles(encryptFiles, numFiles, fileList, pathToDir, keyName, color1, color2);
			ShredFiles(shredFiles, fileList, numFiles, pathToDir, color1, color2);
			DecryptFiles(decryptFiles, numFiles, fileList, pathToDir, keyPath, color1, color2);

		#endif // END OF OS CHECK AND FUNCTION EXECUTION

	} // END OF ROOT USER CHECK
	
	// INCREMENT FUNCTION CALL VARIABLE BECAUSE FUNCTION IS DONE
	numFunctionCalls++;

	// EVALUATE CLOCK TIME
	CLOCK_END = clock();
	CLOCK_TIME = ((double) (CLOCK_END - CLOCK_START)) / CLOCKS_PER_SEC;
	
	if (numFunctionCalls > 1)
	{
		printf("\n\n\033[38;5;231m[%u function calls executed in %lf seconds.]\n", numFunctionCalls, CLOCK_TIME);
	}
	else
	{
		printf("\n\n\033[38;5;231m[%u function call executed in %lf seconds.]\n", numFunctionCalls, CLOCK_TIME);
	}

	return 0;

} // END OF MAIN

// IF THE USER CHOOSES TO PRINT THE VERSION NUMBER, PRINT TO STDOUT
void PrintVersion(bool showVersion, char* versionNum)
{
	// IF STATEMENT GUARD
	if (showVersion == true)
	{
		fprintf(stdout, "aliencrypt %s\n", versionNum);

		// INCREMENT NUM FUNCTION CALLS BECAUSE FUNCTION IS DONE
		numFunctionCalls++;

	} // END OF IF STATEMENT GUARD
} // END OF PRINT VERSION FUNCTION

// IF THE USER CHOOSES TO PRINT THE USAGE MESSAGE, PRINT TO STDOUT
void PrintUsage(bool showHelp)
{
	// IF STATEMENT GUARD
	if (showHelp == true)
	{
		const char* usageMessage = "usage: sudo alien [--encrypt] [--decrypt] [--show-files]\n"
		                   	"                  [--show-file-types] [--remove-exif]\n"
				   	"                  [--shred] [--help [--path=path_to_dir]\n"
				   	"                  [--logo] [--color=1234567] [--version]\n";
		fprintf(stderr, "%s", usageMessage);

		// INCREMENT NUM FUNCTION CALLS BECAUSE FUNCTION IS DONE
		numFunctionCalls++;

	} // END OF IF STATEMENT GUARD
} // END OF PRINT USAGE MESSAGE FUNCTION

// IF THE USER CHOOSES TO SHOW THE LOGO, PRINT TO STDOUT
int PrintLogo(bool showLogo, char* color1, char* color2)
{
	// IF STATEMENT GUARD
	if (showLogo == true)
	{
		// DECLARE AND INITIALIZE EACH LINE IN THE PROGRAM LOGO
		char* L1 = "     dBBBBBb     dBP    dBP dBBBP  dBBBBb  dBBBP dBBBBBb dBP dBP dBBBBBb dBBBBBBP\n";
		char* L2 = "        BB                          dBP            dBP    dBP      dB'\n";
		char* L3 = "    dBP BB   dBP    dBP dBBP   dBP dBP dBP     dBBBBK    dBP   dBBBP'   dBP\n";
		char* L4 = "   dBP  BB  dBP    dBP dBP    dBP dBP dBP     dBP  BB   dBP   dBP      dBP\n";
		char* L5 = "  dBBBBBBB dBBBBP dBP dBBBBP dBP dBP dBBBBP  dBP  dB'  dBP   dBP      dBP\n";
		char* L6 = "\n";
		char* L7 = "                       Aliencrypt (Unix C Version)\n";
		char* L8 = "                   [Program designed by Bombenheimer]\n";
		char* L9 = "                    https://github.com/Bombenheimer/\n";
		char* L10 = "                                 v3.0.1\n";

		// GET THE LENGTH OF THE PROGRAM LOGO
		int programLogoLen = snprintf(NULL, 0, "%s%s %s %s %s %s%s %s %s %s %s %s%s", color1, L1, L2, L3, L4, L5, color2, L6, L7, L8, L9, color1, L10);
		
		// ALLOCATE ENOUGTH MEMORY FOR THE SPACE OF THE LOGO
		char* programLogo = (char *)malloc(programLogoLen + 1);

		// CHECK IF MEMORY WAS ALLOCATED
		if (not(programLogo))
		{
			errno = 1;
			fprintf(stderr, "%sERROR%s: Unable to retrive memory.\n", color1, color2);
			fprintf(stderr, "aliencrypt : MEMFAIL\n");
			return errno;
		}

		// FORMAT THE LOGO AND COPY AS A STRING
		snprintf(programLogo, programLogoLen + 1, "%s%s %s %s %s %s%s %s %s %s %s %s%s", color1, L1, L2, L3, L4, L5, color2, L6, L7, L8, L9, color1, L10);

		// CLEAR SCREEN
		system("clear");

		// PRINT LOGO
		printf("%s", programLogo);

		// FREE ALLOCATED MEMORY BACK TO SYSTEM
		free(programLogo);

		// INCREMENT NUM FUNCTION CALLS BECAUSE FUNCTION IS DONE
		numFunctionCalls++;

	}// END OF IF STATEMENT GUARD
	
	return 0;

} // END OF PRINT LOGO FUNCTION

// IF THE USER CHOOSES TO SHOW FILES, SHOW THEM IN STDOUT
void ShowFiles(bool showFiles, char** fileList, char* pathToDir, unsigned int numFiles, char* color1, char* color2, char* color3)
{
	// IF STATEMENT GUARD
	if (showFiles == true)
	{
		// CLEAR SCREEN
		system("clear");

		// TITLE AND CATEGORIES
		char* listLineHead1 = "                                    FILE LIST\n\n";
		char* listLineHead2 = "NUMBER          FILE SIZE                FILE PERMISSIONS  FILENAME\n\n";

		// STRUTCURE TO HOLD FILE METADATA
		struct stat file_stat;

		// PRINT TITLE AND CATEGORIES
		printf("%s%s%s%s", color1, listLineHead1, listLineHead2, color2);

		// OUTER LOOP FOR NUM FILES
		for (unsigned int i = 0; i < numFiles; i++)
		{
			// ALLOCATE MEMORY FOR FULL FILE PATH
			char* pathToFile = (char *)malloc(strlen(pathToDir) + strlen(fileList[i]) + 2);

			// COPY PATH TO DIRECTORY TO FULL FILE PATH VARIABLE
			strcpy(pathToFile, pathToDir);

			// IF THERE IS NO DIRECTORY SEPARATOR AT THE END OF THE
			// USER PROVIDED PATH, APPEND ONE
			if (pathToDir[strlen(pathToDir) - 1] != '/')
			{
				strcat(pathToFile, "/");
			}

			// APPEND THE FILENAME TO THE FULL FILE PATH VARIABLE
			strcat(pathToFile, fileList[i]);

			// CHECK IF FILE METADATA CAN BE RETRIVED
			if (stat(pathToFile, &file_stat) == 0)
			{
				// FILE METADATA
				mode_t permissions = file_stat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
				double size = file_stat.st_size;
				char size_unit[4];

				// GET FILE SIZE UNIT
				if (size >= 0 and size <= 1023)
				{
					strcpy(size_unit, "BiB");
				}
				if (size >= 1024 and size <= 1048575)
				{
					strcpy(size_unit, "KiB");
					size = size / 1024;
				}
				if (size >= 1048576 and size <= 1073741823)
				{
					strcpy(size_unit, "MiB");
					size = size / (pow(1024, 2));
				}
				if (size >= 1073741824 and size <= 1099511627775)
				{
					strcpy(size_unit, "GiB");
					size = size / (pow(1024, 3));
				}
				if (size >= 1099511627776 and size <= 1125899906842623)
				{
					strcpy(size_unit, "TiB");
					size = size / (pow(1024, 4));
				}

				if (i + 1 < 10)
				{
					printf("%s%d%s...............%06.2lf %s...............%o...............%s\n\n", color3, i + 1, color2, size, size_unit, permissions, fileList[i]);
				}
				if (i + 1 >= 10)
				{
					printf("%s%d%s..............%06.2lf %s...............%o...............%s\n\n", color3, i + 1, color2, size, size_unit, permissions, fileList[i]);
				}
				if (i + 1 >= 100)
				{
					printf("%s%d%s.............%06.2lf %s...............%o...............%s\n\n", color3, i + 1, color2, size, size_unit, permissions, fileList[i]);
				}
				if (i + 1 >= 1000)
				{
					printf("%s%d%s............%06.2lf %s...............%o...............%s\n\n", color3, i + 1, color2, size, size_unit, permissions, fileList[i]);
				}
			}
			else
			{
				perror("Error in show files.\n");
			}

			// FREE MEMORY BACK TO SYSTEM
			free(pathToFile);
			free(fileList[i]);

		} // END OF NUM FILES LOOP

		// FREE MEMORY BACK TO SYSTEM
		free(fileList);
		
		// INCREMENT NUM FUNCTION CALLS BECAUSE FUNCTION IS DONE
		numFunctionCalls++;

	} // END OF IF STATEMENT GUARD
} // END OF SHOW FILES FUCNTION

// IF THE USER CHOOSES TO SHOW ALL FILE TYPES, SHOW THEM IN STDOUT
void ShowFileTypes(bool showFileTypes, char** fileList, unsigned int numFiles, char* color1, char* color2, char* color3)
{
	if (showFileTypes == true)
	{
		// ARCHIVE FILE EXTENTIONS
		const char* archiveTypes[ARCHIVE_NUM] = {".7z", ".ace", ".alz", ".arc", ".arj", ".bz", ".bz2", ".cab", ".cpio", ".deb",
	                                         	 ".dmg", ".gz", ".img", ".iso", ".jar", ".lha", ".lz", ".lzma", ".lzo", ".rar",
	                                         	 ".rpm", ".rz", ".tar", ".tar.7z", ".tar.bz", ".tar.bz2", ".tar.gz", ".tar.lzo", ".tar.xz",
						 	 ".tar.z", ".tbz", ".tbz2", ".tgz", ".tz", ".tzo", ".xz", ".z", ".zip"};

		// AUDIO FILE EXTENTIONS
		const char* audioTypes[AUDIO_NUM] = {".aac", ".ac3", ".aif", ".aifc", ".aiff", ".amr", ".au", ".caf", ".flac", ".m4a",
	                                     	     ".m4b", ".mp3", ".oga", ".voc", ".wav", ".weba", ".wma"};

		// CAD FILE EXTENTIONS
		const char* cadTypes[CAD_NUM] = {".wdg", ".dxf"};

		const char* documentTypes[DOC_NUM] = {".abw", ".djvu", ".doc", ".docm", ".docx", ".dot", ".dotx", ".html", ".hwp", ".lwp",
	                                      	      ".md", ".odt", ".pages", ".pdf", ".rst", ".rtf", ".tex", ".txt", ".wpd", ".wps", ".zabw"};

		// EBOOK FILE EXTENTIONS
		const char* ebookTypes[EBOOK_NUM] = {".azw", ".azw3", ".azw4", ".cbc", ".cbr", ".cbz", ".chm", ".epub", ".fb2", ".htm",
	                                             ".htmlz", ".lit", ".lrf", ".mobi", ".pdb", ".pml", ".prc", ".rb", ".snb", ".tcr", ".txtz"};

		// FONT FILE EXTENTIONS
		const char* fontTypes[FONT_NUM] = {".eot", ".otf", ".ttf", ".woff", ".woff2"};

		// IMAGE FILE EXTENTIONS
		const char* imageTypes[IMAGE_NUM] = {".3fr", ".arw", ".avif", ".bmp", ".cr2", ".cr3", ".crw", ".dcr", ".dng", ".eps",
	                                             ".erf", ".gif", ".heic", ".heif", ".icns", ".ico", ".jfif", ".jpeg", ".jpg", ".mos",
	                                             ".mrw", ".nef", ".odd", ".odg", ".orf", ".pef", ".png", ".ppm", ".ps", ".psd",
	                                             ".raf", ".raw", ".rw2", ".tif", ".tiff", ".webp", ".x3f", ".xcf", ".xps"};

		// PRESENTATION FILE EXTENTIONS
		const char* presentationTypes[PRESENT_NUM] = {".dps", ".key", ".odp", ".pot", ".potx", ".pps", ".ppsx", ".ppt", ".pptm", ".pptx"};

		// SPREADSHEET FILE EXTENTIONS
		const char* spreadsheetTypes[SSHEET_NUM] = {".csv", ".et", ".ods", ".xls", ".xlsm", ".xlsx", ".numbers"};

		// VECTOR FILE EXTENTIONS
		const char* vectorTypes[VECTOR_NUM] = {".ai", ".cdr", ".cgm", ".emf", ".sk", ".sk1", ".svg", ".svgz", ".vsd", ".wmf"};

		// VIDEO FILE EXTENTIONS
		const char* videoTypes[VIDEO_NUM] = {".3g2", ".3gp", ".3gpp", ".avi", ".cavs", ".dv", ".dvr", ".flv", ".m2ts", ".m4v",
	                                             ".mkv", ".mod", ".mov", ".mp4", ".mpeg", ".mpg", ".mts", ".mxf", ".ogg", ".rm",
	                                             ".rmvb", ".swf", ".ts", ".vob", ".webm", ".wmv", ".wtv"};

		// SCRIPT OR PROGRAMMING LANGUAGE FILE EXTENTIONS
		const char* scriptTypes[SCRIPT_NUM] = {".py", ".c", ".java", ".sh", ".cpp", ".lol", ".js", ".asm", ".cmd", ".bat",
	                                               ".php", ".lua", ".ps1", ".vbs", ".swift", ".sql", ".cs"};

		// BINARY FILE EXTENTIONS
		const char* binaryTypes[BINARY_NUM] = {".exe", ".out", ".dll", ".bin", ".elf", ".app", ".apk", ".so", ".class", ".jar"};

		// CONFIGURATION FILE EXTENTIONS
		const char* configTypes[CONFIG_NUM] = {".ini", ".cfg", ".conf", ".properties", ".yaml", ".yml"};

		// TEMPORARY FILE EXTENTIONS
		const char* tempTypes[TEMP_NUM] = {".tmp", ".temp"};

		// METADATA FILE EXTENTIONS
		const char* metadataTypes[META_NUM] = {".json", ".meta", ".xml"};

		// BACKUP FILE EXTENTIONS
		const char* backupTypes[BACKUP_NUM] = {".old", ".bkp", ".backup", ".bak"};

		// DATABASE FILE EXTENTIONS
		const char* databaseTypes[DB_NUM] = {".db", ".sqlite", ".mdb"};

		// LOG FILE EXTENTIONS
		const char* logTypes[LOG_NUM] = {".log"};

		// NUMBER OF EACH FILE TYPE
		struct NumFileTypes NumFile = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

		// OUTER LOOP FOR NUMBER OF FILES
		for (unsigned int i = 0; i < numFiles; i++)
		{
			// SEARCH FOR EXTENTION AND FILENAME SEPERATOR
			char* dotptr = strrchr(fileList[i], '.');

			// CHECK IF THE SEARCH RETURNED A NULL. IF SO, THEN IT MEANS ITS PROBABLY AN EXECUTABLE
			if (dotptr != NULL)
			{
				const char* fileExtention = strchr(fileList[i], '.');

				// INNER LOOP FOR FILE TYPE ARCHIVE
				for (int j = 0; j < ARCHIVE_NUM; j++)
				{
					// CHECK IF THE FILE EXTENTION IS AN EXACT MATCH. IF NOT, CONTINUE
					if (strcmp(fileExtention, archiveTypes[j]) == 0)
					{
						NumFile.archive++;
						free(fileList[i]);
						break;
					}
					else
					{
						continue;
					}
				}

				// INNER LOOP FOR FILE TYPE AUDIO
				for (int j = 0; j < AUDIO_NUM; j++)
				{
					// CHECK IF THE FILE EXTENTION IS AN EXACT MATCH. IF NOT, CONTINUE
					if (strcmp(fileExtention, audioTypes[j]) == 0)
					{
						NumFile.audio++;
						free(fileList[i]);
						break;
					}
					else
					{
						continue;
					}
				}

				// INNER LOOP FOR FILE TYPE CAD
				for (int j = 0; j < CAD_NUM; j++)
				{
					// CHECK IF THE FILE EXTENTION IS AN EXACT MATCH. IF NOT, CONTINUE
					if (strcmp(fileExtention, cadTypes[j]) == 0)
					{
						NumFile.cad++;
						free(fileList[i]);
						break;
					}
					else
					{
						continue;
					}
				}

				// INNER LOOP FOR FILE TYPE DOCUMENT
				for (int j = 0; j < DOC_NUM; j++)
				{
					// CHECK IF THE FILE EXTENTION IS AN EXACT MATCH. IF NOT, CONTINUE
					if (strcmp(fileExtention, documentTypes[j]) == 0)
					{
						NumFile.document++;
						free(fileList[i]);
						break;
					}
					else
					{
						continue;
					}
				}

				// INNER LOOP FOR FILE TYPE EBOOK
				for (int j = 0; j < EBOOK_NUM; j++)
				{
					// CHECK IF THE FILE EXTENTION IS AN EXACT MATCH. IF NOT, CONTINUE
					if (strcmp(fileExtention, ebookTypes[j]) == 0)
					{
						NumFile.ebook++;
						free(fileList[i]);
						break;
					}
					else
					{
						continue;
					}
				}
		
			
				// INNER LOOP FOR FILE TYPE FONT
				for (int j = 0; j < FONT_NUM; j++)
				{
					// CHECK IF THE FILE EXTENTION IS AN EXACT MATCH. IF NOT, CONTINUE
					if (strcmp(fileExtention, fontTypes[j]) == 0)
					{
						NumFile.font++;
						free(fileList[i]);
						break;
					}
					else
					{
						continue;
					}
			
				}

				// INNER LOOP FOR FILE TYPE IMAGE
				for (int j = 0; j < IMAGE_NUM; j++)
				{
					// CHECK IF THE FILE EXTENTION IS AN EXACT MATCH. IF NOT, CONTINUE
					if (strcmp(fileExtention, imageTypes[j]) == 0)
					{
						NumFile.image++;
						free(fileList[i]);
						break;
					}
					else
					{
						continue;
					}
				}

				// INNER LOOP FOR FILE TYPE PRESENTATION
				for (int j = 0; j < PRESENT_NUM; j++)
				{
					// CHECK IF THE FILE EXTENTION IS AN EXACT MATCH. IF NOT, CONTINUE
					if (strcmp(fileExtention, presentationTypes[j]) == 0)
					{
						NumFile.presentation++;
						free(fileList[i]);
						break;
					}
					else
					{
						continue;
					}
				}
		
				// INNER LOOP FOR FILE TYPE SPREADSHEET
				for (int j = 0; j < SSHEET_NUM; j++)
				{
					// CHECK IF THE FILE EXTENTION IS AN EXACT MATCH. IF NOT, CONTINUE
					if (strcmp(fileExtention, spreadsheetTypes[j]) == 0)
					{
						NumFile.spreadsheet++;
						free(fileList[i]);
						break;
					}
					else
					{
						continue;
					}
				}
		
				// INNER LOOP FOR FILE TYPE VECTOR
				for (int j = 0; j < VECTOR_NUM; j++)
				{
					// CHECK IF THE FILE EXTENTION IS AN EXACT MATCH. IF NOT, CONTINUE
					if (strcmp(fileExtention, vectorTypes[j]) == 0)
					{
						NumFile.vector++;
						free(fileList[i]);
						break;
					}
					else
					{
						continue;
					}
				}

				// INNER LOOP FOR FILE TYPE VIDEO
				for (int j = 0; j < VIDEO_NUM; j++)
				{
					// CHECK IF THE FILE EXTENTION IS AN EXACT MATCH. IF NOT, CONTINUE
					if (strcmp(fileExtention, videoTypes[j]) == 0)
					{
						NumFile.video++;
						free(fileList[i]);
						break;
					}
					else
					{
						continue;
					}
				}

				// INNER LOOP FOR FILE TYPE SCRIPT
				for (int j = 0; j < SCRIPT_NUM; j++)
				{
					// CHECK IF THE FILE EXTENTION IS AN EXACT MATCH. IF NOT, CONTINUE
					if (strcmp(fileExtention, scriptTypes[j]) == 0)
					{
						NumFile.script++;
						free(fileList[i]);
						break;
					}
					else
					{
						continue;
					}
				}

				// INNER LOOP FOR FILE TYPE BINARY
				for (int j = 0; j < BINARY_NUM; j++)
				{	
					// CHECK IF THE FILE EXTENTION IS AN EXACT MATCH. IF NOT, CONTINUE
					if (strcmp(fileExtention, binaryTypes[j]) == 0)
					{
						NumFile.binary++;
						free(fileList[i]);
						break;
					}
					else
					{
						continue;
					}
				}
		
				// INNER LOOP FOR FILE TYPE CONFIG
				for (int j = 0; j < CONFIG_NUM; j++)
				{
					// CHECK IF THE FILE EXTENTION IS AN EXACT MATCH. IF NOT, CONTINUE
					if (strcmp(fileExtention, configTypes[j]) == 0)
					{
						NumFile.configuration++;
						free(fileList[i]);
						break;
					}
					else
					{
						continue;
					}
				}

				// INNER LOOP FOR FILE TYPE TEMP
				for (int j = 0; j < TEMP_NUM; j++)
				{
					// CHECK IF THE FILE EXTENTION IS AN EXACT MATCH. IF NOT, CONTINUE
					if (strcmp(fileExtention, tempTypes[j]) == 0)
					{
						NumFile.temporary++;
						free(fileList[i]);
						break;
					}
					else
					{
						continue;
					}
				}
		
				// INNER LOOP FOR FILE TYPE 
				for (int j = 0; j < META_NUM; j++)
				{
					// CHECK IF THE FILE EXTENTION IS AN EXACT MATCH. IF NOT, CONTINUE
					if (strcmp(fileExtention, metadataTypes[j]) == 0)
					{
						NumFile.metadata++;
						free(fileList[i]);
						break;
					}
					else
					{
						continue;
					}
				}

				// INNER LOOP FOR FILE TYPE BACKUP
				for (int j = 0; j < BACKUP_NUM; j++)
				{
					// CHECK IF THE FILE EXTENTION IS AN EXACT MATCH. IF NOT, CONTINUE
					if (strcmp(fileExtention, backupTypes[j]) == 0)
					{
						NumFile.backup++;
						free(fileList[i]);
						break;
					}
					else
					{
						continue;
					}
				}

				// INNER LOOP FOR FILE TYPE DATABASE
				for (int j = 0; j < DB_NUM; j++)
				{
					// CHECK IF THE FILE EXTENTION IS AN EXACT MATCH. IF NOT, CONTINUE
					if (strcmp(fileExtention, databaseTypes[j]) == 0)
					{
						NumFile.database++;
						free(fileList[i]);
						break;
					}
					else
					{
						continue;
					}
				}

				// INNER LOOP FOR FILE TYPE LOG
				for (int j = 0; j < LOG_NUM; j++)
				{
					// CHECK IF THE FILE EXTENTION IS AN EXACT MATCH. IF NOT, CONTINUE
					if (strcmp(fileExtention, logTypes[j]) == 0)
					{
						NumFile.log++;
						free(fileList[i]);
						break;
					}
					else
					{
						continue;
					}
				}
			}
			else
			{
				NumFile.binary++;

			} // END OF FILE EXTENTION CHECK
		} // END OF FILE TYPE CHECK

		// FREE MEMORY BACK TO SYSTEM
		free(fileList);

		// PRINT NUMBER OF EACH FILE TYPE TO STDOUT
		printf("                                %sFILE TYPES\n\n", color1);
		printf("%sAll Files: %s%d\033[38;5;231m\n\n", color2, color3, numFiles);
		printf("%sArchive and Package Files: %s%d\033[38;5;231m\n\n", color2, color3, NumFile.archive);
		printf("%sAudio Files: %s%d\033[38;5;231m\n\n", color2, color3, NumFile.audio);
		printf("%sCad Files: %s%d\033[38;5;231m\n\n", color2, color3, NumFile.cad);
		printf("%sDocument Files: %s%d\033[38;5;231m\n\n", color2, color3, NumFile.document);
		printf("%sEbook Files: %s%d\033[38;5;231m\n\n", color2, color3, NumFile.ebook);
		printf("%sFont Files: %s%d\033[38;5;231m\n\n", color2, color3, NumFile.font);
		printf("%sImage Files: %s%d\033[38;5;231m\n\n", color2, color3, NumFile.image);
		printf("%sPresentation Files: %s%d\033[38;5;231m\n\n", color2, color3, NumFile.presentation);
		printf("%sSpreadsheet Files: %s%d\033[38;5;231m\n\n", color2, color3, NumFile.spreadsheet);
		printf("%sVector Files: %s%d\033[38;5;231m\n\n", color2, color3, NumFile.vector);
		printf("%sVideo Files: %s%d\033[38;5;231m\n\n", color2, color3, NumFile.video);
		printf("%sScript Files: %s%d\033[38;5;231m\n\n", color2, color3, NumFile.script);
		printf("%sBinary and Executable Files: %s%d\033[38;5;231m\n\n", color2, color3, NumFile.binary);
		printf("%sConfiguration Files: %s%d\033[38;5;231m\n\n", color2, color3, NumFile.configuration);
		printf("%sTemporary Files: %s%d\033[38;5;231m\n\n", color2, color3, NumFile.temporary);
		printf("%sMetadata Files: %s%d\033[38;5;231m\n\n", color2, color3, NumFile.metadata);
		printf("%sBackup Files: %s%d\033[38;5;231m\n\n", color2, color3, NumFile.backup);
		printf("%sDatabase Files: %s%d\033[38;5;231m\n\n", color2, color3, NumFile.database);
		printf("%sLog Files: %s%d\033[38;5;231m\n\n", color2, color3, NumFile.log);

		// INCREMENT NUM FUNCTION CALLS BECAUSE FUNCTION IS DONE
		numFunctionCalls++;

	} // END OF IF STATEMENT GUARD
} // END OF SHOW FILE TYPES FUNCTION

// IF THE USER CHOOSES TO REMOVE EXIF METADATA FROM FILES, REMOVE ALL DATA AND SHOW STATUS TO STDOUT
void RemoveExif(bool removeExif, char** fileList, char* pathToDir, unsigned int numFiles, char* color2)
{
	if (removeExif == true)
	{
		// PRINT SPACE BEFORE PROGRAM START
		printf("\n\n");

		// INDICATE SUCCESS OR FAIL
		const char* X_MARK_COL = "\033[38;5;160m";
		const char* CHECK_MARK_COL = "\033[38;5;119m";
		const char* X = "\xE2\x9C\x97";
		const char* CHECK = "\xE2\x9C\x94";

		// PRINT START OF PROGRAM STATUS TO STDOUT
		printf("%sRemoving exif metadata...\033[38;5;231m\n", color2);

		// VARIABLES FOR EXIF MARKERS
		unsigned char exif_marker[] = {0xFF, 0xE1};
		unsigned char marker[2];

		// FOR LOOP FOR NUM FILES	
		for (unsigned int i = 0; i < numFiles; i++)
		{
			// ALLOCATE MEMORRY FOR FULL FILE PATH
			char* pathToFile = (char *)malloc(strlen(pathToDir) + strlen(fileList[i]) + 2);

			// COPY PATH TO DIRECTORY TO FULL FILE PATH VARIABLE
			strcpy(pathToFile, pathToDir);

			// IF THERE IS NO DIRECTORY SEPARATOR AT THE END OF THE
			// USER PROVIDED PATH, APPEND ONE
			if (pathToDir[strlen(pathToDir) - 1] != '/')
			{
				strcat(pathToFile, "/");
			}

			// APPEND THE FILENAME TO THE FULL FILE PATH VARIABLE
			strcat(pathToFile, fileList[i]);

			// LOAD EXIF DATA
			ExifData *exif_data = exif_data_new_from_file(pathToFile);
			
			// REMOVE AND SAVE EXIF DATA AND PRINT STATUS TO STDOUT. OTHERWISE
			// PRINT THAT THE EXIF LOAD PROCESS FAILED
			if (exif_data != NULL)
			{
				// OPEN FILE FOR READING AND WRITING
				FILE *readfile = fopen(pathToFile, "rb");
				FILE *writefile = fopen(pathToFile, "wb");

				// CHECK IF FILE CAN BE OPENED
				if (readfile == NULL and writefile == NULL)
				{
					printf("%s%s%s: %s\n", X_MARK_COL, X, color2, pathToFile);
					free(pathToFile);
					continue;
				}

				// SEARCH FOR EXIF MARKER AND SKIP ANY EXIF DATA THAT MATCHES THE MARKERS
				while (fread(marker, sizeof(unsigned char), 2, readfile) == 2)
				{
					if ((marker[0] == exif_marker[0]) and (marker[1] == exif_marker[1]))
					{
						fseek(readfile, 18, SEEK_CUR);
						break;
					}
				}

				// PUT DATA WIHOUT EXIF BACK INTO THE FILE
				int c;
				while ((c = fgetc(readfile)) != EOF)
				{
					fputc(c, writefile);
				}

				fclose(readfile);
				fclose(writefile);
				
				exif_data_unref(exif_data); // FREE MEMORY BACK TO SYSTEM
				printf("%s%s%s: %s\n", CHECK_MARK_COL, CHECK, color2, pathToFile);
				free(pathToFile);
			}
			else
			{
				printf("%s%s%s: %s\n", X_MARK_COL, X, color2, pathToFile);
				free(pathToFile);
				continue;
			}

		} // END OF FILE LOOPING

		// INCREMENT NUM FUNCTION CALLS BECAUSE FUNCTION IS DONE
		numFunctionCalls++;

	} // END OF IF STATEMENT GUARD
} // END OF REMOVE EXIF METADATA FUNCTION

// IF THE USER CHOOSES TO ENCRYPT FILES, FIRST GENERATE A NAME FOR THE KEY
char* KeyNameGen(bool encryptFiles, char* color1, char* color2)
{
	// ALLOCATE SPACE FOR THE KEY NAME
	char* fullKeyName = (char *)malloc(sizeof(char *) * KEY_NAME_LEN + 9);

	// CHECK IF MEMORY WAS ALLOCATED
	if (not(fullKeyName))
	{
		errno = 1;
		fprintf(stderr, "%sERROR%s: Unable to retrive memory.\n", color1, color2);
		fprintf(stderr, "aliencrypt : MEMFAIL\n");
		exit(1);
	}

	// IF STATEMENT GUARD
	if (encryptFiles == true)
	{

		// PRINT SPACE BEFORE PROGRAM START
		printf("\n\n");

		// CHAR SETS
		const char* keyChars[] = {"0123456789", "ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

		// FORMATED STRING AND ARRAY TO HOLD GENERATED KEYNAME
		char* keyName = "KEY-%s.key";
		char genString[KEY_NAME_LEN + 1];

		// PRINT START OF OPERATION STATUS TO STDOUT
		printf("%sGenerating key for decryption...\033[38;5;231m\n", color2);
		
		// SEED THE RANDOM NUMBER GENERATOR
		srand(time(NULL));

		// GENERATE KEYNAME
		for (int i = 0; i < KEY_NAME_LEN - 1;)
		{
			int charSet = rand() % 2;
			int charSetLen = strlen(keyChars[charSet]);

			if ((charSet == 0) or (charSet == 1))
			{
				genString[i++] = keyChars[charSet][rand() % charSetLen];
			}
		}

		// NULL TERMINATE GENERATED STRING
		genString[KEY_NAME_LEN - 1] = '\0';
		
		// COPY CONTENTS TO KEYNAME VARIABLE
		snprintf(fullKeyName, KEY_NAME_LEN + 9, keyName, genString);

		// INCREMENT NUM OF FUNCTION CALLS BECAUSE FUNCTION IS DONE
		numFunctionCalls++;

		return fullKeyName;

	} // END OF IF STATEMENT GUARD
	
	free(fullKeyName);
	
	return NULL;

} // END OF KEY NAME GENERATION FUNCTION

// IF THE USER CHOOSES TO REMOVE ENCRYPT FILES, ENCRYPT THEM AND SHOW THEIR STATUS TO STDOUT
int EncryptFiles(bool encryptFiles, unsigned int numFiles, char** fileList, char* pathToDir, char* keyName, char* color1, char* color2)
{
	// IF STATEMENT GUARD
	if (encryptFiles == true)
	{
		// INDICATE SUCCESS OR FAIL
		const char* X_MARK_COL = "\033[38;5;160m";
		const char* CHECK_MARK_COL = "\033[38;5;119m";
		const char* X = "\xE2\x9C\x97";
		const char* CHECK = "\xE2\x9C\x94";

		// PRINT WHERE THE KEY IS SAVED IN STDOUT
		printf("Key is saved in : %s%s\n", color1, keyName);

		// PRINT START OF PROGRAM STATUS TO STDOUT
		printf("%sStarting encryption...\033[38;5;231m\n", color2);

		// GENERATE RANDOM KEY
		unsigned char key[KEY_SIZE];
		randombytes_buf(key, KEY_SIZE);

		// WRITE KEY TO KEY FILE
		FILE *keyGen = fopen(keyName, "wb");
		fwrite(key, 1, KEY_SIZE, keyGen);
		fclose(keyGen);

		// FOR LOOP FOR NUM FILES
		for (unsigned int i = 0; i < numFiles; i++)
		{
			// ALLOCATE MEMORY FOR FULL FILE PATH
			char* pathToFile = (char *)malloc(strlen(pathToDir) + strlen(fileList[i]) + 2);

			// CHECK IF MEMORY WAS ALLOCATED
			if (not(pathToFile))
			{
				errno = 1;
				fprintf(stderr, "%sERROR%s: Unable to retrive memory.\n", color1, color2);
				fprintf(stderr, "aliencrypt : MEMFAIL\n");
				return errno;
			}

			// COPY PATH TO DIRECTORY TO FULL FILE PATH VARIABLE
			strcpy(pathToFile, pathToDir);

			// IF THERE IS NO DIRECTORY SEPARATOR AT THE END OF THE
			// USER PROVIDED PATH, APPEND ONE
			if (pathToDir[strlen(pathToDir) - 1] != '/')
			{
				strcat(pathToFile, "/");
			}

			// APPEND THE FILENAME TO THE FULL FILE PATH VARIABLE
			strcat(pathToFile, fileList[i]);
			
			// OPEN FILE FOR READING
			FILE *readfile = fopen(pathToFile, "rb");

			// TEST IF FILE CAN BE OPENED. IF NOT, PRINT FAIL STATUS AND CONTINUE
			if (readfile == NULL)
			{
				printf("%s%s%s: %s\n", X_MARK_COL, X, color2, pathToFile);
				free(pathToFile);
				continue;
			}

			// GET FILE SIZE OF FILE
			fseek(readfile, 0, SEEK_END);
			long inputSize = ftell(readfile);
			fseek(readfile, 0, SEEK_SET);

			// ALLOCATE MEMORY FOR FILE DATA
			unsigned char *inputData = (unsigned char *)malloc(inputSize);

			// CHECK IF MEMORY WAS ALLOCATED
			if (not(inputData))
			{
				fclose(readfile);
				errno = 1;
				fprintf(stderr, "%sERROR%s: Unable to retrive memory.\n", color1, color2);
				fprintf(stderr, "aliencrypt : MEMFAIL\n");
				return errno;
			}

			// READ THE FILE DATA
			fread(inputData, 1, inputSize, readfile);
			fclose(readfile);

			// GENERATE A RANDOM NONCE
			unsigned char nonce[NONCE_SIZE];
			randombytes_buf(nonce, NONCE_SIZE);

			// ALLOCATE MEMORY FOR THE ENCRYPTED DATA
			unsigned char *encrypted_data = (unsigned char *)malloc(inputSize + TAG_SIZE);
			unsigned char tag[TAG_SIZE];

			// CHECK IF MEMORY WAS ALLOCATED
			if (not(encrypted_data))
			{
				free(pathToFile);
				errno = 1;
				fprintf(stderr, "%sERROR%s: Unable to retrive memory.\n", color1, color2);
				fprintf(stderr, "aliencrypt : MEMFAIL\n");
				return errno;
			}

			// ENCRYPT THE DATA
			if (crypto_secretbox_detached(encrypted_data, tag, inputData, inputSize, nonce, key) != 0)
			{
				errno = 1;
				fprintf(stderr, "%sERROR%s: Unable to encrypt file %s.\n", color1, color2, pathToFile);
				fprintf(stderr, "aliencrypt : ENCRYPT_ERR\n");
				free(inputData);
				free(encrypted_data);
				free(pathToFile);
				return errno;
			}

			// OPEN FILE TO WRITE
			FILE *writefile = fopen(pathToFile, "wb");

			// CHECK IF FILE CAN BE WRITTEN TO
			if (writefile == NULL)
			{
				printf("%s%s%s: %s\n", X_MARK_COL, X, color2, pathToFile);
				free(inputData);
				free(encrypted_data);
				free(fileList[i]);
				free(pathToFile);
				continue;
			}

			// WRITE ENCRYPTED DATA BACK TO FILE
			fwrite(nonce, 1, NONCE_SIZE, writefile);
			fwrite(tag, 1, TAG_SIZE, writefile);
			fwrite(encrypted_data, 1, inputSize, writefile);
			fclose(writefile);
			
			// PRINT SUCCESS STATUS TO STDOUT
			printf("%s%s%s: %s\n", CHECK_MARK_COL, CHECK, color2, pathToFile);

			// FREE MEMORY BACK TO SYSTEM
			free(inputData);
			free(encrypted_data);
			free(pathToFile);

		} // END OF FILE LOOPING

		// FREE MEMORY BACK TO SYSTEM
		free(keyName);

		// INCREMENT NUM OF FUNCTION CALLS BECAUSE FUNCTION IS DONE
		numFunctionCalls++;

	} // END OF IF STATEMENT GUARD
	
	return 0;

} // END OF ENCRYPT FILES FUNCTION

// IF THE USER CHOOSES TO OVERWRITE AND DELETE THE FILES, OVERWRITE AND DELETE THEM AND SHOW THEIR STATUS IN STDOUT
int ShredFiles(bool shredFiles, char** fileList, unsigned int numFiles, char* pathToDir, char* color1, char* color2)
{
	if (shredFiles == true)
	{
		// PRINT SPACE BEFORE PROGRAM START
		printf("\n\n");

		// INDICATE SUCCESS OR FAIL
		const char* X_MARK_COL = "\033[38;5;160m";
		const char* CHECK_MARK_COL = "\033[38;5;119m";
		const char* X = "\xE2\x9C\x97";
		const char* CHECK = "\xE2\x9C\x94";

		// PRINT START OF PROGRAM STATUS TO STDOUT
		printf("%sStarting file shreding...\033[38;5;231m\n", color2);

		// FOR LOOP FOR NUM FILES
		for (unsigned int i = 0; i < numFiles; i++)
		{
			// ALLOCATE MEMORY FOR FULL FILE PATH
			char* pathToFile = (char *)malloc(strlen(pathToDir) + strlen(fileList[i]) + 2);

			// CHECK IF MEMORY WAS ALLOCATED
			if (not(pathToFile))
			{
				errno = 1;
				fprintf(stderr, "%sERROR%s: Unable to retrive memory.\n", color1, color2);
				fprintf(stderr, "aliencrypt : MEMFAIL\n");
				return errno;
			}

			// COPY PATH TO DIRECTORY TO FULL FILE PATH VARIABLE
			strcpy(pathToFile, pathToDir);

			// IF THERE IS NO DIRECTORY SEPARATOR AT THE END OF THE
			// USER PROVIDED PATH, APPEND ONE
			if (pathToDir[strlen(pathToDir) - 1] != '/')
			{
				strcat(pathToFile, "/");
			}

			// APPEND THE FILENAME TO THE FULL FILE PATH VARIABLE
			strcat(pathToFile, fileList[i]);

			// OPEN THE FILE FOR READING AND WRITING AND INITIALIZE BUFFER AND BYTES
			FILE *file = fopen(pathToFile, "rb+");
			unsigned char buffer[BUFFER_SIZE];
			size_t bytes_read;

			// CHECK IF FILE CAN BE OPENED FOR READING AN WRITING
			if (file == NULL)
			{
				printf("%s%s%s: %s\n", X_MARK_COL, X, color2, pathToFile);
				free(pathToFile);
				free(fileList[i]);
				continue;
			}

			// OVERWRITE THR FILE WITH RANDOM BYTES OF DATA
			for (int pass = 0; pass < NUM_PASSES; pass++)
			{
				// RESET FILE POSITION TO BEGINNING
				fseek(file, 0, SEEK_SET);

				// FILL BUFFER WITH DATA
				while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0)
				{
					for (size_t i = 0; i < bytes_read; i++)
					{
						buffer[i] = rand() % 256;
					}

					// MOVE POSITION BACK TO BEFORE READ AND WRITE DATA BACK TO FILE
					fseek(file, -bytes_read, SEEK_CUR);
					fwrite(buffer, 1, bytes_read, file);
				}

				// FLUSH CHANGES TO DISK
				fflush(file);
			}

			// CLOSE THE FILE
			fclose(file);

			// DELETE FILE FROM SYSTEM
			unlink(pathToFile);

			// PRINT SUCCESS STATUS TO STDOUT
			printf("%s%s%s: %s\n", CHECK_MARK_COL, CHECK, color2, pathToFile);

			// FREE MEMORY BACK TO SYSTEM
			free(pathToFile);

		} // END OF NUM FILE LOOP

		// INCREMENT NUM FUNCTION CALLS BECAUSE FUNCTION IS DONE
		numFunctionCalls++;

	} // END OF IF STATEMENT GUARD
	
	return 0;

} // END OF SHRED FILES FUNCTION

// IF THE USER CHOOSES TO REMOVE ENCRYPT FILES, ENCRYPT THEM AND SHOW THEIR STATUS TO STDOUT
int DecryptFiles(bool decryptFiles, unsigned int numFiles, char** fileList, char* pathToDir, char* keyPath, char* color1, char* color2)
{
	// IF STATEMENT GUARD
	if (decryptFiles == true)
	{
		// INDICATE SUCCESS OR FAIL
		const char* X_MARK_COL = "\033[38;5;160m";
		const char* CHECK_MARK_COL = "\033[38;5;119m";
		const char* X = "\xE2\x9C\x97";
		const char* CHECK = "\xE2\x9C\x94";

		// PRINT START OF PROGRAM STATUS TO STDOUT
		printf("%sStarting file shreding...\033[38;5;231m\n", color2);

		// FOR LOOP FOR NUM FILES
		for (unsigned int i = 0; i < numFiles; i++)
		{
			// ALLOCATE MEMORY FOR FULL FILE PATH
			char* pathToFile = (char *)malloc(strlen(pathToDir) + strlen(fileList[i]) + 2);

			// CHECK IF MEMORY WAS ALLOCATED
			if (not(pathToFile))
			{
				errno = 1;
				fprintf(stderr, "%sERROR%s: Unable to retrive memory.\n", color1, color2);
				fprintf(stderr, "aliencrypt : MEMFAIL\n");
				return errno;
			}

			// COPY PATH TO DIRECTORY TO FULL FILE PATH VARIABLE
			strcpy(pathToFile, pathToDir);

			// IF THERE IS NO DIRECTORY SEPERATOR AT THE END OF
			// THE USER PROVIDED PATH, APPEND ONE
			if (pathToDir[strlen(pathToDir) - 1] != '/')
			{
				strcat(pathToFile, "/");
			}

			// APPEND THE FILENAME TO THE FULL FILE PATH VARIABLE
			strcat(pathToFile, fileList[i]);

			// READ KEY FROM FILE
			unsigned char key[KEY_SIZE];
			FILE *keyRead = fopen(keyPath, "rb");
			fread(key, 1, KEY_SIZE, keyRead);
			fclose(keyRead);

			// OPEN ENCRYPTED FILE
			FILE *readfile = fopen(pathToFile, "rb");

			// CHECK IF FILE CAN BE OPENED
			if (readfile == NULL)
			{
				printf("%s%s%s: %s\n", X_MARK_COL, X, color2, pathToFile);
				free(pathToFile);
				continue;
			}

			// READ NONCE FROM FILE
			unsigned char nonce[NONCE_SIZE];
			fseek(readfile, 0, SEEK_SET);
			fread(nonce, 1, NONCE_SIZE, readfile);

			// READ AUTHENTICATION TAG FROM FILE
			unsigned char tag[TAG_SIZE];
			fseek(readfile, NONCE_SIZE, SEEK_SET);
			fread(tag, 1, TAG_SIZE, readfile);

			// GET ENCRYPTED DATA SIZE
			fseek(readfile, 0, SEEK_END);
			long encrypted_size = ftell(readfile) - NONCE_SIZE - TAG_SIZE;
			fseek(readfile, NONCE_SIZE + TAG_SIZE, SEEK_SET);

			// ALLOCATE MEMORY FOR ENCRYPTED FILE DATA
			unsigned char *encrypted_data = (unsigned char *)malloc(encrypted_size);

			// CHECK IF MEMORY WAS ALLOCATED
			if (not(encrypted_data))
			{
				errno = 1;
				fprintf(stderr, "%sERROR%s: Unable to retrive memory.\n", color1, color2);
				fprintf(stderr, "aliencrypt : MEMFAIL\n");
				return errno;
			}

			// READ ENCRYPTED DATA FROM ENCRYPTED FILE AND CLOSE THE FILE
			fread(encrypted_data, 1, encrypted_size, readfile);
			fclose(readfile);

			// ALLOCATE MEMORY FOR DECRYPTED DATA
			unsigned char *decrypted_data = (unsigned char *)malloc(encrypted_size);

			// CHECK IF MEMORY WAS ALLOCATED
			if (not(decrypted_data))
			{
				errno = 1;
				fprintf(stderr, "%sERROR%s: Unable to retrive memory.\n", color1, color2);
				fprintf(stderr, "aliencrypt : MEMFAIL\n");
				return errno;
			}

			// DECRYPT THE DATA
			if (crypto_secretbox_open_detached(decrypted_data, encrypted_data, tag, encrypted_size, nonce, key) != 0)
			{
				free(decrypted_data);
				free(encrypted_data);
				errno = 1;
				fprintf(stderr, "%sERROR%s: Unable to encrypt file %s.\n", color1, color2, pathToFile);
				fprintf(stderr, "aliencrypt : ENCRYPT_ERR\n");
				return errno;
			}

			// WRITE OPEN FILE TO WRITE
			FILE *writefile = fopen(pathToFile, "wb");

			// CHECK IF FILE CAN BE WRITTEN TO
			if (writefile == NULL)
			{
				printf("%s%s%s: %s\n", X_MARK_COL, X, color2, pathToFile);
				free(decrypted_data);
				free(encrypted_data);
				free(pathToFile);
				continue;
			}

			// WRITE DECRYPTED DATA BACK TO FILE
			fwrite(decrypted_data, 1, encrypted_size - TAG_SIZE, writefile);
			fclose(writefile);

			// PRINT SUCCESS STATUS TO STDOUT
			printf("%s%s%s: %s\n", CHECK_MARK_COL, CHECK, color2, pathToFile);

			// FREE MEMORY BACK TO SYSTEM
			free(encrypted_data);
			free(decrypted_data);
			free(pathToFile);

		} // END OF NUM FILE LOOP

		// INCREMENT NUM FUNCTION CALLS BECAUSE FUNCTION IS DONE
		numFunctionCalls++;

	} // END OF IF STATEMENT GUARD

	return 0;

} // END OF DECRYPT FILES FUNCTION

 // END OF PROGRAM
