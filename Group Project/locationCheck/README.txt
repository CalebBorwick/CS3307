To run the locationModule
	1. Install QT if not already installed
		i) run 
			$ sudo apt-get install build-essential
			$ sudo apt-get install qtcreator
			$ sudo apt install qt5-default
			$ sudo apt-get install qt5-doc qtbase5-examples qtbase5-doc-html
	2. Naviagte to locationModule folder
	3. run
		$ qmake locationCheck.pro
		$ make
		$ ./locationCheck
	4. Testing
		i)Acceptance Tests:
			1.Can the location be set automatically?
			2.Can the location be set manually?
	5. Completing the window the set location of the user changes.
