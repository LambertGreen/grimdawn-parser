#!/usr/bin/env python3

import lldb
import struct


def set_throw_breakpoint(debugger, command, result, internal_dict):
    debugger.HandleCommand("breakpoint set -E c++")


def __lldb_init_module(debugger, internal_dict):
    set_throw_breakpoint(debugger, None, None, None)


def uint32_to_hex(value):
    little_endian = struct.pack("<I", value)
    big_endian = struct.pack(">I", value)
    return little_endian.hex(), big_endian.hex()
