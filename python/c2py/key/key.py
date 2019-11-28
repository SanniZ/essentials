import os
import sys
import getpass
from ctypes import cdll, c_char_p, create_string_buffer

LIBKEY = os.path.abspath('libkey.so')

if __name__ == '__main__':
    if not os.path.exists(LIBKEY):
        print("No found %s" % LIBKEY)
        sys.exit()
    lib = cdll.LoadLibrary(LIBKEY)
    lib.get_key.argtype = (c_char_p)
    lib.get_key.restype = (c_char_p)
    passwd = create_string_buffer(16)
    passwd.raw = str(getpass.getpass("Input your pwd:")).encode()
    key = lib.get_key(passwd)
    print('get key: ', key)
