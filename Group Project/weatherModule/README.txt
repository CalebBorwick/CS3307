To run the weatherModule 
	1. Install QT if not already installed
		i) run 
			$ sudo apt-get install build-essential
			$ sudo apt-get install qtcreator
			$ sudo apt install qt5-default
			$ sudo apt-get install qt5-doc qtbase5-examples qtbase5-doc-html
	2. Naviagte to weatherModule folder
	3. run
		$ qmake weatherModule.pro
		$ make
		$ ./weatherModule
	4. Testing
		i) when prompted please answer yes or no to turn on or off features and to try the tests
		ii)Acceptance Tests:
			1.Change week to 1 day
			2.Change week to 5 day
			3.Try setting the unit to F
			4.Try setting the unit to C
			5.Try setting the details on
			6.Try setting the details off
			7.Turn off all weather
	5. After test setting are inputed click on the weatherModule to load in information




