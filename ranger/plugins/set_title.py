import ranger.api
import subprocess
import sys
import os

def set_terminal_title(cwd):
    sys.stdout.write(f"\x1b]0;ranger: {cwd}\x07")
    sys.stdout.flush()


HOOK_READY_OLD = ranger.api.hook_ready

def hook_ready(fm):
    sys.stdout.write(f"\x1b]0;Ranger\x07")
    sys.stdout.flush()
    return HOOK_READY_OLD(fm)

ranger.api.hook_ready = hook_ready
