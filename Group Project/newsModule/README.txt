To run the newsModule 
	1. Install QT if not already installed
		i) run 
			$ sudo apt-get install build-essential
			$ sudo apt-get install qtcreator
			$ sudo apt install qt5-default
			$ sudo apt-get install qt5-doc qtbase5-examples qtbase5-doc-html
	2. Naviagte to newsModule folder
	3. run
		$ qmake newsModule.pro
		$ make
		$ ./newsModule
	4. Testing
		i) when prompted please choose type and country code
		ii)Acceptance Tests: 
			1.Run newsModule and choose different category 
			2.Run newsModule and choose and change country
			
	5. The newsModule updates the headlines, but since the headlines don't change that often, you might not see different ones for the same country and category.
