# TCP Chat Server

A simple TCP chat server implemented in C++ using the Winsock API. This server can handle multiple clients simultaneously and allows them to communicate with each other in real time.

## Features

- **Multi-client Support:** Handles multiple clients connected at the same time.
- **Welcome Message:** Sends a welcome message to each client upon connection.
- **Client Messaging:** Broadcasts messages sent by a client to all connected clients.
- **Server Shutdown:** Allows the server to be gracefully shut down by sending the `\quit` command.

## Prerequisites

- **Windows Operating System:** This server is built using Winsock, which is specific to Windows.
- **C++ Compiler:** You will need a C++ compiler that supports the Winsock API. Microsoft Visual Studio is recommended.
- **Git:** If you plan to clone this repository from GitHub.

## Setup

1. **Clone the repository:**
   ```bash
   git clone https://github.com/OmarElprolosy66/Simple_Cpp_TCP_Chat_Room.git
   ```
   
2. **Navigate to the project directory:**
   ```bash
   cd tcp-chat-server
   ```

3. **Open the project in your C++ IDE:**
   - Open the `.sln` file if you're using Visual Studio.
   - Alternatively, create a new project in your preferred IDE and add the source files.

4. **Build the project:**
   - Use your IDE's build functionality or run the build command from the terminal.

## Usage

1. **Run the server:**
   - Start the compiled server executable from your terminal or IDE.

2. **Connect to the server:**
   - Use Netcat or any other TCP client to connect to the server:
     ```bash
     ncat 127.0.0.1 54000
     ```

3. **Send Messages:**
   - Type messages into your TCP client to broadcast them to all connected clients.

4. **Shutdown the server:**
   - Type `\quit` to shut down the server gracefully.

## Example

```bash
> ncat 127.0.0.1 54000
Welcome to the Awesome Chat Server!
```

## Troubleshooting

- **Bind Error (`WSAGetLastError() == 10047`):** Ensure that you're using the correct socket address family (`AF_INET`).
- **Server not shutting down with `\quit`:** Make sure you're handling the newline character correctly in your `recv` buffer.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request if you have any improvements or bug fixes.

## Acknowledgments

- Winsock API documentation: [Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/winsock/)
- Netcat utility: [Netcat](https://nmap.org/ncat/)
