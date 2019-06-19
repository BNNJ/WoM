# WoM

WoM ( windows or mac ) is a Script launcher used as a Virtual Machine manager.

## Usage

Place your script files ( .sh only ) inside the *scripts* directory.
Inside the WoM directory launch ./wom.
Select the script you want to use and press *Enter* to launch it.

## Behavior

By default the executable scans his working directory for a *scripts* diectory

You can either pass various scripts directly as argument.

Or if you want to put Wom inside your */usr/local/bin* directory or another path then use -d option to pass a *scripts* directory or just place a *scripts* directory inside the same directory as the wom executable.

## Options

|Options|           Usage            |
|-------|----------------------------|
|  -d   | Pass a *scripts* directory |

## Useful Tools

[Text to Ascii generator](http://patorjk.com/software/taag/)

## Todo

- Add Submenu for script if options exists.
- Add minilang options parsing inside bash script from executable.
