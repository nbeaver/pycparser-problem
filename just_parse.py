#! /usr/bin/env python

import pycparser
import sys


def parse(filename):
    try:
        ast = pycparser.parse_file(filename)
    except pycparser.plyparser.ParseError:
        sys.stderr.write("File: {}\n".format(filename))
        raise

if __name__ == '__main__':
    if len(sys.argv) == 1:
        sys.stderr.write("Usage: {} /path/to/file.c\n".format(sys.argv[0]))
        sys.exit(1)

    paths = sys.argv[1:]
    for path in paths:
        parse(path)
