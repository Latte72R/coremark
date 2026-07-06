import sys


def print_usage():
    print("Usage:", sys.argv[0], "[bytes per line] [filename]")
    exit()


args = sys.argv[1:]
if len(args) != 2:
    print_usage()

try:
    bytes_per_line = int(args[0])
except Exception:
    print_usage()

with open(args[1], "rb") as f:
    bytestrs = [format(b, "02x") for b in f.read()]

padding = (-len(bytestrs)) % bytes_per_line
bytestrs += ["00"] * padding

results = []
for i in range(0, len(bytestrs), bytes_per_line):
    results.append("".join(bytestrs[i + bytes_per_line - j - 1] for j in range(bytes_per_line)))

print("\n".join(results))
