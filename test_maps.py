import os, subprocess, time

INVALID_PATH = "maps/maps/invalid/"
VALGRINDS_COMMS = "valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes".split()
INTERVAL = 1.5
for path in os.listdir(INVALID_PATH):#["empty_file.ber", "no_walls.ber"]
	print(f"testing: {INVALID_PATH + path}")
	#random_string = ''.join(random.choices(string.ascii_letters + string.digits, k=random.randint(min_len/2, max_len/2))) + ''.join(random.choices(message, k=random.randint(min_len/2, max_len/2)))
	subprocess.call(["cat", INVALID_PATH + path])
	print()
	subprocess.call([*VALGRINDS_COMMS,"./so_long", INVALID_PATH + path])

	input()