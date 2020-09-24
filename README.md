Class assignment for CS537 Operating System Fall 2020

Authors: Marvin Tan(marvin.tan@wisc.edu), Joseph Martin (jrmartin4@wisc.edu)

Build a customized ps command
Usage:

	537ps [options]
		options:
  
		-p <pid> or -p<pid>	Display process information only for the process whose number is
				pid. Multiple occurance is allowed.

		-s		Display the single-character state information about the process. 
				(default false)
		-s-		turns the -s option off

		-U		Display the amount of user time consumed by this process.
				(default true)
		-U-		turns the -U option off

		-S		Display the amount of system time consumed so far by this process.
				(default false)
		-S-		turns the -S option off

		-v		Display the amount of memory currently being used by this program.
				(default false)
		-v-		turns the -v option off

		-c		Display the command-line that started this program.
				(default true)
		-c- 		turns the -c option off
