# KeyChecker

Prepare a "coat" for other programs which user can use a time-limited key to log in. 

The wrapper framework use `mysql` and contains back-end (`Springboot`), back-end supervisor interface (`vue`) and user client (`Qt c++`).

Because it is a wrapper, so sometimes it need communication between user client and the wrappee (another program). Here I use python as a wrappee which means I will create communication between processes. In this project I use a script (python) to create another client of message pipe.
