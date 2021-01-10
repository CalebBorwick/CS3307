To run the lunarModule 
	1. Install QT if not already installed
		i) run 
			$ sudo apt-get install build-essential
			$ sudo apt-get install qtcreator
			$ sudo apt install qt5-default
			$ sudo apt-get install qt5-doc qtbase5-examples qtbase5-doc-html
	2. Naviagte to lunarModule folder
	3. run
		$ qmake lunarModule.pro
		$ make
		$ ./lunarModule
	4. Testing
		i) when prompted please answer yes or no to turn on or off features and to try the tests
		ii)Acceptance Tests:
			1.Change displayLunarProfile to on
			2.Change displayLunarProfile to off
	5. After test setting are inputed click on the lunarModule to load in information
