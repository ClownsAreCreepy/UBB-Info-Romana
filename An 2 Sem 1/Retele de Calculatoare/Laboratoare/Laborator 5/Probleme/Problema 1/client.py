import socket
import struct

def main(ip="127.0.0.1", port=1234):
    # connect to the C server
    with socket.create_connection((ip, port)) as sock:
        # read n
        n = int(input("Lungimea sirului: "))
        if n < 0 or n > 65535:
            print("n out of range (0..65535)")
            return

        # send n
        sock.sendall(struct.pack("!H", n))

        # send the n numbers
        for i in range(n):
            x = int(input(f"x[{i}] = "))
            if x < 0 or x > 65535:
                print("valoare out of range (0..65535)")
                return
            sock.sendall(struct.pack("!H", x))

        # receive the sum
        data = sock.recv(2)
        if len(data) < 2:
            print("recv failed")
            return
        (suma,) = struct.unpack("!H", data)
        print(f"Suma este {suma}")

if __name__ == "__main__":
    # optional: allow ip/port via CLI args
    import sys
    if len(sys.argv) >= 3:
        main(sys.argv[1], int(sys.argv[2]))
    else:
        main()

