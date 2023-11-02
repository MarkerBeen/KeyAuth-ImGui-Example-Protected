# KeyAuth-ImGui-Example-Protected


his is way more secure than client side authentication if you implement it correctly and do some extra steps.

- - - -

### How to implement this correctly?
- Encrypt the packets
- Make the packets invalid after being used once
- Handle key parts of the application from the server (just like I sent the parameters for MessageBoxA in the example) so a cracker cannot just jump to a function in order to bypass the authentication

### Building

Prerequisites:
- A Linux server with the latest stable CMake and g++ installed
- A Windows machine with Visual Studio installed
- - - -
#### Building the server:
Clone the repository and create a build folder
```
cd build
cmake ..
cmake --build .
```
Now you can execute `server`
- - - -
#### Building the client:
Open the solution and click Build -> Rebuild Solution
- - - -
### Example output
Client:

![](https://i.imgur.com/YaYT7OM.png)

Server:

![](https://i.imgur.com/U6xg2SZ.png)


Change 3 strings in program.cs and you're ready.

KeyAuth CPP Example

- Download Repository
- extract `libs.zip` so that there is a libs folder in your project. then you may delete `libs.zip` 
- Add application info to main.cpp file, here is a video tutorial if needed: https://youtube.com/watch?v=uJ0Umy_C6Fg

Then you are ready to compile!

**What is KeyAuth?**

KeyAuth is a GameChanging authentication system. We have never-seen before features, and we listen to our customers.
Feel free to join https://keyauth.com/discord/ if you have questions or suggestions.


**What is KeyAuth?**

KeyAuth is an Open source authentication system with cloud hosting plans as well. Client SDKs available for C++, C#, Python, Rust, PHP, and VB.NET. KeyAuth several unique features such as memory streaming, webhook function where you can send requests to API without leaking the API, discord webhook notifications, ban the user securely through the application at your discretion. Feel free to join https://keyauth.win/discord/ if you have questions or suggestions.
