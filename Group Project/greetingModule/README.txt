To run the greetingsModule 
	1. Install QT if not already installed
		i) run 
			$ sudo apt-get install build-essential
			$ sudo apt-get install qtcreator
			$ sudo apt install qt5-default
			$ sudo apt-get install qt5-doc qtbase5-examples qtbase5-doc-html
	2. Naviagte to greetingsModule folder
	3. run
		$ qmake greetings.pro
		$ make
		$ ./greetings
	4. Testing
		i) Based on your personal profile, you will see a personalized greeting message
		   and an inspirational quote
		ii)Acceptance Tests: 
			1.Change the user profile and see that the greeting message is changed
			
			
	5. The inspirational quote gets updated.
