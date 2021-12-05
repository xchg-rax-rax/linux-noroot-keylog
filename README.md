# Linux Keylogger - No Root Required!

This project is a Linux keylogger that leverages the X windows system running on essentially every Linux distribution with a GUI.
You can't directly access device files associated with your keyboard without root privileges which cuts off the most obvious root for acquiring keystroke information if you only have an unprivileged account.
However the X windows system which handles the rendering and management of essentially all desktop environments on Linux is always running unless the user has booted into a tty and is running as root.
In order for users to be able to write useful software using X windows it has to gather keystroke events form the systems device files and make them available to applications running on the system.
As a result by making appropriate calls to the Xlib and XInput libraries we can capture all keyboard events that occur with any of application being run by a user on the system (although notably not those that occur with a tty session).

## Compilation 

## Usage

## Disclaimer

I made this as a fun project for my own amusement and as a means of learning more about how input devices work on Linux.
I did not make this as a tool for people with malicious intent to use in order to spy on other, steal from them or otherwise cause harm.
Never use this on a system you don't own or have permission to modify.
I am not responsible for your actions.
