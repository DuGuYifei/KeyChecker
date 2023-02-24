# README

User client is the keyCheker log in gui by user. User input the key and send http request to server.

After that the wrapper will communicate or control somthing with wrapee.

After Login:

* Use winapi to create **Message pipe** that can help to make communication between multiprocesses.
* Use **shared memory** to access highly effiecent communication between multiprocesses
* Create **new thread** to always listen the message pipe, if get new message print it. When close it will stop this new thread.
* Create **new thread** to evaluate shared memory and control something of wrappee.
* In this project I create communication **between C++ and python**.