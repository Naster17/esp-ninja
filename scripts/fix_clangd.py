import json
from pathlib import Path
import subprocess

# Constants
PROJECT_ROOT = Path.cwd()
SRC_FILE = PROJECT_ROOT / "src" / "kernel" / "init" / "main.cpp"
CCDB_ORIG = PROJECT_ROOT / "compile_commands.json"
CCDB_BAK = PROJECT_ROOT / "compile_commands.json.bak"
CCLS_FILE = PROJECT_ROOT / ".ccls"
CCDB_NEW = PROJECT_ROOT / "compile_commands.json"

KEEP_FLAGS = ("-I", "-D", "-std", "-Wall")


def ensure_compile_commands():
    if not CCDB_ORIG.exists():
        subprocess.run(["pio", "run", "-t", "compiledb"], check=True)
    if not CCDB_BAK.exists():
        CCDB_ORIG.rename(CCDB_BAK)


def extract_compiler():
    ccdb_data = json.loads(CCDB_BAK.read_text())
    if not ccdb_data:
        raise RuntimeError("Empty compile_commands.json.bak")
    cmd = ccdb_data[0]["command"]
    compiler = cmd.split()[0]
    return compiler


def parse_ccls():
    common_flags = []
    cpp_flags = []
    with open(CCLS_FILE) as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            if line.startswith("%cpp"):
                cpp_flags.extend([flag for flag in line.split()[
                                 1:] if flag == "-Wall" or flag.startswith(KEEP_FLAGS)])
            elif line.startswith("%c"):
                pass  # skip C files for now
            elif not line.startswith("%"):
                common_flags.extend([flag for flag in line.split(
                ) if flag == "-Wall" or flag.startswith(KEEP_FLAGS)])
    return common_flags + cpp_flags


def generate_single_entry_compile_command(compiler, flags):
    entry = {
        "directory": str(PROJECT_ROOT),
        "file": str(SRC_FILE),
        "command": f"{compiler} {' '.join(flags)} {SRC_FILE}"
    }
    CCDB_NEW.write_text(json.dumps([entry], indent=2))
    return 1


# Execution
ensure_compile_commands()
compiler_path = extract_compiler()
filtered_flags = parse_ccls()
entry_count = generate_single_entry_compile_command(
    compiler_path, filtered_flags)
