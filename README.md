# README

User client is the keyCheker log in gui by user. User input the key and send request to server.

After Login:

* Use winapi to create **Message pipe** that can help to make communication between processes.

* Create **new thread** to always listen the message pipe, if get new message print it. When close it will stop this new thread.

* In this project I create communication **between C++ and python**.