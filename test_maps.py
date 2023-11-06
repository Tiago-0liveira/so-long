import os, subprocess, time

INVALID_PATH = "maps/maps/invalid/"
INTERVAL = 1.5
for path in ["empty_file.ber", "no_walls.ber"]:#os.listdir(INVALID_PATH):
    print(f"testing: {INVALID_PATH + path}")
    #random_string = ''.join(random.choices(string.ascii_letters + string.digits, k=random.randint(min_len/2, max_len/2))) + ''.join(random.choices(message, k=random.randint(min_len/2, max_len/2)))
    subprocess.call(["valgrind", "--leak-check=full", "--show-leak-kinds=all","./so_long", INVALID_PATH + path])

    input()