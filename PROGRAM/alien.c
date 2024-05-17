/*
* MIT License
* 
* Copyright (c) 2024 Bombenheimer
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
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
#include <sodium.h> // FUNCTIONS AND MACROS: crypto_secretbox_KEYBYTES, crypto_secretbox_NONCEBYTES, crypto_secretbox_MACBYTES, sodium_init(), randombytes_buf(), crypto_secretbox_detached(), crypto_secretbox_open_detached()
#include <libexif/exif-data.h> // FUNCTIONS AND MACROS: exif_data_new_from_file(), exif_data_unref(), ExifData

// HEADER GUARDS TO DETECT OPERATING SYSTEM
#ifndef _WIN32

// UNIX SPECIFIC LIBRARIES
#include <string.h> // FUNCTIONS: strcmp(), strstr(), strlen(), strrchr(), strcpy(), strcat(), strdup()
#include <unistd.h> // FUNCTIONS: geteuid(), unlink()
#include <dirent.h> // FUNCTIONS, MACROS, AND STRUCTS: DIR, opendir() readdir(), closedir(), struct dirent
#include <iso646.h> // MACROS: and, or, not
#include <getopt.h> // FUNCTIONS AND MACROS: getopt_long(), opt, optind

#endif // END OF HEADER GUARD

// TRUN COLOR OFF
#define _COLOR_OFF "\033[38;5;231m" // WHITE

// DEFAULT COLORS
#define _DEFAULT_COLOR_1 "\033[38;5;46m" // GREEN
#define _DEFAULT_COLOR_2 "\033[38;5;231m" // WHITE
#define _DEFAULT_COLOR_3 "\033[38;5;231m" // WHITE

// HOLIDAY SEASON COLORS
#define _HOLIDAY_COLOR_1 "\033[38;5;160m" // RED
#define _HOLIDAY_COLOR_2 "\033[38;5;46m" // GREEN
#define _HOLIDAY_COLOR_3 "\033[38;5;231m" // WHITE

// CYBERPUNK COLORS
#define _CYBER_COLOR_1 "\033[38;5;87m" // CYAN
#define _CYBER_COLOR_2 "\033[38;5;184m" // YELLOW
#define _CYBER_COLOR_3 "\033[38;5;93m" // PURPLE

// FROZEN DARK COLORS
#define _FROZEND_COLOR_1 "\033[38;5;111m" // ICE BLUE 
#define _FROZEND_COLOR_2 "\033[38;5;102m" // LIGHT SLATE GREY
#define _FROZEND_COLOR_3 "\033[38;5;67m" // STEEL BLUE

// PROTANOPIA COLORS
#define _PROTAN_COLOR_1 "\033[38;5;71m" // GREEN
#define _PROTAN_COLOR_2 "\033[38;5;255m" // WHITE
#define _PROTAN_COLOR_3 "\033[38;5;255m" // WHITE

// DEUTERANOPIA COLORS
#define _DEUTER_COLOR_1 "\033[38;5;70m" // GREEN
#define _DEUTER_COLOR_2 "\033[38;5;255m" // WHITE
#define _DEUTER_COLOR_3 "\033[38;5;255m" // WHITE

// TRITANOPIA COLORS
#define _TRITAN_COLOR_1 "\033[38;5;82m" // GREEN
#define _TRITAN_COLOR_2 "\033[38;5;255m" // WHITE
#define _TRITAN_COLOR_3 "\033[38;5;255m" // WHITE

// GREYSCALE COLORS
#define _GREYSC_COLOR_1 "\033[38;5;249m" // GREEN
#define _GREYSC_COLOR_2 "\033[38;5;231m" // WHITE
#define _GREYSC_COLOR_3 "\033[38;5;231m" // WHITE

// MAX PATH LENGTH
#define _MAX_PATH_LEN 1024

// KEY NAME LENGTH
#define _KEY_NAME_LEN 13

// KEY SIZE, NONCE SIZE, AND TAG SIZE
#define _KEY_SIZE crypto_secretbox_KEYBYTES
#define _NONCE_SIZE crypto_secretbox_NONCEBYTES
#define _TAG_SIZE crypto_secretbox_MACBYTES

// SHRED FILES BUFFER SIZE AND NUMBER OF PASSES
#define _BUFFER_SIZE 4096
#define _NUM_PASSES 5

// DEFINE NUMBER OF CURRENT SUPPORTED FILE EXTENTIONS FOR EACH FILE TYPE
#define _ARCHIVE_NUM 38
#define _AUDIO_NUM 17
#define _CAD_NUM 2
#define _DOC_NUM 21
#define _EBOOK_NUM 21
#define _FONT_NUM 5
#define _IMAGE_NUM 39
#define _PRESENT_NUM 10
#define _SSHEET_NUM 7
#define _VECTOR_NUM 10
#define _VIDEO_NUM 27
#define _SCRIPT_NUM 19
#define _BINARY_NUM 10
#define _CONFIG_NUM 6
#define _TEMP_NUM 2
#define _META_NUM 3
#define _BACKUP_NUM 4
#define _DB_NUM 3
#define _LOG_NUM 1

// VERSION NUMBER
#define _VER_NUM "3.1.3"

// FUNCTION PROTOTYPES FOR OPERATIONS
int PrintLogo(bool showLogo, char* color1, char* color2);
void PrintUsage(unsigned short int errorNum);
void PrintVersion(bool showVersion, char* versionNum);
char* KeyNameGen(bool encryptFiles, char* color1, char* color2);

// FUNCTION PROTOTYPES FOR OPTIONS
void RemoveExif(bool removeExif, bool makeVerbose, char** fileList, char* pathToDir, unsigned short int numFiles, char* color2);
int EncryptFiles(bool encryptFiles, bool makeVerbose, unsigned short int numFiles, char** fileList, char* pathToDir, char* keyName, char* color1, char* color2);
void ShowFiles(bool showFiles, char** fileList, char* pathToDir, unsigned short int numFiles, char* color1, char* color2, char* color3);
void ShowFileTypes(bool showFileTypes, char** fileList, unsigned short int numFiles, char* color1, char* color2, char* color3);
int ShredFiles(bool shredFiles, bool makeVerbose, char** fileList, unsigned short int numFiles, char* pathToDir, char* color1, char* color2);
int DecryptFiles(bool decryptFiles, bool makeVerbose, unsigned short int numFiles, char** fileList, char* pathToDir, char* keyPath, char* color1, char* color2);

// DEFINED TYPE FOR RESTRICTED DIRECTORIES
typedef const char* BadDir;

// STRUCTURE FOR NUMBER OF EACH FILE TYPE
struct NumFileTypes
{
	unsigned short int archive;
	unsigned short int audio;
	unsigned short int cad;
	unsigned short int document;
	unsigned short int ebook;
	unsigned short int font;
	unsigned short int image;
	unsigned short int presentation;
	unsigned short int spreadsheet;
	unsigned short int vector;
	unsigned short int video;
	unsigned short int script;
	unsigned short int binary;
	unsigned short int configuration;
	unsigned short int temporary;
	unsigned short int metadata;
	unsigned short int backup;
	unsigned short int database;
	unsigned short int log;
};

// GLOBAL VARIABLE FOR ALL FUNCTIONS TO USE
unsigned int numFunctionCalls = 0;

/*
 * FUNCTION NAME: main()
 * 
 * OPTIONAL INPUT PARAMETERS:
 * 	argc: INTEGER TYPE VARIABLE
 * 	argv: STRING ARRAY TYPE VARIABLE
 *
 * DESCRIPTION:
 * 	MAIN FUNCTION WHERE PROGRAM EXECUTION WILL OCCUR
 * 
 * PROGRAM EXECUTION STEPS:
 * 	1 - 
 *
 * 	2 - 
 *
 * 	3 - 
 *
 * RETURN VALUE:
 *  0 / EXIT_SUCCESS - SUCCESSFUL PROGRAM EXECUTION
 *  1 / EXIT_FAILURE - UNSUCCESSFUL PROGRAM EXECUTION; OPERAION NOT PERMITTED
 *  2 - FILE OR DIRECTORY NOT FOUND
 */
int main(int argc, char *argv[])
{
  // CLOCK TIME VARIABLES
	clock_t CLOCK_START, CLOCK_END;
	double CLOCK_TIME;

	// START CLOCK TO TIME PROGRAM
	CLOCK_START = clock();

	// CHECK OPERATING SYSTEM. IF ITS NOT MACOS OR LINUX, RAISE AN ERROR
	#if !(defined(__linux__)) && !(defined(__APPLE__) && defined(__MACH__)) && !(defined(_WIN32))
		fprintf(stderr, "%sERROR%s: unknown Operating System.\n", color1, color2);
		fprintf(stderr, "aliencrypt : os not supported\n";
		return EXIT_FAILURE;
  #elif defined(_WIN32)
    fprintf(stderr, "%sERROR%s: windows is not supported in this program.\n", color1, color2);
    fprintf(stderr, "aliencrypt : os not supported");
    return EXIT_FAILURE;
	#endif

  // VARIABLES FOR WORKING WITH FILES
	// SUBJECT TO CHANGE BASED ON USER PREFERENCES
	char* keyName = NULL;
	char* keyPath = NULL;
	char* pathToDir = ".";
  char* filePattern = NULL;
	char fullPath[_MAX_PATH_LEN];
	char** fileList = NULL;
	unsigned int numFiles = 0;
	DIR *directory;
	struct dirent *entry;
	struct stat statbuf;

  // VARIABLES FOR COLORS
	// SUBJECT TO CHANGE BASED ON USER PREFERENCES
  unsigned short int colnum = 0;
	char* color1 = _DEFAULT_COLOR_1;
	char* color2 = _DEFAULT_COLOR_2;
	char* color3 = _DEFAULT_COLOR_3;

	// VARIABLES FOR USER OPTIONS
	// SUBJECT TO CHANGE BASED ON USER PREFERENCES
	bool showLogo = false;
	bool encryptFiles = false;
	bool decryptFiles = false;
	bool showFiles = false;
	bool showFileTypes = false;
	bool removeExif = false;
	bool shredFiles = false;
	bool showVersion = false;
  bool makeVerbose = false;

	// VERSION NUMBER
	char* versionNum = _VER_NUM;

// CHECK IF USER IS RUNNING THE PROGRAM AS ROOT. IF NOT, RAISE AN ERROR
	if (geteuid() != 0)
  {
		fprintf(stderr, "%sWARNING%s: aliencrypt MUST be run as root!\n", color1, color2);
    PrintUsage(EXIT_FAILURE);
		return EXIT_FAILURE;
  }
  else
  {
    // INITIALIZE LIBSODIUM
		if (sodium_init() == -1)
		{
			fprintf(stderr, "%sERROR%s: initialzation of Libsodium Failed.\n", color1, color2);
			return EXIT_FAILURE;
		}

    // RESET ERROR NUMBER TO 0
		errno = 0;

    // STRUCTURE TO HOLD LONG ARGUMENTS
    static struct option long_options[15] =
		{
			{"help", no_argument, 0, 'h'},
			{"encrypt", no_argument, NULL, 'E'},
			{"decrypt", no_argument, NULL, 'D'},
			{"remove-exif", no_argument, NULL, 'R'},
			{"shred", no_argument, NULL, 'S'},
      {"key", required_argument, NULL, 'k'},
      {"pattern", required_argument, NULL, 'p'},
      {"color", required_argument, NULL, 'c'},
      {"verbose", no_argument, NULL, 'v'},
      {"dirpath", required_argument, NULL, 'd'},
			{"show-files", no_argument, NULL, 0},
			{"show-file-types", no_argument, NULL, 0},
      {"logo", no_argument, NULL, 0},
      {"version", no_argument, NULL, 0},
			{NULL, 0, NULL, 0}
		};
    
    // CHECK THE COMMAND LINE ARGUMENTS AND CHANGE THE VARIABLES ACCRODINGLY. IF NONE ARE GIVEN, DEFAULT VALUES WILL BE USED
		int opt, option_index = 0;
		while ((opt = getopt_long(argc, argv, "k:c:d:p:EDRSvh", long_options, &option_index)) != -1)
    {
      // PARSE LONG OPTIONS THAT REQUIRE AN ARGUMENT AND DON'T HAVE A SHORT FORM EQUIVILENT
			if ((opt == 0) and (optarg == NULL))
      {
        if (strcmp(long_options[option_index].name, "show-files") == 0)
        {
          showFiles = true;
        }
        else if (strcmp(long_options[option_index].name, "show-file-types") == 0)
        {
          showFileTypes = true;
        }
        else if (strcmp(long_options[option_index].name, "logo") == 0)
        {
          showLogo = true;
        }
        else if (strcmp(long_options[option_index].name, "version") == 0)
        {
          showVersion = true;
        }
      }
      else
      {
        // CONVERT OPT TO AN ASCII CHARACTER
        char charopt = (char)opt;

        // PARSE SHORT OPTIONS. LONG OPTIONS THAT HAVE CORRESPONDING SHORT OPTIONS WILL RETURN THE SAME RESULT
        switch (charopt)
        {
          case 'E':
            encryptFiles = true; // ENCRYPT FILES
            break;
          case 'D':
            decryptFiles = true; // DECRYPT FILES
            break;
          case 'R':
            removeExif = true; // REMOVE EXIF METADATA
            break;
          case 'S':
            shredFiles = true; // SHRED FILES
            break;
          case 'h':
            PrintUsage(EXIT_SUCCESS); // SHOW HELP MESSAGE
            return EXIT_SUCCESS;
            break;
          case 'v':
            makeVerbose = true; // SHOW ALL OUTPUT
            break;
          case 'd':
            pathToDir = optarg;
            break;
          case 'p':
            filePattern = optarg;
            break;
          case 'c':
            colnum = atoi(optarg);
            break;
          case 'k':
            keyPath = optarg;
            break;
          case '?':
          default:
            PrintUsage(EXIT_FAILURE);
            return EXIT_FAILURE;
        } // END OF SWITCH STATEMENT
      } // END OF ARGUMENT CHECKING
    } // END OF ARGUMENT PARSING
    
    // CHECK IF THERE ARE ANY ARGUMENTS IN ARGV THAT ARE NOT ARGUMENTS OR OPTIONS. IF SO, RAISE AN ERROR
    if (optind < argc)
    {
      fprintf(stderr, "%sERROR%s : an option that is not an argument has been found.\n", color1, color2);
      PrintUsage(EXIT_FAILURE);
      return EXIT_FAILURE;
    }

    // CHECK IF THE USER PROVIDED NO ARGUMENTS AT ALL, OR TOO MANY. IF SO, RAISE AN ERROR
    if (argc == 1)
    {
      fprintf(stderr, "%sERROR%s : no arguments provided.\n", color1, color2);
      PrintUsage(EXIT_FAILURE);
      return EXIT_FAILURE;
    }

    // CHANGE COLORS BASED ON USER PREFERENCES
    if (colnum)
    {
      switch(colnum)
      {
        case 1:
					color1 = _HOLIDAY_COLOR_1;
					color2 = _HOLIDAY_COLOR_2;
					color3 = _HOLIDAY_COLOR_3;
					break;
				case 2:
					color1 = _CYBER_COLOR_1;
					color2 = _CYBER_COLOR_2;
					color3 = _CYBER_COLOR_3;
					break;
				case 3:
					color1 = _FROZEND_COLOR_1;
					color2 = _FROZEND_COLOR_2;
					color3 = _FROZEND_COLOR_3;
					break;
				case 4:
					color1 = _PROTAN_COLOR_1;
					color2 = _PROTAN_COLOR_2;
					color3 = _PROTAN_COLOR_3;
					break;
				case 5:
					color1 = _DEUTER_COLOR_1;
					color2 = _DEUTER_COLOR_2;
					color3 = _DEUTER_COLOR_3;
					break;
				case 6:
					color1 = _TRITAN_COLOR_1;
					color2 = _TRITAN_COLOR_2;
					color3 = _TRITAN_COLOR_3;
					break;
				case 7:
					color1 = _GREYSC_COLOR_1;
					color2 = _GREYSC_COLOR_2;
					color3 = _GREYSC_COLOR_3;
					break;
				default:
					fprintf(stderr, "%sERROR%s: color %hu does not exist.\n", color1, color2, colnum);
					PrintUsage(EXIT_FAILURE);
					return EXIT_FAILURE;
					break;
      } // END OF SWITCH STATEMENT
    } // END OF COLOR FINDING

    // OPEN DIRETCORY. IF IT IS NULL, RAISE AN ERROR
    if ((directory = opendir(pathToDir)) == NULL)
    {
      fprintf(stderr, "%sERROR%s: directory or file does not exist or cannot be accessed.\n", color1, color2);
      fprintf(stderr, "aliencrypt : no such file or directory\n");
      PrintUsage(2);
      return 2;
    }
    else
    {
      // READ DIRECTORY CONTENTS
      while ((entry = readdir(directory)) != NULL)
      {
        // GET DIRECTORY ENTRIES
        char* filename = strdup(entry->d_name);
        snprintf(fullPath, sizeof(fullPath), "%s/%s", pathToDir, filename);

        // SKIP THE ENTRY IF RETRIVING INFORMATION ABOUT THE FILE FAILED
        if (stat(fullPath, &statbuf) == -1){continue;}

        // IF THE USER PROVIDED A FILE PATTERN,
        // SKIP THE ENTRY IF IT IS NOT A FILE OR DOES NOT MATCH THE SEARCH PATTERN.
        // OTHERWISE, ADD ALL FILES TO FILE LIST
        if (filePattern != NULL)
        {
          if ((not( S_ISREG(statbuf.st_mode))) or (strstr(filename, filePattern) == NULL))
          {
            free(filename);
            continue;
          }
        }
        else
        {
          if (not( S_ISREG(statbuf.st_mode)))
          {
            free(filename);
            continue;
          }
        }

        // ALLOCATE MEMORY FOR FILE ENTRY
        fileList = (char **)realloc(fileList, (numFiles + 1) * sizeof(char *));

        // CHECK IF MEMORY WAS ALLOCATED
				if (not(fileList))
				{
					fprintf(stderr, "%sERROR%s: unable to retrive memory.\n", color1, color2);
					fprintf(stderr, "aliencrypt : MEMFAIL\n");
					return EXIT_FAILURE;
        }

        // INSERT FILENAME TO THE LIST
				fileList[numFiles++] = filename;
      }
    }
    // CLOSE DIRECTORY
    closedir(directory);

    // CHECK IF THE PROVIDED KEY FILE EXISTS. IF NOT, RAISE AN ERROR
    if (keyPath != NULL)
    {
      FILE *filecheck = fopen(keyPath, "rb");

      if (filecheck == NULL)
      {
        fprintf(stderr, "%sERROR%s: key file does not exist.\n", color1, color2);
        fprintf(stderr, "aliencrypt : no such file or directory\n");
        PrintUsage(2);
        return 2;
      }
      else
      {
        fclose(filecheck);
      }
    }

    // CHECK IF THE USER GAVE THE DECRYPT OPTION, BUT DID NOT HAVE THE KEY OPTION. IF SO, RAISE AN ERROR
    if ((decryptFiles) and (keyPath == NULL))
    {
      fprintf(stderr, "%sERROR%s: No key option provided.\n", color1, color2);
      PrintUsage(EXIT_FAILURE);
      return EXIT_FAILURE;
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
		if (showLogo == true)
		{
			encryptFiles = false;
			decryptFiles = false;
			showFiles = false;
			showFileTypes = false;
			removeExif = false;
			shredFiles = false;
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
    PrintLogo(showLogo, color1, color2);

    // EXECUTE FUNCTIONS BASED ON OPERATING SYSTEM
// CHECK OPERATING SYSTEM FOR BAD DIRS. IF THERE IS ONE, WARN THE USER
		#if defined(__linux__)
			
			// FUNCTIONS THAT DON'T NEED TO BE CHECKED FOR BAD DIRS CAN
			// BE EXECUTED BASED ON BOOLEAN VALUES
			ShowFiles(showFiles, fileList, pathToDir, numFiles, color1, color2, color3);
			ShowFileTypes(showFileTypes, fileList, numFiles, color1, color2, color3);

			// ITERATOR FOR WHILE LOOP
			unsigned int i = 0;

			// LIST OF BAD DIRECTORIES
			BadDir LinuxDirs[11] = {"/etc", "/bin", "/lib", "/boot", "/root", "/var", "/sys", "/proc", "/sbin",
			                        "/usr/bin", "/usr/sbin"};

			// CHECK THE USER PROVIDED PATH TO SEE IF IT MATCHES THE ONE OF THE BAD DIRECTORES. IF SO, RAISE AN ERROR
			while (i < 11)
			{
				// RAISE AN ERROR IF THE USER DID NOT CHOOSE TO SHOW FILES OR FILE TYPES AND IF THERE IS A SENSITIVE
				// DIRECTORY IN THE PATH ARGUMENT
				if ((strstr(pathToDir, LinuxDirs[i]) != NULL) and ((showFiles == false) and showFileTypes == false))
				{
					fprintf(stderr, "%sWARNING%s: The directory you have entered is a sensitive directory.\n", color1, color2);
					fprintf(stderr, "aliencrypt : %s : %s\n", LinuxDirs[i], strerror(errno));
					return EXIT_FAILURE;
				}
				
				// INCREMENT
				i++;
			}

			// EXECUTE OPTIONS BASED ON BOOLEAN VALUES
			RemoveExif(removeExif, makeVerbose, fileList, pathToDir, numFiles, color2);
			keyName = KeyNameGen(encryptFiles, color1, color2);
			EncryptFiles(encryptFiles, makeVerbose, numFiles, fileList, pathToDir, keyName, color1, color2);
			ShredFiles(shredFiles, makeVerbose, fileList, numFiles, pathToDir, color1, color2);
			DecryptFiles(decryptFiles, makeVerbose, numFiles, fileList, pathToDir, keyPath, color1, color2);

		#elif defined(__APPLE__) and defined(__MACH__)

			// FUNCTIONS THAT DON'T NEED TO BE CHECKED FOR BAD DIRS CAN
			// BE EXECUTED BASED ON BOOLEAN VALUES
			ShowFiles(showFiles, fileList, pathToDir, numFiles, color1, color2, color3);
			ShowFileTypes(showFileTypes, fileList, numFiles, color1, color2, color3);

			// ITERATOR FOR WHILE LOOP
			unsigned int i = 0;

			// LIST OF BAD DIRECTORIES
			BadDir MacDirs[8] = {"/System", "/usr", "/bin", "/Library", "/Applications", "/private", "/var", "/sbin"};

			// CHECK THE USER PROVIDED PATH TO SEE IF IT MATCHES THE ONE OF THE BAD DIRECTORES. IF SO, RAISE AN ERROR
			while (i < 8)
			{
				// RAISE AN ERROR IF THE USER DID NOT CHOOSE TO SHOW FILES OR FILE TYPES AND IF THERE IS A SENSITIVE
				// DIRECTORY IN THE PATH ARGUMENT
				if ((strstr(pathToDir, MacDirs[i]) != NULL) and ((showFiles == false) and showFileTypes == false))
				{
					fprintf(stderr, "%sWARNING%s: The directory you have entered is a sensitive directory.\n", color1, color2);
					fprintf(stderr, "aliencrypt : %s : %s\n", MacDirs[i], strerror(errno));
					return EXIT_FAILURE;
				}

				// INCREMENT
				i++;
			}

			// EXECUTE OPTIONS BASED ON BOOLEAN VALUES
			RemoveExif(removeExif, makeVerbose, fileList, pathToDir, numFiles, color2);
			keyName = KeyNameGen(encryptFiles, color1, color2);
			EncryptFiles(encryptFiles, makeVerbose, numFiles, fileList, pathToDir, keyName, color1, color2);
			ShredFiles(shredFiles, makeVerbose, fileList, numFiles, pathToDir, color1, color2);
			DecryptFiles(decryptFiles, makeVerbose, numFiles, fileList, pathToDir, keyPath, color1, color2);

		#endif // END OF OS CHECK AND FUNCTION EXECUTION
  } // END OF ROOT USER CHECK

  // INCREMENT FUNCTION CALL VARIABLE BECAUSE FUNCTION IS DONE
  numFunctionCalls++;

  // EVALUATE CLOCK TIME
  CLOCK_END = clock();
	CLOCK_TIME = ((double) (CLOCK_END - CLOCK_START)) / CLOCKS_PER_SEC;
  
  // PRINT USAGE STATISTICS TO STDOUT
  if (makeVerbose)
  {
    if (numFunctionCalls > 1)
    {
      fprintf(stdout, "\n\n%s[%u function calls executed in %lf seconds.]\n", _COLOR_OFF, numFunctionCalls, CLOCK_TIME);
    }
    else
    {
      fprintf(stdout, "\n\n%s[%u function call executed in %lf seconds.]\n", _COLOR_OFF, numFunctionCalls, CLOCK_TIME);
    }
  }
  return EXIT_SUCCESS;
} // END OF MAIN 

/*
 * FUNCTION NAME: PrintVersion()
 * 
 * OPTIONAL INPUT PARAMETERS:
 * 	showVersion: BOOLEAN TYPE VARIABLE
 * 	versionNum: DEFINED CONSTANT STRING
 *
 * DESCRIPTION:
 *  SHOW THE PROGRAM VERSION NUMBER TO STDOUT
 * 
 * PROGRAM EXECUTION STEPS:
 * 	1 - USE THE IF STATEMENT GUARD TO EVALUATE IF
 * 	    SHOW VERSION IS TRUE OR FALSE. IF IT IS TRUE,
 * 	    THE PROGRAM WILL CONTINUE AND END IF NOT
 *
 * 	2 - PRINT THE VERSION NUMBER TO STDOUT
 *
 * 	3 - INCREMENT NUM FUNCTION CALLS TO INDICATE THAT
 * 	    THE FUNCTION HAS BEEN COMPLETED
 *
 * 	4 - END FUNCTION
 *
 * RETURN VALUE: VOID
 */
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

/*
 * FUNCTION NAME: PrintUsage()
 * 
 * OPTIONAL INPUT PARAMETERS:
 * 	errorNum: UNSIGNED SHORT INT TYPE VARIABLE
 *
 * DESCRIPTION:
 *  SHOW HELP MESSAGE BASED ON INTEGER RETURN VALUE
 * 
 * PROGRAM EXECUTION STEPS:
 * 	1 - INITIALIZE LONG AND SHORT HELP MESSAGES AS CONSTANT STRINGS
 *
 * 	2 - EVALUATE IF THE RETURN VALUE errorNum IS A 0 OR A NON - ZERO
 * 	    INTEGER. IF NOT 0, SHOW THE SHORT HELP MESSAGE AS THIS INDICATES
 * 	    PROGRAM FAILURE. IF NOT, SHOW THE LONG HELP MESSAGE AS THIS
 * 	    INDICATES THAT THE USER PURPOSEFULY CHOSE TO SHOW A
 * 	    HELP MESSAGE
 *
 * 	3 - INCREMENT NUM FUNCTION CALLS TO INDICATE THAT 
 * 	    THE FUNCTION HAS BEEN COMPLETED
 *
 * 	4 - END FUNCTION
 *
 * RETURN VALUE: VOID
 */
void PrintUsage(unsigned short int errorNum)
{
  // LONG HELP MESSAGE
  const char* longMsg = "aliencrypt v3.1.3\n"
                        "Optional arguments:\n"
                        "\t-E, --encrypt\t\t\t Encrypt a file or all files in a directory.\n"
                        "\t-D, --decrypt\t\t\t Decrypt a file or all files in a directory.\n"
                        "\t-R, --remove-exif\t\t Remove EXIF metadata from a file or all files in a directory (JPEG files only).\n"
                        "\t-S, --shred\t\t\t Overwrite and delete a file or all files in a directory.\n"
                        "\t-h, --help\t\t\t Show this help message.\n"
                        "\t-p, --pattern FILE_PATTERN\t Operate on files that match a pattern.\n"
                        "\t-c, --color 1234567\t\t Show program output in a different color scheme.\n"
                        "\t-k, --key KEY_PATH\t\t Provide a generated decryption key.\n"
                        "\t-v, --verbose\t\t\t Show all program output.\n"
                        "\t-d, --dirpath DIR_PATH\t\t Provide a path to a directory or file.\n"
                        "\t--show-files\t\t\t Show files and file info about a file or all files in a directory.\n"
                        "\t--show-file-types\t\t Show the type of a file or all files in a directory.\n"
                        "\t--logo\t\t\t\t Show program logo.\n"
                        "\t--version\t\t\t Show program version.\n";

  // SHORT HELP MESSAGE
  const char* shortMsg = "usage: sudo alien [-EDRSpvh] [-d DIR_PATH] [-c 1234567] [-k KEY_PATH]\n"
                         "                  [--encrypt] [--decrypt] [--remove-exif] [--shred]\n"
                         "                  [--help] [--color 1234567] [--key KEY_PATH]\n"
                         "                  [--dirpath DIR_PATH] [--verbose] [--show-files]\n"
                         "                  [--show-file-types] [--logo] [--version]\n"
                         "                  [--pattern FILE_PATTERN]\n";

  if (errorNum)
  {
    fprintf(stdout, "%s", shortMsg);
  }
  else
  {
    fprintf(stderr, "%s", longMsg);
  }

  // INCREMENT NUM FUNCTION CALLS BECAUSE FUNCTION IS DONE
  numFunctionCalls++;

} // END OF PRINT USAGE FUNCTION

/*
 * FUNCTION NAME: PrintLogo()
 * 
 * OPTIONAL INPUT PARAMETERS:
 * 	showLogo: BOOLEAN TYPE VARIABLE
 * 	color1: DEFINED CONSTANT STRING
 * 	color2: DEFINED CONSTANT STRING
 *
 * DESCRIPTION:
 * 	PRINTS A USAGE MESSAGE TO STDOUT
 * 
 * PROGRAM EXECUTION STEPS:
 * 	1 - USE THE IF STATEMENT GUARD TO EVALUATE OF THE SHOW LOGO
 * 	    FUNCTION IS SET TO TRUE OT FALSE. IF IT IS TRUE, THE PROGRAM
 * 	    WILL CONTINUE AND END IF NOT
 *
 * 	2 - INITIALZE EACH LINE IN THE LOGO
 *
 * 	3 - GET THE LENGTH OF THE ENTIRE LOGO WITH sprintf() AND THEN
 * 	    STORE IT IN A VARIABLE
 *
 *  4 - ALLOCATE MEMORY FOR THE PROGRAM LOGO TO STORE EVERYTHING
 *      AS WELL AS THE COLOR STRINGS
 *
 *  5 - CHECK IF MEMORY HAS BEEN ALLOCATED
 *
 *  6 - FORMAT THE LOGO TO BE STORED IN THE PROGRAM LOGO
 *
 *  7 - CLEAR TERMINAL SCREEN
 *
 *  8 - PRINT THE PROGRAM LOGO TO STDOUT
 *
 *  9 - FREE MEMORY ALLOCATED TO PROGRAM LOGO BACK TO SYSTEM
 *
 *  10 - INCREMENT NUM FUNCTION CALLS TO INDICATE THAT THE FUNCTION
 *       HAS BEEN COMPLETED
 *
 *  11 - END FUNCTION
 *
 * RETURN VALUE:
 *  EXIT_SUCCESS - SUCCESSFUL PROGRAM EXECUTION
 *  EXIT_FAILURE - UNSUCCESSFUL PROGRAM EXECUTION; OPERAION NOT PERMITTED
 */
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
		char* L10 = "                                 v3.1.3\n";

		// GET THE LENGTH OF THE PROGRAM LOGO
		int programLogoLen = snprintf(NULL, 0, "%s%s %s %s %s %s%s %s %s %s %s %s%s", color1, L1, L2, L3, L4, L5, color2, L6, L7, L8, L9, color1, L10);
		
		// ALLOCATE ENOUGTH MEMORY FOR THE SPACE OF THE LOGO
		char* programLogo = (char *)malloc(programLogoLen + 1);

		// CHECK IF MEMORY WAS ALLOCATED
		if (not(programLogo))
		{
			fprintf(stderr, "%sERROR%s: Unable to retrive memory.\n", color1, color2);
			fprintf(stderr, "aliencrypt : MEMFAIL\n");
			return EXIT_FAILURE;
		}

		// FORMAT THE LOGO AND COPY AS A STRING
		snprintf(programLogo, programLogoLen + 1, "%s%s %s %s %s %s%s %s %s %s %s %s%s", color1, L1, L2, L3, L4, L5, color2, L6, L7, L8, L9, color1, L10);

		// CLEAR SCREEN
		system("clear");

		// PRINT LOGO
		fprintf(stdout, "%s", programLogo);

		// FREE ALLOCATED MEMORY BACK TO SYSTEM
		free(programLogo);

		// INCREMENT NUM FUNCTION CALLS BECAUSE FUNCTION IS DONE
		numFunctionCalls++;

	} // END OF IF STATEMENT GUARD
	
	return EXIT_SUCCESS;

} // END OF PRINT LOGO FUNCTION

/*
 * FUNCTION NAME: ShowFiles()
 * 
 * OPTIONAL INPUT PARAMETERS:
 * 	showFiles: BOOLEAN TYPE VARIABLE
 * 	fileList: STRING ARRAY TYPE VARIABLE
 * 	pathToDir: CHAR ARRAY TYPE VARIABLE
 * 	numFiles: UNSIGNED INTEGER TYPE VARIABLE
 * 	color1: DEFINED CONSTANT STRING
 * 	color2: DEFINED CONSTANT STRING
 * 	color3: DEFINED CONSTANT STRING
 *
 * DESCRIPTION:
 *  SHOW FILES AND THEIR INFORMATION TO STDOUT
 * 
 * PROGRAM EXECUTION STEPS:
 * 	1 - USE THE IF STATEMENT GUARD TO EVALUATE IF
 * 	    SHOW FILES IS TRUE OR FALSE. IF IT IS TRUE,
 * 	    THE PROGRAM WILL CONTINUE AND END IF NOT
 *
 * 	2 - CLEAR TERMINAL SCREEN
 *
 * 	3 - INITIALIZE TITLE AND CATEGORIES
 *
 * 	4 - INITIALIZE STRUCTURE TO HOLD FILE INFORMATION
 *
 * 	5 - PRINT TITLE AND CATEGORIES
 *
 * 	6 - INITIALZE FOR LOOP TO LOOP THROUGH FILES
 *
 * 	7 - ALLOCATE MEMORY FOR PATH TO FILE VARIABLE
 *
 * 	8 - COPY DIR PATH TO THE PATH TO FILE VARIABLE
 *
 * 	9 - CHECK IF THERE IS A PATH SEPERATOR AT THE END
 * 	    OF THE FILE PATH AND APPEND ONE IF THERE IS NOT
 *
 * 	10 - APPEND THE FILENAME TO THE PATH TO FILE VARIABLE
 *
 * 	11 - EVALUATE IF METADATA OF A FILE COULD BE RETRIVED.
 * 	     IF NOT, FREE MEMORY PREVIOUSLY ALLOCATED TO THE
 * 	     FILENAME AND THE PATH TO FILE VARIABLE AND CONTINUE
 * 	     TO THE NEXT FILE.
 *
 * 	12 - INITIALIZE THE PERMISSIONS, FILE SIZE, AND SIZE UNIT
 * 	     VARIABLES FOR FILE INFORMATION PRINTING
 *
 * 	13 - GET THE FILE SIZE UNIT BY EVALUATING THE SIZE OF THE FILE
 * 	     IN BYTES, WHICH INCLUDE BiB, KiB, MiB, GiB, AND TiB.
 *
 * 	14 - PRINT THE FILE AND ITS INFORMATION TO STDOUT AND FORMAT THE LINE
 * 	     BASED ON THE LINE NUMBER TO PREVENT UNALIGNMENT WHEN PRINTING
 *
 * 	15 - FREE MEMORY PREVIOUSLY ALLOCATED TO THE
 * 	     FILENAME AND THE PATH TO FILE VARIABLE
 *
 * 	16 - REPEAT 7-15 FOR EACH FILE UNTIL ALL FILES HAVE BEEN LOOPED THROUGH
 *
 * 	17 - FREE MEMORY ALLOCATED TO FILE LIST BACK TO THE SYSTEM
 *
 * 	18 - INCREMENT NUM FUNCTION CALLS TO INDICATE THAT THE FUNCTION
 * 	     HAS BEEN COMPLETED
 *
 * 	19 - END FUNCTION
 *
 * RETURN VALUE: VOID
 */
void ShowFiles(bool showFiles, char** fileList, char* pathToDir, unsigned short int numFiles, char* color1, char* color2, char* color3)
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
		fprintf(stdout, "%s%s%s%s", color1, listLineHead1, listLineHead2, color2);

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

			// CHECK IF FILE METADATA CAN BE RETRIVED. IF NOT, CONTINUE
			if (stat(pathToFile, &file_stat) == 0)
			{
				// FILE METADATA
				mode_t permissions = file_stat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
				double size = file_stat.st_size;
				char size_unit[4];

				// GET FILE SIZE UNIT
				if (size >= 0 and size <= 1000)
				{
					strcpy(size_unit, "BiB");
				}
				if (size >= 1001 and size <= 1048575)
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
					fprintf(stdout, "%s%d%s...............%06.2lf %s...............%o...............%s\n\n", color3, i + 1, color2, size, size_unit, permissions, fileList[i]);
				}
				if (i + 1 >= 10)
				{
					fprintf(stdout, "%s%d%s..............%06.2lf %s...............%o...............%s\n\n", color3, i + 1, color2, size, size_unit, permissions, fileList[i]);
				}
				if (i + 1 >= 100)
				{
					fprintf(stdout, "%s%d%s.............%06.2lf %s...............%o...............%s\n\n", color3, i + 1, color2, size, size_unit, permissions, fileList[i]);
				}
				if (i + 1 >= 1000)
				{
					fprintf(stdout, "%s%d%s............%06.2lf %s...............%o...............%s\n\n", color3, i + 1, color2, size, size_unit, permissions, fileList[i]);
				}
			}
			else
			{
				free(pathToFile);
				free(fileList[i]);
				continue;
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

/*
 * FUNCTION NAME: ShowFileTypes()
 * 
 * OPTIONAL INPUT PARAMETERS:
 * 	showFileTypes: BOOLEAN TYPE VARIABLE
 * 	fileList: STRING ARRAY TYPE VARIABLE
 * 	numFiles: UNSIGNED SHORT INT TYPE VARIABLE
 * 	color1: DEFINED CONSTANT STRING
 * 	color2: DEFINED CONSTANT STRINGS
 * 	color3: DEFINED CONSTANT STRING
 * 
 * DESCRIPTION:
 *  SHOW NUMBER OF FILES OF EACH TYPE
 * 
 * PROGRAM EXECUTION STEPS:
 * 	1 - USE THE IF STATEMENT GUARD TO EVALUATE IF
 * 	    showFileTypes IS TRUE OR FALSE. IF IT IS TRUE,
 * 	    THE PROGRAM WILL CONTINUE AND END IF NOT
 *
 * 	2 - INITIALIZE CONSTANT STRING ARRAYS OF FILE EXTENTIONS
 * 	    FOR EACH FILE TYPE
 *
 * 	3 - INITIALIZE STRUCTURE TO HOLD THE NUMBER OF FILES FOR ECH TYPE
 * 	    AND INITIALIZE THEM ALL TO 0
 *
 * 	4 - INITIALIZE OUTTER LOOP TO LOOP THROUGH EACH FILE IN fileList
 *
 * 	5 - SEACH FOR THE FIRST OCCURENCE OF THE FILE SEPRARATOR "." AND STORE
 * 	    IT TO dotptr
 *
 * 	6 - EVALUATE IF dotptr is RETURNS NULL or NOT. IF SO, THE FILE IS MOST LIKLEY
 * 	    AN EXECUTABLE AND EXECUTABLE FILES MUST BE COUNTED AND FUNCTION. WILL CONTINUE
 * 	    TO NEXT FILE. IF NOT, THEN TRY EVERY OTHER POSSIBILITY TO MATCH EVERY FILE EXTENTION
 * 	    IN EACH FILE TYPE AND STOP AND CONTINUE THE LOOP TO THE NEXT FILE WHEN MATCHED AND
 * 	    FREE MEMORY ALLOCATED TO FILE LIST, AND CONTINUE TO THE NEXT FILE TYPE IF NOT MATCHED
 *
 * 	7 - REPEAT 5 - 6 FOR EACH FILE IN FILE LIST UNTIL THE LOOP IS FINISHED
 *
 * 	8 - FREE THE POINTER TO FILE LIST
 *
 * 	9 - PRINT THE NUMBER OF EACH FILE IN EACH FILE TYPE TO STDOUT
 *
 * 	10 - INCREMENT NUM FUNCTION CALLS TO INDICATE THAT THE FUNCTION
 * 	     HAS BEEN COMPLETED
 *
 * 	11 - END FUNCTION
 *
 * RETURN VALUE: VOID
 */
void ShowFileTypes(bool showFileTypes, char** fileList, unsigned short int numFiles, char* color1, char* color2, char* color3)
{
	// IF STATEMENT GUARD
	if (showFileTypes == true)
	{
		// ARCHIVE FILE EXTENTIONS
		const char* archiveTypes[_ARCHIVE_NUM] = {".7z", ".ace", ".alz", ".arc", ".arj", ".bz", ".bz2", ".cab", ".cpio", ".deb",
	                                            ".dmg", ".gz", ".img", ".iso", ".jar", ".lha", ".lz", ".lzma", ".lzo", ".rar",
	                                            ".rpm", ".rz", ".tar", ".tar.7z", ".tar.bz", ".tar.bz2", ".tar.gz", ".tar.lzo",
		                                          ".tar.xz", ".tar.z", ".tbz", ".tbz2", ".tgz", ".tz", ".tzo", ".xz", ".z", ".zip"};

		// AUDIO FILE EXTENTIONS
		const char* audioTypes[_AUDIO_NUM] = {".aac", ".ac3", ".aif", ".aifc", ".aiff", ".amr", ".au", ".caf", ".flac", ".m4a",
	                                        ".m4b", ".mp3", ".oga", ".voc", ".wav", ".weba", ".wma"};

		// CAD FILE EXTENTIONS
		const char* cadTypes[_CAD_NUM] = {".wdg", ".dxf"};

		const char* documentTypes[_DOC_NUM] = {".abw", ".djvu", ".doc", ".docm", ".docx", ".dot", ".dotx", ".html", ".hwp", ".lwp",
	                                         ".md", ".odt", ".pages", ".pdf", ".rst", ".rtf", ".tex", ".txt", ".wpd", ".wps", ".zabw"};

		// EBOOK FILE EXTENTIONS
		const char* ebookTypes[_EBOOK_NUM] = {".azw", ".azw3", ".azw4", ".cbc", ".cbr", ".cbz", ".chm", ".epub", ".fb2", ".htm",
	                                        ".htmlz", ".lit", ".lrf", ".mobi", ".pdb", ".pml", ".prc", ".rb", ".snb", ".tcr", ".txtz"};

		// FONT FILE EXTENTIONS
		const char* fontTypes[_FONT_NUM] = {".eot", ".otf", ".ttf", ".woff", ".woff2"};

		// IMAGE FILE EXTENTIONS
		const char* imageTypes[_IMAGE_NUM] = {".3fr", ".arw", ".avif", ".bmp", ".cr2", ".cr3", ".crw", ".dcr", ".dng", ".eps",
	                                        ".erf", ".gif", ".heic", ".heif", ".icns", ".ico", ".jfif", ".jpeg", ".jpg", ".mos",
	                                        ".mrw", ".nef", ".odd", ".odg", ".orf", ".pef", ".png", ".ppm", ".ps", ".psd",
	                                        ".raf", ".raw", ".rw2", ".tif", ".tiff", ".webp", ".x3f", ".xcf", ".xps"};

		// PRESENTATION FILE EXTENTIONS
		const char* presentationTypes[_PRESENT_NUM] = {".dps", ".key", ".odp", ".pot", ".potx", ".pps", ".ppsx", ".ppt", ".pptm", ".pptx"};

		// SPREADSHEET FILE EXTENTIONS
		const char* spreadsheetTypes[_SSHEET_NUM] = {".csv", ".et", ".ods", ".xls", ".xlsm", ".xlsx", ".numbers"};

		// VECTOR FILE EXTENTIONS
		const char* vectorTypes[_VECTOR_NUM] = {".ai", ".cdr", ".cgm", ".emf", ".sk", ".sk1", ".svg", ".svgz", ".vsd", ".wmf"};

		// VIDEO FILE EXTENTIONS
		const char* videoTypes[_VIDEO_NUM] = {".3g2", ".3gp", ".3gpp", ".avi", ".cavs", ".dv", ".dvr", ".flv", ".m2ts", ".m4v",
	                                        ".mkv", ".mod", ".mov", ".mp4", ".mpeg", ".mpg", ".mts", ".mxf", ".ogg", ".rm",
	                                        ".rmvb", ".swf", ".ts", ".vob", ".webm", ".wmv", ".wtv"};

		// SCRIPT OR PROGRAMMING LANGUAGE FILE EXTENTIONS
		const char* scriptTypes[_SCRIPT_NUM] = {".py", ".c", ".java", ".sh", ".cpp", ".lol", ".js", ".asm", ".cmd", ".bat",
	                                          ".php", ".lua", ".ps1", ".vbs", ".swift", ".sql", ".cs", ".h", ".hpp"};

		// BINARY FILE EXTENTIONS
		const char* binaryTypes[_BINARY_NUM] = {".exe", ".out", ".dll", ".bin", ".elf", ".app", ".apk", ".so", ".class", ".jar"};

		// CONFIGURATION FILE EXTENTIONS
		const char* configTypes[_CONFIG_NUM] = {".ini", ".cfg", ".conf", ".properties", ".yaml", ".yml"};

		// TEMPORARY FILE EXTENTIONS
		const char* tempTypes[_TEMP_NUM] = {".tmp", ".temp"};

		// METADATA FILE EXTENTIONS
		const char* metadataTypes[_META_NUM] = {".json", ".meta", ".xml"};

		// BACKUP FILE EXTENTIONS
		const char* backupTypes[_BACKUP_NUM] = {".old", ".bkp", ".backup", ".bak"};

		// DATABASE FILE EXTENTIONS
		const char* databaseTypes[_DB_NUM] = {".db", ".sqlite", ".mdb"};

		// LOG FILE EXTENTIONS
		const char* logTypes[_LOG_NUM] = {".log"};

		// NUMBER OF EACH FILE TYPE
		struct NumFileTypes NumFile = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

		// OUTER LOOP FOR NUMBER OF FILES
		for (unsigned short int i = 0; i < numFiles; i++)
		{
			// SEARCH FOR EXTENTION AND FILENAME SEPERATOR
			char* dotptr = strrchr(fileList[i], '.');

			// CHECK IF THE SEARCH RETURNED A NULL. IF SO, THEN IT MEANS ITS PROBABLY AN EXECUTABLE
			if (dotptr != NULL)
			{
				const char* fileExtention = strchr(fileList[i], '.');

				// INNER LOOP FOR FILE TYPE ARCHIVE
				for (unsigned short int j = 0; j < _ARCHIVE_NUM; j++)
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
				for (unsigned short int j = 0; j < _AUDIO_NUM; j++)
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
				for (unsigned short int j = 0; j < _CAD_NUM; j++)
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
				for (unsigned short int j = 0; j < _DOC_NUM; j++)
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
				for (unsigned short int j = 0; j < _EBOOK_NUM; j++)
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
				for (unsigned short int j = 0; j < _FONT_NUM; j++)
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
				for (unsigned short int j = 0; j < _IMAGE_NUM; j++)
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
				for (unsigned short int j = 0; j < _PRESENT_NUM; j++)
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
				for (unsigned short int j = 0; j < _SSHEET_NUM; j++)
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
				for (unsigned short int j = 0; j < _VECTOR_NUM; j++)
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
				for (unsigned short int j = 0; j < _VIDEO_NUM; j++)
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
				for (unsigned short int j = 0; j < _SCRIPT_NUM; j++)
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
				for (unsigned short int j = 0; j < _BINARY_NUM; j++)
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
				for (unsigned short int j = 0; j < _CONFIG_NUM; j++)
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
				for (unsigned short int j = 0; j < _TEMP_NUM; j++)
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
				for (unsigned short int j = 0; j < _META_NUM; j++)
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
				for (unsigned short int j = 0; j < _BACKUP_NUM; j++)
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
				for (unsigned short int j = 0; j < _DB_NUM; j++)
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
				for (unsigned short int j = 0; j < _LOG_NUM; j++)
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
		fprintf(stdout, "                                %sFILE TYPES\n\n", color1);
	  fprintf(stdout, "%sAll Files: %s%hu\033[38;5;231m\n\n", color2, color3, numFiles);
		fprintf(stdout, "%sArchive and Package Files: %s%d\033[38;5;231m\n\n", color2, color3, NumFile.archive);
		fprintf(stdout, "%sAudio Files: %s%hu\033[38;5;231m\n\n", color2, color3, NumFile.audio);
		fprintf(stdout, "%sCad Files: %s%hu\033[38;5;231m\n\n", color2, color3, NumFile.cad);
		fprintf(stdout, "%sDocument Files: %s%hu\033[38;5;231m\n\n", color2, color3, NumFile.document);
		fprintf(stdout, "%sEbook Files: %s%hu\033[38;5;231m\n\n", color2, color3, NumFile.ebook);
		fprintf(stdout, "%sFont Files: %s%hu\033[38;5;231m\n\n", color2, color3, NumFile.font);
		fprintf(stdout, "%sImage Files: %s%hu\033[38;5;231m\n\n", color2, color3, NumFile.image);
		fprintf(stdout, "%sPresentation Files: %s%hu\033[38;5;231m\n\n", color2, color3, NumFile.presentation);
		fprintf(stdout, "%sSpreadsheet Files: %s%hu\033[38;5;231m\n\n", color2, color3, NumFile.spreadsheet);
		fprintf(stdout, "%sVector Files: %s%hu\033[38;5;231m\n\n", color2, color3, NumFile.vector);
		fprintf(stdout, "%sVideo Files: %s%hu\033[38;5;231m\n\n", color2, color3, NumFile.video);
		fprintf(stdout, "%sScript Files: %s%hu\033[38;5;231m\n\n", color2, color3, NumFile.script);
		fprintf(stdout, "%sBinary and Executable Files: %s%hu\033[38;5;231m\n\n", color2, color3, NumFile.binary);
		fprintf(stdout, "%sConfiguration Files: %s%hu\033[38;5;231m\n\n", color2, color3, NumFile.configuration);
		fprintf(stdout, "%sTemporary Files: %s%hu\033[38;5;231m\n\n", color2, color3, NumFile.temporary);
		fprintf(stdout, "%sMetadata Files: %s%hu\033[38;5;231m\n\n", color2, color3, NumFile.metadata);
		fprintf(stdout, "%sBackup Files: %s%hu\033[38;5;231m\n\n", color2, color3, NumFile.backup);
		fprintf(stdout, "%sDatabase Files: %s%hu\033[38;5;231m\n\n", color2, color3, NumFile.database);
		fprintf(stdout, "%sLog Files: %s%hu\033[38;5;231m\n\n", color2, color3, NumFile.log);

		// INCREMENT NUM FUNCTION CALLS BECAUSE FUNCTION IS DONE
		numFunctionCalls++;

	} // END OF IF STATEMENT GUARD
} // END OF SHOW FILE TYPES FUNCTION

/*
 * FUNCTION NAME: RemoveExif()
 * 
 * OPTIONAL INPUT PARAMETERS:
 * 	removeExif: BOOLEAN TYPE VARIABLE
 * 	makeVerbose: BOOLEAN TYPE VARIABLE
 * 	fileList: STRING ARRAY TYPE VARIABLE
 * 	pathToDir: CHAR ARRAY TYPE VARIABLE
 * 	numFiles: UNSIGNED SHORT INT TYPE VARIABLE
 * 	color2: DEFINED CONSTANT STRING
 *
 * DESCRIPTION:
 *  REMOVE EXIF METADATA FROM A FILE OR FILES IN A DIRECTORY
 * 
 * PROGRAM EXECUTION STEPS:
 * 	1 - USE THE IF STATEMENT GUARD TO EVALUATE IF
 * 	    removeExif IS TRUE OR FALSE. IF IT IS TRUE,
 * 	    THE PROGRAM WILL CONTINUE AND END IF NOT
 *
 * 	2 - ADD A SPACE AT THE BEGINNING OF THE FUNCTIONS
 * 	    EXECUTION IF THE USER CHOOSES VERBOSE OUTPUT
 *
 * 	3 - INITIALIZE STATUS VARIABLES THAT WILL BE
 * 	    PRINTED IF THE USER CHHOSES TO SHOW VERBOSE
 * 	    OUTPUT WHEN makeVerbose IS TRUE
 *
 * 	4 - INFORM THE USER THE THE FUNCTION IS STARTING
 *
 * 	5 - INITIALIZE EXIF DATA MARKERS
 *
 * 	6 - INITIALIZE OUTTER FOR LOOP TO LOOP THROUGH
 * 	    EACH FILE
 *
 * 	7 - ALLOCATE MEMORY FOR THE FULL FILE PATH TO
 * 	    THE FILE pathToFile
 *
 * 	8 - COPY THE DIR PATH TO pathToFile
 *
 * 	9 - ADD A PATH SEPERATOR IN pathToFile IF THERE IS
 * 	    NOT ONE ALREADY PROVIDED BY THER USER
 *
 * 	10 - APPEND THE FILE NAME TO pathToFile
 *
 * 	11 - CHECK TO SEE IF EXIF DATA CAN BE LOADED FROM 
 * 	     THE FILE. IF NOT, PRINT A FAIL STATUS IF makeVerbose
 * 	     IS TRUE, FREE MEMORY ALLOCATED TO pathToFile, AND
 * 	     CONTINUE TO THE NEXT FILE IN THE LIST
 *
 * 	12 - OPEN THE FILE IN WRITE MODE AND AGAIN IN READ MODE
 *
 * 	13 - CHECK IF THE FILE CAN BE OPENED. IF NOT, PRINT A FAIL
 * 	     STATUS IF makeVerbose IS TRUE, FREE MEMORY ALLOCATED
 * 	     TO pathToFile, AND CONTINUE TO THE NEXT FILE IN THE
 * 	     LIST
 *
 * 	14 - READ FILE CONTENTS AND SKIP ANY DATA THAT MATCHES
 * 	     THE EXIF MARKERS AND STORE IT TO THE readfile
 * 	     FILE POINTER
 *
 * 	15 - WRITE CONTENTS READ FROM readfile BACK TO THE FILE
 * 	     WITHOUT THE EXIF DATA
 *
 * 	16 - CLOSE BOTH readfile AND writefile FILE POINTERS
 *
 * 	17 - FREE LOADED EXIF DATA BACK TO SYSTEM
 *
 * 	18 - PRINT SUCCESS STATUS TO STDOUT IF makeVerbose IS 
 * 	     TRUE, THEN FREE MEMORY ALLOCATED TO pathToFile
 *
 * 	19 - INCREMENT NUM FUNCTION CALLS TO INDICATE THAT THE FUNCTION
 * 	     HAS BEEN COMPLETED
 *
 * 	20 - END FUNCTION
 *
 * RETURN VALUE: VOID
 */
void RemoveExif(bool removeExif, bool makeVerbose, char** fileList, char* pathToDir, unsigned short int numFiles, char* color2)
{
	// IF STATEMENT GUARD
	if (removeExif == true)
	{
		// PRINT SPACE BEFORE PROGRAM START
    if (makeVerbose)
    {
		  fprintf(stdout, "\n\n");
    }

		// VARIABLES TO INDICATE SUCCESS OR FAIL OF DATA REMOVAL
    if (makeVerbose)
    {
		  const char* X_MARK_COL = "\033[38;5;160m";
		  const char* CHECK_MARK_COL = "\033[38;5;119m";
		  const char* X = "\xE2\x9C\x97";
		  const char* CHECK = "\xE2\x9C\x94";
    }

		// PRINT START OF PROGRAM STATUS TO STDOUT
		fprintf(stdout, "%sRemoving exif metadata...\033[38;5;231m\n", color2);

		// VARIABLES FOR EXIF MARKERS
		unsigned char exif_marker[] = {0xFF, 0xE1};
		unsigned char marker[2];

		// FOR LOOP FOR NUM FILES
		for (unsigned short int i = 0; i < numFiles; i++)
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
				if ((readfile == NULL) and (writefile == NULL))
				{
          if (makeVerbose)
          {
					  fprintf(stdout, "%s%s%s: %s\n", X_MARK_COL, X, color2, pathToFile);
          }
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

				// CLOSE BOTH FILE POINTERS
				fclose(readfile);
				fclose(writefile);
				
        // FREE MEMORY BACK TO SYSTEM
				exif_data_unref(exif_data);

        // PRINT SUCCESS STATUS TO STDOUT
        if (makeVerbose)
        {
				  fprintf(stdout, "%s%s%s: %s\n", CHECK_MARK_COL, CHECK, color2, pathToFile);
        }
				free(pathToFile);
			}
			else
			{
        if (makeVerbose)
        {
				  fprintf(stdout, "%s%s%s: %s\n", X_MARK_COL, X, color2, pathToFile);
        }
				free(pathToFile);
				continue;
			}

		} // END OF FILE LOOPING

		// INCREMENT NUM FUNCTION CALLS BECAUSE FUNCTION IS DONE
		numFunctionCalls++;

	} // END OF IF STATEMENT GUARD
} // END OF REMOVE EXIF METADATA FUNCTION

/*
 * FUNCTION NAME: KeyNameGen()
 * 
 * INPUT PARAMETERS:
 * 	encryptFiles: BOOLEAN TYPE VARIABLE
 * 	color1: DEFINED CONSTANT STRING
 * 	color2: DEFINED CONSTANT STRING
 *
 * DESCRIPTION:
 *  GENERATE A NAME FOR A DECRYPTION KEY
 * 
 * PROGRAM EXECUTION STEPS:
 * 	1 - ALLOCATE MEMORY FOR THE DECRYPTION KEY FILE NAME
 *
 * 	2 - CHECK IF MEMORY FOR fullKeyName WAS ALLOCATED
 *
 * 	3 - USE THE IF STATEMENT GUARD TO EVALUATE IF
 * 	    encryptFiles IS TRUE OR FALSE. IF IT IS TRUE,
 * 	    THE PROGRAM WILL CONTINUE AND END IF NOT
 *
 * 	4 - INITIALIZE OUTTER FOR LOOP TO LOOP THROUGH
 * 	    EACH FILE
 *
 * 	5 - CHECK IF MEMORY WAS ALLOCATED TO pathToFile
 *
 * 	6 - COPY THE DIR PATH TO pathToFile
 *
 * 	7 - 
 *
 * 	8 - 
 *
 * 	9 - 
 *
 * 	10 - 
 *
 * 	11 - 
 *
 * 	12 - 
 *
 * 	13 - 
 *
 * 	14 - 
 *
 * 	15 - 
 *
 * 	16 - 
 *
 * 	17 - 
 *
 * 	18 - INCREMENT NUM FUNCTION CALLS TO INDICATE THAT THE FUNCTION
 * 	     HAS BEEN COMPLETED
 *
 * 	19 - END FUNCTION
 *
 * RETURN VALUE: VOID
 */
char* KeyNameGen(bool encryptFiles, char* color1, char* color2)
{
	// ALLOCATE SPACE FOR THE KEY NAME
	char* fullKeyName = (char *)malloc(sizeof(char *) * _KEY_NAME_LEN + 9);

	// CHECK IF MEMORY WAS ALLOCATED
	if (not(fullKeyName))
	{
		fprintf(stderr, "%sERROR%s: Unable to retrive memory.\n", color1, color2);
		fprintf(stderr, "aliencrypt : MEMFAIL\n");
		exit(EXIT_FAILURE);
	}

	// IF STATEMENT GUARD
	if (encryptFiles == true)
	{

		// PRINT SPACE BEFORE PROGRAM START
		fprintf(stdout, "\n\n");

		// CHAR SETS
		const char* keyChars[] = {"0123456789", "ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

		// FORMATED STRING AND ARRAY TO HOLD GENERATED KEYNAME
		char* keyName = "KEY-%s.key";
		char genString[_KEY_NAME_LEN + 1];

		// PRINT START OF OPERATION STATUS TO STDOUT
		fprintf(stdout, "%sGenerating key for decryption...\033[38;5;231m\n", color2);
		
		// SEED THE RANDOM NUMBER GENERATOR
		srand(time(NULL));

		// GENERATE KEYNAME
		for (unsigned int i = 0; i < _KEY_NAME_LEN - 1;)
		{
			int charSet = rand() % 2;
			int charSetLen = strlen(keyChars[charSet]);

			if ((charSet == 0) or (charSet == 1))
			{
				genString[i++] = keyChars[charSet][rand() % charSetLen];
			}
		}

		// NULL TERMINATE GENERATED STRING
		genString[_KEY_NAME_LEN - 1] = '\0';
		
		// COPY CONTENTS TO KEYNAME VARIABLE
		snprintf(fullKeyName, _KEY_NAME_LEN + 9, keyName, genString);

		// INCREMENT NUM OF FUNCTION CALLS BECAUSE FUNCTION IS DONE
		numFunctionCalls++;

		return fullKeyName;

	} // END OF IF STATEMENT GUARD
	
	free(fullKeyName);
	
	return NULL;

} // END OF KEY NAME GENERATION FUNCTION

/*
 * FUNCTION NAME: EncryptFiles()
 * 
 * INPUT PARAMETERS:
 * 	encryptFiles: BOOLEAN TYPE VARIABLE
 * 	makeVerbose: BOOLEAN TYPE VARIABLE
 * 	numFiles: UNSIGNED SHORT INT TYPE VARIABLE
 * 	fileList: CHAR ARRAY TYPE VARIABLE
 * 	pathToDir: STRING TYPE VARIABLE
 * 	keyName: STRING TYPE VARIABLE
 * 	color1: DEFINED CONSTANT STRING
 * 	color2: DEFINED CONSTANT STRING
 *
 * DESCRIPTION:
 *  ENCRYPT A FILE OR FILES IN A DIRECTORY
 * 
 * PROGRAM EXECUTION STEPS:
 * 	1 - USE THE IF STATEMENT GUARD TO EVALUATE IF
 * 	    encryptFiles IS TRUE OR FALSE. IF IT IS TRUE,
 * 	    THE PROGRAM WILL CONTINUE AND END IF NOT
 *
 * 	2 - INITIALIZE STATUS VARIABLES THAT WILL BE
 * 	    PRINTED IF THE USER CHHOSES TO SHOW VERBOSE
 * 	    OUTPUT WHEN makeVerbose is TRUE
 *
 * 	3 - INFORM THE USER WHAT THE NAME OF THE 
 * 	    DECRYPTION KEY IS
 *
 * 	4 - INFORM THE USER THAT THE FUNCTION IS STARTING
 *
 * 	5 - GENERATE A RANDOM KEY
 *
 * 	6 - WRITE THE KEY TO A FILE USING THE GENERATED KEY
 * 	    NAME
 *
 * 	7 - INITIALIZE OUTER LOOP TO LOOP THROUGH EACH FILE
 *
 * 	8 - ALLOCATE MEMORY FOR THE FULL FILE PATH TO
 * 	    THE FILE pathToFile
 *
 * 	9 - ADD A PATH SEPERATOR IN pathToFile IF THERE IS
 * 	    NOT ONE ALREADY PROVIDED BY THER USER
 *
 * 	10 - APPEND THE FILE NAME TO pathToFile
 *
 * 	11 - OPEN pathToFile IN READ BINARY MODE
 *
 * 	12 - CHECK IF pathToFile CAN BE OPENED. IF NOT,
 * 	     PRINT A FAIL STATUS IF makeVerbose IS TRUE,
 * 	     THEN FREE MEMORY ALLOCATED TO pathToFile AND
 * 	     THEN CONTINUE TO THE NEXT FILE
 *
 * 	13 - GET THE SIZE OF THE FILE AT pathToFile AND STORE 
 * 	     IT TO VARIABLE inputSize
 *
 * 	14 - ALLOCATE MEMORY FOR FILE DATA inputData
 *
 * 	15 - CHECK IF MEMORY CAN BE ALLOCATED TO inputData.
 * 	     IF NOT, FREE MEMORY ALLOCATED TO pathToFile, THEN
 * 	     PRINT A MEMFAIL STATEMENT AND END THE PROGRAM
 *
 * 	16 - READ THE FILE DATA AND STORE IT TO inputData
 *
 * 	17 - GENERATE A RANDOM NONCE
 *
 * 	18 - ALLOCATE MEMORY FOR THE ENCRYPTED DATA encrypted_data
 *
 * 	19 - CHECK IF MEMORY CAN BE ALLOCATED TO encrypted_data.
 * 	     IF NOT, FREE MEMORY ALLOCATED TO pathToFile, THEN
 * 	     PRINT A MEMFAIL STATEMENT AND END THE PROGRAM
 *
 * 	20 - ENCRYPT THE DATA
 *
 * 	21 - CHECK IF THE DATA WAS ENCRYPTED. IF NOT, FREE MEMORY
 * 	     ALLOCATED TO encrypted_data, inputData, AND inputSize
 * 	     BACK TO SYSTEM AND THEN PRINT A MEMFAIL STATEMENT AND
 * 	     END THE PROGRAM
 *
 * 	22 - OPEN FILE pathToFile IN WRITE BINARY MODE TO WRITE ENCRYPTED
 * 	     DATA BACK TO IT
 *
 * 	23 - CHECK IF pathToFile CAN BE OPENED FOR WRITING. IF NOT,
 * 	     PRINT A FAIL STATUS, IF makeVerbose IS TRUE, FREE
 * 	     MEMORY ALLOCATED TO encrypted_data, inputData, pathToFile,
 * 	     AND THE CURRENT ELEMENT IN fileList BACK TO SYSTEM, AND THEN
 * 	     CONTINUE TO THE NEXT FILE
 *
 * 	24 - WRITE ENCRYPTED DATA BACK TO FILE AND CLOSE IT
 *
 * 	25 - PRINT A SUCCESS STATUS IF makeVerbose IS TRUE
 *
 * 	26 - FREE MEMORY ALLOCATED TO inputData, encrypted_data, AND 
 * 	     pathToFile
 *
 * 	27 - REPEAT STEPS 8 - 26 UNTIL EACH FILE HAS BEEN ENCRYPTED IN THE
 * 	     FILE LIST
 *
 * 	28 - FREE MEMORY ALLOCATED TO KEY NAME keyName BACK TO SYSTEM
 *
 * 	29 - INCREMENT NUM FUNCTION CALLS TO INDICATE THAT THE FUNCTION
 * 	     HAS BEEN COMPLETED
 *
 * 	30 - END FUNCTION
 *
 * RETURN VALUE:
 *  EXIT_SUCCESS - SUCCESSFUL PROGRAM EXECUTION
 *  EXIT_FAILURE - UNSUCCESSFUL PROGRAM EXECUTION; OPERAION NOT PERMITTED
 */
int EncryptFiles(bool encryptFiles, bool makeVerbose, unsigned short int numFiles, char** fileList, char* pathToDir, char* keyName, char* color1, char* color2)
{
	// IF STATEMENT GUARD
	if (encryptFiles == true)
	{
		// INDICATE SUCCESS OR FAIL
    if (makeVerbose)
    {
		  const char* X_MARK_COL = "\033[38;5;160m";
		  const char* CHECK_MARK_COL = "\033[38;5;119m";
		  const char* X = "\xE2\x9C\x97";
		  const char* CHECK = "\xE2\x9C\x94";
    }

		// PRINT WHERE THE KEY IS SAVED IN STDOUT
		fprintf(stdout, "Key is saved in : %s%s\n", color1, keyName);

		// PRINT START OF PROGRAM STATUS TO STDOUT
		fprintf(stdout, "%sStarting encryption...\033[38;5;231m\n", color2);

		// GENERATE RANDOM KEY
		unsigned char key[_KEY_SIZE];
		randombytes_buf(key, _KEY_SIZE);

		// WRITE KEY TO KEY FILE
		FILE *keyGen = fopen(keyName, "wb");
		fwrite(key, 1, _KEY_SIZE, keyGen);
		fclose(keyGen);

		// FOR LOOP FOR NUM FILES
		for (unsigned short int i = 0; i < numFiles; i++)
		{
			// ALLOCATE MEMORY FOR FULL FILE PATH
			char* pathToFile = (char *)malloc(strlen(pathToDir) + strlen(fileList[i]) + 2);

			// CHECK IF MEMORY WAS ALLOCATED
			if (not(pathToFile))
			{
				fprintf(stderr, "%sERROR%s: Unable to retrive memory.\n", color1, color2);
				fprintf(stderr, "aliencrypt : MEMFAIL\n");
				return EXIT_FAILURE;
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
        if (makeVerbose)
        {
				  fprintf(stdout, "%s%s%s: %s\n", X_MARK_COL, X, color2, pathToFile);
        }
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
				fprintf(stderr, "%sERROR%s: Unable to retrive memory.\n", color1, color2);
				fprintf(stderr, "aliencrypt : MEMFAIL\n");
				return EXIT_FAILURE;
			}

			// READ THE FILE DATA
			fread(inputData, 1, inputSize, readfile);
			fclose(readfile);

			// GENERATE A RANDOM NONCE
			unsigned char nonce[_NONCE_SIZE];
			randombytes_buf(nonce, _NONCE_SIZE);

			// ALLOCATE MEMORY FOR THE ENCRYPTED DATA
			unsigned char *encrypted_data = (unsigned char *)malloc(inputSize + _TAG_SIZE);
			unsigned char tag[_TAG_SIZE];

			// CHECK IF MEMORY WAS ALLOCATED
			if (not(encrypted_data))
			{
				free(pathToFile);
				fprintf(stderr, "%sERROR%s: Unable to retrive memory.\n", color1, color2);
				fprintf(stderr, "aliencrypt : MEMFAIL\n");
				return EXIT_FAILURE;
			}

			// ENCRYPT THE DATA
			if (crypto_secretbox_detached(encrypted_data, tag, inputData, inputSize, nonce, key) != 0)
			{
				fprintf(stderr, "%sERROR%s: Unable to encrypt file %s.\n", color1, color2, pathToFile);
				fprintf(stderr, "aliencrypt : ENCRYPT_ERR\n");
				free(inputData);
				free(encrypted_data);
				free(pathToFile);
				return EXIT_FAILURE;
			}

			// OPEN FILE TO WRITE
			FILE *writefile = fopen(pathToFile, "wb");

			// CHECK IF FILE CAN BE WRITTEN TO
			if (writefile == NULL)
			{
        if (makeVerbose)
        {
				  fprintf(stdout, "%s%s%s: %s\n", X_MARK_COL, X, color2, pathToFile);
        }
				free(inputData);
				free(encrypted_data);
				free(fileList[i]);
				free(pathToFile);
				continue;
			}

			// WRITE ENCRYPTED DATA BACK TO FILE
			fwrite(nonce, 1, _NONCE_SIZE, writefile);
			fwrite(tag, 1, _TAG_SIZE, writefile);
			fwrite(encrypted_data, 1, inputSize, writefile);
			fclose(writefile);
			
			// PRINT SUCCESS STATUS TO STDOUT
      if (makeVerbose)
      {
			  fprintf(stdout, "%s%s%s: %s\n", CHECK_MARK_COL, CHECK, color2, pathToFile);
      }

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
	
	return EXIT_SUCCESS;

} // END OF ENCRYPT FILES FUNCTION

/*
 * FUNCTION NAME: ShredFiles()
 * 
 * INPUT PARAMETERS:
 * 	removeExif: BOOLEAN TYPE VARIABLE
 * 	makeVerbose: BOOLEAN TYPE VARIABLE
 * 	fileList: STRING ARRAY TYPE VARIABLE
 * 	pathToDir: CHAR ARRAY TYPE VARIABLE
 * 	numFiles: UNSIGNED SHORT INT TYPE VARIABLE
 * 	color2: DEFINED CONSTANT STRING
 *
 * DESCRIPTION:
 *  OVERWRITE AND DELETE A  FILE OR FILES IN A DIRECTORY
 * 
 * PROGRAM EXECUTION STEPS:
 * 	1 - USE THE IF STATEMENT GUARD TO EVALUATE IF
 * 	    removeExif IS TRUE OR FALSE. IF IT IS TRUE,
 * 	    THE PROGRAM WILL CONTINUE AND END IF NOT
 *
 * 	2 - 
 *
 * 	3 - 
 *
 * 	4 - 
 *
 * 	5 - 
 *
 * 	6 - 
 *
 * 	7 - 
 *
 * 	8 - 
 *
 * 	9 - 
 *
 * 	10 - 
 *
 * 	11 - 
 *
 * 	12 - 
 *
 * 	13 - 
 *
 * 	14 - 
 *
 * 	15 - 
 *
 * 	16 - 
 *
 * 	17 - 
 *
 * 	18 - INCREMENT NUM FUNCTION CALLS TO INDICATE THAT THE FUNCTION
 * 	     HAS BEEN COMPLETED
 *
 * 	19 - END FUNCTION
 *
 * RETURN VALUE: VOID
 */
int ShredFiles(bool shredFiles, bool makeVerbose, char** fileList, unsigned short int numFiles, char* pathToDir, char* color1, char* color2)
{
	// IF STATEMENT GUARD
	if (shredFiles == true)
	{
		// PRINT SPACE BEFORE PROGRAM START
    if (makeVerbose)
    {
		  fprintf(stdout, "\n\n");
    }

		// INDICATE SUCCESS OR FAIL
		const char* X_MARK_COL = "\033[38;5;160m";
		const char* CHECK_MARK_COL = "\033[38;5;119m";
		const char* X = "\xE2\x9C\x97";
		const char* CHECK = "\xE2\x9C\x94";

		// PRINT START OF PROGRAM STATUS TO STDOUT
		fprintf(stdout, "%sStarting file shreding...\033[38;5;231m\n", color2);

		// FOR LOOP FOR NUM FILES
		for (unsigned short int i = 0; i < numFiles; i++)
		{
			// ALLOCATE MEMORY FOR FULL FILE PATH
			char* pathToFile = (char *)malloc(strlen(pathToDir) + strlen(fileList[i]) + 2);

			// CHECK IF MEMORY WAS ALLOCATED
			if (not(pathToFile))
			{
				fprintf(stderr, "%sERROR%s: Unable to retrive memory.\n", color1, color2);
				fprintf(stderr, "aliencrypt : MEMFAIL\n");
				return EXIT_FAILURE;
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
			unsigned char buffer[_BUFFER_SIZE];
			size_t bytes_read;

			// CHECK IF FILE CAN BE OPENED FOR READING AN WRITING
			if (file == NULL)
			{
        if (makeVerbose)
        {
				  fprintf(stdout, "%s%s%s: %s\n", X_MARK_COL, X, color2, pathToFile);
        }
				free(pathToFile);
				free(fileList[i]);
				continue;
			}

			// OVERWRITE THR FILE WITH RANDOM BYTES OF DATA
			for (int pass = 0; pass < _NUM_PASSES; pass++)
			{
				// RESET FILE POSITION TO BEGINNING
				fseek(file, 0, SEEK_SET);

				// FILL BUFFER WITH DATA
				while ((bytes_read = fread(buffer, 1, _BUFFER_SIZE, file)) > 0)
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
      if (makeVerbose)
      {
			  fprintf(stdout, "%s%s%s: %s\n", CHECK_MARK_COL, CHECK, color2, pathToFile);
      }

			// FREE MEMORY BACK TO SYSTEM
			free(pathToFile);

		} // END OF NUM FILE LOOP

		// INCREMENT NUM FUNCTION CALLS BECAUSE FUNCTION IS DONE
		numFunctionCalls++;

	} // END OF IF STATEMENT GUARD
	
	return EXIT_SUCCESS;

} // END OF SHRED FILES FUNCTION

/*
 * FUNCTION NAME: DecryptFiles()
 * 
 * INPUT PARAMETERS:
 * 	removeExif: BOOLEAN TYPE VARIABLE
 * 	makeVerbose: BOOLEAN TYPE VARIABLE
 * 	fileList: STRING ARRAY TYPE VARIABLE
 * 	pathToDir: CHAR ARRAY TYPE VARIABLE
 * 	numFiles: UNSIGNED SHORT INT TYPE VARIABLE
 * 	color2: DEFINED CONSTANT STRING
 *
 * DESCRIPTION:
 *  DECRYPT A FILE OR FILES IN A DIRECTORY WITH A USER PROVIDED DECRYPTION KEY
 * 
 * PROGRAM EXECUTION STEPS:
 * 	1 - USE THE IF STATEMENT GUARD TO EVALUATE IF
 * 	    removeExif IS TRUE OR FALSE. IF IT IS TRUE,
 * 	    THE PROGRAM WILL CONTINUE AND END IF NOT
 *
 * 	2 - 
 *
 * 	3 - 
 *
 * 	4 - 
 *
 * 	5 - 
 *
 * 	6 - 
 *
 * 	7 - 
 *
 * 	8 - 
 *
 * 	9 - 
 *
 * 	10 - 
 *
 * 	11 - 
 *
 * 	12 - 
 *
 * 	13 - 
 *
 * 	14 - 
 *
 * 	15 - 
 *
 * 	16 - 
 *
 * 	17 - 
 *
 * 	18 - INCREMENT NUM FUNCTION CALLS TO INDICATE THAT THE FUNCTION
 * 	     HAS BEEN COMPLETED
 *
 * 	19 - END FUNCTION
 *
 * RETURN VALUE: VOID
 */
int DecryptFiles(bool decryptFiles, bool makeVerbose, unsigned short int numFiles, char** fileList, char* pathToDir, char* keyPath, char* color1, char* color2)
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
		fprintf(stdout, "%sStarting decryption...\033[38;5;231m\n", color2);

		// FOR LOOP FOR NUM FILES
		for (unsigned int i = 0; i < numFiles; i++)
		{
			// ALLOCATE MEMORY FOR FULL FILE PATH
			char* pathToFile = (char *)malloc(strlen(pathToDir) + strlen(fileList[i]) + 2);

			// CHECK IF MEMORY WAS ALLOCATED
			if (not(pathToFile))
			{
				fprintf(stderr, "%sERROR%s: Unable to retrive memory.\n", color1, color2);
				fprintf(stderr, "aliencrypt : MEMFAIL\n");
				return EXIT_FAILURE;
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
			unsigned char key[_KEY_SIZE];
			FILE *keyRead = fopen(keyPath, "rb");
			fread(key, 1, _KEY_SIZE, keyRead);
			fclose(keyRead);

			// OPEN ENCRYPTED FILE
			FILE *readfile = fopen(pathToFile, "rb");

			// CHECK IF FILE CAN BE OPENED
			if (readfile == NULL)
			{
        if (makeVerbose)
        {
				  fprintf(stdout, "%s%s%s: %s\n", X_MARK_COL, X, color2, pathToFile);
        }
				free(pathToFile);
				continue;
			}

			// READ NONCE FROM FILE
			unsigned char nonce[_NONCE_SIZE];
			fseek(readfile, 0, SEEK_SET);
			fread(nonce, 1, _NONCE_SIZE, readfile);

			// READ AUTHENTICATION TAG FROM FILE
			unsigned char tag[_TAG_SIZE];
			fseek(readfile, _NONCE_SIZE, SEEK_SET);
			fread(tag, 1, _TAG_SIZE, readfile);

			// GET ENCRYPTED DATA SIZE
			fseek(readfile, 0, SEEK_END);
			long encrypted_size = ftell(readfile) - _NONCE_SIZE - _TAG_SIZE;
			fseek(readfile, _NONCE_SIZE + _TAG_SIZE, SEEK_SET);

			// ALLOCATE MEMORY FOR ENCRYPTED FILE DATA
			unsigned char *encrypted_data = (unsigned char *)malloc(encrypted_size);

			// CHECK IF MEMORY WAS ALLOCATED
			if (not(encrypted_data))
			{
				fprintf(stderr, "%sERROR%s: Unable to retrive memory.\n", color1, color2);
				fprintf(stderr, "aliencrypt : MEMFAIL\n");
				return EXIT_FAILURE;
			}

			// READ ENCRYPTED DATA FROM ENCRYPTED FILE AND CLOSE THE FILE
			fread(encrypted_data, 1, encrypted_size, readfile);
			fclose(readfile);

			// ALLOCATE MEMORY FOR DECRYPTED DATA
			unsigned char *decrypted_data = (unsigned char *)malloc(encrypted_size);

			// CHECK IF MEMORY WAS ALLOCATED
			if (not(decrypted_data))
			{
				fprintf(stderr, "%sERROR%s: Unable to retrive memory.\n", color1, color2);
				fprintf(stderr, "aliencrypt : MEMFAIL\n");
				return EXIT_FAILURE;
			}

			// DECRYPT THE DATA
			if (crypto_secretbox_open_detached(decrypted_data, encrypted_data, tag, encrypted_size, nonce, key) != 0)
			{
				free(decrypted_data);
				free(encrypted_data);
				fprintf(stderr, "%sERROR%s: Unable to encrypt file %s.\n", color1, color2, pathToFile);
				fprintf(stderr, "aliencrypt : ENCRYPT_ERR\n");
				return EXIT_FAILURE;
			}

			// WRITE OPEN FILE TO WRITE
			FILE *writefile = fopen(pathToFile, "wb");

			// CHECK IF FILE CAN BE WRITTEN TO
			if (writefile == NULL)
			{
        if (makeVerbose)
        {
				  fprintf(stdout, "%s%s%s: %s\n", X_MARK_COL, X, color2, pathToFile);
        }
				free(decrypted_data);
				free(encrypted_data);
				free(pathToFile);
				continue;
			}

			// WRITE DECRYPTED DATA BACK TO FILE
			fwrite(decrypted_data, 1, encrypted_size - _TAG_SIZE, writefile);
			fclose(writefile);

			// PRINT SUCCESS STATUS TO STDOUT
      if (makeVerbose)
      {
			  fprintf(stdout, "%s%s%s: %s\n", CHECK_MARK_COL, CHECK, color2, pathToFile);
      }

			// FREE MEMORY BACK TO SYSTEM
			free(encrypted_data);
			free(decrypted_data);
			free(pathToFile);

		} // END OF NUM FILE LOOP

		// INCREMENT NUM FUNCTION CALLS BECAUSE FUNCTION IS DONE
		numFunctionCalls++;

	} // END OF IF STATEMENT GUARD

	return EXIT_SUCCESS;

} // END OF DECRYPT FILES FUNCTION
 // END OF PROGRAM
