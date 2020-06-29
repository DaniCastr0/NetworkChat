# Network chat

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

This project is about a chat using wxWidget and sockets. The main obejctive is to provide to the user an GUI interface for chating with someoneelse in
the same network. Future developments will extend it to be used with clients in different networks.


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* wxwidget:
  * Follow the instructions here https://wiki.wxwidgets.org/Install.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./NetworkChat`.


## Classes used in the project

* class NetworkChatApp: child of wxApp. The wxApp class represents the application itself. It encapsuled the main function and provide an infinity loop.
* class NetworkChatFrame: child of wxFrame. It represents the main window of the application.
* class NetworkChatPanelDialog: child of wxScrolledWindow. It is a window that scrolls children and graphics and it will be the place where the dialogs are shown.
* class NetworkChatPanelDialogItem: child of wxPanel. It contains the messages of the users.
* class ipbox: child of wxDialog. it is the windows where the client user write the ip of the server.
* class SocketServer: Socket that accept petitions from the clients.
* class SocketClient: Socket that ask for conection to the server.


## Rubric points reached

1. The project demonstrates an understanding of C++ functions and control structures.
2. The project accepts user input and processes the input.(chatgui.cpp:86)
3. The project uses Object Oriented Programming techniques.
4. Classes use appropriate access specifiers for class members.
5. Class constructors utilize member initialization lists.
6. Classes encapsulate behavior.
7. Classes follow an appropriate inheritance hierarchy.
8. The project makes use of references in function declarations.(chatgui.cpp:315,chatgui.cpp:351).
9. The project uses smart pointers instead of raw pointers.(chatgui.cpp:35).
10. The project uses multithreading.(chatgui.cpp:346).
11. A mutex or lock is used in the project.(socketserver.cpp:60)


## Instruction fortesting the App in your local machine.

1. Open one instance of NetworkChat.
2. In the menu file, choose listen. The instance will be waiting for a client.
![Listen](images/file.png)
3. Open another instance of NetworkChat.
4. Choose connect in the file menu. A box will appear. There, you can write the ip of your local machine (127.0.0.1).
![Connecting](images/connect.png)
5. Test it writing in both chats and cheacking that the message appear in the other.