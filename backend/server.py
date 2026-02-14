from http.server import BaseHTTPRequestHandler, HTTPServer

Port=5001

class Handler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        self.wfile.write(bytes("Hello, World!", "utf8"))

def run():
    server=HTTPServer(("localhost", Port), Handler)
    print(f'Server running on port {Port}...')
    server.serve_forever()

if __name__ == '__main__':
    run()