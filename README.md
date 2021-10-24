### A simple script written in C using ftw.h to delete all folders in CWD by specifying its names. 

This is very handy if you have a folder called the same name in multiple folders in your working directory. I made this to be able to delete the "samples" folder in all my Ableton projects, which takes up unnecessary space when you have the files bounced separetely. 

Build it and put it inside /usr/local/bin/ on your unix machine. Go to the folder where you want to recursively delete folders by a specific name. 
```
delete_folders FOLDER_NAME
```

The program will first show you the matches and then prompt you for y/n to make sure it found the correct ones. 