#!/usr/bin/python3

import shutil

total, used, free = shutil.disk_usage("/")
total2, used2, free2 = shutil.disk_usage("/home")


def size_format(b):
    if b < 1000:
        return '%i' % b + 'B'
    elif 1000 <= b < 1000000:
        return '%.1f' % float(b/1000) + 'KB'
    elif 1000000 <= b < 1000000000:
        return '%.1f' % float(b/1000000) + 'MB'
    elif 1000000000 <= b < 1000000000000:
        return '%.1f' % float(b/1000000000) + 'GB'
    elif 1000000000000 <= b:
        return '%.1f' % float(b/1000000000000) + 'TB'

root = ("/r " + size_format(free))
home = ("/h " + size_format(free2))

if __name__ == "__main__":
    print(root, home)
