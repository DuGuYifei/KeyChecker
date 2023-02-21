from win32file import ReadFile, WriteFile, CloseHandle, CreateFile


def start():
    # Connect to named pipe
    pipe = win32file.CreateFile("\\\\.\\pipe\\my_pipe",
                                -2147483648 | 1073741824,  # win32file.GENERIC_READ | win32file.GENERIC_WRITE,
                                0,
                                None,
                                3,  # win32file.OPEN_EXISTING,
                                0,
                                None)

    # Read response from pipe
    response = win32file.ReadFile(pipe, 1024)[1]
    print("Received response:", response.decode())

    # Send message to pipe
    message = b"Hello from Python!"
    win32file.WriteFile(pipe, message)

    win32file.CloseHandle(pipe)


if __name__ == "__main__":
    start()
