from ctypes import *
import getpass

lib = cdll.LoadLibrary('./mdkey.so')
get_mkey = lib.get_md_key
get_mkey.argtype = (c_char_p)
get_mkey.restype = (c_char_p)
pwd = create_string_buffer(16)
pwd.raw = str(getpass.getpass("Input your pwd:")).encode()
key = get_mkey(pwd)
print('get key: ' ,key)
