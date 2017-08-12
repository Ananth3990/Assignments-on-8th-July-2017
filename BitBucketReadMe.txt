i) Create a account on bitbucket, https://bitbucket.org/
ii) Once signed in you should be on the home page of bitbucket.
iii) click on the plus sign on the left pannel. ("+" sign)
iv) Click on create new -> Repository.
v) Give name to your repository. Let the name pattern be <YourName>RTRAssignements. E.g. RohitMagdumRTRAssignments. Keep the rest of the settings as it is. i.e. Git selected. Not mercurial
vi) Once you have created repository you should see two links at the bottom of the page. viz i) I have an existing project ii)  I'm starting from scratch. Click on second option.
vii) There you should see commands that need to be run. To run these commands you will need git bash. Its nothing but a command promt similar to one on linux.
viii) Download the latest "Git for windows" setup from here. https://git-scm.com/download/win
ix) Once the setup is done you should be able to find a exe name Git bash. Click on windows Icon and type "git bash". Click on the first option that you see on windows panel.
x) You should now see a black command promt. Here you can run the git commands.
xi) Now browse to the directory where you want to save all you class assignment work. E.g. E:\Class\.
xi) Now copy the first command from step vi) that you see on bitbucket webpage. e.g. git clone https://rohitmagdum@bitbucket.org/rohitmagdum/rohitmagdumrtrassignments.git paste it on 
    the git bash command prompt and press <Enter>
xii) You should now see a new director formed where you ran the command. E.g. E:\Class\RohitMagdumRTRAssignments. cd to the directory. e.g. cd E:\Class\RohitMagdumRTRAssignments.
xiii) Create a folder hierarchy under this directory as follows:-
                  RohitMagdumRTRAssignments\
				                           |
										   |
										   - OpenGL_On_Windows\
										                      |
															  |
															  - Native\
															  |       |
															  |		  |
															  |		  - <Date>e.g. July8\
															  |		                    |
															  |							|
															  |							- <Project/Assignment Name> e.g. FullScreenWindow
															  |
															  - GLUT\
xiv) One this hierarchy is created add the structure to your git repo you cloned in step xi. E.g. git add OpenGL_On_Windows\
xv) Now commit the directory to the repo. Command for the same is, git commit -m <Your commit comment>. E.g. git commit -m "Initial commit for FullScreenWindow"
xvi) Once committed you need to push the changes to the remote branch. You can do this using command, "git push -u origin master". 
xvii) Here I am assuming we will be working only on master branch. Let's not make it complicated for now.
xviii) Once this is done you are good to go to make changes to your files, add new files, folders etc... and commit and push to repository.
xix) Ideally I would recommend you to checkout your own repo on a different location e.g. E:\Class\Test. Step to do this is same as in step xi. 
	"git clone https://rohitmagdum@bitbucket.org/rohitmagdum/rohitmagdumrtrassignments.git"
xx) Now whenever you make changes to original repo. E.g. you make changes to say E:\Class\RohitMagdumRTRAssignments\OpenGL_On_Windows\Native\July8\FullScreenWindow\Source.cpp.
    You need to add the file using "git add <relative path>/Source.cpp>"
	                then commit it "git commit -m "Changes to Source.cpp"
			then push the changes  "git push -u origin master"
xxi) To test your changes go to your Test directory E.g. E:\Class\Test\RohitMagdumRTRAssignments. And run the command "git pull".
xxii) This should update your test repo with latest changes. Now compile the project from Test directory and confirm everything is working. This is a good practice to test the code.

Note:- i) Please remember to commit the whole project. But before doing that clean the project. So that no debug files get committed unnecessary.
       ii) The other person should be able to clone your repo open the project and compile and run as it is without any changes. So make sure your dependencies are all resolved.
	       Creating the Test directory and testing your own code is precisely for this reason.


		   