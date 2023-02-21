from multiprocessing.shared_memory import SharedMemory


class MyStruct(ctypes.Structure):
    _fields_ = [("x", ctypes.c_int),
                ("y", ctypes.c_int),
                ("is_pressing", ctypes.c_bool)]


if __name__ == "__main__":
    shm = SharedMemory(name="ControllerMemeory", create=False, size=12)
    shm_buf = shm.buf
    p_my_struct = MyStruct.from_buffer(shm_buf)

    print(p_my_struct.x)
    p_my_struct.x = 2
    print(p_my_struct.x)

    shm.unlink()
    shm.close()
