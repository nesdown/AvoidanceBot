// Блок логування даних та їх зовнішньої обробки

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "OttoSerialCommand.h"


#include <string.h>


// Конструкторний ініціалізатор 
OttoSerialCommand::OttoSerialCommand()
{
	strncpy(delim," ",MAXDELIMETER);  // strtok_r needs a null-terminated string
	term='\r';   // return character, default terminator for commands
	numCommand=0;    // Number of callback handlers installed
	clearBuffer(); 
}



// Ініціююча команда
void OttoSerialCommand::clearBuffer()
{
	for (int i=0; i<SERIALCOMMANDBUFFER; i++) 
	{
		buffer[i]='\0';
	}
	bufPos=0; 
}

// Програма отримання ключа оновлення 
char *OttoSerialCommand::next() 
{
	char *nextToken;
	nextToken = strtok_r(NULL, delim, &last); 
	return nextToken; 
}

// Буферна команда створення потоку вводу даних
void OttoSerialCommand::readSerial() 
{
	bool onlyOneCommand = true;
	// If we're using the Hardware port, check it.   Otherwise check the user-created OttoSoftwareSerial Port
	while ((Serial.available() > 0)&&(onlyOneCommand==true))
	{
		int i; 
		boolean matched; 
		
			inChar=Serial.read();   // Read single available character, there may be more waiting
		
		if (inChar==term) {     // Check for the terminator (default '\r') meaning end of command

			onlyOneCommand=false; //
			
			bufPos=0;           // Reset to start of buffer
			token = strtok_r(buffer,delim,&last);   // Search for command at start of buffer
			if (token == NULL) return; 
			matched=false; 
			for (i=0; i<numCommand; i++) {
				
				// Compare the found command against the list of known commands for a match
				if (strncmp(token,CommandList[i].command,SERIALCOMMANDBUFFER) == 0) 
				{
					
					// Execute the stored handler function for the command
					(*CommandList[i].function)(); 
					clearBuffer(); 
					matched=true; 
					break; 
				}
			}
			if (matched==false) {
				(*defaultHandler)(); 
				clearBuffer(); 
			}

		}
		if (isprint(inChar))   // Only printable characters into the buffer
		{
			buffer[bufPos++]=inChar;   // Put character into buffer
			buffer[bufPos]='\0';  // Null terminate
			if (bufPos > SERIALCOMMANDBUFFER-1) bufPos=0; // wrap buffer around if full  
		}
	}
}

// Блок перевірки кількості команд та оновлення даних
{
	if (numCommand < MAXSERIALCOMMANDS) {
				
		strncpy(CommandList[numCommand].command,command,SERIALCOMMANDBUFFER); 
		CommandList[numCommand].function = function; 
		numCommand++; 
	} 
}

// This sets up a handler to be called in the event that the receveived command string
// isn't in the list of things with handlers.
void OttoSerialCommand::addDefaultHandler(void (*function)())
{
	defaultHandler = function;
}
