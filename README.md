# Phonebook
A very simple C project using sqlite3 and autotools to simulate a Phonebook.

## Build Process
First use the autoreconf to generate the needed files for the build  
```
autoreconf --install
```

Then build it like any autotools project you just have to run the following commands:

```
.\configure
make
```
And you will have a executable file.  

If you want to install the application
```
make install
```