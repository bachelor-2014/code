# POCS
- See readme in /pocs

#Build and run
The following is a description of how to build and run the programs written for
our Splotbot setup on a Unix like OS. The dependencies are also described here (including an
apt-get command for debian based Linux distros)

Initially make, a c++11 compliant compiler, NodeJS in version v0.10.26 and OpenCV in version 4.8 is expected
to be installed. Newer/Older versions of NodeJS and OpenCV might also work.

Ubuntu/Debian scripts for OpenCV can be found
[here](https://github.com/jayrambhia/Install-OpenCV/blob/master/Ubuntu/)

NodeJS can be installed and updated doing:
> sudo apt-get install nodejs

> sudo npm install n -g

> sudo n 0.10.26

##Building the C++ code and test program (splotbot/cpp)
Enter the cpp directory and run the make file:
> make

Now you can run the test program with:
> ./test.out

##Building and running the NodeJS server (splotbot/node)
First install the needed NodeJS packages with npm:
> sudo npm install node-gyp -g

> npm install

Then you need to get libcurl:
> sudo apt-get install libcurl4-gnutls-dev

##Building and running the web client (splotbot/client)
First install the NodeJS packages with npm:
> sudo npm install grunt-cli -g

> sudo npm install bower -g

> npm install

Then we need to install ruby and compass:
> sudo apt-get install ruby-full rubygems1.8

> sudo gem install compass

Now we install the dependencies using bower:
> bower install

Then we can host the client using grunt:
> grunt serve --force
