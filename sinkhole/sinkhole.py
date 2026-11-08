import os
import sys
import datetime
import struct
import socket
import subprocess
import threading


SINKHOLE_PORT = 9091
LOG_FILE = "sinkhole_telemetry.log"

def read(conn, size):
	buf = b""
	while len(buf) != size:
		buf += conn.recv(size - len(buf))
	return buf

def recv_all(sock, size):
	data = b''

	while len(data) < size:
		packet = sock.recv(size -len(data))
		if not packet:
			print("Socket closed")
		data += packet

	return data
	
def save(filename, conn):

	date = str(datetime.datetime.now()).replace(" ", "_").replace(":", "-")
	filename = date + filename
	size = struct.unpack("Q", recv_all(conn, 8))[0]
	with open(filename, "wb") as f:
		remaining = size
		while remaining > 0:
			chunk = conn.recv(min(4096, remaining))
			if not chunk:
				break

			f.write(chunk)
			remaining -= len(chunk)
			
			
def log_telemetry(msg: str):
  ts = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
  record = f"[{ts}] {msg}"
  print(record)
  with open(LOG_FILE, "a", encoding="utf-8") as f:
    f.write(record + "\n")


def handle_client(conn: socket.socket, addr: tuple):
  log_telemetry(f"Connection at {addr[0]}:{addr[1]}")

  try:
    os_byte = conn.recv(1)
    if not os_byte:
      return

    if os_byte == b"W":
      remote_os = "Windows"
    elif os_byte == b"U":
      remote_os = "Linux"
    else:
      remote_os = f"Unknown ({os_byte!r})"

    log_telemetry(f"{addr[0]} -- {remote_os}")

    save("_windows_system_info.txt", conn)
    log_telemetry(f"[+]Completed. End session {addr[0]}.")

  except Exception as e:
    log_telemetry(f"[!]ERROR {addr[0]}: {e}")
  finally:
    conn.close()


def run_sinkhole(port: int):
  log_telemetry(f"Port {port}")
  srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
  srv.bind(("", port))
  srv.listen(10)

  try:
    while True:
      conn, addr = srv.accept()
      handle_client(conn, addr)
  except KeyboardInterrupt:
    log_telemetry("[*]Stopped.")
  finally:
    srv.close()



port = int(sys.argv[1]) if len(sys.argv) > 1 else SINKHOLE_PORT
run_sinkhole(port)
